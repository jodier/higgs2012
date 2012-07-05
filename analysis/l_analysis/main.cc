/*-------------------------------------------------------------------------*/

#include <cmath>
#include <cstring>
#include <iostream>

#include <egammaAnalysisUtils/CaloIsoCorrection.h>

#include "main.h"

/*-------------------------------------------------------------------------*/

void core::execute(TChain *chain)
{
	std::cout << "/*-------------------------------------------------------------------------*/" << std::endl;
	std::cout << "/* EXECUTE                                                                 */" << std::endl;
	std::cout << "/*-------------------------------------------------------------------------*/" << std::endl;

	TLeptonFinder algo(chain);
	algo.Loop();

	/**/

	TFile file(core::output.c_str(), "recreate");

	file.cd();

	algo.m_tree1.Write();
	algo.m_tree2.Write();

	file.Close();

}
/*-------------------------------------------------------------------------*/

extern Float_t getMassCut(Float_t H_mass);

/*-------------------------------------------------------------------------*/

void TLeptonFinder::Loop(void)
{
	Int_t elIndexNr;
	Int_t muCB_PLUS_STIndexNr;
	Int_t muStandAloneIndexNr;
	Int_t muCaloIndexNr;

	Int_t elIndexArray[1024];
	Int_t muCB_PLUS_STIndexArray[1024];
	Int_t muStandAloneIndexArray[1024];
	Int_t muCaloIndexArray[1024];

	TLeptonType elTypeArray[1024];
	TLeptonType muCB_PLUS_STTypeArray[1024];
	TLeptonType muStandAloneTypeArray[1024];
	TLeptonType muCaloTypeArray[1024];

	Float_t __el_et = core::configFltLookup("higgs_el_et");
	Float_t __mu_staco_pt = core::configFltLookup("higgs_mu_staco_pt");
	Float_t __mu_calo_pt = core::configFltLookup("higgs_mu_calo_pt");

	const Long64_t eventNr = fChain->GetEntries();

	for(Long64_t event = 0; event < eventNr; event++)
	{
		/*---------------------------------------------------------*/

		LoadEvent(event, eventNr);

		if(event == 0)
		{
			triggerInit();
		}

		fixeEnergy();

		/*---------------------------------------------------------*/
		/* AT LEAST 3 PRIMARY TRACKS AND LAR ERROR		   */
		/*---------------------------------------------------------*/

		nPV2 = 0;
		nPV3 = 0;

		for(Int_t i = 0; i < Int_t(vxp_nTracks->size()); i++)
		{
			if(vxp_nTracks->at(i) >= 2) {
				nPV2++;
			}

			if(vxp_nTracks->at(i) >= 3) {
				nPV3++;
			}
		}

		/**/
#ifdef __IS_MC
		Bool_t isOkVertex = (nPV3 > 0) && (0x00000000001);
#else
		Bool_t isOkVertex = (nPV3 > 0) && (larError != 2);
#endif
		/*---------------------------------------------------------*/
		/* TRIGGERS						   */
		/*---------------------------------------------------------*/

		Bool_t isOkElTrigger = getElTrigger();
		Bool_t isOkMuTrigger = getMuTrigger();

		/*---------------------------------------------------------*/
		/* SELECTIONS						   */
		/*---------------------------------------------------------*/

		elIndexNr = 0;
		muCB_PLUS_STIndexNr = 0;
		muStandAloneIndexNr = 0;
		muCaloIndexNr = 0;

		elNr0 += el_n;
		muNr0 += mu_staco_n + mu_calo_n;

		if(isOkVertex != false)
		{
			elNr1 += el_n;
			muNr1 += mu_staco_n + mu_calo_n;

			if(isOkElTrigger != false
			   ||
			   isOkMuTrigger != false
			 ) {
				elNr2 += el_n;
				muNr2 += mu_staco_n + mu_calo_n;

				/*--------------------------------------*/
				/* STACO MUONS				*/
				/*--------------------------------------*/

				for(Int_t i = 0; i < mu_staco_n; i++)
				{
					if(checkObject(i, TYPE_MUON_CB_PLUS_ST, __el_et, __mu_staco_pt, __mu_calo_pt) != false)
					{
						muCB_PLUS_STIndexArray[muCB_PLUS_STIndexNr] = i;
						muCB_PLUS_STTypeArray[muCB_PLUS_STIndexNr] = TYPE_MUON_CB_PLUS_ST;

						muCB_PLUS_STIndexNr++;
					}

					if(checkObject(i, TYPE_MUON_STANDALONE, __el_et, __mu_staco_pt, __mu_calo_pt) != false)
					{
						muStandAloneIndexArray[muStandAloneIndexNr] = i;
						muStandAloneTypeArray[muStandAloneIndexNr] = TYPE_MUON_STANDALONE;

						muStandAloneIndexNr++;
					}
				}

				/*--------------------------------------*/
				/* CALO MUONS				*/
				/*--------------------------------------*/

				for(Int_t i = 0; i < mu_calo_n; i++)
				{
					if(checkObject(i, TYPE_MUON_CALO, __el_et, __mu_staco_pt, __mu_calo_pt) != false)
					{
						muCaloIndexArray[muCaloIndexNr] = i;
						muCaloTypeArray[muCaloIndexNr] = TYPE_MUON_CALO;

						muCaloIndexNr++;
					}
				}

				/*--------------------------------------*/
				/* CALO - CB_PLUS_ST OVERLAP		*/
				/*--------------------------------------*/

				Int_t tmp1 = muCB_PLUS_STIndexNr;

				for(Int_t i = 0; i < muCaloIndexNr; i++)
				{
					Bool_t isOk = true;

					Int_t index = muCaloIndexArray[i];

					Float_t calo_eta = -logf(tanf(0.5f * mu_calo_id_theta->at(index)));
					Float_t calo_phi = mu_calo_id_phi->at(index);

					for(Int_t j = 0; j < tmp1; j++)
					{
						Int_t xedni = muCB_PLUS_STIndexArray[j];

						Float_t cb_plus_st_eta;
						Float_t cb_plus_st_phi;

						switch(muCB_PLUS_STTypeArray[j])
						{
							case TYPE_MUON_CB_PLUS_ST:
							case TYPE_MUON_STANDALONE:
								cb_plus_st_eta = -logf(tanf(0.5f * mu_staco_id_theta->at(xedni)));
								cb_plus_st_phi = mu_staco_id_phi->at(xedni);
								break;

							case TYPE_MUON_CALO:
								cb_plus_st_eta = -logf(tanf(0.5f * mu_calo_id_theta->at(xedni)));
								cb_plus_st_phi = mu_calo_id_phi->at(xedni);
								break;

							default:
								std::cout << "Oula !!!" << std::endl;

								exit(1);
						}

						if(__dR2(calo_eta, cb_plus_st_eta, calo_phi, cb_plus_st_phi) < 0.1f * 0.1f)
						{
							isOk = false;

							muNr13--;

							break;
						}
					}

					if(isOk != false)
					{
						muCB_PLUS_STIndexArray[muCB_PLUS_STIndexNr] = muCaloIndexArray[i];
						muCB_PLUS_STTypeArray[muCB_PLUS_STIndexNr] = muCaloTypeArray[i];

						muCB_PLUS_STIndexNr++;
					}
				}

				/*--------------------------------------*/
				/* STANDALONE - CB_PLUS_ST OVERLAP	*/
				/*--------------------------------------*/

				Int_t tmp2 = muCB_PLUS_STIndexNr;

				for(Int_t i = 0; i < muStandAloneIndexNr; i++)
				{
					Bool_t isOk = true;

					Int_t index = muStandAloneIndexArray[i];

					Float_t standalone_eta = -logf(tanf(0.5f * mu_staco_id_theta->at(index)));
					Float_t standalone_phi = mu_staco_id_phi->at(index);

					for(Int_t j = 0; j < tmp2; j++)
					{
						Int_t xedni = muCB_PLUS_STIndexArray[j];

						Float_t cb_plus_st_eta;
						Float_t cb_plus_st_phi;

						switch(muCB_PLUS_STTypeArray[j])
						{
							case TYPE_MUON_CB_PLUS_ST:
							case TYPE_MUON_STANDALONE:
								cb_plus_st_eta = -logf(tanf(0.5f * mu_staco_id_theta->at(xedni)));
								cb_plus_st_phi = mu_staco_id_phi->at(xedni);
								break;

							case TYPE_MUON_CALO:
								cb_plus_st_eta = -logf(tanf(0.5f * mu_calo_id_theta->at(xedni)));
								cb_plus_st_phi = mu_calo_id_phi->at(xedni);
								break;

							default:
								std::cout << "Oula !!!" << std::endl;

								exit(1);
						}

						if(__dR2(standalone_eta, cb_plus_st_eta, standalone_phi, cb_plus_st_phi) < 0.2f * 0.2f)
						{
							isOk = false;

							muNr14--;

							break;
						}
					}

					if(isOk != false)
					{
						muCB_PLUS_STIndexArray[muCB_PLUS_STIndexNr] = muStandAloneIndexArray[i];
						muCB_PLUS_STTypeArray[muCB_PLUS_STIndexNr] = muStandAloneTypeArray[i];

						muCB_PLUS_STIndexNr++;
					}
				}

				/*--------------------------------------*/
				/* ELECTRONS				*/
				/*--------------------------------------*/

				for(Int_t i = 0; i < el_n; i++)
				{
					if(checkObject(i, TYPE_ELECTRON, __el_et, __mu_staco_pt, __mu_calo_pt) != false)
					{
						if(checkOverlapping(i, TYPE_ELECTRON, __el_et, __mu_staco_pt, __mu_calo_pt, muCB_PLUS_STIndexNr, muCB_PLUS_STIndexArray, muCB_PLUS_STTypeArray) != false)
						{
							elIndexArray[elIndexNr] = i;
							elTypeArray[elIndexNr] = TYPE_ELECTRON;

							elIndexNr++;
						}
					}
				}

				/*--------------------------------------*/
			}
		}

		/*---------------------------------------------------------*/



		/*---------------------------------------------------------*/

		if((((((elIndexNr))))) >= 2
		   ||
		   muCB_PLUS_STIndexNr >= 2
		 ) {
			m_tree1.Fill();
			m_tree2.Fill();
		}

		/*---------------------------------------------------------*/
	}

	std::cout << "#############################################################################" << std::endl;
	std::cout << "# ELECTRON STACO                                                            #" << std::endl;
	std::cout << "#############################################################################" << std::endl;

	std::cout << "before any cut   : " << elNr0 << std::endl;
	std::cout << "after vertex     : " << elNr1 << std::endl;
	std::cout << "after trigger    : " << elNr2 << std::endl;
	std::cout << "after author=1||3: " << elNr3 << std::endl;
	std::cout << "after loose++    : " << elNr4 << std::endl;
	std::cout << "after |η|<2.47   : " << elNr5 << std::endl;
	std::cout << "after pt>7       : " << elNr6 << std::endl;
	std::cout << "after OQ         : " << elNr7 << std::endl;
	std::cout << "after z0         : " << elNr8 << std::endl;
	std::cout << "after e-e overlap: " << elNr9 << std::endl;
	std::cout << "after e-e overlap: " << elNr10 << std::endl;
	std::cout << "after e-µ overlap: " << elNr11 << std::endl;

	std::cout << "#############################################################################" << std::endl;
	std::cout << "# MUON STACO                                                                #" << std::endl;
	std::cout << "#############################################################################" << std::endl;

	muNr13 += muNr12;
	muNr14 += muNr13;

	std::cout << "before any cut     : " << muNr0 << std::endl;
	std::cout << "after vertex       : " << muNr1 << std::endl;
	std::cout << "after trigger      : " << muNr2 << std::endl;
	std::cout << "after author=6||7  : " << muNr3 << std::endl;
	std::cout << "after d0           : " << muNr4 << std::endl;
	std::cout << "after |η|<2.5      : " << muNr5 << std::endl;
	std::cout << "after pt>6         : " << muNr6 << std::endl;
	std::cout << "after b-Layer      : " << muNr7 << std::endl;
	std::cout << "after Pix          : " << muNr8 << std::endl;
	std::cout << "after SCT          : " << muNr9 << std::endl;
	std::cout << "after holes        : " << muNr10 << std::endl;
	std::cout << "after TRT/outliers : " << muNr11 << std::endl;
	std::cout << "after z0           : " << muNr12 << std::endl;
	std::cout << "after calo overlap : " << muNr13 << std::endl;
	std::cout << "after stand overlap: " << muNr14 << std::endl;

	std::cout << "#############################################################################" << std::endl;
}

/*-------------------------------------------------------------------------*/


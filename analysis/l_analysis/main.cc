/*-------------------------------------------------------------------------*/

#include <cmath>
#include <cstring>
#include <iostream>

#include "main.h"

#ifdef __IS_MC
  #include <HiggsZZ4lUtils/McOverlapRemoval.h>
#endif
	

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

	algo.m_tree0.Write();
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

	//---------------------------------------------------------//
	// Higgs cutflow
	//---------------------------------------------------------//

	Int_t NbEventSample = 0;

	Int_t higgsNr0 = 0;
	Int_t higgsNr1 = 0;
	Int_t higgsNr2 = 0;
	Int_t higgsNr3 = 0;

	//---------------------------------------------------------//

	for(Long64_t event = 0; event < eventNr; event++)
//	for(Long64_t event = 0; event < 1000; event++)
	{
		/*---------------------------------------------------------*/

		NbEventSample++ ; 

		/*---------------------------------------------------------*/
		LoadEvent(event, eventNr);

		if(event == 0)
		{
			triggerInit();
		}

		/*---------------------------------------------------------*/

#ifdef __IS_MC
//For ZZ and ttbar remove event in mass region 110-150 GeV
		if(killEvent(mc_channel_number, 146369, mc_n, mc_pt, mc_eta, mc_phi, mc_m, mc_status, mc_pdgId))
			continue;
#endif
		/*---------------------------------------------------------*/

		//fixeEnergy();

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
   #ifdef __YEAR2011
		Bool_t isOkVertex = (nPV3 > 0) && (larError != 2);
   #endif
   #ifdef __YEAR2012
		Bool_t isOkVertex = (nPV3 > 0) && (larError != 2) && ((coreFlags&0x40000) == 0) && (tileError != 2);
   #endif
#endif
		/*---------------------------------------------------------*/
		/* TRIGGERS						   */
		/*---------------------------------------------------------*/

		Bool_t isOkElTrigger = getElTrigger();
		Bool_t isOkMuTrigger = getMuTrigger();
		Bool_t isOkElMuTrigger = getElMuTrigger();

		/*---------------------------------------------------------*/
		/* SELECTIONS						   */
		/*---------------------------------------------------------*/
		//if (EventNumber != 28491) continue;

		elIndexNr = 0;
		muCB_PLUS_STIndexNr = 0;
		muStandAloneIndexNr = 0;
		muCaloIndexNr = 0;

		elNr0 += el_n;
		muNr0 += mu_staco_n + mu_calo_n;

		Int_t isOK_id = 0;				

		if(isOkVertex != false)
		{
			higgsNr0 += 1;
			higgsNr1 += 1;
			higgsNr2 += 1;

			elNr1 += el_n;
			muNr1 += mu_staco_n + mu_calo_n;

			if(isOkElTrigger != false
			   ||
			   isOkMuTrigger != false
			   ||
			   isOkElMuTrigger != false
			 ) {
				higgsNr3 += 1;

				elNr2 += el_n;
				muNr2 += mu_staco_n + mu_calo_n;

				/*-----------------------------------------*/
				/* STACO MUONS				   */
				/*-----------------------------------------*/

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

				/*-----------------------------------------*/
				/* STANDALONE - CB_PLUS_ST OVERLAP	   */
				/*-----------------------------------------*/

				Int_t tmp2 = muCB_PLUS_STIndexNr;

				for(Int_t i = 0; i < muStandAloneIndexNr; i++)
				{
					Bool_t isOk = true;

					Int_t index = muStandAloneIndexArray[i];

					Float_t standalone_eta = mu_staco_eta->at(index);
					Float_t standalone_phi = mu_staco_phi->at(index);

					for(Int_t j = 0; j < tmp2; j++)
					{
						Int_t xedni = muCB_PLUS_STIndexArray[j];

						Float_t cb_plus_st_eta;
						Float_t cb_plus_st_phi;

						switch(muCB_PLUS_STTypeArray[j])
						{
							case TYPE_MUON_CB_PLUS_ST:
							case TYPE_MUON_STANDALONE:
								cb_plus_st_eta = mu_staco_eta->at(xedni);
								cb_plus_st_phi = mu_staco_phi->at(xedni);
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

				/*-----------------------------------------*/
				/* ELECTRONS				   */
				/*-----------------------------------------*/


				for(Int_t i = 0; i < el_n; i++)
				{
//					cout << "######electron index " <<i<< endl;
//					cout << "el_author " << el_author->at(i) << endl;
//					cout << "l_pt[i] " << electronGetEt(i)<< endl;
//					cout << "eta[i]" << electronGetEtaDirection(i) << endl;
//					cout << "isLM " << ((el_isEMOk_at(i) & (1<<3)) == 8) << endl;

					if(checkObject(i, TYPE_ELECTRON, __el_et, __mu_staco_pt, __mu_calo_pt) != false)
					{
						if(checkOverlapping(i, TYPE_ELECTRON, __el_et, __mu_staco_pt, __mu_calo_pt,
									muCB_PLUS_STIndexNr, muCB_PLUS_STIndexArray, muCB_PLUS_STTypeArray) != false)
						{
							elIndexArray[elIndexNr] = i;
							elTypeArray[elIndexNr] = TYPE_ELECTRON;

							elIndexNr++;
							if( (el_isEMOk_at(i) & (1 << 3)) == 8) isOK_id++;
						}
					}
				}

				/*-----------------------------------------*/
				/* CALO MUONS				   */
				/*-----------------------------------------*/

				for(Int_t i = 0; i < mu_calo_n; i++)
				{
					if(checkObject(i, TYPE_MUON_CALO, __el_et, __mu_staco_pt, __mu_calo_pt) != false)
					{
						muCaloIndexArray[muCaloIndexNr] = i;
						muCaloTypeArray[muCaloIndexNr] = TYPE_MUON_CALO;

						muCaloIndexNr++;
					}
				}

				/*-----------------------------------------*/
				/* CALO - CB_PLUS_ST/ELECTRONS OVERLAP 	   */
				/*-----------------------------------------*/

				Int_t tmp1 = muCB_PLUS_STIndexNr;
				Int_t tmp3 = elIndexNr;


				for(Int_t i = 0; i < muCaloIndexNr; i++)
				{
					Bool_t isOk_mu_CB_ST = true;
					Bool_t isOk_el = true;

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
								cb_plus_st_eta = mu_staco_eta->at(xedni);
								cb_plus_st_phi = mu_staco_phi->at(xedni);
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
							isOk_mu_CB_ST = false;

							break;
						}
					}

					if(isOk_mu_CB_ST != false){
						for(Int_t j = 0; j < tmp3; j++)
						{
							Int_t xedni = elIndexArray[j];
							if((el_isEMOk_at(xedni) & (1<<3)) != 8) continue; //ML
							if(__dR2(el_Unrefittedtrack_eta->at(xedni), calo_eta, el_Unrefittedtrack_phi->at(xedni), calo_phi) < 0.02f * 0.02f)
							{
								isOk_el = false;
								break;
							}
						}
					}

					if((isOk_mu_CB_ST != false) && (isOk_el != false))
					{
						muCB_PLUS_STIndexArray[muCB_PLUS_STIndexNr] = muCaloIndexArray[i];
						muCB_PLUS_STTypeArray[muCB_PLUS_STIndexNr] = muCaloTypeArray[i];

						muCB_PLUS_STIndexNr++;
					}
					else muNr13--;
				}

				/*-----------------------------------------*/
			}
		}

		/*---------------------------------------------------------*/
		/* D0 BIAS						   */
		/*---------------------------------------------------------*/
#if defined( __YEAR2012) && defined(__IS_MC)
		Float_t d0Bias = 2.0e-3f;
#else
		Float_t d0Bias = 0.0000f;
#endif
		/*---------------------------------------------------------*/
		/*---------------------------------------------------------*/
		/*- Event informations					  -*/
		/*---------------------------------------------------------*/
		/*---------------------------------------------------------*/
		m_NbEvtSample = NbEventSample;
		m_RunNumber = RunNumber;
		m_EventNumber = EventNumber;
		m_LumiBlock = lbn;

		m_nPV2 = nPV2;
		m_nIntPerXing = averageIntPerXing;
		m_EtMiss = MET_RefFinal_et;

		m_elTrigger = isOkElTrigger;
		m_muTrigger = isOkMuTrigger;

		/*---------------------------------------------------------*/
		/*---------------------------------------------------------*/
		/*- ELECTRONS						  -*/
		/*---------------------------------------------------------*/
		/*---------------------------------------------------------*/

		int nTRTTotal;
		int nTRTTotalHigh;

		m_l[0].n = elIndexNr;

		for(Int_t i = 0; i < elIndexNr; i++)
		{
			Int_t index = elIndexArray[i];

			/**/

			switch(elTypeArray[i])
			{
				case TYPE_ELECTRON:

					Z0smearObject(index, TYPE_ELECTRON);
					D0smearObject(index, TYPE_ELECTRON);

					m_l[0].weight1[i] = eventGetWeight1();
					m_l[0].weight2[i] = eventGetWeight2();
					m_l[0].weight3[i] = eventGetWeight3(index, TYPE_ELECTRON);

					m_l[0].l_lepton[i] = TYPE_ELECTRON;
					m_l[0].l_id[i] = el_isEMOk_at(index);

					m_l[0].l_tight[i] = el_tight->at(index) != 0;
					m_l[0].l_triggerMatch[i] = triggerMatch(index, TYPE_ELECTRON);
					m_l[0].l_truthMatch[i] = truthMatch(index, TYPE_ELECTRON);

					m_l[0].l_charge[i] = el_charge->at(index);

					m_l[0].l_e[i] = smearObject(index, TYPE_ELECTRON);
					m_l[0].l_pt[i] = electronGetEt(index);
					m_l[0].l_trackpt[i] = el_trackpt->at(index);
					m_l[0].l_EtRaw[i] = electronGetRawEt(index);

					m_l[0].l_eta[i] = electronGetEtaDirection(index);
					m_l[0].l_cl_eta[i] = el_cl_eta->at(index);

					m_l[0].l_phi[i] = electronGetPhiDirection(index);
					m_l[0].l_etas2[i] = el_etas2->at(index);
					m_l[0].l_phis2[i] = el_phis2->at(index);

					m_l[0].l_id_theta[i] = -999999;
					m_l[0].l_id_qoverp[i] = -999999;

					m_l[0].l_z0[i] = el_trackz0pvunbiased->at(index);
					m_l[0].l_d0[i] = el_trackd0pvunbiased->at(index) - d0Bias;
					m_l[0].l_clIso20[i] = el_Etcone20_at(index);
					m_l[0].l_tkIso20[i] = el_ptcone20->at(index);
					m_l[0].l_clIso30[i] = el_Etcone30_at(index);
					m_l[0].l_tkIso30[i] = el_ptcone30->at(index);
					m_l[0].l_d0sigma[i] = fabs((el_trackd0pvunbiased->at(index) - d0Bias) / el_tracksigd0pvunbiased->at(index));

					nTRTTotal     = el_nTRTHits     ->at(index) + el_nTRTOutliers     ->at(index);
					nTRTTotalHigh = el_nTRTHighTHits->at(index) + el_nTRTHighTOutliers->at(index);

					m_l[0].l_f1[i] = el_f1->at(index);
					m_l[0].l_rphi[i] = el_rphi->at(index);
					m_l[0].l_nBlayerHits[i] = el_nBLHits->at(index);
					m_l[0].l_nPixelHits[i] = el_nPixHits->at(index);
					m_l[0].l_nTRTTotal[i] = nTRTTotal;
					m_l[0].l_rTRT[i] = nTRTTotal > 0 ? float(nTRTTotalHigh) / float(nTRTTotal) : 0.0f;

					/**/
#ifdef __IS_MC
					m_l[0].l_type[i] = el_type->at(index);
					m_l[0].l_origin[i] = el_origin->at(index);
					m_l[0].l_typebkg[i] = el_typebkg->at(index);
					m_l[0].l_originbkg[i] = el_originbkg->at(index);
					m_l[0].l_truth_type[i] = el_truth_type->at(index);
					m_l[0].l_truth_mothertype[i] = el_truth_mothertype->at(index);
#else
					m_l[0].l_type[i] = -999999;
					m_l[0].l_origin[i] = -999999;
					m_l[0].l_typebkg[i] = -999999;
					m_l[0].l_originbkg[i]= -999999;
					m_l[0].l_truth_type[i] = -999999;
					m_l[0].l_truth_mothertype[i] = -999999;

#endif

					break;

				default:
					std::cout << "Oula !!!" << std::endl;

					exit(1);
			}
		}

		/*---------------------------------------------------------*/
		/*---------------------------------------------------------*/
		/*- MUONS						  -*/
		/*---------------------------------------------------------*/
		/*---------------------------------------------------------*/

		m_l[1].n = muCB_PLUS_STIndexNr;

		for(Int_t i = 0; i < muCB_PLUS_STIndexNr; i++)
		{
			Int_t index = muCB_PLUS_STIndexArray[i];

			/**/

			switch(muCB_PLUS_STTypeArray[i])
			{
				case TYPE_MUON_CB_PLUS_ST:
				case TYPE_MUON_STANDALONE:

					Z0smearObject(index, TYPE_MUON_CB_PLUS_ST);
					D0smearObject(index, TYPE_MUON_CB_PLUS_ST);

					m_l[1].weight1[i] = eventGetWeight1();
					m_l[1].weight2[i] = eventGetWeight2();
					m_l[1].weight3[i] = eventGetWeight3(index, muCB_PLUS_STTypeArray[i]);

					m_l[1].l_lepton[i] = muCB_PLUS_STTypeArray[i];
					m_l[1].l_id[i] = 0x00;
					m_l[1].l_tight[i] = mu_staco_tight->at(index) != 0;
					m_l[1].l_triggerMatch[i] = triggerMatch(index, muCB_PLUS_STTypeArray[i]);
					m_l[1].l_truthMatch[i] = truthMatch(index, muCB_PLUS_STTypeArray[i]);

					m_l[1].l_charge[i] = mu_staco_charge->at(index);
					m_l[1].l_e[i] = mu_staco_E->at(index);
					m_l[1].l_pt[i] = mu_staco_pt->at(index);
					m_l[1].l_trackpt[i] = -999999;
					m_l[1].l_EtRaw[i] = -999999;
					m_l[1].l_eta[i] = mu_staco_eta->at(index);
					m_l[1].l_phi[i] = mu_staco_phi->at(index);

					m_l[1].l_etas2[i] = -999999;
					m_l[1].l_phis2[i] = -999999;
					m_l[1].l_cl_eta[i] = -999999;

					m_l[1].l_id_theta[i] = mu_staco_id_theta->at(index);
					m_l[1].l_id_qoverp[i] = mu_staco_id_qoverp->at(index);

					m_l[1].l_z0[i] = mu_staco_trackz0pvunbiased->at(index);

					if (muCB_PLUS_STTypeArray[i] != TYPE_MUON_STANDALONE){
						m_l[1].l_d0[i] = mu_staco_trackd0pvunbiased->at(index) - d0Bias;
						m_l[1].l_d0sigma[i] = fabs((mu_staco_trackd0pvunbiased->at(index) - d0Bias) / mu_staco_tracksigd0pvunbiased->at(index));
					}
					else {
						m_l[1].l_d0[i] = mu_staco_trackd0pvunbiased->at(index);
						m_l[1].l_d0sigma[i] = fabs((mu_staco_trackd0pvunbiased->at(index)) / mu_staco_tracksigd0pvunbiased->at(index));
					}

					m_l[1].l_clIso20[i] = mu_staco_etcone20->at(index);
					m_l[1].l_tkIso20[i] = mu_staco_ptcone20->at(index);
					m_l[1].l_clIso30[i] = mu_staco_etcone30->at(index);
					m_l[1].l_tkIso30[i] = mu_staco_ptcone30->at(index);

					m_l[1].l_f1[i] = -999999;
					m_l[1].l_rphi[i] = -999999;
					m_l[1].l_nBlayerHits[i] = -999999;
					m_l[1].l_nPixelHits[i] = -999999;
					m_l[1].l_rTRT[i] = -999999;
					m_l[1].l_nTRTTotal[i] = -999999;
					/**/

					m_l[1].l_type[i] = -999999;
					m_l[1].l_origin[i] = -999999;
					m_l[1].l_typebkg[i] = -999999;
					m_l[1].l_originbkg[i] = -999999;
#ifdef __IS_MC
					m_l[1].l_truth_type[i] = mu_staco_truth_type->at(index);
					m_l[1].l_truth_mothertype[i] = mu_staco_truth_mothertype->at(index);
#else
					m_l[1].l_truth_type[i] = -999999;
					m_l[1].l_truth_mothertype[i] = -999999;
#endif
					break;

				case TYPE_MUON_CALO:

					Z0smearObject(index, TYPE_MUON_CALO);
					D0smearObject(index, TYPE_MUON_CALO);

					m_l[1].weight1[i] = eventGetWeight1();
					m_l[1].weight2[i] = eventGetWeight2();
					m_l[1].weight3[i] = eventGetWeight3(index, TYPE_MUON_CALO);

					m_l[1].l_lepton[i] = TYPE_MUON_CALO;
					m_l[1].l_id[i] = 0x00;
					m_l[1].l_tight[i] = mu_calo_tight->at(index) != 0;
					m_l[1].l_triggerMatch[i] = triggerMatch(index, TYPE_MUON_CALO);
					m_l[1].l_truthMatch[i] = truthMatch(index, TYPE_MUON_CALO);

					m_l[1].l_charge[i] = mu_calo_charge->at(index);
					m_l[1].l_e[i] = mu_calo_E->at(index);
					m_l[1].l_pt[i] = mu_calo_pt->at(index);
					m_l[1].l_trackpt[i] = -999999;
					m_l[1].l_EtRaw[i] = -999999;
					m_l[1].l_eta[i] = mu_calo_eta->at(index);
					m_l[1].l_phi[i] = mu_calo_phi->at(index);

					m_l[1].l_etas2[i] = -999999;
					m_l[1].l_phis2[i] = -999999;
					m_l[1].l_cl_eta[i] = -999999;

					m_l[1].l_id_theta[i] = mu_calo_id_theta->at(index);
					m_l[1].l_id_qoverp[i] = mu_calo_id_qoverp->at(index);


					m_l[1].l_z0[i] = mu_calo_trackz0pvunbiased->at(index);
					m_l[1].l_d0[i] = mu_calo_trackd0pvunbiased->at(index) - d0Bias;

					m_l[1].l_clIso20[i] = mu_calo_etcone20->at(index);
					m_l[1].l_tkIso20[i] = mu_calo_ptcone20->at(index);
					m_l[1].l_clIso20[i] = mu_calo_etcone30->at(index);
					m_l[1].l_tkIso20[i] = mu_calo_ptcone30->at(index);

					m_l[1].l_d0sigma[i] = fabs((mu_calo_trackd0pvunbiased->at(index) - d0Bias) / mu_calo_tracksigd0pvunbiased->at(index));

					m_l[1].l_f1[i] = -999999;
					m_l[1].l_rphi[i] = -999999;
					m_l[1].l_nBlayerHits[i] = -999999;
					m_l[1].l_nPixelHits[i] = -999999;
					m_l[1].l_rTRT[i] = -999999;
					m_l[1].l_nTRTTotal[i] = -999999;

					/**/

					m_l[1].l_type[i] = -999999;
					m_l[1].l_origin[i] = -999999;
					m_l[1].l_typebkg[i] = -999999;
					m_l[1].l_originbkg[i] = -999999;
#ifdef __IS_MC
					m_l[1].l_truth_type[i] = mu_calo_truth_type->at(index);
					m_l[1].l_truth_mothertype[i] = mu_calo_truth_mothertype->at(index);
#else
					m_l[1].l_truth_type[i] = -999999;
					m_l[1].l_truth_mothertype[i] = -999999;
#endif
					break;

				default:
					std::cout << "Oula !!!" << std::endl;

					exit(1);
			}
		}

		/*---------------------------------------------------------*/

		if( ( (elIndexNr >= 2) && (isOK_id >= 2) )
		     ||
		    (muCB_PLUS_STIndexNr >= 2)
		 ) {
			m_tree0.Fill();
			m_tree1.Fill();
			m_tree2.Fill();
		}

		/*---------------------------------------------------------*/
	}
	std::cout << "Nb evt sample    : " << NbEventSample << std::endl;
	std::cout << "#############################################################################" << std::endl;
	std::cout << "# HIGGS                                                                  #" << std::endl;
	std::cout << "#############################################################################" << std::endl;
	std::cout << "before any cut   : " << higgsNr0 << std::endl;
	std::cout << "LAr error        : " << higgsNr1 << std::endl;
	std::cout << "vertex           : " << higgsNr2 << std::endl;
	std::cout << "trigger          : " << higgsNr3 << std::endl;

	std::cout << "#############################################################################" << std::endl;
	std::cout << "# ELECTRONS                                                                  #" << std::endl;
	std::cout << "#############################################################################" << std::endl;

	std::cout << "before any cut   : " << elNr0 << std::endl;
	std::cout << "after vertex     : " << elNr1 << std::endl;
	std::cout << "after trigger    : " << elNr2 << std::endl;
	std::cout << "after author     : " << elNr3 << std::endl;
	std::cout << "after isEM       : " << elNr4 << std::endl;
	std::cout << "after |η|        : " << elNr5 << std::endl;
	std::cout << "after Et         : " << elNr6 << std::endl;
	std::cout << "after OQ         : " << elNr7 << std::endl;
	std::cout << "after z0         : " << elNr8 << std::endl;
	std::cout << "after e-e overlap: " << elNr9 << std::endl;
	std::cout << "after e-e overlap: " << elNr10 << std::endl;
	std::cout << "after e-µ overlap: " << elNr11 << std::endl;

	std::cout << "#############################################################################" << std::endl;
	std::cout << "# MUONS                                                                     #" << std::endl;
	std::cout << "#############################################################################" << std::endl;

	muNr13 += muNr12;
	muNr14 += muNr13;

	std::cout << "before any cut     : " << muNr0 << std::endl;
	std::cout << "after vertex       : " << muNr1 << std::endl;
	std::cout << "after trigger      : " << muNr2 << std::endl;
	std::cout << "after author       : " << muNr3 << std::endl;
	std::cout << "after pt          : " << muNr4 << std::endl;
	std::cout << "after |η|           : " << muNr5 << std::endl;
	std::cout << "after b-Layer      : " << muNr6 << std::endl;
	std::cout << "after Pix          : " << muNr7 << std::endl;
	std::cout << "after SCT          : " << muNr8 << std::endl;
	std::cout << "after holes        : " << muNr9 << std::endl;
	std::cout << "after TRT/outliers : " << muNr10 << std::endl;
	std::cout << "after d0           : " << muNr11 << std::endl;
	std::cout << "after z0           : " << muNr12 << std::endl;
	std::cout << "after calo overlap : " << muNr13 << std::endl;
	std::cout << "after stand overlap: " << muNr14 << std::endl;

	std::cout << "#############################################################################" << std::endl;
}

/*-------------------------------------------------------------------------*/


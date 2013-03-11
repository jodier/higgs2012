/*-------------------------------------------------------------------------*/

#ifndef __L_ANALYSIS
#define __L_ANALYSIS

/*-------------------------------------------------------------------------*/

#include "../../core/include/core.h"

/*-------------------------------------------------------------------------*/

#define MAX 2048

/*-------------------------------------------------------------------------*/

class TLeptonFinder: public TLeptonAnalysis
{
  public:
	TTree m_tree0;
	TTree m_tree1;
	TTree m_tree2;

	TLeptonFinder(TChain *chain): TLeptonAnalysis(chain)
	{
		m_tree0.SetName("event");
		m_tree1.SetName("el");
		m_tree2.SetName("mu");

		/*---------------------------------------------------------*/
		/* General Informations					   */
		/*---------------------------------------------------------*/
		m_tree0.Branch("NbEvtSample", &m_NbEvtSample, "NbEvtSample/I");

		m_tree0.Branch("RunNumber", &m_RunNumber, "RunNumber/I");
		m_tree0.Branch("EventNumber", &m_EventNumber, "EventNumber/I");
		m_tree0.Branch("LumiBlock", &m_LumiBlock, "LumiBlock/I");

		m_tree0.Branch("nPV2", &m_nPV2, "nPV2/I");
		m_tree0.Branch("nIntPerXing", &m_nIntPerXing, "nIntPerXing/F");
		m_tree0.Branch("EtMiss", &m_EtMiss, "EtMiss/F");

		m_tree0.Branch("elTrigger", &m_elTrigger, "elTrigger/I");
		m_tree0.Branch("muTrigger", &m_muTrigger, "muTrigger/I");

		/*---------------------------------------------------------*/
		/* LEPTON Informations					   */
		/*---------------------------------------------------------*/

		TTree *LTreeArray[2] = {&m_tree1, &m_tree2};

		for(int i = 0; i < 2; i++)
		{
			TTree *tree = LTreeArray[i];

			/**/

			tree->Branch("n", &m_l[i].n, "n" "/I");

			tree->Branch("weight1", m_l[i].weight1, "weight1[n]/F");
			tree->Branch("weight2", m_l[i].weight2, "weight2[n]/F");
			tree->Branch("weight3", m_l[i].weight3, "weight3[n]/F");

			tree->Branch("l_lepton", m_l[i].l_lepton, "l_lepton[n]/I");
			tree->Branch("l_id", m_l[i].l_id, "l_id[n]/I");
			tree->Branch("l_tight", m_l[i].l_tight, "l_tight[n]/I");
			tree->Branch("l_triggerMatch", m_l[i].l_triggerMatch, "l_triggerMatch[n]/I");
			tree->Branch("l_truthMatch", m_l[i].l_truthMatch, "l_truthMatch[n]/I");


			tree->Branch("l_charge", m_l[i].l_charge, "l_charge[n]/F");
			tree->Branch("l_e", m_l[i].l_e, "l_e[n]/F");
			tree->Branch("l_pt", m_l[i].l_pt, "l_pt[n]/F");
			tree->Branch("l_trackpt", m_l[i].l_trackpt, "l_trackpt[n]/F");
			tree->Branch("l_EtRaw", m_l[i].l_EtRaw, "l_EtRaw[n]/F");
			tree->Branch("l_eta", m_l[i].l_eta, "l_eta[n]/F");
			tree->Branch("l_etas2", m_l[i].l_etas2, "l_etas2[n]/F");
			tree->Branch("l_cl_eta", m_l[i].l_cl_eta, "l_cl_eta[n]/F");
			tree->Branch("l_phi", m_l[i].l_phi, "l_phi[n]/F");
			tree->Branch("l_phis2", m_l[i].l_phis2, "l_phis2[n]/F");

			tree->Branch("l_id_theta", m_l[i].l_id_theta, "l_id_theta[n]/F");
			tree->Branch("l_id_qoverp", m_l[i].l_id_qoverp, "l_id_qoverp[n]/F");

			tree->Branch("l_z0", m_l[i].l_z0, "l_z0[n]/F");
			tree->Branch("l_d0", m_l[i].l_d0, "l_d0[n]/F");

			tree->Branch("l_tkIso20", m_l[i].l_tkIso20, "l_tkIso20[n]/F");
			tree->Branch("l_clIso20", m_l[i].l_clIso20, "l_clIso20[n]/F");
			tree->Branch("l_tkIso30", m_l[i].l_tkIso30, "l_tkIso30[n]/F");
			tree->Branch("l_clIso30", m_l[i].l_clIso30, "l_clIso30[n]/F");
			tree->Branch("l_d0sigma", m_l[i].l_d0sigma, "l_d0sigma[n]/F");

			tree->Branch("l_f1", m_l[i].l_f1, "l_f1[n]/F");
			tree->Branch("l_rphi", m_l[i].l_rphi, "l_rphi[n]/F");
			tree->Branch("l_nBlayerHits", m_l[i].l_nBlayerHits, "l_nBlayerHits[n]/I");
			tree->Branch("l_nPixelHits", m_l[i].l_nPixelHits, "l_nPixelHits[n]/I");
			tree->Branch("l_nTRTTotal", m_l[i].l_nTRTTotal, "l_nTRTTotal[n]/F");
			tree->Branch("l_rTRT", m_l[i].l_rTRT, "l_rTRT[n]/F");

			/**/

			tree->Branch("l_type", m_l[i].l_type, "l_type[n]/F");
			tree->Branch("l_origin", m_l[i].l_origin, "l_origin[n]/F");
			tree->Branch("l_typebkg", m_l[i].l_typebkg, "l_typebkg[n]/F");
			tree->Branch("l_originbkg", m_l[i].l_originbkg, "l_originbkg[n]/F");
			tree->Branch("l_truth_type", m_l[i].l_truth_type, "l_truth_type[n]/F");
			tree->Branch("l_truth_mothertype", m_l[i].l_truth_mothertype, "l_truth_mothertype[n]/F");
		}

		/*---------------------------------------------------------*/
	}

	void Loop(void);

  private:

	Int_t m_NbEvtSample;
	Int_t m_RunNumber;
	Int_t m_EventNumber;
	Int_t m_LumiBlock;

	Int_t m_nPV2;
	Float_t m_nIntPerXing;
	Float_t m_EtMiss;

	Int_t m_elTrigger;
	Int_t m_muTrigger;

	struct __lepton_s
	{

		Int_t n;

		Float_t weight1[MAX];
		Float_t weight2[MAX];
		Float_t weight3[MAX];

		Int_t l_lepton[MAX];
		Int_t l_id[MAX];
		Int_t l_tight[MAX];
		Int_t l_triggerMatch[MAX];
		Int_t l_truthMatch[MAX];


		Float_t l_charge[MAX];
		Float_t l_e[MAX];
		Float_t l_pt[MAX];
		Float_t l_trackpt[MAX];
		Float_t l_EtRaw[MAX];
		Float_t l_eta[MAX];
		Float_t l_phi[MAX];

		Float_t l_etas2[MAX];
		Float_t l_phis2[MAX];

		Float_t l_cl_eta[MAX];

		Float_t l_id_theta[MAX];
		Float_t l_id_qoverp[MAX];

		Float_t l_z0[MAX];
		Float_t l_d0[MAX];

		Float_t l_clIso20[MAX];
		Float_t l_tkIso20[MAX];
		Float_t l_clIso30[MAX];
		Float_t l_tkIso30[MAX];
		Float_t l_d0sigma[MAX];

		Float_t l_f1[MAX];
		Float_t l_rphi[MAX];
		Int_t l_nBlayerHits[MAX];
		Int_t l_nPixelHits[MAX];
		Float_t l_nTRTTotal[MAX];
		Float_t l_rTRT[MAX];

		Float_t l_type[MAX];
		Float_t l_origin[MAX];
		Float_t l_typebkg[MAX];
		Float_t l_originbkg[MAX];
		Float_t l_truth_type[MAX];
		Float_t l_truth_mothertype[MAX];

	} m_l[2];

};

/*-------------------------------------------------------------------------*/

#endif /* __L_ANALYSIS */

/*-------------------------------------------------------------------------*/


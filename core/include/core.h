/*-------------------------------------------------------------------------*/

#ifndef __CORE_H
#define __CORE_H

/*-------------------------------------------------------------------------*/

#include <map>
#include <set>
#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>

#include <TChain.h>
#include <TH2.h>

/*-------------------------------------------------------------------------*/

#ifdef __IS_CORE
  #define THiggsD3PD_cxx
#endif

#include "THiggsD3PD.h"
#define TNTuple THiggsD3PD

/*-------------------------------------------------------------------------*/

#ifdef __IS_MC
  #define __isMC true
#else
  #define __isMC false
#endif

/*-------------------------------------------------------------------------*/

#define Map_t		std::map
#define String_t	std::string
#define Vector_t	std::vector

/*-------------------------------------------------------------------------*/

#define SWAP(a, b) \
	{				\
		__typeof__(a) c;	\
					\
		(c) = (a);		\
		(a) = (b);		\
		(b) = (c);		\
	}

/*-------------------------------------------------------------------------*/

#define SAME(a, b)

/*-------------------------------------------------------------------------*/

#define LoadEvent(event, eventNr) \
		if(this->LoadTree(event) < 0)									\
		{												\
			break;											\
		}												\
														\
		this->fChain->GetEntry(event);									\
														\
		if(event % 250 == 0)										\
		{												\
			std::cout << "\033[sEvent " << event << "/" << eventNr << "\033[u" << std::flush;	\
		}

/*-------------------------------------------------------------------------*/

namespace core
{
	extern String_t input;
	extern String_t output;
	extern Bool_t grid;
	extern Bool_t ER;
	extern Bool_t SM;
	extern Bool_t OF;

	/*-----------------------------------------------------------------*/
	/* CONFIG							   */
	/*-----------------------------------------------------------------*/

	typedef Map_t<String_t,  Float_t> TFltParamMap;
	typedef Map_t<String_t, String_t> TStrParamMap;

	/*-----------------------------------------------------------------*/

	extern TFltParamMap fltParamMap;
	extern TStrParamMap strParamMap;

	/*-----------------------------------------------------------------*/

	void configReset(void);

	bool configLoad(String_t fName);

	Float_t configFltLookup(String_t pName);
	String_t configStrLookup(String_t pName);

	/*-----------------------------------------------------------------*/
	/* LOADER							   */
	/*-----------------------------------------------------------------*/

	bool loader(TChain *chain1, TChain *chain2);

	/*-----------------------------------------------------------------*/
	/* CORE								   */
	/*-----------------------------------------------------------------*/

	void execute(TChain *chain);

	/*-----------------------------------------------------------------*/
}

/*-------------------------------------------------------------------------*/

#include <PileupReweighting/TPileupReweighting.h>

#include <MuonEfficiencyCorrections/AnalysisMuonConfigurableScaleFactors.h>
#include <MuonMomentumCorrections/SmearingClass.h>

#include <egammaAnalysisUtils/EnergyRescalerUpgrade.h>
//#include <egammaAnalysisUtils/egammaSFclass.h>

#include <ElectronEfficiencyCorrection/TElectronEfficiencyCorrectionTool.h>
#include <egammaAnalysisUtils/VertexPositionReweightingTool.h>
#include <egammaAnalysisUtils/ElectronLikelihoodTool.h>
#include <egammaEvent/egammaPIDdefs.h>
#include <egammaAnalysisUtils/MultiLeptonMenu.h>

#include <TrigMuonEfficiency/TriggerNavigationVariables.h>
#include <TrigMuonEfficiency/ElectronTriggerMatching.h>
#include <TrigMuonEfficiency/MuonTriggerMatching.h>

/*-------------------------------------------------------------------------*/

typedef enum TLeptonClass
{
	CLASS_ELECTRON
	,
	CLASS_MUON

} TLeptonClass;

/*-------------------------------------------------------------------------*/

typedef enum TLeptonType
{
	TYPE_ELECTRON
	,
	TYPE_MUON_CB_PLUS_ST
	,
	TYPE_MUON_STANDALONE
	,
	TYPE_MUON_CALO

} TLeptonType;

/*-------------------------------------------------------------------------*/

class TLeptonAnalysis: public TNTuple
{
  protected:
	void fixeEnergy(void);

  public:
	Int_t nPV2;
	Int_t nPV3;

	UInt_t elTrigger;
	UInt_t muTrigger;
	UInt_t elmuTrigger;

	/*-----------------------------------------------------------------*/
	/* COUNTERS							   */
	/*-----------------------------------------------------------------*/

	UInt_t elNr0;
	UInt_t elNr1;
	UInt_t elNr2;
	UInt_t elNr3;
	UInt_t elNr4;
	UInt_t elNr5;
	UInt_t elNr6;
	UInt_t elNr7;
	UInt_t elNr8;
	UInt_t elNr9;
	UInt_t elNr10;
	UInt_t elNr11;

	UInt_t muNr0;
	UInt_t muNr1;
	UInt_t muNr2;
	UInt_t muNr3;
	UInt_t muNr4;
	UInt_t muNr5;
	UInt_t muNr6;
	UInt_t muNr7;
	UInt_t muNr8;
	UInt_t muNr9;
	UInt_t muNr10;
	UInt_t muNr11;
	UInt_t muNr12;
	UInt_t muNr13;
	UInt_t muNr14;

	/*-----------------------------------------------------------------*/
	/* TOOLS							   */
	/*-----------------------------------------------------------------*/
#if defined( __YEAR2012) && defined(__IS_MC)
	VertexPositionReweightingTool *m_VertexPositionReweighting;

	// d0 smearing
	TH2F *smearD0[3];
	TRandom3 smearD0_rand;
	TAxis *smearD0_x;
	TAxis *smearD0_y;

	// z0 smearing
	TH2F *smearZ0[3];
	TRandom3 smearZ0_rand;
	TAxis *smearZ0_x;
	TAxis *smearZ0_y;

#endif
	Root::TPileupReweighting *m_pileupReweighting;

	MuonSmear::SmearingClass *m_stacoSM;

	Analysis::AnalysisMuonConfigurableScaleFactors *m_stacoSCF;
	Analysis::AnalysisMuonConfigurableScaleFactors *m_stacoSASCF;
	Analysis::AnalysisMuonConfigurableScaleFactors *m_caloMuSCF;

	egRescaler::EnergyRescalerUpgrade m_energyRescaler;

	//egammaSFclass *m_egammaSF;
	Root::TElectronEfficiencyCorrectionTool *m_egSFclass_ID;
	Root::TElectronEfficiencyCorrectionTool *m_egSFclass_Reco;

	ElectronLikelihoodTool  *m_ElectronLikelihoodTool;
	MultiLeptonMenu m_MultiLeptonMenu;

	TriggerNavigationVariables *m_triggerNavigationVariables;
	ElectronTriggerMatching *m_elTriggerMatching;
	MuonTriggerMatching *m_muTriggerMatching;

	/*-----------------------------------------------------------------*/
#ifdef __YEAR2011
	Float_t lumiPeriod2011B;
	Float_t lumiPeriod2011D;
	Float_t lumiPeriod2011E;
	Float_t lumiPeriod2011F;
	Float_t lumiPeriod2011G;
	Float_t lumiPeriod2011H;
	Float_t lumiPeriod2011I;
	Float_t lumiPeriod2011J;
	Float_t lumiPeriod2011K;
	Float_t lumiPeriod2011L;
	Float_t lumiPeriod2011M;
#endif
#ifdef __YEAR2012
	Float_t lumiPeriod2012A;
	Float_t lumiPeriod2012B;
	Float_t lumiPeriod2012C;
	Float_t lumiPeriod2012D;
	Float_t lumiPeriod2012E;
	Float_t lumiPeriod2012F;
	Float_t lumiPeriod2012G;
	Float_t lumiPeriod2012H;
	Float_t lumiPeriod2012I;
	Float_t lumiPeriod2012J;
	Float_t lumiPeriod2012K;
	Float_t lumiPeriod2012L;
	Float_t lumiPeriod2012M;

#endif
	/*-----------------------------------------------------------------*/

	TLeptonAnalysis(TChain *chain): TNTuple(chain), elTrigger(0), muTrigger(0), elmuTrigger(0)
	{
		/*---------------------------------------------------------*/
		/* COUNTERS						   */
		/*---------------------------------------------------------*/

		elNr0 = 0;
		elNr1 = 0;
		elNr2 = 0;
		elNr3 = 0;
		elNr4 = 0;
		elNr5 = 0;
		elNr6 = 0;
		elNr7 = 0;
		elNr8 = 0;
		elNr9 = 0;
		elNr10 = 0;
		elNr11 = 0;

		muNr0 = 0;
		muNr1 = 0;
		muNr2 = 0;
		muNr3 = 0;
		muNr4 = 0;
		muNr5 = 0;
		muNr6 = 0;
		muNr7 = 0;
		muNr8 = 0;
		muNr9 = 0;
		muNr10 = 0;
		muNr11 = 0;
		muNr12 = 0;
		muNr13 = 0;

		/*---------------------------------------------------------*/
		/* VERTEX POSITION REWEIGHTING				   */
		/*---------------------------------------------------------*/
#if defined( __YEAR2012) && defined(__IS_MC)
		m_VertexPositionReweighting = new VertexPositionReweightingTool(VertexPositionReweightingTool::MC12a, "./tools/packages/egammaAnalysisUtils/share/zvtx_weights_2011_2012.root");
#endif

		/*---------------------------------------------------------*/
		/* IP SMEARING						   */
		/*---------------------------------------------------------*/
#if defined( __YEAR2012) && defined(__IS_MC)
		TFile *d0_smearing_file = new TFile("./tools/impact_parameter_smearing.root");
		std::cout << " d0 smearing confi file : ./tools//impact_parameter_smearing.root "<<std::endl;
		smearD0[0] = (TH2F*)d0_smearing_file->Get("smearD0_0");
		smearD0[1] = (TH2F*)d0_smearing_file->Get("smearD0_1");
		smearD0[2] = (TH2F*)d0_smearing_file->Get("smearD0_2");
		smearD0[0]->SetDirectory(0);
		smearD0[1]->SetDirectory(0);
		smearD0[2]->SetDirectory(0);
		smearD0_x = smearD0[0]->GetXaxis();
		smearD0_y = smearD0[0]->GetYaxis();
		d0_smearing_file->Close();

		TFile *z0_smearing_file = new TFile("./tools/impact_parameter_smearing.root");
		std::cout << " z0 smearing confi file : ./tools/impact_parameter_smearing.root "<<std::endl;
		smearZ0[0] = (TH2F*)z0_smearing_file->Get("smearZ0_0");
		smearZ0[1] = (TH2F*)z0_smearing_file->Get("smearZ0_1");
		smearZ0[2] = (TH2F*)z0_smearing_file->Get("smearZ0_2");
		smearZ0[0]->SetDirectory(0);
		smearZ0[1]->SetDirectory(0);
		smearZ0[2]->SetDirectory(0);
		smearZ0_x = smearZ0[0]->GetXaxis();
		smearZ0_y = smearZ0[0]->GetYaxis();
		z0_smearing_file->Close();    

#endif
		/*---------------------------------------------------------*/
		/* VERTEX POSITION REWEIGHTING				   */
		/*---------------------------------------------------------*/
#if defined( __YEAR2012) && defined(__IS_MC)
		m_VertexPositionReweighting = new VertexPositionReweightingTool(VertexPositionReweightingTool::MC12a, "./tools/packages/egammaAnalysisUtils/share/zvtx_weights_2011_2012.root");
#endif

		/*---------------------------------------------------------*/
		/* PILEUP REWEIGHTING					   */
		/*---------------------------------------------------------*/

		m_pileupReweighting = new Root::TPileupReweighting("PileupReweightingTool");
#ifdef __YEAR2011
		m_pileupReweighting->SetUnrepresentedDataAction(2);
		m_pileupReweighting->AddConfigFile("./tools/MC11c.prw.root");
		m_pileupReweighting->AddLumiCalcFile("./tools/ilumicalc_2011_AllYear_All_Good.root");
		m_pileupReweighting->SetDefaultChannel(109292);
		m_pileupReweighting->Initialize();

		lumiPeriod2011B = m_pileupReweighting->GetIntegratedLumi(177986, 178109);
		lumiPeriod2011D = m_pileupReweighting->GetIntegratedLumi(179710, 180481);
		lumiPeriod2011E = m_pileupReweighting->GetIntegratedLumi(180614, 180776);
		lumiPeriod2011F = m_pileupReweighting->GetIntegratedLumi(182013, 182519);
		lumiPeriod2011G = m_pileupReweighting->GetIntegratedLumi(182726, 183462);
		lumiPeriod2011H = m_pileupReweighting->GetIntegratedLumi(183544, 184169);
		lumiPeriod2011I = m_pileupReweighting->GetIntegratedLumi(185353, 186493);
		lumiPeriod2011J = m_pileupReweighting->GetIntegratedLumi(186516, 186755);
		lumiPeriod2011K = m_pileupReweighting->GetIntegratedLumi(186873, 187815);
		lumiPeriod2011L = m_pileupReweighting->GetIntegratedLumi(188902, 190343);
		lumiPeriod2011M = m_pileupReweighting->GetIntegratedLumi(190503, 191933);
#endif
#ifdef __YEAR2012
		m_pileupReweighting->SetUnrepresentedDataAction(2);
		m_pileupReweighting->AddConfigFile("./tools/MC12a.prw.root");
		m_pileupReweighting->AddLumiCalcFile("./tools/ilumicalc_2012_AllYear_All_Good.root");
		m_pileupReweighting->SetDefaultChannel(160156);
		m_pileupReweighting->Initialize();

		lumiPeriod2012A = m_pileupReweighting->GetIntegratedLumi(200804,201556);
		lumiPeriod2012B = m_pileupReweighting->GetIntegratedLumi(202660,205113);
		lumiPeriod2012C = m_pileupReweighting->GetIntegratedLumi(206248,207397);
		lumiPeriod2012D = m_pileupReweighting->GetIntegratedLumi(207447,209025);
		lumiPeriod2012E = m_pileupReweighting->GetIntegratedLumi(209074,210308);
		lumiPeriod2012F = 0.0; 
		lumiPeriod2012G = m_pileupReweighting->GetIntegratedLumi(211522,212272);
		lumiPeriod2012H = m_pileupReweighting->GetIntegratedLumi(212619,213359); 
		lumiPeriod2012I = m_pileupReweighting->GetIntegratedLumi(213431,213819); 
		lumiPeriod2012J = m_pileupReweighting->GetIntegratedLumi(213900,215091); 
		lumiPeriod2012K = 0.0;
		lumiPeriod2012L = m_pileupReweighting->GetIntegratedLumi(215414,215643); 
		lumiPeriod2012M = m_pileupReweighting->GetIntegratedLumi(216399,216432);// 2012 lumiPeriod A-M

#endif
		/*---------------------------------------------------------*/
		/* MUON SMEARING					   */
		/*---------------------------------------------------------*/
#ifdef __YEAR2011
		m_stacoSM = new MuonSmear::SmearingClass("Data11", "staco", "q_pT", "Rel17", "./tools/packages/MuonMomentumCorrections/share/");
#endif
#ifdef __YEAR2012
		m_stacoSM = new MuonSmear::SmearingClass("Data12", "staco", "q_pT", "Rel17.2Repro", "./tools/packages/MuonMomentumCorrections/share/");
		m_stacoSM->UseScale(1);
		m_stacoSM->UseImprovedCombine();

#endif
		/*---------------------------------------------------------*/
		/* MUON SCALE FACTORS					   */
		/*---------------------------------------------------------*/
#ifdef __YEAR2011
		m_stacoSCF = new Analysis::AnalysisMuonConfigurableScaleFactors("./tools/packages/MuonEfficiencyCorrections/share/", "STACO_CB_plus_ST_2011_SF.txt", "MeV", Analysis::AnalysisMuonConfigurableScaleFactors::AverageOverPeriods);
		m_stacoSCF->Initialise();

		m_stacoSASCF = new Analysis::AnalysisMuonConfigurableScaleFactors("./tools/packages/MuonEfficiencyCorrections/share/", "STACOHighEta.txt", "MeV", Analysis::AnalysisMuonConfigurableScaleFactors::Default);
		m_stacoSASCF->Initialise();

		m_caloMuSCF = new Analysis::AnalysisMuonConfigurableScaleFactors("./tools/packages/MuonEfficiencyCorrections/share/", "CaloTag_2011_SF.txt", "MeV", Analysis::AnalysisMuonConfigurableScaleFactors::AverageOverPeriods);
		m_caloMuSCF->Initialise();
#endif
#ifdef __YEAR2012
		m_stacoSCF = new Analysis::AnalysisMuonConfigurableScaleFactors("./tools/packages/MuonEfficiencyCorrections/share/", "STACO_CB_plus_ST_2012_SF.txt", "MeV", Analysis::AnalysisMuonConfigurableScaleFactors::AverageOverRuns);
		m_stacoSCF->Initialise();

		m_stacoSASCF = new Analysis::AnalysisMuonConfigurableScaleFactors("./tools/packages/MuonEfficiencyCorrections/share/", "STACO_CB_plus_ST_2012_SFms.txt", "MeV", Analysis::AnalysisMuonConfigurableScaleFactors::AverageOverRuns);
		m_stacoSASCF->Initialise();

		m_caloMuSCF = new Analysis::AnalysisMuonConfigurableScaleFactors("./tools/packages/MuonEfficiencyCorrections/share/", "CaloTag_2012_SF.txt", "MeV", Analysis::AnalysisMuonConfigurableScaleFactors::AverageOverRuns);
		m_caloMuSCF->Initialise();
#endif

		/*---------------------------------------------------------*/
		/* ELECTRON LIKELIHOOD ID				   */
		/*---------------------------------------------------------*/
#ifdef __YEAR2012
		m_ElectronLikelihoodTool = new ElectronLikelihoodTool("./tools/packages/egammaAnalysisUtils/share/ElectronLikelihoodPdfs.root");
#endif
	
		/*---------------------------------------------------------*/
		/* ELECTRON ENERGY RESCALER				   */
		/*---------------------------------------------------------*/
#ifdef __YEAR2011
		m_energyRescaler.Init("./tools/packages/egammaAnalysisUtils/share/EnergyRescalerData.root","2011","es2011a");
#endif
#ifdef __YEAR2012
		m_energyRescaler.Init("./tools/packages/egammaAnalysisUtils/share/EnergyRescalerData.root","2012","es2012");
#endif
		/*---------------------------------------------------------*/
		/* ELECTRON SCALE FACTORS				   */
		/*---------------------------------------------------------*/

		//m_egammaSF = new egammaSFclass();
		m_egSFclass_ID = new Root::TElectronEfficiencyCorrectionTool;
		m_egSFclass_Reco = new Root::TElectronEfficiencyCorrectionTool;

#ifdef __YEAR2011
		m_egSFclass_ID->addFileName("./tools/packages/ElectronEfficiencyCorrection/data/efficiencySF.offline.Loose.2011.7TeV.rel17p0.v01.root");
		m_egSFclass_Reco->addFileName("./tools/packages/ElectronEfficiencyCorrection/data/efficiencySF.offline.RecoTrk.2011.7TeV.rel17p0.v01.root");
#endif

#ifdef __YEAR2012
		m_egSFclass_ID->addFileName("./tools/packages/ElectronEfficiencyCorrection/data/efficiencySF.offline.Multilepton.2012.8TeV.rel17p2.v02.root");
		m_egSFclass_Reco->addFileName("./tools/packages/ElectronEfficiencyCorrection/data/efficiencySF.offline.RecoTrk.2012.8TeV.rel17p2.v02.root");
#endif
		m_egSFclass_ID->initialize();
		m_egSFclass_Reco->initialize();

		/*---------------------------------------------------------*/
		/* TRIGGER SCALE FACTORS				   */
		/*---------------------------------------------------------*/

		/* TODO */

		/*---------------------------------------------------------*/
		/* TRIGGER MATCHING					   */
		/*---------------------------------------------------------*/

		m_triggerNavigationVariables = new TriggerNavigationVariables();

		m_elTriggerMatching = new ElectronTriggerMatching(m_triggerNavigationVariables);
		m_muTriggerMatching = new MuonTriggerMatching(m_triggerNavigationVariables);

		/*---------------------------------------------------------*/
	}

	/*-----------------------------------------------------------------*/

	~TLeptonAnalysis(void)
	{
#if defined( __YEAR2012) && defined(__IS_MC)
		delete m_VertexPositionReweighting;
#endif
		delete m_pileupReweighting;

		delete m_stacoSM;

		delete m_stacoSCF;
		delete m_stacoSASCF;
		delete m_caloMuSCF;

		//delete m_egammaSF;
		delete m_egSFclass_ID;
		delete m_egSFclass_Reco;

		delete m_triggerNavigationVariables;
		delete m_elTriggerMatching;
		delete m_muTriggerMatching;
	}

	/*-----------------------------------------------------------------*/
	/* TRIGGER							   */
	/*-----------------------------------------------------------------*/

	void triggerInit(void)
	{
		m_triggerNavigationVariables->set_trig_DB_SMK(trig_DB_SMK);
		m_triggerNavigationVariables->set_trig_Nav_n(trig_Nav_n);
		m_triggerNavigationVariables->set_trig_Nav_chain_ChainId(trig_Nav_chain_ChainId);
		m_triggerNavigationVariables->set_trig_Nav_chain_RoIType(trig_Nav_chain_RoIType);
		m_triggerNavigationVariables->set_trig_Nav_chain_RoIIndex(trig_Nav_chain_RoIIndex);

		/* electron */
		m_triggerNavigationVariables->set_trig_RoI_EF_e_egammaContainer_egamma_Electrons(trig_RoI_EF_e_egammaContainer_egamma_Electrons);
		m_triggerNavigationVariables->set_trig_RoI_EF_e_egammaContainer_egamma_ElectronsStatus(trig_RoI_EF_e_egammaContainer_egamma_ElectronsStatus);
		m_triggerNavigationVariables->set_trig_EF_el_n(trig_EF_el_n);
		m_triggerNavigationVariables->set_trig_EF_el_eta(trig_EF_el_eta);
		m_triggerNavigationVariables->set_trig_EF_el_phi(trig_EF_el_phi);

		/* muon */
		m_triggerNavigationVariables->set_trig_RoI_EF_mu_Muon_ROI(trig_RoI_EF_mu_Muon_ROI);

		m_triggerNavigationVariables->set_trig_EF_trigmuonef_track_MuonType(trig_EF_trigmuonef_track_MuonType); 
#ifdef __YEAR2011
		m_triggerNavigationVariables->set_trig_RoI_EF_mu_TrigMuonEFInfoContainer(trig_RoI_EF_mu_TrigMuonEFInfoContainer_eMuonEFInfo);
		m_triggerNavigationVariables->set_trig_RoI_EF_mu_TrigMuonEFInfoContainerStatus(trig_RoI_EF_mu_TrigMuonEFInfoContainer_eMuonEFInfoStatus);
		//m_triggerNavigationVariables->set_trig_RoI_EF_mu_TrigMuonEFInfoContainerStatus(trig_RoI_EF_mu_TrigMuonEFInfoContainer_MuonEFInfoStatus); //for EF_e10_medium_mu6"
		//m_triggerNavigationVariables->set_trig_RoI_EF_mu_TrigMuonEFInfoContainer(trig_RoI_EF_mu_TrigMuonEFInfoContainer_MuonEFInfo); //for EF_e10_medium_mu6"
#endif
#ifdef __YEAR2012
		m_triggerNavigationVariables->set_trig_RoI_EF_mu_TrigMuonEFInfoContainer(trig_RoI_EF_mu_TrigMuonEFInfoContainer);
		m_triggerNavigationVariables->set_trig_RoI_EF_mu_TrigMuonEFInfoContainerStatus(trig_RoI_EF_mu_TrigMuonEFInfoContainerStatus);
#endif

		m_triggerNavigationVariables->set_trig_RoI_L2_mu_CombinedMuonFeature(trig_RoI_L2_mu_CombinedMuonFeature);
		m_triggerNavigationVariables->set_trig_RoI_L2_mu_CombinedMuonFeatureStatus(trig_RoI_L2_mu_CombinedMuonFeatureStatus);
		m_triggerNavigationVariables->set_trig_RoI_L2_mu_MuonFeature(trig_RoI_L2_mu_MuonFeature);
		m_triggerNavigationVariables->set_trig_RoI_L2_mu_Muon_ROI(trig_RoI_L2_mu_Muon_ROI);
		m_triggerNavigationVariables->set_trig_EF_trigmuonef_track_CB_pt(trig_EF_trigmuonef_track_CB_pt);
		m_triggerNavigationVariables->set_trig_EF_trigmuonef_track_CB_eta(trig_EF_trigmuonef_track_CB_eta);
		m_triggerNavigationVariables->set_trig_EF_trigmuonef_track_CB_phi(trig_EF_trigmuonef_track_CB_phi);
		m_triggerNavigationVariables->set_trig_EF_trigmuonef_track_SA_pt(trig_EF_trigmuonef_track_SA_pt);
		m_triggerNavigationVariables->set_trig_EF_trigmuonef_track_SA_eta(trig_EF_trigmuonef_track_SA_eta);
		m_triggerNavigationVariables->set_trig_EF_trigmuonef_track_SA_phi(trig_EF_trigmuonef_track_SA_phi);
		m_triggerNavigationVariables->set_trig_EF_trigmugirl_track_CB_pt(trig_EF_trigmugirl_track_CB_pt);
		m_triggerNavigationVariables->set_trig_EF_trigmugirl_track_CB_eta(trig_EF_trigmugirl_track_CB_eta);
		m_triggerNavigationVariables->set_trig_EF_trigmugirl_track_CB_phi(trig_EF_trigmugirl_track_CB_phi);
		m_triggerNavigationVariables->set_trig_L2_combmuonfeature_eta(trig_L2_combmuonfeature_eta);
		m_triggerNavigationVariables->set_trig_L2_combmuonfeature_phi(trig_L2_combmuonfeature_phi);
		m_triggerNavigationVariables->set_trig_L2_muonfeature_eta(trig_L2_muonfeature_eta);
		m_triggerNavigationVariables->set_trig_L2_muonfeature_phi(trig_L2_muonfeature_phi);
		m_triggerNavigationVariables->set_trig_L1_mu_eta(trig_L1_mu_eta);
		m_triggerNavigationVariables->set_trig_L1_mu_phi(trig_L1_mu_phi);
		m_triggerNavigationVariables->set_trig_L1_mu_thrName(trig_L1_mu_thrName);
#ifdef __YEAR2012
		m_triggerNavigationVariables->set_trig_RoI_EF_mu_TrigMuonEFIsolationContainer(trig_RoI_EF_mu_TrigMuonEFIsolationContainer); // for 2012 isolated trigger
		m_triggerNavigationVariables->set_trig_RoI_EF_mu_TrigMuonEFIsolationContainerStatus(trig_RoI_EF_mu_TrigMuonEFIsolationContainerStatus); // for 2012 isolated trigger
#endif
		if(m_triggerNavigationVariables->isValid() == false)
		{
			std::cerr << "VARIABLES NOT CORRECTLY SET\n";

			exit(1);
		}
	}

	/*-----------------------------------------------------------------*/
	/* DEFINITIONS							   */
	/*-----------------------------------------------------------------*/

	Float_t eventGetWeight1(void);
	Float_t eventGetWeight2(void);
	Float_t eventGetWeight3(
		Int_t index,
		TLeptonType type
	);

	Float_t electronGetEtaDirection(Int_t index);
	Float_t electronGetPhiDirection(Int_t index);
	Float_t electronGetEt(Int_t index);
	Float_t electronGetRawEt(Int_t index);

	UInt_t el_isEMOk_at(Int_t index);
	Float_t el_Etcone20_at(Int_t index);
	Float_t el_Etcone30_at(Int_t index);

	/*-----------------------------------------------------------------*/
	/* SELECTION							   */
	/*-----------------------------------------------------------------*/

	double smearObject(
		Int_t index,
		TLeptonType type
	);

	void Z0smearObject(Int_t index, TLeptonType type);
	void D0smearObject(Int_t index, TLeptonType type);

	Bool_t checkObject(
		Int_t index,
		TLeptonType type,
		Float_t __el_et,
		Float_t __mu_pt,
		Float_t __mu_calo_pt
	);

	Bool_t checkOverlapping(
		Int_t index,
		TLeptonType type,
		Float_t __el_et,
		Float_t __mu_pt,
		Float_t __mu_calo_pt,
		Int_t muonIndexNr, Int_t muonIndexArray[], TLeptonType muonTypeArray[]
	);

	/*-----------------------------------------------------------------*/
	/* TRUTH							   */
	/*-----------------------------------------------------------------*/

	Bool_t truthMatch(
		Int_t index,
		TLeptonType type
	);

	/*-----------------------------------------------------------------*/
	/* TRIGGER							   */
	/*-----------------------------------------------------------------*/

	UInt_t getElTrigger(void);
	UInt_t getMuTrigger(void);
	UInt_t getElMuTrigger(void);

	UInt_t triggerMatch(
		Int_t index,
		TLeptonType type
	);

	Int_t triggerTrace(UInt_t result[]);

	/*-----------------------------------------------------------------*/
};

/*-------------------------------------------------------------------------*/
/* UTILS								   */
/*-------------------------------------------------------------------------*/

Char_t getlumiPeriod(Int_t RunNumber);

Float_t __dR2(
	Float_t eta1, Float_t eta2,
	Float_t phi1, Float_t phi2
);

TLeptonClass getLeptonClass(TLeptonType type);

Bool_t buildPair(
	Int_t pair[2],
	Float_t charge1,
	Float_t charge2
);

Bool_t buildPairs(
	Int_t pair1[2],
	Int_t pair2[2],
	Int_t pair3[2],
	Int_t pair4[2],
	TLeptonType type1,
	TLeptonType type2,
	TLeptonType type3,
	TLeptonType type4,
	Float_t charge1,
	Float_t charge2,
	Float_t charge3,
	Float_t charge4
);

void reIndex(
	Int_t L[4],
	Float_t M[4],
	Int_t (* func)(const void *, const void *)
);

Double_t binomialError(
	Double_t x,
	Double_t y
);

/*-------------------------------------------------------------------------*/

#endif /* __CORE_H */

/*-------------------------------------------------------------------------*/


void D3PDSkimmer_MC2012(void)
{
	TChain *chain = new TChain("physics");

	chain->Add("/afs/cern.ch/atlas/groups/HSG2/NTUP_HSG2.00814271._000001.root");

	/*-----------------------------------------------------------------*/

	chain->SetBranchStatus("*", 0);

	/*-----------------------------------------------------------------*/

	chain->SetBranchStatus("RunNumber", 1);
	chain->SetBranchStatus("EventNumber", 1);
	chain->SetBranchStatus("lbn", 1);
	chain->SetBranchStatus("larError", 1);

	/*-----------------------------------------------------------------*/

	chain->SetBranchStatus("actualIntPerXing", 1);
	chain->SetBranchStatus("averageIntPerXing", 1);

	/*-----------------------------------------------------------------*/

	chain->SetBranchStatus("vxp_n", 1);
	chain->SetBranchStatus("vxp_nTracks", 1);

	/*-----------------------------------------------------------------*/

	chain->SetBranchStatus("mc_n", 1);
	chain->SetBranchStatus("mc_pdgId", 1);
	chain->SetBranchStatus("mc_children", 1);
	chain->SetBranchStatus("mc_child_index", 1);
	chain->SetBranchStatus("mc_channel_number", 1);

	/*-----------------------------------------------------------------*/

	chain->SetBranchStatus("mcevt_weight", 1);

	/*-----------------------------------------------------------------*/
	/* ELECTRONS GSF						   */
	/*-----------------------------------------------------------------*/

	chain->SetBranchStatus("el_author", 1);
	chain->SetBranchStatus("el_charge", 1);
	chain->SetBranchStatus("el_etas2", 1);
	chain->SetBranchStatus("el_cl_E", 1);
	chain->SetBranchStatus("el_cl_eta", 1);
	chain->SetBranchStatus("el_cl_phi", 1);
	chain->SetBranchStatus("el_cl_pt", 1);
	chain->SetBranchStatus("el_EF_index", 1);
	chain->SetBranchStatus("el_etap", 1);
	chain->SetBranchStatus("el_etas2", 1);
	chain->SetBranchStatus("el_phis2", 1);
	chain->SetBranchStatus("el_Etcone20", 1);
	chain->SetBranchStatus("el_Etcone30", 1);
	chain->SetBranchStatus("el_ED_median", 1);
	chain->SetBranchStatus("el_loosePP", 1);
	chain->SetBranchStatus("el_medium", 1);
	chain->SetBranchStatus("el_n", 1);
	chain->SetBranchStatus("el_nPixHits", 1);
	chain->SetBranchStatus("el_nSCTHits", 1);
	chain->SetBranchStatus("el_OQ", 1);
	chain->SetBranchStatus("el_type", 1);
	chain->SetBranchStatus("el_typebkg", 1);
	chain->SetBranchStatus("el_origin", 1);
	chain->SetBranchStatus("el_originbkg", 1);
	chain->SetBranchStatus("el_ptcone20", 1);
	chain->SetBranchStatus("el_ptcone30", 1);
	chain->SetBranchStatus("el_tight", 1);
	chain->SetBranchStatus("el_trackd0", 1);
	chain->SetBranchStatus("el_trackd0pvunbiased", 1);
	chain->SetBranchStatus("el_tracksigd0pvunbiased", 1);
	chain->SetBranchStatus("el_tracketa", 1);
	chain->SetBranchStatus("el_trackphi", 1);
	chain->SetBranchStatus("el_trackpt", 1);
	chain->SetBranchStatus("el_trackqoverp", 1);
	chain->SetBranchStatus("el_tracktheta", 1);
	chain->SetBranchStatus("el_trackz0", 1);
	chain->SetBranchStatus("el_trackz0pvunbiased", 1);
	chain->SetBranchStatus("el_refittedTrack_LMqoverp", 1);
	chain->SetBranchStatus("el_refittedTrack_author", 1);
	chain->SetBranchStatus("el_Ethad", 1);
	chain->SetBranchStatus("el_Ethad1", 1);
	chain->SetBranchStatus("el_reta", 1);
	chain->SetBranchStatus("el_rphi", 1);
	chain->SetBranchStatus("el_weta2", 1);
	chain->SetBranchStatus("el_f1", 1);
	chain->SetBranchStatus("el_f3", 1);
	chain->SetBranchStatus("el_wstot", 1);
	chain->SetBranchStatus("el_emaxs1", 1);
	chain->SetBranchStatus("el_Emax2", 1);
	chain->SetBranchStatus("el_deltaeta1", 1);
	chain->SetBranchStatus("el_deltaphiRescaled", 1);
	chain->SetBranchStatus("el_nBLHits", 1);
	chain->SetBranchStatus("el_nBLayerOutliers", 1);
	chain->SetBranchStatus("el_nSiHits", 1);
	chain->SetBranchStatus("el_nPixelDeadSensors", 1);
	chain->SetBranchStatus("el_nPixelOutliers", 1);
	chain->SetBranchStatus("el_nSCTDeadSensors", 1);
	chain->SetBranchStatus("el_nSCTOutliers", 1);
	chain->SetBranchStatus("el_nTRTHits", 1);
	chain->SetBranchStatus("el_nTRTOutliers", 1);
	chain->SetBranchStatus("el_nTRTHighTHits", 1);
	chain->SetBranchStatus("el_nTRTHighTOutliers", 1);
	chain->SetBranchStatus("el_expectBLayerHit", 1);
	chain->SetBranchStatus("el_truth_mothertype", 1);
	chain->SetBranchStatus("el_truth_type", 1);

	/*-----------------------------------------------------------------*/
	/* MUONS STACO							   */
	/*-----------------------------------------------------------------*/

	chain->SetBranchStatus("mu_staco_author", 1);
	chain->SetBranchStatus("mu_staco_charge", 1);
	chain->SetBranchStatus("mu_staco_E", 1);
	chain->SetBranchStatus("mu_staco_EFCB_index", 1);
	chain->SetBranchStatus("mu_staco_eta", 1);
	chain->SetBranchStatus("mu_staco_etcone20", 1);
	chain->SetBranchStatus("mu_staco_etcone30", 1);
	chain->SetBranchStatus("mu_staco_expectBLayerHit", 1);
	chain->SetBranchStatus("mu_staco_id_d0", 1);
	chain->SetBranchStatus("mu_staco_id_phi", 1);
	chain->SetBranchStatus("mu_staco_id_qoverp", 1);
	chain->SetBranchStatus("mu_staco_id_qoverp_exPV", 1);
	chain->SetBranchStatus("mu_staco_id_theta", 1);
	chain->SetBranchStatus("mu_staco_id_theta_exPV", 1);
	chain->SetBranchStatus("mu_staco_id_z0", 1);
	chain->SetBranchStatus("mu_staco_isStandAloneMuon", 1);
	chain->SetBranchStatus("mu_staco_isCombinedMuon", 1);
	chain->SetBranchStatus("mu_staco_isSegmentTaggedMuon", 1);
	chain->SetBranchStatus("mu_staco_me_qoverp_exPV", 1);
	chain->SetBranchStatus("mu_staco_me_theta_exPV", 1);
	chain->SetBranchStatus("mu_staco_n", 1);
	chain->SetBranchStatus("mu_staco_nBLHits", 1);
	chain->SetBranchStatus("mu_staco_nPixelDeadSensors", 1);
	chain->SetBranchStatus("mu_staco_nPixHits", 1);
	chain->SetBranchStatus("mu_staco_nPixHoles", 1);
	chain->SetBranchStatus("mu_staco_nSCTDeadSensors", 1);
	chain->SetBranchStatus("mu_staco_nSCTHits", 1);
	chain->SetBranchStatus("mu_staco_nSCTHoles", 1);
	chain->SetBranchStatus("mu_staco_nTRTHits", 1);
	chain->SetBranchStatus("mu_staco_nTRTOutliers", 1);
	chain->SetBranchStatus("mu_staco_nCSCEtaHits", 1);
	chain->SetBranchStatus("mu_staco_nCSCPhiHits", 1);
	chain->SetBranchStatus("mu_staco_nMDTEMHits", 1);
	chain->SetBranchStatus("mu_staco_nMDTEOHits", 1);
	chain->SetBranchStatus("mu_staco_phi", 1);
	chain->SetBranchStatus("mu_staco_pt", 1);
	chain->SetBranchStatus("mu_staco_ptcone20", 1);
	chain->SetBranchStatus("mu_staco_ptcone30", 1);
	chain->SetBranchStatus("mu_staco_tight", 1);
	chain->SetBranchStatus("mu_staco_d0_exPV", 1);
	chain->SetBranchStatus("mu_staco_z0_exPV", 1);
	chain->SetBranchStatus("mu_staco_trackIPEstimate_d0_unbiasedpvunbiased", 1);
	chain->SetBranchStatus("mu_staco_trackIPEstimate_sigd0_unbiasedpvunbiased", 1);
	chain->SetBranchStatus("mu_staco_truth_mothertype", 1);
	chain->SetBranchStatus("mu_staco_truth_type", 1);

	/*-----------------------------------------------------------------*/
	/* MUONS muid							   */
	/*-----------------------------------------------------------------*/

	chain->SetBranchStatus("mu_muid_author", 1);
	chain->SetBranchStatus("mu_muid_charge", 1);
	chain->SetBranchStatus("mu_muid_E", 1);
	chain->SetBranchStatus("mu_muid_EFCB_index", 1);
	chain->SetBranchStatus("mu_muid_eta", 1);
	chain->SetBranchStatus("mu_muid_etcone20", 1);
	chain->SetBranchStatus("mu_muid_etcone30", 1);
	chain->SetBranchStatus("mu_muid_expectBLayerHit", 1);
	chain->SetBranchStatus("mu_muid_id_d0", 1);
	chain->SetBranchStatus("mu_muid_id_phi", 1);
	chain->SetBranchStatus("mu_muid_id_qoverp", 1);
	chain->SetBranchStatus("mu_muid_id_qoverp_exPV", 1);
	chain->SetBranchStatus("mu_muid_id_theta", 1);
	chain->SetBranchStatus("mu_muid_id_theta_exPV", 1);
	chain->SetBranchStatus("mu_muid_id_z0", 1);
	chain->SetBranchStatus("mu_muid_isStandAloneMuon", 1);
	chain->SetBranchStatus("mu_muid_isCombinedMuon", 1);
	chain->SetBranchStatus("mu_muid_isSegmentTaggedMuon", 1);
	chain->SetBranchStatus("mu_muid_me_qoverp_exPV", 1);
	chain->SetBranchStatus("mu_muid_me_theta_exPV", 1);
	chain->SetBranchStatus("mu_muid_n", 1);
	chain->SetBranchStatus("mu_muid_nBLHits", 1);
	chain->SetBranchStatus("mu_muid_nPixelDeadSensors", 1);
	chain->SetBranchStatus("mu_muid_nPixHits", 1);
	chain->SetBranchStatus("mu_muid_nPixHoles", 1);
	chain->SetBranchStatus("mu_muid_nSCTDeadSensors", 1);
	chain->SetBranchStatus("mu_muid_nSCTHits", 1);
	chain->SetBranchStatus("mu_muid_nSCTHoles", 1);
	chain->SetBranchStatus("mu_muid_nTRTHits", 1);
	chain->SetBranchStatus("mu_muid_nTRTOutliers", 1);
	chain->SetBranchStatus("mu_muid_nCSCEtaHits", 1);
	chain->SetBranchStatus("mu_muid_nCSCPhiHits", 1);
	chain->SetBranchStatus("mu_muid_nMDTEMHits", 1);
	chain->SetBranchStatus("mu_muid_nMDTEOHits", 1);
	chain->SetBranchStatus("mu_muid_phi", 1);
	chain->SetBranchStatus("mu_muid_pt", 1);
	chain->SetBranchStatus("mu_muid_ptcone20", 1);
	chain->SetBranchStatus("mu_muid_ptcone30", 1);
	chain->SetBranchStatus("mu_muid_tight", 1);
	chain->SetBranchStatus("mu_muid_d0_exPV", 1);
	chain->SetBranchStatus("mu_muid_z0_exPV", 1);
	chain->SetBranchStatus("mu_muid_trackIPEstimate_d0_unbiasedpvunbiased", 1);
	chain->SetBranchStatus("mu_muid_trackIPEstimate_sigd0_unbiasedpvunbiased", 1);
	chain->SetBranchStatus("mu_muid_truth_mothertype", 1);
	chain->SetBranchStatus("mu_muid_truth_type", 1);

	/*-----------------------------------------------------------------*/
	/* MUONS calo							   */
	/*-----------------------------------------------------------------*/

	chain->SetBranchStatus("mu_calo_author", 1);
	chain->SetBranchStatus("mu_calo_caloMuonIdTag", 1);
	chain->SetBranchStatus("mu_calo_caloLRLikelihood", 1);
	chain->SetBranchStatus("mu_calo_charge", 1);
	chain->SetBranchStatus("mu_calo_E", 1);
	chain->SetBranchStatus("mu_calo_eta", 1);
	chain->SetBranchStatus("mu_calo_etcone20", 1);
	chain->SetBranchStatus("mu_calo_etcone30", 1);
	chain->SetBranchStatus("mu_calo_expectBLayerHit", 1);
	chain->SetBranchStatus("mu_calo_id_d0", 1);
	chain->SetBranchStatus("mu_calo_id_phi", 1);
	chain->SetBranchStatus("mu_calo_id_qoverp", 1);
	chain->SetBranchStatus("mu_calo_id_qoverp_exPV", 1);
	chain->SetBranchStatus("mu_calo_id_theta", 1);
	chain->SetBranchStatus("mu_calo_id_theta_exPV", 1);
	chain->SetBranchStatus("mu_calo_id_z0", 1);
	chain->SetBranchStatus("mu_calo_isStandAloneMuon", 1);
	chain->SetBranchStatus("mu_calo_isCombinedMuon", 1);
	chain->SetBranchStatus("mu_calo_isSegmentTaggedMuon", 1);
	chain->SetBranchStatus("mu_calo_me_qoverp_exPV", 1);
	chain->SetBranchStatus("mu_calo_me_theta_exPV", 1);
	chain->SetBranchStatus("mu_calo_n", 1);
	chain->SetBranchStatus("mu_calo_nBLHits", 1);
	chain->SetBranchStatus("mu_calo_nPixelDeadSensors", 1);
	chain->SetBranchStatus("mu_calo_nPixHits", 1);
	chain->SetBranchStatus("mu_calo_nPixHoles", 1);
	chain->SetBranchStatus("mu_calo_nSCTDeadSensors", 1);
	chain->SetBranchStatus("mu_calo_nSCTHits", 1);
	chain->SetBranchStatus("mu_calo_nSCTHoles", 1);
	chain->SetBranchStatus("mu_calo_nTRTHits", 1);
	chain->SetBranchStatus("mu_calo_nTRTOutliers", 1);
	chain->SetBranchStatus("mu_calo_nCSCEtaHits", 1);
	chain->SetBranchStatus("mu_calo_nCSCPhiHits", 1);
	chain->SetBranchStatus("mu_calo_nMDTEMHits", 1);
	chain->SetBranchStatus("mu_calo_nMDTEOHits", 1);
	chain->SetBranchStatus("mu_calo_phi", 1);
	chain->SetBranchStatus("mu_calo_pt", 1);
	chain->SetBranchStatus("mu_calo_ptcone20", 1);
	chain->SetBranchStatus("mu_calo_ptcone30", 1);
	chain->SetBranchStatus("mu_calo_tight", 1);
	chain->SetBranchStatus("mu_calo_d0_exPV", 1);
	chain->SetBranchStatus("mu_calo_z0_exPV", 1);
	chain->SetBranchStatus("mu_calo_trackIPEstimate_d0_unbiasedpvunbiased", 1);
	chain->SetBranchStatus("mu_calo_trackIPEstimate_sigd0_unbiasedpvunbiased", 1);
	chain->SetBranchStatus("mu_calo_truth_mothertype", 1);
	chain->SetBranchStatus("mu_calo_truth_type", 1);

	/*-----------------------------------------------------------------*/
	/* TRIGGER							   */
	/*-----------------------------------------------------------------*/

	chain->SetBranchStatus("EF_2e12_medium", 1);
	chain->SetBranchStatus("EF_2e12T_medium", 1);
	chain->SetBranchStatus("EF_2e12Tvh_medium", 1);
	chain->SetBranchStatus("EF_2e15_medium", 1);
	chain->SetBranchStatus("EF_2mu10_loose", 1);
	chain->SetBranchStatus("EF_e10_medium_mu10", 1);
	chain->SetBranchStatus("EF_e10_medium_mu6", 1);
	chain->SetBranchStatus("EF_e20_medium", 1);
	chain->SetBranchStatus("EF_e22_medium", 1);
	chain->SetBranchStatus("EF_e22_medium1", 1);
	chain->SetBranchStatus("EF_e22vh_medium1", 1);
	chain->SetBranchStatus("EF_mu10", 1);
	chain->SetBranchStatus("EF_mu15_mu10_EFFS", 1);
	chain->SetBranchStatus("EF_mu15_mu10_EFFS_medium", 1);
	chain->SetBranchStatus("EF_mu18", 1);
	chain->SetBranchStatus("EF_mu18_MG", 1);
	chain->SetBranchStatus("EF_mu18_MG_medium", 1);
	chain->SetBranchStatus("EF_mu20", 1);
	chain->SetBranchStatus("EF_mu20_MG", 1);
	chain->SetBranchStatus("EF_mu20_MG_medium", 1);
	chain->SetBranchStatus("EF_mu22", 1);
	chain->SetBranchStatus("EF_mu22_MG", 1);
	chain->SetBranchStatus("EF_mu22_MG_medium", 1);

	chain->SetBranchStatus("EF_e24vhi_medium1", 1);
	chain->SetBranchStatus("EF_e60_medium1", 1);
	chain->SetBranchStatus("EF_2e12Tvh_loose1", 1);
	chain->SetBranchStatus("EF_mu24i_tight", 1);
	chain->SetBranchStatus("EF_mu36_tight", 1);
	chain->SetBranchStatus("EF_2mu13", 1);
	chain->SetBranchStatus("EF_mu18_tight_mu8_EFFS", 1);

	/*-----------------------------------------------------------------*/

	chain->SetBranchStatus("trig_DB_SMK", 1);
	chain->SetBranchStatus("trig_Nav_n", 1);
	chain->SetBranchStatus("trig_Nav_chain_ChainId", 1);
	chain->SetBranchStatus("trig_Nav_chain_RoIType", 1);
	chain->SetBranchStatus("trig_Nav_chain_RoIIndex", 1);

	chain->SetBranchStatus("trig_RoI_EF_e_egammaContainer_egamma_Electrons", 1);
	chain->SetBranchStatus("trig_RoI_EF_e_egammaContainer_egamma_ElectronsStatus", 1);
	chain->SetBranchStatus("trig_EF_el_n", 1);
	chain->SetBranchStatus("trig_EF_el_eta", 1);
	chain->SetBranchStatus("trig_EF_el_phi", 1);

	chain->SetBranchStatus("trig_RoI_EF_mu_Muon_ROI", 1);
	chain->SetBranchStatus("trig_RoI_EF_mu_TrigMuonEFInfoContainer", 1);
	chain->SetBranchStatus("trig_RoI_EF_mu_TrigMuonEFInfoContainer_eMuonEFInfo", 1);
	chain->SetBranchStatus("trig_RoI_EF_mu_TrigMuonEFInfoContainerStatus", 1);
	chain->SetBranchStatus("trig_RoI_EF_mu_TrigMuonEFInfoContainer_eMuonEFInfoStatus", 1);
	chain->SetBranchStatus("trig_RoI_L2_mu_CombinedMuonFeature", 1);
	chain->SetBranchStatus("trig_RoI_L2_mu_CombinedMuonFeatureStatus", 1);
	chain->SetBranchStatus("trig_RoI_L2_mu_MuonFeature", 1);
	chain->SetBranchStatus("trig_RoI_L2_mu_Muon_ROI", 1);
	chain->SetBranchStatus("trig_EF_trigmuonef_track_CB_pt", 1);
	chain->SetBranchStatus("trig_EF_trigmuonef_track_CB_eta", 1);
	chain->SetBranchStatus("trig_EF_trigmuonef_track_CB_phi", 1);
	chain->SetBranchStatus("trig_EF_trigmuonef_track_SA_pt", 1);
	chain->SetBranchStatus("trig_EF_trigmuonef_track_SA_eta", 1);
	chain->SetBranchStatus("trig_EF_trigmuonef_track_SA_phi", 1);
	chain->SetBranchStatus("trig_EF_trigmugirl_track_CB_pt", 1);
	chain->SetBranchStatus("trig_EF_trigmugirl_track_CB_eta", 1);
	chain->SetBranchStatus("trig_EF_trigmugirl_track_CB_phi", 1);
	chain->SetBranchStatus("trig_L2_combmuonfeature_eta", 1);
	chain->SetBranchStatus("trig_L2_combmuonfeature_phi", 1);
	chain->SetBranchStatus("trig_L2_muonfeature_eta", 1);
	chain->SetBranchStatus("trig_L2_muonfeature_phi", 1);
	chain->SetBranchStatus("trig_L1_mu_eta", 1);
	chain->SetBranchStatus("trig_L1_mu_phi", 1);
	chain->SetBranchStatus("trig_L1_mu_thrName", 1);
	chain->SetBranchStatus("trig_RoI_EF_mu_TrigMuonEFIsolationContainer", 1);
	chain->SetBranchStatus("trig_RoI_EF_mu_TrigMuonEFIsolationContainerStatus", 1);

	/*-----------------------------------------------------------------*/

	TFile *f = new TFile("result.root", "recreate");

	TTree *t = chain->CopyTree("", "", 10);

	t->Write();

	delete t;
	delete f;

	/*-----------------------------------------------------------------*/

	TFile *f = TFile::Open("result.root");

	((TTree *) f->Get("physics"))->MakeClass("THiggsD3PD");

	delete f;

	/*-----------------------------------------------------------------*/
/*
 *	system("sed -i -e \"s/*el_GSF/*el/g\" THiggsD3PD.h");
 *	system("sed -i -e \"s/\\&el_GSF/\\&el/g\" THiggsD3PD.h");
 *
 *	system("sed -i -e \"s/*b_el_GSF/*b_el/g\" THiggsD3PD.h");
 *	system("sed -i -e \"s/\\&b_el_GSF/\\&b_el/g\" THiggsD3PD.h");
 *
 *	system("sed -i -e \"s/   el_GSF/   el/g\" THiggsD3PD.h");
 */
	/*-----------------------------------------------------------------*/

	system("sed -i -e \"s/vector/std::vector/g\" THiggsD3PD.h");
	system("sed -i -e \"s/string/std::string/g\" THiggsD3PD.h");

	system("sed -i -e \"s/#include <std::vector>/#include <vector>/g\" THiggsD3PD.h");

	system("sed -i -e \"s/#include <TFile.h>/&\\n\\n#define __IS_MC\\n\\n#define __YEAR2012/g\" THiggsD3PD.h");

	/*-----------------------------------------------------------------*/

	remove("THiggsD3PD.C");

	/*-----------------------------------------------------------------*/
}


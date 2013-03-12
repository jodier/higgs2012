#ifndef EGAMMAEVENT_EGAMMAPIDDEFS_H
#define EGAMMAEVENT_EGAMMAPIDDEFS_H
/**
  @class egammaPIDdefs
     This file defines the bit-occupation of the PID and OQ flags of egamma 
     and the enum definition of the identification results

     The enum PID contains variables related to the particle identification
     such as IsEM (cut-based selection) and Multivariate analysis.
     It contains also the word IsGoodOQ which is related to the Object quality

     The IsEM variable is coded through bit mask, each of the 32 bits
     of this variable (coded as an unsigned integer) has a meaning. 
     Two enums exist to determine the meaning of each bit, one for electrons
     and one for photons
      BitDefElectron : definition of the 32 bits defined to identify an electron
      BitDefPhoton : definition of the 32 bits defined to identify a photon

      Note that the enum BitDef is obsolete and kept for files reconstructed before rel 15.2.0
      Following these enums one can find variables which combine these
      bits to obtain different levels of identification, such as ElectronLoose, PhotonTight etc.

      The concrete use of the bits for IsEM is done in 
          egammaElectronCutIDTool.cxx : the cut-based selection for electrons
          egammaElectronCutIDToolBase.py : cut thresholds which are applied for the different menus
          egammaPhotonCutIDTool.cxx : the cut-based selection for photons
          egammaPhotonCutIDToolBase.py : cut thresholds which are applied for the different menus
      In particular it means that even if a bit is defined and enters in the 
      definition of a selection level, it does not mean that the cut is applied in practice as its threshold could have a dummy value

      The concrete use of the bits for IsGoodOQ is done in
         egammaOQFlagsBuilder.cxx : tool to fill Object Quality flags

      UPDATED:
         Jan  5, 2011: add IsEMLoose, IsEMMedium, and IsEMTight PIDs; change
                       EgPidUndefined to be an unsigned int with UINT_MAX;
         May  9, 2011: Change EgPidUndefined back to 0.
         May 31, 2011: Change EgPidUndefined back to UINT_MAX. Add flag on whether
	               the variable was found. Add ++ definitions

   @author Dirk Zerwas
*/

#include <climits>

namespace egammaPID { 
  
 /*! \enum Bitdefinitons for the egamma identification tools */
  enum PID {
    /** @brief cut-based identification for egamma objects (cluster and track-based) */
    IsEM                = 0,
    /** @brief loglikelihood identification */
    ElectronWeight,
    /** @brief loglikelihood identification */
    BgWeight,
    NeuralNet,
    Hmatrix,
    Hmatrix5,
    /** @brief cut-based identification for softe electrons in jets (for btag) */
    SofteIsEM,
    /** @brief loglikelihood identification */
    SofteElectronWeight,
    /** @brief loglikelihood identification */
    SofteBgWeight,
    SofteNeuralNet,
    /** @brief Isolation Likelihood for jet separation*/
    IsolationLikelihood_jets,
    /** @brief Isolation Likelihood for separation of electrons from heavy quark decays*/
    IsolationLikelihood_HQDelectrons,
    AdaBoost,
    /** @brief loglikelihood identification */
    PhotonWeight,
    /** @brief loglikelihood identification */
    BgPhotonWeight,
    /** @brief Fisher variable */
    FisherScore, 
    /** @brief Object Quality variable */
    IsGoodOQ,
    /** @brief cut-based identification for egamma objects (Loose) */
    IsEMLoose,
    /** @brief cut-based identification for egamma objects (Medium) */
    IsEMMedium,
    /** @brief cut-based identification for egamma objects (Tight) */
    IsEMTight,
    /** @brief Ringer Neural Network Output */
    RingerNN,
    /** @brief Default for the last enum (don't change it !)*/
    LastEgammaPID
  };


  enum egammaIDQuality {
    ElectronIDLoose,
    ElectronIDLoosePP,
    ElectronIDMedium,
    ElectronIDMediumPP,
    ElectronIDTight,
    ElectronIDTightPP,
    PhotonIDLoose,
    PhotonIDTight,
    PhotonIDLooseAR,
    PhotonIDTightAR,
    ElectronIDLooseIso,
    ElectronIDLoosePPIso,
    ElectronIDMediumIso,
    ElectronIDMediumPPIso,
    ElectronIDTightIso,
    ElectronIDTightPPIso,
    PhotonIDLooseIso,
    PhotonIDTightIso,
    PhotonIDLooseARIso,
    PhotonIDTightARIso,
    frwdElectronIDLoose,
    frwdElectronIDTight,
    NoIDCut,
    PhotonIDMedium,
    PhotonIDMediumAR
  };
    

  //const double EgPidUndefined = -999.;
  //const unsigned int EgPidUndefined = 0.;
  const unsigned int EgPidUndefined = UINT_MAX;

  /*! \enum Bitdefinitons for the egamma class, for the electron identification 
    see egammaParameters for info on the variable definitions */
  enum BitDefElectron {
    /** @brief cluster eta range */
    ClusterEtaRange_Electron        =  0,
    
    /** @brief matching to photon (not necessarily conversion--the name is historical) */
    ConversionMatch_Electron        =  1,
    
    /** @brief cluster leakage into the hadronic calorimeter */
    ClusterHadronicLeakage_Electron =  2,
    /** @brief energy in 2nd sampling (e.g E277>0) */
    ClusterMiddleEnergy_Electron    =  3, 
    /** @brief energy ratio in 2nd sampling (e.g E237/E277) */
    ClusterMiddleEratio37_Electron  =  4,
    /** @brief energy ratio in 2nd sampling (e.g E233/E237) */
    ClusterMiddleEratio33_Electron  =  5,
    /** @brief width in the second sampling (e.g Weta2) */
    ClusterMiddleWidth_Electron     =  6,

    /** @brief energy fraction in the third layer */
    ClusterBackEnergyFraction_Electron = 7,

    /** @brief fraction of energy found in 1st sampling (NB: not used in fact for electrons)*/
    ClusterStripsEratio_Electron    =  8,
    /** @brief energy of 2nd maximum in 1st sampling ~e2tsts1/(1000+const_lumi*et) */
    ClusterStripsDeltaEmax2_Electron =  9,
    /** @brief difference between 2nd maximum and 1st minimum in strips (e2tsts1-emins1) */
    ClusterStripsDeltaE_Electron    = 10,
    /** @brief shower width in 1st sampling */
    ClusterStripsWtot_Electron      = 11,
    /** @brief shower shape in shower core 1st sampling */
    ClusterStripsFracm_Electron     = 12,
    /** @brief shower width weighted by distance from the maximum one */
    ClusterStripsWeta1c_Electron    = 13,

    /** @brief difference between max and 2nd max in strips */
    ClusterStripsDEmaxs1_Electron   = 15,
    /** @brief B layer hit */
    TrackBlayer_Electron            = 16,
    /** @brief number of Pixel hits */
    TrackPixel_Electron             = 17,
    /** @brief number of Pixel and SCT hits */
    TrackSi_Electron                = 18,
    /** @brief distance of closet approach */
    TrackA0_Electron                = 19,
    /** @brief eta difference between cluster and extrapolated track in the 1st sampling */
    TrackMatchEta_Electron          = 20,
    /** @brief phi difference between cluster and extrapolated track in the 2nd sampling */
    TrackMatchPhi_Electron          = 21,
    /** @brief energy-momentum match */
    TrackMatchEoverP_Electron       = 22,
    /** @brief number of TRT hits */
    TrackTRThits_Electron           = 24,
    /** @brief ratio of high to all TRT hits for isolated electrons */
    TrackTRTratio_Electron          = 25,
    /** @brief ratio of high to all TRT hits for non-isolated electrons (not for new ++ menus) */    
    TrackTRTratio90_Electron        = 26,

    /** @brief distance of closet approach for tight selection (not to be used in new ++ menus) */
    TrackA0Tight_Electron           = 27,
    /** @brief eta difference between cluster and extrapolated track in the 1st sampling for 
	tight selection (not to be used in new ++ menus)*/
    TrackMatchEtaTight_Electron     = 28,

    /** @brief isolation */
    Isolation_Electron              = 29,
    /** @brief calorimetric isolation */
    ClusterIsolation_Electron       = 30,
    /** @brief tracker isolation */
    TrackIsolation_Electron         = 31
  };

  /*! \enum Bitdefinitons for the egamma class for photon identification
    see egammaParameters for info on the variable definitions */
  enum BitDefPhoton {
    /** @brief cluster eta range */
    ClusterEtaRange_Photon        =  0,
    /** @brief cluster eta range */
    ClusterEtaRange_PhotonLoose   =  1,

    // selection for Loose photons
    /** @brief cluster leakage into the hadronic calorimeter */
    ClusterHadronicLeakage_PhotonLoose =  2,
    /** @brief energy in 2nd sampling (e277) */
    ClusterMiddleEnergy_PhotonLoose    =  3, 
    /** @brief energy ratio in 2nd sampling */
    ClusterMiddleEratio37_PhotonLoose  =  4,
    /** @brief energy ratio in 2nd sampling */
    ClusterMiddleEratio33_PhotonLoose  =  5,
    /** @brief width in the second sampling */
    ClusterMiddleWidth_PhotonLoose     =  6,

    /** @brief energy fraction in the third layer */
    ClusterBackEnergyFraction_Photon = 7,

    // selection for tight photons
    /** @brief cluster leakage into the hadronic calorimeter */
    ClusterHadronicLeakage_Photon =  10,
    /** @brief energy in 2nd sampling (e277) */
    ClusterMiddleEnergy_Photon    =  11, 
    /** @brief energy ratio in 2nd sampling */
    ClusterMiddleEratio37_Photon  =  12,
    /** @brief energy ratio in 2nd sampling for photons */
    ClusterMiddleEratio33_Photon  =  13,
    /** @brief width in the second sampling */
    ClusterMiddleWidth_Photon     =  14,

    /** @brief fraction of energy found in 1st sampling */
    ClusterStripsEratio_Photon    =  15,
    /** @brief energy of 2nd maximum in 1st sampling ~e2tsts1/(1000+const_lumi*et) */
    ClusterStripsDeltaEmax2_Photon =  16,
    /** @brief difference between 2nd maximum and 1st minimum in strips (e2tsts1-emins1) */
    ClusterStripsDeltaE_Photon    = 17,
    /** @brief shower width in 1st sampling */
    ClusterStripsWtot_Photon      = 18,
    /** @brief shower shape in shower core 1st sampling */
    ClusterStripsFracm_Photon     = 19,
    /** @brief shower width weighted by distance from the maximum one */
    ClusterStripsWeta1c_Photon    = 20,
    /** @brief difference between max and 2nd max in strips */
    ClusterStripsDEmaxs1_Photon  = 21,

    /** @brief energy-momentum match for photon selection*/
    TrackMatchEoverP_Photon       = 22,
    
    /** @brief ambiguity resolution for photon (vs electron) */
    AmbiguityResolution_Photon    = 23,

    /** @brief isolation */
    Isolation_Photon              = 29,
    /** @brief calorimetric isolation for photon selection */
    ClusterIsolation_Photon       = 30,
    /** @brief tracker isolation for photon selection */
    TrackIsolation_Photon         = 31
  };


  //
  // cut definition for electrons
  //
  /** @brief cuts of hadronic leakage*/
  const unsigned int HADLEAKETA_ELECTRON = 
    0x1 << ClusterEtaRange_Electron        | 
    0x1 << ClusterHadronicLeakage_Electron;
  /** @brief cuts in strips (with ClusterStripsDEmaxs1)*/
  const unsigned int CALOSTRIPS_ELECTRON =
    0x1 << ClusterStripsEratio_Electron     |
    0x1 << ClusterStripsDeltaEmax2_Electron |
    0x1 << ClusterStripsDeltaE_Electron     |
    0x1 << ClusterStripsWtot_Electron       |
    0x1 << ClusterStripsFracm_Electron      |
    0x1 << ClusterStripsWeta1c_Electron     |
    0x1 << ClusterStripsDEmaxs1_Electron    ;
  const unsigned int CALOSTRIPS_LOOSE_ELECTRON =
    0x1 << ClusterStripsWtot_Electron       |
    0x1 << ClusterStripsDEmaxs1_Electron    ;
  /** @brief cuts in middle sampling*/
  const unsigned int CALOMIDDLE_ELECTRON =    
    0x1 << ClusterMiddleEnergy_Electron     |
    0x1 << ClusterMiddleEratio37_Electron   |
    0x1 << ClusterMiddleWidth_Electron     ;
  const unsigned int CALOBACK_ELECTRON = 
    0x1 << ClusterBackEnergyFraction_Electron;

  /** @brief calorimeter isolation*/
  const unsigned int CALORIMETRICISOLATION_ELECTRON = 
    0x1 << ClusterIsolation_Electron ;

  /** @brief all cuts in calorimeter (except isolation)*/
  const unsigned int CALO_ELECTRON = HADLEAKETA_ELECTRON | CALOSTRIPS_ELECTRON | CALOMIDDLE_ELECTRON | CALOBACK_ELECTRON;

  /** @brief Track quality cuts except b-layer for electrons*/
  const unsigned int TRACKINGNOBLAYER_ELECTRON =     
    0x1 << TrackPixel_Electron   |
    0x1 << TrackSi_Electron      |
    0x1 << TrackA0_Electron;
  /** @brief Track quality cuts except b-layer for electrons*/
  const unsigned int TRACKINGLOOSE_ELECTRON =     
    0x1 << TrackPixel_Electron   |
    0x1 << TrackSi_Electron;
  /** @brief Track quality cuts for electrons*/
  const unsigned int TRACKING_ELECTRON = 
    TRACKINGNOBLAYER_ELECTRON |  
    0x1 << TrackBlayer_Electron;
  /** @brief Track cluster matching in eta for electrons*/
  const unsigned int TRACKMATCHDETA_ELECTRON =
    0x1 << TrackMatchEta_Electron;
  /** @brief Track cluster matching in eta, phi for electrons*/
  const unsigned int TRACKMATCHNOEOVERP_ELECTRON =
    0x1 << TrackMatchEta_Electron      |
    0x1 << TrackMatchPhi_Electron;
  /** @brief Track cluster matching in eta, phi, E/p for electrons*/
  const unsigned int TRACKMATCH_ELECTRON =
    0x1 << TrackMatchEta_Electron      |
    0x1 << TrackMatchPhi_Electron      |
    0x1 << TrackMatchEoverP_Electron  ;
  /** @brief Tight Track cluster matching */
  const unsigned int TRACKMATCHTIGHT_ELECTRON =
    0x1 << TrackMatchEtaTight_Electron      |
    0x1 << TrackA0Tight_Electron;
  /** @brief Track cluster matching in eta tight for electrons*/
  const unsigned int TRACKMATCHDETATIGHT_ELECTRON = 
    0x1 << TrackMatchEtaTight_Electron;
  /** @brief Tight conversion matching */
  const unsigned int CONVMATCH_ELECTRON =
    0x1 << ConversionMatch_Electron;

  /** @brief TRT hits and TR ratio for electrons*/
  const unsigned int TRT_ELECTRON = 
    0x1 << TrackTRThits_Electron   |
    0x1 << TrackTRTratio_Electron;

  /** @brief TR ratio for electrons*/
  const unsigned int TRT_RATIO_ELECTRON = 
    0x1 << TrackTRTratio_Electron;

  /** @brief isolation by tracker */
  const unsigned int TRACKINGISOLATION_ELECTRON = 
    0x1 << TrackIsolation_Electron;
  /** @brief isolation for electrons is combination of calo and tracker */
  const unsigned int ISOLATION_ELECTRON = 
    0x1 << Isolation_Electron ;
  /** @brief isolation for electrons is combination of calo and tracker */
  const unsigned int CALOTRACKISOLATION_ELECTRON = 
    CALORIMETRICISOLATION_ELECTRON | TRACKINGISOLATION_ELECTRON;

  /** @brief all cuts except TRT for electrons*/
  const unsigned int ALLNOTRT_ELECTRON = 
    TRACKING_ELECTRON | TRACKMATCH_ELECTRON | CALO_ELECTRON;
  /** @brief all cuts for electrons*/
  const unsigned int ALL_ELECTRON = 
    ALLNOTRT_ELECTRON | TRT_ELECTRON;


  //////////////////////////
  // new ++ menus

  /** @brief Loose++ electron selection */
  const unsigned int ElectronLoosePP = 
    CALOMIDDLE_ELECTRON | HADLEAKETA_ELECTRON | CALOSTRIPS_LOOSE_ELECTRON | 
    TRACKMATCHDETA_ELECTRON | TRACKINGLOOSE_ELECTRON;

  /** @brief Loose++ electron selecton with isolation */
  const unsigned int ElectronLoosePPIso = 
    ElectronLoosePP |
    ISOLATION_ELECTRON;

  /** @brief Medium++ electron selecton */
  const unsigned int ElectronMediumPP =
    CALO_ELECTRON | 
    TRACKING_ELECTRON | 
    TRACKMATCHDETA_ELECTRON |
    TRT_RATIO_ELECTRON;

  /** @brief Medium++ electron selecton with isolation */
  const unsigned int ElectronMediumPPIso = 
    ElectronMediumPP |
    ISOLATION_ELECTRON;

  /** @brief Tight++ electron selecton */
  const unsigned int ElectronTightPP =
    CALO_ELECTRON | 
    TRACKING_ELECTRON | 
    TRACKMATCH_ELECTRON |
    CONVMATCH_ELECTRON |
    TRT_ELECTRON;

  /** @brief Tight++ electron selecton with isolation */
  const unsigned int ElectronTightPPIso = 
    ElectronTightPP |
    ISOLATION_ELECTRON;


  //////////////////////////
  // definitions as in 16.6, but with outliers

  /** @brief Loose electron selection */
  const unsigned int ElectronLoose = 
    CALOMIDDLE_ELECTRON | HADLEAKETA_ELECTRON;

  /** @brief Loose electron selecton with isolation */
  const unsigned int ElectronLooseIso = 
    ElectronLoose |
    ISOLATION_ELECTRON;

  /** @brief Medium electron selection with the delta eta cut has been removed */
  const unsigned int ElectronMedium_WithoutTrackMatch = 
    CALO_ELECTRON | TRACKINGNOBLAYER_ELECTRON;
  /** @brief Medium electron selection without deta match with isolation requirement */
  const unsigned int ElectronMediumIso_WithoutTrackMatch = 
    ElectronMedium_WithoutTrackMatch | 
    ISOLATION_ELECTRON;
  /** @brief Medium electron selection with deta match (was ElectronMedium in 15.X)*/
  const unsigned int ElectronMedium_WithTrackMatch = 
    CALO_ELECTRON | TRACKINGNOBLAYER_ELECTRON | TRACKMATCHDETA_ELECTRON;
  /** @brief MediumIso electron selection with deta match (was ElectronMediumIso in 15.X)*/
  const unsigned int ElectronMediumIso_WithTrackMatch = 
    ElectronMedium_WithTrackMatch | 
    ISOLATION_ELECTRON;
  /** @brief Medium electron selecton */
  const unsigned int ElectronMedium = ElectronMedium_WithTrackMatch;
  /** @brief MediumIso electron selecton */
  const unsigned int ElectronMediumIso = ElectronMediumIso_WithTrackMatch;


  /** @brief Tight electron without track match (corresponds to RobusterTight in 15.6.X but 
      without the deltaEta bits TrackMatchEta_Electron and TrackMatchEtaTight_Electron) */
  const unsigned int ElectronTight_WithoutTrackMatch = 
    CALO_ELECTRON | 
    TRACKING_ELECTRON | 
    0x1 << TrackMatchEoverP_Electron | 
    0x1 << TrackA0Tight_Electron |
    CONVMATCH_ELECTRON | 
    TRT_ELECTRON ;

  /** @brief Tight without conversion requirement or track match */
  const unsigned int ElectronTight_WithoutTrackMatch_NoConvCut = 
    CALO_ELECTRON | 
    TRACKING_ELECTRON | 
    0x1 << TrackMatchEoverP_Electron | 
    0x1 << TrackA0Tight_Electron |
    TRT_ELECTRON ;

  /** @brief Tight_WithTrackMatch electron selection with isolation requirement */
  const unsigned int ElectronTightIso_WithoutTrackMatch = 
    ElectronTight_WithoutTrackMatch | 
    ISOLATION_ELECTRON;


  /** @brief Tight electron selection with track match*/
  const unsigned int ElectronTight_WithTrackMatch = 
    CALO_ELECTRON | TRACKING_ELECTRON | TRACKMATCH_ELECTRON | 
    TRACKMATCHTIGHT_ELECTRON | CONVMATCH_ELECTRON | TRT_ELECTRON ;

  /** @brief Tight with track match without conversion requirement */
  const unsigned int ElectronTight_WithTrackMatch_NoConvCut = 
    CALO_ELECTRON | TRACKING_ELECTRON | TRACKMATCH_ELECTRON | 
    TRACKMATCHTIGHT_ELECTRON | TRT_ELECTRON ;

  /** @brief Tight_WithTrackMatch electron selection with isolation requirement */
  const unsigned int ElectronTightIso_WithTrackMatch = 
    ElectronTight_WithTrackMatch | 
    ISOLATION_ELECTRON;

  /** @brief Tight electron selection */
  const unsigned int ElectronTight = ElectronTight_WithTrackMatch;
  /** @brief Tight without conversion requirement */
  const unsigned int ElectronTight_NoConvCut = ElectronTight_WithTrackMatch_NoConvCut;
  /** @brief Tight electron selection with isolation requirement */
  const unsigned int ElectronTightIso = ElectronTightIso_WithTrackMatch;

  /** @brief Tight electron (corresponds to RobusterTight in 15.6.X with the loose deltaEta bit
      TrackMatchEta_Electron but with out the tight one TrackMatchEtaTight_Electron) */
  const unsigned int ElectronTight_WithLooseEtaTrackMatch = 
    CALO_ELECTRON | 
    TRACKING_ELECTRON | 
    TRACKMATCHDETA_ELECTRON |
    0x1 << TrackMatchEoverP_Electron | 
    0x1 << TrackA0Tight_Electron |
    CONVMATCH_ELECTRON | 
    TRT_ELECTRON ;

  /** @brief Tight electron (corresponds to RobusterTight in 15.6.X with the deltaEta bits
      TrackMatchEta_Electron and TrackMatchEtaTight_Electron) */
  const unsigned int ElectronTight_WithTightEtaTrackMatch = 
    CALO_ELECTRON | 
    TRACKING_ELECTRON | 
    TRACKMATCHDETA_ELECTRON |
    TRACKMATCHTIGHT_ELECTRON |
    0x1 << TrackMatchEoverP_Electron | 
    CONVMATCH_ELECTRON | 
    TRT_ELECTRON ;

  /** @brief Tight_WithLooseEtaTrackMatch electron selection with isolation requirement */
  const unsigned int ElectronTightIso_WithLooseEtaTrackMatch = 
    ElectronTight_WithLooseEtaTrackMatch |
    ISOLATION_ELECTRON;

  /** @brief Tight_WithTightEtaTrackMatch electron selection with isolation requirement */
  const unsigned int ElectronTightIso_WithTightEtaTrackMatch = 
    ElectronTight_WithTightEtaTrackMatch |
    ISOLATION_ELECTRON;


  //
  // for photon selection
  //
  /** @brief cuts of hadronic leakage (for Loose selection)*/
  const unsigned int HADLEAKETA_PHOTONLOOSE = 
    0x1 << ClusterEtaRange_PhotonLoose  | 
    0x1 << ClusterHadronicLeakage_PhotonLoose;
  /** @brief cuts of hadronic leakage*/
  const unsigned int HADLEAKETA_PHOTON = 
    0x1 << ClusterEtaRange_Photon        | 
    0x1 << ClusterHadronicLeakage_Photon;
  /** @brief cuts in middle sampling (for Loose selection)*/
  const unsigned int CALOMIDDLE_PHOTONLOOSE=    
    0x1 << ClusterMiddleEnergy_PhotonLoose     |
    0x1 << ClusterMiddleEratio37_PhotonLoose   |
    0x1 << ClusterMiddleEratio33_PhotonLoose   |
    0x1 << ClusterMiddleWidth_PhotonLoose     ;
  /** @brief cuts in middle sampling*/
  const unsigned int CALOMIDDLE_PHOTON =    
    0x1 << ClusterMiddleEnergy_Photon     |
    0x1 << ClusterMiddleEratio37_Photon   |
    0x1 << ClusterMiddleEratio33_Photon   |
    0x1 << ClusterMiddleWidth_Photon     ;
 /** @brief cuts in strips (with ClusterStripsDEmaxs1)*/
  const unsigned int CALOSTRIPS_PHOTON =
    0x1 << ClusterStripsEratio_Photon     |
    0x1 << ClusterStripsDeltaEmax2_Photon |
    0x1 << ClusterStripsDeltaE_Photon     |
    0x1 << ClusterStripsWtot_Photon       |
    0x1 << ClusterStripsFracm_Photon      |
    0x1 << ClusterStripsWeta1c_Photon     |
    0x1 << ClusterStripsDEmaxs1_Photon    ;

 /** @brief cuts in strips (with ClusterStripsDEmaxs1)*/
  const unsigned int CALOSTRIPS_PHOTONMEDIUM =
    0x1 << ClusterStripsDEmaxs1_Photon    ;

  /** @brief calorimeter isolation*/
  const unsigned int CALORIMETRICISOLATION_PHOTON = 
    0x1 << ClusterIsolation_Photon;
  /** @brief all cuts in calorimeter (except isolation)*/
  const unsigned int CALO_PHOTON = 
    HADLEAKETA_PHOTON | CALOSTRIPS_PHOTON | CALOMIDDLE_PHOTON;

  /** @brief isolation by tracker */
  const unsigned int TRACKINGISOLATION_PHOTON = 
    0x1 << TrackIsolation_Photon;
  /** @brief isolation for photons is combination of calo and tracker */
  const unsigned int ISOLATION_PHOTON = 
    0x1 << Isolation_Photon ;
  /** @brief isolation for photons is combination of calo and tracker */
  const unsigned int CALOTRACKISOLATION_PHOTON = 
    CALORIMETRICISOLATION_PHOTON | TRACKINGISOLATION_PHOTON;

  /** @brief Track cluster matching E/p for photons*/
  const unsigned int TRACKMATCH_PHOTON =
    0x1 << TrackMatchEoverP_Photon  ;

  /** @brief Ambigiuty resolve for photons */
  const unsigned int AMBIGUITYRESOLVE_PHOTON =
    0x1 << AmbiguityResolution_Photon;

  /** @brief Loose photon selection with Ambiguity resolver*/
  const unsigned int PhotonLooseAR = 
    CALOMIDDLE_PHOTONLOOSE | HADLEAKETA_PHOTONLOOSE | AMBIGUITYRESOLVE_PHOTON;
  /** @brief Loose photon selection with Ambiguity resolver and Isolation*/
  const unsigned int PhotonLooseARIso = PhotonLooseAR | ISOLATION_PHOTON;

  /** @brief Medium photon selection */
  const unsigned int PhotonMediumAR = PhotonLooseAR | CALOSTRIPS_PHOTONMEDIUM;

  /** @brief Tight photon selection with Ambiguity resolver*/
  const unsigned int PhotonTightAR = CALO_PHOTON | AMBIGUITYRESOLVE_PHOTON;
  /** @brief Tight photon selection with isolation and Ambiguity resolver*/
  const unsigned int PhotonTightARIso = PhotonTightAR | ISOLATION_PHOTON;

  /** @brief Loose photon selection */
  const unsigned int PhotonLoose = 
    CALOMIDDLE_PHOTONLOOSE | HADLEAKETA_PHOTONLOOSE;
  /** @brief Loose photon selection with Isolation*/
  const unsigned int PhotonLooseIso = PhotonLoose | ISOLATION_PHOTON;

  /** @brief Medium photon selection */
  const unsigned int PhotonMedium = PhotonLoose | CALOSTRIPS_PHOTONMEDIUM;

  /** @brief Tight photon selection */
  const unsigned int PhotonTight = CALO_PHOTON ;
  /** @brief Tight photon selection with isolation*/
  const unsigned int PhotonTightIso = PhotonTight | ISOLATION_PHOTON;




  /**@brief forward electron flavours */
  /*
    --variables:

    ["FIRST_ENG_DENS"] =1;
    ["ENG_FRAC_MAX"]   =2;
    ["LONGITUDINAL"]   =4;
    ["SECOND_LAMBDA"]  =8;
    ["LATERAL"]        =16;
    ["SECOND_R"]       =32;
    ["CENTER_LAMBDA"]  =64;
    
    --Flavors
    Tight: All avriables except First_ENG_DENS
    Loose: SECOND_LAMBDA, SECOND_R, CENTER_LAMBDA 
  */
  
  const unsigned int frwdElectronTight = 126;
  const unsigned int frwdElectronLoose = 104;


  //
  // for object quality flags
  //

  enum BitDefOQ {
    /** @brief Dead High Voltage in the EM Presampler */
    DeadHVPS = 0,
    /** @brief Dead High Voltage in the EM strips, middle and back affecting the core of the cluster*/
    DeadHVS1S2S3Core = 1,
    /** @brief Dead High Voltage in the EM strips, middle and back affecting the edge of the cluster*/
    DeadHVS1S2S3Edge = 2,

    /** @brief Non Nominal High Voltage in the EM Presampler */
    NonNominalHVPS = 3,
   /** @brief Non Nominal High Voltage in the EM strips, middle and back*/
    NonNominalHVS1S2S3 = 4,


    /** @brief Missing FEB in the core of the cluster */
    MissingFEBCellCore = 5,
    /** @brief Missing FEB in the edge of the cluster */
    MissingFEBCellEdgePS = 6,
    /** @brief Missing FEB in the edge of the cluster */
    MissingFEBCellEdgeS1 = 7,
    /** @brief Missing FEB in the edge of the cluster */
    MissingFEBCellEdgeS2 = 8,
    /** @brief Missing FEB in the edge of the cluster */
    MissingFEBCellEdgeS3 = 9,


    /** @brief Masked cell in the core of the cluster */
    MaskedCellCore = 10,
    /** @brief Masked presampler cell in the edge of the cluster */
    MaskedCellEdgePS = 11,
    /** @brief Masked strip cell in the edge of the cluster */
    MaskedCellEdgeS1 = 12,
    /** @brief Masked middle cell in the edge of the cluster */
    MaskedCellEdgeS2 = 13,
    /** @brief Masked back cell in the edge of the cluster */
    MaskedCellEdgeS3 = 14,

   /** @brief Missing FEB or masked cell in S1 core (corresponding to the 8 strips in front of the core of the cluster)*/
    BadS1Core = 15,


    /** @brief Sporadic noisy cell in the core of the cluster */
    SporadicNoiseLowQCore = 16,
    /** @brief Sporadic noisy cell in the edge of the cluster */
    SporadicNoiseLowQEdge = 17,

    /** @brief High quality factor cell in the core of the cluster */
    HighQCore = 18,
    /** @brief High quality factor cell in the edge of the cluster */
    HighQEdge = 19,

    /** @brief Affected cell in the core of the cluster */
    AffectedCellCore = 20,
    /** @brief Affected presampler cell in the edge of the cluster */
    AffectedCellEdgePS = 21,
    /** @brief Affected strip cell in the edge of the cluster */
    AffectedCellEdgeS1 = 22,
    /** @brief Affected middle cell in the edge of the cluster */
    AffectedCellEdgeS2 = 23,
    /** @brief Affected back cell in the edge of the cluster */
    AffectedCellEdgeS3 = 24,

    /** @brief High quality factor cell in the HEC */
    HECHighQ = 25,

    /** @brief Out of time cell */
    OutTime =26,

    /** @brief Cleaning based on LArQ factor--> sum[ E(Q>4000)/E]*/
    LArQCleaning=27,
    /** @brief Dead cell in the Tile Calorimeter S0 affecting the hadronic leakage calculation*/
    DeadCellTileS0=28,
    /** @brief Dead cell in the Tile Calorimeter S1,2,3 affecting the hadronic leakage calculation*/
    DeadCellTileS1S2=29
  };

  /** @brief */
  
  const unsigned int BADCLUSELECTRON = 
    0x1 << MaskedCellCore |
    0x1 << MissingFEBCellCore |
    0x1 << MissingFEBCellEdgeS1 |
    0x1 << MissingFEBCellEdgeS2 |
    0x1 << DeadHVS1S2S3Core | 
    0x1 << DeadHVS1S2S3Edge ; 
  
 const unsigned int BADCLUSPHOTON = 
    0x1 << MaskedCellCore |
    0x1 << MissingFEBCellCore |
    0x1 << MissingFEBCellEdgeS1 |
    0x1 << MissingFEBCellEdgeS2 |
    0x1 << DeadHVS1S2S3Core | 
    0x1 << DeadHVS1S2S3Edge |
    0x1 << BadS1Core; 
  


  const unsigned int ALLOQ= 0xFFFFFFFF;


  ////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////
  // 
  //
  //    BEWARE, OBSOLETE BELOW HERE.
  //    (only kept not to crash users who have not changed their code accordingly)
  //
  //
  ////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////

  ////////////////////
  // for electrons

  /** @brief old cuts in strips (without ClusterStripsDEmaxs1)*/
  const unsigned int CALOSTRIPSOLD_ELECTRON =
    0x1 << ClusterStripsEratio_Electron     |
    0x1 << ClusterStripsDeltaEmax2_Electron |
    0x1 << ClusterStripsDeltaE_Electron     |
    0x1 << ClusterStripsWtot_Electron       |
    0x1 << ClusterStripsFracm_Electron      |
    0x1 << ClusterStripsWeta1c_Electron     ;

  /** @brief TRT hits and TR ratio (@90% eff) for electrons*/
  const unsigned int TRT90_ELECTRON = 
    0x1 << TrackTRThits_Electron   |
    0x1 << TrackTRTratio90_Electron;

  /** @brief "old" all cuts in calorimeter (except isolation) without ClusterStripsDEmaxs1 */
  const unsigned int CALONOISOOLD_ELECTRON = HADLEAKETA_ELECTRON | CALOSTRIPSOLD_ELECTRON | CALOMIDDLE_ELECTRON ;
  /** @brief "old" all cuts in calorimeter (including isolation) without ClusterStripsDEmaxs1 */
  const unsigned int CALOOLD_ELECTRON = CALONOISOOLD_ELECTRON | CALORIMETRICISOLATION_ELECTRON;

  /** @brief all cuts except TRT for electrons(old way)*/
  const unsigned int ALLNOTRTOLD_ELECTRON = 
    TRACKING_ELECTRON | TRACKMATCH_ELECTRON | CALOOLD_ELECTRON;
  /** @brief all cuts fo electrons (old way)*/
  const unsigned int ALLOLD_ELECTRON = 
    ALLNOTRTOLD_ELECTRON | TRT_ELECTRON;

  // old definitions of cuts as in rel<15.2.0
  const unsigned int ElectronLooseOLD = 
    CALOMIDDLE_ELECTRON | HADLEAKETA_ELECTRON;
  const unsigned int ElectronMediumOLD = 
    CALOOLD_ELECTRON | TRACKINGNOBLAYER_ELECTRON | TRACKMATCHDETA_ELECTRON;
  const unsigned int ElectronMediumNoIsoOLD = 
    CALONOISOOLD_ELECTRON | TRACKINGNOBLAYER_ELECTRON | TRACKMATCHDETA_ELECTRON;
  const unsigned int ElectronTightOLD = 
    ALLOLD_ELECTRON;
  const unsigned int ElectronTightTRTNoIsoOLD = 
    TRACKING_ELECTRON | TRACKMATCH_ELECTRON | CALONOISOOLD_ELECTRON | TRT90_ELECTRON ;
  const unsigned int ElectronTightNoIsolationOLD = ElectronTightTRTNoIsoOLD;

  /** @brief obsolete - kept not crash clients */
  const unsigned int ElectronMediumNoIso = ElectronMedium;
	   
  /** @brief obsolete - kept not to crash clients */
  const unsigned int ElectronTightTRTNoIso = ElectronTight;
  /** @brief obsolete - kept not to crash clients */
  const unsigned int ElectronTightNoIsolation = ElectronTight;

  ////////////////////
  // for photons
  /** @brief old cuts in strips (without ClusterStripsDEmaxs1)*/
  const unsigned int CALOSTRIPSOLD_PHOTON =
    0x1 << ClusterStripsEratio_Photon     |
    0x1 << ClusterStripsDeltaEmax2_Photon |
    0x1 << ClusterStripsDeltaE_Photon     |
    0x1 << ClusterStripsWtot_Photon       |
    0x1 << ClusterStripsFracm_Photon      |
    0x1 << ClusterStripsWeta1c_Photon     ;

  /** @brief "old" all cuts in calorimeter (except isolation) without ClusterStripsDEmaxs1 */
  const unsigned int CALONOISOOLD_PHOTON = 
    HADLEAKETA_PHOTON | CALOSTRIPSOLD_PHOTON | CALOMIDDLE_PHOTON ;
 
  /** @brief Tight photon (old definition) */
  const unsigned int PhotonTightOLD = 
    CALONOISOOLD_PHOTON | CALORIMETRICISOLATION_PHOTON;

  /** @brief Tight electron (NB: kept for backward compatibility) */
  const unsigned int ElectronTightRobust = ElectronTight_WithLooseEtaTrackMatch;


  ////////////////////
  /*! \enum Bitdefinitons for the egamma class--very old */
  enum BitDef {
    // Cluster based egamma
    /** @brief cluster eta range */
    ClusterEtaRange        =  0,
    /** @brief cluster leakage into the hadronic calorimeter */
    ClusterHadronicLeakage =  1,
    /** @brief energy in 2nd sampling (e277) */
    ClusterMiddleEnergy    =  4, 
    /** @brief energy ratio in 2nd sampling (e237/e277) */
    ClusterMiddleEratio37  =  5,
    /** @brief energy ratio in 2nd sampling (e233/e237) for photons */
    ClusterMiddleEratio33  =  6,
    /** @brief width in the second sampling (weta2) */
    ClusterMiddleWidth     =  7,
    /** @brief fraction of energy found in 1st sampling (f1) */
    ClusterStripsEratio    =  8,
    /** @brief energy of 2nd maximum in 1st sampling ~e2tsts1/(1000+const_lumi*et) */
    ClusterStripsDeltaEmax2=  9,
    /** @brief difference between 2nd maximum and 1st minimum in strips (e2tsts1-emins1) */
    ClusterStripsDeltaE    = 10,
    /** @brief shower width in 1st sampling (wtots1) */
    ClusterStripsWtot      = 11,
    /** @brief shower shape in shower core 1st sampling (fracs1) */
    ClusterStripsFracm     = 12,
    /** @brief shower width weighted by distance from the maximum one (weta1) */
    ClusterStripsWeta1c    = 13,
    /** @brief calorimetric isolation (etcone20) */
    ClusterIsolation       = 14,
    /** @brief difference between max and 2nd max in strips */
    ClusterStripsDEmaxs1  = 15,
    //Track based egamma
    /** @brief B layer hit */
    TrackBlayer            = 16,
    /** @brief number of Pixel hits */
    TrackPixel             = 17,
    /** @brief number of Pixel and SCT hits */
    TrackSi                = 18,
    /** @brief distance of closet approach */
    TrackA0                = 19,
    /** @brief eta difference between cluster and extrapolated track in the 1st sampling */
    TrackMatchEta          = 20,
    /** @brief phi difference between cluster and extrapolated track in the 2nd sampling */
    TrackMatchPhi          = 21,
    /** @brief energy-momentum match */
    TrackMatchEoverP       = 22,
    /** @brief number of TRT hits */
    TrackTRThits           = 24,
    /** @brief ratio of high to all TRT hits for isolated electrons */
    TrackTRTratio          = 25,
    /** @brief ratio of high to all TRT hits for non-isolated electrons */    
    TrackTRTratio90        = 26,
    /** @brief tracker isolation (ptcone30) */
    TrackIsolation       = 27
  };
  //
  // old definition of cut bits, kept only not break codes 
  // It has to be used on "old" AODs produced with "rel 14"
  //
  /** @brief cuts of hadronic leakage*/
  const unsigned int HADLEAKETA = 
    0x1 << ClusterEtaRange        | 
    0x1 << ClusterHadronicLeakage;
  /** @brief old cuts in strips (without ClusterStripsDEmaxs1)*/
  const unsigned int CALOSTRIPSOLD=
    0x1 << ClusterStripsEratio     |
    0x1 << ClusterStripsDeltaEmax2 |
    0x1 << ClusterStripsDeltaE     |
    0x1 << ClusterStripsWtot       |
    0x1 << ClusterStripsFracm      |
    0x1 << ClusterStripsWeta1c     ;
  /** @brief cuts in strips (with ClusterStripsDEmaxs1)*/
  const unsigned int CALOSTRIPS=
    0x1 << ClusterStripsEratio     |
    0x1 << ClusterStripsDeltaEmax2 |
    0x1 << ClusterStripsDeltaE     |
    0x1 << ClusterStripsWtot       |
    0x1 << ClusterStripsFracm      |
    0x1 << ClusterStripsWeta1c     |
    0x1 << ClusterStripsDEmaxs1    ;
  /** @brief cuts in middle sampling*/
  const unsigned int CALOMIDDLE=    
    0x1 << ClusterMiddleEnergy     |
    0x1 << ClusterMiddleEratio37   |
    0x1 << ClusterMiddleEratio33   |
    0x1 << ClusterMiddleWidth     ;
  /** @brief calorimeter isolation*/
  const unsigned int CALOISO = 0x1 << ClusterIsolation ;
  /** @brief "old" all cuts in calorimeter (except isolation) without ClusterStripsDEmaxs1 */
  const unsigned int CALONOISOOLD = HADLEAKETA | CALOSTRIPSOLD | CALOMIDDLE ;
  /** @brief all cuts in calorimeter (except isolation)*/
  const unsigned int CALONOISO = HADLEAKETA | CALOSTRIPS | CALOMIDDLE ;
  /** @brief all cuts in calorimeter (including isolation) without ClusterStripsDEmaxs1 */
  const unsigned int CALOOLD = CALONOISOOLD | CALOISO ;
  /** @brief all cuts in calorimeter (including isolation) */
  const unsigned int CALO = CALONOISO | CALOISO ;

  /** @brief */
  const unsigned int TRACKINGNOBLAYER =     
    0x1 << TrackPixel   |
    0x1 << TrackSi      |
    0x1 << TrackA0     ;
  const unsigned int TRACKING = TRACKINGNOBLAYER |  0x1 << TrackBlayer;
  const unsigned int TRACKMATCHDETA =
    0x1 << TrackMatchEta;
  const unsigned int TRACKMATCH =
    0x1 << TrackMatchEta      |
    0x1 << TrackMatchPhi      |
    0x1 << TrackMatchEoverP  ;
  const unsigned int TRACKMATCHNOEOVERP =
    0x1 << TrackMatchEta      |
    0x1 << TrackMatchPhi     ;
  const unsigned int TRT = 
    0x1 << TrackTRThits   |
    0x1 << TrackTRTratio ;
  const unsigned int TRT90 = 
    0x1 << TrackTRThits   |
    0x1 << TrackTRTratio90 ;
  /** @brief isolation by tracker */
  const unsigned int TRACKISO = 0x1 << TrackIsolation;
  /** @brief */
  const unsigned int ALLNOTRT= TRACKING | TRACKMATCH | CALO;
  /** @brief */
  const unsigned int ALLNOTRTOLD= TRACKING | TRACKMATCH | CALOOLD;
  /** @brief all cuts*/
  //const unsigned int ALL= ALLNOTRT | TRT;
  const unsigned int ALL= 0xFFFFFFFF;
  /** @brief all cuts (old way)*/
  const unsigned int ALLOLD= ALLNOTRTOLD | TRT;

  // old definitions of cuts as for AODS in rel<15.2.0
  const unsigned int ElectronLooseOLDRel = CALOMIDDLE | HADLEAKETA;
  const unsigned int ElectronMediumOLDRel = CALOOLD | TRACKINGNOBLAYER | TRACKMATCHDETA;
  const unsigned int ElectronMediumNoIsoOLDRel = CALONOISOOLD | TRACKINGNOBLAYER | TRACKMATCHDETA ;
  const unsigned int ElectronTightOLDRel = ALLOLD;
  const unsigned int ElectronTightTRTNoIsoOLDRel = TRACKING | TRACKMATCH | CALONOISOOLD | TRT90 ;
  const unsigned int ElectronTightNoIsolationOLDRel = ElectronTightTRTNoIsoOLDRel;

  const unsigned int PhotonTightOLDRel = CALOOLD;


}


#endif // EGAMMAREC_EGAMMAPIDDEFS_H


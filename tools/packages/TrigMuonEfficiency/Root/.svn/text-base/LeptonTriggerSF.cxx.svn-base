// STL include(s):
#include <stdexcept>
#include <sstream>
#include <iostream>

// Local include(s):
#include "TrigMuonEfficiency/LeptonTriggerSF.h"
#include "ElectronEfficiencyCorrection/TElectronEfficiencyCorrectionTool.h"


// ROOT include(s):
#include "TFile.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TRandom.h"
#include "TDirectory.h"
#include "TLorentzVector.h"
#include "TH2.h"

//
// Constant declaration(s):
//
static const double commonSystMTSG = 0.01;
static const double muon_barrel_endcap_boundary = 1.05;
static const double electron_maximum_eta = 2.47;
static const double GeVtoMeV = 1000.;



/// Helper macro for printing nice error messages
/**
 * This macro is used to print some pretty error messages that specify
 * the file name and line number. This can be very useful when debugging
 * problems.
 *
 * It can be placed into a ROOT print function like this:
 *
 * <code>
 *  ::Error( "ThisFunction", ERROR_MESSAGE( "My message with an int %i" ), myInt );
 * </code>
 *
 * @param MESSAGE The message to "make pretty"
 */
#define ERROR_MESSAGE( MESSAGE )                \
   "%s:%i " MESSAGE, __FILE__, __LINE__



/*=================================================================* 
 * constructor/destructor
 *=================================================================*/
LeptonTriggerSF::LeptonTriggerSF(const std::string& directory,
                                 const std::string& directoryElectron,
                                 const std::string& electronFileVersion)
  : m_year(2011),
    m_efficiencyMap(),
    m_phiBoundaryBarrel(0.0),
    m_phiBoundaryEndcap(0.0),
    m_IsAFII(false)
{
  m_electronFileVersion = electronFileVersion;
  initialise(directory, "", std::vector<std::string>(), directoryElectron);
}



LeptonTriggerSF::LeptonTriggerSF(const int year,
                                 const std::string& directory,
                                 const std::string& fileName,
                                 const std::string& directoryElectron,
                                 const std::string& electronFileVersion)
  : m_year(year),
    m_efficiencyMap(),
    m_phiBoundaryBarrel(0.0),
    m_phiBoundaryEndcap(0.0),
    m_IsAFII(false)
{
  m_electronFileVersion = electronFileVersion;
  initialise(directory, fileName, std::vector<std::string>(), directoryElectron);
}



LeptonTriggerSF::LeptonTriggerSF(const int year,
                                 const std::vector<std::string>& qualities,
                                 const std::string& directory,
                                 const std::string& fileName,
                                 const std::string& directoryElectron,
                                 const std::string& electronFileVersion)
  : m_year(year),
    m_efficiencyMap(),
    m_phiBoundaryBarrel(0.0),
    m_phiBoundaryEndcap(0.0),
    m_IsAFII(false)
{
  m_electronFileVersion = electronFileVersion;
  initialise(directory, fileName, qualities, directoryElectron);
}



LeptonTriggerSF::~LeptonTriggerSF()
{
  for (EfficiencyMap::const_iterator cit = m_efficiencyMap.begin();
       cit != m_efficiencyMap.end();
       cit++) {
    delete cit->second;
  }

  for (ElectronEfficiencyToolMap::const_iterator cit = m_electronSF.begin();
       cit != m_electronSF.end();
       cit++) {
    delete cit->second;
  }
}



/*=================================================================* 
 * public methods
 *=================================================================*/
std::pair<double, double>
LeptonTriggerSF::GetTriggerSF(const int runNumber,
                              const bool useGeV,
                              const std::vector<TLorentzVector>& muons, 
                              const MuonQuality muonQuality,
                              const int systematicVariation,
                              TrigMuonEff::Configuration* config) const
{
  std::vector< MuonQuality > muonsQuality(muons.size(), muonQuality);
  std::vector<TLorentzVector> electrons;
  std::vector<ElectronQuality> electronsQuality;

  TrigMuonEff::Configuration configuration;
  configuration.runNumber = runNumber;
  configuration.useGeV = useGeV;
  configuration.setByUser = false;
  configuration.isAFII = m_IsAFII;
  configuration.systematics = systematicVariation;

  if (config) {
    configuration.setByUser = true;
    configuration.trigger = config->trigger;
    configuration.period = config->period;
    configuration.binning = config->binning;
  }

  return GetTriggerSF(configuration, muons, muonsQuality, electrons, electronsQuality);
}



std::pair<double, double>
LeptonTriggerSF::GetTriggerSF(const int runNumber,
                              const bool useGeV,
                              const std::vector<TLorentzVector>& muons,
                              const std::vector<MuonQuality>& muonsQuality,
                              const int systematicVariation,
                              TrigMuonEff::Configuration* config) const
{
  std::vector<TLorentzVector> electrons;
  std::vector<ElectronQuality> electronsQuality;

  TrigMuonEff::Configuration configuration;
  configuration.runNumber = runNumber;
  configuration.useGeV = useGeV;
  configuration.setByUser = false;
  configuration.isAFII = m_IsAFII;
  configuration.systematics = systematicVariation;

  if (config) {
    configuration.setByUser = true;
    configuration.trigger = config->trigger;
    configuration.period = config->period;
    configuration.binning = config->binning;
  }

  return GetTriggerSF(configuration, muons, muonsQuality, electrons, electronsQuality);
}



std::pair<double, double>
LeptonTriggerSF::GetTriggerSF(const int runNumber,
                              const bool useGeV,
                              const std::vector<TLorentzVector>& muons,
                              const std::vector<MuonQuality>& muonsQuality,
                              const std::string& trigger,
                              const int systematicVariation,
                              TrigMuonEff::Configuration* config) const
{
  TrigMuonEff::Configuration configuration;
  configuration.runNumber = runNumber;
  configuration.useGeV = useGeV;
  configuration.systematics = systematicVariation;
  configuration.setByUser = false;
  configuration.isAFII = m_IsAFII;

  if (config) {
    configuration.setByUser = true;
    configuration.trigger = config->trigger;
    configuration.period = config->period;
    configuration.binning = config->binning;
  }

  return GetTriggerSF(configuration, muons, muonsQuality, trigger);
}



std::pair<double, double>
LeptonTriggerSF::GetTriggerSF(const int runNumber,
                              const bool useGeV,
                              const std::vector<TLorentzVector>& muons,
                              const MuonQuality muonQuality,
                              const std::vector<TLorentzVector>& electrons,
                              const ElectronQuality electronQuality,
                              const int systematicVariation,
                              TrigMuonEff::Configuration* config) const
{
  std::vector<MuonQuality> muonsQuality(muons.size(), muonQuality);
  std::vector<ElectronQuality> electronsQuality(electrons.size(), electronQuality);

  TrigMuonEff::Configuration configuration;
  configuration.runNumber = runNumber;
  configuration.useGeV = useGeV;
  configuration.setByUser = false;
  configuration.isAFII = m_IsAFII;
  configuration.systematics = systematicVariation;

  if (config) {
    configuration.setByUser = true;
    configuration.trigger = config->trigger;
    configuration.period = config->period;
    configuration.binning = config->binning;
  }

  return GetTriggerSF(configuration, muons, muonsQuality, electrons, electronsQuality);
}



std::pair<double, double>
LeptonTriggerSF::GetTriggerSF(const int runNumber,
                              const bool useGeV,
                              const std::vector<TLorentzVector>& muons,
                              const std::vector<MuonQuality>& muonsQuality,
                              const std::vector<TLorentzVector>& electrons,
                              const std::vector<ElectronQuality>& electronsQuality,
                              const int systematicVariation,
                              TrigMuonEff::Configuration* config) const
{
  TrigMuonEff::Configuration configuration;
  configuration.runNumber = runNumber;
  configuration.useGeV = useGeV;
  configuration.systematics = systematicVariation;
  configuration.setByUser = false;
  configuration.isAFII = m_IsAFII;

  if (config) {
    configuration.setByUser = true;
    configuration.trigger = config->trigger;
    configuration.period = config->period;
    configuration.binning = config->binning;
  }

  return GetTriggerSF(configuration, muons, muonsQuality, electrons, electronsQuality);
}



std::pair<double, double>
LeptonTriggerSF::GetTriggerSF(const TrigMuonEff::Configuration& configuration,
                              const std::vector< TLorentzVector >& muons,
                              const std::vector< MuonQuality >& muonsQuality,
                              const std::vector< TLorentzVector >& electrons,
                              const std::vector< ElectronQuality >& electronsQuality) const
{
  // Get the offline muon and electron thresholds:
  const std::pair< double, double > threshold = getThresholds(configuration);

  double rate_not_fired_data = 1.;
  double rate_not_fired_mc   = 1.;

  // needed for uncertainty calculation
  double inv_sq_eff_data    = 0.;
  double inv_sq_eff_mc      = 0.;
  double inv_sq_eff_data_el = 0.;
  double inv_sq_eff_mc_el   = 0.;
  double inv_sq_eff_data_mu = 0.;
  double inv_sq_eff_mc_mu   = 0.;

  for (size_t ielec = 0; ielec < electrons.size(); ++ielec) {

    const int set_data = getElectronQuality(configuration.runNumber, electronsQuality.at(ielec), true);
    const int set_mc   = getElectronQuality(configuration.runNumber, electronsQuality.at(ielec), false);

    double eff_data = 0., eff_mc = 0.;    
    double err_data = 0., err_mc = 0.;    

    if (((electrons.at(ielec)).Pt() < threshold.second) or
        (fabs((electrons.at(ielec)).Eta()) >= electron_maximum_eta)) {

      eff_data = 0.;
      eff_mc   = 0.;
      err_data = 0.;
      err_mc   = 0.;

    } else {

      // get efficiency from data
      std::pair<double, double> rc;
      rc = ElEff_Data(electrons.at(ielec), set_mc, set_data, m_year, configuration);
      eff_data = rc.first;
      err_data = rc.second;

      // get efficiency from MC
      rc = ElEff_MC(electrons.at(ielec), set_mc, m_year, configuration);
      eff_mc = rc.first;
      err_mc = rc.second;

    }
    
    rate_not_fired_data *= (1. - eff_data);
    rate_not_fired_mc   *= (1. - eff_mc);

    // needed for uncertainty calculation
    if (eff_data) {
      const double c = err_data/( 1. - eff_data );
      inv_sq_eff_data += c*c;
      inv_sq_eff_data_el += c*c; // contribution only due to electron trigger
    }

    if (eff_mc) {
      const double c = err_mc/( 1. - eff_mc );
      inv_sq_eff_mc += c*c;
      inv_sq_eff_mc_el += c*c; // contribution only due to electron trigger
    }
  }

  for (size_t imuon = 0; imuon < muons.size(); ++imuon) {

    double eff_data = 0., eff_mc = 0.;
    double err_data = 0., err_mc = 0.;

    if ((muons.at(imuon)).Pt() < threshold.first) {

      eff_data = 0.;
      eff_mc   = 0.;
      err_data = 0.;
      err_mc   = 0.;

    } else {

      if (not configuration.setByUser) {
        if (not setConfiguration(const_cast<TrigMuonEff::Configuration&>(configuration))) {
          return std::make_pair( 0., 0. );
        }
      }


      if (muonsQuality.at(imuon) == CaloMuon) continue;

      // get efficiency from data
      configuration.isData = true;
      std::pair<double, double> rc;
      rc = getMuonEfficiency(configuration, muons.at(imuon), muonsQuality.at(imuon));
      eff_data = rc.first;
      err_data = rc.second;

      // get efficiency from MC
      configuration.isData = false;
      rc = getMuonEfficiency(configuration, muons.at(imuon), muonsQuality.at(imuon));
      eff_mc = rc.first;
      err_mc = rc.second;

    }

    rate_not_fired_data *= ( 1. - eff_data );
    rate_not_fired_mc   *= ( 1. - eff_mc );

    // needed for uncertainty calculation
    if (eff_data) {
      const double c = err_data/( 1. - eff_data );
      inv_sq_eff_data += c*c;
      inv_sq_eff_data_mu += c*c; // contribution only due to muon trigger
    }

    if (eff_mc) {
      const double c = err_mc/( 1. - eff_mc );
      inv_sq_eff_mc += c*c;
      inv_sq_eff_mc_mu += c*c; // contribution only due to muon trigger
    }
  }

  double event_SF = 1.;
  double event_SF_err = 0.;
  double event_SF_err_el = 0.;
  double event_SF_err_mu = 0.;

  // prevent events with no triggered electrons or muons
  if ((electrons.size() or muons.size()) and
      (fabs(1. - rate_not_fired_mc) > 0.0001)) {

    event_SF        = ( 1. - rate_not_fired_data ) / ( 1. - rate_not_fired_mc );

    event_SF_err    = getSfError( rate_not_fired_data, rate_not_fired_mc,
                                  inv_sq_eff_data, inv_sq_eff_mc );
    event_SF_err_el = getSfError( rate_not_fired_data, rate_not_fired_mc,
                                  inv_sq_eff_data_el, inv_sq_eff_mc_el );
    event_SF_err_mu = getSfError( rate_not_fired_data, rate_not_fired_mc,
                                    inv_sq_eff_data_mu, inv_sq_eff_mc_mu );
  }
  

  switch (configuration.systematics) {
    case noVariation:
    case statisticalOnlyMuon:
      return std::make_pair( event_SF, event_SF_err ); 

    case plusOneSigma:
      return std::make_pair(event_SF + event_SF_err, event_SF_err);

    case minusOneSigma:
      return std::make_pair( event_SF - event_SF_err, event_SF_err ); 

    case plusOneSigmaElectron:
      return std::make_pair( event_SF + event_SF_err_el, event_SF_err ); 

    case minusOneSigmaElectron:
      return std::make_pair( event_SF - event_SF_err_el, event_SF_err); 

    case plusOneSigmaMuon:
      return std::make_pair( event_SF + event_SF_err_mu, event_SF_err); 

    case minusOneSigmaMuon:
      return std::make_pair( event_SF - event_SF_err_mu, event_SF_err); 

    default:
      ::Warning("LeptonTriggerSF::GetTriggerSF",
                "unknown systematics option '%i' given: no systematic variation used", configuration.systematics);
      return std::make_pair( event_SF, event_SF_err ); 
  }
}



std::pair<double, double>
LeptonTriggerSF::GetTriggerSF(const TrigMuonEff::Configuration& config,
                              const std::vector<TLorentzVector>& muons,
                              const std::vector<MuonQuality>& muonsQuality,
                              const std::string& trigger) const
{
  if (muons.size() != 2) {
    ::Fatal("LeptonTriggerSF::GetTriggerSF",
            ERROR_MESSAGE("Currently dimuon trigger chains only implemented for events with exactly 2 muons."));
    throw std::runtime_error("Muon vector has wrong size");
  }

  double eff_data = 0., eff_mc = 0.;
    
  if (not config.setByUser) {
    if (not setConfiguration(const_cast<TrigMuonEff::Configuration&>(config))) {
      return std::make_pair( 0., 0. );
    }
  }

  const bool is_mu24i_tight_or_mu36_tight = (trigger.find("mu24i_tight_or_mu36_tight") != std::string::npos);
  const bool is_mu18_tight_mu8_EFFS = (trigger.find("mu18_tight_mu8_EFFS") != std::string::npos);
  const bool is_2mu13 = (trigger.find("2mu13") != std::string::npos);

  // get efficiency from data
  config.isData = true;
  if ((is_mu24i_tight_or_mu36_tight and is_mu18_tight_mu8_EFFS) or
      (is_mu24i_tight_or_mu36_tight and is_2mu13)) { // single OR dimuon
    eff_data = getSingleOrDimuonEfficiency(config, muons, muonsQuality, trigger);     

  } else if (is_mu18_tight_mu8_EFFS or is_2mu13) {
    eff_data = getDimuonEfficiency(config, muons, muonsQuality, trigger); // dimuon only

  } else {
    ::Fatal("LeptonTriggerSF::GetTriggerSF",
            ERROR_MESSAGE("unknown trigger combination: %s"), trigger.c_str());
    throw std::runtime_error("unknown trigger combination");
  }

  /// get efficiency from MC
  config.isData = false;
  if ((is_mu24i_tight_or_mu36_tight and is_mu18_tight_mu8_EFFS) or
      (is_mu24i_tight_or_mu36_tight and is_2mu13)) { // single OR dimuon
    eff_mc = getSingleOrDimuonEfficiency(config, muons, muonsQuality, trigger);

  } else if (is_mu18_tight_mu8_EFFS or is_2mu13) {
    eff_mc = getDimuonEfficiency(config, muons, muonsQuality, trigger); // dimuon only     
  }

  double event_SF = 1.;
  double event_SF_err = 0.;
    
  // prevent events with no triggered muons
  if (( muons.size()) and (fabs(eff_mc) > 0.0001)) event_SF = eff_data / eff_mc;
  /*std::cout << "eff_data = " << eff_data << ", eff_mc = " << eff_mc << std::endl;
  std::cout << "Muon 1: pT = " << muons[0].Pt() << ", eta = " << muons[0].Eta() << ", phi = " << muons[0].Phi() << std::endl;
  std::cout << "Muon 2: pT = " << muons[1].Pt() << ", eta = " << muons[1].Eta() << ", phi = " << muons[1].Phi() << std::endl;*/

  return std::make_pair(event_SF, event_SF_err); 
}



std::pair<double, double>
LeptonTriggerSF::getMuonEfficiency(const TrigMuonEff::Configuration& configuration,
                                   const TLorentzVector& muon,
                                   const MuonQuality muonQuality,
                                   const std::string& trigger) const
{
  if (muonQuality == CaloMuon) return std::make_pair(0.0, 0.0);

  const double mu_eta = muon.Eta();
  const double mu_phi = fixPhiRange(muon);

  const std::string type = (configuration.isData ? "_data" : "_mc");
  const std::string region = ((fabs(mu_eta) < muon_barrel_endcap_boundary) ? "_barrel" : "_endcap" );
  const std::string quality = getMuonQuality(muonQuality);
  const std::string chain = (trigger.empty() ? configuration.trigger : trigger);

  const std::string histname = "_MuonTrigEff_" + configuration.period + ((m_year > 2011) ? chain + "_" : "") + quality +
                               "_EtaPhi_" + configuration.binning + region + type;

  const EfficiencyMap* map = &m_efficiencyMap;

  if (configuration.replicaIndex >= 0) {
    if (configuration.replicaIndex < (int) m_efficiencyMapReplicaArray.size()) {
      map = &m_efficiencyMapReplicaArray.at(configuration.replicaIndex);

    } else {
      ::Fatal("LeptonTriggerSF::getMuonEfficiency",
              ERROR_MESSAGE("index for replicated histograms is out of range. %d"), configuration.replicaIndex);
      throw std::runtime_error( "Internal coding error detected" );
    }
  }

  EfficiencyMap::const_iterator cit = map->find(histname);
  if (cit == map->end()) {
    ::Fatal("LeptonTriggerSF::getMuonEfficiency",
            ERROR_MESSAGE("Could not find what you are looking for in the efficiency map. \"%s\" "
                          "This is either a bug or you are not using the right .root file, please double check."),
                          histname.c_str() );
    throw std::runtime_error( "Internal coding error detected" );
  }

  const int bin = (cit->second)->FindFixBin(mu_eta, mu_phi);
  const double efficiency = (cit->second)->GetBinContent(bin);
  const double statisticalError = (cit->second)->GetBinError(bin);

  const double systematicError = commonSystMTSG * efficiency;
  double uncertainty = 0;
  switch (configuration.systematics) {
    case statisticalOnlyMuon:
      uncertainty = statisticalError;
      break;

    case systematicOnlyMuon:
      uncertainty = systematicError;
      break;

    default:
      uncertainty = sqrt(statisticalError*statisticalError + systematicError*systematicError);
      break;
  };

  return std::make_pair(efficiency, uncertainty);
}



double
LeptonTriggerSF::getDimuonEfficiency(const TrigMuonEff::Configuration& configuration,
                                     const std::vector<TLorentzVector>& muons,
                                     const std::vector<MuonQuality>& muonsQuality,
                                     const std::string& chain) const
{
  DimuonThresholds thresholds;
  getDimuonThresholds(configuration, thresholds);

  double threshold_leg1 = 0.;
  double threshold_leg2 = 0.;

  if (chain.find("mu18_tight_mu8_EFFS") != std::string::npos) {
    threshold_leg1 = thresholds.mu18_tight;
    threshold_leg2 = thresholds.mu8_EFFS;

  } else if (chain.find("2mu13") != std::string::npos) {
    threshold_leg1 = thresholds.mu13;
    threshold_leg2 = thresholds.mu13;

  } else {
    ::Error("LeptonTriggerSF::getDimuonEfficiency",
      ERROR_MESSAGE("Invalid dimuon or combination of single and dimuon trigger chain name given"));
  }

  double eff_mu1_leg1 = 0.;
  double eff_mu2_leg1 = 0.;
  double eff_mu1_leg2 = 0.;
  double eff_mu2_leg2 = 0.;
  double eff_mu1_bothlegs = 0.;
  double eff_mu2_bothlegs = 0.;

  DimuonTrigger dimuon;
  getDimuonLegs(chain, dimuon);

  enum {
    Leg1 = 0,
    Leg2 = 1
  };

  if ((muons.at(Leg1)).Pt() >= threshold_leg1) {
    eff_mu1_leg1 = getMuonEfficiency(configuration, muons.at(Leg1), muonsQuality.at(Leg1), dimuon.leg1).first;
    eff_mu1_bothlegs = getMuonEfficiency(configuration, muons.at(Leg1), muonsQuality.at(Leg1), dimuon.bothLegs).first;
  }

  if ((muons.at(Leg2)).Pt() >= threshold_leg1) {
    eff_mu2_leg1 = getMuonEfficiency(configuration, muons.at(Leg2), muonsQuality.at(Leg2), dimuon.leg1).first;
    eff_mu2_bothlegs = getMuonEfficiency(configuration, muons.at(Leg2), muonsQuality.at(Leg2), dimuon.bothLegs).first;
  }

  if ((muons.at(Leg1)).Pt() >= threshold_leg2) eff_mu1_leg2 = getMuonEfficiency(configuration, muons.at(Leg1), muonsQuality.at(Leg1), dimuon.leg2).first;
  if ((muons.at(Leg2)).Pt() >= threshold_leg2) eff_mu2_leg2 = getMuonEfficiency(configuration, muons.at(Leg2), muonsQuality.at(Leg2), dimuon.leg2).first;

  /*if(config.isData){
    std::cout << "DATA: di_eff_mu1 = " << eff_mu1_leg1 << std::endl;
    std::cout << "DATA: di_eff_mu2 = " << eff_mu2_leg1 << std::endl;
  } else{
    std::cout << "MC: di_eff_mu1 = " << eff_mu1_leg1 << std::endl;
    std::cout << "MC: di_eff_mu2 = " << eff_mu2_leg1 << std::endl;
    }*/

  return eff_mu1_leg1*eff_mu2_leg2 + eff_mu2_leg1*eff_mu1_leg2 - eff_mu1_bothlegs*eff_mu2_bothlegs;

}



double
LeptonTriggerSF::getSingleOrDimuonEfficiency(const TrigMuonEff::Configuration& config,
                                             const std::vector<TLorentzVector>& muons,
                                             const std::vector<MuonQuality>& muonsQuality,
                                             const std::string& chain) const
{
  if (config.trigger.compare("mu24i_tight_or_EF_mu36_tight") != 0) {
    ::Fatal("LeptonTriggerSF::getSingleOrDimuonEfficiency",
            ERROR_MESSAGE("Currently dimuon trigger only with (mu24i_tight_or_mu_36_tight) trigger is supported: %s"),
            config.trigger.c_str());
    throw std::runtime_error("Currently dimuon trigger only with (mu24i_tight_or_mu_36_tight) trigger is supported");
  }

  const std::pair<double, double> threshold = getThresholds(config);

  double single_eff_tmp = 0.;
  double dimuon_eff_tmp = 0.;
  double overlap_term = 0.;

  const double mu1_eff = getMuonEfficiency(config, muons.at(0), muonsQuality.at(0)).first;
  const double mu2_eff = getMuonEfficiency(config, muons.at(1), muonsQuality.at(1)).first;
  
  const bool is_mu18_tight_mu8_EFFS = (chain.find("mu18_tight_mu8_EFFS") != std::string::npos);
  const bool is_2mu13 = (chain.find("2mu13") != std::string::npos);

  if (is_mu18_tight_mu8_EFFS) {
    dimuon_eff_tmp = getDimuonEfficiency(config, muons, muonsQuality, "mu18_tight_mu8_EFFS");

  } else if (is_2mu13) {
    dimuon_eff_tmp = getDimuonEfficiency(config, muons, muonsQuality, "2mu13");

  } else {
    ::Error("LeptonTriggerSF::getSingleOrDimuonEfficiency",
      ERROR_MESSAGE("Invalid dimuon chain name given: %s"), chain.c_str());
    return -1.;
  }
  

  const bool is_mu1_above_threshold = ((muons.at(0)).Pt() >= threshold.first);
  const bool is_mu2_above_threshold = ((muons.at(1)).Pt() >= threshold.first);

  // all above threshold
  if (is_mu1_above_threshold and is_mu2_above_threshold) {
    single_eff_tmp = mu1_eff + mu2_eff - mu1_eff*mu2_eff;

    if (is_mu18_tight_mu8_EFFS) {
      overlap_term = getMuonEfficiency(config, muons.at(0), muonsQuality.at(0), "mu18_tight").first*
                     getMuonEfficiency(config, muons.at(1), muonsQuality.at(1), "mu18_tight").first; // this still needs to be checked!

    } else {
      // check whether mu13 or mu24i_tight_or_mu36_tight is more efficient
      double higher_mu1 = 0;
      double higher_mu2 = 0;
      double eff = getMuonEfficiency(config, muons.at(0), muonsQuality.at(0), "mu13").first;
      higher_mu1 = (mu1_eff > eff) ? mu1_eff : eff;

      eff = getMuonEfficiency(config, muons.at(1), muonsQuality.at(1), "mu13").first;
      higher_mu2 = (mu2_eff > eff) ? mu2_eff : eff;

      overlap_term = higher_mu1*higher_mu2;
    }

  // one above, one below threshold
  } else if (((not is_mu1_above_threshold) and is_mu2_above_threshold) or
             ((not is_mu2_above_threshold) and is_mu1_above_threshold)) {
    if (is_mu1_above_threshold) single_eff_tmp = mu1_eff;
    if (is_mu2_above_threshold) single_eff_tmp = mu2_eff;
    if (chain.find("mu18_tight_mu8_EFFS") != std::string::npos ) {
      overlap_term = getMuonEfficiency(config, muons.at(0), muonsQuality.at(0), "mu18_tight").first*
                     getMuonEfficiency(config, muons.at(1), muonsQuality.at(1), "mu18_tight").first; // this still needs to be checked!
    } else {
      overlap_term = single_eff_tmp*dimuon_eff_tmp;
    }
  }

  /*if(config.isData){
    std::cout << "DATA: single_eff = " << single_eff_tmp << ", di_eff = " << dimuon_eff_tmp << ", overlap_term = " << overlap_term << std::endl;
    std::cout << "DATA: single_eff_mu1 = " << mu1_eff << " +- " << getMuonEfficiency(config, muons[0], muonq[0]).second << std::endl;
    std::cout << "DATA: single_eff_mu2 = " << mu2_eff << " +- " << getMuonEfficiency(config, muons[1], muonq[1]).second << std::endl;
  } else{
    std::cout << "MC: single_eff = " << single_eff_tmp << ", di_eff = " << dimuon_eff_tmp << ", overlap_term = " << overlap_term << std::endl;
    std::cout << "MC: single_eff_mu1 = " << mu1_eff << " +- " << getMuonEfficiency(config, muons[0], muonq[0]).second << std::endl;
    std::cout << "MC: single_eff_mu2 = " << mu2_eff << " +- " << getMuonEfficiency(config, muons[1], muonq[1]).second << std::endl;
    }*/

  return single_eff_tmp + dimuon_eff_tmp - overlap_term;

}



std::pair<double, double>
LeptonTriggerSF::getElectronSF(const TLorentzVector& electron,
                               const int combination,
                               const int /* year : not needed for ElectronEfficiencyCorrection */,
                               const TrigMuonEff::Configuration& config) const
{
  const double eta = electron.Eta();
  double pt = electron.Pt();
  if (config.useGeV) pt *= GeVtoMeV;

  if (not m_electronSF[combination]) throw std::runtime_error("getElectronSF: m_electronSF[..] is not initialised for the given combination.");
  const Root::TResult& rc = m_electronSF[combination]->calculate(config.isAFII ? PATCore::ParticleDataType::Fast : PATCore::ParticleDataType::Full, config.runNumber, eta, pt);

  return std::pair<double, double>(rc.getScaleFactor(), rc.getTotalUncertainty());
}



std::pair<double, double>
LeptonTriggerSF::ElEff_Data(const TLorentzVector& electron,
                            const int combinationSF,
                            const int combinationEfficiency,
                            const int year,
                            const TrigMuonEff::Configuration& config) const
{
  std::pair<double, double> sf = getElectronSF(electron, combinationSF, year, config);
  std::pair<double, double> mcEfficiency = getElectronSF(electron, combinationEfficiency, year, config);

  const double efficiency = sf.first * mcEfficiency.first;
  const double par1 = sf.second / sf.first;
  const double par2 = mcEfficiency.second / mcEfficiency.first;
  const double error = efficiency * sqrt(par1*par1 + par2*par2);

  return std::make_pair(efficiency, error);
}



void
LeptonTriggerSF::createMcReplicaMuon(const int n,
                                     const std::string& trigger)
{
  const bool filter = not trigger.empty();
  m_efficiencyMapReplicaArray.clear();

  // create n replica maps
  for (int ii = 0; ii < n; ii++) {
    EfficiencyMap map;
    for (EfficiencyMap::const_iterator cit = m_efficiencyMap.begin();
        cit != m_efficiencyMap.end();
        cit++) {
      const std::string& name = cit->first;
      TH2* th2 = cit->second;

      if (filter and (name.find(trigger) == std::string::npos)) continue;
      if (not th2) {
        ::Fatal("LeptonTriggerSF::createMcReplicaMuon",
                ERROR_MESSAGE("An internal coding error detected"));
        throw std::runtime_error("An internal coding error detected");
      }

      TH2* hcopy = dynamic_cast<TH2*>(th2->Clone());
      if (not hcopy) {
        ::Fatal("LeptonTriggerSF::createMcReplicaMuon",
                ERROR_MESSAGE("Couldn't make copy of histogram \"%s\""), name.c_str());
        throw std::runtime_error(("Couldn't make copy of histogram " + name ).c_str());
      }

      std::pair<EfficiencyMap::iterator, bool> rc = map.insert(EfficiencyPair(name, hcopy));
      if (not rc.second) {
        ::Fatal("LeptonTriggerSF::createMcReplicaMuon",
                ERROR_MESSAGE("histogram \"%s\" duplicated"), name.c_str());
        throw std::runtime_error(("histogram duplication: " + name).c_str());
      }
    }
    m_efficiencyMapReplicaArray.push_back(map);
  }


  // fill n replica maps
  for (EfficiencyMap::const_iterator cit = m_efficiencyMap.begin();
      cit != m_efficiencyMap.end();
      cit++) {

    const std::string& name = cit->first;
    TH2* th2 = cit->second;

    if (filter and (name.find(trigger) == std::string::npos)) continue;

    if (not th2) {
      ::Fatal("LeptonTriggerSF::createMcReplicaMuon",
              ERROR_MESSAGE("An internal coding error detected"));
      throw std::runtime_error("An internal coding error detected");
    }


    for (int ii = 1; ii <= th2->GetNbinsX(); ii++) {
      for (int jj = 1; jj <= th2->GetNbinsY(); jj++) {
        const double efficiency = th2->GetBinContent(ii, jj);
        const double statisticalError = th2->GetBinError(ii, jj);
        TRandom random = TRandom();

        for (int kk = 0; kk < n; kk++) {
          EfficiencyMap &map = m_efficiencyMapReplicaArray.at(kk);
          EfficiencyMap::const_iterator itr = map.find(name);
          if (itr == map.end()) {
            ::Fatal("LeptonTriggerSF::createMcReplicaMuon",
                    ERROR_MESSAGE("Could not find what you are looking for in the efficiency map. \"%s\" "
                                  "This is either a bug or you are not using the right .root file, please double check."),
                                  name.c_str());
            throw std::runtime_error("Internal coding error detected");
          }
          const double v = random.Gaus(efficiency, statisticalError);
          (itr->second)->SetBinContent(ii, jj, v);
        }
      }
    }
  }
}



std::pair<double, double>
LeptonTriggerSF::getSfReplicaMuon(const int runNumber,
                                  const bool useGeV,
                                  const std::vector<TLorentzVector>& muons,
                                  const std::vector<MuonQuality>& muonsQuality,
                                  const int index,
                                  TrigMuonEff::Configuration* config) const
{
  std::vector<TLorentzVector> electrons;
  std::vector<ElectronQuality> electronsQuality;

  TrigMuonEff::Configuration configuration;
  configuration.runNumber = runNumber;
  configuration.useGeV = useGeV;
  configuration.setByUser = false;
  configuration.replicaIndex = index;
  configuration.isAFII = m_IsAFII;

  if (config) {
    configuration.setByUser = true;
    configuration.trigger = config->trigger;
    configuration.period = config->period;
    configuration.binning = config->binning;
  }

  return GetTriggerSF(configuration, muons, muonsQuality, electrons, electronsQuality);
}



/*=================================================================* 
 * private methods
 *=================================================================*/
std::string
LeptonTriggerSF::getDirectory(const std::string& directory) const
{
  //
  // Try to find the correct directory to use:
  //
  std::string path = directory;
  if (path.empty()) { // default to InstallArea/share for the files if running in Athena
    const char *tmparea = gSystem->Getenv("TestArea");
    if (tmparea) {
      path = std::string(tmparea) + "/InstallArea/share/";
      ::Info("LeptonTriggerSF::getDirectory", "Using default directory: %s", path.c_str());

    } else {
      ::Warning("LeptonTriggerSF::getDirectory",
                "You are not running in Athena but also did not set a directory to the root file." );
    }

  } else {
    ::Info("LeptonTriggerSF::getDirectory", "Using user defined directory: %s", path.c_str());
  }

  return path;
}



void
LeptonTriggerSF::setStorage(Storage& storage) const
{
  //
  // Constants used in the file reading:
  //
  static const std::string type_[] = {"data", "mc"};
  static const std::vector<std::string> type(type_, type_ + sizeof(type_)/sizeof(std::string));

  static const std::string region_[]  = {"barrel", "endcap"};
  static const std::vector<std::string> region(region_, region_ + sizeof(region_)/sizeof(std::string));


  static std::vector<std::string> quality2011, quality2012;
  if ((not m_qualities.empty()) and (m_qualities.size() != 2)) {
    ::Fatal("LeptonTriggerSF::setStorage",
            ERROR_MESSAGE("If giving a muon qualities vector, it needs to be of size 2."));
    throw std::runtime_error("Muon qualities vector has wrong size ");

  } else if (m_qualities.size() == 2) {
    quality2011 = m_qualities;
    quality2012 = m_qualities;

  } else {
    // If multiple instances of the tool are initialized within the same
    // process, we have to be careful not to fill these vectors multiple
    // times:
    quality2011.clear();
    quality2012.clear();
    quality2011.push_back("loose");
    quality2011.push_back("combined");
    quality2012.push_back("loose");
    quality2012.push_back("combined");
  }


  // 2011
  static const std::string bins2011_[]    = {"fine", "coarse"};
  static const std::vector<std::string> bins2011(bins2011_, bins2011_ + sizeof(bins2011_)/sizeof(std::string));

  static const std::string trigger2011_[] = {"mu18_MG", "mu18_MG_medium", "mu18_MG_medium",
                                             "mu18_MG_medium", "mu18_MG_medium", "mu18_MG_medium", "mu18_MG_medium", "mu18_MG_medium"};
  static const std::vector<std::string> trigger2011(trigger2011_, trigger2011_ + sizeof(trigger2011_)/sizeof(std::string));

  static const std::string period2011_[] = {"BtoI", "JtoMwoL3toL4", "L3toL4",
                                            "J", "K", "JtoK", "JtoM", "LtoM"};
  static const std::vector<std::string> period2011(period2011_, period2011_ + sizeof(period2011_)/sizeof(std::string));


  // 2012
  static const std::string bins2012_[]    = {"fine", "coarse"};
  static const std::vector<std::string> bins2012(bins2012_, bins2012_ + sizeof(bins2012_)/sizeof(std::string));

  static const std::string trigger2012_[] = {"mu24i_tight_or_EF_mu36_tight", "mu24i_tight_or_EF_mu36_tight", "mu24i_tight_or_EF_mu36_tight", "mu24i_tight_or_EF_mu36_tight", "mu24i_tight_or_EF_mu36_tight",
                                             "mu24i_tight", "mu24i_tight", "mu24i_tight", "mu24i_tight", "mu24i_tight",
                                             "mu18_tight", "mu18_tight", "mu18_tight", "mu18_tight", "mu18_tight",
                                             "mu36_tight", "mu36_tight", "mu36_tight", "mu36_tight", "mu36_tight",
                                             "mu8_EFFS", "mu8_EFFS", "mu8_EFFS", "mu8_EFFS", "mu8_EFFS",
                                             "mu8", "mu8", "mu8", "mu8", "mu8",
                                             "mu13", "mu13", "mu13", "mu13", "mu13"};
  static const std::vector<std::string> trigger2012(trigger2012_, trigger2012_ + sizeof(trigger2012_)/sizeof(std::string));

  static const std::string period2012_[] = {"A", "B", "CtoE", "G", "HtoL",
                                            "A", "B", "CtoE", "G", "HtoL",
                                            "A", "B", "CtoE", "G", "HtoL",
                                            "A", "B", "CtoE", "G", "HtoL",
                                            "A", "B", "CtoE", "G", "HtoL",
                                            "A", "B", "CtoE", "G", "HtoL",
                                            "A", "B", "CtoE", "G", "HtoL"};
  static const std::vector<std::string> period2012(period2012_, period2012_ + sizeof(period2012_)/sizeof(std::string));


  storage.type = &type;
  storage.region = &region;
  switch (m_year) {
    case 2011:
      storage.trigger = &trigger2011;
      storage.period = &period2011;
      storage.quality = &quality2011;
      storage.bins = &bins2011;
      break;

    case 2012:
      storage.trigger = &trigger2012;
      storage.period = &period2012;
      storage.quality = &quality2012;
      storage.bins = &bins2012;
      break;

    default:
      ::Fatal("LeptonTriggerSF::setStorage",
              ERROR_MESSAGE("Unknown year: %d"), m_year);
      throw std::runtime_error("unknown year");
      break;
  }

  if (storage.period->size() != storage.trigger->size()) {
    ::Fatal("LeptonTriggerSF::setStorage",
            ERROR_MESSAGE("size of period and trigger is different: check configuration"));
    throw std::runtime_error("size of period and trigger is different: check configuration");
  }

  ::Info("LeptonTriggerSF::setStorage",
         "Year = %d, nperiods = %u", m_year, (unsigned int)storage.period->size());
  ::Info("LeptonTriggerSF::setStorage",
         "nquality = %u, nbins = %u, ntype = %u, nregion = %u",
         (unsigned int)storage.quality->size(), (unsigned int)storage.bins->size(), (unsigned int)storage.type->size(), (unsigned int)storage.region->size());

  return;
}



TDirectory*
LeptonTriggerSF::getTemporaryDirectory(void) const
{
  //
  // Create a unique directory in memory to hold the histograms:
  //
  gROOT->cd();
  TDirectory* tempDir = 0;
  int counter = 0;
  while (not tempDir) {
    // First, let's find a directory name that doesn't exist yet:
    std::stringstream dirname;
    dirname << "LeptonTriggerSFTempDir_%i" << counter;
    if (gROOT->GetDirectory((dirname.str()).c_str())) {
      ++counter;
      continue;
    }
    // Let's try to make this directory:
    tempDir = gROOT->mkdir((dirname.str()).c_str());
    if (not tempDir) {
      ::Fatal("LeptonTriggerSF::getTemporaryDirectory",
              ERROR_MESSAGE("Temporary directory could not be created"));
      throw std::runtime_error("Temporary directory could not be created");
    }
  }

  return tempDir;
}



void
LeptonTriggerSF::initialise(const std::string& directory,
                            const std::string& fileName,
                            const std::vector<std::string>& qualities,
                            const std::string& directoryElectron)
{
  m_fileNameMap.clear();
  m_fileNameMap[27] = directoryElectron + "/" + "efficiencySF.e20_medium.Loose.2011.7TeV." + m_electronFileVersion + ".root";
  m_fileNameMap[20] = directoryElectron + "/" + "efficiency.e20_medium.Loose.2011.7TeV." + m_electronFileVersion + ".root";
  m_fileNameMap[8] = directoryElectron + "/" + "efficiencySF.e20_medium.Medium.2011.7TeV." + m_electronFileVersion + ".root";
  m_fileNameMap[9] = directoryElectron + "/" + "efficiency.e20_medium.Medium.2011.7TeV." + m_electronFileVersion + ".root";
  m_fileNameMap[10] = directoryElectron + "/" + "efficiencySF.e20_medium.Tight.2011.7TeV." + m_electronFileVersion + ".root";
  m_fileNameMap[11] = directoryElectron + "/" + "efficiency.e20_medium.Tight.2011.7TeV." + m_electronFileVersion + ".root";
  m_fileNameMap[28] = directoryElectron + "/" + "efficiencySF.e22_medium1.Loose.2011.7TeV." + m_electronFileVersion + ".root";
  m_fileNameMap[21] = directoryElectron + "/" + "efficiency.e22_medium1.Loose.2011.7TeV." + m_electronFileVersion + ".root";
  m_fileNameMap[12] = directoryElectron + "/" + "efficiencySF.e22_medium.Medium.2011.7TeV." + m_electronFileVersion + ".root";
  m_fileNameMap[13] = directoryElectron + "/" + "efficiency.e22_medium.Medium.2011.7TeV." + m_electronFileVersion + ".root";
  m_fileNameMap[14] = directoryElectron + "/" + "efficiencySF.e22_medium.Tight.2011.7TeV." + m_electronFileVersion + ".root";
  m_fileNameMap[15] = directoryElectron + "/" + "efficiency.e22_medium.Tight.2011.7TeV." + m_electronFileVersion + ".root";
  m_fileNameMap[29] = directoryElectron + "/" + "efficiencySF.e22vh_medium1.Loose.2011.7TeV." + m_electronFileVersion + ".root";
  m_fileNameMap[22] = directoryElectron + "/" + "efficiency.e22vh_medium1.Loose.2011.7TeV." + m_electronFileVersion + ".root";
  m_fileNameMap[16] = directoryElectron + "/" + "efficiencySF.e22vh_medium1.Medium.2011.7TeV." + m_electronFileVersion + ".root";
  m_fileNameMap[17] = directoryElectron + "/" + "efficiency.e22vh_medium1.Medium.2011.7TeV." + m_electronFileVersion + ".root";
  m_fileNameMap[18] = directoryElectron + "/" + "efficiencySF.e22vh_medium1.Tight.2011.7TeV." + m_electronFileVersion + ".root";
  m_fileNameMap[19] = directoryElectron + "/" + "efficiency.e22vh_medium1.Tight.2011.7TeV." + m_electronFileVersion + ".root";
  m_fileNameMap[31] = directoryElectron + "/" + "efficiencySF.e24vhi_medium1_e60_medium1.Loose.2012.8TeV." + m_electronFileVersion + ".root";
  m_fileNameMap[32] = directoryElectron + "/" + "efficiency.e24vhi_medium1_e60_medium1.Loose.2012.8TeV." + m_electronFileVersion + ".root";
  m_fileNameMap[33] = directoryElectron + "/" + "efficiencySF.e24vhi_medium1_e60_medium1.Medium.2012.8TeV." + m_electronFileVersion + ".root";
  m_fileNameMap[34] = directoryElectron + "/" + "efficiency.e24vhi_medium1_e60_medium1.Medium.2012.8TeV." + m_electronFileVersion + ".root";
  m_fileNameMap[35] = directoryElectron + "/" + "efficiencySF.e24vhi_medium1_e60_medium1.Tight.2012.8TeV." + m_electronFileVersion + ".root";
  m_fileNameMap[36] = directoryElectron + "/" + "efficiency.e24vhi_medium1_e60_medium1.Tight.2012.8TeV." + m_electronFileVersion + ".root";
  m_fileNameMap[37] = directoryElectron + "/" + "efficiencySF.e24vhi_medium1_e60_medium1.Multilepton.2012.8TeV." + m_electronFileVersion + ".root";
  m_fileNameMap[38] = directoryElectron + "/" + "efficiency.e24vhi_medium1_e60_medium1.Multilepton.2012.8TeV." + m_electronFileVersion + ".root";

  m_electronSF.clear();

  m_max_period = TrigMuonEff::period_undefined;

  m_qualities = qualities;

  // Remember which TDirectory the system is in at the beginning of the method:
  TDirectory* origDir = gDirectory;

  // set parameters for reading a root file
  Storage storage;
  setStorage(storage);

  // Open the efficiency file:
  const std::string filePath = getDirectory(directory) + "/" + fileName;
  TFile* file = TFile::Open(filePath.c_str());

  if (not file) {
    ::Fatal("LeptonTriggerSF::initialise", ERROR_MESSAGE("Couldn't open file \"%s\""), filePath.c_str());
    throw std::runtime_error(("Couldn't open file \"" + filePath + "\". input root files are available at "
                              "https://twiki.cern.ch/twiki/bin/viewauth/Atlas/TrigMuonEfficiency "
                              "or in /afs/cern.ch/user/t/takashi/public/SF2012/").c_str());
  }

  ::Info("LeptonTriggerSF::initialise", "File \"%s\" opened", file->GetName());


  // Create a unique directory in memory to hold the histograms:
  TDirectory* tempDir = getTemporaryDirectory();
  tempDir->cd();


  //
  // Read in the histograms:
  //
  for (size_t iqu = 0; iqu < storage.quality->size(); ++iqu) {
    for (size_t ibins = 0; ibins < storage.bins->size(); ++ibins) {
      for (size_t iperiod = 0; iperiod < storage.period->size(); ++iperiod) {
        for (size_t iregion = 0; iregion < storage.region->size(); ++iregion) {
          for (size_t itype = 0; itype < storage.type->size(); ++itype) {

            // Construct the histogram name:
            std::string histname = ("_MuonTrigEff_" + storage.period->at(iperiod) + "_" +
                                    ((m_year > 2011) ? storage.trigger->at(iperiod) + "_" : "") +
                                    storage.quality->at(iqu) +
                                    "_EtaPhi_" +
                                    storage.bins->at(ibins) + "_" +
                                    storage.region->at(iregion) + "_" +
                                    storage.type->at(itype));
            // Try to access the histogram:
            std::string path = (storage.quality->at(iqu) + "/" +
                                storage.bins->at(ibins) + "/" +
                                storage.trigger->at(iperiod) + "_" + storage.period->at(iperiod) + "/" +
                                "etaphi_" + storage.region->at(iregion) + "_eff_" + storage.type->at(itype) + "_period" +
                                storage.period->at(iperiod) + "_EF_" + storage.trigger->at(iperiod));
            TH2* hist = dynamic_cast<TH2*>(file->Get(path.c_str()));
            if (not hist) {
              ::Warning("LeptonTriggerSF::initialise",
                        "%s not available in %s", path.c_str(), filePath.c_str());
              continue;
            }
            // Make a copy of the histogram into the in-memory directory:
            TH2* hcopy = dynamic_cast<TH2*>(hist->Clone());
            if (not hcopy) {
              ::Fatal("LeptonTriggerSF::initialise",
                      ERROR_MESSAGE("Couldn't make copy of histogram \"%s\""), histname.c_str());
              throw std::runtime_error(("Couldn't make copy of histogram " + histname ).c_str());
            }

            // Now, remember this histogram:
            // std::cout << "DEBUG: " << path << " = " << histname << "\n";
            std::pair<EfficiencyMap::iterator, bool> rc = m_efficiencyMap.insert(EfficiencyPair(histname, hcopy));
            if (not rc.second) {
              ::Fatal("LeptonTriggerSF::initialise",
                      ERROR_MESSAGE("histogram \"%s\" duplicated"), histname.c_str());
              throw std::runtime_error(("histogram duplication: " + histname).c_str());
            }
          }
        }
      }
    }
  }


  //
  // Set the phi boundaries:
  //
  if (m_year == 2011) {
    setPhiBoundary2011(storage.period);

  } else {
    setPhiBoundary(file);
  }

  // Now we can close the file:
  file->Close();
  delete file;

  // Return to the directory we were in before the function call:
  origDir->cd();

  ::Info("LeptonTriggerSF::initialise",
         "Initialization successful");

  return;
}




std::string
LeptonTriggerSF::getMuonQuality(const MuonQuality quality)
{
  std::string name;
  switch (quality) {
    case loose:
      name = "loose";
      break;

    case combined:
      name = "combined";
      break;

    default:
      ::Error("LeptonTriggerSF::getMuonQuality",
              ERROR_MESSAGE("Unknown muon quality (%i) received; Using loose muon as default"),
              quality );
      name = "loose";
   }

   return name;
}




int
LeptonTriggerSF::getElectronQuality(const int runNumber,
                                    const ElectronQuality quality,
                                    const bool isSF) const
{
  int combination = 0;

  if (runNumber <= 186755) { // e20_medium
    switch (quality) {
      case loosepp:
        combination = isSF ? 27 : 20;

        initialiseElectronTool(27);
        initialiseElectronTool(20);
        break;

      case mediumpp:
        combination = isSF ? 8 : 9;

        initialiseElectronTool(8);
        initialiseElectronTool(9);
        break;

      case tightpp:
        combination = isSF ? 10 : 11;

        initialiseElectronTool(10);
        initialiseElectronTool(11);
        break;

      default:
        ::Error("LeptonTriggerSF::getElectronQuality",
                ERROR_MESSAGE("Unknown electron quality (%i) received; Using loose++ electron as default" ),
                quality );
        combination = isSF ? 27 : 20;

        initialiseElectronTool(27);
        initialiseElectronTool(20);
    }
      
  } else if (runNumber <= 187815) { // e22_medium
    switch (quality) {
      case loosepp:
        combination = isSF ? 28 : 21;

        initialiseElectronTool(28);
        initialiseElectronTool(21);
        break;

      case mediumpp:
        combination = isSF ? 12 : 13;

        initialiseElectronTool(12);
        initialiseElectronTool(13);
        break;

      case tightpp:
        combination = isSF ? 14 : 15;

        initialiseElectronTool(14);
        initialiseElectronTool(15);
        break;

      default:
        ::Error("LeptonTriggerSF::getElectronQuality",
                ERROR_MESSAGE("Unknown electron quality (%i) received; Using loose++ electron as default" ),
                quality );
        combination = isSF ? 28 : 21;

        initialiseElectronTool(28);
        initialiseElectronTool(21);
    }

  } else if (runNumber <= 191933 ) { // e22vh_medium1
    switch (quality) {
      case loosepp:
        combination = isSF ? 29 : 22;

        initialiseElectronTool(29);
        initialiseElectronTool(22);
        break;

      case mediumpp:
        combination = isSF ? 16 : 17;

        initialiseElectronTool(16);
        initialiseElectronTool(17);
        break;

      case tightpp:
        combination = isSF ? 18 : 19;

        initialiseElectronTool(18);
        initialiseElectronTool(19);
        break;

      default:
        ::Error("LeptonTriggerSF::getElectronQuality",
                ERROR_MESSAGE("Unknown electron quality (%i) received; Using loose++ electron as default" ),
                quality );
        combination = isSF ? 29 : 22;

        initialiseElectronTool(29);
        initialiseElectronTool(22);
    }

  } else if (runNumber <=  9999999) { // e24vhi_medium1 || e60_medium1
    switch (quality) {
      case loosepp:
        combination = isSF ? 31 : 32;

        initialiseElectronTool(31);
        initialiseElectronTool(32);
        break;

      case mediumpp:
        combination = isSF ? 33 : 34;

        initialiseElectronTool(33);
        initialiseElectronTool(34);
        break;

      case tightpp:
        combination = isSF ? 35 : 36;

        initialiseElectronTool(35);
        initialiseElectronTool(36);
        break;

      case ML:
        combination = isSF ? 37 : 38;

        initialiseElectronTool(37);
        initialiseElectronTool(38);
        break;

      default:
        ::Error("LeptonTriggerSF::getElectronQuality",
                ERROR_MESSAGE("Unknown electron quality (%i) received; Using loose++ electron as default" ),
                quality );
        combination = isSF ? 31 : 32;

        initialiseElectronTool(31);
        initialiseElectronTool(32);
    }

  } else {
    ::Error("LeptonTriggerSF::getElectronQuality",
            ERROR_MESSAGE( "Bad run number (%i) received" ), runNumber);
  }

  return combination;
}




std::pair<double, double>
LeptonTriggerSF::getThresholds(const TrigMuonEff::Configuration& config)
{
  std::pair<double, double> result(20., 21.);  // (muon, electron)

  if (config.runNumber <= 186755) {
    result.second = 21.;

  } else if (config.runNumber <= 191933) {
    result.second = 23.;

  } else if ((200804 <= config.runNumber) and (config.runNumber <= 9999999)) {
    result.first = 25.;  // muon
    result.second = 25.; // electron

  } else {
    ::Error("LeptonTriggerSF::getThresholds",
            ERROR_MESSAGE( "Unknown run number (%i) received" ), config.runNumber);
    return result;
  }

  if (not config.useGeV ) {
    result.first  *= GeVtoMeV;
    result.second *= GeVtoMeV;
  }

  return result;
}



void
LeptonTriggerSF::getDimuonThresholds(const TrigMuonEff::Configuration& config,
                                     DimuonThresholds& thresholds)
{
  thresholds.mu18_tight = 20;
  thresholds.mu8_EFFS = 10;
  thresholds.mu13 = 15;

  if (not config.useGeV) {
    thresholds.mu18_tight *= GeVtoMeV;
    thresholds.mu8_EFFS *= GeVtoMeV;
    thresholds.mu13 *= GeVtoMeV;
  }
}



TrigMuonEff::DataPeriod
LeptonTriggerSF::getDataPeriod(int runNumber)
{
  if (runNumber < 178044) return TrigMuonEff::period_undefined;
  if (runNumber <= 186493) return TrigMuonEff::period_2011_BtoI;
  if ((runNumber <= 189090) or
      (runNumber >= 189639 and runNumber <= 191933)) return TrigMuonEff::period_2011_JtoMwithoutL3L4;
  if ((runNumber >= 189184) and (runNumber <= 189610)) return TrigMuonEff::period_2011_L3toL4;
  if ((runNumber >= 200804) and (runNumber <= 201556)) return TrigMuonEff::period_2012_A;
  if ((runNumber >= 202660) and (runNumber <= 205113)) return TrigMuonEff::period_2012_B;
  if ((runNumber >= 206248) and (runNumber <= 210308)) return TrigMuonEff::period_2012_CtoE;
  if ((runNumber >= 211522) and (runNumber <= 212272)) return TrigMuonEff::period_2012_G;
  if ((runNumber >= 212619) and (runNumber <= 215643)) return TrigMuonEff::period_2012_HtoL;

  ::Error("LeptonTriggerSF::getDataPeriod",
          ERROR_MESSAGE( "Can't associate run number (%i) to a period" ), runNumber);
  return TrigMuonEff::period_undefined;
}



double
LeptonTriggerSF::getSfError(const double a,
                            const double b,
                            const double c,
                            const double d)
{
  const double a2 = a*a;
  const double b2 = b*b;
  const double p1 = (1 - a);
  const double p2 = (1 - b);
  const double p12 = p1*p1;
  const double p22 = p2*p2;
  const double p24 = p22*p22;

  return sqrt( ( a2 / p22 ) * c + ( ( b2 * p12 ) / p24 ) * d );
}



void
LeptonTriggerSF::getDimuonLegs(const std::string& chain,
                               DimuonTrigger& dimuon)
{

  if (chain.find("mu18_tight_mu8_EFFS") != std::string::npos) {
    dimuon.leg1 = "mu18_tight";
    dimuon.leg2 = "mu8_EFFS";
    dimuon.bothLegs = "mu18_tight"; // for now, eventually should be mu18i_tight_or_mu8_EFFS

  } else if (chain.find("2mu13") != std::string::npos) {
    dimuon.leg1 = "mu13";
    dimuon.leg2 = "mu13";
    dimuon.bothLegs = "mu13";

  } else {
    dimuon.leg1 = "";
    dimuon.leg2 = "";
    dimuon.bothLegs = "";
    ::Error( "LeptonTriggerSF::getDimuonLegs",
      ERROR_MESSAGE("Invalid dimuon or combination of single and dimuon trigger chain name given"));
  }
}



bool
LeptonTriggerSF::setConfiguration(TrigMuonEff::Configuration& config,
                                  TrigMuonEff::DataPeriod period) const
{
  if (period == TrigMuonEff::period_undefined) {
    period = getDataPeriod(config.runNumber);
    if (m_max_period != TrigMuonEff::period_undefined) {
      if (period > m_max_period) {
        static bool hasWarned = false;
        if (not hasWarned) {
          ::Warning("LeptonTriggerSF::period out of range:", "setting it to %d", period);
          hasWarned = true;
        }
        period = m_max_period;
      }
    }

    if (period == TrigMuonEff::period_undefined) {
      ::Error( "LeptonTriggerSF::setConfiguration",
      ERROR_MESSAGE("RunNumber is not in 2011 or 2012 dataset. No scale factors calculated. "
                    "Please use RunNumber between 178044-191933 for 2011 data, or "
                    "above 200804 (upper run number limit removed for now) for 2012 data. %d" ), config.runNumber );
      return false;
    }
  }

  switch (period) {
    case TrigMuonEff::period_2011_BtoI:
      config.period = "BtoI_";
      config.binning = "fine";
      break;

    case TrigMuonEff::period_2011_JtoMwithoutL3L4:
      config.period = "JtoMwoL3toL4_";
      config.binning = "fine";
      break;

    case TrigMuonEff::period_2011_L3toL4:
      config.period = "L3toL4_";
      config.binning = "coarse";
      break;

    case TrigMuonEff::per2012A:
      config.period = "A_";
      config.binning = "fine";
      config.trigger = "mu24i_tight_or_EF_mu36_tight";
      break;

    case TrigMuonEff::per2012B:
      config.period = "B_";
      config.binning = "fine";
      config.trigger = "mu24i_tight_or_EF_mu36_tight";
      break;

    case TrigMuonEff::per2012CtoE:
      config.period = "CtoE_";
      config.binning = "fine";
      config.trigger = "mu24i_tight_or_EF_mu36_tight";
      break;

    case TrigMuonEff::per2012G:
      config.period = "G_";
      config.binning = "fine";
      config.trigger = "mu24i_tight_or_EF_mu36_tight";
      break;

    case TrigMuonEff::per2012HtoL:
      config.period = "HtoL_";
      config.binning = "fine";
      config.trigger = "mu24i_tight_or_EF_mu36_tight";
      break;

    // speical cases
    case TrigMuonEff::per2011J:
      config.period = "J_";
      config.binning = "coarse";
      break;

    case TrigMuonEff::per2011K:
      config.period = "K_";
      config.binning = "coarse";
      break;

   case TrigMuonEff::per2011J_K:
      config.period = "JtoK_";
      config.binning = "coarse";
      break;

   case TrigMuonEff::per2011J_M:
      config.period = "JtoM_";
      config.binning = "coarse";
      break;

   case TrigMuonEff::per2011L_M:
      config.period = "LtoM_";
      config.binning = "coarse";
      break;

    default:
      ::Error("LeptonTriggerSF::setConfiguration",
      ERROR_MESSAGE("Unknown data period (%i) requested"), period);
      return false;
   }

   return true;
}



void
LeptonTriggerSF::setPhiBoundary2011(const std::vector<std::string> *period)
{
  m_phiBoundaryBarrel = M_PI;
  m_phiBoundaryEndcap = M_PI;

  EfficiencyMap::const_iterator itr = m_efficiencyMap.begin();
  EfficiencyMap::const_iterator end = m_efficiencyMap.end();

  for (; itr != end; ++itr) {
    if (not itr->second) {
      ::Fatal("LeptonTriggerSF::setPhiBoundary2011",
              ERROR_MESSAGE("An internal coding error detected"));
      throw std::runtime_error("An internal coding error detected");
    }

    // setting lower phi to account for unusual binning
    std::string string = "_MuonTrigEff_" + period->at(0) + "_loose_EtaPhi_fine_barrel_data";
    if (itr->first.find( string ) != std::string::npos) {
      m_phiBoundaryBarrel = itr->second->GetYaxis()->GetXmin();
    } 
    string = "_MuonTrigEff_" + period->at(0) + "_loose_EtaPhi_fine_endcap_data";
    if (itr->first.find(string) != std::string::npos) {
      m_phiBoundaryEndcap = itr->second->GetYaxis()->GetXmin();
    }
    if (m_phiBoundaryBarrel < -M_PI) m_phiBoundaryBarrel += 2. * M_PI;
    if (m_phiBoundaryEndcap < -M_PI) m_phiBoundaryEndcap += 2. * M_PI;
 }

 return;

}



void
LeptonTriggerSF::setPhiBoundary(TFile* file)
{
  gROOT->cd();

  m_phiBoundaryBarrel = M_PI;
  m_phiBoundaryEndcap = M_PI;

  TH2* hist = 0;

  const char* barrel = "binning_barrel";
  hist = dynamic_cast< TH2* >(file->Get(barrel));
  if (not hist) {
    ::Warning("LeptonTriggerSF::setPhiBoundary", "%s not available", barrel);

  } else {
    m_phiBoundaryBarrel = hist->GetYaxis()->GetXmin();
  }

  const char* endcap = "binning_endcap";
  hist = dynamic_cast< TH2* >(file->Get(endcap));
  if (not hist) {
    ::Warning("LeptonTriggerSF::setPhiBoundary", "%s not available", endcap);

  } else {
    m_phiBoundaryEndcap = hist->GetYaxis()->GetXmin();
  }


  if (m_phiBoundaryBarrel < -M_PI) m_phiBoundaryBarrel += 2. * M_PI;
  if (m_phiBoundaryEndcap < -M_PI) m_phiBoundaryEndcap += 2. * M_PI;

  return;
}



double
LeptonTriggerSF::fixPhiRange(const TLorentzVector& muon) const
{
  double phi = muon.Phi();

  if (phi > M_PI) {
    ::Warning("LeptonTriggerSF::fixPhiRange",
              "Muon phi %4.2f > pi! Using (phi-2*pi)", phi);
    phi -= 2 * M_PI;

  } else if (phi < -M_PI) {
    ::Warning("LeptonTriggerSF::fixPhiRange",
              "Muon phi %4.2f < -pi! Using (phi+2*pi)", phi);
    phi += 2 * M_PI;
  }


  if (fabs(muon.Eta()) < muon_barrel_endcap_boundary) {  // barrel
    if (m_phiBoundaryBarrel < 0.) {
      if (phi < m_phiBoundaryBarrel) {
        phi += 2 * M_PI;
      }
    } else {
      if (phi >= m_phiBoundaryBarrel) {
        phi -= 2 * M_PI;
      }
    }
  } else {  // endcap
    if (m_phiBoundaryEndcap < 0.) {
      if (phi < m_phiBoundaryEndcap) {
        phi += 2 * M_PI;
      }
    } else {
      if (phi >= m_phiBoundaryEndcap ) {
        phi -= 2 * M_PI;
      }
    }
  }

  return phi;
}



void
LeptonTriggerSF::initialiseElectronTool(const int key) const
{
  if (m_electronSF.find(key) == m_electronSF.end()) {
    Root::TElectronEfficiencyCorrectionTool *tool = new Root::TElectronEfficiencyCorrectionTool;
    if (m_fileNameMap.find(key) == m_fileNameMap.end()) throw std::runtime_error("initialiseElectronTool: key error");
    tool->addFileName(m_fileNameMap[key]);
    tool->initialize();
    m_electronSF.insert(ElectronEfficiencyToolPair(key, tool));
  }
}
// eof

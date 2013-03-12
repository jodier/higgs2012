//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 31.10.2011, MCP working group
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifndef AnalysisMuonConfigurableScaleFactorsH
#define AnalysisMuonConfigurableScaleFactorsH

//////////////////////////////////
// CLASS AnalysisMuonConfigurableScaleFactors //
//////////////////////////////////

/// \class AnalysisMuonConfigurableScaleFactors
///
/// This class provides efficiency scale factors and their uncertainties
/// for physics analyses using the Soft Muon Tagger.
///
/// For release 17 data analysis with MC11a and MC11b.
///
/// \date 30.03.2012
/// \author Marco.Vanadia@CERN.CH

//////////////////
// HEADER FILES //
//////////////////

// ROOT //
#include "TLorentzVector.h"
#include "TString.h"
#include "TRandom3.h"

// STL //
#include <vector>
#include <string>
#include <map>
#include <utility>
#include <math.h>

// Base class //
#include "MuonEfficiencyScaleFactor.h"
#include "MuonEfficiencyCorrections/EtaPhiBinning.h"

namespace Analysis {

class AnalysisMuonConfigurableScaleFactors : public MuonEfficiencyScaleFactor {

public:

    enum Configuration{
      Default,
      PerPeriod,
      PerRun,
      AverageOverPeriods,
      AverageOverRuns
    };
    //! Constructor
    AnalysisMuonConfigurableScaleFactors(void);
    ///< Default constructor.
    ///< Please do not use the default constructor!

    AnalysisMuonConfigurableScaleFactors(std::string directory,
					 std::string file,
					 const std::string & unit="MeV",     				     
					 Configuration conf=Default);
    ///< Constructor.
    ///< \param unit MeV if muon momenta are provided in MeV,
    ///<             GeV if muon momenta are provided in GeV.
    ///< \param dir Directory containing the scale factors.

    /// configuration=Default no binning in time
    /// =PerPeriod
    /// =PerRun
    /// =AverageOverPeriods
    /// =AverageOverRuns
    void Initialise();


    virtual ~AnalysisMuonConfigurableScaleFactors(){};

    // Methods //
    double scaleFactor(int charge, const TLorentzVector & tlv) const;
    double dataEff(int charge, const TLorentzVector & tlv) const;
    double scaleFactor(const TLorentzVector & tlv) const
    {
      return this->scaleFactor(0, tlv);
    };
    double dataEff(const TLorentzVector & tlv) const
    {
      return this->dataEff(0, tlv);
    };
    double scaleFactor(int charge, const TLorentzVector & tlv, std::string period) const;
    double dataEff(int charge, const TLorentzVector & tlv, std::string period) const;
    double scaleFactor(const TLorentzVector & tlv, std::string period) const
    {
      return this->scaleFactor(0,tlv,period);
    };
    double dataEff(const TLorentzVector & tlv, std::string period) const
    {
      return this->dataEff(0,tlv,period);
    };
    double scaleFactor(int charge, const TLorentzVector & tlv, int runnumber) const;
    double dataEff(int charge, const TLorentzVector & tlv, int runnumber) const;
    double scaleFactor(const TLorentzVector & tlv, int runnumber) const
    {
      return this->scaleFactor(0,tlv,runnumber);
    }
    double dataEffFactor(const TLorentzVector & tlv, int runnumber) const
    {
      return this->dataEff(0,tlv,runnumber);
    }

    double scaleFactorUncertainty(int charge, const TLorentzVector & tlv) const;
    double dataEffUncertainty(int charge, const TLorentzVector & tlv) const;
    double scaleFactorUncertainty(const TLorentzVector & tlv) const
    {
      return this->scaleFactorUncertainty(0, tlv);
    };
    double dataEffUncertainty(const TLorentzVector & tlv) const
    {
      return this->dataEffUncertainty(0, tlv);
    };
    double scaleFactorUncertainty(int charge, const TLorentzVector & tlv, std::string period) const;
    double dataEffUncertainty(int charge, const TLorentzVector & tlv, std::string period) const;
    double scaleFactorUncertainty(const TLorentzVector & tlv, std::string period) const
    {
      return scaleFactorUncertainty(0,tlv,period);
    };
    double dataEffUncertainty(const TLorentzVector & tlv, std::string period) const
    {
      return dataEffUncertainty(0,tlv,period);
    };
    double scaleFactorUncertainty(int charge, const TLorentzVector & tlv, int runnumber) const;
    double dataEffUncertainty(int charge, const TLorentzVector & tlv, int runnumber) const;
    double scaleFactorUncertainty(const TLorentzVector & tlv, int runnumber) const
    {
      return this->scaleFactorUncertainty(0,tlv,runnumber);
    };
    double dataEffUncertainty(const TLorentzVector & tlv, int runnumber) const
    {
      return this->dataEffUncertainty(0,tlv,runnumber);
    };
    double scaleFactorSystematicUncertainty(int charge, const TLorentzVector & tlv) const;
    double dataEffSystematicUncertainty(int charge, const TLorentzVector & tlv) const;
    double scaleFactorSystematicUncertainty(const TLorentzVector & tlv) const
    {
      return this->scaleFactorSystematicUncertainty(0, tlv);
    };
    double dataEffSystematicUncertainty(const TLorentzVector & tlv) const
    {
      return this->dataEffSystematicUncertainty(0, tlv);
    };
    double scaleFactorSystematicUncertainty(int charge, const TLorentzVector & tlv, std::string period) const;
    double dataEffSystematicUncertainty(int charge, const TLorentzVector & tlv, std::string period) const;
    double scaleFactorSystematicUncertainty(const TLorentzVector & tlv, std::string period) const
    {
      return this->scaleFactorSystematicUncertainty(0,tlv,period);
    };
    double dataEffSystematicUncertainty(const TLorentzVector & tlv, std::string period) const
    {
      return this->dataEffSystematicUncertainty(0,tlv,period);
    };
    double scaleFactorSystematicUncertainty(int charge, const TLorentzVector & tlv, int runnumber) const;
    double dataEffSystematicUncertainty(int charge, const TLorentzVector & tlv, int runnumber) const;
    double scaleFactorSystematicUncertainty(const TLorentzVector & tlv, int runnumber) const
    {
      return this->scaleFactorSystematicUncertainty(0,tlv,runnumber);
    };
    double dataEffSystematicUncertainty(const TLorentzVector & tlv, int runnumber) const
    {
      return this->dataEffSystematicUncertainty(0,tlv,runnumber);
    };

    void addPeriod(TString period, double lumi);
    void addRun(int runnumber, double lumi);
    void setRunInterval(int run_min, int run_max){
      m_run_min=run_min;
      m_run_max=run_max;
    };

   //function to generate a replica of SFs to treat statistical error
    void generateReplicas(int nreplica, int seed=9876);

    double scaleFactorReplica(int charge, const TLorentzVector & tlv, int nr) const;
    double scaleFactorReplica(const TLorentzVector & tlv, int nr) const
    {
      return this->scaleFactorReplica(0,tlv,nr);
    };
    double scaleFactorReplica(int charge,const TLorentzVector & tlv, std::string period, int nr) const;
    double scaleFactorReplica(const TLorentzVector & tlv, std::string period, int nr) const
    {
      return this->scaleFactorReplica(0,tlv,period,nr);
    };
    double scaleFactorReplica(int charge, const TLorentzVector & tlv, int runnumber, int nr) const;
    double scaleFactorReplica(const TLorentzVector & tlv, int runnumber, int nr) const
    {
      return this->scaleFactorReplica(0,tlv,runnumber,nr);
    };

    double dataEffReplica(int charge, const TLorentzVector & tlv, int nr) const;
    double dataEffReplica(const TLorentzVector & tlv, int nr) const
    {
      return this->dataEffReplica(0,tlv,nr);
    };
    double dataEffReplica(int charge,const TLorentzVector & tlv, std::string period, int nr) const;
    double dataEffReplica(const TLorentzVector & tlv, std::string period, int nr) const
    {
      return this->dataEffReplica(0,tlv,period,nr);
    };
    double dataEffReplica(int charge, const TLorentzVector & tlv, int runnumber, int nr) const;
    double dataEffReplica(const TLorentzVector & tlv, int runnumber, int nr) const
    {
      return this->dataEffReplica(0,tlv,runnumber,nr);
    };
   

private:
// unit //
    double m_unit; // m_unit = 1 for GeV, 0.001 for MeV

// pt-eta-phi map of the efficiency scale factors //
    std::vector<std::vector<int> > m_region;
    std::vector<std::vector<int> > m_charge;
    std::vector<std::vector<double> > m_pt_min, m_pt_max; // bin boundaries in pt
    std::vector<std::vector<double> > m_eta_min, m_eta_max; // bin boundaries in pt
    std::vector<std::vector<double> > m_phi_min, m_phi_max; // bin boundaries in pt
    std::vector<std::vector<double> > m_sf; // scale factors
    std::vector<std::vector<double> > m_sf_stat_err; // statistical errors of the scale
                                       // factors
    std::vector<std::vector<double> > m_sf_syst_err; // systematic errors of the scale 
                                       // factors

    std::vector<std::vector<double> > m_effdata; // scale factors
    std::vector<std::vector<double> > m_effdata_stat_err; // statistical errors of the scale
                                       // factors
    std::vector<std::vector<double> > m_effdata_syst_err; // systematic errors of the scale 
                                       // factors
    std::vector<TString> m_period; //
    std::vector<int> m_run; //
    std::map<TString, double> m_period_lumi;
    std::map<int, double> m_run_lumi;
    int m_run_min;
    int m_run_max;
    double m_EnergyDependentSystematic;
    bool m_UseChargeDependentSF;
    bool m_FileWithEffi;

    Configuration m_configuration;
    bool m_usingDefaultLumi;

    int m_nreplica;
    std::vector< std::vector< std::vector <double> > > m_sf_replica, m_effdata_replica ;

    void InitialiseAverageOverPeriods();
    void InitialiseAverageOverRuns();

    void init(std::string directory,
	      std::string file,
	      const std::string & unit="MeV",	      				     
	      Configuration conf=Default);

    void read_file(
		   Configuration conf,
		   const std::string & name,
                   std::vector<std::vector<int> >& region,
                   std::vector<std::vector<double> >& eta_min,
                   std::vector<std::vector<double> >& eta_max,
                   std::vector<std::vector<double> >& phi_min,
                   std::vector<std::vector<double> >& phi_max,
                   std::vector<std::vector<double> >& pt_min,
                   std::vector<std::vector<double> >& pt_max,
		   std::vector<std::vector<int> >& charge,
                   std::vector<std::vector<double> >& sf,
                   std::vector<std::vector<double> >& sf_stat_err,
                   std::vector<std::vector<double> >& sf_syst_err,
                   std::vector<std::vector<double> >& effdata,
                   std::vector<std::vector<double> >& effdata_stat_err,
                   std::vector<std::vector<double> >& effdata_syst_err,
		   std::vector<TString> &period,
		   std::vector<int> &run,
		   std::map<TString, double> &period_lumi,
		   std::map<int, double> &run_lumi,
		   double &EnergyDependentSystematic,
		   bool &UseChargeDependentSF,
		   bool &FileWithEffi
		   ) const;

    std::pair<int,int> get_pt_eta_phi_bin_index(int charge,const TLorentzVector & tlv, TString period="", int runnumber=0) const;
    EtaPhiBinning m_EPbin;
 };


}

#endif

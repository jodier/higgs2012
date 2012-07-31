//////////////////////////////////////////////////////////////
//
// REWRITE - May 2012, Maarten Boonekamp
//
///////////////////////////////////////////////////////////
#ifndef EnergyRescalerUpgrade_h
#define EnergyRescalerUpgrade_h

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <cctype>


#include <TRandom3.h>
#include <TFile.h>
#include <TGraphErrors.h>
#include <TH1D.h>
#include <TF1.h>


namespace egRescaler {

  // Taken from CLHEP/Units/SystemOfUnits.h
  static const double GeV = 1.e+3;
  
  
  class EnergyRescalerUpgrade {
    
  public:
    
    EnergyRescalerUpgrade();
    EnergyRescalerUpgrade(std::string filename, std::string year, std::string esmodel);
    virtual ~EnergyRescalerUpgrade();
    
    void Init(std::string filename, std::string year, std::string esmodel);

    // Resolution error variations    

    typedef enum { NOMINAL=0, ERR_DOWN=1, ERR_UP=2 } CorrType;
    
    // Scale error variations    

    enum Variation { 
      
      // central value
      Nominal, 
      
      // Zee scale uncertainty variations
      ZeeStatUp, ZeeStatDown, ZeeGenUp, ZeeGenDown, ZeeMethodUp, ZeeMethodDown,
      
      // PS and Material uncertainty variations
      PSStatUp, PSStatDown, R12StatUp, R12StatDown, B12Up, B12Down,
      
      // Low-pt
      LowPtUp, LowPtDown,

      // All
      AllUp, AllDown, AllUpApprox, AllDownApprox

    };
    
    
    enum ParticleType {
      
      Electron, 
      Unconverted, 
      Converted
      
    };
    
    
    // take eta and uncorrected energy of electron, return  corrected energy, 
    // apply given variation, for given particle type
    // Note : energies in MeV
    
    double applyEnergyCorrection( double cl_eta, double energy, ParticleType ptype=Electron, Variation var=Nominal, double varSF=1. );
    double applyEnergyCorrection( double cl_eta, ParticleType ptype=Electron, Variation var=Nominal, double varSF=1. );
    
    double getCorrectionError( double cl_eta, double energy, ParticleType ptype=Electron, Variation var=Nominal, double varSF=1. );

    ///set random seed to some fix value(would need for MC comparison )
    
    void SetRandomSeed( unsigned seed=0 );
    
    
    /// smearing corrections
    // Note : energies in MeV
    
    double getSmearingCorrection( double eta, double energy, int value=NOMINAL, bool mc_withCT=false ) ;
    
    /// MC calibration corrections
    
    double applyAFtoG4(double eta);
    
    // functions for resolution uncertainty evaluation
    
    double mcSamplingTerm(double cl_eta);
    double mcSamplingTermRelError( double cl_eta );
    double mcNoiseTerm( double cl_eta );
    double mcConstantTerm( double cl_eta );

    double dataConstantTerm( double cl_eta );
    double dataConstantTermError( double cl_eta );
    double dataConstantTermUpError( double cl_eta );
    double dataConstantTermDownError( double cl_eta );

    double dataZPeakResolution( double cl_eta );
    double mcZPeakResolution( double cl_eta );
    double dataConstantTermCorError( double cl_eta ); 
    double fcn_sigma(double energy, double Cdata, double Cdata_er, double S, double S_er);
    void   resolutionError( double energy, double cl_eta, double& errUp, double& errDown );
    double resolution( double energy, double cl_eta, bool withCT );
    
    // functions for energy scale corrections
    
    double getAlphaZee(double cl_eta, Variation var, double varSF=1. );
    
    double getAlphaLowPt(double transverseEnergy, Variation var, double varSF=1. );
    
    double getAlphaPS(double cl_eta, Variation var, double varSF=1. );
    double getPSNonLinearity(double cl_eta, double energy, ParticleType ptype);
    
    double getR12(double cl_eta, Variation var, double varSF=1. );
    double getAlphaMaterial(double cl_eta, ParticleType ptype);
    double getMaterialNonLinearity(double cl_eta, double energy, ParticleType ptype);
    
    
    
    
  private:
    
    mutable TRandom3   m_random3;
    
    TFile* m_erFile;
    TH1D *m_zeeNom, *m_zeeModel, *m_zeeMethod;
    TH1D *m_psNom, *m_psB12;
    TH1D *m_r12Nom, *m_r12B12;
    
    TH1D*         m_psElectronEtaBins;
    TList*        m_psElectronGraphs;
    TH1D*         m_psUnconvertedEtaBins;
    TList*        m_psUnconvertedGraphs;
    TH1D*         m_psConvertedEtaBins;
    TList*        m_psConvertedGraphs;
    
    TGraphErrors* m_matElectronScale;
    TGraphErrors* m_matUnconvertedScale;
    TGraphErrors* m_matConvertedScale;
    
    TH1D*         m_matElectronEtaBins;
    TList*        m_matElectronGraphs;
    
    bool m_initialized;
    bool m_debug;
    
    
#ifdef ROOTCORE
    ClassDef(EnergyRescalerUpgrade,1)
#endif
      
  };


} // end of namespace
#endif


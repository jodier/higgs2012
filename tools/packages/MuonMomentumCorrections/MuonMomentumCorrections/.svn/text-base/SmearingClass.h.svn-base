////////////////////////////////////////////////////////////////////////////
//           SmearingClass.h -- ATLAS Experiment Software                 //
////////////////////////////////////////////////////////////////////////////
///
/// class providing corrections to the simulated muon pT to match pT in data.
/// Resolution smearing and scale shift numbers are preliminary
/// 
/// responsible: atlas-perf-muons-conveners (at) cern.ch
///
#ifndef MuonMomentumCorrections_SmearingClass_H
#define MuonMomentumCorrections_SmearingClass_H

#include <cstring>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <TROOT.h>
#include <math.h>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <TRandom3.h>
#include <TLorentzVector.h>

namespace MuonSmear{

  /** Smearing and scaling types (enums are used for faster access) */
  typedef enum {
    SMEAR_PT=1,
    SMEAR_QPT=2
  } SMEARTYPE;
  typedef enum {
    SCALE_DEFAULT=1,
    SCALE_KPKM=2,
    SCALE_KC=3,
    SCALE_K=4,
    SCALE_C=5
  } SCALETYPE;
  typedef enum{
    DET_MS=1,
    DET_ID=2,
    DET_CB=3
  } DETTYPE;
  typedef enum{
    ID_UP=1,
    ID_LOW=2,
    MS_UP=3,
    MS_LOW=4,
    SCALE_UP=5,
    SCALE_LOW=6
  } SYSTTYPE;
  typedef enum{
    DATA10=1,
    DATA11=2,
    DATA12=3
  } DATATYPE;
  typedef enum{
    MUID=1,
    STACO=2,
    MUONS=3
  } ALGOTYPE;
  typedef enum{
    REL16_6=1,
    REL17=2,
    REL17_2=3,
    REL17_2_REPRO=4
  } RELTYPE;
  
  /** Smearing Class */
  class SmearingClass{
  
  public:
    /*Constructors*/
    SmearingClass();
    SmearingClass(std::string Data, std::string Algo="muid", 
		  std::string SmearType="q_pT",
		  std::string Rel="Rel16.6", std::string Dir="");
    SmearingClass(const SmearingClass&);
    virtual ~SmearingClass();
  
    /*************/
    /*  Methods  */   
    /*************/
      
    /** configure smearing **/
    void SetSeed(int);
    void SetSeed(int, int, int offset=680049);
    void UseTan2(bool);
    void UseGeV();
    void UseScale(bool);
    void RestrictCurvatureCorrections(double nsigma=2.5);
    void UseImprovedCombine();
    void ApplyToData(bool U=true);
    void SetAlgoSmearRelDir(std::string, std::string, std::string SmearType="q_pT", 
			    std::string Rel="Rel16.6", std::string Dir="");
    void SetRegions();
    void FillValues();
    void FillScales(std::string Scaletype="KC", bool ApplyToData=false);
    void PrintValues();
  
    void Event(const TLorentzVector & p, std::string DetType, double Charge=0);
    /* Pt      -> Momentum of the muon in the given detector part.
       DetType -> Detector type: ID = inner detector.
	                         MS = muon spectrometer.
       Charge  -> Charge of the muon.
       Eta     -> Eta of the muon
       Phi     -> Phi of the muon
    */
    void Event(double Pt, double Eta, std::string DetType, double Charge=0,
               double Phi=0);

    void Event(const TLorentzVector & p_MS,
               const TLorentzVector & p_ID,
               const TLorentzVector & p_CB,
               double Charge=0);
    ///< \param p_MS    Stand-alone muon momentum, i.e MS momentum corrected
    ///<                for the energy loss in the calorimeters.
    ///< \param p_ID    Inner detector momentum.
    ///< \param p_CB    Combined muon momentum.
    ///< \param Charge  Charge of the muon.
    void Event(double PtMS, double PtID, double PtCB, double Eta,
               double Charge=0, double Phi=0);
    
    void Event();
  
    double Smearing(int);
    double SmearingSYSVar(int, double var);
    double ICombine(double, double);
    double Combine(double, double);
    double Combine2(double, double);
    double ExpectedResolution(std::string DetType, bool mc=false) const; //!< Expected resolution in data (or unsmeard MC if second argument is true)
    double ExpectedResolution(int DetType, bool mc=false) const; //!< Expected resolution in data (or unsmeard MC if second argument is true)
    void ErrorMatrix();
    
    double ScaleApply(double pt, double S1, double S2, double S=1.0) const;
    double ScaleMS(double pt) const;
    double ScaleID(double pt) const;
    double ScaleCB(double pt) const;

    double pTMS();
    double pTMS(double SmearMS, bool doScale=true);
 
    double pTID();
    double pTID(double SmearID, bool doScale=true);
 
    double pTCB();
    double pTCB(double SmearCB, bool doScale=true);
  
    double ChargeFlip(double);
    double ChargeFlipMS();
    double ChargeFlipID();
    double ChargeFlipCB();
  
    double SMS();
    double SID();
    double SCB();
 	      
    double VMS();
    double VID();
    double Corr();
 
 
    void MSUP(double&, bool useErrMatrix = false); 
    void MSUP(double&, double&, double&, bool useErrMatrix = false);
  
    void MSLOW(double&, bool useErrMatrix = false);
    void MSLOW(double&, double&, double&, bool useErrMatrix = false);
  
    void IDUP(double&, bool useErrMatrix = false);
    void IDUP(double&, double&, double&, bool useErrMatrix = false);

    void IDLOW(double&, bool useErrMatrix = false);
    void IDLOW(double&, double&, double&, bool useErrMatrix = false);
  
    SYSTTYPE SelectFun(std::string);
    DATATYPE SetData(std::string);
    ALGOTYPE SetAlgorithm(std::string);
    RELTYPE  SetRelease(std::string);

    void PTVar(double&, std::string);
    void PTVar(double&, double&, double&, std::string);
  
    double Sign(double);
  
    /** simple methods for retrieving input values 
	(not needed since all members are public) **/
    double ptms_orig();
    double ptid_orig();
    double ptcb_orig();
    double ETA();
    int DetRegion();
    int GetScaleRegion();

    /*members*/
    double ptms,ptid,ptcb,eta,phi,charge;
    double vms,vid,corr;
    double smearDeltaMS,smearDeltaID,smearDeltaCB;
    bool   useTan2;
    int detRegion;
    int scaleRegion;
    double GeV;
    double g1,g2,g3,g4;
    double wMS,wID;
    bool useScale;
    double restrictCurvCorrSigma;
    ifstream InValues; //! don't persistify
    bool useImprovedCombine;
    bool apply_to_data;
    
    std::vector<double> getScale_ID();
    std::vector<double> getScaleSyst_ID();
    std::vector<double> getScale_MS();
    std::vector<double> getScaleSyst_MS();
    std::vector<double> getScale_CB();
    std::vector<double> getScaleSyst_CB();
  
    std::vector<double> getp1_ID();
    std::vector<double> getp2_ID();
    std::vector<double> getp2_ID_TAN();
    std::vector<double> getp1_MS();
    std::vector<double> getp2_MS();
  
    std::vector<double> getE_p1_ID();
    std::vector<double> getE_p2_ID();   
    std::vector<double> getE_p2_ID_TAN();   
    std::vector<double> getE_p1_MS();
    std::vector<double> getE_p2_MS();
  
    std::vector<double> getS_p1_ID();
    std::vector<double> getS_p2_ID();
    std::vector<double> getS_p2_ID_TAN();   
    std::vector<double> getS_p1_MS();   
    std::vector<double> getS_p2_MS();   
  
    std::vector<double> getMC_p1_ID();   
    std::vector<double> getMC_p2_ID();   
    std::vector<double> getMC_p2_ID_TAN();   
    std::vector<double> getMC_p0_MS();   
    std::vector<double> getMC_p1_MS();   
    std::vector<double> getMC_p2_MS();

    std::vector<double> getCorrMatC0();
    std::vector<double> getCorrMatC1();
    std::vector<double> getCorrMatC2();
    std::vector<double> getCorrMatC3();
    std::vector<double> getCorrMatC4();
    std::vector<double> getCorrMatC5();
  		      
    std::vector<double> getCorrMatTanC0();
    std::vector<double> getCorrMatTanC1();
    std::vector<double> getCorrMatTanC2();
    std::vector<double> getCorrMatTanC3();
    std::vector<double> getCorrMatTanC4();
    std::vector<double> getCorrMatTanC5();

#ifdef ROOTCORE
    ClassDef(SmearingClass,1)
#endif
  
  protected:
    bool m_CallSetClass;
    double m_pTmax;
    std::string m_DataYear;
    std::string m_Fdir;
    std::string m_Release;
    std::string m_ScaleType;
    SMEARTYPE Tsmear;
    SCALETYPE Tscale;
    DETTYPE   Tdet;
    SYSTTYPE  Tfun;
    DATATYPE  Tdata;
    RELTYPE   Trel;
    ALGOTYPE  Talgo;
    
    std::string m_Algorithm;

    /* overall scale correction */
    std::vector<double> m_scale_ID;
    std::vector<double> m_scaleSyst_ID;
    std::vector<double> m_scale_MS;
    std::vector<double> m_scaleSyst_MS;
    std::vector<double> m_scale_CB;
    std::vector<double> m_scaleSyst_CB;

    /* charge-dependent momentum corrections */
    std::vector<double> m_scaleBins;
    std::vector<double> m_S1_ID;
    std::vector<double> m_S2_ID;
    std::vector<double> m_S1_MS;
    std::vector<double> m_S2_MS;
    std::vector<double> m_S1_CB;
    std::vector<double> m_S2_CB;
    /* correlated and anti-correlated errors on the above */
    std::vector<double> m_S1Corr_ID;
    std::vector<double> m_S2Corr_ID;
    std::vector<double> m_S1Corr_MS;
    std::vector<double> m_S2Corr_MS;
    std::vector<double> m_S1Corr_CB;
    std::vector<double> m_S2Corr_CB;
    std::vector<double> m_S1ACorr_ID;
    std::vector<double> m_S2ACorr_ID;
    std::vector<double> m_S1ACorr_MS;
    std::vector<double> m_S2ACorr_MS;
    std::vector<double> m_S1ACorr_CB;
    std::vector<double> m_S2ACorr_CB;
    
    /* corrections on resolution parameters */
    std::vector<double> m_p1_ID;
    std::vector<double> m_p2_ID;
    std::vector<double> m_p2_ID_TAN;
    std::vector<double> m_p1_MS;
    std::vector<double> m_p2_MS;
    /* stat. errors on resolution parameters corrections */
    std::vector<double> m_E_p1_ID;
    std::vector<double> m_E_p2_ID;   
    std::vector<double> m_E_p2_ID_TAN;   
    std::vector<double> m_E_p1_MS;
    std::vector<double> m_E_p2_MS;
    /* syst. errors on resolution parameters corrections */
    std::vector<double> m_S_p1_ID;
    std::vector<double> m_S_p2_ID;
    std::vector<double> m_S_p2_ID_TAN;   
    std::vector<double> m_S_p1_MS;   
    std::vector<double> m_S_p2_MS;   
    /* MC resolution parameters */
    std::vector<double> m_MC_p1_ID;   
    std::vector<double> m_MC_p2_ID;   
    std::vector<double> m_MC_p2_ID_TAN;   
    std::vector<double> m_MC_p0_MS;   
    std::vector<double> m_MC_p1_MS;   
    std::vector<double> m_MC_p2_MS;   
    /* correlation matrix */
    std::vector<double> m_CorrMatC0;
    std::vector<double> m_CorrMatC1;
    std::vector<double> m_CorrMatC2;
    std::vector<double> m_CorrMatC3;
    std::vector<double> m_CorrMatC4;
    std::vector<double> m_CorrMatC5;
    std::vector<double> m_CorrMatTanC0;
    std::vector<double> m_CorrMatTanC1;
    std::vector<double> m_CorrMatTanC2;
    std::vector<double> m_CorrMatTanC3;
    std::vector<double> m_CorrMatTanC4;
    std::vector<double> m_CorrMatTanC5;
  
  private:
    static TRandom3* m_rand;
    /* number of regions */
    unsigned short int m_nb_regions;
    /* eta boundaries of the regions */
    std::vector<float> m_eta_min;
    std::vector<float> m_eta_max;
    /* phi boundaries of the regions */
    std::vector<float> m_phi_min;
    std::vector<float> m_phi_max;

    /* methods */
    void Initialize(std::string data, std::string algo, std::string smearType,
		    std::string rel, std::string dir);
    void Finalize();
    void Clean();
    void CleanScales();
    int getRegion(double eta,double phi);
    int getRegionOld(double eta);
  };
}
#endif

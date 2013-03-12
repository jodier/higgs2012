#ifndef ELECTRONLIKELIHOODTOOL_H
#define ELECTRONLIKELIHOODTOOL_H

#include <fstream>
#include <iostream>
#include "TFile.h"
#include "TH1.h"

//#define IP_BINS 2
#define IP_BINS 1

//----------------------------------------------------------------------------------------

/**
   Author: Kurt Brendlinger <kurb@sas.upenn.edu>
   
   Includes the following operating points:
     "Tight"      - Same background rejection as current (2012) tightpp  menu
     "Very_Tight" - Same signal efficiency    as current (2012) tightpp  menu
     "Medium"     - Same signal efficiency    as current (2012) mediumpp menu
     "Very_Loose" - Same background rejection as current (2012) multilepton menu
     "Loose"      - Same signal efficiency    as current (2012) multilepton menu
     "Loose_BL_Pix" - Same as ::Loose, but with a cut on blayer, and a harder pixel cut. HSG2: USE THIS!
   
   Others (deprecated) - please use the menus above!:

     "Tight_FixedBkgRejection"           - Same background rejection as current (2012) tightpp  menu
     "Tight_FixedSignalEfficiency"       - Same signal efficiency    as current (2012) tightpp  menu
     "Medium_FixedBkgRejection"          - Same background rejection as current (2012) mediumpp menu
     "Medium_FixedSignalEfficiency"      - Same signal efficiency    as current (2012) mediumpp menu
     "Loose1_FixedBkgRejection"          - Same background rejection as current (2012) loosepp  menu
     "Loose1_FixedSignalEfficiency"      - Same signal efficiency    as current (2012) loosepp  menu
     "Multilepton_FixedBkgRejection"     - Same background rejection as current (2012) multilepton menu
     "Multilepton_FixedSignalEfficiency" - Same signal efficiency    as current (2012) multilepton menu
   
   Usage:
     Much like the cuts menus, the passLikelihood method takes input PiD Variables, as well as
     an enum corresponding to a particular operating point (see above),
     and returns true if the electron satisfies that operating point's requriements.
     It returns false otherwise.

     Additional output will be given if debug is set, (false by default).

     In order to correctly apply the macro, you must use the following (d3pd) variables as inputs:
       eta 		: el_etas2
       eT (in MeV) 	: el_cl_E/cosh(el_etas2) NOTE THAT THIS IS DIFFERENT FROM ORIGINALLY ADVERTISED!
       f3               : el_f3
       rHad 		: el_Ethad / eT (see above for eT)
       rHad1 		: el_Ethad1/ eT
       Reta     	: el_reta
       w2 		: el_weta2
       f1       	: el_f1
       wstot    	: el_wstot
       DEmaxs1 		: (el_emaxs1+el_Emax2 == 0.) ? 0. : (el_emaxs1-el_Emax2)/(el_emaxs1+el_Emax2)
                          (i.e. Eratio)
       deltaEta 	: el_deltaeta1
       d0 		: el_trackd0pv
       TRratio 		: el_TRTHighTOutliersRatio
       d0sigma 		: el_tracksigd0pv
       fside    	: el_fside
       rphi     	: el_rphi
       ws3      	: el_ws3
       deltaPoverP      : see below.
       nSi 		: el_nSiHits
       nSiDeadSensors 	: el_nPixelDeadSensors + el_nSCTDeadSensors
       nPix 		: el_nPixHits
       nPixDeadSensors 	: el_nPixelDeadSensors
       nBlayer 		: el_nBLHits
       nBlayerOutliers 	: el_nBLayerOutliers
       expectBlayer 	: el_expectHitInBLayer
       convBit 		: el_isEM & (0x1 << egammaPID::ConversionMatch_Electron) (must #include "egammaEvent/egammaPIDdefs.h")
                        : OR, alternatively, el_isEM & (0x1 << 1)
       ip 		: Count number of vertices in vxp_n with >= 2 tracks in vxp_trk_n

   DEFINITION OF deltaPoverP :
	double dpOverp = 0.;
	for (unsigned int i = 0; i<el_refittedTrack_LMqoverp[el].size();++i) {
	   if((el_refittedTrack_author[el]).at(i)== 4) {
	     dpOverp= 1.-(el_trackqoverp[el]/(el_refittedTrack_LMqoverp[el].at(i)));
	   }
	 }
	return dpOverp;

   Created:
      June 2011

*/
//-------------------------------------------------------------------------------------------------------

namespace LikeEnum {
  enum Menu {
    Very_Loose,
    Loose,
    Medium,
    Tight,
    Very_Tight,
    Tight_FixedBkgRejection,
    Tight_FixedSignalEfficiency,
    Medium_FixedBkgRejection,
    Medium_FixedSignalEfficiency,
    Loose1_FixedBkgRejection,
    Loose1_FixedSignalEfficiency,
    Multilepton_FixedBkgRejection,
    Multilepton_FixedSignalEfficiency,
    Loose_BL_Pix=100
  };
}

class ElectronLikelihoodTool
{
public:
  ElectronLikelihoodTool();
  ElectronLikelihoodTool(std::string wfile,std::string vars="",std::string ipbinning="");
  ~ElectronLikelihoodTool();

  // To concoct a bitmask on your own, use the 
  // variable names prescribed in fVariables.

  unsigned int GetLikelihoodBitmask(std::string vars,bool debug=false);
  unsigned int LikelihoodTightBitmask(bool debug=false){
    std::string vars = "el_deltaeta1,el_weta2,el_TRTHighTHitsRatio,el_f1,el_f3,el_deltaEmax2,el_rphi,el_rhad,el_reta,el_DeltaPoverP,el_deltaphiRescaled,el_trackd0,el_d0Sig";//,el_ptcone20pt";
    return GetLikelihoodBitmask(vars,debug);
  };
  unsigned int LikelihoodMediumBitmask(bool debug=false){
    std::string vars = "el_deltaeta1,el_weta2,el_TRTHighTHitsRatio,el_f1,el_f3,el_deltaEmax2,el_rphi,el_rhad,el_reta,el_DeltaPoverP,el_deltaphiRescaled,el_trackd0,el_d0Sig";//,el_ptcone20pt";
    return GetLikelihoodBitmask(vars,debug);
  };
  unsigned int LikelihoodLooseBitmask(bool debug=false){
    //std::string vars = "el_rhad,el_reta,el_deltaeta1,el_weta2,el_d0Sig,el_TRTHighTHitsRatio,el_f1,el_trackd0,el_f3,el_deltaEmax2,el_rphi";
    std::string vars = "el_rhad,el_reta,el_deltaeta1,el_weta2,el_TRTHighTHitsRatio,el_f1,el_f3,el_deltaEmax2,el_rphi,el_DeltaPoverP,el_deltaphiRescaled";
    return GetLikelihoodBitmask(vars,debug);
  };
  unsigned int LikelihoodMultileptonBitmask(bool debug=false){
    std::string vars = "el_rhad,el_reta,el_deltaeta1,el_weta2,el_TRTHighTHitsRatio,el_f1,el_f3,el_deltaEmax2,el_rphi,el_DeltaPoverP,el_deltaphiRescaled";
    return GetLikelihoodBitmask(vars,debug);
  };
  //bool passLikelihood      (const egamma* eg, LikeEnum::Menu operating_point);
  bool passLikelihood      (LikeEnum::Menu operating_point,
			    double eta, double eT,double f3, double rHad, double rHad1,
			    double Reta, double w2, double f1, double DEmaxs1,
			    double deltaEta, double d0, double TRratio,
			    double d0sigma,
			    double rphi, double ws3,
			    //
			    double deltaPoverP ,double deltaphires,
			    //
			    //int nTRT, int nTRTOutliers,
			    int nSi,int nSiDeadSensors, int nPix, int nPixDeadSensors,
			    int nBlayer, int nBlayerOutliers, bool expectBlayer,
			    int convBit, double ip); // bool debug=false
  double EvaluateLikelihood(double eta, double eT,double f3, double rHad, double rHad1,
			    double Reta, double w2, double f1, double wstot, double DEmaxs1,
			    double deltaEta, double d0, double TRratio, double eOverP,
			    double deltaPhi, double d0sigma, double fside,
			    double ptcone20, double rphi, double ws3,
			    double deltaPoverP ,double deltaphires,
			    double ip, unsigned int mask=0);
  
  // For every input "varVector", make sure elements of vector are
  // in the same order as prescribed in fVariables

  double EvaluateLikelihood(std::vector<double> varVector,double et,double eta,double ip=0, unsigned int mask=0); // et (24*1000.), eta
  double EvaluateLikelihood(std::vector<float>  varVector,double et,double eta,double ip=0, unsigned int mask=0); // et (24*1000.), eta
  static ElectronLikelihoodTool& Instance(std::string,std::string,std::string);

  void setDebug(void){ fDebug = true; };
  void setDebug(bool d){ fDebug = d; };

private:
  double TransformLikelihoodOutput(double ps,double pb);

  bool                fDebug;
  std::string         fPDFfilename;
  unsigned int        fVariableMask;
  std::string         fIpBinning;
  TFile*              fPDFfile;  
  //static const unsigned int  fnIpBins =2;
  static const double fIpBounds[IP_BINS+1];
  static const unsigned int  fnEtBins         = 6;
  static const unsigned int  fnFineEtBins     = 9;
  static const unsigned int  fnEtaBins           = 10;
  static const unsigned int  fnVariables             = 15; // 19
  TH1F*               fPDFbins     [2][IP_BINS][6][10][15]; // [sig(0)/bkg(1)][ip][et][eta][variable]
  double              fPDFIntegrals[2][IP_BINS][6][10][15]; // [sig(0)/bkg(1)][ip][et][eta][variable]
  static const char*  fVariables                      [15]; // 
  //static const double cutDiscriminant [1][6][10];     // [ip][et][eta]

  static const double Disc_Tight_FBR[1][9][10];
  static const double Disc_Tight_FSE[1][9][10];
  static const double Disc_Medium_FBR[1][9][10];
  static const double Disc_Medium_FSE[1][9][10];
  static const double Disc_Loose1_FBR[1][9][10];
  static const double Disc_Loose1_FSE[1][9][10];
  static const double Disc_Multilepton_FBR[1][9][10];
  static const double Disc_Multilepton_FSE[1][9][10];

  static const double Disc_Tight_FBR_b[1][9][10];
  static const double Disc_Tight_FSE_b[1][9][10];
  static const double Disc_Medium_FBR_b[1][9][10];
  static const double Disc_Medium_FSE_b[1][9][10];
  static const double Disc_Loose1_FBR_b[1][9][10];
  static const double Disc_Loose1_FSE_b[1][9][10];
  static const double Disc_Multilepton_FBR_b[1][9][10];
  static const double Disc_Multilepton_FSE_b[1][9][10];

  unsigned int getIpBin(double ip);
  void getBinName(char* buffer, int etbin,int etabin, int ipbin, std::string iptype);
};

  ElectronLikelihoodTool GetElectronLikelihoodTool(std::string wfile,std::string vars,std::string ipbinning);

//----------------------------------------------------------------------------------------
#endif

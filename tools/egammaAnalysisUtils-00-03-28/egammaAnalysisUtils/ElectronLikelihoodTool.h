#ifndef ELECTRONLIKELIHOODTOOL_H
#define ELECTRONLIKELIHOODTOOL_H

#include <fstream>
#include <iostream>
#include "TFile.h"
#include "TH1.h"
//----------------------------------------------------------------------------------------

/**
   Author: John Alison <johnda@sas.upenn.edu>
           Chris Lester <clester@sas.upenn.edu>
	   
   Includes:
         
     Loose++ Optimization for  > 20 GeV electrons (MC corrected from Z T and P)
     Medium++ Optimization for  > 20 GeV electrons (MC corrected from Z T and P)
     Tight++ Optimization for  > 20 GeV electrons (MC corrected from Z T and P)
	    
	   Loose++  Optimization for  10-20 GeV electrons (MC corrected from TightEle)
     Medium++ Optimization for 10-20 GeV electrons (MC corrected from Tight Ele )
	   Tight++ Optimization for 10-20 GeV electrons (MC corrected from Tight Ele )
	   
   Usage:
     The is isTightPlusPlus, isMediumPlusPlus, and isLoosePlusPlus methods take input PiD Variables,
     and returns true if the electron satisfies the loose++ or medium++ requriements.
     It returns false otherwise.

     Additional output will be givedn if debug is set, (false by default).
     
     The trigger bit emulates the online selction of e20_medium1.

     An example of using the macro with the details of the input variables can be found 
       in offline/Reconstruction/egamma/egammaAnalysis/egammaAnalysisUtils

   Created:
      June 2011

*/
//-------------------------------------------------------------------------------------------------------
class ElectronLikelihoodTool
{
public:
  ElectronLikelihoodTool(){};
  ElectronLikelihoodTool(std::string wfile,std::string vars="",std::string ipbinning="");
  ~ElectronLikelihoodTool();

  // To concoct a bitmask on your own, use the 
  // variable names prescribed in fVariables.

  unsigned int GetLikelihoodBitmask(std::string vars,bool debug=false);
  unsigned int LikelihoodTightBitmask(bool debug=false){
    std::string vars = "el_deltaeta1,el_weta2,el_d0Sig,el_TRTHighTHitsRatio,el_f1,el_trackd0,el_f3,el_deltaEmax2,el_rphi,el_ws3,el_rhad,el_reta,el_ptcone20pt";
    return GetLikelihoodBitmask(vars,debug);
  };
  unsigned int LikelihoodMediumBitmask(bool debug=false){
    std::string vars = "el_deltaeta1,el_weta2,el_d0Sig,el_TRTHighTHitsRatio,el_f1,el_trackd0,el_f3,el_deltaEmax2,el_rphi,el_rhad,el_reta,el_ptcone20pt";
    return GetLikelihoodBitmask(vars,debug);
  };
  unsigned int LikelihoodLooseBitmask(bool debug=false){
    std::string vars = "el_rhad,el_reta,el_deltaeta1,el_weta2,el_d0Sig,el_TRTHighTHitsRatio,el_f1,el_trackd0,el_f3,el_deltaEmax2,el_rphi";
    return GetLikelihoodBitmask(vars,debug);
  };
  bool passLikelihood      (std::string operating_point,
			    double eta, double eT,double f3, double rHad, double rHad1,
			    double Reta, double w2, double f1, double wstot, double DEmaxs1,
			    double deltaEta, double d0, double TRratio, double eOverP,
			    double deltaPhi, double d0sig, double fside,
			    double ptcone20, double rphi, double ws3,
			    //
			    int nTRT, int nTRTOutliers,
			    int nSi,int nSiOutliers, int nPix, int nPixOutliers,
			    int nBlayer, int nBlayerOutliers, bool expectBlayer, 
			    int convBit,bool debug=false);
  double EvaluateLikelihood(double eta, double eT,double f3, double rHad, double rHad1,
			    double Reta, double w2, double f1, double wstot, double DEmaxs1,
			    double deltaEta, double d0, double TRratio, double eOverP,
			    double deltaPhi, double d0sig, double fside,
			    double ptcone20, double rphi, double ws3,
			    unsigned int mask=0);
  
  // For every input "varVector", make sure elements of vector are
  // in the same order as prescribed in fVariables

  double EvaluateLikelihood(std::vector<double> varVector,double et,double eta,double ip=0, unsigned int mask=0); // et (24*1000.), eta
  double EvaluateLikelihood(std::vector<float>  varVector,double et,double eta,double ip=0, unsigned int mask=0); // et (24*1000.), eta
  static ElectronLikelihoodTool& Instance(std::string,std::string,std::string);

private:
  double TransformLikelihoodOutput(double ps,double pb);

  std::string         fPDFfilename;
  unsigned int        fVariableMask;
  std::string         fIpBinning;
  TFile*              fPDFfile;  
  static const unsigned int  fnIpBins =1;
  static const unsigned int  fnEtBins   = 5;
  static const unsigned int  fnEtaBins     = 10;
  static const unsigned int  fnVariables       = 17;
  TH1F*               fPDFbins     [2][1][5][10][17]; // [sig(0)/bkg(1)][ip][et][eta][variable]
  double              fPDFIntegrals[2][1][5][10][17]; // [sig(0)/bkg(1)][ip][et][eta][variable]
  static const char*  fVariables                [17]; // 
  //static const double cutDiscriminant [1][5][10];     // [ip][et][eta]

  static const double Disc_Tight_FixedBkgRejection[1][5][10];
  static const double Disc_Tight_FixedSignalEfficency[1][5][10];
  static const double Disc_Medium_FixedBkgRejection[1][5][10];
  static const double Disc_Medium_FixedSignalEfficiency[1][5][10];
  static const double Disc_Loose1_FixedBkgRejection[1][5][10];
  static const double Disc_Loose1_FixedSignalEfficiency[1][5][10];

  unsigned int getIpBin(double ip);
  void getBinName(char* buffer, int etbin,int etabin, int ipbin, std::string iptype);
};

  ElectronLikelihoodTool GetElectronLikelihoodTool(std::string wfile,std::string vars,std::string ipbinning);

//----------------------------------------------------------------------------------------
#endif

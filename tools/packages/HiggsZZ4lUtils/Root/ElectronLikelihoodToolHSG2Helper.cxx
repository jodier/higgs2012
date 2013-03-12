#include <cmath>
#include "HiggsZZ4lUtils/ElectronLikelihoodToolHSG2Helper.h"

namespace likelihoodHelper {

//---------------------------------------------------------------------------------------
// Gets the Eta bin [0-9] given the eta
unsigned int getLikelihoodEtaBin(double eta){
  const unsigned int nEtaBins = 10;
  const double etaBins[nEtaBins] = {0.1,0.6,0.8,1.15,1.37,1.52,1.81,2.01,2.37,2.47};
  
  for(unsigned int etaBin = 0; etaBin < nEtaBins; ++etaBin){
    if(fabs(eta) < etaBins[etaBin])
      return etaBin;
  }
  
  return 9;
}
//---------------------------------------------------------------------------------------
// Gets the Et bin [0-10] given the et (MeV)
unsigned int getLikelihoodEtBin(double eT){
  const unsigned int nEtBins = 6; // 11
  const double GeV = 1000;
  //const double eTBins[nEtBins] = {5*GeV,10*GeV,15*GeV,20*GeV,30*GeV,40*GeV,50*GeV,60*GeV,70*GeV,80*GeV};
  const double eTBins[nEtBins] = {10*GeV,15*GeV,20*GeV,30*GeV,40*GeV,50*GeV};  

  for(unsigned int eTBin = 0; eTBin < nEtBins; ++eTBin){
    if(eT < eTBins[eTBin])
      return eTBin;
  }
  
  return 5; // 10 // Return the last bin if > the last bin.
}

//---------------------------------------------------------------------------------------
// Gets the Et bin [0-10] given the et (MeV)
unsigned int getLikelihoodEtFineBin(double eT){
  const unsigned int nEtBins = 9; // 11
  const double GeV = 1000;
  //const double eTBins[nEtBins] = {5*GeV,10*GeV,15*GeV,20*GeV,30*GeV,40*GeV,50*GeV,60*GeV,70*GeV,80*GeV};
  const double eTBins[nEtBins] = {10*GeV,15*GeV,20*GeV,25*GeV,30*GeV,35*GeV,40*GeV,45*GeV,50*GeV};  

  for(unsigned int eTBin = 0; eTBin < nEtBins; ++eTBin){
    if(eT < eTBins[eTBin])
      return eTBin;
  }
  
  return 8; // Return the last bin if > the last bin.
}

}

using namespace likelihoodHelper;

bool passLikelihoodThreePointFive(ElectronLikelihoodTool* tool,
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
				  int convBit, double ip){
  ///
  unsigned int bitmask = tool->LikelihoodLooseBitmask();
  unsigned int etbin = getLikelihoodEtFineBin(eT);
  unsigned int etabin = getLikelihoodEtaBin(eta);
  unsigned int ipbin  = 0;

  double wstot = -9999.;
  double fside = -9999.;
  double eOverP = -9999.;  
  double deltaPhi = -9999.;  
  double ptcone20 = -9999.;

  if (nSiDeadSensors + nPixDeadSensors + nBlayer + nBlayerOutliers + expectBlayer 
      + convBit + ip + wstot + fside + eOverP + deltaPhi + ptcone20 > -999.) 
    std::cout << "This is here to get rid of warnings. Do not worry about it." << std::endl;


  const double Disc_3_5XControlRegion[1][9][10] = {{{ -0.208, -0.208,  0.086, -0.136, -0.106,  0.008, -0.088, -0.028, -0.004, -0.076},
						    { -0.058, -0.058,  0.008, -0.016, -0.076, -0.052, -0.070, -0.028, -0.046, -0.160},
						    { -0.028, -0.028,  0.002, -0.040, -0.070, -0.070, -0.076, -0.112, -0.130, -0.142},
						    { -0.088, -0.088, -0.040, -0.130, -0.154, -0.142, -0.130, -0.172, -0.202, -0.244},
						    { -0.052, -0.052, -0.016, -0.076, -0.106, -0.130, -0.118, -0.142, -0.154, -0.148},
						    { -0.094, -0.094, -0.106, -0.124, -0.184, -0.256, -0.148, -0.196, -0.238, -0.256},
						    { -0.064, -0.064, -0.022, -0.070, -0.130, -0.166, -0.226, -0.226, -0.154, -0.274},
						    { -0.100, -0.100,  0.044, -0.034, -0.178, -0.298, -0.208, -0.316, -0.166, -0.256},
						    { -0.040, -0.040, -0.058, -0.136,  0.020, -0.244, -0.256, -0.160, -0.208, -0.328}}};

  double cutDiscriminant = Disc_3_5XControlRegion[ipbin][etbin][etabin];

  if (nSi + nSiDeadSensors < 7){
    //if (fDebug) std::cout << "Likelihood macro (loose): Silicon Failed." << std::endl;
    return false;
  }
  if (nPix+nPixDeadSensors < 1){
    //if (fDebug) std::cout << "Likelihood macro (loose): Pixels Failed." << std::endl;
    return false;
  }

  double response = tool->EvaluateLikelihood(eta,eT,f3,rHad,rHad1,Reta,w2,f1,wstot,DEmaxs1,
				       deltaEta,d0,TRratio,eOverP,deltaPhi,d0sigma,fside,
				       ptcone20,rphi,ws3,
				       deltaPoverP,deltaphires,
				       0,bitmask);

  if (response < cutDiscriminant) {
    return false;
  }
  return true;
  ///
}

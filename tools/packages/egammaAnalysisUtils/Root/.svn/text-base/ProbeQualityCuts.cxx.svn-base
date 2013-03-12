/*
  GetProbeQuality in Tag&Probe measurements 2012 MENU
==========================================================================================================
  double Et_cl           =  el_cl_E/cosh(el_etas2);
  double etas2           =  el_etas2;
  double rHad            =  el_Ethad/Et_cl;
  double rHad1           =  el_Ethad1/Et_cl;
===============================================================================================
*/

#include "egammaAnalysisUtils/MultiLeptonDefs_HCP2012.h"
#include "egammaAnalysisUtils/IsEMPlusPlusDefs.h"
#include "egammaAnalysisUtils/ProbeQualityCuts.h"
#include <iostream>
#include <cmath>


//----------------------------------------------------------------------------------------
bool passProbeQualityRHad(double eta, double eT,
			double rHad, double rHad1) {
         		      
  // Sanity Check on eta
  if( fabs( eta ) > 2.47 ) return false;
  
//Check RHad for ML menue
  unsigned int eTBinML = getEtBinH4l(eT);
  unsigned int etaBinML = getEtaBinH4l(eta);
  bool passRHadML = passRHad(rHad,rHad1,eTBinML,etaBinML);


  //Check RHad for PP menue
  unsigned int eTBin = getEtBin(eT);
  unsigned int etaBin = getEtaBin(eta);
  bool passRHad_PP = passRHad_med(rHad,rHad1 ,eTBin,etaBin,egammaMenu::eg2012);

  bool TagAndProbe_PassRHad = false;

  if (passRHad_PP || passRHadML) {
    TagAndProbe_PassRHad = true;
    //    cout << "setting rhad to true" << endl;
  }

  return TagAndProbe_PassRHad;

}


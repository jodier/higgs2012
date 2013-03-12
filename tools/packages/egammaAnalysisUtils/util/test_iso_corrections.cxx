#include <iostream>

#include "egammaAnalysisUtils/CaloIsoCorrection.h"

using namespace std;
using namespace CaloIsoCorrection;

int main(int /* argc */, char** /* argv */){

  float clusterEnergy = 100000.;
  float etaCluster = .8;
  float etaPointing = .85;
  float etaS2 = .78;
  float radius = .40;
  bool isConversion = false;
  float EtCone_val = 5000.;
  
  unsigned int nPV = 5;
  bool is_mc = false;
  
  Version ver = REL17;
  
  float Etcone40 = 5000.;
  float Etcone40_ED_corrected = 4500.;
  
  float ED_median = 1039.;


  cout << "GetNPVCorrectedIsolation: " << GetNPVCorrectedIsolation(nPV,
                                                       etaS2,
                                                       radius,
                                                       is_mc,
                                                       EtCone_val,
                                                       PHOTON) << endl;

  cout << "GetEDCorrectedIsolation: " << GetEDCorrectedIsolation(Etcone40,
                                                      Etcone40_ED_corrected,
                                                      radius,
                                                      EtCone_val,
                                                      PHOTON) << endl;

  cout << "GetPtCorrectedIsolation: " << GetPtCorrectedIsolation(clusterEnergy,
                                                      etaS2,
                                                      etaPointing,
                                                      etaCluster,
                                                      radius,
                                                      is_mc,
                                                      EtCone_val,
                                                      isConversion,
                                                      ELECTRON,
                                                      ver) << endl;

  cout << "GetPtNPVCorrectedIsolation: " << GetPtNPVCorrectedIsolation(nPV, 
	                                                      clusterEnergy, 
	                                                      etaS2, 
	                                                      etaPointing, 
	                                                      etaCluster, 
	                                                      radius, 
	                                                      is_mc, 
	                                                      EtCone_val, 
	                                                      isConversion, 
	                                                      ELECTRON, 
	                                                      ver) << endl; 

  cout << "GetPtCorrectedTopoIsolation: " << GetPtCorrectedTopoIsolation(clusterEnergy,
                                                          etaS2,
                                                          etaPointing,
                                                          etaCluster,
                                                          radius,
                                                          is_mc,
                                                          EtCone_val,
                                                          isConversion,
                                                          ELECTRON) << endl;


  cout << "GetEDMedian: " << GetEDMedian(Etcone40, Etcone40_ED_corrected) << endl;
  
  cout << "GetPtEDCorrectedTopoIsolation: " << GetPtEDCorrectedTopoIsolation(ED_median,
                                                          clusterEnergy,
                                                          etaS2,
                                                          etaPointing,
                                                          etaCluster,
                                                          radius,
                                                          is_mc,
                                                          EtCone_val,
                                                          isConversion,
                                                          ELECTRON) << endl;




  return 0;


}

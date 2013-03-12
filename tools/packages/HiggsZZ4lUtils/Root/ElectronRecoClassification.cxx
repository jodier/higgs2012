#include "HiggsZZ4lUtils/ElectronRecoClassification.h"
#include <cmath>
#include <iostream>
 

ElectronRecoClass::RecoType ElectronRecoClass::getRecoClassification(double eta,double TRTHighTOutliersRatio, double f1, 
								     double rphi, int nPix, int nPixDeadSensors,int nBlayerHits, 
								     bool expectBlayer,int nTRT, int nTRTOutliers ){

  bool passf1=(f1>0.1);
  bool passrphi=(rphi>0.9);
  bool passConv=((expectBlayer && nBlayerHits<1) || (!expectBlayer && (nPix+nPixDeadSensors)<2));
  int nTRTTotal= nTRT+nTRTOutliers;
  //
  int ibin_eta_TRT = -1;
  static const double CutTR[6] = {0.09, 0.105, 0.11, 0.125, 0.145, 0.16};
  static const double CutBinEta_TRT[6] = {0.1, 0.625, 1.07, 1.304, 1.752, 2.0};  
  //Find eta bin
  for (unsigned int ibinEta=0;ibinEta<6;ibinEta++) {
    if ( ibinEta == 0 ){
      if ( fabs(eta) < CutBinEta_TRT[ibinEta] ) {
	ibin_eta_TRT = ibinEta;
      }
    } 
    else {
      if ( fabs(eta) >= CutBinEta_TRT[ibinEta-1] && fabs(eta) < CutBinEta_TRT[ibinEta] ) {
	ibin_eta_TRT = ibinEta;
     }
    }
  }
  //
  bool passTR=false;
  if (ibin_eta_TRT >= 0) {//apply the cut 
    passTR= (TRTHighTOutliersRatio > CutTR[ibin_eta_TRT]) ;
  }


  if(fabs(eta)<2.0 || nTRTTotal>=10 ){ //either less than 2.0 or nTRTTotal>=10 for the "edges" 
    if(passConv){
      return ElectronRecoClass::Photon;
    }
    else if(passTR&&passf1){
      return ElectronRecoClass::Electron;    
    }
    else{
      return ElectronRecoClass::Jet;    
    }
  }
  else{ //No TRT hits or above eta 2.0
    if(passConv){
      return ElectronRecoClass::Photon;
    }
    else if(passf1&&passrphi){
      return ElectronRecoClass::Electron;    
    }
    else{
      return ElectronRecoClass::Jet;
    }
  }
  

}



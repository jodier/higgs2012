#ifndef ELECTRONRECOCLASSIFICATION
#define ELECTRONRECOCLASSIFICATION

namespace ElectronRecoClass{

  enum RecoType{
    Electron = 1,
    Photon   = 2,
    Jet      = 3
  };

  
  RecoType getRecoClassification(double eta,double TRTHighTOutliersRatio, double f1, 
				 double rphi, int nPix, int nPixDeadSensors,int nBlayerHits, 
				 bool expectBlayer,int nTRT, int nTRTOutliers);

}


#endif

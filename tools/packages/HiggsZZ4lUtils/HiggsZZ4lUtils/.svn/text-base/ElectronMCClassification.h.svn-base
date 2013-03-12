#ifndef ELECTRONMCCLASSIFICATION
#define ELECTRONMCCLASSIFICATION

namespace ElectronDetailedTruth{

  enum MCDetailedType{
    Zboson =1,
    Wboson =2,
    OtherIsolated=3,
    ZbosonBrem=4,
    WbosonBrem=5,
    FSR=6,
    HeavyFlavor=7,
    HeavyFlavorBrem=8,
    LightMesonDecay=9,
    OtherBkgConversion=10,
    OtherBkgElectron=11,
    Hadron=12,
    Muon=13,
    UnKnown=14,
    Other=15
  };

  MCDetailedType getDetailedMCClassification(int type,int origin,int typebkg,int originbkg );
}

namespace ElectronTruth{

  enum MCType{
    Isolated =1,
    Heavy =2,
    FSR=3,
    Photon=4,
    Hadron=5,
    Muon =6,
    Other=7
  };
  
  MCType getMCClassification(int type,int origin,int typebkg,int originbkg );

}


#endif

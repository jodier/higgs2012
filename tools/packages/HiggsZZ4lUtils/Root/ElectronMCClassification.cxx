#include "HiggsZZ4lUtils/ElectronMCClassification.h"
#include "HiggsZZ4lUtils/H4lMCTruthClassifierDefs.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ElectronDetailedTruth::MCDetailedType ElectronDetailedTruth::getDetailedMCClassification(int type,int origin,int /*typebkg*/,int originbkg ){

  if(type==H4lMCTruthPartClassifier::IsoElectron){ //isolated electron
   
    if(origin==H4lMCTruthPartClassifier::ZBoson){
	return ElectronDetailedTruth::Zboson;
      }
   
    else if(origin==H4lMCTruthPartClassifier::WBoson){
	return ElectronDetailedTruth::Wboson;
      }
   
    else{
	return ElectronDetailedTruth::OtherIsolated;
      }
  }

  else if(type==H4lMCTruthPartClassifier::NonIsoElectron){ //Non-isolated electron --> heavy
    return ElectronDetailedTruth::HeavyFlavor;
  }

  else if(type==H4lMCTruthPartClassifier::BkgElectron && origin==H4lMCTruthPartClassifier::PhotonConv){ //Photon conversions --> many cases as we need to find the origin of the photon
   
    if(originbkg==H4lMCTruthPartClassifier::ZBoson){ //brem from Z
      return ElectronDetailedTruth::ZbosonBrem;
    }
    else if(originbkg==H4lMCTruthPartClassifier::WBoson){//brem from W
      return ElectronDetailedTruth::WbosonBrem;
    }
    else if(originbkg==H4lMCTruthPartClassifier::FSRPhot){//FSR
      return ElectronDetailedTruth::FSR;
    }
   
    else if(originbkg==H4lMCTruthPartClassifier::PiZero || originbkg==H4lMCTruthPartClassifier::LightMeson 
	    || originbkg==H4lMCTruthPartClassifier::StrangeMeson || originbkg==H4lMCTruthPartClassifier::LightBaryon ||
	    originbkg==H4lMCTruthPartClassifier::StrangeBaryon) { //Pi0 Zero or light meson/baryon
      return ElectronDetailedTruth::LightMesonDecay;
    }

    else if ((originbkg>=H4lMCTruthPartClassifier::CharmedMeson && originbkg<=H4lMCTruthPartClassifier::BBbarMeson) 
	     || (originbkg>=H4lMCTruthPartClassifier::CharmedBaryon &&originbkg<=H4lMCTruthPartClassifier::BottomBaryon)){ //heavy meson/baryon
      return ElectronDetailedTruth::HeavyFlavorBrem;
    }
    
    else{
      return ElectronDetailedTruth::OtherBkgConversion;
    }

  }
  else if(type==H4lMCTruthPartClassifier::BkgElectron ){ //BkgElectron but no conversion.
      return ElectronDetailedTruth::OtherBkgElectron;
  }
  else if(type==H4lMCTruthPartClassifier::Hadron){//Hadron
    return ElectronDetailedTruth::Hadron;
  }

  else if( type==H4lMCTruthPartClassifier::IsoMuon || type==H4lMCTruthPartClassifier::NonIsoMuon || type==H4lMCTruthPartClassifier::BkgMuon){//Muon
    return ElectronDetailedTruth::Muon;
  }
  
  else if (type==H4lMCTruthPartClassifier::Unknown || type==H4lMCTruthPartClassifier::UnknownElectron || type==H4lMCTruthPartClassifier::UnknownMuon){ //Unknown
    return ElectronDetailedTruth::UnKnown;
  }

  else{ //everything else
    return ElectronDetailedTruth::Other;
  }

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ElectronTruth::MCType ElectronTruth::getMCClassification(int type,int origin,int typebkg,int originbkg ){

  ElectronDetailedTruth::MCDetailedType  detailedtype = ElectronDetailedTruth::getDetailedMCClassification(type,origin,typebkg,originbkg );

  if(detailedtype==ElectronDetailedTruth::Zboson || detailedtype==ElectronDetailedTruth::Wboson ||
     detailedtype==ElectronDetailedTruth::ZbosonBrem || detailedtype==ElectronDetailedTruth::WbosonBrem ||
     detailedtype==ElectronDetailedTruth::OtherIsolated){
    return ElectronTruth::Isolated; 
  }
  else if(detailedtype==ElectronDetailedTruth::HeavyFlavor ||detailedtype==ElectronDetailedTruth::HeavyFlavorBrem){
    return ElectronTruth::Heavy;
  }
  else if(detailedtype==ElectronDetailedTruth::FSR){
    return ElectronTruth::FSR;
  }
  else if(detailedtype==ElectronDetailedTruth::Muon){
    return ElectronTruth::Muon;
  }
  else if(detailedtype==ElectronDetailedTruth::LightMesonDecay || detailedtype==ElectronDetailedTruth::OtherBkgConversion ){
    return ElectronTruth::Photon; 
  }
  else if(detailedtype==ElectronDetailedTruth::Hadron){
    return ElectronTruth::Hadron;
  }

  return ElectronTruth::Other;

}


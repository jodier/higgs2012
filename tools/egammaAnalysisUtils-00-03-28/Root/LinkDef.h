#ifdef __CINT__
#include "egammaAnalysisUtils/EnergyRescaler.h"
#include "egammaAnalysisUtils/EnergyRescalerUpgrade.h"
#include "egammaAnalysisUtils/egammaSFclass.h"
#include "egammaAnalysisUtils/checkOQ.h"
#include "egammaAnalysisUtils/egammaTriggerMatching.h"
#include "egammaAnalysisUtils/CaloIsoCorrection.h"
#include "egammaAnalysisUtils/ConvertedPhotonScaleTool.h"
#include "egammaAnalysisUtils/EisoTool.h"
#include "egammaAnalysisUtils/FsrPhotons.h"
#include "egammaAnalysisUtils/IsEMPlusPlusDefs.h"

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;
#pragma link C++ class egRescaler::EnergyRescalerUpgrade+;
#pragma link C++ class eg2011::EnergyRescaler+;
#pragma link C++ class eg2011::EnergyRescaler::calibMap+;
//#pragma link C++ class std::vector<eg2011::EnergyRescaler::calibMap>+;
#pragma link C++ class egammaSFclass+;
#pragma link C++ class egammaOQ+;
#pragma link C++ function PassedTriggerEF;
#pragma link C++ namespace CaloIsoCorrection;
#pragma link C++ class ConvertedPhotonScaleTool+;
#pragma link C++ class EisoTool;
#pragma link C++ class FsrPhotons;
#pragma link C++ namespace egammaMenu;
#pragma link C++ enum egammaMenu::egMenu;

#pragma link C++ function isLoosePlusPlus;
#pragma link C++ function isMediumPlusPlus;
#pragma link C++ function isTightPlusPlus;

#endif

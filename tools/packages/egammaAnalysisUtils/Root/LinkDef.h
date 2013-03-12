#ifdef __CINT__

#include "egammaAnalysisUtils/EnergyRescaler.h"
#include "egammaAnalysisUtils/EnergyRescalerUpgrade.h"
#include "egammaAnalysisUtils/egammaSFclass.h"
#include "egammaAnalysisUtils/checkOQ.h"
#include "egammaAnalysisUtils/egammaTriggerMatching.h"
#include "egammaAnalysisUtils/CaloIsoCorrection.h"
#include "egammaAnalysisUtils/ConvertedPhotonScaleTool.h"
#include "egammaAnalysisUtils/EisoTool.h"
#include "egammaAnalysisUtils/EisoTool2012.h"
#include "egammaAnalysisUtils/FsrPhotons.h"
#include "egammaAnalysisUtils/MultiLeptonDefs_HCP2012.h" 
#include "egammaAnalysisUtils/H4l2011Defs.h"
#include "egammaAnalysisUtils/MultiLeptonMenu.h" 
#include "egammaAnalysisUtils/IsEMPlusPlusDefs.h"
#include "egammaAnalysisUtils/VertexPositionReweightingTool.h"
#include "egammaAnalysisUtils/BosonPtReweightingTool.h"
#include "egammaAnalysisUtils/ElectronMCChargeCorrector.h"
#include "egammaAnalysisUtils/IsEMForwardDefs.h"
#include "egammaAnalysisUtils/PhotonIDTool.h"
#include "egammaAnalysisUtils/FudgeMCTool.h"
#include "egammaAnalysisUtils/PhotonEfficiencySFTool.h"
#include "egammaAnalysisUtils/ShowerDepthTool.h"
#include "egammaAnalysisUtils/CaloPointingCorrectionTool.h"
#include "egammaAnalysisUtils/DiphotonVertexIDTool.h"
#include "egammaAnalysisUtils/ElectronLikelihoodTool.h"

#include<vector>

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
#pragma link C++ class EisoTool2012;
#pragma link C++ class FsrPhotons;
#pragma link C++ class VertexPositionReweightingTool;
#pragma link C++ class BosonPtReweightingTool;
#pragma link C++ class ElectronMCChargeCorrector;
#pragma link C++ class MultiLeptonMenu;
#pragma link C++ class H4l2011Defs;
#pragma link C++ class PhotonIDTool;
#pragma link C++ class FudgeMCTool;
#pragma link C++ class PhotonEfficiencySFTool;
#pragma link C++ class ShowerDepthTool;
#pragma link C++ class CaloPointingCorrectionTool;
#pragma link C++ class DiphotonVertexIDTool+;
#pragma link C++ class ElectronLikelihoodTool;

#pragma link C++ class vector<vector<vector<int> > >+;
#pragma link C++ class vector<vector<vector<float> > >+;
#pragma link C++ class vector<vector<float> >+;

#pragma link C++ namespace egammaMenu;
#pragma link C++ enum egammaMenu::egMenu;
#pragma link C++ namespace LikeEnum;
#pragma link C++ enum LikeEnum::Menu;

//#pragma link C++ enum BosonPtReweightingTool::ePtWeightType;

#pragma link C++ function isLoosePlusPlus;
#pragma link C++ function isMediumPlusPlus;
#pragma link C++ function isTightPlusPlus;
#pragma link C++ function passMultiLepton;
#pragma link C++ function isForward_Loose;
#pragma link C++ function isForward_Medium;
#pragma link C++ function isForward_Tight;
#pragma link C++ function Forward_IsEM;
#pragma link C++ namespace egammaForwardMenu;
#pragma link C++ enum egammaForwardMenu::egForwardMenu;
#pragma link C++ enum egammaForwardMenu::egForwardCut;

#endif

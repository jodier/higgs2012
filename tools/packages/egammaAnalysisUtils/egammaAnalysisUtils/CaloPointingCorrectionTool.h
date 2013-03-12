#ifndef CaloPointingCorrectionTool_h
#define CaloPointingCorrectionTool_h

#include <vector>
#include "TString.h"

class TH1F;

class CaloPointingCorrectionTool {
  public :
    CaloPointingCorrectionTool(
      TString dataFile="$ROOTCOREDIR/data/egammaAnalysisUtils/histo_zcorrection_data.root",
      TString mcFile = "$ROOTCOREDIR/data/egammaAnalysisUtils/histo_zcorrection_mc.root",
      TString dataHistoName = "dz_trk_pointing_vs_etas2",
      TString mcHistoName = "dz_trk_pointing_vs_etas2");
    
    ~CaloPointingCorrectionTool();

    /** **/
    float getCaloPointingCorrected(float zPointing, float etas2, bool isData = true);
    
    std::vector<float> getCaloPointingCorrected(std::vector<float>& zPointing,
      std::vector<float>& etas2, bool isData = true);
    
  private:
    TH1F *m_hData, *m_hMC;    
    TH1F* getHisto(TString fileName, TString histoName);

};

#endif

#ifndef ShowerDepthTool_h
#define ShowerDepthTool_h

#include "TString.h"
#include <cmath>

class TH1;

class ShowerDepthTool {
  public :
    ShowerDepthTool(
      TString dataFile="$ROOTCOREDIR/data/egammaAnalysisUtils/CaloDeltaRZ.root",
      TString mcFile = "$ROOTCOREDIR/data/egammaAnalysisUtils/CaloDeltaRZ.root",
      TString dataHistoName = "hData",
      TString mcHistoName = "hMC");
    
    ~ShowerDepthTool();
    
    /** Return the calorimeter displacement in R(Z) for barrel (endcap) **/
    float getRZCorrection(float eta, float phi, bool isData = true);
    
    /** Shower depth (in mm) on EM1 vs. eta, considering misalignments **/
    float getCorrectedShowerDepthEM1(float etas1, float phi, bool isData = true)
      { return getShowerDepthEM1(etas1) - getRZCorrection(etas1, phi, isData); }

    /** Shower depth (in mm) on EM2 vs. eta, considering misalignments **/
    float getCorrectedShowerDepthEM2(float etas2, float phi, bool isData = true)
      { return getShowerDepthEM2(etas2) - getRZCorrection(etas2, phi, isData); }

    /** Return the shower depth in R,Z considering misalignments **/
    std::pair<float, float> getCorrectedRZ(float eta, float phi, 
                                           bool isData = true,
                                           int sampling = 1);
    
    /** Eta direction from zvertex to the shower in the given sampling **/
    float getCorrectedEtaDirection(float zvertex, float eta, float phi, 
                                   bool isData=true, int sampling = 1);
    

    /** Shower depth (in mm) vs. eta on EM1 **/
    static float getShowerDepthEM1(float etas1);
    
    /** Shower depth (in mm) vs. eta on EM2 **/
    static float getShowerDepthEM2(float etas2);

    /** Shower depth in R,Z for the given sampling **/
    static std::pair<float, float> getRZ(float eta, int sampling);

    static float getEtaDirection(float zvertex, float R, float z)    
      { return asinh( (z- zvertex)/R ); }
    
    /** Return TH1* from file given fileName, histoName **/
    static TH1* getHistoFromFile(TString fileName, TString histoName);

    
  private:
    TH1 *m_hData, *m_hMC;    

};

#endif

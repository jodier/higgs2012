/*
  Variable definition (units are MeV)
  ==========================================================================================================
  double Et_cl           =  el_cl_E/cosh(el_etas2);
  double etas2           =  el_etas2;
  double rHad            =  el_Ethad/Et_cl;
  double rHad1           =  el_Ethad1/Et_cl;
  double Reta            =  el_reta;
  double w2              =  el_weta2;
  double f1              =  el_f1;
  double f3              =  el_f3;
  double wstot           =  el_wstot;
  double DEmaxs1         = fabs(el_emaxs1+el_Emax2)>0. ? (el_emaxs1-el_Emax2)/(el_emaxs1+el_Emax2) : 0.;
  double deltaEta        = el_deltaeta1;
  double deltaPhiRescaled = el_deltaphiRescaled;
  int    nSi              = el_nSiHits;
  int    nSiDeadSensors   = el_nSCTDeadSensors+el_nPixelDeadSensors;
  int    nPix             = el_nPixHits;
  int    nPixDeadSensors  = el_nPixelDeadSensors;
  int    nTRThigh         = el_nTRTHighTHits;
  int    nTRThighOutliers = el_nTRTHighTOutliers;
  int    nTRT             = el_nTRTHits;  
  int    nTRTOutliers     = el_nTRTOutliers; 
  bool   expectBlayer     = el_expectBLayerHit; 
  int    nBlayerHits      = el_nBLHits;

  double rTRT = 0.;
  rTRT = (nTRT+nTRTOutliers) > 0 ?  ((double) (nTRThigh+nTRThighOutliers)/(nTRT+nTRTOutliers) ) : 0.;
  int nTRTTotal = nTRT+nTRTOutliers;

  double dpOverp =0;
  for (unsigned int i = 0; i<el_refittedTrack_LMqoverp.size;++i)
  {
  if((el_refittedTrack_author).at(i)==4)
  {
  dpOverp= 1-(el_trackqoverp/(el_refittedTrack_LMqoverp.at(i)));
  }
  }
*/

#include "egammaAnalysisUtils/MultiLeptonMenu.h"
#include <iostream>
#include <cmath>

namespace{
    const double GeV = 1000;
}

MultiLeptonMenu::MultiLeptonMenu(): m_mask(0),m_doDebug(false){
}

MultiLeptonMenu::MultiLeptonMenu(bool doDebug):m_mask(0),m_doDebug(doDebug){
}

MultiLeptonMenu::~MultiLeptonMenu(){
}

bool MultiLeptonMenu::passMultiLepton(double eta, double eT,
                                      double rHad, double rHad1, double Reta, double w2, 
                                      double f1, double f3, double wstot, double DEmaxs1, 
                                      double deltaEta, int nSi, int nSiDeadSensors, int nPix, 
                                      int nPixDeadSensors, double deltaPhiRes, double dpOverp, 
                                      double TRratio,  int nTRTTotal,  int nBlayerHits, bool expectBlayer) const
{


    m_mask=0;
    //Get eta/et bins
    unsigned int etbin = getEtBinH4l(eT);
    unsigned int etabin = getEtaBinH4l(eta);  
    //High Low Brem
    bool isBrem = getBremCategoryH4l(dpOverp, etbin, etabin);

    if (!passCoverage(eta)){
        m_mask|= ( 0x1 << CoverageBit);
        if(m_doDebug) std::cout << "Failed eta coverage Et/eta " << eT << " " << eta << " " << std::endl;
    }
    if (!passSilicon(nSi,nSiDeadSensors)){
        m_mask|= ( 0x1 << SiliconBit);
        if(m_doDebug) std::cout << "Failed nSi " << nSi + nSiDeadSensors << " " << eT << " " << eta << " " << std::endl;
    }
    if (!passPixel(nPix, nPixDeadSensors, etabin)){
        m_mask|= ( 0x1 << PixelBit);
        if(m_doDebug){
            std::cout << "Failed nPix " << nPix << " " << nPixDeadSensors << " " << eT << " " << eta << " " << std::endl;
        }
    }
    if (!passBlayer( nBlayerHits, expectBlayer, etabin)){
        m_mask|= ( 0x1 << BlayerBit);
        if(m_doDebug) std::cout << "Failed nBlayer " << expectBlayer << " " << nBlayerHits << " " << eT << " " << eta << " " << std::endl;
    }
    if (!passRHad(rHad, rHad1,  etbin, etabin)){
        m_mask|= ( 0x1 << RhadBit);
        if(m_doDebug) std::cout << "Failed RHad " << rHad << " " << eT << " " << eta << " " << std::endl;
    }
    if (!passF3(f3,  etbin, etabin)){
        m_mask|= ( 0x1 << F3Bit);
        if(m_doDebug) std::cout << "Failed f3 " << f3 << " " << eT << " " << eta << " " << std::endl;
    }
    if (!passReta(Reta,  etbin, etabin)){
        m_mask|= ( 0x1 << RetaBit);
        if(m_doDebug) std::cout << "Failed Reta " << Reta << " " << eT << " " << eta << " " << std::endl;
    }
    if (!passW2(w2,  etbin, etabin)){
        m_mask|= ( 0x1 << W2Bit);
        if(m_doDebug) std::cout << "Failed w2 " << w2 << " " << eT << " " << eta << " " << std::endl;
    }
    if(f1 > 0.005){
        if (!passWstot(wstot, etbin, etabin)){
            m_mask|= ( 0x1 << WstotBit);
            if(m_doDebug) std::cout << "Failed wstot " << wstot << " " << eT << " " << eta << " " << std::endl;
        }
        if (!passEratio(DEmaxs1, etbin, etabin)){
            m_mask|= ( 0x1 << EratioBit);
            if(m_doDebug) std::cout << "Failed DEmaxs1 " << DEmaxs1 << " " << eT << " " << eta << " " << std::endl;
        }
    }  
    if (!passDeltaEta(deltaEta, etbin, etabin)){
        m_mask|= ( 0x1 << DeltaEtaBit);
        if(m_doDebug) std::cout << "Failed dEta " << deltaEta << " " << eT << " " << eta << " " << std::endl;
    }
    if (!passDeltaPhiRes(deltaPhiRes, isBrem, etbin, etabin)){
        m_mask|= ( 0x1 << DeltaPhiResBit);
        if(m_doDebug) std::cout << "Failed dPhiRes " << deltaPhiRes << " " << isBrem << " " << eT << " " << eta << " " << std::endl;
    }
    if (!passTR(TRratio, eta, nTRTTotal)){
        m_mask|= ( 0x1 << TRBit);
        if(m_doDebug) std::cout << "Failed TR " << TRratio << " "<<nTRTTotal<<" "<< eT << " " << eta << " " << std::endl;
    }

    return (m_mask==0);
}

unsigned int MultiLeptonMenu::getmask() const 
{

    return m_mask;
}

//Helper Functions 
bool MultiLeptonMenu::passCoverage(double eta) const 
{

    if( fabs( eta ) > 2.47 ) return false;
    return true;
}

bool MultiLeptonMenu::passSilicon(int nSi, int nSiDeadSensors) const 
{

    if((nSi + nSiDeadSensors)  < 7) return false;
    return true;
}

bool MultiLeptonMenu::passPixel(int nPix, int nPixDeadSensors, unsigned int etabin) const 
{

    static double cutNPix[10] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};   
    if((nPix+nPixDeadSensors) < cutNPix[etabin]) return false;
    return true;
}

bool MultiLeptonMenu::passBlayer(int nBlayerHits, bool expectBlayer, unsigned int etabin) const 
{

    static double cutNBlayer[10] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};   
    if (expectBlayer && nBlayerHits < cutNBlayer[etabin]) return false;
    return true;
}

bool MultiLeptonMenu::passRHad(double rhad, double rhad1, unsigned int etbin, unsigned int etabin) const
{
    //                                0.0     0.1      0.6   0.8     1.15   1.37     1.52    1.81    2.01    2.37    2.47
    static const double cutrhad[11][10] = {{ 0.258,  0.258, 0.208,  0.206,  0.256,  0.188,  0.254,  0.254,  0.226,  0.176 } // 0 - 5 GeV
                                           ,{ 0.155,  0.155, 0.115,  0.125,  0.125,  0.100,  0.140,  0.135,  0.125,  0.105 } // 5 - 10 GeV
                                           ,{ 0.075,  0.075, 0.065,  0.065,  0.065,  0.055,  0.080,  0.080,  0.065,  0.050 } // 10 - 15 GeV
                                           ,{ 0.055,  0.055, 0.045,  0.045,  0.045,  0.040,  0.055,  0.055,  0.050,  0.040 } // 15 - 20 GeV
                                           ,{ 0.038,  0.038, 0.032,  0.032,  0.032,  0.026,  0.040,  0.040,  0.035,  0.030 } // 20 - 30 GeV
                                           ,{ 0.025,  0.025, 0.022,  0.022,  0.022,  0.019,  0.030,  0.030,  0.025,  0.020 } // 30 - 40 GeV
                                           ,{ 0.025,  0.025, 0.021,  0.022,  0.021,  0.019,  0.028,  0.028,  0.023,  0.020 } // 40 - 50 GeV
                                           ,{ 0.025,  0.025, 0.021,  0.022,  0.021,  0.019,  0.028,  0.028,  0.023,  0.020 } // 50 - 60 GeV
                                           ,{ 0.025,  0.025, 0.021,  0.022,  0.021,  0.019,  0.028,  0.028,  0.023,  0.020 } // 60 - 70 GeV
                                           ,{ 0.025,  0.025, 0.021,  0.022,  0.021,  0.019,  0.028,  0.028,  0.023,  0.020 } // 70 - 80 GeV
                                           ,{ 0.025,  0.025, 0.021,  0.022,  0.021,  0.019,  0.028,  0.028,  0.023,  0.020 } }; // 80 - inf GeV
    if(etabin == 3 || etabin == 4){
        if (rhad > cutrhad[etbin][etabin])
            return false;
    } else{
        if(rhad1 > cutrhad[etbin][etabin])
            return false;
    }
    return true;
}
bool MultiLeptonMenu::passF3(double f3, unsigned int etbin, unsigned int etabin) const 
{

    //                             0.0     0.1       0.6       0.8    1.15      1.37     1.52    1.81    2.01     2.37     2.47
    static const double cutf3[11][10] = {{  0.0593 , 0.0593 , 0.0540 , 0.0430 , 0.0481 ,  9999 , 0.0363 , 0.0391 , 0.0420 , 9999 } // 0 - 5 GeV
                                         ,{ 0.0377 , 0.0377 , 0.0356 , 0.0327 , 0.0365 ,  9999 , 0.0275 , 0.0315 , 0.0360 , 9999 } // 5 - 10 GeV
                                         ,{ 0.0279 , 0.0279 , 0.0261 , 0.0239 , 0.0267 ,  9999 , 0.0217 , 0.0261 , 0.0270 , 9999 } // 10 - 15 GeV
                                         ,{ 0.0259 , 0.0259 , 0.0219 , 0.0211 , 0.0239 ,  9999 , 0.0203 , 0.0253 , 0.0270 , 9999 } // 15 - 20 GeV
                                         ,{ 0.0252 , 0.0252 , 0.0199 , 0.0196 , 0.0225 ,  9999 , 0.0207 , 0.0261 , 0.0270 , 9999 } // 20 - 30 GeV
                                         ,{ 0.0259 , 0.0259 , 0.0197 , 0.0193 , 0.0215 ,  9999 , 0.0223 , 0.0274 , 0.0270 , 9999 } // 30 - 40 GeV
                                         ,{ 0.0265 , 0.0265 , 0.0201 , 0.0201 , 0.0222 ,  9999 , 0.0240 , 0.0291 , 0.0290 , 9999 } // 40 - 50 GeV
                                         ,{ 0.0265 , 0.0265 , 0.0201 , 0.0201 , 0.0222 ,  9999 , 0.0240 , 0.0291 , 0.0290 , 9999 } // 50 - 60 GeV
                                         ,{ 0.0292 , 0.0292 , 0.0219 , 0.0215 , 0.0241 ,  9999 , 0.0264 , 0.0327 , 0.0315 , 9999 } // 60 - 70 GeV
                                         ,{ 0.0292 , 0.0292 , 0.0219 , 0.0215 , 0.0241 ,  9999 , 0.0264 , 0.0327 , 0.0315 , 9999 } // 70 - 80 GeV
                                         ,{  9999  ,  9999  ,  9999  ,  9999  ,  9999  ,  9999 ,  9999  ,  9999  ,  9999  , 9999 } }; // 80 - inf GeV

    if(f3 > cutf3[etbin][etabin]) return false;
    return true;
}

bool MultiLeptonMenu::passReta(double reta, unsigned int etbin, unsigned int etabin) const
{
    //                                    0.0     0.1      0.6       0.8     1.15      1.37     1.52     1.81     2.01     2.37     2.47
    static const double cutReta37[11][10] = {{    0.600 ,  0.600 ,  0.600 ,  0.600 ,  0.650 ,  0.650 ,  0.700 ,  0.690 ,  0.690 ,  0.690 }    // 0 - 5 GeV
                                             , {  0.750 ,  0.750 ,  0.730 ,  0.730 ,  0.735 ,  0.700 ,  0.735 ,  0.735 ,  0.775 ,  0.775 }    // 5 - 10 GeV
                                             , {  0.827 ,  0.827 ,  0.804 ,  0.826 ,  0.770 ,  0.700 ,  0.770 ,  0.802 ,  0.830 ,  0.830 }    // 10 - 15 GeV
                                             , {  0.863 ,  0.863 ,  0.845 ,  0.826 ,  0.770 ,  0.700 ,  0.813 ,  0.847 ,  0.853 ,  0.853 }    // 15 - 20 GeV
                                             , {  0.893 ,  0.893 ,  0.878 ,  0.864 ,  0.839 ,  0.700 ,  0.851 ,  0.873 ,  0.879 ,  0.878 }    // 20 - 30 GeV
                                             , {  0.893 ,  0.893 ,  0.878 ,  0.864 ,  0.839 ,  0.700 ,  0.851 ,  0.873 ,  0.879 ,  0.878 }    // 30 - 40 GeV
                                             , {  0.917 ,  0.917 ,  0.908 ,  0.900 ,  0.888 ,  0.700 ,  0.883 ,  0.898 ,  0.898 ,  0.896 }    // 40 - 50 GeV
                                             , {  0.917 ,  0.917 ,  0.908 ,  0.900 ,  0.888 ,  0.700 ,  0.883 ,  0.898 ,  0.898 ,  0.896 }    // 50 - 60 GeV
                                             , {  0.917 ,  0.917 ,  0.908 ,  0.900 ,  0.888 ,  0.700 ,  0.883 ,  0.898 ,  0.898 ,  0.896 }    // 60 - 70 GeV
                                             , {  0.917 ,  0.917 ,  0.908 ,  0.900 ,  0.888 ,  0.700 ,  0.883 ,  0.898 ,  0.898 ,  0.896 }    // 70 - 80 GeV
                                             , {  0.917 ,  0.917 ,  0.908 ,  0.900 ,  0.888 ,  0.700 ,  0.883 ,  0.898 ,  0.898 ,  0.896 } }; // 80 - inf GeV
  
    if(reta < cutReta37[etbin][etabin]) return false;
    return true;
}

bool MultiLeptonMenu::passW2(double w2, unsigned int etbin, unsigned int etabin) const
{

    //                                  0.0       0.1      0.6     0.8       1.15      1.37    1.52     1.81      2.01      2.37     2.47
    static const double cutWeta2[11][10] = { {   0.0166 , 0.0166 , 0.0172 , 0.0167 , 0.0170 , 0.0385 , 0.0164 , 0.0152 , 0.0156 , 0.0157 }   // 0 - 5 GeV
                                             , { 0.0145 , 0.0145 , 0.0152 , 0.0154 , 0.0158 , 0.0347 , 0.0159 , 0.0140 , 0.0150 , 0.0150 }   // 5 - 10 GeV
                                             , { 0.0129 , 0.0129 , 0.0137 , 0.0141 , 0.0146 , 0.0311 , 0.0151 , 0.0133 , 0.0140 , 0.0140 }   // 10 - 15 GeV
                                             , { 0.0122 , 0.0122 , 0.0129 , 0.0133 , 0.0139 , 0.0278 , 0.0145 , 0.0128 , 0.0140 , 0.0140 }   // 15 - 20 GeV
                                             , { 0.0117 , 0.0117 , 0.0123 , 0.0126 , 0.0131 , 0.0257 , 0.0139 , 0.0124 , 0.0135 , 0.0135 }   // 20 - 30 GeV
                                             , { 0.0117 , 0.0117 , 0.0123 , 0.0126 , 0.0131 , 0.0257 , 0.0139 , 0.0124 , 0.0135 , 0.0135 }   // 30 - 40 GeV
                                             , { 0.0112 , 0.0112 , 0.0118 , 0.0121 , 0.0125 , 0.0247 , 0.0132 , 0.0120 , 0.0130 , 0.0135 }   // 40 - 50 GeV
                                             , { 0.0112 , 0.0112 , 0.0118 , 0.0121 , 0.0125 , 0.0247 , 0.0132 , 0.0120 , 0.0130 , 0.0135 }   // 50 - 60 GeV
                                             , { 0.0112 , 0.0112 , 0.0118 , 0.0121 , 0.0125 , 0.0247 , 0.0132 , 0.0120 , 0.0130 , 0.0135 }   // 60 - 70 GeV
                                             , { 0.0112 , 0.0112 , 0.0118 , 0.0121 , 0.0125 , 0.0247 , 0.0132 , 0.0120 , 0.0130 , 0.0135 }   // 70 - 80 GeV
                                             , { 0.0112 , 0.0112 , 0.0118 , 0.0121 , 0.0125 , 0.0247 , 0.0132 , 0.0120 , 0.0130 , 0.0135 } };// 80 - inf GeV

    if(w2 > cutWeta2[etbin][etabin]) return false;    
    return  true;
}

bool MultiLeptonMenu::passWstot(double wstot, unsigned int etbin, unsigned int etabin) const 
{
    //                                       0.0     0.1      0.6       0.8       1.15      1.37      1.52      1.81      2.01      2.37     2.47
    static const double cutWstot[11][10] = { {   3.926,   3.926,   4.069,   4.501,   4.986,   9999,   4.650,   3.190,   1.966,   9999 }    // 0 - 5 GeV
                                             , { 3.296,   3.296,   3.427,   3.936,   4.309,   9999,   4.313,   2.845,   1.818,   9999 }    // 5 - 10 GeV
                                             , { 3.095,   3.095,   3.202,   3.708,   4.095,   9999,   3.968,   2.692,   1.754,   9999 }    // 10 - 15 GeV
                                             , { 3.035,   3.035,   3.129,   3.553,   3.941,   9999,   3.758,   2.555,   1.714,   9999 }    // 15 - 20 GeV
                                             , { 3.035,   3.035,   3.129,   3.508,   3.793,   9999,   3.609,   2.505,   1.703,   9999 }    // 20 - 30 GeV
                                             , { 2.881,   2.881,   2.941,   3.319,   3.506,   9999,   3.380,   2.381,   1.644,   9999 }    // 30 - 40 GeV
                                             , { 2.881,   2.881,   2.941,   3.319,   3.506,   9999,   3.380,   2.381,   1.644,   9999 }    // 40 - 50 GeV
                                             , { 2.881,   2.881,   2.941,   3.319,   3.506,   9999,   3.380,   2.381,   1.644,   9999 }    // 50 - 60 GeV
                                             , { 2.881,   2.881,   2.941,   3.319,   3.506,   9999,   3.380,   2.381,   1.644,   9999 }    // 60 - 70 GeV
                                             , { 2.881,   2.881,   2.941,   3.319,   3.506,   9999,   3.380,   2.381,   1.644,   9999 }    // 70 - 80 GeV
                                             , { 2.881,   2.881,   2.941,   3.319,   3.506,   9999,   3.380,   2.381,   1.644,   9999 } }; // 80 - inf GeV

    if(wstot > cutWstot[etbin][etabin]) return false;
    return true;

}
bool MultiLeptonMenu::passEratio(double DEmaxs1, unsigned int etbin, unsigned int etabin) const 
{  
    //                                           0.0     0.1      0.6      0.8      1.15      1.37    1.52     1.81    2.01    2.37    2.47
    static const double cutDEmaxs1[11][10] = { {    0.278 ,  0.278 ,  0.150 ,  0.150 ,  0.250 , -9999 ,  0.100 ,  0.136 ,  0.492 , -9999 }    // 0 - 5 GeV
                                               , {  0.506 ,  0.506 ,  0.320 ,  0.281 ,  0.250 , -9999 ,  0.250 ,  0.281 ,  0.543 , -9999 }    // 5 - 10 GeV
                                               , {  0.587 ,  0.587 ,  0.509 ,  0.420 ,  0.335 , -9999 ,  0.335 ,  0.369 ,  0.616 , -9999 }    // 10 - 15 GeV
                                               , {  0.591 ,  0.591 ,  0.556 ,  0.420 ,  0.335 , -9999 ,  0.335 ,  0.369 ,  0.639 , -9999 }    // 15 - 20 GeV
                                               , {  0.627 ,  0.627 ,  0.617 ,  0.420 ,  0.335 , -9999 ,  0.417 ,  0.505 ,  0.653 , -9999 }    // 20 - 30 GeV
                                               , {  0.627 ,  0.627 ,  0.617 ,  0.420 ,  0.335 , -9999 ,  0.417 ,  0.505 ,  0.653 , -9999 }    // 30 - 40 GeV
                                               , {  0.627 ,  0.627 ,  0.617 ,  0.420 ,  0.335 , -9999 ,  0.417 ,  0.505 ,  0.653 , -9999 }    // 40 - 50 GeV
                                               , {  0.627 ,  0.627 ,  0.617 ,  0.420 ,  0.335 , -9999 ,  0.417 ,  0.505 ,  0.653 , -9999 }    // 50 - 60 GeV
                                               , {  0.627 ,  0.627 ,  0.617 ,  0.420 ,  0.335 , -9999 ,  0.417 ,  0.505 ,  0.653 , -9999 }    // 60 - 70 GeV
                                               , {  0.627 ,  0.627 ,  0.617 ,  0.420 ,  0.335 , -9999 ,  0.417 ,  0.505 ,  0.653 , -9999 }    // 70 - 80 GeV
                                               , {  0.627 ,  0.627 ,  0.617 ,  0.420 ,  0.335 , -9999 ,  0.417 ,  0.505 ,  0.653 , -9999 } }; // 80 -    GeV

    if(DEmaxs1 < cutDEmaxs1[etbin][etabin]) return false;  
    return  true;
}

bool MultiLeptonMenu::passDeltaEta(double deltaEta, unsigned int etbin, unsigned int etabin) const
{

    //                                        0.0     0.1      0.6      0.8      1.15      1.37    1.52     1.81    2.01    2.37    2.47
    static const double cutDeltaEta[11][10]  = {{0.017,   0.017,   0.020,   0.020,   0.020,   0.020,   0.020,   0.020,   0.020,   0.020}, // 0 - 5 GeV   
                                                {0.012,   0.009,   0.009,   0.011,   0.013,   0.014,   0.013,   0.011,   0.011,   0.014}, // 5 - 10 GeV  
                                                {0.012,   0.009,   0.008,   0.009,   0.009,   0.013,   0.010,   0.010,   0.008,   0.013}, // 10 - 15 GeV 
                                                {0.011,   0.008,   0.007,   0.007,   0.009,   0.013,   0.009,   0.007,   0.007,   0.011}, // 15 - 20 GeV 
                                                {0.011,   0.008,   0.007,   0.007,   0.009,   0.013,   0.009,   0.007,   0.007,   0.011}, // 20 - 30 GeV 
                                                {0.011,   0.008,   0.007,   0.007,   0.009,   0.013,   0.009,   0.007,   0.007,   0.011}, // 30 - 40 GeV 
                                                {0.011,   0.008,   0.007,   0.007,   0.009,   0.013,   0.009,   0.007,   0.007,   0.011}, // 40 - 50 GeV 
                                                {0.011,   0.008,   0.007,   0.007,   0.009,   0.013,   0.009,   0.007,   0.007,   0.011}, // 50 - 60 GeV 
                                                {0.011,   0.008,   0.007,   0.007,   0.009,   0.013,   0.009,   0.007,   0.007,   0.011}, // 60 - 70 GeV 
                                                {0.011,   0.008,   0.007,   0.007,   0.009,   0.013,   0.009,   0.007,   0.007,   0.011}, // 70 - 80 GeV 
                                                {0.011,   0.008,   0.007,   0.007,   0.009,   0.013,   0.009,   0.007,   0.007,   0.011}};// 80 - inf GeV 

    if (fabs(deltaEta) > cutDeltaEta[etbin][etabin]) return false;  
    return true;


}
bool MultiLeptonMenu::passDeltaPhiRes(double deltaPhiRes, bool isBrem, unsigned int etbin, unsigned int etabin) const
{

    //                                             0.0      0.1  x    0.6      0.8  x   1.15    1.37     1.52   x 1.81    2.01  x 2.37     2.47   
    static const double maxDeltaPhiResHigh[11][10]= {{0.083,   0.083,   0.071,   0.050,   0.043,   0.048,   0.047,   0.038,   0.032,   0.044}, // 0 - 5 GeV   
                                                     {0.038,   0.030,   0.028,   0.023,   0.023,   0.028,   0.023,   0.023,   0.023,   0.038}, // 5 - 10 GeV  
                                                     {0.020,   0.015,   0.013,   0.013,   0.020,   0.023,   0.020,   0.018,   0.023,   0.033}, // 10 - 15 GeV 
                                                     {0.017,   0.015,   0.013,   0.013,   0.018,   0.018,   0.018,   0.018,   0.023,   0.028}, // 15 - 20 GeV 
                                                     {0.017,   0.015,   0.013,   0.013,   0.018,   0.018,   0.018,   0.018,   0.023,   0.028}, // 20 - 30 GeV 
                                                     {0.017,   0.015,   0.013,   0.013,   0.018,   0.018,   0.018,   0.018,   0.023,   0.028}, // 30 - 40 GeV 
                                                     {0.017,   0.015,   0.013,   0.013,   0.018,   0.018,   0.018,   0.018,   0.023,   0.028}, // 40 - 50 GeV 
                                                     {0.017,   0.015,   0.013,   0.013,   0.018,   0.018,   0.018,   0.018,   0.023,   0.028}, // 50 - 60 GeV 
                                                     {0.017,   0.015,   0.013,   0.013,   0.018,   0.018,   0.018,   0.018,   0.023,   0.028}, // 60 - 70 GeV 
                                                     {0.017,   0.015,   0.013,   0.013,   0.018,   0.018,   0.018,   0.018,   0.023,   0.028}, // 70 - 80 GeV 
                                                     {0.017,   0.015,   0.013,   0.013,   0.018,   0.018,   0.018,   0.018,   0.023,   0.028}};// 80 
    //                                             0.0      0.1      0.6       0.8     1.15      1.37     1.52      1.81     2.01    2.37     2.47   
    static const double minDeltaPhiResHigh[11][10]= {{-0.100,  -0.100,  -0.100,  -0.100,  -0.115,  -0.120,  -0.090,  -0.735,  -0.050,  -0.038},// 0 - 5 GeV   
                                                     {-0.086,  -0.078,  -0.078,  -0.078,  -0.083,  -0.053,  -0.048,  -0.028,  -0.023,  -0.023},// 5 - 10 GeV  
                                                     {-0.038,  -0.038,  -0.038,  -0.043,  -0.047,  -0.038,  -0.028,  -0.023,  -0.014,  -0.017},// 10 - 15 GeV 
                                                     {-0.032,  -0.032,  -0.032,  -0.032,  -0.032,  -0.032,  -0.029,  -0.014,  -0.014,  -0.014},// 15 - 20 GeV 
                                                     {-0.032,  -0.032,  -0.032,  -0.032,  -0.032,  -0.032,  -0.026,  -0.014,  -0.014,  -0.014},// 20 - 30 GeV 
                                                     {-0.032,  -0.032,  -0.032,  -0.032,  -0.032,  -0.032,  -0.026,  -0.014,  -0.014,  -0.014},// 30 - 34 GeV 
                                                     {-0.032,  -0.032,  -0.032,  -0.032,  -0.032,  -0.032,  -0.026,  -0.014,  -0.014,  -0.014},// 34 - 50 GeV 
                                                     {-0.032,  -0.032,  -0.032,  -0.032,  -0.032,  -0.032,  -0.026,  -0.014,  -0.014,  -0.014},// 50 - 60 GeV 
                                                     {-0.032,  -0.032,  -0.032,  -0.032,  -0.032,  -0.032,  -0.026,  -0.014,  -0.014,  -0.014},// 60 - 70 GeV 
                                                     {-0.032,  -0.032,  -0.032,  -0.032,  -0.032,  -0.032,  -0.026,  -0.014,  -0.014,  -0.014},// 70 - 80 GeV 
                                                     {-0.032,  -0.032,  -0.032,  -0.032,  -0.032,  -0.032,  -0.026,  -0.014,  -0.014,  -0.014}};// 80
  
    //                                            0.0      0.1      0.6       0.8     1.15      1.37     1.52      1.81     2.01    2.37     2.47   
    static const double maxDeltaPhiResLow[11][10] = {{0.100,   0.100,   0.100,   0.075,   0.075,   0.080,   0.075,   0.060,   0.045,   0.070}, // 0 - 5 GeV   
                                                     {0.038,   0.038,   0.038,   0.023,   0.027,   0.038,   0.028,   0.028,   0.028,   0.068}, // 5 - 10 GeV  
                                                     {0.020,   0.017,   0.018,   0.020,   0.020,   0.026,   0.023,   0.023,   0.023,   0.062}, // 10 - 15 GeV 
                                                     {0.017,   0.017,   0.017,   0.018,   0.018,   0.018,   0.020,   0.022,   0.031,   0.053}, // 15 - 20 GeV 
                                                     {0.017,   0.017,   0.017,   0.018,   0.018,   0.018,   0.020,   0.022,   0.031,   0.053}, // 20 - 30 GeV 
                                                     {0.017,   0.017,   0.017,   0.018,   0.018,   0.018,   0.020,   0.022,   0.031,   0.053}, // 30 - 40 GeV 
                                                     {0.017,   0.017,   0.017,   0.018,   0.018,   0.018,   0.020,   0.022,   0.031,   0.053}, // 40 - 50 GeV 
                                                     {0.017,   0.017,   0.017,   0.018,   0.018,   0.018,   0.020,   0.022,   0.031,   0.053}, // 50 - 60 GeV 
                                                     {0.017,   0.017,   0.017,   0.018,   0.018,   0.018,   0.020,   0.022,   0.031,   0.053}, // 60 - 70 GeV 
                                                     {0.017,   0.017,   0.017,   0.018,   0.018,   0.018,   0.020,   0.022,   0.031,   0.053}, // 70 - 80 GeV 
                                                     {0.017,   0.017,   0.017,   0.018,   0.018,   0.018,   0.020,   0.022,   0.031,   0.053}};// 80
    //                                        0.0      0.1      0.6       0.8     1.15     1.37     1.52      1.81     2.01    2.37     2.47   
    static const double minDeltaPhiResLow[11][10]= {{-0.100,  -0.100,  -0.100,  -0.100,  -0.095,  -0.080,  -0.070,  -0.060,  -0.045,  -0.035}, // 0 - 5 GeV   
                                                    {-0.074,  -0.068,  -0.068,  -0.071,  -0.057,  -0.048,  -0.038,  -0.026,  -0.011,  -0.020}, // 5 - 10 GeV  
                                                    {-0.041,  -0.028,  -0.028,  -0.038,  -0.028,  -0.028,  -0.020,  -0.011,  -0.011,  -0.011}, // 10 - 15 GeV 
                                                    {-0.023,  -0.023,  -0.023,  -0.023,  -0.023,  -0.023,  -0.020,  -0.011,  -0.011,  -0.011}, // 15 - 20 GeV 
                                                    {-0.023,  -0.023,  -0.023,  -0.023,  -0.023,  -0.023,  -0.020,  -0.011,  -0.011,  -0.011}, // 20 - 25 GeV 
                                                    {-0.023,  -0.023,  -0.023,  -0.023,  -0.023,  -0.023,  -0.020,  -0.011,  -0.011,  -0.011}, // 25 - 40 GeV 
                                                    {-0.023,  -0.023,  -0.023,  -0.023,  -0.023,  -0.023,  -0.020,  -0.011,  -0.011,  -0.011}, // 40 - 50 GeV 
                                                    {-0.023,  -0.023,  -0.023,  -0.023,  -0.023,  -0.023,  -0.020,  -0.011,  -0.011,  -0.011}, // 50 - 60 GeV 
                                                    {-0.023,  -0.023,  -0.023,  -0.023,  -0.023,  -0.023,  -0.020,  -0.011,  -0.011,  -0.011}, // 60 - 70 GeV 
                                                    {-0.023,  -0.023,  -0.023,  -0.023,  -0.023,  -0.023,  -0.020,  -0.011,  -0.011,  -0.011}, // 70 - 80 GeV 
                                                    {-0.023,  -0.023,  -0.023,  -0.023,  -0.023,  -0.023,  -0.020,  -0.011,  -0.011,  -0.011}};// 80   
    if(isBrem){
        if(deltaPhiRes < minDeltaPhiResHigh[etbin][etabin] || deltaPhiRes > maxDeltaPhiResHigh[etbin][etabin]) return false;
    }
    if(!isBrem){
        if(deltaPhiRes < minDeltaPhiResLow[etbin][etabin] || deltaPhiRes > maxDeltaPhiResLow[etbin][etabin]) return false;
    }
    return true;
}
bool MultiLeptonMenu::passTR(double TRratio, double eta, unsigned int  nTRTTotal ) const
{

    if (fabs(eta)>1.37 && fabs(eta)<1.52 ){

        return (nTRTTotal >10 && TRratio > 0.1);
    }
    return true; 
}


unsigned int MultiLeptonMenu::getEtaBinH4l(double eta) const
{

    const unsigned int nEtaBins = 10;
    static const double etabins[nEtaBins] = {0.1,0.6,0.8,1.15,1.37,1.52,1.81,2.01,2.37,2.47}; 
    for(unsigned int etabin = 0; etabin < nEtaBins; ++etabin){
        if(fabs(eta) < etabins[etabin])
            return etabin;
    }
    return 9;
}

unsigned int MultiLeptonMenu::getEtBinH4l(double eT) const 
{
    const unsigned int nEtBins = 10;
    static const double etbins[nEtBins] = {5*GeV,10*GeV,15*GeV,20*GeV,30*GeV,40*GeV,50*GeV,60*GeV,70*GeV,80*GeV};
  
    for(unsigned int etbin = 0; etbin < nEtBins; ++etbin){
        if(eT < etbins[etbin])
            return etbin;
    }
  
    return 10;
}

bool MultiLeptonMenu::getBremCategoryH4l(double dpOverp, unsigned int etbin, unsigned int etabin) const
{

    //                                      0.0    0.1    0.6    0.8    1.15   1.37   1.52   1.81   2.01   2.37    2.47
    static const double bremThresholds[11][10] = {{0.098, 0.098, 0.154, 0.270, 0.306, 0.422, 0.482, 0.606, 0.306, 0.382}, // 0-5 GeV
                                                  {0.110, 0.110, 0.178, 0.374, 0.410, 0.478, 0.610, 0.658, 0.314, 0.410}, // 5-10 GeV
                                                  {0.118, 0.118, 0.194, 0.430, 0.438, 0.502, 0.642, 0.674, 0.322, 0.434}, // 10-15 GeV
                                                  {0.122, 0.122, 0.202, 0.438, 0.458, 0.538, 0.678, 0.722, 0.330, 0.440}, // 15-20 GeV
                                                  {0.142, 0.142, 0.226, 0.506, 0.574, 0.586, 0.714, 0.730, 0.338, 0.462}, // 20-30 GeV
                                                  {0.242, 0.242, 0.362, 0.654, 0.674, 0.630, 0.798, 0.806, 0.362, 0.490}, // 30-40 GeV
                                                  {0.242, 0.242, 0.362, 0.654, 0.674, 0.630, 0.798, 0.806, 0.362, 0.490}, // 40-50 GeV
                                                  {0.242, 0.242, 0.362, 0.654, 0.674, 0.630, 0.798, 0.806, 0.362, 0.490}, // 50-60 GeV
                                                  {0.242, 0.242, 0.362, 0.654, 0.674, 0.630, 0.798, 0.806, 0.362, 0.490}, // 60-70 GeV
                                                  {0.242, 0.242, 0.362, 0.654, 0.674, 0.630, 0.798, 0.806, 0.362, 0.490}, // 70-80 GeV
                                                  {0.242, 0.242, 0.362, 0.654, 0.674, 0.630, 0.798, 0.806, 0.362, 0.490}};// >80 GeV
	
    if(dpOverp < bremThresholds[etbin][etabin]) return false; // Low-brem electron
    return true; // High-brem electron
}


void MultiLeptonMenu::printMask(unsigned int mask) const
{

    if (!mask) {
        std::cout << "MultiLepton: all cuts OK" << std::endl;
        return;
    }
    if (mask & (0x1 << CoverageBit)) std::cout << "MultiLepton: Failed Coverage" << std::endl;
    if (mask & (0x1 << SiliconBit)) std::cout << "MultiLepton: Failed Silicon" << std::endl;
    if (mask & (0x1 << PixelBit)) std::cout << "MultiLepton: Failed Pixel" << std::endl;
    if (mask & (0x1 << BlayerBit)) std::cout << "MultiLepton: Failed Blayer" << std::endl;
    if (mask & (0x1 << RhadBit)) std::cout << "MultiLepton: Failed Rhad" << std::endl;
    if (mask & (0x1 << F3Bit)) std::cout << "MultiLepton: Failed F3" << std::endl;
    if (mask & (0x1 << RetaBit)) std::cout << "MultiLepton: Failed Reta" << std::endl;
    if (mask & (0x1 << W2Bit)) std::cout << "MultiLepton: Failed W2" << std::endl;
    if (mask & (0x1 << WstotBit)) std::cout << "MultiLepton: Failed Wstot" << std::endl;
    if (mask & (0x1 << EratioBit)) std::cout << "MultiLepton: Failed Eratio" << std::endl;
    if (mask & (0x1 << DeltaEtaBit)) std::cout << "MultiLepton: Failed DeltaEta" << std::endl;
    if (mask & (0x1 << DeltaPhiResBit)) std::cout << "MultiLepton: Failed DeltaPhiRes" << std::endl;
    if (mask & (0x1 << TRBit)) std::cout << "MultiLepton: Failed TR" << std::endl;
}

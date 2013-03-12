#include "egammaAnalysisUtils/ShowerDepthTool.h"

#include "TFile.h"
#include "TH1.h"
#include "TSystem.h"
#include <iostream>
#include <math.h>

using namespace std;

ShowerDepthTool::ShowerDepthTool(TString dataFile, TString mcFile,
  TString dataHistoName, TString mcHistoName) :
  m_hData(0), m_hMC(0)
{
  gSystem->ExpandPathName(dataFile);
  m_hData = getHistoFromFile(dataFile, dataHistoName);
  
  gSystem->ExpandPathName(mcFile);
  m_hMC = getHistoFromFile(mcFile, mcHistoName);
}

ShowerDepthTool::~ShowerDepthTool()
{
  delete m_hData;
  delete m_hMC;
}

/** Return the shower depth on sampling 1 given etas1. From:
https://svnweb.cern.ch/trac/atlasoff/browser/Calorimeter/CaloDetDescr/trunk/src/CaloDepthTool.cxx#L347 **/
float ShowerDepthTool::getShowerDepthEM1(float etas1)
{
  float radius, aetas1 = fabs(etas1);
  if (aetas1 < 0.8)
    radius = (1558.859292 - 4.990838*aetas1 - 21.144279*aetas1*aetas1);
  else if (aetas1<1.5)
    radius = (1522.775373 + 27.970192*aetas1 - 21.104108*aetas1*aetas1);
  else
    radius = 3790.671754;
  if (etas1 < 0. and aetas1 > 1.5)
    return -radius;
  return radius;
}

/** Return the shower depth on sampling 1 given etas1. From:
https://svnweb.cern.ch/trac/atlasoff/browser/Calorimeter/CaloDetDescr/trunk/src/CaloDepthTool.cxx#L347 **/
float ShowerDepthTool::getShowerDepthEM2(float etas2)
{
  float radius, aetas2 = fabs(etas2);
  if (aetas2 < 0.8)
    radius = (1698.990944 - 49.431767*aetas2 - 24.504976*aetas2*aetas2);
  else if (aetas2 < 1.5)
    radius = (8027.574119 - 2717.653528*aetas2);
  else
    radius = (3473.473909 + 453.941515*aetas2 - 119.101945*aetas2*aetas2);
  if (etas2 < 0. and aetas2 > 1.5)
    return -radius;
  return radius;
}


float ShowerDepthTool::getCorrectedEtaDirection(float zvertex, 
                                                float eta,
                                                float phi, 
                                                bool isData,
                                                int sampling)
{
  std::pair<float, float> RZ = getCorrectedRZ(eta, phi, isData, sampling);
  return getEtaDirection(zvertex, RZ.first, RZ.second);
}

std::pair<float,float> ShowerDepthTool::getRZ(float eta, int sampling)
{
  if (sampling != 1 && sampling != 2)
  {
    cout << "Invalid sampling: " << sampling << endl;
    return std::make_pair<float, float>(0., 0.);
  }
  float depth = (sampling == 1 ? getShowerDepthEM1(eta) : getShowerDepthEM2(eta) );
  if (fabs(eta) <  1.5)
    return std::make_pair<float, float>( depth, depth*sinh(eta) );
  return std::make_pair<float, float>( depth/sinh(eta), depth );
}



std::pair<float, float> ShowerDepthTool::getCorrectedRZ(float eta, 
                                                        float phi,
                                                        bool isData,
                                                        int sampling)
{
  if (sampling != 1 && sampling != 2)
  {
    cout << "Invalid sampling: " << sampling << endl;
    return std::make_pair<float, float>(0., 0.);
  }
  float depth = (sampling == 1 ? getCorrectedShowerDepthEM1(eta, phi, isData) :
    getCorrectedShowerDepthEM2(eta, phi, isData) );
  if (fabs(eta) <  1.5)
    return std::make_pair<float, float>( depth, depth*sinh(eta) );
  return std::make_pair<float, float>( depth/sinh(eta), depth );
}


/** Return the calorimeter displacement in R(Z) for barrel (endcap) **/
float ShowerDepthTool::getRZCorrection(float eta, float phi, bool isData)
{
  TH1* histo = (isData ? m_hData : m_hMC);
  if (!histo)
    return 0;
  return histo->Interpolate(eta, phi);
}


TH1* ShowerDepthTool::getHistoFromFile(TString fileName, TString histoName)
{
  TFile *f = TFile::Open(fileName);
  if (!f)
  {
    cout << "Invalid file: " << fileName << endl;
    return 0;
  }
  TH1 *h = dynamic_cast<TH1*>( f->Get(histoName) );
  if (!h)
  {
    cout << "Invalid histogram name (" << histoName << ") or type" << endl;
    return 0;
  }
  h->SetDirectory(0);
  return h;
}

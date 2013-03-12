#ifndef egammaOQ_h
#define egammaOQ_h

//#include "TROOT.h"
#include "TString.h"
#include "TFile.h"
#include "TH2I.h"
#include "TNamed.h"

#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

class egammaOQ {
 
 private:
  vector<double> m_LumiVec;
  vector<double> m_RunFracMC;

 public:

  egammaOQ( string name = "egammaOQ");
  virtual ~egammaOQ();
  
  int    setLumiVec(double Per1,double Per2,double Per3,double Per4) ;
  double getOQWeight(int runumber) const;
  int    deadRegionS2(double myEta, double myPhi, double deltaEta, double deltaPhi, int candidate, bool verbose=false) const;
  int    checkOQCluster(int runnumber, double myEta, double myPhi, int candidate, bool syst=false, bool verbose=false) const;
  int    checkOQClusterElectron(int runnumber, double myEta, double myPhi, bool syst=false, bool verbose=false) const;
  int    checkOQClusterPhoton(int runnumber, double myEta, double myPhi, bool conv, bool syst=false, bool verbose=false) const;
  int    checkOQCluster(double myEta, double myPhi, int NetaCells, int NphiCells, int candidate, bool verbose=false) const;

  #ifdef ROOTCORE
  ClassDef(egammaOQ,1)
  #endif 
   

};

#endif

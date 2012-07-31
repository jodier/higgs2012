#include "egammaAnalysisUtils/FsrPhotons.h"
#include <algorithm>
#include <cmath>


using namespace std;

FsrPhotons::FsrPhotons() {

  //DO NOT CHANGE: cuts to be used for FSR photon selection
  HIGHETMIN=3500.;//to select egamma Photon with Et>3.5GeV
  OVERLAP=0.01;
  OVERLAPELMU=0.001;

}

FsrPhotons::~FsrPhotons() { }


vector<FsrPhotons::FsrCandidate>* FsrPhotons::getFsrPhotons(float mueta, float muphi, float muidtheta, float muidphi,  vector<float> *pheta, vector<float> *phphi, vector<float> *phEt, vector<float> *phf1, vector<int> *phauthor, vector<float> *eleta, vector<float> *elphi, vector<float> *elEt, vector<float> *elf1, vector<float>* eltracktheta, vector<float>* eltrackphi, double DRCUT, double ETCUT, double F1CUT) {

  // pair.first : ph index; pair.second: dR
  vector< pair <unsigned int,double> > phfsr;
  phfsr.clear();

  // Loop over photon candidates and choose the FSR photons
  for (unsigned int pindx=0; pindx < (unsigned int) pheta->size(); pindx++ ) {
    if(( ((phauthor->at(pindx)==4) || (phauthor->at(pindx)==16)) && (phEt->at(pindx) > HIGHETMIN) && (phEt->at(pindx) > ETCUT) && (phf1->at(pindx) > F1CUT) )||( ((phauthor->at(pindx)==128) ) && (phEt->at(pindx) > ETCUT) && (phf1->at(pindx) > F1CUT) && (phEt->at(pindx) <= HIGHETMIN) )  ) {
      double dr = deltaR(mueta, muphi, pheta->at(pindx), phphi->at(pindx));
      // ph_cl_eta/phi should be used in duplicate
      if (dr < DRCUT) {
	phfsr.push_back(make_pair(pindx, dr));
      }
    }  
  } 

  // look for fsr photons in electrons
  vector< pair <unsigned int,double> >  elfsr;
  elfsr.clear();
  for (unsigned int eindx=0; eindx < (unsigned int) eleta->size(); eindx++ ) {
    bool isoverlap = (phfsr.size() > 0) && isOverlap(eleta->at(eindx), elphi->at(eindx), &phfsr, pheta, phphi );
    bool elmutrackmatch = (fabs(eltracktheta->at(eindx)-muidtheta)<OVERLAPELMU && fabs(eltrackphi->at(eindx)-muidphi)<OVERLAPELMU);
    if( (!isoverlap) && (elmutrackmatch) && (elEt->at(eindx) > ETCUT) && (elf1->at(eindx) > F1CUT)) {
      double dr = deltaR(mueta, muphi, eleta->at(eindx), elphi->at(eindx));
      // ph_cl_eta/phi should be used in duplicate
      if (dr < DRCUT) {
	elfsr.push_back(make_pair(eindx, dr));
      }
    }
  }
  
  vector<FsrCandidate>* cand = new vector<FsrCandidate>();
  
  for (unsigned int i=0; i < phfsr.size(); i++ ) {
    FsrCandidate c;
    c.container = "photon";
    c.index = phfsr.at(i).first;
    c.deltaR = phfsr.at(i).second;
    cand->push_back(c);
  }
  for (unsigned int i=0; i < elfsr.size(); i++ ) {
    FsrCandidate c;
    c.container = "electron";
    c.index = elfsr.at(i).first;
    c.deltaR = elfsr.at(i).second;
    cand->push_back(c);
  }
  std::sort(cand->begin(), cand->end());

  return cand;
}

bool FsrPhotons::isOverlap(float eleta, float elphi, vector< pair <unsigned int, double> > *phfsr, vector<float>* pheta, vector<float>* phphi) {

  for (unsigned int indx=0; indx < phfsr->size(); indx++ ) {
    int phfsrindex = phfsr->at(indx).first;
    double dr = deltaR(eleta, elphi, pheta->at(phfsrindex), phphi->at(phfsrindex));
    if (dr < OVERLAP) return true;
  }
  return false;
}


double FsrPhotons::deltaR(float meta, float mphi, float peta, float pphi) {

  double deta= fabs(meta - peta);
  double dphi= fabs(mphi - pphi);
  if (dphi > M_PI) dphi=2*M_PI-dphi;
  double dR=sqrt((dphi*dphi)+(deta*deta));
 
  return dR;
}

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


bool
FsrPhotons::getFsrPhotons(float mueta, 
                          float muphi,  
                          float muidtheta, 
                          float muidphi, 
                          std::vector<float>* pheta, 
                          std::vector<float>* phphi, 
                          std::vector<float>* phEt, 
                          std::vector<float>* phf1, 
                          std::vector<int>*   phauthor, 
                          std::vector<float>* eleta, 
                          std::vector<float>* elphi, 
                          std::vector<float>* elEt, 
                          std::vector<float>* elf1,  
                          std::vector<float>* eltracktheta, 
                          std::vector<float>* eltrackphi, 
                          FsrCandidate& candidate)
{

  std::vector<FsrPhotons::FsrCandidate>* cands = getFsrPhotons(mueta, 
                                                               muphi, 
                                                               muidtheta, 
                                                               muidphi, 
                                                               pheta, 
                                                               phphi, 
                                                               phEt, 
                                                               phf1, 
                                                               phauthor, 
                                                               eleta, 
                                                               elphi, 
                                                               elEt, 
                                                               elf1, 
                                                               eltracktheta, 
                                                               eltrackphi);
  if (cands->size() > 0) {
    candidate = cands->at(0);
    return true;
  }
  candidate = FsrCandidate();
  return false;
}



std::vector<FsrPhotons::FsrCandidate>* 
FsrPhotons::getFsrPhotons(float mueta, 
                          float muphi, 
                          float muidtheta, 
                          float muidphi, 
                          std::vector<float> *pheta, 
                          std::vector<float> *phphi, 
                          std::vector<float> *phEt, 
                          std::vector<float> *phf1, 
                          std::vector<int> *phauthor, 
                          std::vector<float> *eleta, 
                          std::vector<float> *elphi, 
                          std::vector<float> *elEt, 
                          std::vector<float> *elf1, 
                          std::vector<float>* eltracktheta, 
                          std::vector<float>* eltrackphi,        
                          double DRCUT, 
                          double DRTOPOCUT, 
                          double ETCUT, 
                          double F1TOPOCUT, 
                          double F1CUT, 
                          std::string option) {

  // pair.first : ph index; pair.second: dR
  std::vector< pair <unsigned int,double> > phfsr;
  phfsr.clear();

  // Loop over photon candidates and choose the FSR photons
  for (unsigned int pindx=0; pindx < (unsigned int) pheta->size(); pindx++ ) {
    if(( ((phauthor->at(pindx)==4) || 
          (phauthor->at(pindx)==16)) && (phEt->at(pindx) > HIGHETMIN) && (phEt->at(pindx) > ETCUT) && (phf1->at(pindx) > F1CUT) ) || 
       ((phauthor->at(pindx)==128) && (phf1->at(pindx) > F1TOPOCUT) && ((ETCUT < phEt->at(pindx)) && (phEt->at(pindx) <= HIGHETMIN)))  ) {
      double dr = deltaR(mueta, muphi, pheta->at(pindx), phphi->at(pindx));
      // ph_cl_eta/phi should be used in duplicate
      if (dr < DRTOPOCUT || (phauthor->at(pindx)!=128 && dr<DRCUT)) {
	phfsr.push_back(make_pair(pindx, dr));
      }
    }  
  }

  // look for fsr photons in electrons
  std::vector< pair <unsigned int,double> >  elfsr;
  elfsr.clear();
  for (unsigned int eindx=0; eindx < (unsigned int) eleta->size(); eindx++ ) {
    bool isoverlap = (phfsr.size() > 0) && isOverlap(eleta->at(eindx), elphi->at(eindx), &phfsr, pheta, phphi );
    bool elmutrackmatch = (fabs(eltracktheta->at(eindx)-muidtheta)<OVERLAPELMU && fabs(eltrackphi->at(eindx)-muidphi)<OVERLAPELMU);
    if( (!isoverlap) && (elmutrackmatch) && (elEt->at(eindx) > ETCUT) && (elEt->at(eindx) > HIGHETMIN) && (elf1->at(eindx) > F1CUT)) {
      double dr = deltaR(mueta, muphi, eleta->at(eindx), elphi->at(eindx));
      // ph_cl_eta/phi should be used in duplicate
      if (dr < DRCUT) {
	elfsr.push_back(make_pair(eindx, dr));
      }
    }
  }
  
  m_fsrPhotons.clear();
  m_fsrPhotons.reserve(phfsr.size() + elfsr.size());
  
  for (unsigned int i=0; i < phfsr.size(); i++ ) {
    FsrCandidate c;
    c.container = "photon";
    c.index     = phfsr.at(i).first;
    c.deltaR    = phfsr.at(i).second;
    c.f1        = phf1->at(c.index);
    c.eta       = pheta->at(c.index);
    c.phi       = phphi->at(c.index);
    c.Et        = phEt->at(c.index);
    if(c.deltaR <0.05) c.Et = phEt->at(c.index)-(400/cosh(pheta->at(c.index)));
    m_fsrPhotons.push_back(c);
  }
  for (unsigned int i=0; i < elfsr.size(); i++ ) {
    FsrCandidate c;
    c.container = "electron";
    c.index     = elfsr.at(i).first;
    c.deltaR    = elfsr.at(i).second;
    c.f1        = elf1->at(c.index);
    c.eta       = eleta->at(c.index);
    c.phi       = elphi->at(c.index);
    c.Et        = elEt->at(c.index);
    if(c.deltaR <0.05) c.Et = elEt->at(c.index)-(400/cosh(eleta->at(c.index)));
    m_fsrPhotons.push_back(c);
  }

  // sort FSR candidates w.r.t min dR or ET
  if (option=="ET") std::sort(m_fsrPhotons.begin(), m_fsrPhotons.end(), compareEt);
  else std::sort(m_fsrPhotons.begin(), m_fsrPhotons.end());

  return &m_fsrPhotons;
}

bool FsrPhotons::isOverlap(float eleta, float elphi, std::vector< pair <unsigned int, double> > *phfsr, std::vector<float>* pheta, std::vector<float>* phphi) {

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

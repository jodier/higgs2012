#ifndef FSRPHOTONS_H
#define FSRPHOTONS_H

#include <iostream>
#include <vector>

/********************************************************************
NAME:     FsrPhotons.cxx
PACKAGE:  ....

AUTHORS:  T. Cuhadar Donszelmann, Xu Da and S. Paganis
CREATED:  July 2011
	
PURPOSE:  Find the possible FSR photons for a given muon 

USAGE:
        FsrPhotons x;
        // by default: dR_CUT=0.15,Et_CUT=1000.0, f1TOPO_CUT=0.2, f1_CUT=0.1 and option="ET"
        // The option is set to "ET",this means the FSR candidates passed the cuts will be ordered w.r.t max ET, 
        // if the option is not set hen the FSR candidates will be ordered w.r.t min dR.
        vector<FsrCandidate>* list = x.getFsrPhotons(muonEta, muonPhi, muonIdtheta, muonIdphi, ph_eta, ph_phi, ph_Et, ph_f1, ph_author, el_cl_eta, el_cl_phi, el_Et, el_f1, el_tracktheta, el_trackphi,double dR_CUT,double Et_CUT, double F1TOPO_CUT, double f1_CUT, option);

        // Two ways to retrieve the best FSR candidate information
        // The old way
        if (list->size()>0) {
             string cname =   list->at(0).container;   // give you which container the candidate is from "photon" or "electron"
             int i        =   list->at(0).index;       // index of the fsr candidate 
             double dr    =   list->at(0).deltaR;      // delta_R between muon and the fsr candidate
             double Et    =   list->at(0).Et;      // delta_R between muon and the fsr candidate
        }
        // or by using inline functions (new)
        if (list->size()>0) {
            string cname =   x->getBestCandidateContainer(list);;  // give you which container the candidate is from "photon" or "electron"
            int i        =   x->getBestCandidateIndex(list);       // index of the fsr candidate 
            double dr    =   x->getBestCandidateDr(list);          // delta_R between muon and the fsr candidate
            double dr    =   x->getBestCandidateEt(list);          // Et of the fsr candidate 
        }
********************************************************************/

#ifdef ROOTCORE
#include "TROOT.h"
#endif

class FsrPhotons {

public :
 
  FsrPhotons(); 
  virtual ~FsrPhotons(); 

  class FsrCandidate {
  public:
      FsrCandidate() : index(-1), deltaR(-1), Et(-1), f1(-1), eta(-1), phi(-1) {}
    std::string container;
    int index;
    double deltaR;
    double Et;
    double f1;
    double eta;
    double phi;
    bool operator<(const FsrCandidate& c) const {
       return deltaR < c.deltaR;    
    }
  };

    bool   getFsrPhotons(float mueta, 
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
                         FsrCandidate& candidate);

  std::vector<FsrCandidate>* getFsrPhotons(float mueta, 
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
                                           double DRCUT = 0.15, 
                                           double DRTOPOCUT = 0.08, 
                                           double ETCUT = 1000.0, 
                                           double F1TOPOCUT = 0.2, 
                                           double F1CUT = 0.1, 
                                           std::string option="ET");


  inline int getBestCandidateIndex(std::vector<FsrPhotons::FsrCandidate>* candidates)
  {
        return candidates->at(0).index;
  }
  inline std::string getBestCandidateContainer(std::vector<FsrPhotons::FsrCandidate>* candidates)
  {
        return candidates->at(0).container;
  }
  inline double getBestCandidateDr(std::vector<FsrPhotons::FsrCandidate>* candidates)
  {
        return candidates->at(0).deltaR;
  }
  inline double getBestCandidateEt(std::vector<FsrPhotons::FsrCandidate>* candidates)
  {
        return candidates->at(0).Et;
  }


  #ifdef ROOTCORE
  ClassDef(FsrPhotons,1)
  #endif

private: 

  double HIGHETMIN;
  double OVERLAP;
  double OVERLAPELMU;
  std::vector<FsrCandidate> m_fsrPhotons;

  bool isOverlap(float eleta, float elphi, std::vector< std::pair<unsigned int, double> >* ph_fsr, std::vector<float> *ph_eta, std::vector<float> *ph_phi);
  double deltaR(float muonEta, float muonPhi, float phEta, float phPhi);
  
  static bool compareEt(FsrCandidate c1, FsrCandidate c2) { return (c1.Et > c2.Et); }

};
#endif

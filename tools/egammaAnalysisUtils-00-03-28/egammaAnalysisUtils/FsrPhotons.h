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
        vector<FsrCandidate>* list = x.getFsrPhotons(muonEta, muonPhi, muonIdtheta, muonIdphi, ph_eta, ph_phi, ph_Et, ph_f1, ph_author, el_cl_eta, el_cl_phi, el_Et, el_f1, el_tracktheta, el_trackphi,double dR_CUT,double Et_CUT, double f1_CUT);//by default: dR_CUT=0.3,Et_CUT=1000.0, f1_CUT=0.15
        if (list->size()>0) {
             string cname =   list->at(0).container;   // give you which container the candidate is from "photon" or "electron"
             int i  =   list->at(0).index;       // index of the fsr candidate 
             double dr  =   list->at(0).deltaR;  // delta_R between muon and the fsr candidate
        }
********************************************************************/

#ifdef ROOTCORE
#include "TROOT.h"
#endif

class FsrPhotons {

public :
 
  FsrPhotons(); 
  virtual ~FsrPhotons(); 

  struct FsrCandidate {
    std::string container;
    int index;
    double deltaR;
    bool operator<(const FsrCandidate& c) const {
       return deltaR < c.deltaR;    
    }
  };

  std::vector<FsrCandidate>* getFsrPhotons(float mueta, float muphi,  float muidtheta, float muidphi, std::vector<float> *pheta, std::vector<float> *phphi, std::vector<float> *phEt, std::vector<float> *phf1, std::vector<int> *phauthor, std::vector<float> *eleta, std::vector<float> *elphi, std::vector<float> *elEt, std::vector<float> *elf1,  std::vector<float>* eltracktheta, std::vector<float>* eltrackphi, double DRCUT = 0.3, double ETCUT = 1000.0, double F1CUT = 0.15);

  #ifdef ROOTCORE
  ClassDef(FsrPhotons,1)
  #endif

private: 

  double HIGHETMIN;
  double OVERLAP;
  double OVERLAPELMU;
  
  bool isOverlap(float eleta, float elphi, std::vector< std::pair<unsigned int, double> >* ph_fsr, std::vector<float> *ph_eta, std::vector<float> *ph_phi);
  double deltaR(float muonEta, float muonPhi, float phEta, float phPhi);
  
};
#endif

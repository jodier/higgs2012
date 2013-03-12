#ifndef __McOverlapRemoval_h__
#define __McOverlapRemoval_h__


//////////////////////////////////////////////////////////////
// Small macro to remove overlaps                          /// 
// between H->4l related                                   ///
// MC samples                                              ///
//////////////////////////////////////////////////////////////
// Usage:                                                  ///
// mc_channel_number1 : sample to remove events from       /// 
//                     (current sample)                    ///          
// mc_channel_number2 : core sample                        ///
// MC_n               : number of entries in truth record  ///
// MC_pt,             : pointer to the relevant D3PD info  ///
// MC_eta,                                                 /// 
// MC_phi,                                                 ///
// MC_m,                                                   ///
// MC_status,                                              ///
// MC_pdgId                                                ///
//////////////////////////////////////////////////////////////
// K. Nikolopoulos (U. Birmingham)                         ///
// May 23, 2012                                            ///
//////////////////////////////////////////////////////////////
// ttbar
//
// we have three samples: 
// the 1lepton filter (105200)
// the 2lepton filter (109345 in mc11, 110001 in mc12)
// the 4lepton filter (109346 in mc11, 146369 in mc12)
//
// the 2lepton filter should not be used 
// (i.e. kill all events) 
// since it has lower statistics than then 1lepton filter
//
// from the 1lepton filter, remove those that fall 
// in the 4lepton filter phase-space
//
//////////////////////////////////////////////////////////////
//
#include<iostream>
#include<iomanip>
using namespace std;

#include <TLorentzVector.h>

bool killEvent(UInt_t mc_channel_number1, UInt_t mc_channel_number2,
	       Int_t MC_n,
	       vector<float>* MC_pt,
	       vector<float>* MC_eta,
	       vector<float>* MC_phi,
	       vector<float>* MC_m,
	       vector<int>* MC_status,
	       vector<int>* MC_pdgId)
;
#endif

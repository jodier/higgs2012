// Efficiency scale factors macro
// Date: 11/01/2010
// Author: Olivier Arnaez <olivier.arnaez@cern.ch>
//         Jan Kretzschmar <jan.kretzschmar@cern.ch>
//
// Usage: 
// std::pair<float,float> sf_error = objsf->scaleFactor(eta(cluster), ET(MeV), set, range, rel, etcorrection, runnumber)
//
// The first number (sf_error.first) returns the efficiency scale factor,
// the second number is its uncertainty (sf_errror.second)
// 
// The combined (W/Z/jpsi) scale factor and uncertainty vs eta and ET (in MeV) are given
// 
// different "sets" of numbers available (not all with all sets):
//    Electron ID and reconstruction
//    * Loose SF (set=0)
//    * Medium SF (set=1)
//    * Tight SF (set=2)
//    * e20_medium trigger SF (set=3) (use set >=8 for release 17 2011 data/MC11a)
//    * reco+trkqual SF (set=4)
//    * Loose++ SF (set=5)
//    * Medium++ SF (set=6)
//    * Tight++ SF (set=7)
//    * MultiLepton (set=30)
//    * Forward Loose SF, detailed G4 FCAL (set=23)
//    * Forward Tight SF, detailed G4 FCAL  (set=24)
//    * Forward Loose SF, Frozen showers FCAL (set=25)
//    * Forward Tight SF, Frozen showers FCAL  (set=26)
//
//    2011 Triggers
//    * e20_medium trigger SF w.r.t Medium++ offline (set=8)
//    * e20_medium MC efficiency w.r.t Medium++ offline (set=9)
//    * e20_medium trigger SF w.r.t Tight++ offline (set=10)
//    * e20_medium MC efficiency w.r.t Tight++ offline (set=11)
//    * e22_medium trigger SF w.r.t Medium++ offline (set=12)
//    * e22_medium MC efficiency w.r.t Medium++ offline (set=13)
//    * e22_medium trigger SF w.r.t Tight++ offline (set=14)
//    * e22_medium MC efficiency w.r.t Tight++ offline (set=15)
//    * e22vh_medium1 trigger SF (using e22_medium1 on MC11a) w.r.t Medium++ offline (set=16)
//    * e22_medium1 MC efficiency w.r.t Medium++ offline (set=17)
//    * e22vh_medium1 trigger SF (using e22_medium1 on MC11a) w.r.t Tight++ offline (set=18)
//    * e22_medium1 MC efficiency w.r.t Tight++ offline (set=19)
//    * e20_medium MC efficiency w.r.t Loose++ offline (set=20)
//    * e22_medium1 MC efficiency w.r.t Loose++ offline (set=21)
//    * e22vh_medium1 MC efficiency w.r.t Loose++ offline (set=22)
//    * e20_medium SF  w.r.t Loose++ offline (set=27)  
//    * e22_medium1 SF  w.r.t Loose++ offline (set=28)
//    * e22vh_medium1 SF  w.r.t Loose++ offline (set=29)
//   
//    2012 Triggers
//    * e24vhi_medium1||e60_medium1 trigger SF w.r.t Loose++ offline (set=31)
//    * e24vhi_medium1||e60_medium1 MC efficiency w.r.t Loose++ offline (set=32)
//    * e24vhi_medium1||e60_medium1 trigger SF w.r.t Medium++ offline (set=33)
//    * e24vhi_medium1||e60_medium1 MC efficiency w.r.t Medium++ offline (set=34)
//    * e24vhi_medium1||e60_medium1 trigger SF w.r.t Tight++ offline (set=35)
//    * e24vhi_medium1||e60_medium1 MC efficiency w.r.t Tight++ offline (set=36)
//    * e24vhi_medium1||e60_medium1 trigger SF w.r.t ML offline (set=37)
//    * e24vhi_medium1||e60_medium1 MC efficiency w.r.t ML offline (set=38)
//    * e12Tvh_loose1 trigger SF w.r.t Loose++ offline (set=39)
//    * e12Tvh_loose1 MC efficiency w.r.t Loose++ offline (set=40)
//    * e12Tvh_loose1 trigger SF w.r.t Medium++ offline (set=41)
//    * e12Tvh_loose1 MC efficiency w.r.t Medium++ offline (set=42)
//    * e12Tvh_loose1 trigger SF w.r.t Tight++ offline (set=43)
//    * e12Tvh_loose1 MC efficiency w.r.t Tight++ offline (set=44)
//    * e12Tvh_loose1 trigger SF w.r.t ML offline (set=45)
//    * e12Tvh_loose1 MC efficiency w.r.t ML offline (set=46)
//
//
// data and MC release selection:
//    * release 15 2010 data/MC09 (rel=0)
//    * release 16 2010 data/MC10 (rel=1)
//    * release 16.6 2011 data/MC10ab (estimated from 2010 data) (rel=2)
//    * release 16.6 estimated from 2011 data "EPS recommendations" and MC10b (rel=3)
//    * release 16.6 estimated from 2011 data "EPS recommendations" including Jpsi measurements (rel=4)
//    * release 17 estimated from 2011 data/MC11a "CERN council recommendations" (rel=5)
//    * release 17 estimated from 2011 data/MC11a/b/c "Moriond recommendations" G4 FullSim MC (rel=6)
//    * release 17 estimated from 2011 data/MC11a/b/c "Moriond recommendations" AFII MC (rel=7)
//    * release 17.2 estimated from 2012 data/MC12a   "ICHEP 2012 recommendations" G4 FullSim MC (rel=8)
//    * release 17.2 estimated from 2012 data/MC12a   "ICHEP 2012 recommendations" AFII MC (rel=9)
//    * release 17.2 estimated from 2012 data/MC12a   "HCP 2012 recommendations" G4 FullSim MC (rel=10)
//    * release 17.2 estimated from 2012 data/MC12a   "HCP 2012 recommendations" AFII MC (rel=11)
//    * Updated 2011 forward electrons, release 17 MC11c, G4 FullSim MC (rel=12)
// measured with probes in the ranges:
//    * 20-50 GeV range (range=0)
//    * 30-50 GeV (range=1)
// and correcting (etcorrection=1) or not (etcorrection=0) for the ET-dependence
//
// Eta binning is changing from release to release
//
// Note that for rel>=4 range should be left at 0 and etcorrection=1 always
//
// From the ICHEP2012 SF (rel=8 and 9) on there is a run number argument needed.
// This is used only for the trigger SF run dependence.
// For the user the simplest is to start supplying the run numbers from now on
// (e.g. using the "RandomRunNumber" from the ExtendedPileupReweighting tool)
// 
// ONLY for release 16.6, 2011 data there are separate functions
// for Forward Electrons (|eta|>=2.5)
// std::pair<float,float> sf_error = objsf->scaleFactorForward(eta, set)
// where eta = electron eta = cluster eta (as no track)
// cuts are ForwardLoose (set=0) or ForwardTight (set=2)
// 

#ifndef egammaSFclass_h
#define egammaSFclass_h

#include <iostream>
#include <string>
#include <map>
#include <vector>

#ifdef ROOTCORE
#include "TROOT.h"
#endif

using namespace std;

class egammaSFclass {

public:

  egammaSFclass();
  virtual ~egammaSFclass() {};

  std::pair<float,float> etCorrection(float ET, int set, int rel=5, int runrange = -1);
  std::pair<float,float> scaleFactor(float eta, float ET, int set, int range=0, int rel=5, bool etcorrection=true, int runnumber = -1);

  // legacy separate "forward electron classes"
  std::pair<float,float> scaleFactorForward(float eta, int set);
  std::pair<float,float> scaleFactorForwardLoose(float eta)
    { return scaleFactorForward(eta, 0); };
  std::pair<float,float> scaleFactorForwardTight(float eta)
    { return scaleFactorForward(eta, 2); };

  //For the binning
  std::vector<float> m_Etabins;
  std::vector<float> m_FineEtabins;
  std::vector<float> m_11Etabins;
  std::vector<float> m_FwdEtabins;

  std::vector<float> m_ETbins;
  std::vector<float> m_ETbinsFullRange;
  std::vector<float> m_ETbinsTrigger;
  std::vector<float> m_ETbinsTrigger_e24;
  std::vector<float> m_ETbinsTrigger_e12;

  //For the scale factors of the standard egamma cuts 
  //Release 15
  //Probes between 30 and 50 GeV (plateau region)
  std::vector<float> efficienciesRel15Loose3050;
  std::vector<float> uncertaintiesRel15Loose3050;
  std::vector<float> efficienciesRel15Medium3050;
  std::vector<float> uncertaintiesRel15Medium3050;
  std::vector<float> efficienciesRel15Tight3050;
  std::vector<float> uncertaintiesRel15Tight3050;
  //Probes between 20 and 50 GeV
  std::vector<float> efficienciesRel15Loose2050;
  std::vector<float> uncertaintiesRel15Loose2050;
  std::vector<float> efficienciesRel15Medium2050;
  std::vector<float> uncertaintiesRel15Medium2050;
  std::vector<float> efficienciesRel15Tight2050;
  std::vector<float> uncertaintiesRel15Tight2050;

  //Release 16
  //Probes between 30 and 50 GeV (plateau region)
  std::vector<float> efficienciesRel16Medium3050;
  std::vector<float> uncertaintiesRel16Medium3050;
  std::vector<float> efficienciesRel16Tight3050;
  std::vector<float> uncertaintiesRel16Tight3050;
  //Probes between 20 and 50 GeV
  std::vector<float> efficienciesRel16Medium2050;
  std::vector<float> uncertaintiesRel16Medium2050;
  std::vector<float> efficienciesRel16Tight2050;
  std::vector<float> uncertaintiesRel16Tight2050;

  //Release 16.6 with 2010 data
  //Probes between 30 and 50 GeV (plateau region)
  std::vector<float> efficienciesRel166Data2010Medium3050;
  std::vector<float> uncertaintiesRel166Data2010Medium3050;
  std::vector<float> efficienciesRel166Data2010Tight3050;
  std::vector<float> uncertaintiesRel166Data2010Tight3050;
  //Probes between 20 and 50 GeV
  std::vector<float> efficienciesRel166Data2010Medium2050;
  std::vector<float> uncertaintiesRel166Data2010Medium2050;
  std::vector<float> efficienciesRel166Data2010Tight2050;
  std::vector<float> uncertaintiesRel166Data2010Tight2050;

  //Release 16.6, EPS recommendations
  //Identification for probes between 20 and 50 GeV
  std::vector<float> efficienciesRel166EPSMedium2050;
  std::vector<float> uncertaintiesRel166EPSMedium2050;
  std::vector<float> efficienciesRel166EPSTight2050;
  std::vector<float> uncertaintiesRel166EPSTight2050;
  //Identification for low ET probes
  std::vector<float> efficienciesRel166EPSMediumLowET;
  std::vector<float> uncertaintiesRel166EPSMediumLowET;
  std::vector<float> efficienciesRel166EPSTightLowET;
  std::vector<float> uncertaintiesRel166EPSTightLowET;
  //For trigger efficiencies on the plateau
  std::vector<float> efficienciesRel166EPSTrigger;
  std::vector<float> uncertaintiesRel166EPSTrigger;
  //For reco+trkquality efficiencies
  std::vector<float> efficienciesRel166EPSRecoTrkQual;
  std::vector<float> uncertaintiesRel166EPSRecoTrkQual;

  //For the ET-corrections of the scale factors
  //Release 16
  //Medium
  std::vector<float> ETCorrectionsMediumRel16;
  std::vector<float> uncertaintiesETCorrectionsMediumRel16;
  //Tight
  std::vector<float> ETCorrectionsTightRel16;
  std::vector<float> uncertaintiesETCorrectionsTightRel16;
  //Release 16.6 with 2010 data
  //Medium
  std::vector<float> ETCorrectionsMediumRel166Data2010;
  std::vector<float> uncertaintiesETCorrectionsMediumRel166Data2010;
  //Tight
  std::vector<float> ETCorrectionsTightRel166Data2010;
  std::vector<float> uncertaintiesETCorrectionsTightRel166Data2010;
  //Release 16.6, EPS recommendations
  //Medium
  std::vector<float> ETCorrectionsMediumRel166EPS;
  std::vector<float> uncertaintiesETCorrectionsMediumRel166EPS;
  //Tight
  std::vector<float> ETCorrectionsTightRel166EPS;
  std::vector<float> uncertaintiesETCorrectionsTightRel166EPS;
  //Release 16.6, EPS recommendations including low ET electrons
  //Medium
  std::vector<float> ETCorrectionsMediumRel166EPSFullRange;
  std::vector<float> uncertaintiesETCorrectionsMediumRel166EPSFullRange;
  //Tight
  std::vector<float> ETCorrectionsTightRel166EPSFullRange;
  std::vector<float> uncertaintiesETCorrectionsTightRel166EPSFullRange;


  // Release 17, "CERN Council" recommendations
  // converter
  void copyToVector(const float *myarray, int n, std::vector<float> &dest, double renorm = 100.);

  // For reco+trkquality efficiencies
  std::vector<float> efficienciesRel17CCRecoTrkQual;
  std::vector<float> uncertaintiesRel17CCRecoTrkQual;

  // Identification eta for probes between 15 and 50 GeV
  std::vector<float> efficienciesRel17CCLoosePP1550;
  std::vector<float> uncertaintiesRel17CCLoosePP1550;
  std::vector<float> efficienciesRel17CCMediumPP1550;
  std::vector<float> uncertaintiesRel17CCMediumPP1550;
  std::vector<float> efficienciesRel17CCTightPP1550;
  std::vector<float> uncertaintiesRel17CCTightPP1550;
  //Identification eta for low ET probes
  std::vector<float> efficienciesRel17CCLoosePP415;
  std::vector<float> uncertaintiesRel17CCLoosePP415;
  std::vector<float> efficienciesRel17CCMediumPP415;
  std::vector<float> uncertaintiesRel17CCMediumPP415;
  std::vector<float> efficienciesRel17CCTightPP415;
  std::vector<float> uncertaintiesRel17CCTightPP415;
  // ET correction
  std::vector<float> ETCorrectionsRel17CCLoosePP;
  std::vector<float> uncertaintiesETCorrectionsRel17CCLoosePP;
  std::vector<float> ETCorrectionsRel17CCMediumPP;
  std::vector<float> uncertaintiesETCorrectionsRel17CCMediumPP;
  std::vector<float> ETCorrectionsRel17CCTightPP;
  std::vector<float> uncertaintiesETCorrectionsRel17CCTightPP;

  // Trigger efficiencies
  // e20_medium B-J
  std::vector<float> MCefficienciesRel17CCe20_mediumLoosePP;
  std::vector<float> MCefficienciesRel17CCe20_mediumLoosePPET;

  std::vector<float> efficienciesRel17CCe20_mediumMediumPP;
  std::vector<float> uncertaintiesRel17CCe20_mediumMediumPP;
  std::vector<float> efficienciesRel17CCe20_mediumMediumPPET;
  std::vector<float> uncertaintiesRel17CCe20_mediumMediumPPET;

  std::vector<float> MCefficienciesRel17CCe20_mediumMediumPP;
  std::vector<float> MCefficienciesRel17CCe20_mediumMediumPPET;

  std::vector<float> efficienciesRel17CCe20_mediumTightPP;
  std::vector<float> uncertaintiesRel17CCe20_mediumTightPP;
  std::vector<float> efficienciesRel17CCe20_mediumTightPPET;
  std::vector<float> uncertaintiesRel17CCe20_mediumTightPPET;

  std::vector<float> MCefficienciesRel17CCe20_mediumTightPP;
  std::vector<float> MCefficienciesRel17CCe20_mediumTightPPET;


  // e22_medium K

  std::vector<float> MCefficienciesRel17CCe22_mediumLoosePP;
  std::vector<float> MCefficienciesRel17CCe22_mediumLoosePPET;

  std::vector<float> efficienciesRel17CCe22_mediumMediumPP;
  std::vector<float> uncertaintiesRel17CCe22_mediumMediumPP;
  std::vector<float> efficienciesRel17CCe22_mediumMediumPPET;
  std::vector<float> uncertaintiesRel17CCe22_mediumMediumPPET;

  std::vector<float> MCefficienciesRel17CCe22_mediumMediumPP;
  std::vector<float> MCefficienciesRel17CCe22_mediumMediumPPET;

  std::vector<float> efficienciesRel17CCe22_mediumTightPP;
  std::vector<float> uncertaintiesRel17CCe22_mediumTightPP;
  std::vector<float> efficienciesRel17CCe22_mediumTightPPET;
  std::vector<float> uncertaintiesRel17CCe22_mediumTightPPET;

  std::vector<float> MCefficienciesRel17CCe22_mediumTightPP;
  std::vector<float> MCefficienciesRel17CCe22_mediumTightPPET;


  // e22vh_medium1 L-M
  std::vector<float> MCefficienciesRel17CCe22vh_medium1LoosePP;
  std::vector<float> MCefficienciesRel17CCe22vh_medium1LoosePPET;

  std::vector<float> efficienciesRel17CCe22vh_medium1MediumPP;
  std::vector<float> uncertaintiesRel17CCe22vh_medium1MediumPP;
  std::vector<float> efficienciesRel17CCe22vh_medium1MediumPPET;
  std::vector<float> uncertaintiesRel17CCe22vh_medium1MediumPPET;

  std::vector<float> MCefficienciesRel17CCe22vh_medium1MediumPP;
  std::vector<float> MCefficienciesRel17CCe22vh_medium1MediumPPET;

  std::vector<float> efficienciesRel17CCe22vh_medium1TightPP;
  std::vector<float> uncertaintiesRel17CCe22vh_medium1TightPP;
  std::vector<float> efficienciesRel17CCe22vh_medium1TightPPET;
  std::vector<float> uncertaintiesRel17CCe22vh_medium1TightPPET;

  std::vector<float> MCefficienciesRel17CCe22vh_medium1TightPP;
  std::vector<float> MCefficienciesRel17CCe22vh_medium1TightPPET;

  // Release 17, "Moriond" recommendations
  // For reco+trkquality efficiencies
  std::vector<float> efficienciesRel17MoriondRecoTrkQual;
  std::vector<float> uncertaintiesRel17MoriondRecoTrkQual;

  // Identification eta for probes between 15 and 50 GeV
  std::vector<float> efficienciesRel17MoriondLoosePP1550;
  std::vector<float> uncertaintiesRel17MoriondLoosePP1550;
  std::vector<float> efficienciesRel17MoriondMedium1550;
  std::vector<float> uncertaintiesRel17MoriondMedium1550;
  std::vector<float> efficienciesRel17MoriondMediumPP1550;
  std::vector<float> uncertaintiesRel17MoriondMediumPP1550;
  std::vector<float> efficienciesRel17MoriondTightPP1550;
  std::vector<float> uncertaintiesRel17MoriondTightPP1550;
  //Identification eta for low ET probes
  std::vector<float> efficienciesRel17MoriondLoosePP415;
  std::vector<float> uncertaintiesRel17MoriondLoosePP415;
  std::vector<float> efficienciesRel17MoriondMedium415;
  std::vector<float> uncertaintiesRel17MoriondMedium415;
  std::vector<float> efficienciesRel17MoriondMediumPP415;
  std::vector<float> uncertaintiesRel17MoriondMediumPP415;
  std::vector<float> efficienciesRel17MoriondTightPP415;
  std::vector<float> uncertaintiesRel17MoriondTightPP415;
  // ET correction
  std::vector<float> ETCorrectionsRel17MoriondLoosePP;
  std::vector<float> uncertaintiesETCorrectionsRel17MoriondLoosePP;
  std::vector<float> ETCorrectionsRel17MoriondMedium;
  std::vector<float> uncertaintiesETCorrectionsRel17MoriondMedium;
  std::vector<float> ETCorrectionsRel17MoriondMediumPP;
  std::vector<float> uncertaintiesETCorrectionsRel17MoriondMediumPP;
  std::vector<float> ETCorrectionsRel17MoriondTightPP;
  std::vector<float> uncertaintiesETCorrectionsRel17MoriondTightPP;

  // Forward electron Identification eta for probes >20 GeV
  std::vector<float> efficienciesRel17MoriondForwardLoose;
  std::vector<float> uncertaintiesRel17MoriondForwardLoose;
  std::vector<float> efficienciesRel17MoriondForwardTight;
  std::vector<float> uncertaintiesRel17MoriondForwardTight;

  std::vector<float> efficienciesRel17MoriondFrozenShowersForwardLoose;
  std::vector<float> efficienciesRel17MoriondFrozenShowersForwardTight;

  // Trigger efficiencies
  // e20_medium B-J
  std::vector<float> MCefficienciesRel17Morionde20_mediumLoosePP;
  std::vector<float> MCefficienciesRel17Morionde20_mediumLoosePPET;

  std::vector<float> efficienciesRel17Morionde20_mediumLoosePP;
  std::vector<float> uncertaintiesRel17Morionde20_mediumLoosePP;
  std::vector<float> efficienciesRel17Morionde20_mediumLoosePPET;
  std::vector<float> uncertaintiesRel17Morionde20_mediumLoosePPET;

  std::vector<float> efficienciesRel17Morionde20_mediumMediumPP;
  std::vector<float> uncertaintiesRel17Morionde20_mediumMediumPP;
  std::vector<float> efficienciesRel17Morionde20_mediumMediumPPET;
  std::vector<float> uncertaintiesRel17Morionde20_mediumMediumPPET;


  std::vector<float> MCefficienciesRel17Morionde20_mediumMediumPP;
  std::vector<float> MCefficienciesRel17Morionde20_mediumMediumPPET;

  std::vector<float> efficienciesRel17Morionde20_mediumTightPP;
  std::vector<float> uncertaintiesRel17Morionde20_mediumTightPP;
  std::vector<float> efficienciesRel17Morionde20_mediumTightPPET;
  std::vector<float> uncertaintiesRel17Morionde20_mediumTightPPET;

  std::vector<float> MCefficienciesRel17Morionde20_mediumTightPP;
  std::vector<float> MCefficienciesRel17Morionde20_mediumTightPPET;


  // e22_medium K

  std::vector<float> MCefficienciesRel17Morionde22_mediumLoosePP;
  std::vector<float> MCefficienciesRel17Morionde22_mediumLoosePPET;

  std::vector<float> efficienciesRel17Morionde22_mediumLoosePP;
  std::vector<float> uncertaintiesRel17Morionde22_mediumLoosePP;
  std::vector<float> efficienciesRel17Morionde22_mediumLoosePPET;
  std::vector<float> uncertaintiesRel17Morionde22_mediumLoosePPET;

  std::vector<float> efficienciesRel17Morionde22_mediumMediumPP;
  std::vector<float> uncertaintiesRel17Morionde22_mediumMediumPP;
  std::vector<float> efficienciesRel17Morionde22_mediumMediumPPET;
  std::vector<float> uncertaintiesRel17Morionde22_mediumMediumPPET;

  std::vector<float> MCefficienciesRel17Morionde22_mediumMediumPP;
  std::vector<float> MCefficienciesRel17Morionde22_mediumMediumPPET;

  std::vector<float> efficienciesRel17Morionde22_mediumTightPP;
  std::vector<float> uncertaintiesRel17Morionde22_mediumTightPP;
  std::vector<float> efficienciesRel17Morionde22_mediumTightPPET;
  std::vector<float> uncertaintiesRel17Morionde22_mediumTightPPET;

  std::vector<float> MCefficienciesRel17Morionde22_mediumTightPP;
  std::vector<float> MCefficienciesRel17Morionde22_mediumTightPPET;


  // e22vh_medium1 L-M
  std::vector<float> MCefficienciesRel17Morionde22vh_medium1LoosePP;
  std::vector<float> MCefficienciesRel17Morionde22vh_medium1LoosePPET;

  std::vector<float> efficienciesRel17Morionde22vh_medium1LoosePP;
  std::vector<float> uncertaintiesRel17Morionde22vh_medium1LoosePP;
  std::vector<float> efficienciesRel17Morionde22vh_medium1LoosePPET;
  std::vector<float> uncertaintiesRel17Morionde22vh_medium1LoosePPET;

  std::vector<float> efficienciesRel17Morionde22vh_medium1MediumPP;
  std::vector<float> uncertaintiesRel17Morionde22vh_medium1MediumPP;
  std::vector<float> efficienciesRel17Morionde22vh_medium1MediumPPET;
  std::vector<float> uncertaintiesRel17Morionde22vh_medium1MediumPPET;

  std::vector<float> MCefficienciesRel17Morionde22vh_medium1MediumPP;
  std::vector<float> MCefficienciesRel17Morionde22vh_medium1MediumPPET;

  std::vector<float> efficienciesRel17Morionde22vh_medium1TightPP;
  std::vector<float> uncertaintiesRel17Morionde22vh_medium1TightPP;
  std::vector<float> efficienciesRel17Morionde22vh_medium1TightPPET;
  std::vector<float> uncertaintiesRel17Morionde22vh_medium1TightPPET;

  std::vector<float> MCefficienciesRel17Morionde22vh_medium1TightPP;
  std::vector<float> MCefficienciesRel17Morionde22vh_medium1TightPPET;

  // Release 17, "Moriond" recommendations - AFII samples
  // For reco+trkquality efficiencies
  std::vector<float> efficienciesRel17MoriondAFIIRecoTrkQual;
  std::vector<float> uncertaintiesRel17MoriondAFIIRecoTrkQual;

  // Identification eta for probes between 15 and 50 GeV
  std::vector<float> efficienciesRel17MoriondAFIILoosePP1550;
  std::vector<float> uncertaintiesRel17MoriondAFIILoosePP1550;
  std::vector<float> efficienciesRel17MoriondAFIIMedium1550;
  std::vector<float> uncertaintiesRel17MoriondAFIIMedium1550;
  std::vector<float> efficienciesRel17MoriondAFIIMediumPP1550;
  std::vector<float> uncertaintiesRel17MoriondAFIIMediumPP1550;
  std::vector<float> efficienciesRel17MoriondAFIITightPP1550;
  std::vector<float> uncertaintiesRel17MoriondAFIITightPP1550;
  //Identification eta for low ET probes
  std::vector<float> efficienciesRel17MoriondAFIILoosePP415;
  std::vector<float> uncertaintiesRel17MoriondAFIILoosePP415;
  std::vector<float> efficienciesRel17MoriondAFIIMedium415;
  std::vector<float> uncertaintiesRel17MoriondAFIIMedium415;
  std::vector<float> efficienciesRel17MoriondAFIIMediumPP415;
  std::vector<float> uncertaintiesRel17MoriondAFIIMediumPP415;
  std::vector<float> efficienciesRel17MoriondAFIITightPP415;
  std::vector<float> uncertaintiesRel17MoriondAFIITightPP415;
  // ET correction
  std::vector<float> ETCorrectionsRel17MoriondAFIILoosePP;
  std::vector<float> uncertaintiesETCorrectionsRel17MoriondAFIILoosePP;
  std::vector<float> ETCorrectionsRel17MoriondAFIIMedium;
  std::vector<float> uncertaintiesETCorrectionsRel17MoriondAFIIMedium;
  std::vector<float> ETCorrectionsRel17MoriondAFIIMediumPP;
  std::vector<float> uncertaintiesETCorrectionsRel17MoriondAFIIMediumPP;
  std::vector<float> ETCorrectionsRel17MoriondAFIITightPP;
  std::vector<float> uncertaintiesETCorrectionsRel17MoriondAFIITightPP;

  // Trigger efficiencies
  // e20_medium B-J
  std::vector<float> MCefficienciesRel17MoriondAFIIe20_mediumLoosePP;
  std::vector<float> MCefficienciesRel17MoriondAFIIe20_mediumLoosePPET;

  std::vector<float> efficienciesRel17MoriondAFIIe20_mediumLoosePP;
  std::vector<float> uncertaintiesRel17MoriondAFIIe20_mediumLoosePP;
  std::vector<float> efficienciesRel17MoriondAFIIe20_mediumLoosePPET;
  std::vector<float> uncertaintiesRel17MoriondAFIIe20_mediumLoosePPET;

  std::vector<float> efficienciesRel17MoriondAFIIe20_mediumMediumPP;
  std::vector<float> uncertaintiesRel17MoriondAFIIe20_mediumMediumPP;
  std::vector<float> efficienciesRel17MoriondAFIIe20_mediumMediumPPET;
  std::vector<float> uncertaintiesRel17MoriondAFIIe20_mediumMediumPPET;

  std::vector<float> MCefficienciesRel17MoriondAFIIe20_mediumMediumPP;
  std::vector<float> MCefficienciesRel17MoriondAFIIe20_mediumMediumPPET;

  std::vector<float> efficienciesRel17MoriondAFIIe20_mediumTightPP;
  std::vector<float> uncertaintiesRel17MoriondAFIIe20_mediumTightPP;
  std::vector<float> efficienciesRel17MoriondAFIIe20_mediumTightPPET;
  std::vector<float> uncertaintiesRel17MoriondAFIIe20_mediumTightPPET;

  std::vector<float> MCefficienciesRel17MoriondAFIIe20_mediumTightPP;
  std::vector<float> MCefficienciesRel17MoriondAFIIe20_mediumTightPPET;


  // e22_medium K

  std::vector<float> MCefficienciesRel17MoriondAFIIe22_mediumLoosePP;
  std::vector<float> MCefficienciesRel17MoriondAFIIe22_mediumLoosePPET;

  std::vector<float> efficienciesRel17MoriondAFIIe22_mediumMediumPP;
  std::vector<float> uncertaintiesRel17MoriondAFIIe22_mediumMediumPP;
  std::vector<float> efficienciesRel17MoriondAFIIe22_mediumMediumPPET;
  std::vector<float> uncertaintiesRel17MoriondAFIIe22_mediumMediumPPET;

  std::vector<float> efficienciesRel17MoriondAFIIe22_mediumLoosePP;
  std::vector<float> uncertaintiesRel17MoriondAFIIe22_mediumLoosePP;
  std::vector<float> efficienciesRel17MoriondAFIIe22_mediumLoosePPET;
  std::vector<float> uncertaintiesRel17MoriondAFIIe22_mediumLoosePPET;

  std::vector<float> MCefficienciesRel17MoriondAFIIe22_mediumMediumPP;
  std::vector<float> MCefficienciesRel17MoriondAFIIe22_mediumMediumPPET;

  std::vector<float> efficienciesRel17MoriondAFIIe22_mediumTightPP;
  std::vector<float> uncertaintiesRel17MoriondAFIIe22_mediumTightPP;
  std::vector<float> efficienciesRel17MoriondAFIIe22_mediumTightPPET;
  std::vector<float> uncertaintiesRel17MoriondAFIIe22_mediumTightPPET;

  std::vector<float> MCefficienciesRel17MoriondAFIIe22_mediumTightPP;
  std::vector<float> MCefficienciesRel17MoriondAFIIe22_mediumTightPPET;


  // e22vh_medium1 L-M
  std::vector<float> MCefficienciesRel17MoriondAFIIe22vh_medium1LoosePP;
  std::vector<float> MCefficienciesRel17MoriondAFIIe22vh_medium1LoosePPET;

  std::vector<float> efficienciesRel17MoriondAFIIe22vh_medium1LoosePP;
  std::vector<float> uncertaintiesRel17MoriondAFIIe22vh_medium1LoosePP;
  std::vector<float> efficienciesRel17MoriondAFIIe22vh_medium1LoosePPET;
  std::vector<float> uncertaintiesRel17MoriondAFIIe22vh_medium1LoosePPET;

  std::vector<float> efficienciesRel17MoriondAFIIe22vh_medium1MediumPP;
  std::vector<float> uncertaintiesRel17MoriondAFIIe22vh_medium1MediumPP;
  std::vector<float> efficienciesRel17MoriondAFIIe22vh_medium1MediumPPET;
  std::vector<float> uncertaintiesRel17MoriondAFIIe22vh_medium1MediumPPET;

  std::vector<float> MCefficienciesRel17MoriondAFIIe22vh_medium1MediumPP;
  std::vector<float> MCefficienciesRel17MoriondAFIIe22vh_medium1MediumPPET;

  std::vector<float> efficienciesRel17MoriondAFIIe22vh_medium1TightPP;
  std::vector<float> uncertaintiesRel17MoriondAFIIe22vh_medium1TightPP;
  std::vector<float> efficienciesRel17MoriondAFIIe22vh_medium1TightPPET;
  std::vector<float> uncertaintiesRel17MoriondAFIIe22vh_medium1TightPPET;

  std::vector<float> MCefficienciesRel17MoriondAFIIe22vh_medium1TightPP;
  std::vector<float> MCefficienciesRel17MoriondAFIIe22vh_medium1TightPPET;

  // Updated 2011 Forward electrons
  std::vector<float> efficienciesRel17HCPForwardLoose;
  std::vector<float> uncertaintiesRel17HCPForwardLoose;
  std::vector<float> efficienciesRel17HCPForwardMedium;
  std::vector<float> uncertaintiesRel17HCPForwardMedium;
  std::vector<float> efficienciesRel17HCPForwardTight;
  std::vector<float> uncertaintiesRel17HCPForwardTight;


  // Release 17.2, "ICHEP 2012" recommendations
  int getRunRange(int runnumber, const std::vector<int> &runranges);
  std::vector<int> runranges_ICHEP2012;
  // For reco+trkquality efficiencies
  std::vector<float> efficienciesRel172ICHEPRecoTrkQual;
  std::vector<float> uncertaintiesRel172ICHEPRecoTrkQual;

  // Identification eta for probes between 15 and 50 GeV
  std::vector<float> efficienciesRel172ICHEPLoosePP1550;
  std::vector<float> uncertaintiesRel172ICHEPLoosePP1550;
  std::vector<float> efficienciesRel172ICHEPMedium1550;
  std::vector<float> uncertaintiesRel172ICHEPMedium1550;
  std::vector<float> efficienciesRel172ICHEPMediumPP1550;
  std::vector<float> uncertaintiesRel172ICHEPMediumPP1550;
  std::vector<float> efficienciesRel172ICHEPTightPP1550;
  std::vector<float> uncertaintiesRel172ICHEPTightPP1550;
  std::vector<float> efficienciesRel172ICHEPML1550;
  std::vector<float> uncertaintiesRel172ICHEPML1550;
  //Identification eta for low ET probes
  std::vector<float> efficienciesRel172ICHEPLoosePP415;
  std::vector<float> uncertaintiesRel172ICHEPLoosePP415;
  std::vector<float> efficienciesRel172ICHEPMedium415;
  std::vector<float> uncertaintiesRel172ICHEPMedium415;
  std::vector<float> efficienciesRel172ICHEPMediumPP415;
  std::vector<float> uncertaintiesRel172ICHEPMediumPP415;
  std::vector<float> efficienciesRel172ICHEPTightPP415;
  std::vector<float> uncertaintiesRel172ICHEPTightPP415;
  std::vector<float> efficienciesRel172ICHEPML415;
  std::vector<float> uncertaintiesRel172ICHEPML415;
  // ET correction
  std::vector<float> ETCorrectionsRel172ICHEPLoosePP;
  std::vector<float> uncertaintiesETCorrectionsRel172ICHEPLoosePP;
  std::vector<float> ETCorrectionsRel172ICHEPMedium;
  std::vector<float> uncertaintiesETCorrectionsRel172ICHEPMedium;
  std::vector<float> ETCorrectionsRel172ICHEPMediumPP;
  std::vector<float> uncertaintiesETCorrectionsRel172ICHEPMediumPP;
  std::vector<float> ETCorrectionsRel172ICHEPTightPP;
  std::vector<float> uncertaintiesETCorrectionsRel172ICHEPTightPP;
  std::vector<float> ETCorrectionsRel172ICHEPML;
  std::vector<float> uncertaintiesETCorrectionsRel172ICHEPML;

  // Trigger efficiencies
  // e24vhi_medium1||e60_medium1
  std::vector< std::vector<float> > efficienciesRel172ICHEP_e24vhi_medium1_LoosePP;
  std::vector< std::vector<float> > uncertaintiesRel172ICHEP_e24vhi_medium1_LoosePP;
  std::vector< std::vector<float> > efficienciesRel172ICHEP_e24vhi_medium1_LoosePPET;
  std::vector< std::vector<float> > uncertaintiesRel172ICHEP_e24vhi_medium1_LoosePPET;

  std::vector< std::vector<float> > MCefficienciesRel172ICHEP_e24vhi_medium1_LoosePP;
  std::vector< std::vector<float> > MCefficienciesRel172ICHEP_e24vhi_medium1_LoosePPET;

  std::vector< std::vector<float> > efficienciesRel172ICHEP_e24vhi_medium1_MediumPP;
  std::vector< std::vector<float> > uncertaintiesRel172ICHEP_e24vhi_medium1_MediumPP;
  std::vector< std::vector<float> > efficienciesRel172ICHEP_e24vhi_medium1_MediumPPET;
  std::vector< std::vector<float> > uncertaintiesRel172ICHEP_e24vhi_medium1_MediumPPET;

  std::vector< std::vector<float> > MCefficienciesRel172ICHEP_e24vhi_medium1_MediumPP;
  std::vector< std::vector<float> > MCefficienciesRel172ICHEP_e24vhi_medium1_MediumPPET;

  std::vector< std::vector<float> > efficienciesRel172ICHEP_e24vhi_medium1_TightPP;
  std::vector< std::vector<float> > uncertaintiesRel172ICHEP_e24vhi_medium1_TightPP;
  std::vector< std::vector<float> > efficienciesRel172ICHEP_e24vhi_medium1_TightPPET;
  std::vector< std::vector<float> > uncertaintiesRel172ICHEP_e24vhi_medium1_TightPPET;

  std::vector< std::vector<float> > MCefficienciesRel172ICHEP_e24vhi_medium1_TightPP;
  std::vector< std::vector<float> > MCefficienciesRel172ICHEP_e24vhi_medium1_TightPPET;

  std::vector< std::vector<float> > efficienciesRel172ICHEP_e24vhi_medium1_ML;
  std::vector< std::vector<float> > uncertaintiesRel172ICHEP_e24vhi_medium1_ML;
  std::vector< std::vector<float> > efficienciesRel172ICHEP_e24vhi_medium1_MLET;
  std::vector< std::vector<float> > uncertaintiesRel172ICHEP_e24vhi_medium1_MLET;

  std::vector< std::vector<float> > MCefficienciesRel172ICHEP_e24vhi_medium1_ML;
  std::vector< std::vector<float> > MCefficienciesRel172ICHEP_e24vhi_medium1_MLET;

  // e12Tvh_loose1
  std::vector< std::vector<float> > efficienciesRel172ICHEP_e12Tvh_loose1_LoosePP;
  std::vector< std::vector<float> > uncertaintiesRel172ICHEP_e12Tvh_loose1_LoosePP;
  std::vector< std::vector<float> > efficienciesRel172ICHEP_e12Tvh_loose1_LoosePPET;
  std::vector< std::vector<float> > uncertaintiesRel172ICHEP_e12Tvh_loose1_LoosePPET;

  std::vector< std::vector<float> > MCefficienciesRel172ICHEP_e12Tvh_loose1_LoosePP;
  std::vector< std::vector<float> > MCefficienciesRel172ICHEP_e12Tvh_loose1_LoosePPET;

  std::vector< std::vector<float> > efficienciesRel172ICHEP_e12Tvh_loose1_MediumPP;
  std::vector< std::vector<float> > uncertaintiesRel172ICHEP_e12Tvh_loose1_MediumPP;
  std::vector< std::vector<float> > efficienciesRel172ICHEP_e12Tvh_loose1_MediumPPET;
  std::vector< std::vector<float> > uncertaintiesRel172ICHEP_e12Tvh_loose1_MediumPPET;

  std::vector< std::vector<float> > MCefficienciesRel172ICHEP_e12Tvh_loose1_MediumPP;
  std::vector< std::vector<float> > MCefficienciesRel172ICHEP_e12Tvh_loose1_MediumPPET;

  std::vector< std::vector<float> > efficienciesRel172ICHEP_e12Tvh_loose1_TightPP;
  std::vector< std::vector<float> > uncertaintiesRel172ICHEP_e12Tvh_loose1_TightPP;
  std::vector< std::vector<float> > efficienciesRel172ICHEP_e12Tvh_loose1_TightPPET;
  std::vector< std::vector<float> > uncertaintiesRel172ICHEP_e12Tvh_loose1_TightPPET;

  std::vector< std::vector<float> > MCefficienciesRel172ICHEP_e12Tvh_loose1_TightPP;
  std::vector< std::vector<float> > MCefficienciesRel172ICHEP_e12Tvh_loose1_TightPPET;

  std::vector< std::vector<float> > efficienciesRel172ICHEP_e12Tvh_loose1_ML;
  std::vector< std::vector<float> > uncertaintiesRel172ICHEP_e12Tvh_loose1_ML;
  std::vector< std::vector<float> > efficienciesRel172ICHEP_e12Tvh_loose1_MLET;
  std::vector< std::vector<float> > uncertaintiesRel172ICHEP_e12Tvh_loose1_MLET;

  std::vector< std::vector<float> > MCefficienciesRel172ICHEP_e12Tvh_loose1_ML;
  std::vector< std::vector<float> > MCefficienciesRel172ICHEP_e12Tvh_loose1_MLET;


  // Release 17.2, "ICHEP 2012" recommendations AFII
  // For reco+trkquality efficiencies
  std::vector<float> efficienciesRel172ICHEP_AFIIRecoTrkQual;
  std::vector<float> uncertaintiesRel172ICHEP_AFIIRecoTrkQual;

  // Identification eta for probes between 15 and 50 GeV
  std::vector<float> efficienciesRel172ICHEP_AFIILoosePP1550;
  std::vector<float> uncertaintiesRel172ICHEP_AFIILoosePP1550;
  std::vector<float> efficienciesRel172ICHEP_AFIIMedium1550;
  std::vector<float> uncertaintiesRel172ICHEP_AFIIMedium1550;
  std::vector<float> efficienciesRel172ICHEP_AFIIMediumPP1550;
  std::vector<float> uncertaintiesRel172ICHEP_AFIIMediumPP1550;
  std::vector<float> efficienciesRel172ICHEP_AFIITightPP1550;
  std::vector<float> uncertaintiesRel172ICHEP_AFIITightPP1550;
  std::vector<float> efficienciesRel172ICHEP_AFIIML1550;
  std::vector<float> uncertaintiesRel172ICHEP_AFIIML1550;
  //Identification eta for low ET probes
  std::vector<float> efficienciesRel172ICHEP_AFIILoosePP415;
  std::vector<float> uncertaintiesRel172ICHEP_AFIILoosePP415;
  std::vector<float> efficienciesRel172ICHEP_AFIIMedium415;
  std::vector<float> uncertaintiesRel172ICHEP_AFIIMedium415;
  std::vector<float> efficienciesRel172ICHEP_AFIIMediumPP415;
  std::vector<float> uncertaintiesRel172ICHEP_AFIIMediumPP415;
  std::vector<float> efficienciesRel172ICHEP_AFIITightPP415;
  std::vector<float> uncertaintiesRel172ICHEP_AFIITightPP415;
  std::vector<float> efficienciesRel172ICHEP_AFIIML415;
  std::vector<float> uncertaintiesRel172ICHEP_AFIIML415;
  // ET correction
  std::vector<float> ETCorrectionsRel172ICHEP_AFIILoosePP;
  std::vector<float> uncertaintiesETCorrectionsRel172ICHEP_AFIILoosePP;
  std::vector<float> ETCorrectionsRel172ICHEP_AFIIMedium;
  std::vector<float> uncertaintiesETCorrectionsRel172ICHEP_AFIIMedium;
  std::vector<float> ETCorrectionsRel172ICHEP_AFIIMediumPP;
  std::vector<float> uncertaintiesETCorrectionsRel172ICHEP_AFIIMediumPP;
  std::vector<float> ETCorrectionsRel172ICHEP_AFIITightPP;
  std::vector<float> uncertaintiesETCorrectionsRel172ICHEP_AFIITightPP;
  std::vector<float> ETCorrectionsRel172ICHEP_AFIIML;
  std::vector<float> uncertaintiesETCorrectionsRel172ICHEP_AFIIML;

  // Trigger efficiencies
  // e24vhi_medium1||e60_medium1
  std::vector< std::vector<float> > efficienciesRel172ICHEP_AFII_e24vhi_medium1_LoosePP;
  std::vector< std::vector<float> > uncertaintiesRel172ICHEP_AFII_e24vhi_medium1_LoosePP;
  std::vector< std::vector<float> > efficienciesRel172ICHEP_AFII_e24vhi_medium1_LoosePPET;
  std::vector< std::vector<float> > uncertaintiesRel172ICHEP_AFII_e24vhi_medium1_LoosePPET;

  std::vector< std::vector<float> > MCefficienciesRel172ICHEP_AFII_e24vhi_medium1_LoosePP;
  std::vector< std::vector<float> > MCefficienciesRel172ICHEP_AFII_e24vhi_medium1_LoosePPET;

  std::vector< std::vector<float> > efficienciesRel172ICHEP_AFII_e24vhi_medium1_MediumPP;
  std::vector< std::vector<float> > uncertaintiesRel172ICHEP_AFII_e24vhi_medium1_MediumPP;
  std::vector< std::vector<float> > efficienciesRel172ICHEP_AFII_e24vhi_medium1_MediumPPET;
  std::vector< std::vector<float> > uncertaintiesRel172ICHEP_AFII_e24vhi_medium1_MediumPPET;

  std::vector< std::vector<float> > MCefficienciesRel172ICHEP_AFII_e24vhi_medium1_MediumPP;
  std::vector< std::vector<float> > MCefficienciesRel172ICHEP_AFII_e24vhi_medium1_MediumPPET;

  std::vector< std::vector<float> > efficienciesRel172ICHEP_AFII_e24vhi_medium1_TightPP;
  std::vector< std::vector<float> > uncertaintiesRel172ICHEP_AFII_e24vhi_medium1_TightPP;
  std::vector< std::vector<float> > efficienciesRel172ICHEP_AFII_e24vhi_medium1_TightPPET;
  std::vector< std::vector<float> > uncertaintiesRel172ICHEP_AFII_e24vhi_medium1_TightPPET;

  std::vector< std::vector<float> > MCefficienciesRel172ICHEP_AFII_e24vhi_medium1_TightPP;
  std::vector< std::vector<float> > MCefficienciesRel172ICHEP_AFII_e24vhi_medium1_TightPPET;

  std::vector< std::vector<float> > efficienciesRel172ICHEP_AFII_e24vhi_medium1_ML;
  std::vector< std::vector<float> > uncertaintiesRel172ICHEP_AFII_e24vhi_medium1_ML;
  std::vector< std::vector<float> > efficienciesRel172ICHEP_AFII_e24vhi_medium1_MLET;
  std::vector< std::vector<float> > uncertaintiesRel172ICHEP_AFII_e24vhi_medium1_MLET;

  std::vector< std::vector<float> > MCefficienciesRel172ICHEP_AFII_e24vhi_medium1_ML;
  std::vector< std::vector<float> > MCefficienciesRel172ICHEP_AFII_e24vhi_medium1_MLET;

  // e12Tvh_loose1
  std::vector< std::vector<float> > efficienciesRel172ICHEP_AFII_e12Tvh_loose1_LoosePP;
  std::vector< std::vector<float> > uncertaintiesRel172ICHEP_AFII_e12Tvh_loose1_LoosePP;
  std::vector< std::vector<float> > efficienciesRel172ICHEP_AFII_e12Tvh_loose1_LoosePPET;
  std::vector< std::vector<float> > uncertaintiesRel172ICHEP_AFII_e12Tvh_loose1_LoosePPET;

  std::vector< std::vector<float> > MCefficienciesRel172ICHEP_AFII_e12Tvh_loose1_LoosePP;
  std::vector< std::vector<float> > MCefficienciesRel172ICHEP_AFII_e12Tvh_loose1_LoosePPET;

  std::vector< std::vector<float> > efficienciesRel172ICHEP_AFII_e12Tvh_loose1_MediumPP;
  std::vector< std::vector<float> > uncertaintiesRel172ICHEP_AFII_e12Tvh_loose1_MediumPP;
  std::vector< std::vector<float> > efficienciesRel172ICHEP_AFII_e12Tvh_loose1_MediumPPET;
  std::vector< std::vector<float> > uncertaintiesRel172ICHEP_AFII_e12Tvh_loose1_MediumPPET;

  std::vector< std::vector<float> > MCefficienciesRel172ICHEP_AFII_e12Tvh_loose1_MediumPP;
  std::vector< std::vector<float> > MCefficienciesRel172ICHEP_AFII_e12Tvh_loose1_MediumPPET;

  std::vector< std::vector<float> > efficienciesRel172ICHEP_AFII_e12Tvh_loose1_TightPP;
  std::vector< std::vector<float> > uncertaintiesRel172ICHEP_AFII_e12Tvh_loose1_TightPP;
  std::vector< std::vector<float> > efficienciesRel172ICHEP_AFII_e12Tvh_loose1_TightPPET;
  std::vector< std::vector<float> > uncertaintiesRel172ICHEP_AFII_e12Tvh_loose1_TightPPET;

  std::vector< std::vector<float> > MCefficienciesRel172ICHEP_AFII_e12Tvh_loose1_TightPP;
  std::vector< std::vector<float> > MCefficienciesRel172ICHEP_AFII_e12Tvh_loose1_TightPPET;

  std::vector< std::vector<float> > efficienciesRel172ICHEP_AFII_e12Tvh_loose1_ML;
  std::vector< std::vector<float> > uncertaintiesRel172ICHEP_AFII_e12Tvh_loose1_ML;
  std::vector< std::vector<float> > efficienciesRel172ICHEP_AFII_e12Tvh_loose1_MLET;
  std::vector< std::vector<float> > uncertaintiesRel172ICHEP_AFII_e12Tvh_loose1_MLET;

  std::vector< std::vector<float> > MCefficienciesRel172ICHEP_AFII_e12Tvh_loose1_ML;
  std::vector< std::vector<float> > MCefficienciesRel172ICHEP_AFII_e12Tvh_loose1_MLET;

  // HCP 2012 update
  std::vector<int> runranges_HCP2012;
  // e24vhi_medium1||e60_medium1

  std::vector< std::vector<float> > efficienciesRel172HCP_e24vhi_medium1_LoosePP;
  std::vector< std::vector<float> > uncertaintiesRel172HCP_e24vhi_medium1_LoosePP;
  std::vector< std::vector<float> > efficienciesRel172HCP_e24vhi_medium1_LoosePPET;
  std::vector< std::vector<float> > uncertaintiesRel172HCP_e24vhi_medium1_LoosePPET;

  std::vector< std::vector<float> > MCefficienciesRel172HCP_e24vhi_medium1_LoosePP;
  std::vector< std::vector<float> > MCefficienciesRel172HCP_e24vhi_medium1_LoosePPET;

  std::vector< std::vector<float> > efficienciesRel172HCP_e24vhi_medium1_MediumPP;
  std::vector< std::vector<float> > uncertaintiesRel172HCP_e24vhi_medium1_MediumPP;
  std::vector< std::vector<float> > efficienciesRel172HCP_e24vhi_medium1_MediumPPET;
  std::vector< std::vector<float> > uncertaintiesRel172HCP_e24vhi_medium1_MediumPPET;

  std::vector< std::vector<float> > MCefficienciesRel172HCP_e24vhi_medium1_MediumPP;
  std::vector< std::vector<float> > MCefficienciesRel172HCP_e24vhi_medium1_MediumPPET;

  std::vector< std::vector<float> > efficienciesRel172HCP_e24vhi_medium1_TightPP;
  std::vector< std::vector<float> > uncertaintiesRel172HCP_e24vhi_medium1_TightPP;
  std::vector< std::vector<float> > efficienciesRel172HCP_e24vhi_medium1_TightPPET;
  std::vector< std::vector<float> > uncertaintiesRel172HCP_e24vhi_medium1_TightPPET;

  std::vector< std::vector<float> > MCefficienciesRel172HCP_e24vhi_medium1_TightPP;
  std::vector< std::vector<float> > MCefficienciesRel172HCP_e24vhi_medium1_TightPPET;

  std::vector< std::vector<float> > efficienciesRel172HCP_e24vhi_medium1_ML;
  std::vector< std::vector<float> > uncertaintiesRel172HCP_e24vhi_medium1_ML;
  std::vector< std::vector<float> > efficienciesRel172HCP_e24vhi_medium1_MLET;
  std::vector< std::vector<float> > uncertaintiesRel172HCP_e24vhi_medium1_MLET;

  std::vector< std::vector<float> > MCefficienciesRel172HCP_e24vhi_medium1_ML;
  std::vector< std::vector<float> > MCefficienciesRel172HCP_e24vhi_medium1_MLET;

  std::vector< std::vector<float> > efficienciesRel172HCP_AFII_e24vhi_medium1_LoosePP;
  std::vector< std::vector<float> > uncertaintiesRel172HCP_AFII_e24vhi_medium1_LoosePP;
  std::vector< std::vector<float> > efficienciesRel172HCP_AFII_e24vhi_medium1_LoosePPET;
  std::vector< std::vector<float> > uncertaintiesRel172HCP_AFII_e24vhi_medium1_LoosePPET;

  std::vector< std::vector<float> > MCefficienciesRel172HCP_AFII_e24vhi_medium1_LoosePP;
  std::vector< std::vector<float> > MCefficienciesRel172HCP_AFII_e24vhi_medium1_LoosePPET;

  std::vector< std::vector<float> > efficienciesRel172HCP_AFII_e24vhi_medium1_MediumPP;
  std::vector< std::vector<float> > uncertaintiesRel172HCP_AFII_e24vhi_medium1_MediumPP;
  std::vector< std::vector<float> > efficienciesRel172HCP_AFII_e24vhi_medium1_MediumPPET;
  std::vector< std::vector<float> > uncertaintiesRel172HCP_AFII_e24vhi_medium1_MediumPPET;

  std::vector< std::vector<float> > MCefficienciesRel172HCP_AFII_e24vhi_medium1_MediumPP;
  std::vector< std::vector<float> > MCefficienciesRel172HCP_AFII_e24vhi_medium1_MediumPPET;

  std::vector< std::vector<float> > efficienciesRel172HCP_AFII_e24vhi_medium1_TightPP;
  std::vector< std::vector<float> > uncertaintiesRel172HCP_AFII_e24vhi_medium1_TightPP;
  std::vector< std::vector<float> > efficienciesRel172HCP_AFII_e24vhi_medium1_TightPPET;
  std::vector< std::vector<float> > uncertaintiesRel172HCP_AFII_e24vhi_medium1_TightPPET;

  std::vector< std::vector<float> > MCefficienciesRel172HCP_AFII_e24vhi_medium1_TightPP;
  std::vector< std::vector<float> > MCefficienciesRel172HCP_AFII_e24vhi_medium1_TightPPET;

  std::vector< std::vector<float> > efficienciesRel172HCP_AFII_e24vhi_medium1_ML;
  std::vector< std::vector<float> > uncertaintiesRel172HCP_AFII_e24vhi_medium1_ML;
  std::vector< std::vector<float> > efficienciesRel172HCP_AFII_e24vhi_medium1_MLET;
  std::vector< std::vector<float> > uncertaintiesRel172HCP_AFII_e24vhi_medium1_MLET;

  std::vector< std::vector<float> > MCefficienciesRel172HCP_AFII_e24vhi_medium1_ML;
  std::vector< std::vector<float> > MCefficienciesRel172HCP_AFII_e24vhi_medium1_MLET;


  #ifdef ROOTCORE
  ClassDef(egammaSFclass,1)
  #endif

};

#endif



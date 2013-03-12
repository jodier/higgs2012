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
//    * Forward Medium SF, detailed G4 FCAL  (set=47)
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
// ONLY for release 16.6, 2011 data there are separete functions
// for Forward Electrons (|eta|>=2.5)
// std::pair<float,float> sf_error = objsf->scaleFactorForward(eta, set)
// where eta = electron eta = cluster eta (as no track)
// cuts are ForwardLoose (set=0) or ForwardTight (set=2)
// 

#include "egammaAnalysisUtils/egammaSFclass.h"
#include <cmath>

egammaSFclass::egammaSFclass()
{
  //Definition of the eta binning
  m_Etabins.push_back(-2.47);
  m_Etabins.push_back(-2.01); 
  m_Etabins.push_back(-1.52); 
  m_Etabins.push_back(-1.37); 
  m_Etabins.push_back(-0.8); 
  m_Etabins.push_back(0); 
  m_Etabins.push_back(0.8); 
  m_Etabins.push_back(1.37); 
  m_Etabins.push_back(1.52); 
  m_Etabins.push_back(2.01); 
  m_Etabins.push_back(2.47);
  //Definition of the fine eta binning
  m_FineEtabins.push_back(-2.47);
  m_FineEtabins.push_back(-2.37);
  m_FineEtabins.push_back(-2.01);
  m_FineEtabins.push_back(-1.81);
  m_FineEtabins.push_back(-1.52);
  m_FineEtabins.push_back(-1.37);
  m_FineEtabins.push_back(-1.15);
  m_FineEtabins.push_back(-0.8 );
  m_FineEtabins.push_back(-0.6 );
  m_FineEtabins.push_back(-0.1 );
  m_FineEtabins.push_back( 0.  );
  m_FineEtabins.push_back( 0.1 );
  m_FineEtabins.push_back( 0.6 );
  m_FineEtabins.push_back( 0.8 );
  m_FineEtabins.push_back( 1.15);
  m_FineEtabins.push_back( 1.37);
  m_FineEtabins.push_back( 1.52);
  m_FineEtabins.push_back( 1.81);
  m_FineEtabins.push_back( 2.01);
  m_FineEtabins.push_back( 2.37);
  m_FineEtabins.push_back( 2.47);
  //Definition of the eta binning with 11 bins
  m_11Etabins.push_back(-2.47);
  m_11Etabins.push_back(-2.01); 
  m_11Etabins.push_back(-1.52); 
  m_11Etabins.push_back(-1.37); 
  m_11Etabins.push_back(-0.8); 
  m_11Etabins.push_back(-0.1); 
  m_11Etabins.push_back(0.1); 
  m_11Etabins.push_back(0.8); 
  m_11Etabins.push_back(1.37); 
  m_11Etabins.push_back(1.52); 
  m_11Etabins.push_back(2.01); 
  m_11Etabins.push_back(2.47);
  //Definition of the eta binning for forward electrons
  m_FwdEtabins.push_back(2.5);
  m_FwdEtabins.push_back(2.6);
  m_FwdEtabins.push_back(2.7);
  m_FwdEtabins.push_back(2.8);
  m_FwdEtabins.push_back(2.9);
  m_FwdEtabins.push_back(3.0);
  m_FwdEtabins.push_back(3.16);
  m_FwdEtabins.push_back(3.35);
  m_FwdEtabins.push_back(3.6);
  m_FwdEtabins.push_back(4.0);
  m_FwdEtabins.push_back(4.9);

  //Definition of the ET binning
  m_ETbins.push_back(0.);
  m_ETbins.push_back(20000.); 
  m_ETbins.push_back(25000.); 
  m_ETbins.push_back(30000.); 
  m_ETbins.push_back(35000.); 
  m_ETbins.push_back(40000.); 
  m_ETbins.push_back(45000.); 
  m_ETbins.push_back(500000000.); 
  //Definition of the ET binning on the full range
  m_ETbinsFullRange.push_back(    0.);
  m_ETbinsFullRange.push_back( 7000.);
  m_ETbinsFullRange.push_back(10000.);
  m_ETbinsFullRange.push_back(15000.);
  m_ETbinsFullRange.push_back(20000.); 
  m_ETbinsFullRange.push_back(25000.); 
  m_ETbinsFullRange.push_back(30000.); 
  m_ETbinsFullRange.push_back(35000.); 
  m_ETbinsFullRange.push_back(40000.); 
  m_ETbinsFullRange.push_back(45000.); 
  m_ETbinsFullRange.push_back(500000000.); 
  //Definition of the ET binning for trigger
  m_ETbinsTrigger.push_back(21000.);
  m_ETbinsTrigger.push_back(23000.);
  m_ETbinsTrigger.push_back(25000.); 
  m_ETbinsTrigger.push_back(30000.); 
  m_ETbinsTrigger.push_back(35000.); 
  m_ETbinsTrigger.push_back(40000.); 
  m_ETbinsTrigger.push_back(500000000.); 

  //Definition of the ET binning for trigger - 2012 e24
  m_ETbinsTrigger_e24.push_back(25000.);
  m_ETbinsTrigger_e24.push_back(26000.);
  m_ETbinsTrigger_e24.push_back(27000.);
  m_ETbinsTrigger_e24.push_back(28000.);
  m_ETbinsTrigger_e24.push_back(29000.);
  m_ETbinsTrigger_e24.push_back(30000.);
  m_ETbinsTrigger_e24.push_back(32000.);
  m_ETbinsTrigger_e24.push_back(35000.);
  m_ETbinsTrigger_e24.push_back(40000.);
  m_ETbinsTrigger_e24.push_back(45000.);
  m_ETbinsTrigger_e24.push_back(50000.);
  m_ETbinsTrigger_e24.push_back(60000.);
  m_ETbinsTrigger_e24.push_back(80000.);
  m_ETbinsTrigger_e24.push_back(150000.);
  m_ETbinsTrigger_e24.push_back(200000.);
  m_ETbinsTrigger_e24.push_back(500000000.); 

  //Definition of the ET binning for trigger - 2012 e12
  m_ETbinsTrigger_e12.push_back(14000.);
  m_ETbinsTrigger_e12.push_back(15000.);
  m_ETbinsTrigger_e12.push_back(17000.);
  m_ETbinsTrigger_e12.push_back(20000.);
  m_ETbinsTrigger_e12.push_back(25000.);
  m_ETbinsTrigger_e12.push_back(30000.);
  m_ETbinsTrigger_e12.push_back(35000.);
  m_ETbinsTrigger_e12.push_back(40000.);
  m_ETbinsTrigger_e12.push_back(45000.);
  m_ETbinsTrigger_e12.push_back(50000.);
  m_ETbinsTrigger_e12.push_back(60000.);
  m_ETbinsTrigger_e12.push_back(80000.);
  m_ETbinsTrigger_e12.push_back(100000.);
  m_ETbinsTrigger_e12.push_back(150000.);
  m_ETbinsTrigger_e12.push_back(500000000.);


  //For the scale factors of the standard egamma cuts 

  //Release 15
  //Probes between 30 and 50 GeV (plateau region)
  //Loose
  efficienciesRel15Loose3050.push_back(98.1); 
  efficienciesRel15Loose3050.push_back(99.0); 
  efficienciesRel15Loose3050.push_back(0.); 
  efficienciesRel15Loose3050.push_back(98.6); 
  efficienciesRel15Loose3050.push_back(99.5); 
  efficienciesRel15Loose3050.push_back(99.1); 
  efficienciesRel15Loose3050.push_back(98.8); 
  efficienciesRel15Loose3050.push_back(0.); 
  efficienciesRel15Loose3050.push_back(99.9); 
  efficienciesRel15Loose3050.push_back(98.2);
  uncertaintiesRel15Loose3050.push_back(1.6); 
  uncertaintiesRel15Loose3050.push_back( 1.5); 
  uncertaintiesRel15Loose3050.push_back(0.); 
  uncertaintiesRel15Loose3050.push_back( 1.5); 
  uncertaintiesRel15Loose3050.push_back( 1.5); 
  uncertaintiesRel15Loose3050.push_back( 1.5); 
  uncertaintiesRel15Loose3050.push_back( 1.5); 
  uncertaintiesRel15Loose3050.push_back(0.); 
  uncertaintiesRel15Loose3050.push_back( 1.5); 
  uncertaintiesRel15Loose3050.push_back( 1.6);
  //Medium
  efficienciesRel15Medium3050.push_back(95.4); 
  efficienciesRel15Medium3050.push_back(98.7);
  efficienciesRel15Medium3050.push_back(0.); 
  efficienciesRel15Medium3050.push_back(97.9);
  efficienciesRel15Medium3050.push_back(98.1);
  efficienciesRel15Medium3050.push_back(97.7); 
  efficienciesRel15Medium3050.push_back(97.9); 
  efficienciesRel15Medium3050.push_back(0.); 
  efficienciesRel15Medium3050.push_back(99.9); 
  efficienciesRel15Medium3050.push_back(97.4);
  uncertaintiesRel15Medium3050.push_back(1.7);
  uncertaintiesRel15Medium3050.push_back( 1.6);
  uncertaintiesRel15Medium3050.push_back(0.); 
  uncertaintiesRel15Medium3050.push_back( 1.6);
  uncertaintiesRel15Medium3050.push_back( 1.5); 
  uncertaintiesRel15Medium3050.push_back( 1.5); 
  uncertaintiesRel15Medium3050.push_back( 1.5); 
  uncertaintiesRel15Medium3050.push_back(0.); 
  uncertaintiesRel15Medium3050.push_back( 1.6);
  uncertaintiesRel15Medium3050.push_back( 1.7);
  //Tight
  efficienciesRel15Tight3050.push_back(92.3); 
  efficienciesRel15Tight3050.push_back(99.2); 
  efficienciesRel15Tight3050.push_back(0.);
  efficienciesRel15Tight3050.push_back(101.5); 
  efficienciesRel15Tight3050.push_back(98.9); 
  efficienciesRel15Tight3050.push_back(99.9);
  efficienciesRel15Tight3050.push_back(104.2); 
  efficienciesRel15Tight3050.push_back(0.);
  efficienciesRel15Tight3050.push_back(102.6); 
  efficienciesRel15Tight3050.push_back(95.5);
  uncertaintiesRel15Tight3050.push_back(3.3);
  uncertaintiesRel15Tight3050.push_back( 2.3); 
  uncertaintiesRel15Tight3050.push_back(0.);
  uncertaintiesRel15Tight3050.push_back( 2.0); 
  uncertaintiesRel15Tight3050.push_back( 1.8); 
  uncertaintiesRel15Tight3050.push_back( 1.8);
  uncertaintiesRel15Tight3050.push_back( 2.5); 
  uncertaintiesRel15Tight3050.push_back(0.); 
  uncertaintiesRel15Tight3050.push_back( 5.0); 
  uncertaintiesRel15Tight3050.push_back( 3.2);

  //Probes between 20 and 50 GeV
  //Loose
  efficienciesRel15Loose2050.push_back(97.6); 
  efficienciesRel15Loose2050.push_back(99.0); 
  efficienciesRel15Loose2050.push_back(0.); 
  efficienciesRel15Loose2050.push_back(98.2); 
  efficienciesRel15Loose2050.push_back(99.1); 
  efficienciesRel15Loose2050.push_back(98.8); 
  efficienciesRel15Loose2050.push_back(98.2); 
  efficienciesRel15Loose2050.push_back(0.); 
  efficienciesRel15Loose2050.push_back(99.6); 
  efficienciesRel15Loose2050.push_back(97.4);
  uncertaintiesRel15Loose2050.push_back(1.6); 
  uncertaintiesRel15Loose2050.push_back(1.5); 
  uncertaintiesRel15Loose2050.push_back(0.); 
  uncertaintiesRel15Loose2050.push_back( 1.5); 
  uncertaintiesRel15Loose2050.push_back( 1.5); 
  uncertaintiesRel15Loose2050.push_back( 1.5); 
  uncertaintiesRel15Loose2050.push_back( 1.5); 
  uncertaintiesRel15Loose2050.push_back(0.); 
  uncertaintiesRel15Loose2050.push_back( 1.5); 
  uncertaintiesRel15Loose2050.push_back( 1.6);
  //Medium
  efficienciesRel15Medium2050.push_back(94.5); 
  efficienciesRel15Medium2050.push_back(98.8);
  efficienciesRel15Medium2050.push_back(0.); 
  efficienciesRel15Medium2050.push_back(97.2);
  efficienciesRel15Medium2050.push_back(97.4);
  efficienciesRel15Medium2050.push_back(97.2); 
  efficienciesRel15Medium2050.push_back(96.7); 
  efficienciesRel15Medium2050.push_back(0.); 
  efficienciesRel15Medium2050.push_back(99.5); 
  efficienciesRel15Medium2050.push_back(96.1);
  uncertaintiesRel15Medium2050.push_back(1.7);
  uncertaintiesRel15Medium2050.push_back( 1.6);
  uncertaintiesRel15Medium2050.push_back(0.); 
  uncertaintiesRel15Medium2050.push_back( 1.6);
  uncertaintiesRel15Medium2050.push_back( 1.5); 
  uncertaintiesRel15Medium2050.push_back( 1.5); 
  uncertaintiesRel15Medium2050.push_back( 1.5); 
  uncertaintiesRel15Medium2050.push_back(0.); 
  uncertaintiesRel15Medium2050.push_back( 2.9);
  uncertaintiesRel15Medium2050.push_back( 1.7);
  //Tight
  efficienciesRel15Tight2050.push_back(92.5); 
  efficienciesRel15Tight2050.push_back(99.5); 
  efficienciesRel15Tight2050.push_back(0.);
  efficienciesRel15Tight2050.push_back(100.6); 
  efficienciesRel15Tight2050.push_back(98.2); 
  efficienciesRel15Tight2050.push_back(98.7);
  efficienciesRel15Tight2050.push_back(103.3); 
  efficienciesRel15Tight2050.push_back(0.);
  efficienciesRel15Tight2050.push_back(102.8); 
  efficienciesRel15Tight2050.push_back(93.6);
  uncertaintiesRel15Tight2050.push_back(3.4);
  uncertaintiesRel15Tight2050.push_back( 2.4); 
  uncertaintiesRel15Tight2050.push_back(0.);
  uncertaintiesRel15Tight2050.push_back( 2.1); 
  uncertaintiesRel15Tight2050.push_back( 1.8); 
  uncertaintiesRel15Tight2050.push_back( 1.8);
  uncertaintiesRel15Tight2050.push_back( 2.5); 
  uncertaintiesRel15Tight2050.push_back(0.); 
  uncertaintiesRel15Tight2050.push_back( 4.5); 
  uncertaintiesRel15Tight2050.push_back( 3.4);


  //Release 16
  //Probes between 30 and 50 GeV (plateau region)
  //Medium
  efficienciesRel16Medium3050.push_back(98.8); 
  efficienciesRel16Medium3050.push_back(98.0);
  efficienciesRel16Medium3050.push_back(96.9); 
  efficienciesRel16Medium3050.push_back(98.0);
  efficienciesRel16Medium3050.push_back(97.4);
  efficienciesRel16Medium3050.push_back(98.1); 
  efficienciesRel16Medium3050.push_back(98.1); 
  efficienciesRel16Medium3050.push_back(98.3); 
  efficienciesRel16Medium3050.push_back(98.6); 
  efficienciesRel16Medium3050.push_back(97.5);
  uncertaintiesRel16Medium3050.push_back(0.8);
  uncertaintiesRel16Medium3050.push_back(0.9);
  uncertaintiesRel16Medium3050.push_back(2.5); 
  uncertaintiesRel16Medium3050.push_back(0.8);
  uncertaintiesRel16Medium3050.push_back(0.7); 
  uncertaintiesRel16Medium3050.push_back(0.7); 
  uncertaintiesRel16Medium3050.push_back(0.8); 
  uncertaintiesRel16Medium3050.push_back(2.6); 
  uncertaintiesRel16Medium3050.push_back(0.8);
  uncertaintiesRel16Medium3050.push_back(0.8);
  //Tight
  efficienciesRel16Tight3050.push_back(102.0); 
  efficienciesRel16Tight3050.push_back(102.7); 
  efficienciesRel16Tight3050.push_back(114.4);
  efficienciesRel16Tight3050.push_back(106.7); 
  efficienciesRel16Tight3050.push_back( 99.0); 
  efficienciesRel16Tight3050.push_back(100.1);
  efficienciesRel16Tight3050.push_back(105.7); 
  efficienciesRel16Tight3050.push_back(110.8);
  efficienciesRel16Tight3050.push_back(104.2); 
  efficienciesRel16Tight3050.push_back(102.7);
  uncertaintiesRel16Tight3050.push_back(3.0);
  uncertaintiesRel16Tight3050.push_back(1.1); 
  uncertaintiesRel16Tight3050.push_back(3.9);
  uncertaintiesRel16Tight3050.push_back(1.1); 
  uncertaintiesRel16Tight3050.push_back(0.8); 
  uncertaintiesRel16Tight3050.push_back(0.8);
  uncertaintiesRel16Tight3050.push_back(0.9); 
  uncertaintiesRel16Tight3050.push_back(4.6); 
  uncertaintiesRel16Tight3050.push_back(2.6); 
  uncertaintiesRel16Tight3050.push_back(1.2);

  //Probes between 20 and 50 GeV
  //Medium
  efficienciesRel16Medium2050.push_back(97.6); 
  efficienciesRel16Medium2050.push_back(96.8);
  efficienciesRel16Medium2050.push_back(97.7); 
  efficienciesRel16Medium2050.push_back(97.1);
  efficienciesRel16Medium2050.push_back(96.8);
  efficienciesRel16Medium2050.push_back(97.6); 
  efficienciesRel16Medium2050.push_back(97.2); 
  efficienciesRel16Medium2050.push_back(98.2); 
  efficienciesRel16Medium2050.push_back(97.9); 
  efficienciesRel16Medium2050.push_back(96.2);
  uncertaintiesRel16Medium2050.push_back(1.0);
  uncertaintiesRel16Medium2050.push_back(1.0);
  uncertaintiesRel16Medium2050.push_back(3.3); 
  uncertaintiesRel16Medium2050.push_back(1.1);
  uncertaintiesRel16Medium2050.push_back(0.8); 
  uncertaintiesRel16Medium2050.push_back(0.8); 
  uncertaintiesRel16Medium2050.push_back(0.9); 
  uncertaintiesRel16Medium2050.push_back(3.2); 
  uncertaintiesRel16Medium2050.push_back(1.0);
  uncertaintiesRel16Medium2050.push_back(2.8);
  //Tight
  efficienciesRel16Tight2050.push_back(100.2); 
  efficienciesRel16Tight2050.push_back(101.5); 
  efficienciesRel16Tight2050.push_back(117.9);
  efficienciesRel16Tight2050.push_back(105.7); 
  efficienciesRel16Tight2050.push_back( 98.1); 
  efficienciesRel16Tight2050.push_back( 99.1);
  efficienciesRel16Tight2050.push_back(105.2); 
  efficienciesRel16Tight2050.push_back(113.9);
  efficienciesRel16Tight2050.push_back(103.8); 
  efficienciesRel16Tight2050.push_back(101.2);
  uncertaintiesRel16Tight2050.push_back(1.1);
  uncertaintiesRel16Tight2050.push_back(1.2); 
  uncertaintiesRel16Tight2050.push_back(4.4);
  uncertaintiesRel16Tight2050.push_back(1.5); 
  uncertaintiesRel16Tight2050.push_back(0.9); 
  uncertaintiesRel16Tight2050.push_back(1.0);
  uncertaintiesRel16Tight2050.push_back(1.1); 
  uncertaintiesRel16Tight2050.push_back(5.2); 
  uncertaintiesRel16Tight2050.push_back(3.0); 
  uncertaintiesRel16Tight2050.push_back(1.3);


  //For the ET-corrections of the scale factors
  //Medium
  ETCorrectionsMediumRel16.push_back( 79.6);
  ETCorrectionsMediumRel16.push_back( 93.9);
  ETCorrectionsMediumRel16.push_back( 96.2);
  ETCorrectionsMediumRel16.push_back( 99.7);
  ETCorrectionsMediumRel16.push_back(100.6);
  ETCorrectionsMediumRel16.push_back(100.4);
  ETCorrectionsMediumRel16.push_back(101.00);
  uncertaintiesETCorrectionsMediumRel16.push_back( 9.4);
  uncertaintiesETCorrectionsMediumRel16.push_back( 3.6);
  uncertaintiesETCorrectionsMediumRel16.push_back( 1.4);
  uncertaintiesETCorrectionsMediumRel16.push_back( 0.7);
  uncertaintiesETCorrectionsMediumRel16.push_back( 0.5);
  uncertaintiesETCorrectionsMediumRel16.push_back( 0.7);
  uncertaintiesETCorrectionsMediumRel16.push_back( 1.7);
  //Medium
  ETCorrectionsTightRel16.push_back( 76.7);
  ETCorrectionsTightRel16.push_back( 93.6);
  ETCorrectionsTightRel16.push_back( 95.1);
  ETCorrectionsTightRel16.push_back( 99.9);
  ETCorrectionsTightRel16.push_back(100.4);
  ETCorrectionsTightRel16.push_back(100.0);
  ETCorrectionsTightRel16.push_back(100.7);
  uncertaintiesETCorrectionsTightRel16.push_back(10.0);
  uncertaintiesETCorrectionsTightRel16.push_back( 3.7);
  uncertaintiesETCorrectionsTightRel16.push_back( 1.6);
  uncertaintiesETCorrectionsTightRel16.push_back( 0.9);
  uncertaintiesETCorrectionsTightRel16.push_back( 0.7);
  uncertaintiesETCorrectionsTightRel16.push_back( 0.9);
  uncertaintiesETCorrectionsTightRel16.push_back( 1.8);



  //Release 16.6 Data 2010
  //Probes between 30 and 50 GeV (plateau region)
  //Medium
  efficienciesRel166Data2010Medium3050.push_back(98.44); 
  efficienciesRel166Data2010Medium3050.push_back(96.93);
  efficienciesRel166Data2010Medium3050.push_back(96.61); 
  efficienciesRel166Data2010Medium3050.push_back(96.87);
  efficienciesRel166Data2010Medium3050.push_back(97.06);
  efficienciesRel166Data2010Medium3050.push_back(97.49); 
  efficienciesRel166Data2010Medium3050.push_back(97.04); 
  efficienciesRel166Data2010Medium3050.push_back(97.17); 
  efficienciesRel166Data2010Medium3050.push_back(97.31); 
  efficienciesRel166Data2010Medium3050.push_back(97.51);
  uncertaintiesRel166Data2010Medium3050.push_back(2.14);
  uncertaintiesRel166Data2010Medium3050.push_back(2.20);
  uncertaintiesRel166Data2010Medium3050.push_back(2.84); 
  uncertaintiesRel166Data2010Medium3050.push_back(2.13);
  uncertaintiesRel166Data2010Medium3050.push_back(2.18); 
  uncertaintiesRel166Data2010Medium3050.push_back(2.10); 
  uncertaintiesRel166Data2010Medium3050.push_back(2.13); 
  uncertaintiesRel166Data2010Medium3050.push_back(2.89); 
  uncertaintiesRel166Data2010Medium3050.push_back(2.13);
  uncertaintiesRel166Data2010Medium3050.push_back(2.21);
  //Tight
  efficienciesRel166Data2010Tight3050.push_back(101.47); 
  efficienciesRel166Data2010Tight3050.push_back(104.02); 
  efficienciesRel166Data2010Tight3050.push_back(112.70);
  efficienciesRel166Data2010Tight3050.push_back(106.82); 
  efficienciesRel166Data2010Tight3050.push_back( 99.35); 
  efficienciesRel166Data2010Tight3050.push_back(100.13);
  efficienciesRel166Data2010Tight3050.push_back(105.94); 
  efficienciesRel166Data2010Tight3050.push_back(113.57);
  efficienciesRel166Data2010Tight3050.push_back(105.48); 
  efficienciesRel166Data2010Tight3050.push_back(101.99);
  uncertaintiesRel166Data2010Tight3050.push_back(3.46);
  uncertaintiesRel166Data2010Tight3050.push_back(2.65); 
  uncertaintiesRel166Data2010Tight3050.push_back(3.65);
  uncertaintiesRel166Data2010Tight3050.push_back(2.49); 
  uncertaintiesRel166Data2010Tight3050.push_back(2.33); 
  uncertaintiesRel166Data2010Tight3050.push_back(2.28);
  uncertaintiesRel166Data2010Tight3050.push_back(2.45); 
  uncertaintiesRel166Data2010Tight3050.push_back(3.72); 
  uncertaintiesRel166Data2010Tight3050.push_back(3.38); 
  uncertaintiesRel166Data2010Tight3050.push_back(2.70);

  //Probes between 20 and 50 GeV
  //Medium
  efficienciesRel166Data2010Medium2050.push_back(97.35); 
  efficienciesRel166Data2010Medium2050.push_back(95.86);
  efficienciesRel166Data2010Medium2050.push_back(96.25); 
  efficienciesRel166Data2010Medium2050.push_back(95.80);
  efficienciesRel166Data2010Medium2050.push_back(96.01);
  efficienciesRel166Data2010Medium2050.push_back(96.84); 
  efficienciesRel166Data2010Medium2050.push_back(96.04); 
  efficienciesRel166Data2010Medium2050.push_back(96.54); 
  efficienciesRel166Data2010Medium2050.push_back(96.59); 
  efficienciesRel166Data2010Medium2050.push_back(96.33);
  uncertaintiesRel166Data2010Medium2050.push_back(2.21);
  uncertaintiesRel166Data2010Medium2050.push_back(2.25);
  uncertaintiesRel166Data2010Medium2050.push_back(3.22); 
  uncertaintiesRel166Data2010Medium2050.push_back(2.27);
  uncertaintiesRel166Data2010Medium2050.push_back(2.23); 
  uncertaintiesRel166Data2010Medium2050.push_back(2.13); 
  uncertaintiesRel166Data2010Medium2050.push_back(2.17); 
  uncertaintiesRel166Data2010Medium2050.push_back(3.20); 
  uncertaintiesRel166Data2010Medium2050.push_back(2.24);
  uncertaintiesRel166Data2010Medium2050.push_back(2.41);
  //Tight
  efficienciesRel166Data2010Tight2050.push_back(99.90); 
  efficienciesRel166Data2010Tight2050.push_back(103.11); 
  efficienciesRel166Data2010Tight2050.push_back(116.16);
  efficienciesRel166Data2010Tight2050.push_back(105.70); 
  efficienciesRel166Data2010Tight2050.push_back( 97.98); 
  efficienciesRel166Data2010Tight2050.push_back( 99.08);
  efficienciesRel166Data2010Tight2050.push_back(105.23); 
  efficienciesRel166Data2010Tight2050.push_back(115.12);
  efficienciesRel166Data2010Tight2050.push_back(104.91); 
  efficienciesRel166Data2010Tight2050.push_back(101.99);
  uncertaintiesRel166Data2010Tight2050.push_back(2.28);
  uncertaintiesRel166Data2010Tight2050.push_back(2.89); 
  uncertaintiesRel166Data2010Tight2050.push_back(4.35);
  uncertaintiesRel166Data2010Tight2050.push_back(2.72); 
  uncertaintiesRel166Data2010Tight2050.push_back(2.40); 
  uncertaintiesRel166Data2010Tight2050.push_back(2.24);
  uncertaintiesRel166Data2010Tight2050.push_back(2.48); 
  uncertaintiesRel166Data2010Tight2050.push_back(4.17); 
  uncertaintiesRel166Data2010Tight2050.push_back(2.45); 
  uncertaintiesRel166Data2010Tight2050.push_back(3.29);
  //For the ET-corrections of the scale factors
  //Medium
  ETCorrectionsMediumRel166Data2010.push_back(80.60);
  ETCorrectionsMediumRel166Data2010.push_back(92.07);
  ETCorrectionsMediumRel166Data2010.push_back(96.34);
  ETCorrectionsMediumRel166Data2010.push_back(100.19);
  ETCorrectionsMediumRel166Data2010.push_back(101.54);
  ETCorrectionsMediumRel166Data2010.push_back(101.25);
  ETCorrectionsMediumRel166Data2010.push_back(102.29);
  uncertaintiesETCorrectionsMediumRel166Data2010.push_back( 9.60);
  uncertaintiesETCorrectionsMediumRel166Data2010.push_back( 3.27);
  uncertaintiesETCorrectionsMediumRel166Data2010.push_back( 1.40);
  uncertaintiesETCorrectionsMediumRel166Data2010.push_back( 0.70);
  uncertaintiesETCorrectionsMediumRel166Data2010.push_back( 0.53);
  uncertaintiesETCorrectionsMediumRel166Data2010.push_back( 0.74);
  uncertaintiesETCorrectionsMediumRel166Data2010.push_back( 1.59);
  //Tight
  ETCorrectionsTightRel166Data2010.push_back(77.78);
  ETCorrectionsTightRel166Data2010.push_back(91.84);
  ETCorrectionsTightRel166Data2010.push_back(95.67);
  ETCorrectionsTightRel166Data2010.push_back(100.86);
  ETCorrectionsTightRel166Data2010.push_back(101.83);
  ETCorrectionsTightRel166Data2010.push_back(101.33);
  ETCorrectionsTightRel166Data2010.push_back(102.10);
  uncertaintiesETCorrectionsTightRel166Data2010.push_back(10.29);
  uncertaintiesETCorrectionsTightRel166Data2010.push_back( 3.47);
  uncertaintiesETCorrectionsTightRel166Data2010.push_back( 1.52);
  uncertaintiesETCorrectionsTightRel166Data2010.push_back( 1.04);
  uncertaintiesETCorrectionsTightRel166Data2010.push_back( 0.66);
  uncertaintiesETCorrectionsTightRel166Data2010.push_back( 0.92);
  uncertaintiesETCorrectionsTightRel166Data2010.push_back( 1.90);


  //Release 16.6 Data 2011 EPS recommendations
  //Identification for probes between 20 and 50 GeV
  //Medium
  efficienciesRel166EPSMedium2050.push_back(95.7273);
  efficienciesRel166EPSMedium2050.push_back(95.5243);
  efficienciesRel166EPSMedium2050.push_back(96.403);
  efficienciesRel166EPSMedium2050.push_back(96.3494);
  efficienciesRel166EPSMedium2050.push_back(97.9518);
  efficienciesRel166EPSMedium2050.push_back(96.3292);
  efficienciesRel166EPSMedium2050.push_back(97.0952);
  efficienciesRel166EPSMedium2050.push_back(96.3317);
  efficienciesRel166EPSMedium2050.push_back(97.1977);
  efficienciesRel166EPSMedium2050.push_back(97.8678);
  efficienciesRel166EPSMedium2050.push_back(96.5697);
  efficienciesRel166EPSMedium2050.push_back(96.7783);
  efficienciesRel166EPSMedium2050.push_back(97.0532);
  efficienciesRel166EPSMedium2050.push_back(96.4621);
  efficienciesRel166EPSMedium2050.push_back(95.3501);
  efficienciesRel166EPSMedium2050.push_back(97.9656);
  efficienciesRel166EPSMedium2050.push_back(96.3031);
  efficienciesRel166EPSMedium2050.push_back(97.3978);
  efficienciesRel166EPSMedium2050.push_back(95.7546);
  efficienciesRel166EPSMedium2050.push_back(97.2443);
  uncertaintiesRel166EPSMedium2050.push_back(0.758538);
  uncertaintiesRel166EPSMedium2050.push_back(1.48083);
  uncertaintiesRel166EPSMedium2050.push_back(0.778086);
  uncertaintiesRel166EPSMedium2050.push_back(0.496963);
  uncertaintiesRel166EPSMedium2050.push_back(1.0011);
  uncertaintiesRel166EPSMedium2050.push_back(0.694056);
  uncertaintiesRel166EPSMedium2050.push_back(0.603261);
  uncertaintiesRel166EPSMedium2050.push_back(0.719089);
  uncertaintiesRel166EPSMedium2050.push_back(0.635625);
  uncertaintiesRel166EPSMedium2050.push_back(0.825545);
  uncertaintiesRel166EPSMedium2050.push_back(0.777055);
  uncertaintiesRel166EPSMedium2050.push_back(0.655198);
  uncertaintiesRel166EPSMedium2050.push_back(0.736623);
  uncertaintiesRel166EPSMedium2050.push_back(0.633197);
  uncertaintiesRel166EPSMedium2050.push_back(1.04172);
  uncertaintiesRel166EPSMedium2050.push_back(0.612204);
  uncertaintiesRel166EPSMedium2050.push_back(0.47725);
  uncertaintiesRel166EPSMedium2050.push_back(1.32532);
  uncertaintiesRel166EPSMedium2050.push_back(0.74313);
  uncertaintiesRel166EPSMedium2050.push_back(1.44683);
  //Tight
  efficienciesRel166EPSTight2050.push_back( 99.9569);
  efficienciesRel166EPSTight2050.push_back( 99.1664);
  efficienciesRel166EPSTight2050.push_back(103.421 );
  efficienciesRel166EPSTight2050.push_back(102.688 );
  efficienciesRel166EPSTight2050.push_back(113.028 );
  efficienciesRel166EPSTight2050.push_back(111.078 );
  efficienciesRel166EPSTight2050.push_back(103.481 );
  efficienciesRel166EPSTight2050.push_back( 99.5783);
  efficienciesRel166EPSTight2050.push_back( 98.4303);
  efficienciesRel166EPSTight2050.push_back(100.837 );
  efficienciesRel166EPSTight2050.push_back( 99.1868);
  efficienciesRel166EPSTight2050.push_back( 98.1188);
  efficienciesRel166EPSTight2050.push_back(100.492 );
  efficienciesRel166EPSTight2050.push_back(102.816 );
  efficienciesRel166EPSTight2050.push_back(109.09  );
  efficienciesRel166EPSTight2050.push_back(113.772 );
  efficienciesRel166EPSTight2050.push_back(103.355 );
  efficienciesRel166EPSTight2050.push_back(103.454 );
  efficienciesRel166EPSTight2050.push_back( 98.4376);
  efficienciesRel166EPSTight2050.push_back(102.174 );
  uncertaintiesRel166EPSTight2050.push_back(2.82899);
  uncertaintiesRel166EPSTight2050.push_back(1.47076);
  uncertaintiesRel166EPSTight2050.push_back(2.64305);
  uncertaintiesRel166EPSTight2050.push_back(0.692373);
  uncertaintiesRel166EPSTight2050.push_back(2.0146 );
  uncertaintiesRel166EPSTight2050.push_back(0.967662);
  uncertaintiesRel166EPSTight2050.push_back(0.714802);
  uncertaintiesRel166EPSTight2050.push_back(0.807023);
  uncertaintiesRel166EPSTight2050.push_back(0.686988);
  uncertaintiesRel166EPSTight2050.push_back(1.4562);
  uncertaintiesRel166EPSTight2050.push_back(0.984975);
  uncertaintiesRel166EPSTight2050.push_back(0.703155);
  uncertaintiesRel166EPSTight2050.push_back(0.80346);
  uncertaintiesRel166EPSTight2050.push_back(0.742777);
  uncertaintiesRel166EPSTight2050.push_back(1.78409);
  uncertaintiesRel166EPSTight2050.push_back(1.13598);
  uncertaintiesRel166EPSTight2050.push_back(0.716145);
  uncertaintiesRel166EPSTight2050.push_back(2.28302);
  uncertaintiesRel166EPSTight2050.push_back(1.13891);
  uncertaintiesRel166EPSTight2050.push_back(2.02877);
  //Identification for low ET probes
  //Medium
  efficienciesRel166EPSMediumLowET.push_back(91.16);
  efficienciesRel166EPSMediumLowET.push_back(99.84);
  efficienciesRel166EPSMediumLowET.push_back( 0.00);
  efficienciesRel166EPSMediumLowET.push_back(101.4);
  efficienciesRel166EPSMediumLowET.push_back(96.76);
  efficienciesRel166EPSMediumLowET.push_back(98.11);
  efficienciesRel166EPSMediumLowET.push_back(96.75);
  efficienciesRel166EPSMediumLowET.push_back( 0.00);
  efficienciesRel166EPSMediumLowET.push_back(86.38);
  efficienciesRel166EPSMediumLowET.push_back(84.37);
  uncertaintiesRel166EPSMediumLowET.push_back(11.0);
  uncertaintiesRel166EPSMediumLowET.push_back( 8.5);
  uncertaintiesRel166EPSMediumLowET.push_back( 0.0);
  uncertaintiesRel166EPSMediumLowET.push_back(10.8);
  uncertaintiesRel166EPSMediumLowET.push_back( 6.7);
  uncertaintiesRel166EPSMediumLowET.push_back( 7.0);
  uncertaintiesRel166EPSMediumLowET.push_back( 7.2);
  uncertaintiesRel166EPSMediumLowET.push_back( 0.0);
  uncertaintiesRel166EPSMediumLowET.push_back(10.1);
  uncertaintiesRel166EPSMediumLowET.push_back(10.2);
  //Tight
  efficienciesRel166EPSTightLowET.push_back(91.67);
  efficienciesRel166EPSTightLowET.push_back(100.6);
  efficienciesRel166EPSTightLowET.push_back( 0.00);
  efficienciesRel166EPSTightLowET.push_back(101.1);
  efficienciesRel166EPSTightLowET.push_back(96.88);
  efficienciesRel166EPSTightLowET.push_back(98.14);
  efficienciesRel166EPSTightLowET.push_back(98.23);
  efficienciesRel166EPSTightLowET.push_back( 0.00);
  efficienciesRel166EPSTightLowET.push_back(86.59);
  efficienciesRel166EPSTightLowET.push_back(84.39);
  uncertaintiesRel166EPSTightLowET.push_back(10.9);
  uncertaintiesRel166EPSTightLowET.push_back( 9.6);
  uncertaintiesRel166EPSTightLowET.push_back( 0.0);
  uncertaintiesRel166EPSTightLowET.push_back(10.5);
  uncertaintiesRel166EPSTightLowET.push_back( 6.1);
  uncertaintiesRel166EPSTightLowET.push_back( 6.1);
  uncertaintiesRel166EPSTightLowET.push_back( 9.5);
  uncertaintiesRel166EPSTightLowET.push_back( 0.0);
  uncertaintiesRel166EPSTightLowET.push_back(11.3);
  uncertaintiesRel166EPSTightLowET.push_back( 8.6);
  //For the ET-corrections of the identification scale factors
  //Medium
  ETCorrectionsMediumRel166EPS.push_back( 87.0781);
  ETCorrectionsMediumRel166EPS.push_back( 90.9091);
  ETCorrectionsMediumRel166EPS.push_back( 97.3568);
  ETCorrectionsMediumRel166EPS.push_back(100.453);
  ETCorrectionsMediumRel166EPS.push_back(101.55);
  ETCorrectionsMediumRel166EPS.push_back(101.365);
  ETCorrectionsMediumRel166EPS.push_back(102.087);
  uncertaintiesETCorrectionsMediumRel166EPS.push_back(6.00538);
  uncertaintiesETCorrectionsMediumRel166EPS.push_back(2.62057);
  uncertaintiesETCorrectionsMediumRel166EPS.push_back(0.93479);
  uncertaintiesETCorrectionsMediumRel166EPS.push_back(0.94788);
  uncertaintiesETCorrectionsMediumRel166EPS.push_back(0.43064);
  uncertaintiesETCorrectionsMediumRel166EPS.push_back(0.40351);
  uncertaintiesETCorrectionsMediumRel166EPS.push_back(0.53891);
  //Tight
  ETCorrectionsTightRel166EPS.push_back( 84.3469);
  ETCorrectionsTightRel166EPS.push_back( 89.3899);
  ETCorrectionsTightRel166EPS.push_back( 97.1825);
  ETCorrectionsTightRel166EPS.push_back(100.33);
  ETCorrectionsTightRel166EPS.push_back(101.319);
  ETCorrectionsTightRel166EPS.push_back(101.238);
  ETCorrectionsTightRel166EPS.push_back(101.552);
  uncertaintiesETCorrectionsTightRel166EPS.push_back(6.52625);
  uncertaintiesETCorrectionsTightRel166EPS.push_back(2.75939);
  uncertaintiesETCorrectionsTightRel166EPS.push_back(1.6303);
  uncertaintiesETCorrectionsTightRel166EPS.push_back(1.29104);
  uncertaintiesETCorrectionsTightRel166EPS.push_back(0.420933);
  uncertaintiesETCorrectionsTightRel166EPS.push_back(0.435997);
  uncertaintiesETCorrectionsTightRel166EPS.push_back(1.05739);
  //For the low ET electrons
  //Medium
  ETCorrectionsMediumRel166EPSFullRange.push_back(0.000/0.9666);
  ETCorrectionsMediumRel166EPSFullRange.push_back(97.36/0.9666);
  ETCorrectionsMediumRel166EPSFullRange.push_back(93.55/0.9666);
  uncertaintiesETCorrectionsMediumRel166EPSFullRange.push_back(7.25/0.9666);
  uncertaintiesETCorrectionsMediumRel166EPSFullRange.push_back(7.41/0.9666);
  uncertaintiesETCorrectionsMediumRel166EPSFullRange.push_back(8.57/0.9666);
  ETCorrectionsMediumRel166EPSFullRange.push_back( 87.0781);
  ETCorrectionsMediumRel166EPSFullRange.push_back( 90.9091);
  ETCorrectionsMediumRel166EPSFullRange.push_back( 97.3568);
  ETCorrectionsMediumRel166EPSFullRange.push_back(100.453);
  ETCorrectionsMediumRel166EPSFullRange.push_back(101.55);
  ETCorrectionsMediumRel166EPSFullRange.push_back(101.365);
  ETCorrectionsMediumRel166EPSFullRange.push_back(102.087);
  uncertaintiesETCorrectionsMediumRel166EPSFullRange.push_back(9.18078);
  uncertaintiesETCorrectionsMediumRel166EPSFullRange.push_back(2.62057);
  uncertaintiesETCorrectionsMediumRel166EPSFullRange.push_back(0.93479);
  uncertaintiesETCorrectionsMediumRel166EPSFullRange.push_back(0.94788);
  uncertaintiesETCorrectionsMediumRel166EPSFullRange.push_back(0.43064);
  uncertaintiesETCorrectionsMediumRel166EPSFullRange.push_back(0.40351);
  uncertaintiesETCorrectionsMediumRel166EPSFullRange.push_back(0.53891);
  //Tight
  ETCorrectionsTightRel166EPSFullRange.push_back(0.000/0.9673);
  ETCorrectionsTightRel166EPSFullRange.push_back(105.8/0.9673);
  ETCorrectionsTightRel166EPSFullRange.push_back(98.8/0.9673);
  uncertaintiesETCorrectionsTightRel166EPSFullRange.push_back(10.24/0.9673);
  uncertaintiesETCorrectionsTightRel166EPSFullRange.push_back(10.43/0.9673);  
  uncertaintiesETCorrectionsTightRel166EPSFullRange.push_back(10.50/0.9673);
  ETCorrectionsTightRel166EPSFullRange.push_back( 84.3469);
  ETCorrectionsTightRel166EPSFullRange.push_back( 89.3899);
  ETCorrectionsTightRel166EPSFullRange.push_back( 97.1825);
  ETCorrectionsTightRel166EPSFullRange.push_back(100.33);
  ETCorrectionsTightRel166EPSFullRange.push_back(101.319);
  ETCorrectionsTightRel166EPSFullRange.push_back(101.238);
  ETCorrectionsTightRel166EPSFullRange.push_back(101.552);
  uncertaintiesETCorrectionsTightRel166EPSFullRange.push_back(10.1599);
  uncertaintiesETCorrectionsTightRel166EPSFullRange.push_back(2.75939);
  uncertaintiesETCorrectionsTightRel166EPSFullRange.push_back(1.6303);
  uncertaintiesETCorrectionsTightRel166EPSFullRange.push_back(1.29104);
  uncertaintiesETCorrectionsTightRel166EPSFullRange.push_back(0.420933);
  uncertaintiesETCorrectionsTightRel166EPSFullRange.push_back(0.435997);
  uncertaintiesETCorrectionsTightRel166EPSFullRange.push_back(1.05739);
  //Trigger efficiency scale factors
  efficienciesRel166EPSTrigger.push_back(96.5517);
  efficienciesRel166EPSTrigger.push_back(97.3861);
  efficienciesRel166EPSTrigger.push_back(98.4245);
  efficienciesRel166EPSTrigger.push_back(98.6712);
  efficienciesRel166EPSTrigger.push_back(97.7936);
  efficienciesRel166EPSTrigger.push_back(99.7033);
  efficienciesRel166EPSTrigger.push_back(98.9571);
  efficienciesRel166EPSTrigger.push_back(98.4703);
  efficienciesRel166EPSTrigger.push_back(99.3016);
  efficienciesRel166EPSTrigger.push_back(99.1186);
  efficienciesRel166EPSTrigger.push_back(99.2838);
  efficienciesRel166EPSTrigger.push_back(99.2266);
  efficienciesRel166EPSTrigger.push_back(99.709);
  efficienciesRel166EPSTrigger.push_back(99.1478);
  efficienciesRel166EPSTrigger.push_back(99.5733);
  efficienciesRel166EPSTrigger.push_back(98.9866);
  efficienciesRel166EPSTrigger.push_back(99.8198);
  efficienciesRel166EPSTrigger.push_back(97.821);
  efficienciesRel166EPSTrigger.push_back(97.862);
  efficienciesRel166EPSTrigger.push_back(97.901);
  uncertaintiesRel166EPSTrigger.push_back(0.645476);
  uncertaintiesRel166EPSTrigger.push_back(0.588429);
  uncertaintiesRel166EPSTrigger.push_back(0.432384);
  uncertaintiesRel166EPSTrigger.push_back(0.43052);
  uncertaintiesRel166EPSTrigger.push_back(0.579508);
  uncertaintiesRel166EPSTrigger.push_back(0.410817);
  uncertaintiesRel166EPSTrigger.push_back(0.457);
  uncertaintiesRel166EPSTrigger.push_back(0.515013);
  uncertaintiesRel166EPSTrigger.push_back(0.402588);
  uncertaintiesRel166EPSTrigger.push_back(0.418344);
  uncertaintiesRel166EPSTrigger.push_back(0.415669);
  uncertaintiesRel166EPSTrigger.push_back(0.404291);
  uncertaintiesRel166EPSTrigger.push_back(0.407594);
  uncertaintiesRel166EPSTrigger.push_back(0.460203);
  uncertaintiesRel166EPSTrigger.push_back(0.410275);
  uncertaintiesRel166EPSTrigger.push_back(0.53542);
  uncertaintiesRel166EPSTrigger.push_back(0.425722);
  uncertaintiesRel166EPSTrigger.push_back(0.667037);
  uncertaintiesRel166EPSTrigger.push_back(0.426163);
  uncertaintiesRel166EPSTrigger.push_back(0.976323);
  //Reco+trackquality efficiencies
  efficienciesRel166EPSRecoTrkQual.push_back( 97.59);
  efficienciesRel166EPSRecoTrkQual.push_back(100.91);
  efficienciesRel166EPSRecoTrkQual.push_back(100.91);
  efficienciesRel166EPSRecoTrkQual.push_back(100.91);
  efficienciesRel166EPSRecoTrkQual.push_back(100.91);
  efficienciesRel166EPSRecoTrkQual.push_back(100.91);
  efficienciesRel166EPSRecoTrkQual.push_back(100.91);
  efficienciesRel166EPSRecoTrkQual.push_back( 99.84);
  efficienciesRel166EPSRecoTrkQual.push_back( 99.84);
  efficienciesRel166EPSRecoTrkQual.push_back( 99.84);
  efficienciesRel166EPSRecoTrkQual.push_back( 99.84);
  efficienciesRel166EPSRecoTrkQual.push_back( 99.84);
  efficienciesRel166EPSRecoTrkQual.push_back( 99.84);
  efficienciesRel166EPSRecoTrkQual.push_back(100.91);
  efficienciesRel166EPSRecoTrkQual.push_back(100.91);
  efficienciesRel166EPSRecoTrkQual.push_back(100.91);
  efficienciesRel166EPSRecoTrkQual.push_back(100.91);
  efficienciesRel166EPSRecoTrkQual.push_back(100.91);
  efficienciesRel166EPSRecoTrkQual.push_back(100.91);
  efficienciesRel166EPSRecoTrkQual.push_back( 97.59);
  uncertaintiesRel166EPSRecoTrkQual.push_back(1.84);
  uncertaintiesRel166EPSRecoTrkQual.push_back(0.70);
  uncertaintiesRel166EPSRecoTrkQual.push_back(0.70);
  uncertaintiesRel166EPSRecoTrkQual.push_back(0.70);
  uncertaintiesRel166EPSRecoTrkQual.push_back(0.70);
  uncertaintiesRel166EPSRecoTrkQual.push_back(0.70);
  uncertaintiesRel166EPSRecoTrkQual.push_back(0.70);
  uncertaintiesRel166EPSRecoTrkQual.push_back(0.66);
  uncertaintiesRel166EPSRecoTrkQual.push_back(0.66);
  uncertaintiesRel166EPSRecoTrkQual.push_back(0.66);
  uncertaintiesRel166EPSRecoTrkQual.push_back(0.66);
  uncertaintiesRel166EPSRecoTrkQual.push_back(0.66);
  uncertaintiesRel166EPSRecoTrkQual.push_back(0.66);
  uncertaintiesRel166EPSRecoTrkQual.push_back(0.70);
  uncertaintiesRel166EPSRecoTrkQual.push_back(0.70);
  uncertaintiesRel166EPSRecoTrkQual.push_back(0.70);
  uncertaintiesRel166EPSRecoTrkQual.push_back(0.70);
  uncertaintiesRel166EPSRecoTrkQual.push_back(0.70);
  uncertaintiesRel166EPSRecoTrkQual.push_back(0.70);
  uncertaintiesRel166EPSRecoTrkQual.push_back(1.84);

  // 2011 data with rel. 17 and MC11a ("CERN Council SF")
  // for technical reasons the values are first stored in float[],
  // then converted to vector<float>
  // Raw Rel17CC Reco+TQ SF
const float Sf_RecoTrkQ_Eta[]={ 102.01, 100.67, 100.97, 100.17, 99.40, 99.16, 99.25, 100.13, 100.73, 100.57, 102.30};
const float Sf_RecoTrkQ_Eta_err[]={ 0.70, 0.57, 0.70, 0.57, 1.11, 1.16, 0.99, 0.55, 0.90, 0.60, 0.71};
  // Raw Rel17CC Identification SF
const float sfLoosePP_Combined_eta[] = {0.978162, 0.989691, 0.9892, 1.00281, 0.993113, 0.994409, 0.995224, 1.00113, 0.9927, 0.990337, 0.98053};
const float errsfLoosePP_Combined_eta[] = {0.0184629, 0.015968, 0.00871837, 0.00385742, 0.00430604, 0.00414063, 0.00707358, 0.003712, 0.00843564, 0.0164764, 0.0178917};
const float sfLoosePP_Jpsi_eta[] = {0.928469, 0.876753, 0.947689, 0.940677, 0.933882, 0.932504, 0.943054, 0.924861, 1.07193, 0.909942, 0.94223};
const float errsfLoosePP_Jpsi_eta[] = {0.0442547, 0.0651155, 0.100367, 0.0459643, 0.0318983, 0.0337912, 0.0316421, 0.0362685, 0.0843151, 0.0566668, 0.0470655};
const float sfLoosePP_Combined_pt[] = {0., 1.04564, 1.02127, 0.950536, 0.956266, 0.985196, 1.00014, 1.00734, 1.00668, 1.00266};
const float errsfLoosePP_Combined_pt[] = {1., 0.0577688, 0.0532959, 0.0192058, 0.0159554, 0.0120122, 0.00643931, 0.00608316, 0.00608894, 0.00670763};
const float sfMediumPP_Combined_eta[] = {0.956077, 0.984517, 0.9933, 0.998451, 0.998374, 1.01566, 0.999115, 0.995048, 0.9972, 0.98697, 0.957895};
const float errsfMediumPP_Combined_eta[] = {0.013147, 0.0124841, 0.00889719, 0.00400233, 0.00446367, 0.00438371, 0.00441865, 0.00390813, 0.0090824, 0.0131541, 0.0154712};
const float sfMediumPP_Jpsi_eta[] = {0.913436, 0.892599, 0.981171, 0.918171, 0.939638, 0.935174, 0.934618, 0.907705, 1.09734, 0.874291, 0.903363};
const float errsfMediumPP_Jpsi_eta[] = {0.0451658, 0.0664901, 0.10942, 0.0456451, 0.0314451, 0.0334607, 0.0309696, 0.0362455, 0.0959015, 0.0564854, 0.0509632};
const float sfMediumPP_Combined_pt[] = {0., 1.06787, 1.0114, 0.949246, 0.940358, 0.974558, 0.994974, 1.0084, 1.00916, 1.0066};
const float errsfMediumPP_Combined_pt[] = {1., 0.0569981, 0.0482483, 0.0216574, 0.0173227, 0.0114571, 0.00633696, 0.00606375, 0.00609331, 0.00677809};
const float sfTightPP_Combined_eta[] = {0.970385, 1.00039, 1.0294, 1.02121, 1.00159, 1.01284, 1.00105, 1.01674, 1.0349, 1.00659, 0.971479};
const float errsfTightPP_Combined_eta[] = {0.0144101, 0.0116894, 0.00947048, 0.00424625, 0.00453523, 0.00451146, 0.00448671, 0.00412469, 0.00987978, 0.0116082, 0.0147539};
const float sfTightPP_Jpsi_eta[] = {0.961754, 0.913472, 1.00017, 0.920565, 0.940924, 0.930151, 0.934168, 0.898207, 1.19533, 0.887737, 0.949335};
const float errsfTightPP_Jpsi_eta[] = {0.0504488, 0.0706803, 0.117501, 0.0490665, 0.0352094, 0.0382616, 0.035019, 0.0403119, 0.109184, 0.0611907, 0.055913};
const float sfTightPP_Combined_pt[] = {0., 1.067, 1.0142, 0.953088, 0.94455, 0.974825, 0.995567, 1.00683, 1.00781, 1.00327};
const float errsfTightPP_Combined_pt[] = {1., 0.0635091, 0.0501458, 0.0228872, 0.0181984, 0.0118053, 0.00635714, 0.00609709, 0.00613041, 0.00679589};
  // Raw Rel17CC Trigger SF and eff
//////////////////////////////////////
/////// trigger e20_medium
//////////////////////////////////////

///// MC Efficiencies  vs Et
const float mcEff_e20_loo1_Et[6]={0.864088, 0.89944, 0.939482, 0.97356, 0.988114, 1.0045};
const float mcEff_e20_med1_Et[6]={0.932642, 0.959893, 0.98097, 0.990982, 0.995659, 1.00106};
const float mcEff_e20_tig1_Et[6]={0.940908, 0.965677, 0.984083, 0.992407, 0.996765, 1.00114};
//////  SF vs Et
const float SF_e20_med1_Et[6]={1.00245, 0.999368, 0.998914, 0.999601, 1.00048, 0.999809};
const float  SF_e20_med1_Et_toterror[6]={0.00597661,0.00298427,0.00154714,0.00105366,0.000587446,0.000577095};
const float SF_e20_tig1_Et[6]={1.0025, 0.995979, 0.997492, 0.999587, 1.0005, 1.00004}; 
const float  SF_e20_tig1_Et_toterror[6]={0.00570995,0.00346066,0.00152597,0.000993986,0.000568664,0.000466317};
//// MC Efficiencies vs eta
const float  mcEff_e20_loo1_eta[20]={0.83473,0.949204,0.944577,0.944431,0.828458,0.964727,0.970421,0.965379,0.955024,0.950054,0.940576,0.955574,0.966962,0.971468,0.963756,0.840913,0.95043,0.944207,0.951791,0.840843};
const float  mcEff_e20_med1_eta[20]={0.872355,0.969229,0.977964,0.973087,0.849374,0.985378,0.986858,0.988503,
0.979529,0.980543,0.974007,0.980666,0.98927,0.988601,0.98482,0.860735,0.978141,0.977674,0.970493,0.875797};
const float  mcEff_e20_tig1_eta[20]={0.886963,0.975401,0.983324,0.979107,0.853658,0.988534,0.990043,
0.991176,0.981667,0.982593,0.975875,0.982813,0.992012,0.99155,0.987791,0.865031,0.983154,0.982475,
0.975659,0.888129};
//// SF vs eta
const float  SF_e20_med1_eta[20]={1.01132,0.988154,0.98865,0.987197,1.03248,1.00244,0.994201,0.981812,1.00942,
0.923586,0.97601,1.00496,1.00136,0.995827,1.00157,1.02941,0.988385,0.983446,0.99408,1.01889};
const float SF_e20_med1_eta_toterror[20]={0.0138381, 0.010173, 0.0101778, 0.0105304, 0.0112517, 0.0100553, 
0.0100303, 0.0100703, 0.0100135, 0.0108708, 0.0105664, 0.0100226, 0.0100271, 0.0100309, 
0.0100894, 0.0114349, 0.0101388, 0.010223, 0.010139, 0.0129749};
const float  SF_e20_tig1_eta[20]={1.00768,0.98708,0.988363,0.986254,1.03095,1.00141,0.993596,0.980864,
1.00878,0.926747,0.975567,1.00439,0.999926,0.995449,1.00165,1.02746,0.989032,0.984948,0.994878,1.01632};
const float SF_e20_tig1_eta_toterror[20]={0.0133341, 0.0102052, 0.0101942, 0.0104491, 0.0114524, 0.0100434, 
0.0100267, 0.010074, 0.0100116, 0.0109426, 0.0105505, 0.010022, 0.0100252, 0.0100245, 0.0100841, 
0.0115263, 0.0101251, 0.0101966, 0.0101346, 0.0131077};
 /////////////////////////////////////////
////////  Trigger e22medium
/////////////////////////////////////////
///// MC efficiencies vs Et

float mcEff_e22_loo1_Et[6]={0., 0.877805, 0.933197, 0.973957, 0.990786, 1.00939}; 
float mcEff_e22_med1_Et[6]={0., 0.938168, 0.97598, 0.990546, 0.996888, 1.00369}; 
float mcEff_e22_tig1_Et[6]={0., 0.945008, 0.978626, 0.991608, 0.997479, 1.00331};
///   SF vs Et
const float SF_e22_med1_Et[6]={0., 1.00106, 0.997813, 1.00152, 1.00105, 0.999557};
const float  SF_e22_med1_Et_toterror[6]={1.,0.00788436,0.00348746,0.00196079,0.00128428,0.000730529};
const float SF_e22_tig1_Et[6]={0., 0.997016, 0.996317, 1.00213, 1.00131, 0.999715};
const float  SF_e22_tig1_Et_toterror[6]={1.,0.00795901,0.00301526,0.00186497,0.00135485,0.000586026};
///  MC efficiencies vs eta
const float  mcEff_e22_loo1_eta[20]={0.80987,0.935756,0.930274,0.933041,0.774026,0.955098,0.962545,0.958426,0.946747,0.940417,0.932461,0.946313,0.957602,0.961308,0.951713,0.796754,0.937367,0.935115,0.938189,0.820834};
const float  mcEff_e22_med1_eta[20]={0.850781,0.957769,0.965943,0.962989,0.796618,0.976691,0.98031,0.981781,0.9729,0.973739,0.966018,0.972751,0.981814,0.98023,0.973673,0.818503,0.967127,0.968771,0.959493,0.855468};
const float  mcEff_e22_tig1_eta[20]={0.866554,0.963796,0.97137,0.968614,0.800967,0.98014,0.983543,
0.98483,0.975155,0.975365,0.967583,0.974961,0.984649,0.983594,0.977511,0.821548,0.972552,
0.973661,0.965113,0.867067};
/// SF vs eta
const float  SF_e22_med1_eta[20]={1.0429,0.993361,0.990606,0.983569,1.07278,1.00356,0.99341,0.983135,
1.00858,0.922439,0.975137,1.00435,1.00485,0.998841,1.00251,1.05195,0.988802,0.974716,0.998945,1.03681};
const float SF_e22_med1_eta_toterror[20]={0.0170972, 0.0104995, 0.010535, 0.0113039, 0.0164707, 0.0101648, 
0.0101347, 0.0102433, 0.0100746, 0.01125, 0.0113536, 0.0100524, 0.010093, 0.0100712, 0.0102185, 
0.0129822, 0.0106089, 0.0108853, 0.0103578, 0.0177669};
const float  SF_e22_tig1_eta[20]={1.04354,0.9923,0.991662,0.983054,1.07381,1.00123,0.993014,0.982268,
1.00798,0.923537,0.977255,1.00411,1.00372,0.997861,1.00232,1.05236,0.988432,0.977005,0.997971,1.03317};
const float SF_e22_tig1_eta_toterror[20]={0.0167165, 0.0104359, 0.0106771, 0.0114704, 0.0167785, 0.0101834, 
0.0101823, 0.0102809, 0.0100571, 0.0113901, 0.011439, 0.0100538, 0.0100842, 0.0100766, 0.0101922, 
0.0131861, 0.0105969, 0.010921, 0.0103099, 0.0168021};
 
//////////////////////////////////////////////
///////  trigger e22vh medium1
////////////////////////////////////////////
//////////  MC efficiencies vs Et

const float mcEff_e22vh_loo1_Et[6]={0., 0.867613, 0.925484, 0.971542, 0.996169, 1.02254};
const float mcEff_e22vh_med1_Et[6]={0., 0.935306, 0.976425, 0.989257, 0.998406, 1.00712};
const float mcEff_e22vh_tig1_Et[6]={0., 0.946316, 0.984708, 0.993602, 1.00022, 1.00552};
///  SF vs Et
const float SF_e22vh_med1_Et[6]={0., 0.976255, 0.990213, 1.00065, 0.999608, 1.00088};
const float  SF_e22vh_med1_Et_toterror[6]={1.,0.00839289,0.00617629,0.00476838,0.00253987,0.00111677};
const float SF_e22vh_tig1_Et[6]={0., 0.971424, 0.986322, 0.998, 0.999025, 1.00115};
const float  SF_e22vh_tig1_Et_toterror[6]={1.,0.00840815,0.00611464,0.00418324,0.00233599,0.00100704};

/// MC efficiencies vs eta
const float  mcEff_e22vh_loo1_eta[20]={0.70588,0.850925,0.885496,0.88813,0.708504,0.898123,0.918406,0.916392,0.898269,0.815695,0.81267,0.897603,0.920762,0.919525,0.902682,0.726406,0.872302,0.884492,0.855155,0.72748};

const float  mcEff_e22vh_med1_eta[20]={0.806431,0.934885,0.950239,0.936858,0.783633,0.948002,0.9631,0.960062,
0.94823,0.909058,0.905434,0.948098,0.967413,0.963304,0.946392,0.793201,0.933363,0.945796,0.94782,0.828012};
const float  mcEff_e22vh_tig1_eta[20]={0.840512,0.949399,0.959665,0.95542,0.801649,0.969443,0.972239,
0.970461,0.959291,0.956205,0.956761,0.960181,0.977778,0.973809,0.965969,0.804513,0.953652,0.956252,
0.957446,0.847437};
// SF vs eta
const float  SF_e22vh_med1_eta[20]={0.984147,0.980365,0.970567,0.984624,0.97203,1.01202,0.999753,0.991051,
1.02403,0.990278,1.02291,1.01998,1.00556,1.00275,1.00858,1.02538,0.993383,0.965577,0.973939,0.953943};
const float SF_e22vh_med1_eta_toterror[20]={0.0305649, 0.0112576, 0.0118168, 0.0127388, 0.0190914, 0.0112009, 
0.0103002, 0.0105304, 0.0102212, 0.0128408, 0.0125235, 0.0103448, 0.0104107, 0.010408, 0.0108098, 
0.016527, 0.0125478, 0.0111028, 0.0107405, 0.0223372};
const float  SF_e22vh_tig1_eta[20]={0.964279,0.977745,0.975187,0.978157,0.961275,0.999952,0.995353,0.984084,
1.01769,0.956689,0.985402,1.01267,0.998659,0.99684,0.997916,1.0241,0.985229,0.970021,0.976287,0.947805};
const float SF_e22vh_tig1_eta_toterror[20]={0.033432, 0.0204931, 0.0208272, 0.0212713, 0.026605, 0.0203521, 
0.0201282, 0.020186, 0.0200903, 0.0213355, 0.0208187, 0.020117, 0.0201333, 0.0201497, 0.0203914, 
0.0245803, 0.0209498, 0.0205718, 0.0205268, 0.0272371};


 copyToVector(Sf_RecoTrkQ_Eta, 11, efficienciesRel17CCRecoTrkQual, 1.);
 copyToVector(Sf_RecoTrkQ_Eta_err, 11, uncertaintiesRel17CCRecoTrkQual, 1.);
 
 // Identification eta for probes between 15 and 50 GeV
 copyToVector(sfLoosePP_Combined_eta, 11, efficienciesRel17CCLoosePP1550);
 copyToVector(errsfLoosePP_Combined_eta, 11, uncertaintiesRel17CCLoosePP1550);
 copyToVector(sfMediumPP_Combined_eta, 11, efficienciesRel17CCMediumPP1550);
 copyToVector(errsfMediumPP_Combined_eta, 11, uncertaintiesRel17CCMediumPP1550);
 copyToVector(sfTightPP_Combined_eta, 11, efficienciesRel17CCTightPP1550);
 copyToVector(errsfTightPP_Combined_eta, 11, uncertaintiesRel17CCTightPP1550);
 //Identification eta for low ET probes
 copyToVector(sfLoosePP_Jpsi_eta, 11, efficienciesRel17CCLoosePP415);
 copyToVector(errsfLoosePP_Jpsi_eta, 11, uncertaintiesRel17CCLoosePP415);
 copyToVector(sfMediumPP_Jpsi_eta, 11, efficienciesRel17CCMediumPP415);
 copyToVector(errsfMediumPP_Jpsi_eta, 11, uncertaintiesRel17CCMediumPP415);
 copyToVector(sfTightPP_Jpsi_eta, 11, efficienciesRel17CCTightPP415);
 copyToVector(errsfTightPP_Jpsi_eta, 11, uncertaintiesRel17CCTightPP415);
 // ET correction
 copyToVector(sfLoosePP_Combined_pt, 10, ETCorrectionsRel17CCLoosePP);
 copyToVector(errsfLoosePP_Combined_pt, 10, uncertaintiesETCorrectionsRel17CCLoosePP);
 copyToVector(sfMediumPP_Combined_pt, 10, ETCorrectionsRel17CCMediumPP);
 copyToVector(errsfMediumPP_Combined_pt, 10, uncertaintiesETCorrectionsRel17CCMediumPP);
 copyToVector(sfTightPP_Combined_pt, 10, ETCorrectionsRel17CCTightPP);
 copyToVector(errsfTightPP_Combined_pt, 10, uncertaintiesETCorrectionsRel17CCTightPP);
 
 // Trigger efficiencies
 // e20_medium B-J
  copyToVector(SF_e20_med1_eta, 20, efficienciesRel17CCe20_mediumMediumPP);
  copyToVector(SF_e20_med1_eta_toterror, 20, uncertaintiesRel17CCe20_mediumMediumPP);
  copyToVector(SF_e20_med1_Et, 6, efficienciesRel17CCe20_mediumMediumPPET);
  copyToVector(SF_e20_med1_Et_toterror, 6, uncertaintiesRel17CCe20_mediumMediumPPET);

  copyToVector(mcEff_e20_med1_eta, 20, MCefficienciesRel17CCe20_mediumMediumPP);
  copyToVector(mcEff_e20_med1_Et, 6, MCefficienciesRel17CCe20_mediumMediumPPET);

  copyToVector(SF_e20_tig1_eta, 20, efficienciesRel17CCe20_mediumTightPP);
  copyToVector(SF_e20_tig1_eta_toterror, 20, uncertaintiesRel17CCe20_mediumTightPP);
  copyToVector(SF_e20_tig1_Et, 6, efficienciesRel17CCe20_mediumTightPPET);
  copyToVector(SF_e20_tig1_Et_toterror, 6, uncertaintiesRel17CCe20_mediumTightPPET);

  copyToVector(mcEff_e20_tig1_eta, 20, MCefficienciesRel17CCe20_mediumTightPP);
  copyToVector(mcEff_e20_tig1_Et, 6, MCefficienciesRel17CCe20_mediumTightPPET);

  copyToVector(mcEff_e20_loo1_eta, 20, MCefficienciesRel17CCe20_mediumLoosePP);
  copyToVector(mcEff_e20_loo1_Et, 6, MCefficienciesRel17CCe20_mediumLoosePPET);


  // e22_medium K
  copyToVector(SF_e22_med1_eta, 20, efficienciesRel17CCe22_mediumMediumPP);
  copyToVector(SF_e22_med1_eta_toterror, 20, uncertaintiesRel17CCe22_mediumMediumPP);
  copyToVector(SF_e22_med1_Et, 6, efficienciesRel17CCe22_mediumMediumPPET);
  copyToVector(SF_e22_med1_Et_toterror, 6, uncertaintiesRel17CCe22_mediumMediumPPET);

  copyToVector(mcEff_e22_med1_eta, 20, MCefficienciesRel17CCe22_mediumMediumPP);
  copyToVector(mcEff_e22_med1_Et, 6, MCefficienciesRel17CCe22_mediumMediumPPET);

  copyToVector(SF_e22_tig1_eta, 20, efficienciesRel17CCe22_mediumTightPP);
  copyToVector(SF_e22_tig1_eta_toterror, 20, uncertaintiesRel17CCe22_mediumTightPP);
  copyToVector(SF_e22_tig1_Et, 6, efficienciesRel17CCe22_mediumTightPPET);
  copyToVector(SF_e22_tig1_Et_toterror, 6, uncertaintiesRel17CCe22_mediumTightPPET);

  copyToVector(mcEff_e22_tig1_eta, 20, MCefficienciesRel17CCe22_mediumTightPP);
  copyToVector(mcEff_e22_tig1_Et, 6, MCefficienciesRel17CCe22_mediumTightPPET);

  copyToVector(mcEff_e22_loo1_eta, 20, MCefficienciesRel17CCe22_mediumLoosePP);
  copyToVector(mcEff_e22_loo1_Et, 6, MCefficienciesRel17CCe22_mediumLoosePPET);


  // e22vh_medium1 L-M
  copyToVector(SF_e22vh_med1_eta, 20, efficienciesRel17CCe22vh_medium1MediumPP);
  copyToVector(SF_e22vh_med1_eta_toterror, 20, uncertaintiesRel17CCe22vh_medium1MediumPP);
  copyToVector(SF_e22vh_med1_Et, 6, efficienciesRel17CCe22vh_medium1MediumPPET);
  copyToVector(SF_e22vh_med1_Et_toterror, 6, uncertaintiesRel17CCe22vh_medium1MediumPPET);

  copyToVector(mcEff_e22vh_med1_eta, 20, MCefficienciesRel17CCe22vh_medium1MediumPP);
  copyToVector(mcEff_e22vh_med1_Et, 6, MCefficienciesRel17CCe22vh_medium1MediumPPET);

  copyToVector(SF_e22vh_tig1_eta, 20, efficienciesRel17CCe22vh_medium1TightPP);
  copyToVector(SF_e22vh_tig1_eta_toterror, 20, uncertaintiesRel17CCe22vh_medium1TightPP);
  copyToVector(SF_e22vh_tig1_Et, 6, efficienciesRel17CCe22vh_medium1TightPPET);
  copyToVector(SF_e22vh_tig1_Et_toterror, 6, uncertaintiesRel17CCe22vh_medium1TightPPET);

  copyToVector(mcEff_e22vh_tig1_eta, 20, MCefficienciesRel17CCe22vh_medium1TightPP);
  copyToVector(mcEff_e22vh_tig1_Et, 6, MCefficienciesRel17CCe22vh_medium1TightPPET);


  copyToVector(mcEff_e22vh_loo1_eta, 20, MCefficienciesRel17CCe22vh_medium1LoosePP);
  copyToVector(mcEff_e22vh_loo1_Et, 6, MCefficienciesRel17CCe22vh_medium1LoosePPET);


  // 2011 data with rel. 17 and MC11a/b/c G4 FullSim ("Moriond SF")
const float sfLoosePP_Combined_Moriond_eta[] = {0.983727, 0.992645, 0.9892, 1.00425, 0.994238, 0.99583, 0.995955, 1.00307, 0.9907, 0.994061, 0.984558};
const float errsfLoosePP_Combined_Moriond_eta[] = {0.0190335, 0.0158532, 0.00838153, 0.00394904, 0.00432761, 0.00425582, 0.00429913, 0.00357115, 0.0079806, 0.0164504, 0.0178845};
const float sfLoosePP_Jpsi_Moriond_eta[] = {0.928469, 0.876753, 0.947689, 0.940677, 0.933882, 0.932504, 0.943054, 0.924861, 1.07193, 0.909942, 0.94223};
const float errsfLoosePP_Jpsi_Moriond_eta[] = {0.0442547, 0.0651155, 0.100367, 0.0459643, 0.0318983, 0.0337912, 0.0316421, 0.0362685, 0.0843151, 0.0566668, 0.0470655};

const float sfLoosePP_Combined_Moriond_pt[] = {0., 1.04564, 1.02127, 0.952484, 0.958019, 0.986368, 1.00122, 1.00889, 1.00725, 1.00164};
const float errsfLoosePP_Combined_Moriond_pt[] = {1., 0.0584143, 0.0539949, 0.0220578, 0.0191925, 0.011236, 0.00582933, 0.00661811, 0.00532031, 0.00642074};


const float sfMedium_Combined_Moriond_eta[] = {0.980389, 0.984739, 0.987, 0.995007, 0.992199, 0.999625, 0.992335, 0.991465, 0.9896, 0.990364, 0.982351};
const float errsfMedium_Combined_Moriond_eta[] = {0.0187827, 0.01235, 0.00807527, 0.00418403, 0.0044624, 0.00429145, 0.00446588, 0.00383729, 0.00793473, 0.0138236, 0.0179662};
const float sfMedium_Jpsi_Moriond_eta[] = {0.942597, 0.974524, 1.08641, 1.01779, 0.975308, 0.97664, 0.982064, 0.971485, 1.07755, 0.981647, 0.910087};
const float errsfMedium_Jpsi_Moriond_eta[] = {0.042, 0.085, 0.091, 0.049, 0.028, 0.03, 0.028, 0.049, 0.095, 0.06, 0.049};
const float sfMedium_Combined_Moriond_pt[] = {0., 1.02283, 0.980082, 0.954413, 0.950976, 0.982899, 0.998409, 1.00998, 1.00825, 1.00394};
const float errsfMedium_Combined_Moriond_pt[] = {1., 0.0562668, 0.0482163, 0.0225589, 0.0206991, 0.00776764, 0.00602853, 0.00685129, 0.00541447, 0.00645837};


const float sfMediumPP_Combined_Moriond_eta[] = {0.967144, 0.990423, 0.9926, 0.998398, 1.00044, 1.01609, 1.00082, 0.995716, 0.9922, 0.994387, 0.967035};
const float errsfMediumPP_Combined_Moriond_eta[] = {0.0152302, 0.0126984, 0.00866025, 0.00419149, 0.00447153, 0.00445324, 0.00447221, 0.00391371, 0.00843564, 0.0148758, 0.0164505};
const float sfMediumPP_Jpsi_Moriond_eta[] = {0.913436, 0.892599, 0.981171, 0.918171, 0.939638, 0.935174, 0.934618, 0.907705, 1.09734, 0.874291, 0.903363};
const float errsfMediumPP_Jpsi_Moriond_eta[] = {0.0451658, 0.0664901, 0.10942, 0.0456451, 0.0314451, 0.0334607, 0.0309696, 0.0362455, 0.0959015, 0.0564854, 0.0509632};
const float sfMediumPP_Combined_Moriond_pt[] = {0., 1.06787, 1.0114, 0.952377, 0.942511, 0.977914, 0.995868, 1.00973, 1.01033, 1.0053};
const float errsfMediumPP_Combined_Moriond_pt[] = {1., 0.0576523, 0.0490194, 0.0245875, 0.0217735, 0.00821047, 0.00626121, 0.00701316, 0.00551153, 0.00653204};


const float sfTightPP_Combined_Moriond_eta[] = {0.987679, 1.00704, 1.027, 1.02319, 1.00345, 1.01298, 1.00215, 1.0204, 1.0276, 1.01574, 0.985344};
const float errsfTightPP_Combined_Moriond_eta[] = {0.00770372, 0.0116938, 0.00920923, 0.00471006, 0.00464143, 0.0051928, 0.0045983, 0.00446568, 0.0090824, 0.0140841, 0.0168724};
const float sfTightPP_Jpsi_Moriond_eta[] = {0.961754, 0.913472, 1.00017, 0.920565, 0.940924, 0.930151, 0.934168, 0.898207, 1.19533, 0.887737, 0.949335};
const float errsfTightPP_Jpsi_Moriond_eta[] = {0.0504488, 0.0706803, 0.117501, 0.0490665, 0.0352094, 0.0382616, 0.035019, 0.0403119, 0.109184, 0.0611907, 0.055913};
const float sfTightPP_Combined_Moriond_pt[] = {0., 1.067, 1.0142, 0.957576, 0.949916, 0.979087, 0.996125, 1.00763, 1.00897, 1.0016};
const float errsfTightPP_Combined_Moriond_pt[] = {1., 0.0640969, 0.0508882, 0.0259462, 0.0232052, 0.0085569, 0.00700376, 0.00719543, 0.00578251, 0.00667381};



  // reco+TQ are by choice identical to the "Cern council" results!
  copyToVector(Sf_RecoTrkQ_Eta, 11, efficienciesRel17MoriondRecoTrkQual, 1.);
  copyToVector(Sf_RecoTrkQ_Eta_err, 11, uncertaintiesRel17MoriondRecoTrkQual, 1.);
 
  // Identification eta for probes between 15 and 50 GeV
  copyToVector(sfLoosePP_Combined_Moriond_eta, 11, efficienciesRel17MoriondLoosePP1550);
  copyToVector(errsfLoosePP_Combined_Moriond_eta, 11, uncertaintiesRel17MoriondLoosePP1550);
  copyToVector(sfMedium_Combined_Moriond_eta, 11, efficienciesRel17MoriondMedium1550);
  copyToVector(errsfMedium_Combined_Moriond_eta, 11, uncertaintiesRel17MoriondMedium1550);
  copyToVector(sfMediumPP_Combined_Moriond_eta, 11, efficienciesRel17MoriondMediumPP1550);
  copyToVector(errsfMediumPP_Combined_Moriond_eta, 11, uncertaintiesRel17MoriondMediumPP1550);
  copyToVector(sfTightPP_Combined_Moriond_eta, 11, efficienciesRel17MoriondTightPP1550);
  copyToVector(errsfTightPP_Combined_Moriond_eta, 11, uncertaintiesRel17MoriondTightPP1550);
  //Identification eta for low ET probes
  copyToVector(sfLoosePP_Jpsi_Moriond_eta, 11, efficienciesRel17MoriondLoosePP415);
  copyToVector(errsfLoosePP_Jpsi_Moriond_eta, 11, uncertaintiesRel17MoriondLoosePP415);
  copyToVector(sfMedium_Jpsi_Moriond_eta, 11, efficienciesRel17MoriondMedium415);
  copyToVector(errsfMedium_Jpsi_Moriond_eta, 11, uncertaintiesRel17MoriondMedium415);
  copyToVector(sfMediumPP_Jpsi_Moriond_eta, 11, efficienciesRel17MoriondMediumPP415);
  copyToVector(errsfMediumPP_Jpsi_Moriond_eta, 11, uncertaintiesRel17MoriondMediumPP415);
  copyToVector(sfTightPP_Jpsi_Moriond_eta, 11, efficienciesRel17MoriondTightPP415);
  copyToVector(errsfTightPP_Jpsi_Moriond_eta, 11, uncertaintiesRel17MoriondTightPP415);
  // ET correction
  copyToVector(sfLoosePP_Combined_Moriond_pt, 10, ETCorrectionsRel17MoriondLoosePP);
  copyToVector(errsfLoosePP_Combined_Moriond_pt, 10, uncertaintiesETCorrectionsRel17MoriondLoosePP);
  copyToVector(sfMedium_Combined_Moriond_pt, 10, ETCorrectionsRel17MoriondMedium);
  copyToVector(errsfMedium_Combined_Moriond_pt, 10, uncertaintiesETCorrectionsRel17MoriondMedium);
  copyToVector(sfMediumPP_Combined_Moriond_pt, 10, ETCorrectionsRel17MoriondMediumPP);
  copyToVector(errsfMediumPP_Combined_Moriond_pt, 10, uncertaintiesETCorrectionsRel17MoriondMediumPP);
  copyToVector(sfTightPP_Combined_Moriond_pt, 10, ETCorrectionsRel17MoriondTightPP);
  copyToVector(errsfTightPP_Combined_Moriond_pt, 10, uncertaintiesETCorrectionsRel17MoriondTightPP);
 
 // Trigger efficiencies
 // e20_medium B-J  


const float  mcEff_e20_loo1c_eta[20]={0.848389,0.956334,0.950973,0.953063,0.832028,0.970957,0.975289,
0.971215,0.961237,0.960304,0.934168, 0.946466,0.955915,0.959373,0.954392, 0.848096,0.956117,
0.950492,0.957751,0.854038};
 const float mcEff_e20_med1c_eta[]={0.885794, 0.977261, 0.983728, 0.980814, 0.852281, 0.990963, 
0.991499, 0.991901, 0.984694, 0.987225, 0.96583, 0.970429, 0.977551, 0.975742, 0.973367, 
0.869728, 0.984179, 0.985036, 0.978288, 0.887523}; 
const float mcEff_e20_tig1c_eta[]={0.902422, 0.98492, 0.98942, 0.985926, 0.855551, 0.993568, 
0.993645, 0.994026, 0.986244, 0.989781, 0.968321, 0.972046, 0.979683, 0.978163, 0.975803, 
0.871911, 0.988501, 0.990043, 0.985543, 0.906235}; 

const float mcEff_e20_loo1c_Et[]={0.876544, 0.911258, 0.946972, 0.980841, 0.994258, 1.00986};
const float mcEff_e20_med1c_Et[]={0.943346, 0.966699, 0.984657, 0.994935, 0.999148, 1.00367};
const float mcEff_e20_tig1c_Et[]={0.949817, 0.972587, 0.98651, 0.995306, 0.999683, 1.003};
//SF MC11c

const float  SF_e20_loo1c_eta[20]={0.998949,0.976708,0.985923,0.960299,1.02274,0.984517,0.983232,
0.971822,1.00301,0.896542,0.974195,1.01332,1.0075,1.00208,0.998327,1.02373,0.967299,0.985603,
0.982879,1.00387};
const float SF_e20_loo1c_eta_toterror[20]={0.0133927, 0.00183132, 0.00237557, 0.00727585, 0.00635603, 
0.00182113, 0.00122957, 0.00174555, 0.000928082, 0.00381891, 0.00305131, 0.00109265, 0.0015499, 
0.00131237, 0.0017381, 0.00527935, 0.00418972, 0.00252536, 0.00185791, 0.0125777};
 const float SF_e20_med1c_eta[]={0.996195, 0.979772, 0.982875, 0.978667, 1.02795, 0.996923, 0.989745, 
0.978374, 1.00409, 0.89795, 0.974241, 1.01556, 1.01324, 1.00898, 1.01327, 1.01829, 0.981891, 
0.97597, 0.985885, 1.00469}; 
const float SF_e20_med1c_eta_toterror[]={0.0126418, 0.00152712, 0.00169908, 0.00279707, 0.00496428, 
0.000840994, 0.000693205, 0.00104571, 0.00056198, 0.00333248, 0.00253498, 0.000735072, 
0.000894095, 0.000821252, 0.0011766, 0.004989, 0.00136793, 0.001719, 0.00147176, 0.0120504}; 
const float SF_e20_tig1c_eta[]={0.990602, 0.977016, 0.982264, 0.978669, 1.02712, 0.9964, 0.990204, 
0.97791, 1.0041, 0.920103, 0.983076, 1.01551, 1.01238, 1.0091, 1.01396, 1.01941, 0.983368, 
0.977353, 0.984219, 0.994481}; 
const float SF_e20_tig1c_eta_toterror[]={0.0126946, 0.0015388, 0.00158688, 0.00270277, 0.00521395, 
0.00081376, 0.000654352, 0.00103651, 0.000539949, 0.00334691, 0.0024402, 0.000736938, 
0.00087863, 0.00079522, 0.00112249, 0.00498023, 0.00130398, 0.00159166, 0.00135454, 0.0120652}; 
 
const float SF_e20_loo1c_Et[]={0.965482, 0.975569, 0.989, 0.994475, 0.998588, 1.00222};
const float SF_e20_loo1c_Et_toterror[]={0.0097343, 0.00707489, 0.00621119, 0.00541167, 0.00513511, 0.00503009};
const float SF_e20_med1c_Et[]={0.992814, 0.995266, 0.997939, 0.998636, 1.00009, 1.00052};
const float SF_e20_med1c_Et_toterror[]={0.00740121, 0.00586089, 0.00520539, 0.00506951, 0.00504291, 0.00501729};
const float SF_e20_tig1c_Et[]={0.994419, 0.99071, 0.997164, 0.998778, 0.999922, 1.00064};
const float SF_e20_tig1c_Et_toterror[]={0.00717398, 0.00590631, 0.00517393, 0.0050728, 0.00504031, 0.00501678};

  copyToVector(SF_e20_loo1c_eta, 20, efficienciesRel17Morionde20_mediumLoosePP);
  copyToVector(SF_e20_loo1c_eta_toterror, 20, uncertaintiesRel17Morionde20_mediumLoosePP);
  copyToVector(SF_e20_loo1c_Et, 6, efficienciesRel17Morionde20_mediumLoosePPET);
  copyToVector(SF_e20_loo1c_Et_toterror, 6, uncertaintiesRel17Morionde20_mediumLoosePPET);

  copyToVector(SF_e20_med1c_eta, 20, efficienciesRel17Morionde20_mediumMediumPP);
  copyToVector(SF_e20_med1c_eta_toterror, 20, uncertaintiesRel17Morionde20_mediumMediumPP);
  copyToVector(SF_e20_med1c_Et, 6, efficienciesRel17Morionde20_mediumMediumPPET);
  copyToVector(SF_e20_med1c_Et_toterror, 6, uncertaintiesRel17Morionde20_mediumMediumPPET);

  copyToVector(SF_e20_tig1c_eta, 20, efficienciesRel17Morionde20_mediumTightPP);
  copyToVector(SF_e20_tig1c_eta_toterror, 20, uncertaintiesRel17Morionde20_mediumTightPP);
  copyToVector(SF_e20_tig1c_Et, 6, efficienciesRel17Morionde20_mediumTightPPET);
  copyToVector(SF_e20_tig1c_Et_toterror, 6, uncertaintiesRel17Morionde20_mediumTightPPET);

  copyToVector(mcEff_e20_loo1c_eta, 20, MCefficienciesRel17Morionde20_mediumLoosePP);
  copyToVector(mcEff_e20_loo1c_Et, 6, MCefficienciesRel17Morionde20_mediumLoosePPET);
  copyToVector(mcEff_e20_med1c_eta, 20, MCefficienciesRel17Morionde20_mediumMediumPP);
  copyToVector(mcEff_e20_med1c_Et, 6, MCefficienciesRel17Morionde20_mediumMediumPPET);
  copyToVector(mcEff_e20_tig1c_eta, 20, MCefficienciesRel17Morionde20_mediumTightPP);
  copyToVector(mcEff_e20_tig1c_Et, 6, MCefficienciesRel17Morionde20_mediumTightPPET);

  //// e22_medium K 

const float  mcEff_e22_loo1c_eta[20]={0.840584,0.953721,0.950048,0.952885,0.795771,0.972006,0.974945,0.969896,0.96188,0.956744,0.901899,0.914529,0.925091,0.925385,0.922256,0.808596,0.957785,0.951094,0.956664,0.84567};
const float mcEff_e22_med1c_eta[20] = {0.88053, 0.97644, 0.98375, 0.97965, 0.81019, 0.99031, 0.99011, 0.99125, 0.98457, 0.98497, 0.93506, 0.94347, 0.95187, 0.94754, 0.94672, 0.82641, 0.98257, 0.98388, 0.97803, 0.87764}; 
const float mcEff_e22_tig1c_eta[20] = {0.90645, 0.98682, 0.98994, 0.98426, 0.81090, 0.99335, 0.99266, 0.99259, 0.98572, 0.98822, 0.93821, 0.94517, 0.95526, 0.95105, 0.95012, 0.83115, 0.98861, 0.98896, 0.98797, 0.90253}; 

const float mcEff_e22_loo1c_Et[]={0., 0.888972, 0.939452, 0.977535, 0.994082, 1.01171};
const float mcEff_e22_med1c_Et[]={0., 0.944215, 0.977993, 0.992536, 0.999043, 1.00482};
const float mcEff_e22_tig1c_Et[]={0., 0.951214, 0.980248, 0.993901, 0.999523, 1.00402};

//
 //SF 11c 
const float  SF_e22_loo1c_eta[20]={1.04505,0.982017,0.98524,0.959152,1.05681,0.980914,0.983889,0.972793,1.00162,0.900027,1.00613,1.04607,1.04169,1.03825,1.03126,1.06077,0.96713,0.980231,0.989389,1.02917};
const float SF_e22_loo1c_eta_toterror[20]={0.0175488, 0.00292899, 0.00391901, 0.00658872, 0.010585, 0.00239365, 0.00164762, 0.0024999, 0.00131486, 0.0050669, 0.011244, 0.0101584, 0.0103494, 0.0102053, 0.010486, 0.00810613, 
0.00424727, 0.00377396, 0.00260471, 0.0152136};
const  float SF_e22_med1c_eta[]={1.03024, 0.98367, 0.981344, 0.975884, 1.05909, 0.997067, 0.990773, 
0.979462, 1.00306, 0.900019, 1.00263, 1.04896, 1.04779, 1.04571, 1.04256, 1.05124, 0.981777, 
0.970867, 0.989822, 1.02413}; 
const float SF_e22_med1c_eta_toterror[]={0.0154226, 0.00239801, 0.00274037, 0.00393086, 0.00868051, 
0.00133035, 0.0011408, 0.00169364, 0.000833678, 0.00446543, 0.0108841, 0.0100862, 0.0101717, 0.0101252, 0.0102804, 0.00747541, 0.00219934, 0.0028696, 0.00209202, 0.0146176}; 
const float SF_e22_tig1c_eta[]={1.03125, 0.97921, 0.982814, 0.976566, 1.06166, 0.9957, 0.990672, 
0.979767, 1.00323, 0.919104, 1.01636, 1.04919, 1.0467, 1.04592, 1.04398, 1.04873, 0.981864, 
0.97313, 0.986599, 1.0129}; 
const float SF_e22_tig1c_eta_toterror[]={0.0154282, 0.00235617, 0.0026783, 0.00396651, 0.00881431, 
0.00133136, 0.00124223, 0.0016658, 0.000797657, 0.0043214, 0.0108864, 0.0100887, 0.0101736, 0.0101333, 
0.0102847, 0.00765196, 0.00218572, 0.00280942, 0.00204223, 0.0147474}; 
const float SF_e22_loo1c_Et[]={0., 0.976139, 0.986007, 0.997185, 0.998897, 1.00168};
const float SF_e22_loo1c_Et_toterror[]={1., 0.010067, 0.00635541, 0.00571717, 0.0051924, 0.00506772};
const float SF_e22_med1c_Et[]={0., 0.995079, 0.996567, 1.00054, 1.00046, 1.00007};
const float SF_e22_med1c_Et_toterror[]={1, 0.00803895, 0.00556503, 0.00525804, 0.00510948, 0.00505457};
const float SF_e22_tig1c_Et[]={0., 0.991279, 0.995014, 1.00048, 1.00033, 1.00026};
const float SF_e22_tig1c_Et_toterror[]={1, 0.00827327, 0.00547239, 0.00526172, 0.0051088, 0.00503921};


  copyToVector(SF_e22_loo1c_eta, 20, efficienciesRel17Morionde22_mediumLoosePP);
  copyToVector(SF_e22_loo1c_eta_toterror, 20, uncertaintiesRel17Morionde22_mediumLoosePP);
  copyToVector(SF_e22_loo1c_Et, 6, efficienciesRel17Morionde22_mediumLoosePPET);
  copyToVector(SF_e22_loo1c_Et_toterror, 6, uncertaintiesRel17Morionde22_mediumLoosePPET);

  copyToVector(SF_e22_med1c_eta, 20, efficienciesRel17Morionde22_mediumMediumPP);
  copyToVector(SF_e22_med1c_eta_toterror, 20, uncertaintiesRel17Morionde22_mediumMediumPP);
  copyToVector(SF_e22_med1c_Et, 6, efficienciesRel17Morionde22_mediumMediumPPET);
  copyToVector(SF_e22_med1c_Et_toterror, 6, uncertaintiesRel17Morionde22_mediumMediumPPET);

  copyToVector(SF_e22_tig1c_eta, 20, efficienciesRel17Morionde22_mediumTightPP);
  copyToVector(SF_e22_tig1c_eta_toterror, 20, uncertaintiesRel17Morionde22_mediumTightPP);
  copyToVector(SF_e22_tig1c_Et, 6, efficienciesRel17Morionde22_mediumTightPPET);
  copyToVector(SF_e22_tig1c_Et_toterror, 6, uncertaintiesRel17Morionde22_mediumTightPPET);

  copyToVector(mcEff_e22_loo1c_eta, 20, MCefficienciesRel17Morionde22_mediumLoosePP);
  copyToVector(mcEff_e22_loo1c_Et, 6, MCefficienciesRel17Morionde22_mediumLoosePPET);
  copyToVector(mcEff_e22_med1c_eta, 20, MCefficienciesRel17Morionde22_mediumMediumPP);
  copyToVector(mcEff_e22_med1c_Et, 6, MCefficienciesRel17Morionde22_mediumMediumPPET);
  copyToVector(mcEff_e22_tig1c_eta, 20, MCefficienciesRel17Morionde22_mediumTightPP);
  copyToVector(mcEff_e22_tig1c_Et, 6, MCefficienciesRel17Morionde22_mediumTightPPET);

  // e22vh_medium1 L-M
const float  mcEff_e22vh_loo1c_eta[20]={0.753385,0.878486,0.89769,0.906778,0.726772,0.932791,0.937339,0.92971,0.930485,0.915429,0.907636,0.930841,0.932583,0.938241,0.930442,0.742618,0.914729,0.899687,0.879789,0.757878};
const float  mcEff_e22vh_med1c_eta[20]={0.855469,0.957704,0.962118,0.957255,0.79774,0.975774,0.975337,0.971563,0.974653,0.973731,0.968879,0.976654,0.973704,0.977386,0.973054,0.811455,0.963224,0.96084,0.959001,0.858417};
const float  mcEff_e22vh_tig1c_eta[20]={0.873634,0.969314,0.971734,0.966338,0.803909,0.981871,0.980063,0.975153,0.977292,0.977283,0.972042,0.978912,0.976689,0.98102,0.977944,0.81777,0.97238,0.969662,0.969989,0.884153};

const float mcEff_e22vh_loo1c_Et[]={0., 0.841141, 0.916559, 0.969456, 0.989858, 1.01729};
const float mcEff_e22vh_med1c_Et[]={0., 0.917413, 0.970792, 0.991354, 0.997288, 1.00565};
const float mcEff_e22vh_tig1c_Et[]={0., 0.9261, 0.974482, 0.992761, 0.998153, 1.00453};

// SF 11c
const float  SF_e22vh_loo1c_eta[20]={0.927087,0.934726,0.974119,0.956884,0.975238,0.980472,0.987201,0.97768,1.00221,0.91543,0.950363,0.996395,0.998819,0.987623,0.979209,1.02748,0.956823,0.964382,0.940593,0.923664};
const float SF_e22vh_loo1c_eta_toterror[20]={0.0145067, 0.00322803, 0.00300779, 0.00775627, 0.00862159, 
0.00191749, 0.00135194, 0.00186679, 0.001231, 0.00377874, 0.00299133, 0.00114196, 0.00182424, 
0.0013885, 0.00201595, 0.00657098, 0.00553785, 0.00313311, 0.00284801, 0.014375};
 const float SF_e22vh_med1c_eta[]={0.94445, 0.96441, 0.966463, 0.972076, 0.966836, 0.98881, 0.992735, 
0.984184, 1.00167, 0.910663, 0.945655, 0.994987, 1.00315, 0.992454, 0.98608, 1.01339, 0.972269, 
0.957904, 0.971932, 0.934367}; 
const float SF_e22vh_med1c_eta_toterror[]={0.0124695, 0.00182701, 0.00207682, 0.00424349, 0.0058064, 
0.00118148, 0.000888236, 0.00123393, 0.000644093, 0.00317546, 0.00220527, 0.000653257, 0.00100326, 
0.000829406, 0.00128047, 0.00488073, 0.00246987, 0.00214208, 0.00168504, 0.012745}; 
const float SF_e22vh_tig1c_eta[]={0.943578, 0.965082, 0.971145, 0.975588, 0.971474, 0.994236, 0.994395, 
0.985146, 1.00519, 0.942796, 0.976236, 0.998936, 1.00446, 0.995353, 0.991931, 1.01868, 0.976645, 0.964693, 0.972793, 0.923387}; 
const float SF_e22vh_tig1c_eta_toterror[]={0.0124287, 0.00172295, 0.00196625, 0.00442023, 0.00585806, 
0.00107372, 0.000884212, 0.0012172, 0.00058651, 0.00276835, 0.00213339, 0.000617185, 0.000966887, 
0.000788727, 0.00119594, 0.00525708, 0.00246356, 0.00214231, 0.00163689, 0.0128776}; 

//
const float SF_e22vh_loo1c_Et[]={0., 0.961035, 0.977873, 0.988738, 0.997348, 1.00438};
const float SF_e22vh_loo1c_Et_toterror[]={1., 0.00925124, 0.00750312, 0.00589792, 0.00522709, 0.00505072};
const float SF_e22vh_med1c_Et[]={0., 0.991858, 0.993749, 0.996976, 0.99943, 1.00129};
const float SF_e22vh_med1c_Et_toterror[]={1., 0.00698902, 0.00587858, 0.00527041, 0.00506882, 0.00501655};
const float SF_e22vh_tig1c_Et[]={0., 0.990188, 0.994625, 0.997235, 0.999762, 1.00104};
const float SF_e22vh_tig1c_Et_toterror[]={1., 0.0070191, 0.00567937, 0.00522457, 0.00507731, 0.00501631};

  copyToVector(SF_e22vh_loo1c_eta, 20, efficienciesRel17Morionde22vh_medium1LoosePP);
  copyToVector(SF_e22vh_loo1c_eta_toterror, 20, uncertaintiesRel17Morionde22vh_medium1LoosePP);
  copyToVector(SF_e22vh_loo1c_Et, 6, efficienciesRel17Morionde22vh_medium1LoosePPET);
  copyToVector(SF_e22vh_loo1c_Et_toterror, 6, uncertaintiesRel17Morionde22vh_medium1LoosePPET);

  copyToVector(SF_e22vh_med1c_eta, 20, efficienciesRel17Morionde22vh_medium1MediumPP);
  copyToVector(SF_e22vh_med1c_eta_toterror, 20, uncertaintiesRel17Morionde22vh_medium1MediumPP);
  copyToVector(SF_e22vh_med1c_Et, 6, efficienciesRel17Morionde22vh_medium1MediumPPET);
  copyToVector(SF_e22vh_med1c_Et_toterror, 6, uncertaintiesRel17Morionde22vh_medium1MediumPPET);


  copyToVector(SF_e22vh_tig1c_eta, 20, efficienciesRel17Morionde22vh_medium1TightPP);
  copyToVector(SF_e22vh_tig1c_eta_toterror, 20, uncertaintiesRel17Morionde22vh_medium1TightPP);
  copyToVector(SF_e22vh_tig1c_Et, 6, efficienciesRel17Morionde22vh_medium1TightPPET);
  copyToVector(SF_e22vh_tig1c_Et_toterror, 6, uncertaintiesRel17Morionde22vh_medium1TightPPET);

  copyToVector(mcEff_e22vh_loo1c_eta, 20, MCefficienciesRel17Morionde22vh_medium1LoosePP);
  copyToVector(mcEff_e22vh_loo1c_Et, 6, MCefficienciesRel17Morionde22vh_medium1LoosePPET);
  copyToVector(mcEff_e22vh_med1c_eta, 20, MCefficienciesRel17Morionde22vh_medium1MediumPP);
  copyToVector(mcEff_e22vh_med1c_Et, 6, MCefficienciesRel17Morionde22vh_medium1MediumPPET);
  copyToVector(mcEff_e22vh_tig1c_eta, 20, MCefficienciesRel17Morionde22vh_medium1TightPP);
  copyToVector(mcEff_e22vh_tig1c_Et, 6, MCefficienciesRel17Morionde22vh_medium1TightPPET);



  efficienciesRel17MoriondForwardLoose.push_back(99.9);
  efficienciesRel17MoriondForwardLoose.push_back(100.6);
  efficienciesRel17MoriondForwardLoose.push_back(98.6);
  efficienciesRel17MoriondForwardLoose.push_back(101.3);
  efficienciesRel17MoriondForwardLoose.push_back(100.2);
  efficienciesRel17MoriondForwardLoose.push_back(100.6);
  efficienciesRel17MoriondForwardLoose.push_back(0.000);
  efficienciesRel17MoriondForwardLoose.push_back(101.3);
  efficienciesRel17MoriondForwardLoose.push_back(97.7);
  efficienciesRel17MoriondForwardLoose.push_back(85.6);
  uncertaintiesRel17MoriondForwardLoose.push_back(3.1);
  uncertaintiesRel17MoriondForwardLoose.push_back(3.0);
  uncertaintiesRel17MoriondForwardLoose.push_back(2.1);
  uncertaintiesRel17MoriondForwardLoose.push_back(2.8);
  uncertaintiesRel17MoriondForwardLoose.push_back(2.0);
  uncertaintiesRel17MoriondForwardLoose.push_back(1.8);
  uncertaintiesRel17MoriondForwardLoose.push_back(100.);
  uncertaintiesRel17MoriondForwardLoose.push_back(7.5);
  uncertaintiesRel17MoriondForwardLoose.push_back(4.5);
  uncertaintiesRel17MoriondForwardLoose.push_back(6.9);

  efficienciesRel17MoriondForwardTight.push_back(97.8);
  efficienciesRel17MoriondForwardTight.push_back(93.2);
  efficienciesRel17MoriondForwardTight.push_back(83.6);
  efficienciesRel17MoriondForwardTight.push_back(90.1);
  efficienciesRel17MoriondForwardTight.push_back(84.9);
  efficienciesRel17MoriondForwardTight.push_back(87.4);
  efficienciesRel17MoriondForwardTight.push_back(0.000);
  efficienciesRel17MoriondForwardTight.push_back(90.9);
  efficienciesRel17MoriondForwardTight.push_back(90.0);
  efficienciesRel17MoriondForwardTight.push_back(75.8);
  uncertaintiesRel17MoriondForwardTight.push_back(4.3);
  uncertaintiesRel17MoriondForwardTight.push_back(3.7);
  uncertaintiesRel17MoriondForwardTight.push_back(3.1);
  uncertaintiesRel17MoriondForwardTight.push_back(2.6);
  uncertaintiesRel17MoriondForwardTight.push_back(2.5);
  uncertaintiesRel17MoriondForwardTight.push_back(2.1);
  uncertaintiesRel17MoriondForwardTight.push_back(100.);
  uncertaintiesRel17MoriondForwardTight.push_back(5.2);
  uncertaintiesRel17MoriondForwardTight.push_back(3.7);
  uncertaintiesRel17MoriondForwardTight.push_back(5.2);

  // Frozen Shower corrections in FCAL
  efficienciesRel17MoriondFrozenShowersForwardLoose = efficienciesRel17MoriondForwardLoose;
  efficienciesRel17MoriondFrozenShowersForwardTight = efficienciesRel17MoriondForwardTight;

  efficienciesRel17MoriondFrozenShowersForwardLoose[7] *= 1.015;
  efficienciesRel17MoriondFrozenShowersForwardLoose[8] *= 1.008;
  efficienciesRel17MoriondFrozenShowersForwardLoose[9] *= 1.018;

  efficienciesRel17MoriondFrozenShowersForwardTight[7] *= 1.010;
  efficienciesRel17MoriondFrozenShowersForwardTight[8] *= 1.006;
  efficienciesRel17MoriondFrozenShowersForwardTight[9] *= 1.041;


  // 2011 data with rel. 17 and MC11a/b/c AFII ("Moriond SF")
const float sfLoosePP_Combined_Moriond_AFII_eta[] = {0.990782, 0.984431, 1.0473, 1.00123, 0.999666, 0.998526, 1.00158, 1.0011, 1.0422, 0.985262, 0.990121};
const float errsfLoosePP_Combined_Moriond_AFII_eta[] = {0.0206951, 0.0160733, 0.00920923, 0.00394199, 0.00433968, 0.00427718, 0.00434684, 0.00354063, 0.00832827, 0.0159877, 0.0185366};
const float sfLoosePP_Jpsi_Moriond_AFII_eta[] = {0.944222, 0.867498, 1.01712, 0.917386, 0.938785, 0.923568, 0.945621, 0.920033, 1.03348, 0.897483, 0.949521};
const float errsfLoosePP_Jpsi_Moriond_AFII_eta[] = {0.0528257, 0.0924515, 0.116728, 0.0549565, 0.0425954, 0.0456152, 0.0422733, 0.0611321, 0.129607, 0.0822144, 0.068279};
const float sfLoosePP_Combined_Moriond_AFII_pt[] = {0, 1.03524, 1.02731, 0.946599, 0.952656, 0.985613, 1.00222, 1.01042, 1.00727, 1.00107};
const float errsfLoosePP_Combined_Moriond_AFII_pt[] = {1., 0.0575071, 0.0554038, 0.0221221, 0.0191394, 0.0122292, 0.00584829, 0.00683113, 0.00533981, 0.0064188};

const float sfMedium_Combined_Moriond_AFII_eta[] = {0.993134, 0.973003, 1.0982, 0.997358, 1.0093, 1.01942, 1.01548, 0.998222, 1.0948, 0.97789, 0.992183};
const float errsfMedium_Combined_Moriond_AFII_eta[] = {0.0209136, 0.0138568, 0.00914549, 0.00418142, 0.00855772, 0.00459038, 0.0089923, 0.00384268, 0.00838153, 0.0146522, 0.0187527};
const float sfMedium_Jpsi_Moriond_AFII_eta[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
const float errsfMedium_Jpsi_Moriond_AFII_eta[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
const float sfMedium_Combined_Moriond_AFII_pt[] = {0., 1, 1, 0.94817, 0.938252, 0.976575, 0.997979, 1.01049, 1.01606, 1.01232};
const float errsfMedium_Combined_Moriond_AFII_pt[] = {1.00005, 1.00005, 1.00005, 0.0240558, 0.0205825, 0.00782366, 0.00611601, 0.00752741, 0.00545777, 0.00649618};

const float sfMediumPP_Combined_Moriond_AFII_eta[] = {0.985436, 0.979718, 1.1627, 1.00117, 1.01279, 1.02311, 1.01838, 1.00231, 1.154, 0.982628, 0.983485};
const float errsfMediumPP_Combined_Moriond_AFII_eta[] = {0.0182925, 0.0136327, 0.00914549, 0.00414907, 0.00754674, 0.00472048, 0.00843378, 0.00387936, 0.00866025, 0.0150049, 0.0178148};
const float sfMediumPP_Jpsi_Moriond_AFII_eta[] = {0.939877, 0.877112, 1.11866, 0.906626, 0.953615, 0.947036, 0.95061, 0.904586, 1.10336, 0.856909, 0.918436};
const float errsfMediumPP_Jpsi_Moriond_AFII_eta[] = {0.0544204, 0.0932347, 0.133983, 0.055122, 0.0422624, 0.0459001, 0.0418465, 0.0611701, 0.141489, 0.0819855, 0.0715578};
const float sfMediumPP_Combined_Moriond_AFII_pt[] = {0., 1.06326, 1.01785, 0.935893, 0.932939, 0.973115, 0.996294, 1.00996, 1.01637, 1.0127};
const float errsfMediumPP_Combined_Moriond_AFII_pt[] = {1., 0.0561516, 0.0509324, 0.0246582, 0.0217461, 0.00823226, 0.0063997, 0.00788586, 0.00555109, 0.00656721};

const float sfTightPP_Combined_Moriond_AFII_eta[] = {1.00032, 0.997738, 1.2036, 1.0263, 1.01493, 1.03012, 1.01828, 1.02795, 1.1994, 1.00119, 0.999282};
const float errsfTightPP_Combined_Moriond_AFII_eta[] = {0.0180631, 0.013335, 0.0120847, 0.00472454, 0.00465211, 0.00587229, 0.00919978, 0.00446069, 0.00974115, 0.0128199, 0.0176403};
const float sfTightPP_Jpsi_Moriond_AFII_eta[] = {0.961117, 0.878841, 1.12571, 0.908417, 0.962517, 0.947508, 0.958219, 0.897417, 1.15715, 0.859185, 0.943734};
const float errsfTightPP_Jpsi_Moriond_AFII_eta[] = {0.058636, 0.0955017, 0.14339, 0.0581671, 0.0453877, 0.0501971, 0.0461154, 0.0635471, 0.151759, 0.0846577, 0.0746562};
const float sfTightPP_Combined_Moriond_AFII_pt[] = {0., 1.05978, 1.02195, 0.944854, 0.938838, 0.974907, 0.995292, 1.0075, 1.01237, 1.01166};
const float errsfTightPP_Combined_Moriond_AFII_pt[] = {1., 0.0632592, 0.0528317, 0.0260368, 0.0231078, 0.00852419, 0.00717741, 0.00797035, 0.00573223, 0.00678183};


  // reco+TQ are by choice identical to the "Cern council" results!
  copyToVector(Sf_RecoTrkQ_Eta, 11, efficienciesRel17MoriondAFIIRecoTrkQual, 1.);
  copyToVector(Sf_RecoTrkQ_Eta_err, 11, uncertaintiesRel17MoriondAFIIRecoTrkQual, 1.);
 
 // Identification eta for probes between 15 and 50 GeV
  copyToVector(sfLoosePP_Combined_Moriond_AFII_eta, 11, efficienciesRel17MoriondAFIILoosePP1550);
  copyToVector(errsfLoosePP_Combined_Moriond_AFII_eta, 11, uncertaintiesRel17MoriondAFIILoosePP1550);
  copyToVector(sfMedium_Combined_Moriond_AFII_eta, 11, efficienciesRel17MoriondAFIIMedium1550);
  copyToVector(errsfMedium_Combined_Moriond_AFII_eta, 11, uncertaintiesRel17MoriondAFIIMedium1550);
  copyToVector(sfMediumPP_Combined_Moriond_AFII_eta, 11, efficienciesRel17MoriondAFIIMediumPP1550);
  copyToVector(errsfMediumPP_Combined_Moriond_AFII_eta, 11, uncertaintiesRel17MoriondAFIIMediumPP1550);
  copyToVector(sfTightPP_Combined_Moriond_AFII_eta, 11, efficienciesRel17MoriondAFIITightPP1550);
  copyToVector(errsfTightPP_Combined_Moriond_AFII_eta, 11, uncertaintiesRel17MoriondAFIITightPP1550);
  //Identification eta for low ET probes
  copyToVector(sfLoosePP_Jpsi_Moriond_AFII_eta, 11, efficienciesRel17MoriondAFIILoosePP415);
  copyToVector(errsfLoosePP_Jpsi_Moriond_AFII_eta, 11, uncertaintiesRel17MoriondAFIILoosePP415);
  copyToVector(sfMedium_Jpsi_Moriond_AFII_eta, 11, efficienciesRel17MoriondAFIIMedium415);
  copyToVector(errsfMedium_Jpsi_Moriond_AFII_eta, 11, uncertaintiesRel17MoriondAFIIMedium415);
  copyToVector(sfMediumPP_Jpsi_Moriond_AFII_eta, 11, efficienciesRel17MoriondAFIIMediumPP415);
  copyToVector(errsfMediumPP_Jpsi_Moriond_AFII_eta, 11, uncertaintiesRel17MoriondAFIIMediumPP415);
  copyToVector(sfTightPP_Jpsi_Moriond_AFII_eta, 11, efficienciesRel17MoriondAFIITightPP415);
  copyToVector(errsfTightPP_Jpsi_Moriond_AFII_eta, 11, uncertaintiesRel17MoriondAFIITightPP415);
  // ET correction
  copyToVector(sfLoosePP_Combined_Moriond_AFII_pt, 10, ETCorrectionsRel17MoriondAFIILoosePP);
  copyToVector(errsfLoosePP_Combined_Moriond_AFII_pt, 10, uncertaintiesETCorrectionsRel17MoriondAFIILoosePP);
  copyToVector(sfMedium_Combined_Moriond_AFII_pt, 10, ETCorrectionsRel17MoriondAFIIMedium);
  copyToVector(errsfMedium_Combined_Moriond_AFII_pt, 10, uncertaintiesETCorrectionsRel17MoriondAFIIMedium);
  copyToVector(sfMediumPP_Combined_Moriond_AFII_pt, 10, ETCorrectionsRel17MoriondAFIIMediumPP);
  copyToVector(errsfMediumPP_Combined_Moriond_AFII_pt, 10, uncertaintiesETCorrectionsRel17MoriondAFIIMediumPP);
  copyToVector(sfTightPP_Combined_Moriond_AFII_pt, 10, ETCorrectionsRel17MoriondAFIITightPP);
  copyToVector(errsfTightPP_Combined_Moriond_AFII_pt, 10, uncertaintiesETCorrectionsRel17MoriondAFIITightPP);
  
 // Trigger efficiencies 
 // e20_medium B-J

const float mcEff_e20_loo1AF_eta[]={0.837784, 0.958348, 0.954186, 0.944921, 0.834737, 0.971725, 
0.97076, 0.965811, 0.953751, 0.953137, 0.93615, 0.944741, 0.959838, 0.964714, 0.963277, 0.849676, 
0.951548, 0.954741, 0.958616, 0.846399}; 
 const float mcEff_e20_med1AF_eta[]={0.898123, 0.979152, 0.982123, 0.976245, 0.908137, 0.989558, 
0.991127, 0.993397, 0.984975, 0.988081, 0.976318, 0.979741, 0.987332, 0.986481, 0.981413, 0.916848, 
0.981398, 0.981793, 0.979101, 0.902182}; 
const float mcEff_e20_tig1AF_eta[]={0.91683, 0.986025, 0.98714, 0.981276, 0.912122, 0.992078, 
0.993612, 0.995387, 0.986526, 0.991699, 0.980298, 0.981418, 0.989378, 0.989054, 0.984199, 0.92104, 
0.986463, 0.986933, 0.985685, 0.921703}; 

const float mcEff_e20_loo1AF_Et[]={0.875913, 0.914573, 0.951531, 0.984388, 0.996399, 1.00911};
const float mcEff_e20_med1AF_Et[]={0.93754, 0.967349, 0.987042, 0.99702, 0.99998, 1.00245};
const float mcEff_e20_tig1AF_Et[]={0.945612, 0.971708, 0.988945, 0.99764, 1.00018, 1.00189};

const  float SF_e20_loo1AF_eta[]={1.01159, 0.974655, 0.982602, 0.968572, 1.01941, 0.983739, 0.987819, 
0.97726, 1.01088, 0.903296, 0.972191, 1.01517, 1.00338, 0.996529, 0.989118, 1.02178, 0.971944, 
0.981215, 0.981992, 1.01294}; 
const float SF_e20_loo1AF_eta_toterror[]={0.0127233, 0.00162322, 0.00192803, 0.00676287, 0.0112238, 
0.00184649, 0.00106451, 0.00145809, 0.00081248, 0.00363176, 0.00642653, 0.000852247, 0.00118298, 
0.00105471, 0.00147156, 0.00642835, 0.00484407, 0.00192131, 0.00152101, 0.0116767}; 
const  float SF_e20_med1AF_eta[]={0.982521, 0.97788, 0.98448, 0.983248, 0.964709, 0.998338, 0.990116, 
0.976901, 1.0038, 0.897178, 0.963795, 1.00591, 1.0032, 0.997999, 1.00497, 0.965928, 0.984674, 
0.979194, 0.985067, 0.988369}; 
const float SF_e20_med1AF_eta_toterror[]={0.0120236, 0.00133611, 0.00140082, 0.00237377, 0.0074995, 
0.000718399, 0.000621108, 0.000937908, 0.000408613, 0.00297396, 0.00374874, 0.000519895, 
0.000600476, 0.000664762, 0.000916474, 0.00516008, 0.00122018, 0.00152137, 0.00124171, 0.0112851}; 
const float SF_e20_tig1AF_eta[]={0.975036, 0.975921, 0.984533, 0.983307, 0.963394, 0.997896, 0.990237, 
0.976572, 1.00381, 0.918325, 0.971076, 1.00582, 1.00246, 0.997985, 1.00531, 0.965012, 0.985399, 
0.980433, 0.984076, 0.977792}; 
const float SF_e20_tig1AF_eta_toterror[]={0.0119353, 0.00134182, 0.00144698, 0.00244823, 0.00715443, 
0.000685729, 0.000590407, 0.000939461, 0.000393648, 0.0025467, 0.00279181, 0.000515491, 
0.000565587, 0.000603549, 0.000878349, 0.00568995, 0.00114848, 0.00145738, 0.00123273, 0.0113562}; 

const float SF_e20_loo1AF_Et[]={0.966609, 0.972459, 0.984701, 0.991333, 0.996887, 1.00341};
const float SF_e20_loo1AF_Et_toterror[]={0.0101678, 0.00776877, 0.00648891, 0.00567344, 0.00510576, 
0.00503267};
const float SF_e20_med1AF_Et[]={0.998711, 0.994343, 0.995275, 0.996295, 0.999002, 1.00149};
const float SF_e20_med1AF_Et_toterror[]={0.00721775, 0.00577872, 0.00530762, 0.00520579, 0.00503048, 0.00501212};
const float SF_e20_tig1AF_Et[]={0.998593, 0.991357, 0.994461, 0.996193, 0.99918, 1.0015};
const float SF_e20_tig1AF_Et_toterror[]={0.00736422, 0.00580596, 0.00526614, 0.00519258, 0.00503818, 0.005011};


  copyToVector(SF_e20_loo1AF_eta, 20, efficienciesRel17MoriondAFIIe20_mediumLoosePP);
  copyToVector(SF_e20_loo1AF_eta_toterror, 20, uncertaintiesRel17MoriondAFIIe20_mediumLoosePP);
  copyToVector(SF_e20_loo1AF_Et, 6, efficienciesRel17MoriondAFIIe20_mediumLoosePPET);
  copyToVector(SF_e20_loo1AF_Et_toterror, 6, uncertaintiesRel17MoriondAFIIe20_mediumLoosePPET);
  
  copyToVector(SF_e20_med1AF_eta, 20, efficienciesRel17MoriondAFIIe20_mediumMediumPP);
  copyToVector(SF_e20_med1AF_eta_toterror, 20, uncertaintiesRel17MoriondAFIIe20_mediumMediumPP);
  copyToVector(SF_e20_med1AF_Et, 6, efficienciesRel17MoriondAFIIe20_mediumMediumPPET);
  copyToVector(SF_e20_med1AF_Et_toterror, 6, uncertaintiesRel17MoriondAFIIe20_mediumMediumPPET);

  copyToVector(SF_e20_tig1AF_eta, 20, efficienciesRel17MoriondAFIIe20_mediumTightPP);
  copyToVector(SF_e20_tig1AF_eta_toterror, 20, uncertaintiesRel17MoriondAFIIe20_mediumTightPP);
  copyToVector(SF_e20_tig1AF_Et, 6, efficienciesRel17MoriondAFIIe20_mediumTightPPET);
  copyToVector(SF_e20_tig1AF_Et_toterror, 6, uncertaintiesRel17MoriondAFIIe20_mediumTightPPET);

  copyToVector(mcEff_e20_loo1AF_eta, 20, MCefficienciesRel17MoriondAFIIe20_mediumLoosePP);
  copyToVector(mcEff_e20_loo1AF_Et, 6, MCefficienciesRel17MoriondAFIIe20_mediumLoosePPET);
  copyToVector(mcEff_e20_med1AF_eta, 20, MCefficienciesRel17MoriondAFIIe20_mediumMediumPP);
  copyToVector(mcEff_e20_med1AF_Et, 6, MCefficienciesRel17MoriondAFIIe20_mediumMediumPPET);
  copyToVector(mcEff_e20_tig1AF_eta, 20, MCefficienciesRel17MoriondAFIIe20_mediumTightPP);
  copyToVector(mcEff_e20_tig1AF_Et, 6, MCefficienciesRel17MoriondAFIIe20_mediumTightPPET);


  // e22_medium K

const float mcEff_e22_loo1AF_eta[20] = {0.833747,0.956846,0.951756,0.943097,0.809434,0.969812,0.970325,0.965237,0.953058,0.951805,0.919851,0.927237,0.942461,0.946344,0.944457,0.825211,0.94888,0.953134,0.95764,0.843531};
const float mcEff_e22_med1AF_eta[20] = {0.90366, 0.97809, 0.98258, 0.97693, 0.88845, 0.98838, 0.99082, 0.99282, 0.98426, 0.98784, 0.96275, 0.96594, 0.97370, 0.97213, 0.96527, 0.89546, 0.98029, 0.98190, 0.97815, 0.89741};
const float mcEff_e22_tig1AF_eta[20] = {0.93069, 0.98667, 0.98724, 0.98215, 0.89277, 0.99071, 0.99317, 0.99507, 0.98575, 0.99166, 0.96768, 0.96734, 0.97543, 0.97595, 0.96925, 0.90150, 0.98575, 0.98697, 0.98643, 0.92243};
const float mcEff_e22_loo1AF_Et[]={0., 0.885186, 0.939948, 0.981269, 0.996204, 1.01011};
const float mcEff_e22_med1AF_Et[]={0., 0.940987, 0.979161, 0.994945, 0.999995, 1.00335};
const float mcEff_e22_tig1AF_Et[]={0., 0.946754, 0.981608, 0.995751, 1.00006, 1.00283};

const float  SF_e22_loo1AF_eta[20]={1.0536,0.97881,0.983469,0.969107,1.03897,0.983133,0.988574,0.977489,1.01089,0.904715,0.986548,1.03174,1.02249,1.01525,1.00702,1.03936,0.976207,0.978133,0.98838,1.03178};
const float SF_e22_loo1AF_eta_toterror[20]={0.0150737, 0.00273343, 0.00338387, 0.00654829, 0.0147355, 
0.00229121, 0.00153903, 0.002332, 0.00129245, 0.00545286, 0.00650272, 0.00137271, 0.00199354, 
0.0015861, 0.00240757, 0.00941302, 0.00430818, 0.00362917, 0.00235633, 0.0140102};
const float SF_e22_med1AF_eta[]={1.01241, 0.981162, 0.983998, 0.98209, 0.977993, 0.998123, 0.990079, 
0.977828, 1.003, 0.898257, 0.975397, 1.02197, 1.02169, 1.01657, 1.01914, 0.978953, 0.986046, 
0.973089, 0.989486, 1.00536}; 
const float SF_e22_med1AF_eta_toterror[]={0.0135984, 0.0022501, 0.00247966, 0.00378395, 0.010849, 
0.00121093, 0.0010623, 0.00158136, 0.000705665, 0.00462989, 0.00497647, 0.000843935, 0.00108361, 0.00103298, 
0.0016114, 0.00881784, 0.00192929, 0.00276556, 0.00189862, 0.0131987}; 
const float SF_e22_tig1AF_eta[]={1.00792, 0.978083, 0.98605, 0.982132, 0.979026, 0.997125, 0.990273, 
0.977802, 1.00294, 0.916215, 0.987263, 1.02216, 1.02163, 1.0161, 1.0188, 0.979266, 0.986212, 
0.974763, 0.98686, 0.994493}; 
const float SF_e22_tig1AF_eta_toterror[]={0.0134268, 0.00216703, 0.00238488, 0.00398101, 0.0107513, 
0.00120725, 0.00110686, 0.00157572, 0.00067908, 0.00427834, 0.00403234, 0.000845761, 0.00101562, 
0.00102069, 0.00155189, 0.00832287, 0.00198942, 0.00271315, 0.00190448, 0.0134414}; 

const float SF_e22_loo1AF_Et[]={0., 0.979921, 0.985088, 0.992992, 0.996368, 1.00287};
const float SF_e22_loo1AF_Et_toterror[]={1., 0.00943126, 0.00686203, 0.00605053, 0.00516196, 0.00506721};
const float SF_e22_med1AF_Et[]={0., 0.998053, 0.994937, 0.997683, 0.99907, 1.00108};
const float SF_e22_med1AF_Et_toterror[]={1., 0.00732952, 0.00586389, 0.00554881, 0.0050874, 0.00502854};
const float SF_e22_tig1AF_Et[]={0., 0.99551, 0.993202, 0.998189, 0.999363, 1.001};
const float SF_e22_tig1AF_Et_toterror[]={1., 0.00750782, 0.00566467, 0.00551505, 0.00508131, 0.00502837};


  copyToVector(SF_e22_loo1AF_eta, 20, efficienciesRel17MoriondAFIIe22_mediumLoosePP);
  copyToVector(SF_e22_loo1AF_eta_toterror, 20, uncertaintiesRel17MoriondAFIIe22_mediumLoosePP);
  copyToVector(SF_e22_loo1AF_Et, 6, efficienciesRel17MoriondAFIIe22_mediumLoosePPET);
  copyToVector(SF_e22_loo1AF_Et_toterror, 6, uncertaintiesRel17MoriondAFIIe22_mediumLoosePPET);

  copyToVector(SF_e22_med1AF_eta, 20, efficienciesRel17MoriondAFIIe22_mediumMediumPP);
  copyToVector(SF_e22_med1AF_eta_toterror, 20, uncertaintiesRel17MoriondAFIIe22_mediumMediumPP);
  copyToVector(SF_e22_med1AF_Et, 6, efficienciesRel17MoriondAFIIe22_mediumMediumPPET);
  copyToVector(SF_e22_med1AF_Et_toterror, 6, uncertaintiesRel17MoriondAFIIe22_mediumMediumPPET);

  copyToVector(SF_e22_tig1AF_eta, 20, efficienciesRel17MoriondAFIIe22_mediumTightPP);
  copyToVector(SF_e22_tig1AF_eta_toterror, 20, uncertaintiesRel17MoriondAFIIe22_mediumTightPP);
  copyToVector(SF_e22_tig1AF_Et, 6, efficienciesRel17MoriondAFIIe22_mediumTightPPET);
  copyToVector(SF_e22_tig1AF_Et_toterror, 6, uncertaintiesRel17MoriondAFIIe22_mediumTightPPET);

  copyToVector(mcEff_e22_loo1AF_eta, 20, MCefficienciesRel17MoriondAFIIe22_mediumLoosePP);
  copyToVector(mcEff_e22_loo1AF_Et, 6, MCefficienciesRel17MoriondAFIIe22_mediumLoosePPET);
  copyToVector(mcEff_e22_med1AF_eta, 20, MCefficienciesRel17MoriondAFIIe22_mediumMediumPP);
  copyToVector(mcEff_e22_med1AF_Et, 6, MCefficienciesRel17MoriondAFIIe22_mediumMediumPPET);
  copyToVector(mcEff_e22_tig1AF_eta, 20, MCefficienciesRel17MoriondAFIIe22_mediumTightPP);
  copyToVector(mcEff_e22_tig1AF_Et, 6, MCefficienciesRel17MoriondAFIIe22_mediumTightPPET);

  // e22vh_medium1 L-M

const float mcEff_e22vh_loo1AF_eta[20]={0.687217,0.869343,0.889377,0.894433,0.707848,0.927745,0.930883,0.926332,0.923035,0.914771,0.904406,0.921625,0.929644,0.931911,0.922862,0.717363,0.902978,0.888726,0.868617,0.710998};
const float mcEff_e22vh_med1AF_eta[20]={0.863631,0.956778,0.953849,0.948926,0.864313,0.97087,0.976042,0.977363,0.973809,0.975869,0.971452,0.976045,0.978746,0.978596,0.966552,0.872116,0.956014,0.952087,0.95684,0.868906};
const float  mcEff_e22vh_tig1AF_eta[20]={0.886873,0.967241,0.963728,0.957384,0.871022,0.976454,0.980351,0.980797,0.976152,0.979879,0.97632,0.978193,0.981469,0.982378,0.971531,0.879474,0.964959,0.962242,0.967308,0.890388};
const float mcEff_e22vh_loo1AF_Et[]={0., 0.840015, 0.913787, 0.97277, 0.994508, 1.01668};
const float mcEff_e22vh_med1AF_Et[]={0., 0.915316, 0.968868, 0.993366, 1.00034, 1.00444};
const float mcEff_e22vh_tig1AF_Et[]={0., 0.922225, 0.972056, 0.994273, 1.0006, 1.00361};

 const float SF_e22vh_loo1AF_eta[]={1.01634, 0.944556, 0.983225, 0.97009, 1.00127, 0.985803, 0.994047, 
0.981245, 1.0103, 0.916105, 0.953837, 1.00636, 1.00198, 0.994332, 0.987251, 1.06357, 0.969275, 
0.976274, 0.952691, 0.98456}; 
const float SF_e22vh_loo1AF_eta_toterror[]={0.0135111, 0.00261142, 0.00272109, 0.00769375, 0.0157165, 
0.00170863, 0.00119628, 0.00157821, 0.00106624, 0.00361085, 0.00797615, 0.00112804, 0.00152361, 
0.00120121, 0.00197525, 0.0117977, 0.00563133, 0.00274614, 0.0024229, 0.0136814}; 
const float SF_e22vh_med1AF_eta[]={0.935521, 0.965343, 0.974842, 0.980607, 0.892346, 0.993804, 0.992018, 
0.978343, 1.00254, 0.908673, 0.943179, 0.995608, 0.997979, 0.991227, 0.992714, 0.942859, 0.979602, 
0.96671, 0.974127, 0.923082}; 
const float SF_e22vh_med1AF_eta_toterror[]={0.0117289, 0.00160082, 0.00194001, 0.00325921, 0.00863573, 
0.00103898, 0.000756795, 0.00106191, 0.000555511, 0.00270058, 0.00484516, 0.000592502, 0.000825087, 
0.000741658, 0.00113719, 0.00614673, 0.00193288, 0.00193402, 0.00147208, 0.0117276}; 
const float SF_e22vh_tig1AF_eta[]={0.929489, 0.967151, 0.979212, 0.98471, 0.896601, 0.999751, 0.994103, 
0.979477, 1.00637, 0.940301, 0.971972, 0.99967, 0.999566, 0.993977, 0.998478, 0.947168, 0.984156, 
0.972131, 0.975489, 0.916916}; 
const float SF_e22vh_tig1AF_eta_toterror[]={0.0117703, 0.00153752, 0.00180921, 0.00352061, 0.008609, 
0.000942758, 0.000719669, 0.00103639, 0.000486768, 0.0022468, 0.0031436, 0.000543901, 0.000767379, 
0.000686692, 0.00103902, 0.00604, 0.0019273, 0.00192993, 0.0014464, 0.0120508}; 

const float SF_e22vh_loo1AF_Et[]={0., 0.96301, 0.981539, 0.986071, 0.993393, 1.0057};
const float SF_e22vh_loo1AF_Et_toterror[]={1., 0.00907074, 0.00832292, 0.00640083, 0.00523584, 0.00513875};
const float SF_e22vh_med1AF_Et[]={0., 0.994123, 0.995714, 0.994947, 0.996375, 1.00249};
const float SF_e22vh_med1AF_Et_toterror[]={1., 0.00670693, 0.0061998, 0.0055103, 0.00512157, 0.00502586};
const float SF_e22vh_tig1AF_Et[]={0., 0.994298, 0.997056, 0.995666, 0.997267, 1.00191};
const float SF_e22vh_tig1AF_Et_toterror[]={1., 0.00682907, 0.00591816, 0.0054974, 0.00514654, 0.00501857};


  copyToVector(SF_e22vh_loo1AF_eta, 20, efficienciesRel17MoriondAFIIe22vh_medium1LoosePP);
  copyToVector(SF_e22vh_loo1AF_eta_toterror, 20, uncertaintiesRel17MoriondAFIIe22vh_medium1LoosePP);
  copyToVector(SF_e22vh_loo1AF_Et, 6, efficienciesRel17MoriondAFIIe22vh_medium1LoosePPET);
  copyToVector(SF_e22vh_loo1AF_Et_toterror, 6, uncertaintiesRel17MoriondAFIIe22vh_medium1LoosePPET);

  copyToVector(SF_e22vh_med1AF_eta, 20, efficienciesRel17MoriondAFIIe22vh_medium1MediumPP);
  copyToVector(SF_e22vh_med1AF_eta_toterror, 20, uncertaintiesRel17MoriondAFIIe22vh_medium1MediumPP);
  copyToVector(SF_e22vh_med1AF_Et, 6, efficienciesRel17MoriondAFIIe22vh_medium1MediumPPET);
  copyToVector(SF_e22vh_med1AF_Et_toterror, 6, uncertaintiesRel17MoriondAFIIe22vh_medium1MediumPPET);

  copyToVector(SF_e22vh_tig1AF_eta, 20, efficienciesRel17MoriondAFIIe22vh_medium1TightPP);
  copyToVector(SF_e22vh_tig1AF_eta_toterror, 20, uncertaintiesRel17MoriondAFIIe22vh_medium1TightPP);
  copyToVector(SF_e22vh_tig1AF_Et, 6, efficienciesRel17MoriondAFIIe22vh_medium1TightPPET);
  copyToVector(SF_e22vh_tig1AF_Et_toterror, 6, uncertaintiesRel17MoriondAFIIe22vh_medium1TightPPET);

  copyToVector(mcEff_e22vh_loo1AF_eta, 20, MCefficienciesRel17MoriondAFIIe22vh_medium1LoosePP);
  copyToVector(mcEff_e22vh_loo1AF_Et, 6, MCefficienciesRel17MoriondAFIIe22vh_medium1LoosePPET);
  copyToVector(mcEff_e22vh_med1AF_eta, 20, MCefficienciesRel17MoriondAFIIe22vh_medium1MediumPP);
  copyToVector(mcEff_e22vh_med1AF_Et, 6, MCefficienciesRel17MoriondAFIIe22vh_medium1MediumPPET);
  copyToVector(mcEff_e22vh_tig1AF_eta, 20, MCefficienciesRel17MoriondAFIIe22vh_medium1TightPP);
  copyToVector(mcEff_e22vh_tig1AF_Et, 6, MCefficienciesRel17MoriondAFIIe22vh_medium1TightPPET);

  // Rel17.2 ICHEP2012
  runranges_ICHEP2012.push_back(200804);
  runranges_ICHEP2012.push_back(203228);
  runranges_ICHEP2012.push_back(204134);
  runranges_ICHEP2012.push_back(299999);

  // Raw Rel17.2 ICHEP2012 Reco+TQ SF
const float Sf_RecoTrk_ICHEP2012_FullSim_Eta[]={ 100.17, 100.09, 99.56, 100.06, 99.68, 99.63, 99.49, 99.42, 99.16, 99.05, 
        98.51, 99.19, 99.59, 99.65, 99.74, 99.54, 99.69, 100.03, 100.11, 101.35};
const float Sf_RecoTrk_ICHEP2012_FullSim_Eta_err[]={ 0.88, 0.63, 0.67, 0.59, 0.73, 0.62, 0.60, 0.67, 0.68, 0.81,
						     0.86, 0.68, 0.68, 0.63, 0.61, 0.77, 0.61, 0.65, 0.60, 1.03};
  // Raw Rel17.2 ICHEP2012 Identification SF
const float sfLoosePP_Combined_ICHEP2012_FullSim_eta[] = {0.987364, 0.987379, 0.990928, 0.984649, 0.988641, 0.993711, 0.997745, 0.989537, 0.994535, 0.995155, 1.00108, 0.994803, 0.994159, 0.993825, 0.996122, 0.982731, 0.985756, 0.993547, 0.985504, 0.988026};
const float errsfLoosePP_Combined_ICHEP2012_FullSim_eta[] = {0.0071796, 0.00749325, 0.00664238, 0.00676599, 0.00778821, 0.00645217, 0.00547359, 0.00638748, 0.00519282, 0.0071698, 0.0073661, 0.00519869, 0.0063059, 0.00558669, 0.00612042, 0.00727061, 0.00684737, 0.00687769, 0.00631499, 0.00741711};
const float sfLoosePP_Jpsi_ICHEP2012_FullSim_eta[] = {0.91527, 0.91527, 0.974753, 0.974753, 0.74059, 1.00478, 1.00478, 0.968881, 0.968881, 0.954486, 0.954486, 0.968881, 0.968881, 1.00478, 1.00478, 0.74059, 0.974753, 0.974753, 0.91527, 0.91527};
const float errsfLoosePP_Jpsi_ICHEP2012_FullSim_eta[] = {0.0598101, 0.0598101, 0.0618038, 0.0618038, 0.162827, 0.0620513, 0.0620513, 0.0297072, 0.0297072, 0.0429718, 0.0429718, 0.0297072, 0.0297072, 0.0620513, 0.0620513, 0.162827, 0.0618038, 0.0618038, 0.0598101, 0.0598101};
const float sfLoosePP_Combined_ICHEP2012_FullSim_pt[] = {0., 1.01257, 0.994296, 0.986777, 0.9926, 0.995081, 0.997315, 1.00303, 1.00014, 1.00279};
const float errsfLoosePP_Combined_ICHEP2012_FullSim_pt[] = {1., 0.0420641, 0.0312593, 0.0144229, 0.0108073, 0.00841313, 0.00738718, 0.00644986, 0.00583332, 0.00597086};
const float sfMediumPP_Combined_ICHEP2012_FullSim_eta[] = {0.87404, 0.957077, 0.988879, 0.982049, 1.00371, 1.00089, 0.993011, 0.986335, 0.98503, 0.98446, 0.993192, 0.985622, 0.987418, 0.985391, 0.992725, 0.98578, 0.972556, 0.992569, 0.947343, 0.862924};
const float errsfMediumPP_Combined_ICHEP2012_FullSim_eta[] = {0.00810588, 0.00690462, 0.00721425, 0.00910648, 0.011541, 0.00715064, 0.00568557, 0.00674545, 0.00550176, 0.00755203, 0.00775166, 0.0054039, 0.0066015, 0.00603667, 0.00655796, 0.00952103, 0.00836118, 0.00751994, 0.00674452, 0.00820352};
const float sfMediumPP_Jpsi_ICHEP2012_FullSim_eta[] = {0.866197, 0.866197, 0.962979, 0.962979, 0.904127, 0.972332, 0.972332, 0.937871, 0.937871, 0.928985, 0.928985, 0.937871, 0.937871, 0.972332, 0.972332, 0.904127, 0.962979, 0.962979, 0.866197, 0.866197};
const float errsfMediumPP_Jpsi_ICHEP2012_FullSim_eta[] = {0.0600513, 0.0600513, 0.0757844, 0.0757844, 0.183368, 0.0656124, 0.0656124, 0.0445448, 0.0445448, 0.0574999, 0.0574999, 0.0445448, 0.0445448, 0.0656124, 0.0656124, 0.183368, 0.0757844, 0.0757844, 0.0600513, 0.0600513};
const float sfMediumPP_Combined_ICHEP2012_FullSim_pt[] = {0., 0.985027, 0.996811, 0.979568, 0.972108, 0.986021, 0.99579, 1.00522, 1.00345, 1.0074};
const float errsfMediumPP_Combined_ICHEP2012_FullSim_pt[] = {1., 0.0493258, 0.0354562, 0.0176138, 0.0126734, 0.0092937, 0.00809336, 0.00683625, 0.00590703, 0.00603461};
const float sfTightPP_Combined_ICHEP2012_FullSim_eta[] = {0.930744, 0.961164, 1.00531, 1.00644, 1.05451, 1.03309, 1.00004, 0.994434, 0.972013, 0.990799, 0.998388, 0.972589, 0.995779, 0.998215, 1.02542, 1.02591, 0.997232, 1.00955, 0.95144, 0.922011};
const float errsfTightPP_Combined_ICHEP2012_FullSim_eta[] = {0.00972178, 0.00683749, 0.00817691, 0.0105476, 0.0134716, 0.0079027, 0.00607182, 0.00714603, 0.00568264, 0.0128642, 0.00812256, 0.00565039, 0.00691809, 0.00659521, 0.00737416, 0.011579, 0.00974249, 0.00832908, 0.00719666, 0.0122134};
const float sfTightPP_Jpsi_ICHEP2012_FullSim_eta[] = {0.868955, 0.868955, 0.995929, 0.995929, 0.739608, 0.978624, 0.978624, 0.922656, 0.922656, 0.94204, 0.94204, 0.922656, 0.922656, 0.978624, 0.978624, 0.739608, 0.995929, 0.995929, 0.868955, 0.868955};
const float errsfTightPP_Jpsi_ICHEP2012_FullSim_eta[] = {0.0585262, 0.0585262, 0.0746998, 0.0746998, 0.296811, 0.0535224, 0.0535224, 0.0299912, 0.0299912, 0.0519417, 0.0519417, 0.0299912, 0.0299912, 0.0535224, 0.0535224, 0.296811, 0.0746998, 0.0746998, 0.0585262, 0.0585262};
const float sfTightPP_Combined_ICHEP2012_FullSim_pt[] = {0., 0.992914, 0.994417, 0.989651, 0.979188, 0.993662, 0.997165, 1.00578, 0.998631, 1.00191};
const float errsfTightPP_Combined_ICHEP2012_FullSim_pt[] = {1., 0.052229, 0.0368077, 0.0209003, 0.0149796, 0.0104897, 0.00890163, 0.00722296, 0.00599719, 0.00604058};
const float sfML_Combined_ICHEP2012_FullSim_eta[] = {0.970529, 0.97958, 0.98559, 0.986378, 1.00473, 0.992431, 0.995883, 0.98984, 0.995706, 0.994208, 0.9998, 0.996105, 0.992979, 0.991465, 0.9947, 0.99535, 0.987801, 0.990348, 0.977654, 0.969441};
const float errsfML_Combined_ICHEP2012_FullSim_eta[] = {0.0075259, 0.00623461, 0.0067099, 0.00656002, 0.00735255, 0.0063367, 0.00550871, 0.00645102, 0.00524159, 0.0072904, 0.00742402, 0.00521658, 0.00631767, 0.00568698, 0.00606575, 0.00684467, 0.00642388, 0.00694741, 0.00635931, 0.00782686};
const float sfML_Jpsi_ICHEP2012_FullSim_eta[] = {0.944157, 0.944157, 1.01088, 1.01088, 0.939516, 1.03015, 1.03015, 0.992631, 0.992631, 1.00361, 1.00361, 0.992631, 0.992631, 1.03015, 1.03015, 0.939516, 1.01088, 1.01088, 0.944157, 0.944157};
const float errsfML_Jpsi_ICHEP2012_FullSim_eta[] = {0.0723374, 0.0723374, 0.0777731, 0.0777731, 0.2042, 0.0722961, 0.0722961, 0.0514086, 0.0514086, 0.0601671, 0.0601671, 0.0514086, 0.0514086, 0.0722961, 0.0722961, 0.2042, 0.0777731, 0.0777731, 0.0723374, 0.0723374};
const float sfML_Combined_ICHEP2012_FullSim_pt[] = {0., 0.961119, 1.03077, 0.983377, 0.989613, 0.996496, 0.997865, 1.00302, 1.00042, 1.00258};
const float errsfML_Combined_ICHEP2012_FullSim_pt[] = {1., 0.0424335, 0.0310767, 0.0151659, 0.0109894, 0.00844686, 0.00734595, 0.00642996, 0.00583576, 0.00596439};

  // reco+TQ 
  copyToVector(Sf_RecoTrk_ICHEP2012_FullSim_Eta, 20, efficienciesRel172ICHEPRecoTrkQual, 1.);
  copyToVector(Sf_RecoTrk_ICHEP2012_FullSim_Eta_err, 20, uncertaintiesRel172ICHEPRecoTrkQual, 1.);
 
  // Identification eta for probes between 15 and 50 GeV
  copyToVector(sfLoosePP_Combined_ICHEP2012_FullSim_eta, 20, efficienciesRel172ICHEPLoosePP1550);
  copyToVector(errsfLoosePP_Combined_ICHEP2012_FullSim_eta, 20, uncertaintiesRel172ICHEPLoosePP1550);
  copyToVector(sfMediumPP_Combined_ICHEP2012_FullSim_eta, 20, efficienciesRel172ICHEPMediumPP1550);
  copyToVector(errsfMediumPP_Combined_ICHEP2012_FullSim_eta, 20, uncertaintiesRel172ICHEPMediumPP1550);
  copyToVector(sfTightPP_Combined_ICHEP2012_FullSim_eta, 20, efficienciesRel172ICHEPTightPP1550);
  copyToVector(errsfTightPP_Combined_ICHEP2012_FullSim_eta, 20, uncertaintiesRel172ICHEPTightPP1550);
  copyToVector(sfML_Combined_ICHEP2012_FullSim_eta, 20, efficienciesRel172ICHEPML1550);
  copyToVector(errsfML_Combined_ICHEP2012_FullSim_eta, 20, uncertaintiesRel172ICHEPML1550);
  //Identification eta for low ET probes
  copyToVector(sfLoosePP_Jpsi_ICHEP2012_FullSim_eta, 20, efficienciesRel172ICHEPLoosePP415);
  copyToVector(errsfLoosePP_Jpsi_ICHEP2012_FullSim_eta, 20, uncertaintiesRel172ICHEPLoosePP415);
  copyToVector(sfMediumPP_Jpsi_ICHEP2012_FullSim_eta, 20, efficienciesRel172ICHEPMediumPP415);
  copyToVector(errsfMediumPP_Jpsi_ICHEP2012_FullSim_eta, 20, uncertaintiesRel172ICHEPMediumPP415);
  copyToVector(sfTightPP_Jpsi_ICHEP2012_FullSim_eta, 20, efficienciesRel172ICHEPTightPP415);
  copyToVector(errsfTightPP_Jpsi_ICHEP2012_FullSim_eta, 20, uncertaintiesRel172ICHEPTightPP415);
  copyToVector(sfML_Jpsi_ICHEP2012_FullSim_eta, 20, efficienciesRel172ICHEPML415);
  copyToVector(errsfML_Jpsi_ICHEP2012_FullSim_eta, 20, uncertaintiesRel172ICHEPML415);
  // ET correction
  copyToVector(sfLoosePP_Combined_ICHEP2012_FullSim_pt, 10, ETCorrectionsRel172ICHEPLoosePP);
  copyToVector(errsfLoosePP_Combined_ICHEP2012_FullSim_pt, 10, uncertaintiesETCorrectionsRel172ICHEPLoosePP);
  copyToVector(sfMediumPP_Combined_ICHEP2012_FullSim_pt, 10, ETCorrectionsRel172ICHEPMediumPP);
  copyToVector(errsfMediumPP_Combined_ICHEP2012_FullSim_pt, 10, uncertaintiesETCorrectionsRel172ICHEPMediumPP);
  copyToVector(sfTightPP_Combined_ICHEP2012_FullSim_pt, 10, ETCorrectionsRel172ICHEPTightPP);
  copyToVector(errsfTightPP_Combined_ICHEP2012_FullSim_pt, 10, uncertaintiesETCorrectionsRel172ICHEPTightPP);
  copyToVector(sfML_Combined_ICHEP2012_FullSim_pt, 10, ETCorrectionsRel172ICHEPML);
  copyToVector(errsfML_Combined_ICHEP2012_FullSim_pt, 10, uncertaintiesETCorrectionsRel172ICHEPML);

  // single electron trigger e24vhi_medium1||e60_medium1 vs. different offline and 3 data periods, plus MC efficiencies!
const float sf_e24e60_ICHEP2012_period0_LoosePP_eta[] = {0.2899, 0.92037, 0.94225, 0.97048, 0.97059, 0.99468, 0.98196, 0.96851, 0.99093, 0.99854, 0.99877, 0.99726, 0.98354, 0.97778, 0.97665, 0.89871, 0.95507, 0.95387, 0.8937, 0.20499};
const float errsf_e24e60_ICHEP2012_period0_LoosePP_eta[] = {0.0192938, 0.011136, 0.0110494, 0.012512, 0.022836, 0.0105817, 0.010198, 0.0103053, 0.0101104, 0.0106453, 0.0105056, 0.0100854, 0.0103452, 0.0101827, 0.01033, 0.0170504, 0.0111404, 0.0110073, 0.0112209, 0.0131439};

const float effMC_e24e60_ICHEP2012_period0_LoosePP_eta[] = {0.7921, 0.8477, 0.83655, 0.86018, 0.62884, 0.90368, 0.90543, 0.92214, 0.92735, 0.90334, 0.89544, 0.92707, 0.92795, 0.90669, 0.90255, 0.64108, 0.85829, 0.84054, 0.85257, 0.80755};
const float sf_e24e60_ICHEP2012_period0_LoosePP_pt[] = {0.930722, 0.948576, 0.953993, 0.964265, 0.988936, 0.988068, 0.993055, 1, 0.997542, 1.00338, 1.01348, 1.00031, 1.01295, 1.01663, 1.01663};
const float errsf_e24e60_ICHEP2012_period0_LoosePP_pt[] = {0.0129287, 0.00999545, 0.00962752, 0.00705201, 0.00929025, 0.00519191, 0.00443561, 0.00259596, 0.001206, 0.0013593, 0.00174767, 0.00281058, 0.00491596, 0.0149319, 0.0184987};

const float effMC_e24e60_ICHEP2012_period0_LoosePP_pt[] = {0.748888, 0.887837, 0.911644, 0.925109, 0.944473, 0.956961, 0.972636, 0.989601, 1.00549, 1.01656, 1.01981, 1.05233, 1.06753, 1.07743, 1.08433};
const float sf_e24e60_ICHEP2012_period0_MediumPP_eta[] = {0.3277, 0.95195, 0.94959, 0.97587, 0.96163, 0.99468, 0.98962, 0.96952, 0.99801, 1.00432, 0.99981, 1.00189, 0.99479, 0.98972, 0.9868, 0.90391, 0.97373, 0.96399, 0.93235, 0.23194};
const float errsf_e24e60_ICHEP2012_period0_MediumPP_eta[] = {0.0165761, 0.0106148, 0.0109989, 0.0105367, 0.0175646, 0.0101572, 0.0101017, 0.010177, 0.0100369, 0.0102306, 0.0102679, 0.0100288, 0.0100867, 0.0100741, 0.0101589, 0.0138553, 0.0104204, 0.0107409, 0.010687, 0.0181528};

const float effMC_e24e60_ICHEP2012_period0_MediumPP_eta[] = {0.8076, 0.88712, 0.89246, 0.90588, 0.69876, 0.95495, 0.9571, 0.96456, 0.96547, 0.95059, 0.94712, 0.96528, 0.96578, 0.95812, 0.95423, 0.71449, 0.90451, 0.89742, 0.8894, 0.82147};
const float sf_e24e60_ICHEP2012_period0_MediumPP_pt[] = {0.948388, 0.951441, 0.968134, 0.969858, 0.985668, 0.994197, 0.997047, 0.998335, 1.00151, 0.998984, 1.00158, 1.01228, 1.00166, 1.006, 1.00209};
const float errsf_e24e60_ICHEP2012_period0_MediumPP_pt[] = {0.0118148, 0.00763652, 0.00754524, 0.00625728, 0.00496931, 0.00341767, 0.00235282, 0.00147051, 0.000943155, 0.00108514, 0.00144009, 0.00167334, 0.00347852, 0.0107702, 0.014624};

const float effMC_e24e60_ICHEP2012_period0_MediumPP_pt[] = {0.776329, 0.917128, 0.936747, 0.952269, 0.963133, 0.970174, 0.981376, 0.993044, 1.00162, 1.00927, 1.01049, 1.03235, 1.04062, 1.04395, 1.05053};
const float sf_e24e60_ICHEP2012_period0_ML_eta[] = {0.29189, 0.92903, 0.94506, 0.96821, 0.95695, 0.9955, 0.98538, 0.96817, 0.9913, 0.99946, 1.00125, 0.9971, 0.98576, 0.98026, 0.97783, 0.89077, 0.95619, 0.95374, 0.90015, 0.20429};
const float errsf_e24e60_ICHEP2012_period0_ML_eta[] = {0.0191401, 0.0110708, 0.0112163, 0.0121609, 0.0231601, 0.0105211, 0.0101697, 0.0102456, 0.0100867, 0.010449, 0.0104346, 0.0100706, 0.0102679, 0.0101643, 0.0103102, 0.0163221, 0.0113037, 0.0111404, 0.0113318, 0.0141351};

const float effMC_e24e60_ICHEP2012_period0_ML_eta[] = {0.79662, 0.8557, 0.8461, 0.86804, 0.63168, 0.90824, 0.91111, 0.92792, 0.92944, 0.91506, 0.91183, 0.9289, 0.93265, 0.9124, 0.90492, 0.64566, 0.86635, 0.85033, 0.85925, 0.812};
const float sf_e24e60_ICHEP2012_period0_ML_pt[] = {0.917946, 0.933936, 0.954677, 0.952763, 0.969675, 0.990651, 0.991736, 0.9958, 1.00317, 1.00035, 1.00616, 1.01635, 1.00309, 1.01538, 1.02367};
const float errsf_e24e60_ICHEP2012_period0_ML_pt[] = {0.0130218, 0.00963328, 0.00955138, 0.00764724, 0.00851741, 0.00535409, 0.00470915, 0.00210888, 0.00114657, 0.00133085, 0.00168915, 0.00250813, 0.00513911, 0.0150693, 0.0187752};

const float effMC_e24e60_ICHEP2012_period0_ML_pt[] = {0.744159, 0.882508, 0.906492, 0.922205, 0.940303, 0.955939, 0.971895, 0.990048, 1.00653, 1.01762, 1.02209, 1.04711, 1.06029, 1.0701, 1.07213};
const float sf_e24e60_ICHEP2012_period0_TightPP_eta[] = {0.32178, 0.94973, 0.95618, 0.97216, 0.96144, 0.99318, 0.98825, 0.97015, 0.99684, 1.00047, 0.99702, 1.00045, 0.99385, 0.98755, 0.98443, 0.90515, 0.97118, 0.96297, 0.93118, 0.23222};
const float errsf_e24e60_ICHEP2012_period0_TightPP_eta[] = {0.0165283, 0.0104934, 0.0107191, 0.0105622, 0.0172535, 0.0100907, 0.0100741, 0.0101304, 0.0100231, 0.0101845, 0.0102202, 0.0100192, 0.0100603, 0.0100682, 0.0101134, 0.0135882, 0.0103607, 0.0106048, 0.0106048, 0.018851};

const float effMC_e24e60_ICHEP2012_period0_TightPP_eta[] = {0.85848, 0.92638, 0.93376, 0.93998, 0.72304, 0.97935, 0.97497, 0.97901, 0.97981, 0.96592, 0.96259, 0.97967, 0.97999, 0.97579, 0.97835, 0.73878, 0.94078, 0.9381, 0.92849, 0.87291};
const float sf_e24e60_ICHEP2012_period0_TightPP_pt[] = {0.949221, 0.945388, 0.978816, 0.969818, 0.991239, 0.994686, 0.994828, 0.998275, 1.00123, 0.99922, 1.00157, 1.01163, 1.00283, 1.00301, 0.995967};
const float errsf_e24e60_ICHEP2012_period0_TightPP_pt[] = {0.011651, 0.00733016, 0.00798083, 0.00554083, 0.00421917, 0.00261283, 0.0021045, 0.00114883, 0.000813333, 0.000915, 0.00148433, 0.001403, 0.00303983, 0.0102988, 0.0155855};

const float effMC_e24e60_ICHEP2012_period0_TightPP_pt[] = {0.788841, 0.934628, 0.949171, 0.965813, 0.974764, 0.979116, 0.987127, 0.997019, 1.00107, 1.0044, 1.00306, 1.01974, 1.02235, 1.02757, 1.03292};
const float sf_e24e60_ICHEP2012_period1_LoosePP_eta[] = {1.01067, 0.94924, 0.95251, 0.9597, 0.92395, 0.9921, 0.98272, 0.96523, 0.99256, 0.99056, 0.98801, 0.993, 0.98498, 0.98035, 0.98269, 0.8941, 0.95713, 0.9592, 0.9482, 0.97946};
const float errsf_e24e60_ICHEP2012_period1_LoosePP_eta[] = {0.0132024, 0.0110198, 0.0108853, 0.0116825, 0.0260554, 0.0104346, 0.0102633, 0.0102, 0.0100571, 0.0103686, 0.0104232, 0.0100867, 0.0101733, 0.0102243, 0.0103102, 0.019637, 0.0112666, 0.0108117, 0.0106695, 0.0134136};

const float effMC_e24e60_ICHEP2012_period1_LoosePP_eta[] = {0.7921, 0.8477, 0.83655, 0.86018, 0.62884, 0.90368, 0.90543, 0.92214, 0.92735, 0.90334, 0.89544, 0.92707, 0.92795, 0.90669, 0.90255, 0.64108, 0.85829, 0.84054, 0.85257, 0.80755};
const float sf_e24e60_ICHEP2012_period1_LoosePP_pt[] = {0.958425, 0.957149, 0.974651, 0.973152, 0.981356, 0.989713, 0.996519, 0.999781, 1.00218, 1.00006, 1.00755, 0.994868, 1.00734, 0.98166, 0.98166};
const float errsf_e24e60_ICHEP2012_period1_LoosePP_pt[] = {0.0134004, 0.0128939, 0.00875126, 0.00872087, 0.0085183, 0.00520619, 0.00253219, 0.00165099, 0.00099262, 0.00112429, 0.00168138, 0.00215743, 0.00391983, 0.0117696, 0.02753};

const float effMC_e24e60_ICHEP2012_period1_LoosePP_pt[] = {0.748888, 0.887837, 0.911644, 0.925109, 0.944473, 0.956961, 0.972636, 0.989601, 1.00549, 1.01656, 1.01981, 1.05233, 1.06753, 1.07743, 1.08433};
const float sf_e24e60_ICHEP2012_period1_MediumPP_eta[] = {1.04099, 0.97285, 0.95806, 0.96808, 0.9167, 0.99056, 0.9865, 0.9698, 0.99678, 0.99079, 0.99258, 0.9975, 0.98976, 0.98251, 0.97871, 0.88038, 0.95949, 0.95845, 0.97277, 1.02476};
const float errsf_e24e60_ICHEP2012_period1_MediumPP_eta[] = {0.0131115, 0.0105273, 0.0106977, 0.0103712, 0.0197489, 0.0101554, 0.0100671, 0.0101194, 0.0100266, 0.01021, 0.0102285, 0.0100336, 0.0100867, 0.0100816, 0.0101385, 0.0145799, 0.0103686, 0.0106181, 0.0104695, 0.0137519};

const float effMC_e24e60_ICHEP2012_period1_MediumPP_eta[] = {0.8076, 0.88712, 0.89246, 0.90588, 0.69876, 0.95495, 0.9571, 0.96456, 0.96547, 0.95059, 0.94712, 0.96528, 0.96578, 0.95812, 0.95423, 0.71449, 0.90451, 0.89742, 0.8894, 0.82147};
const float sf_e24e60_ICHEP2012_period1_MediumPP_pt[] = {0.961688, 0.974066, 0.977863, 0.985284, 0.989484, 0.991574, 0.996108, 1.00044, 1.00039, 1.00054, 1.00186, 1.00646, 0.996744, 0.99735, 0.989363};
const float errsf_e24e60_ICHEP2012_period1_MediumPP_pt[] = {0.0105511, 0.00761297, 0.00589652, 0.00466471, 0.00495752, 0.00264536, 0.00159529, 0.000979387, 0.000797645, 0.000827936, 0.001252, 0.00165587, 0.002817, 0.00982416, 0.0189718};

const float effMC_e24e60_ICHEP2012_period1_MediumPP_pt[] = {0.776329, 0.917128, 0.936747, 0.952269, 0.963133, 0.970174, 0.981376, 0.993044, 1.00162, 1.00927, 1.01049, 1.03235, 1.04062, 1.04395, 1.05053};
const float sf_e24e60_ICHEP2012_period1_ML_eta[] = {1.01301, 0.949, 0.95785, 0.96029, 0.91495, 0.99354, 0.9847, 0.96624, 0.99212, 0.99346, 0.99288, 0.99238, 0.98686, 0.98199, 0.98436, 0.88724, 0.9564, 0.96193, 0.94818, 0.97897};
const float errsf_e24e60_ICHEP2012_period1_ML_eta[] = {0.0131568, 0.0108041, 0.0107852, 0.0118619, 0.0259723, 0.0104092, 0.010177, 0.0102, 0.0100592, 0.010325, 0.0103503, 0.0100841, 0.0101625, 0.0101864, 0.010277, 0.0192852, 0.0111272, 0.0107852, 0.0107191, 0.0131764};

const float effMC_e24e60_ICHEP2012_period1_ML_eta[] = {0.79662, 0.8557, 0.8461, 0.86804, 0.63168, 0.90824, 0.91111, 0.92792, 0.92944, 0.91506, 0.91183, 0.9289, 0.93265, 0.9124, 0.90492, 0.64566, 0.86635, 0.85033, 0.85925, 0.812};
const float sf_e24e60_ICHEP2012_period1_ML_pt[] = {0.940282, 0.959641, 0.959448, 0.975187, 0.973514, 0.983979, 0.992944, 0.998724, 1.00098, 1.00371, 1.00331, 1.00953, 0.997011, 1.00618, 0.970512};
const float errsf_e24e60_ICHEP2012_period1_ML_pt[] = {0.0122604, 0.00790996, 0.00739277, 0.00633811, 0.005395, 0.0034885, 0.00210932, 0.00118649, 0.000922829, 0.00104452, 0.00161242, 0.00208904, 0.00394484, 0.0122604, 0.0274212};

const float effMC_e24e60_ICHEP2012_period1_ML_pt[] = {0.744159, 0.882508, 0.906492, 0.922205, 0.940303, 0.955939, 0.971895, 0.990048, 1.00653, 1.01762, 1.02209, 1.04711, 1.06029, 1.0701, 1.07213};
const float sf_e24e60_ICHEP2012_period1_TightPP_eta[] = {1.04018, 0.97313, 0.95734, 0.96931, 0.91497, 0.98946, 0.98499, 0.96915, 0.99613, 0.99195, 0.99221, 0.9965, 0.98989, 0.98208, 0.97745, 0.88102, 0.95668, 0.96106, 0.97341, 1.01641};
const float errsf_e24e60_ICHEP2012_period1_TightPP_eta[] = {0.0125784, 0.0103766, 0.0104784, 0.0103819, 0.0186902, 0.0100961, 0.0100479, 0.0100907, 0.0100192, 0.010214, 0.010208, 0.0100186, 0.0100754, 0.0100648, 0.0100975, 0.014128, 0.0103053, 0.0104636, 0.0103401, 0.0131179};

const float effMC_e24e60_ICHEP2012_period1_TightPP_eta[] = {0.85848, 0.92638, 0.93376, 0.93998, 0.72304, 0.97935, 0.97497, 0.97901, 0.97981, 0.96592, 0.96259, 0.97967, 0.97999, 0.97579, 0.97835, 0.73878, 0.94078, 0.9381, 0.92849, 0.87291};
const float sf_e24e60_ICHEP2012_period1_TightPP_pt[] = {0.965203, 0.971656, 0.984391, 0.985999, 0.989367, 0.991481, 0.998359, 0.999401, 0.999825, 1.00087, 1.00157, 1.00671, 1.00068, 0.993049, 0.991724};
const float errsf_e24e60_ICHEP2012_period1_TightPP_pt[] = {0.0102461, 0.00620023, 0.00546187, 0.00408629, 0.00383342, 0.00232635, 0.00132501, 0.000799051, 0.000677676, 0.000718135, 0.00117329, 0.00123398, 0.00248818, 0.00947735, 0.0146965};

const float effMC_e24e60_ICHEP2012_period1_TightPP_pt[] = {0.788841, 0.934628, 0.949171, 0.965813, 0.974764, 0.979116, 0.987127, 0.997019, 1.00107, 1.0044, 1.00306, 1.01974, 1.02235, 1.02757, 1.03292};
const float sf_e24e60_ICHEP2012_period2_LoosePP_eta[] = {1.01067, 0.94924, 0.95251, 0.9597, 0.92395, 0.9921, 0.98272, 0.96523, 0.99256, 0.99056, 0.98801, 0.993, 0.98498, 0.98035, 0.98269, 0.8941, 0.95713, 0.9592, 0.9482, 0.97946};
const float errsf_e24e60_ICHEP2012_period2_LoosePP_eta[] = {0.0239646, 0.022835, 0.0108853, 0.0116825, 0.0260554, 0.0104346, 0.0102633, 0.0102, 0.0100571, 0.0103686, 0.0104232, 0.0100867, 0.0101733, 0.0102243, 0.0103102, 0.019637, 0.0112666, 0.0108117, 0.022668, 0.0240816};

const float effMC_e24e60_ICHEP2012_period2_LoosePP_eta[] = {0.7921, 0.8477, 0.83655, 0.86018, 0.62884, 0.90368, 0.90543, 0.92214, 0.92735, 0.90334, 0.89544, 0.92707, 0.92795, 0.90669, 0.90255, 0.64108, 0.85829, 0.84054, 0.85257, 0.80755};
const float sf_e24e60_ICHEP2012_period2_LoosePP_pt[] = {0.958425, 0.957149, 0.974651, 0.973152, 0.981356, 0.989713, 0.996519, 0.999781, 1.00218, 1.00006, 1.00755, 0.994868, 1.00734, 0.98166, 0.98166};
const float errsf_e24e60_ICHEP2012_period2_LoosePP_pt[] = {0.0134004, 0.0128939, 0.00875126, 0.00872087, 0.0085183, 0.00520619, 0.00253219, 0.00165099, 0.00099262, 0.00112429, 0.00168138, 0.00215743, 0.00391983, 0.0117696, 0.02753};

const float effMC_e24e60_ICHEP2012_period2_LoosePP_pt[] = {0.748888, 0.887837, 0.911644, 0.925109, 0.944473, 0.956961, 0.972636, 0.989601, 1.00549, 1.01656, 1.01981, 1.05233, 1.06753, 1.07743, 1.08433};
const float sf_e24e60_ICHEP2012_period2_MediumPP_eta[] = {1.04099, 0.97285, 0.95806, 0.96808, 0.9167, 0.99056, 0.9865, 0.9698, 0.99678, 0.99079, 0.99258, 0.9975, 0.98976, 0.98251, 0.97871, 0.88038, 0.95949, 0.95845, 0.97277, 1.02476};
const float errsf_e24e60_ICHEP2012_period2_MediumPP_eta[] = {0.0239146, 0.0226014, 0.0106977, 0.0103712, 0.0197489, 0.0101554, 0.0100671, 0.0101194, 0.0100266, 0.01021, 0.0102285, 0.0100336, 0.0100867, 0.0100816, 0.0101385, 0.0145799, 0.0103686, 0.0106181, 0.0225745, 0.0242717};

const float effMC_e24e60_ICHEP2012_period2_MediumPP_eta[] = {0.8076, 0.88712, 0.89246, 0.90588, 0.69876, 0.95495, 0.9571, 0.96456, 0.96547, 0.95059, 0.94712, 0.96528, 0.96578, 0.95812, 0.95423, 0.71449, 0.90451, 0.89742, 0.8894, 0.82147};
const float sf_e24e60_ICHEP2012_period2_MediumPP_pt[] = {0.961688, 0.974066, 0.977863, 0.985284, 0.989484, 0.991574, 0.996108, 1.00044, 1.00039, 1.00054, 1.00186, 1.00646, 0.996744, 0.99735, 0.989363};
const float errsf_e24e60_ICHEP2012_period2_MediumPP_pt[] = {0.0105511, 0.00761297, 0.00589652, 0.00466471, 0.00495752, 0.00264536, 0.00159529, 0.000979387, 0.000797645, 0.000827936, 0.001252, 0.00165587, 0.002817, 0.00982416, 0.0189718};

const float effMC_e24e60_ICHEP2012_period2_MediumPP_pt[] = {0.776329, 0.917128, 0.936747, 0.952269, 0.963133, 0.970174, 0.981376, 0.993044, 1.00162, 1.00927, 1.01049, 1.03235, 1.04062, 1.04395, 1.05053};
const float sf_e24e60_ICHEP2012_period2_ML_eta[] = {1.01301, 0.949, 0.95785, 0.96029, 0.91495, 0.99354, 0.9847, 0.96624, 0.99212, 0.99346, 0.99288, 0.99238, 0.98686, 0.98199, 0.98436, 0.88724, 0.9564, 0.96193, 0.94818, 0.97897};
const float errsf_e24e60_ICHEP2012_period2_ML_eta[] = {0.0239396, 0.0227317, 0.0107852, 0.0118619, 0.0259723, 0.0104092, 0.010177, 0.0102, 0.0100592, 0.010325, 0.0103503, 0.0100841, 0.0101625, 0.0101864, 0.010277, 0.0192852, 0.0111272, 0.0107852, 0.0226914, 0.0239503};

const float effMC_e24e60_ICHEP2012_period2_ML_eta[] = {0.79662, 0.8557, 0.8461, 0.86804, 0.63168, 0.90824, 0.91111, 0.92792, 0.92944, 0.91506, 0.91183, 0.9289, 0.93265, 0.9124, 0.90492, 0.64566, 0.86635, 0.85033, 0.85925, 0.812};
const float sf_e24e60_ICHEP2012_period2_ML_pt[] = {0.940282, 0.959641, 0.959448, 0.975187, 0.973514, 0.983979, 0.992944, 0.998724, 1.00098, 1.00371, 1.00331, 1.00953, 0.997011, 1.00618, 0.970512};
const float errsf_e24e60_ICHEP2012_period2_ML_pt[] = {0.0122604, 0.00790996, 0.00739277, 0.00633811, 0.005395, 0.0034885, 0.00210932, 0.00118649, 0.000922829, 0.00104452, 0.00161242, 0.00208904, 0.00394484, 0.0122604, 0.0274212};

const float effMC_e24e60_ICHEP2012_period2_ML_pt[] = {0.744159, 0.882508, 0.906492, 0.922205, 0.940303, 0.955939, 0.971895, 0.990048, 1.00653, 1.01762, 1.02209, 1.04711, 1.06029, 1.0701, 1.07213};
const float sf_e24e60_ICHEP2012_period2_TightPP_eta[] = {1.04018, 0.97313, 0.95734, 0.96931, 0.91497, 0.98946, 0.98499, 0.96915, 0.99613, 0.99195, 0.99221, 0.9965, 0.98989, 0.98208, 0.97745, 0.88102, 0.95668, 0.96106, 0.97341, 1.01641};
const float errsf_e24e60_ICHEP2012_period2_TightPP_eta[] = {0.0236266, 0.0225316, 0.0104784, 0.0103819, 0.0186902, 0.0100961, 0.0100479, 0.0100907, 0.0100192, 0.010214, 0.010208, 0.0100186, 0.0100754, 0.0100648, 0.0100975, 0.014128, 0.0103053, 0.0104636, 0.0225148, 0.0239182};

const float effMC_e24e60_ICHEP2012_period2_TightPP_eta[] = {0.85848, 0.92638, 0.93376, 0.93998, 0.72304, 0.97935, 0.97497, 0.97901, 0.97981, 0.96592, 0.96259, 0.97967, 0.97999, 0.97579, 0.97835, 0.73878, 0.94078, 0.9381, 0.92849, 0.87291};
const float sf_e24e60_ICHEP2012_period2_TightPP_pt[] = {0.965203, 0.971656, 0.984391, 0.985999, 0.989367, 0.991481, 0.998359, 0.999401, 0.999825, 1.00087, 1.00157, 1.00671, 1.00068, 0.993049, 0.991724};
const float errsf_e24e60_ICHEP2012_period2_TightPP_pt[] = {0.0102461, 0.00620023, 0.00546187, 0.00408629, 0.00383342, 0.00232635, 0.00132501, 0.000799051, 0.000677676, 0.000718135, 0.00117329, 0.00123398, 0.00248818, 0.00947735, 0.0146965};

const float effMC_e24e60_ICHEP2012_period2_TightPP_pt[] = {0.788841, 0.934628, 0.949171, 0.965813, 0.974764, 0.979116, 0.987127, 0.997019, 1.00107, 1.0044, 1.00306, 1.01974, 1.02235, 1.02757, 1.03292};

 efficienciesRel172ICHEP_e24vhi_medium1_LoosePP.resize(3);
 uncertaintiesRel172ICHEP_e24vhi_medium1_LoosePP.resize(3);
 efficienciesRel172ICHEP_e24vhi_medium1_LoosePPET.resize(3);
 uncertaintiesRel172ICHEP_e24vhi_medium1_LoosePPET.resize(3);
 
 MCefficienciesRel172ICHEP_e24vhi_medium1_LoosePP.resize(3);
 MCefficienciesRel172ICHEP_e24vhi_medium1_LoosePPET.resize(3);
 
 efficienciesRel172ICHEP_e24vhi_medium1_MediumPP.resize(3);
 uncertaintiesRel172ICHEP_e24vhi_medium1_MediumPP.resize(3);
 efficienciesRel172ICHEP_e24vhi_medium1_MediumPPET.resize(3);
 uncertaintiesRel172ICHEP_e24vhi_medium1_MediumPPET.resize(3);
 
 MCefficienciesRel172ICHEP_e24vhi_medium1_MediumPP.resize(3);
 MCefficienciesRel172ICHEP_e24vhi_medium1_MediumPPET.resize(3);
 
 efficienciesRel172ICHEP_e24vhi_medium1_TightPP.resize(3);
 uncertaintiesRel172ICHEP_e24vhi_medium1_TightPP.resize(3);
 efficienciesRel172ICHEP_e24vhi_medium1_TightPPET.resize(3);
 uncertaintiesRel172ICHEP_e24vhi_medium1_TightPPET.resize(3);
 
 MCefficienciesRel172ICHEP_e24vhi_medium1_TightPP.resize(3);
 MCefficienciesRel172ICHEP_e24vhi_medium1_TightPPET.resize(3);

 efficienciesRel172ICHEP_e24vhi_medium1_ML.resize(3);
 uncertaintiesRel172ICHEP_e24vhi_medium1_ML.resize(3);
 efficienciesRel172ICHEP_e24vhi_medium1_MLET.resize(3);
 uncertaintiesRel172ICHEP_e24vhi_medium1_MLET.resize(3);
 
 MCefficienciesRel172ICHEP_e24vhi_medium1_ML.resize(3);
 MCefficienciesRel172ICHEP_e24vhi_medium1_MLET.resize(3);

  copyToVector(sf_e24e60_ICHEP2012_period0_LoosePP_eta, 20, efficienciesRel172ICHEP_e24vhi_medium1_LoosePP[0]);
  copyToVector(errsf_e24e60_ICHEP2012_period0_LoosePP_eta, 20, uncertaintiesRel172ICHEP_e24vhi_medium1_LoosePP[0]);
  copyToVector(sf_e24e60_ICHEP2012_period0_LoosePP_pt, 15, efficienciesRel172ICHEP_e24vhi_medium1_LoosePPET[0]);
  copyToVector(errsf_e24e60_ICHEP2012_period0_LoosePP_pt, 15, uncertaintiesRel172ICHEP_e24vhi_medium1_LoosePPET[0]);

  copyToVector(sf_e24e60_ICHEP2012_period0_MediumPP_eta, 20, efficienciesRel172ICHEP_e24vhi_medium1_MediumPP[0]);
  copyToVector(errsf_e24e60_ICHEP2012_period0_MediumPP_eta, 20, uncertaintiesRel172ICHEP_e24vhi_medium1_MediumPP[0]);
  copyToVector(sf_e24e60_ICHEP2012_period0_MediumPP_pt, 15, efficienciesRel172ICHEP_e24vhi_medium1_MediumPPET[0]);
  copyToVector(errsf_e24e60_ICHEP2012_period0_MediumPP_pt, 15, uncertaintiesRel172ICHEP_e24vhi_medium1_MediumPPET[0]);

  copyToVector(sf_e24e60_ICHEP2012_period0_TightPP_eta, 20, efficienciesRel172ICHEP_e24vhi_medium1_TightPP[0]);
  copyToVector(errsf_e24e60_ICHEP2012_period0_TightPP_eta, 20, uncertaintiesRel172ICHEP_e24vhi_medium1_TightPP[0]);
  copyToVector(sf_e24e60_ICHEP2012_period0_TightPP_pt, 15, efficienciesRel172ICHEP_e24vhi_medium1_TightPPET[0]);
  copyToVector(errsf_e24e60_ICHEP2012_period0_TightPP_pt, 15, uncertaintiesRel172ICHEP_e24vhi_medium1_TightPPET[0]);

  copyToVector(sf_e24e60_ICHEP2012_period0_ML_eta, 20, efficienciesRel172ICHEP_e24vhi_medium1_ML[0]);
  copyToVector(errsf_e24e60_ICHEP2012_period0_ML_eta, 20, uncertaintiesRel172ICHEP_e24vhi_medium1_ML[0]);
  copyToVector(sf_e24e60_ICHEP2012_period0_ML_pt, 15, efficienciesRel172ICHEP_e24vhi_medium1_MLET[0]);
  copyToVector(errsf_e24e60_ICHEP2012_period0_ML_pt, 15, uncertaintiesRel172ICHEP_e24vhi_medium1_MLET[0]);

  copyToVector(effMC_e24e60_ICHEP2012_period0_LoosePP_eta, 20, MCefficienciesRel172ICHEP_e24vhi_medium1_LoosePP[0]);
  copyToVector(effMC_e24e60_ICHEP2012_period0_LoosePP_pt, 15, MCefficienciesRel172ICHEP_e24vhi_medium1_LoosePPET[0]);
  copyToVector(effMC_e24e60_ICHEP2012_period0_MediumPP_eta, 20, MCefficienciesRel172ICHEP_e24vhi_medium1_MediumPP[0]);
  copyToVector(effMC_e24e60_ICHEP2012_period0_MediumPP_pt, 15, MCefficienciesRel172ICHEP_e24vhi_medium1_MediumPPET[0]);
  copyToVector(effMC_e24e60_ICHEP2012_period0_TightPP_eta, 20, MCefficienciesRel172ICHEP_e24vhi_medium1_TightPP[0]);
  copyToVector(effMC_e24e60_ICHEP2012_period0_TightPP_pt, 15, MCefficienciesRel172ICHEP_e24vhi_medium1_TightPPET[0]);
  copyToVector(effMC_e24e60_ICHEP2012_period0_ML_eta, 20, MCefficienciesRel172ICHEP_e24vhi_medium1_ML[0]);
  copyToVector(effMC_e24e60_ICHEP2012_period0_ML_pt, 15, MCefficienciesRel172ICHEP_e24vhi_medium1_MLET[0]);

  copyToVector(sf_e24e60_ICHEP2012_period1_LoosePP_eta, 20, efficienciesRel172ICHEP_e24vhi_medium1_LoosePP[1]);
  copyToVector(errsf_e24e60_ICHEP2012_period1_LoosePP_eta, 20, uncertaintiesRel172ICHEP_e24vhi_medium1_LoosePP[1]);
  copyToVector(sf_e24e60_ICHEP2012_period1_LoosePP_pt, 15, efficienciesRel172ICHEP_e24vhi_medium1_LoosePPET[1]);
  copyToVector(errsf_e24e60_ICHEP2012_period1_LoosePP_pt, 15, uncertaintiesRel172ICHEP_e24vhi_medium1_LoosePPET[1]);

  copyToVector(sf_e24e60_ICHEP2012_period1_MediumPP_eta, 20, efficienciesRel172ICHEP_e24vhi_medium1_MediumPP[1]);
  copyToVector(errsf_e24e60_ICHEP2012_period1_MediumPP_eta, 20, uncertaintiesRel172ICHEP_e24vhi_medium1_MediumPP[1]);
  copyToVector(sf_e24e60_ICHEP2012_period1_MediumPP_pt, 15, efficienciesRel172ICHEP_e24vhi_medium1_MediumPPET[1]);
  copyToVector(errsf_e24e60_ICHEP2012_period1_MediumPP_pt, 15, uncertaintiesRel172ICHEP_e24vhi_medium1_MediumPPET[1]);

  copyToVector(sf_e24e60_ICHEP2012_period1_TightPP_eta, 20, efficienciesRel172ICHEP_e24vhi_medium1_TightPP[1]);
  copyToVector(errsf_e24e60_ICHEP2012_period1_TightPP_eta, 20, uncertaintiesRel172ICHEP_e24vhi_medium1_TightPP[1]);
  copyToVector(sf_e24e60_ICHEP2012_period1_TightPP_pt, 15, efficienciesRel172ICHEP_e24vhi_medium1_TightPPET[1]);
  copyToVector(errsf_e24e60_ICHEP2012_period1_TightPP_pt, 15, uncertaintiesRel172ICHEP_e24vhi_medium1_TightPPET[1]);

  copyToVector(sf_e24e60_ICHEP2012_period1_ML_eta, 20, efficienciesRel172ICHEP_e24vhi_medium1_ML[1]);
  copyToVector(errsf_e24e60_ICHEP2012_period1_ML_eta, 20, uncertaintiesRel172ICHEP_e24vhi_medium1_ML[1]);
  copyToVector(sf_e24e60_ICHEP2012_period1_ML_pt, 15, efficienciesRel172ICHEP_e24vhi_medium1_MLET[1]);
  copyToVector(errsf_e24e60_ICHEP2012_period1_ML_pt, 15, uncertaintiesRel172ICHEP_e24vhi_medium1_MLET[1]);

  copyToVector(effMC_e24e60_ICHEP2012_period1_LoosePP_eta, 20, MCefficienciesRel172ICHEP_e24vhi_medium1_LoosePP[1]);
  copyToVector(effMC_e24e60_ICHEP2012_period1_LoosePP_pt, 15, MCefficienciesRel172ICHEP_e24vhi_medium1_LoosePPET[1]);
  copyToVector(effMC_e24e60_ICHEP2012_period1_MediumPP_eta, 20, MCefficienciesRel172ICHEP_e24vhi_medium1_MediumPP[1]);
  copyToVector(effMC_e24e60_ICHEP2012_period1_MediumPP_pt, 15, MCefficienciesRel172ICHEP_e24vhi_medium1_MediumPPET[1]);
  copyToVector(effMC_e24e60_ICHEP2012_period1_TightPP_eta, 20, MCefficienciesRel172ICHEP_e24vhi_medium1_TightPP[1]);
  copyToVector(effMC_e24e60_ICHEP2012_period1_TightPP_pt, 15, MCefficienciesRel172ICHEP_e24vhi_medium1_TightPPET[1]);
  copyToVector(effMC_e24e60_ICHEP2012_period1_ML_eta, 20, MCefficienciesRel172ICHEP_e24vhi_medium1_ML[1]);
  copyToVector(effMC_e24e60_ICHEP2012_period1_ML_pt, 15, MCefficienciesRel172ICHEP_e24vhi_medium1_MLET[1]);

  copyToVector(sf_e24e60_ICHEP2012_period2_LoosePP_eta, 20, efficienciesRel172ICHEP_e24vhi_medium1_LoosePP[2]);
  copyToVector(errsf_e24e60_ICHEP2012_period2_LoosePP_eta, 20, uncertaintiesRel172ICHEP_e24vhi_medium1_LoosePP[2]);
  copyToVector(sf_e24e60_ICHEP2012_period2_LoosePP_pt, 15, efficienciesRel172ICHEP_e24vhi_medium1_LoosePPET[2]);
  copyToVector(errsf_e24e60_ICHEP2012_period2_LoosePP_pt, 15, uncertaintiesRel172ICHEP_e24vhi_medium1_LoosePPET[2]);

  copyToVector(sf_e24e60_ICHEP2012_period2_MediumPP_eta, 20, efficienciesRel172ICHEP_e24vhi_medium1_MediumPP[2]);
  copyToVector(errsf_e24e60_ICHEP2012_period2_MediumPP_eta, 20, uncertaintiesRel172ICHEP_e24vhi_medium1_MediumPP[2]);
  copyToVector(sf_e24e60_ICHEP2012_period2_MediumPP_pt, 15, efficienciesRel172ICHEP_e24vhi_medium1_MediumPPET[2]);
  copyToVector(errsf_e24e60_ICHEP2012_period2_MediumPP_pt, 15, uncertaintiesRel172ICHEP_e24vhi_medium1_MediumPPET[2]);

  copyToVector(sf_e24e60_ICHEP2012_period2_TightPP_eta, 20, efficienciesRel172ICHEP_e24vhi_medium1_TightPP[2]);
  copyToVector(errsf_e24e60_ICHEP2012_period2_TightPP_eta, 20, uncertaintiesRel172ICHEP_e24vhi_medium1_TightPP[2]);
  copyToVector(sf_e24e60_ICHEP2012_period2_TightPP_pt, 15, efficienciesRel172ICHEP_e24vhi_medium1_TightPPET[2]);
  copyToVector(errsf_e24e60_ICHEP2012_period2_TightPP_pt, 15, uncertaintiesRel172ICHEP_e24vhi_medium1_TightPPET[2]);

  copyToVector(sf_e24e60_ICHEP2012_period2_ML_eta, 20, efficienciesRel172ICHEP_e24vhi_medium1_ML[2]);
  copyToVector(errsf_e24e60_ICHEP2012_period2_ML_eta, 20, uncertaintiesRel172ICHEP_e24vhi_medium1_ML[2]);
  copyToVector(sf_e24e60_ICHEP2012_period2_ML_pt, 15, efficienciesRel172ICHEP_e24vhi_medium1_MLET[2]);
  copyToVector(errsf_e24e60_ICHEP2012_period2_ML_pt, 15, uncertaintiesRel172ICHEP_e24vhi_medium1_MLET[2]);

  copyToVector(effMC_e24e60_ICHEP2012_period2_LoosePP_eta, 20, MCefficienciesRel172ICHEP_e24vhi_medium1_LoosePP[2]);
  copyToVector(effMC_e24e60_ICHEP2012_period2_LoosePP_pt, 15, MCefficienciesRel172ICHEP_e24vhi_medium1_LoosePPET[2]);
  copyToVector(effMC_e24e60_ICHEP2012_period2_MediumPP_eta, 20, MCefficienciesRel172ICHEP_e24vhi_medium1_MediumPP[2]);
  copyToVector(effMC_e24e60_ICHEP2012_period2_MediumPP_pt, 15, MCefficienciesRel172ICHEP_e24vhi_medium1_MediumPPET[2]);
  copyToVector(effMC_e24e60_ICHEP2012_period2_TightPP_eta, 20, MCefficienciesRel172ICHEP_e24vhi_medium1_TightPP[2]);
  copyToVector(effMC_e24e60_ICHEP2012_period2_TightPP_pt, 15, MCefficienciesRel172ICHEP_e24vhi_medium1_TightPPET[2]);
  copyToVector(effMC_e24e60_ICHEP2012_period2_ML_eta, 20, MCefficienciesRel172ICHEP_e24vhi_medium1_ML[2]);
  copyToVector(effMC_e24e60_ICHEP2012_period2_ML_pt, 15, MCefficienciesRel172ICHEP_e24vhi_medium1_MLET[2]);

  // electron trigger e12Tvh_loose1 vs. different offline and 3 data periods, plus MC efficiencies!
const float sf_e12l_ICHEP2012_period0_LoosePP_eta[] = {0.9984, 0.9967, 0.983, 1.0041, 1.0059, 1.0027, 1.0016, 0.9811, 1.0004, 1.0032, 0.9993, 1.0021, 0.9988, 1.0033, 1.0015, 0.9974, 1.004, 0.9815, 0.9969, 0.9763};
const float errsf_e12l_ICHEP2012_period0_LoosePP_eta[] = {0.0130599, 0.010198, 0.0104403, 0.0102181, 0.0113177, 0.0100975, 0.0100404, 0.0101272, 0.0100499, 0.0100975, 0.0101435, 0.0100319, 0.0100975, 0.0100404, 0.0100975, 0.0112254, 0.010198, 0.0108462, 0.0101789, 0.0132548};

const float effMC_e12l_ICHEP2012_period0_LoosePP_eta[] = {0.8088, 0.9192, 0.9197, 0.9288, 0.8578, 0.9605, 0.9706, 0.9745, 0.976, 0.9752, 0.9752, 0.9755, 0.9745, 0.9708, 0.9593, 0.8663, 0.9285, 0.9171, 0.9206, 0.8199};
const float sf_e12l_ICHEP2012_period0_LoosePP_pt[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
const float errsf_e12l_ICHEP2012_period0_LoosePP_pt[] = {0.0368628, 0.021581, 0.00450446, 0.00360357, 0.00210208, 0.00110109, 0.000800793, 0.000700693, 0.000700693, 0.00110109, 0.00140139, 0.00290287, 0.00500495, 0.0114113};

const float effMC_e12l_ICHEP2012_period0_LoosePP_pt[] = {0.812124, 0.893399, 0.933672, 0.96229, 0.976963, 0.988723, 0.995903, 1.00308, 1.00933, 1.01235, 1.01453, 1.0189, 1.02057, 1.02431};
const float sf_e12l_ICHEP2012_period0_MediumPP_eta[] = {1.0404, 0.997, 0.9836, 1.0002, 1.009, 1.0018, 1.0007, 0.9806, 0.9997, 1.0019, 0.9994, 1.0019, 0.999, 1.0019, 1.0009, 1.0005, 1.0039, 0.9801, 0.999, 1.0245};
const float errsf_e12l_ICHEP2012_period0_MediumPP_eta[] = {0.0129958, 0.0101789, 0.0103846, 0.0101607, 0.0113177, 0.0100717, 0.0100319, 0.0101119, 0.0100319, 0.0100841, 0.0100975, 0.010018, 0.0100499, 0.0100319, 0.0100841, 0.0108853, 0.0102181, 0.0106283, 0.0101789, 0.0130599};

const float effMC_e12l_ICHEP2012_period0_MediumPP_eta[] = {0.819, 0.9288, 0.9362, 0.9444, 0.8764, 0.9708, 0.9786, 0.9809, 0.9816, 0.9799, 0.9808, 0.9811, 0.9808, 0.9786, 0.9697, 0.8838, 0.943, 0.9333, 0.9299, 0.8288};
const float sf_e12l_ICHEP2012_period0_MediumPP_pt[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
const float errsf_e12l_ICHEP2012_period0_MediumPP_pt[] = {0.0341942, 0.0212919, 0.00400208, 0.00210109, 0.00130068, 0.000900469, 0.000700364, 0.000700364, 0.000600312, 0.000900469, 0.00140073, 0.00260135, 0.0048025, 0.00990516};

const float effMC_e12l_ICHEP2012_period0_MediumPP_pt[] = {0.828911, 0.906125, 0.944216, 0.968887, 0.981274, 0.990668, 0.996552, 1.00233, 1.00749, 1.01007, 1.01142, 1.0141, 1.01565, 1.0172};
const float sf_e12l_ICHEP2012_period0_ML_eta[] = {1.0033, 0.9969, 0.9841, 1.0022, 1.001, 1.0029, 1.0009, 0.9812, 1.0001, 1.0024, 1, 1.0022, 0.9996, 1.0028, 1.0015, 0.9971, 1.0038, 0.9837, 0.998, 0.9779};
const float errsf_e12l_ICHEP2012_period0_ML_eta[] = {0.0128062, 0.0101789, 0.0103581, 0.0101789, 0.0115104, 0.0100841, 0.0100319, 0.0101272, 0.0100319, 0.0100841, 0.0100975, 0.010018, 0.0100499, 0.0100404, 0.0100975, 0.0110923, 0.0101789, 0.0106283, 0.0101789, 0.0129958};

const float effMC_e12l_ICHEP2012_period0_ML_eta[] = {0.8321, 0.9264, 0.9292, 0.9373, 0.8664, 0.966, 0.9772, 0.9797, 0.9804, 0.9796, 0.9802, 0.9798, 0.9794, 0.9767, 0.9652, 0.8741, 0.936, 0.9265, 0.9274, 0.8409};
const float sf_e12l_ICHEP2012_period0_ML_pt[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
const float errsf_e12l_ICHEP2012_period0_ML_pt[] = {0.0337282, 0.0213978, 0.00450407, 0.00240217, 0.00130118, 0.000900814, 0.000700633, 0.000600543, 0.000700633, 0.000900814, 0.00140127, 0.00270244, 0.00480434, 0.0114103};

const float effMC_e12l_ICHEP2012_period0_ML_pt[] = {0.818684, 0.901018, 0.939806, 0.966389, 0.979732, 0.990179, 0.996281, 1.00259, 1.00807, 1.01056, 1.01211, 1.01531, 1.01769, 1.01811};
const float sf_e12l_ICHEP2012_period0_TightPP_eta[] = {1.0324, 0.9976, 0.9864, 0.9995, 1.0017, 0.9989, 0.999, 0.9807, 0.9979, 0.9994, 0.9994, 0.9997, 0.9972, 0.9995, 0.9964, 0.9976, 1.0008, 0.9812, 0.996, 1.0188};
const float errsf_e12l_ICHEP2012_period0_TightPP_eta[] = {0.0124403, 0.0100975, 0.010198, 0.0100975, 0.0110073, 0.0100319, 0.0100125, 0.0100717, 0.010008, 0.0100404, 0.0100404, 0.010008, 0.0100245, 0.0100125, 0.0100404, 0.0106977, 0.0100841, 0.0103581, 0.0100975, 0.0125603};

const float effMC_e12l_ICHEP2012_period0_TightPP_eta[] = {0.8718, 0.9641, 0.9732, 0.9732, 0.903, 0.9906, 0.9935, 0.9939, 0.9939, 0.9934, 0.9935, 0.9937, 0.9941, 0.9935, 0.9904, 0.91, 0.9734, 0.973, 0.9667, 0.8778};
const float sf_e12l_ICHEP2012_period0_TightPP_pt[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
const float errsf_e12l_ICHEP2012_period0_TightPP_pt[] = {0.0346011, 0.0209138, 0.00310729, 0.00150353, 0.000902117, 0.000601411, 0.000501176, 0.000400941, 0.000501176, 0.000701646, 0.00100235, 0.00230541, 0.00431011, 0.00831952};

const float effMC_e12l_ICHEP2012_period0_TightPP_pt[] = {0.862382, 0.933784, 0.966699, 0.984828, 0.992221, 0.996171, 0.999108, 1.00123, 1.00296, 1.00316, 1.00417, 1.00225, 1.00326, 0.999513};
const float sf_e12l_ICHEP2012_period1_LoosePP_eta[] = {0.9984, 0.9967, 0.983, 1.0041, 1.0059, 1.0027, 1.0016, 0.9811, 1.0004, 1.0032, 0.9993, 1.0021, 0.9988, 1.0033, 1.0015, 0.9974, 1.004, 0.9815, 0.9969, 0.9763};
const float errsf_e12l_ICHEP2012_period1_LoosePP_eta[] = {0.0130599, 0.010198, 0.0104403, 0.0102181, 0.0113177, 0.0100975, 0.0100404, 0.0101272, 0.0100499, 0.0100975, 0.0101435, 0.0100319, 0.0100975, 0.0100404, 0.0100975, 0.0112254, 0.010198, 0.0108462, 0.0101789, 0.0132548};

const float effMC_e12l_ICHEP2012_period1_LoosePP_eta[] = {0.8088, 0.9192, 0.9197, 0.9288, 0.8578, 0.9605, 0.9706, 0.9745, 0.976, 0.9752, 0.9752, 0.9755, 0.9745, 0.9708, 0.9593, 0.8663, 0.9285, 0.9171, 0.9206, 0.8199};
const float sf_e12l_ICHEP2012_period1_LoosePP_pt[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
const float errsf_e12l_ICHEP2012_period1_LoosePP_pt[] = {0.0368628, 0.021581, 0.00450446, 0.00360357, 0.00210208, 0.00110109, 0.000800793, 0.000700693, 0.000700693, 0.00110109, 0.00140139, 0.00290287, 0.00500495, 0.0114113};

const float effMC_e12l_ICHEP2012_period1_LoosePP_pt[] = {0.812124, 0.893399, 0.933672, 0.96229, 0.976963, 0.988723, 0.995903, 1.00308, 1.00933, 1.01235, 1.01453, 1.0189, 1.02057, 1.02431};
const float sf_e12l_ICHEP2012_period1_MediumPP_eta[] = {1.0404, 0.997, 0.9836, 1.0002, 1.009, 1.0018, 1.0007, 0.9806, 0.9997, 1.0019, 0.9994, 1.0019, 0.999, 1.0019, 1.0009, 1.0005, 1.0039, 0.9801, 0.999, 1.0245};
const float errsf_e12l_ICHEP2012_period1_MediumPP_eta[] = {0.0129958, 0.0101789, 0.0103846, 0.0101607, 0.0113177, 0.0100717, 0.0100319, 0.0101119, 0.0100319, 0.0100841, 0.0100975, 0.010018, 0.0100499, 0.0100319, 0.0100841, 0.0108853, 0.0102181, 0.0106283, 0.0101789, 0.0130599};

const float effMC_e12l_ICHEP2012_period1_MediumPP_eta[] = {0.819, 0.9288, 0.9362, 0.9444, 0.8764, 0.9708, 0.9786, 0.9809, 0.9816, 0.9799, 0.9808, 0.9811, 0.9808, 0.9786, 0.9697, 0.8838, 0.943, 0.9333, 0.9299, 0.8288};
const float sf_e12l_ICHEP2012_period1_MediumPP_pt[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
const float errsf_e12l_ICHEP2012_period1_MediumPP_pt[] = {0.0341942, 0.0212919, 0.00400208, 0.00210109, 0.00130068, 0.000900469, 0.000700364, 0.000700364, 0.000600312, 0.000900469, 0.00140073, 0.00260135, 0.0048025, 0.00990516};

const float effMC_e12l_ICHEP2012_period1_MediumPP_pt[] = {0.828911, 0.906125, 0.944216, 0.968887, 0.981274, 0.990668, 0.996552, 1.00233, 1.00749, 1.01007, 1.01142, 1.0141, 1.01565, 1.0172};
const float sf_e12l_ICHEP2012_period1_ML_eta[] = {1.0033, 0.9969, 0.9841, 1.0022, 1.001, 1.0029, 1.0009, 0.9812, 1.0001, 1.0024, 1, 1.0022, 0.9996, 1.0028, 1.0015, 0.9971, 1.0038, 0.9837, 0.998, 0.9779};
const float errsf_e12l_ICHEP2012_period1_ML_eta[] = {0.0128062, 0.0101789, 0.0103581, 0.0101789, 0.0115104, 0.0100841, 0.0100319, 0.0101272, 0.0100319, 0.0100841, 0.0100975, 0.010018, 0.0100499, 0.0100404, 0.0100975, 0.0110923, 0.0101789, 0.0106283, 0.0101789, 0.0129958};

const float effMC_e12l_ICHEP2012_period1_ML_eta[] = {0.8321, 0.9264, 0.9292, 0.9373, 0.8664, 0.966, 0.9772, 0.9797, 0.9804, 0.9796, 0.9802, 0.9798, 0.9794, 0.9767, 0.9652, 0.8741, 0.936, 0.9265, 0.9274, 0.8409};
const float sf_e12l_ICHEP2012_period1_ML_pt[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
const float errsf_e12l_ICHEP2012_period1_ML_pt[] = {0.0337282, 0.0213978, 0.00450407, 0.00240217, 0.00130118, 0.000900814, 0.000700633, 0.000600543, 0.000700633, 0.000900814, 0.00140127, 0.00270244, 0.00480434, 0.0114103};

const float effMC_e12l_ICHEP2012_period1_ML_pt[] = {0.818684, 0.901018, 0.939806, 0.966389, 0.979732, 0.990179, 0.996281, 1.00259, 1.00807, 1.01056, 1.01211, 1.01531, 1.01769, 1.01811};
const float sf_e12l_ICHEP2012_period1_TightPP_eta[] = {1.0324, 0.9976, 0.9864, 0.9995, 1.0017, 0.9989, 0.999, 0.9807, 0.9979, 0.9994, 0.9994, 0.9997, 0.9972, 0.9995, 0.9964, 0.9976, 1.0008, 0.9812, 0.996, 1.0188};
const float errsf_e12l_ICHEP2012_period1_TightPP_eta[] = {0.0124403, 0.0100975, 0.010198, 0.0100975, 0.0110073, 0.0100319, 0.0100125, 0.0100717, 0.010008, 0.0100404, 0.0100404, 0.010008, 0.0100245, 0.0100125, 0.0100404, 0.0106977, 0.0100841, 0.0103581, 0.0100975, 0.0125603};

const float effMC_e12l_ICHEP2012_period1_TightPP_eta[] = {0.8718, 0.9641, 0.9732, 0.9732, 0.903, 0.9906, 0.9935, 0.9939, 0.9939, 0.9934, 0.9935, 0.9937, 0.9941, 0.9935, 0.9904, 0.91, 0.9734, 0.973, 0.9667, 0.8778};
const float sf_e12l_ICHEP2012_period1_TightPP_pt[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
const float errsf_e12l_ICHEP2012_period1_TightPP_pt[] = {0.0346011, 0.0209138, 0.00310729, 0.00150353, 0.000902117, 0.000601411, 0.000501176, 0.000400941, 0.000501176, 0.000701646, 0.00100235, 0.00230541, 0.00431011, 0.00831952};

const float effMC_e12l_ICHEP2012_period1_TightPP_pt[] = {0.862382, 0.933784, 0.966699, 0.984828, 0.992221, 0.996171, 0.999108, 1.00123, 1.00296, 1.00316, 1.00417, 1.00225, 1.00326, 0.999513};
const float sf_e12l_ICHEP2012_period2_LoosePP_eta[] = {0.9984, 0.9967, 0.983, 1.0041, 1.0059, 1.0027, 1.0016, 0.9811, 1.0004, 1.0032, 0.9993, 1.0021, 0.9988, 1.0033, 1.0015, 0.9974, 1.004, 0.9815, 0.9969, 0.9763};
const float errsf_e12l_ICHEP2012_period2_LoosePP_eta[] = {0.0130599, 0.010198, 0.0104403, 0.0102181, 0.0113177, 0.0100975, 0.0100404, 0.0101272, 0.0100499, 0.0100975, 0.0101435, 0.0100319, 0.0100975, 0.0100404, 0.0100975, 0.0112254, 0.010198, 0.0108462, 0.0101789, 0.0132548};

const float effMC_e12l_ICHEP2012_period2_LoosePP_eta[] = {0.8088, 0.9192, 0.9197, 0.9288, 0.8578, 0.9605, 0.9706, 0.9745, 0.976, 0.9752, 0.9752, 0.9755, 0.9745, 0.9708, 0.9593, 0.8663, 0.9285, 0.9171, 0.9206, 0.8199};
const float sf_e12l_ICHEP2012_period2_LoosePP_pt[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
const float errsf_e12l_ICHEP2012_period2_LoosePP_pt[] = {0.0368628, 0.021581, 0.00450446, 0.00360357, 0.00210208, 0.00110109, 0.000800793, 0.000700693, 0.000700693, 0.00110109, 0.00140139, 0.00290287, 0.00500495, 0.0114113};

const float effMC_e12l_ICHEP2012_period2_LoosePP_pt[] = {0.812124, 0.893399, 0.933672, 0.96229, 0.976963, 0.988723, 0.995903, 1.00308, 1.00933, 1.01235, 1.01453, 1.0189, 1.02057, 1.02431};
const float sf_e12l_ICHEP2012_period2_MediumPP_eta[] = {1.0404, 0.997, 0.9836, 1.0002, 1.009, 1.0018, 1.0007, 0.9806, 0.9997, 1.0019, 0.9994, 1.0019, 0.999, 1.0019, 1.0009, 1.0005, 1.0039, 0.9801, 0.999, 1.0245};
const float errsf_e12l_ICHEP2012_period2_MediumPP_eta[] = {0.0129958, 0.0101789, 0.0103846, 0.0101607, 0.0113177, 0.0100717, 0.0100319, 0.0101119, 0.0100319, 0.0100841, 0.0100975, 0.010018, 0.0100499, 0.0100319, 0.0100841, 0.0108853, 0.0102181, 0.0106283, 0.0101789, 0.0130599};

const float effMC_e12l_ICHEP2012_period2_MediumPP_eta[] = {0.819, 0.9288, 0.9362, 0.9444, 0.8764, 0.9708, 0.9786, 0.9809, 0.9816, 0.9799, 0.9808, 0.9811, 0.9808, 0.9786, 0.9697, 0.8838, 0.943, 0.9333, 0.9299, 0.8288};
const float sf_e12l_ICHEP2012_period2_MediumPP_pt[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
const float errsf_e12l_ICHEP2012_period2_MediumPP_pt[] = {0.0341942, 0.0212919, 0.00400208, 0.00210109, 0.00130068, 0.000900469, 0.000700364, 0.000700364, 0.000600312, 0.000900469, 0.00140073, 0.00260135, 0.0048025, 0.00990516};

const float effMC_e12l_ICHEP2012_period2_MediumPP_pt[] = {0.828911, 0.906125, 0.944216, 0.968887, 0.981274, 0.990668, 0.996552, 1.00233, 1.00749, 1.01007, 1.01142, 1.0141, 1.01565, 1.0172};
const float sf_e12l_ICHEP2012_period2_ML_eta[] = {1.0033, 0.9969, 0.9841, 1.0022, 1.001, 1.0029, 1.0009, 0.9812, 1.0001, 1.0024, 1, 1.0022, 0.9996, 1.0028, 1.0015, 0.9971, 1.0038, 0.9837, 0.998, 0.9779};
const float errsf_e12l_ICHEP2012_period2_ML_eta[] = {0.0128062, 0.0101789, 0.0103581, 0.0101789, 0.0115104, 0.0100841, 0.0100319, 0.0101272, 0.0100319, 0.0100841, 0.0100975, 0.010018, 0.0100499, 0.0100404, 0.0100975, 0.0110923, 0.0101789, 0.0106283, 0.0101789, 0.0129958};

const float effMC_e12l_ICHEP2012_period2_ML_eta[] = {0.8321, 0.9264, 0.9292, 0.9373, 0.8664, 0.966, 0.9772, 0.9797, 0.9804, 0.9796, 0.9802, 0.9798, 0.9794, 0.9767, 0.9652, 0.8741, 0.936, 0.9265, 0.9274, 0.8409};
const float sf_e12l_ICHEP2012_period2_ML_pt[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
const float errsf_e12l_ICHEP2012_period2_ML_pt[] = {0.0337282, 0.0213978, 0.00450407, 0.00240217, 0.00130118, 0.000900814, 0.000700633, 0.000600543, 0.000700633, 0.000900814, 0.00140127, 0.00270244, 0.00480434, 0.0114103};

const float effMC_e12l_ICHEP2012_period2_ML_pt[] = {0.818684, 0.901018, 0.939806, 0.966389, 0.979732, 0.990179, 0.996281, 1.00259, 1.00807, 1.01056, 1.01211, 1.01531, 1.01769, 1.01811};
const float sf_e12l_ICHEP2012_period2_TightPP_eta[] = {1.0324, 0.9976, 0.9864, 0.9995, 1.0017, 0.9989, 0.999, 0.9807, 0.9979, 0.9994, 0.9994, 0.9997, 0.9972, 0.9995, 0.9964, 0.9976, 1.0008, 0.9812, 0.996, 1.0188};
const float errsf_e12l_ICHEP2012_period2_TightPP_eta[] = {0.0124403, 0.0100975, 0.010198, 0.0100975, 0.0110073, 0.0100319, 0.0100125, 0.0100717, 0.010008, 0.0100404, 0.0100404, 0.010008, 0.0100245, 0.0100125, 0.0100404, 0.0106977, 0.0100841, 0.0103581, 0.0100975, 0.0125603};

const float effMC_e12l_ICHEP2012_period2_TightPP_eta[] = {0.8718, 0.9641, 0.9732, 0.9732, 0.903, 0.9906, 0.9935, 0.9939, 0.9939, 0.9934, 0.9935, 0.9937, 0.9941, 0.9935, 0.9904, 0.91, 0.9734, 0.973, 0.9667, 0.8778};
const float sf_e12l_ICHEP2012_period2_TightPP_pt[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
const float errsf_e12l_ICHEP2012_period2_TightPP_pt[] = {0.0346011, 0.0209138, 0.00310729, 0.00150353, 0.000902117, 0.000601411, 0.000501176, 0.000400941, 0.000501176, 0.000701646, 0.00100235, 0.00230541, 0.00431011, 0.00831952};

const float effMC_e12l_ICHEP2012_period2_TightPP_pt[] = {0.862382, 0.933784, 0.966699, 0.984828, 0.992221, 0.996171, 0.999108, 1.00123, 1.00296, 1.00316, 1.00417, 1.00225, 1.00326, 0.999513};

 efficienciesRel172ICHEP_e12Tvh_loose1_LoosePP.resize(3);
 uncertaintiesRel172ICHEP_e12Tvh_loose1_LoosePP.resize(3);
 efficienciesRel172ICHEP_e12Tvh_loose1_LoosePPET.resize(3);
 uncertaintiesRel172ICHEP_e12Tvh_loose1_LoosePPET.resize(3);
 
 MCefficienciesRel172ICHEP_e12Tvh_loose1_LoosePP.resize(3);
 MCefficienciesRel172ICHEP_e12Tvh_loose1_LoosePPET.resize(3);
 
 efficienciesRel172ICHEP_e12Tvh_loose1_MediumPP.resize(3);
 uncertaintiesRel172ICHEP_e12Tvh_loose1_MediumPP.resize(3);
 efficienciesRel172ICHEP_e12Tvh_loose1_MediumPPET.resize(3);
 uncertaintiesRel172ICHEP_e12Tvh_loose1_MediumPPET.resize(3);
 
 MCefficienciesRel172ICHEP_e12Tvh_loose1_MediumPP.resize(3);
 MCefficienciesRel172ICHEP_e12Tvh_loose1_MediumPPET.resize(3);
 
 efficienciesRel172ICHEP_e12Tvh_loose1_TightPP.resize(3);
 uncertaintiesRel172ICHEP_e12Tvh_loose1_TightPP.resize(3);
 efficienciesRel172ICHEP_e12Tvh_loose1_TightPPET.resize(3);
 uncertaintiesRel172ICHEP_e12Tvh_loose1_TightPPET.resize(3);
 
 MCefficienciesRel172ICHEP_e12Tvh_loose1_TightPP.resize(3);
 MCefficienciesRel172ICHEP_e12Tvh_loose1_TightPPET.resize(3);

 efficienciesRel172ICHEP_e12Tvh_loose1_ML.resize(3);
 uncertaintiesRel172ICHEP_e12Tvh_loose1_ML.resize(3);
 efficienciesRel172ICHEP_e12Tvh_loose1_MLET.resize(3);
 uncertaintiesRel172ICHEP_e12Tvh_loose1_MLET.resize(3);
 
 MCefficienciesRel172ICHEP_e12Tvh_loose1_ML.resize(3);
 MCefficienciesRel172ICHEP_e12Tvh_loose1_MLET.resize(3);

  copyToVector(sf_e12l_ICHEP2012_period0_LoosePP_eta, 20, efficienciesRel172ICHEP_e12Tvh_loose1_LoosePP[0]);
  copyToVector(errsf_e12l_ICHEP2012_period0_LoosePP_eta, 20, uncertaintiesRel172ICHEP_e12Tvh_loose1_LoosePP[0]);
  copyToVector(sf_e12l_ICHEP2012_period0_LoosePP_pt, 14, efficienciesRel172ICHEP_e12Tvh_loose1_LoosePPET[0]);
  copyToVector(errsf_e12l_ICHEP2012_period0_LoosePP_pt, 14, uncertaintiesRel172ICHEP_e12Tvh_loose1_LoosePPET[0]);

  copyToVector(sf_e12l_ICHEP2012_period0_MediumPP_eta, 20, efficienciesRel172ICHEP_e12Tvh_loose1_MediumPP[0]);
  copyToVector(errsf_e12l_ICHEP2012_period0_MediumPP_eta, 20, uncertaintiesRel172ICHEP_e12Tvh_loose1_MediumPP[0]);
  copyToVector(sf_e12l_ICHEP2012_period0_MediumPP_pt, 14, efficienciesRel172ICHEP_e12Tvh_loose1_MediumPPET[0]);
  copyToVector(errsf_e12l_ICHEP2012_period0_MediumPP_pt, 14, uncertaintiesRel172ICHEP_e12Tvh_loose1_MediumPPET[0]);

  copyToVector(sf_e12l_ICHEP2012_period0_TightPP_eta, 20, efficienciesRel172ICHEP_e12Tvh_loose1_TightPP[0]);
  copyToVector(errsf_e12l_ICHEP2012_period0_TightPP_eta, 20, uncertaintiesRel172ICHEP_e12Tvh_loose1_TightPP[0]);
  copyToVector(sf_e12l_ICHEP2012_period0_TightPP_pt, 14, efficienciesRel172ICHEP_e12Tvh_loose1_TightPPET[0]);
  copyToVector(errsf_e12l_ICHEP2012_period0_TightPP_pt, 14, uncertaintiesRel172ICHEP_e12Tvh_loose1_TightPPET[0]);

  copyToVector(sf_e12l_ICHEP2012_period0_ML_eta, 20, efficienciesRel172ICHEP_e12Tvh_loose1_ML[0]);
  copyToVector(errsf_e12l_ICHEP2012_period0_ML_eta, 20, uncertaintiesRel172ICHEP_e12Tvh_loose1_ML[0]);
  copyToVector(sf_e12l_ICHEP2012_period0_ML_pt, 14, efficienciesRel172ICHEP_e12Tvh_loose1_MLET[0]);
  copyToVector(errsf_e12l_ICHEP2012_period0_ML_pt, 14, uncertaintiesRel172ICHEP_e12Tvh_loose1_MLET[0]);

  copyToVector(effMC_e12l_ICHEP2012_period0_LoosePP_eta, 20, MCefficienciesRel172ICHEP_e12Tvh_loose1_LoosePP[0]);
  copyToVector(effMC_e12l_ICHEP2012_period0_LoosePP_pt, 14, MCefficienciesRel172ICHEP_e12Tvh_loose1_LoosePPET[0]);
  copyToVector(effMC_e12l_ICHEP2012_period0_MediumPP_eta, 20, MCefficienciesRel172ICHEP_e12Tvh_loose1_MediumPP[0]);
  copyToVector(effMC_e12l_ICHEP2012_period0_MediumPP_pt, 14, MCefficienciesRel172ICHEP_e12Tvh_loose1_MediumPPET[0]);
  copyToVector(effMC_e12l_ICHEP2012_period0_TightPP_eta, 20, MCefficienciesRel172ICHEP_e12Tvh_loose1_TightPP[0]);
  copyToVector(effMC_e12l_ICHEP2012_period0_TightPP_pt, 14, MCefficienciesRel172ICHEP_e12Tvh_loose1_TightPPET[0]);
  copyToVector(effMC_e12l_ICHEP2012_period0_ML_eta, 20, MCefficienciesRel172ICHEP_e12Tvh_loose1_ML[0]);
  copyToVector(effMC_e12l_ICHEP2012_period0_ML_pt, 14, MCefficienciesRel172ICHEP_e12Tvh_loose1_MLET[0]);

  copyToVector(sf_e12l_ICHEP2012_period1_LoosePP_eta, 20, efficienciesRel172ICHEP_e12Tvh_loose1_LoosePP[1]);
  copyToVector(errsf_e12l_ICHEP2012_period1_LoosePP_eta, 20, uncertaintiesRel172ICHEP_e12Tvh_loose1_LoosePP[1]);
  copyToVector(sf_e12l_ICHEP2012_period1_LoosePP_pt, 14, efficienciesRel172ICHEP_e12Tvh_loose1_LoosePPET[1]);
  copyToVector(errsf_e12l_ICHEP2012_period1_LoosePP_pt, 14, uncertaintiesRel172ICHEP_e12Tvh_loose1_LoosePPET[1]);

  copyToVector(sf_e12l_ICHEP2012_period1_MediumPP_eta, 20, efficienciesRel172ICHEP_e12Tvh_loose1_MediumPP[1]);
  copyToVector(errsf_e12l_ICHEP2012_period1_MediumPP_eta, 20, uncertaintiesRel172ICHEP_e12Tvh_loose1_MediumPP[1]);
  copyToVector(sf_e12l_ICHEP2012_period1_MediumPP_pt, 14, efficienciesRel172ICHEP_e12Tvh_loose1_MediumPPET[1]);
  copyToVector(errsf_e12l_ICHEP2012_period1_MediumPP_pt, 14, uncertaintiesRel172ICHEP_e12Tvh_loose1_MediumPPET[1]);

  copyToVector(sf_e12l_ICHEP2012_period1_TightPP_eta, 20, efficienciesRel172ICHEP_e12Tvh_loose1_TightPP[1]);
  copyToVector(errsf_e12l_ICHEP2012_period1_TightPP_eta, 20, uncertaintiesRel172ICHEP_e12Tvh_loose1_TightPP[1]);
  copyToVector(sf_e12l_ICHEP2012_period1_TightPP_pt, 14, efficienciesRel172ICHEP_e12Tvh_loose1_TightPPET[1]);
  copyToVector(errsf_e12l_ICHEP2012_period1_TightPP_pt, 14, uncertaintiesRel172ICHEP_e12Tvh_loose1_TightPPET[1]);

  copyToVector(sf_e12l_ICHEP2012_period1_ML_eta, 20, efficienciesRel172ICHEP_e12Tvh_loose1_ML[1]);
  copyToVector(errsf_e12l_ICHEP2012_period1_ML_eta, 20, uncertaintiesRel172ICHEP_e12Tvh_loose1_ML[1]);
  copyToVector(sf_e12l_ICHEP2012_period1_ML_pt, 14, efficienciesRel172ICHEP_e12Tvh_loose1_MLET[1]);
  copyToVector(errsf_e12l_ICHEP2012_period1_ML_pt, 14, uncertaintiesRel172ICHEP_e12Tvh_loose1_MLET[1]);

  copyToVector(effMC_e12l_ICHEP2012_period1_LoosePP_eta, 20, MCefficienciesRel172ICHEP_e12Tvh_loose1_LoosePP[1]);
  copyToVector(effMC_e12l_ICHEP2012_period1_LoosePP_pt, 14, MCefficienciesRel172ICHEP_e12Tvh_loose1_LoosePPET[1]);
  copyToVector(effMC_e12l_ICHEP2012_period1_MediumPP_eta, 20, MCefficienciesRel172ICHEP_e12Tvh_loose1_MediumPP[1]);
  copyToVector(effMC_e12l_ICHEP2012_period1_MediumPP_pt, 14, MCefficienciesRel172ICHEP_e12Tvh_loose1_MediumPPET[1]);
  copyToVector(effMC_e12l_ICHEP2012_period1_TightPP_eta, 20, MCefficienciesRel172ICHEP_e12Tvh_loose1_TightPP[1]);
  copyToVector(effMC_e12l_ICHEP2012_period1_TightPP_pt, 14, MCefficienciesRel172ICHEP_e12Tvh_loose1_TightPPET[1]);
  copyToVector(effMC_e12l_ICHEP2012_period1_ML_eta, 20, MCefficienciesRel172ICHEP_e12Tvh_loose1_ML[1]);
  copyToVector(effMC_e12l_ICHEP2012_period1_ML_pt, 14, MCefficienciesRel172ICHEP_e12Tvh_loose1_MLET[1]);

  copyToVector(sf_e12l_ICHEP2012_period2_LoosePP_eta, 20, efficienciesRel172ICHEP_e12Tvh_loose1_LoosePP[2]);
  copyToVector(errsf_e12l_ICHEP2012_period2_LoosePP_eta, 20, uncertaintiesRel172ICHEP_e12Tvh_loose1_LoosePP[2]);
  copyToVector(sf_e12l_ICHEP2012_period2_LoosePP_pt, 14, efficienciesRel172ICHEP_e12Tvh_loose1_LoosePPET[2]);
  copyToVector(errsf_e12l_ICHEP2012_period2_LoosePP_pt, 14, uncertaintiesRel172ICHEP_e12Tvh_loose1_LoosePPET[2]);

  copyToVector(sf_e12l_ICHEP2012_period2_MediumPP_eta, 20, efficienciesRel172ICHEP_e12Tvh_loose1_MediumPP[2]);
  copyToVector(errsf_e12l_ICHEP2012_period2_MediumPP_eta, 20, uncertaintiesRel172ICHEP_e12Tvh_loose1_MediumPP[2]);
  copyToVector(sf_e12l_ICHEP2012_period2_MediumPP_pt, 14, efficienciesRel172ICHEP_e12Tvh_loose1_MediumPPET[2]);
  copyToVector(errsf_e12l_ICHEP2012_period2_MediumPP_pt, 14, uncertaintiesRel172ICHEP_e12Tvh_loose1_MediumPPET[2]);

  copyToVector(sf_e12l_ICHEP2012_period2_TightPP_eta, 20, efficienciesRel172ICHEP_e12Tvh_loose1_TightPP[2]);
  copyToVector(errsf_e12l_ICHEP2012_period2_TightPP_eta, 20, uncertaintiesRel172ICHEP_e12Tvh_loose1_TightPP[2]);
  copyToVector(sf_e12l_ICHEP2012_period2_TightPP_pt, 14, efficienciesRel172ICHEP_e12Tvh_loose1_TightPPET[2]);
  copyToVector(errsf_e12l_ICHEP2012_period2_TightPP_pt, 14, uncertaintiesRel172ICHEP_e12Tvh_loose1_TightPPET[2]);

  copyToVector(sf_e12l_ICHEP2012_period2_ML_eta, 20, efficienciesRel172ICHEP_e12Tvh_loose1_ML[2]);
  copyToVector(errsf_e12l_ICHEP2012_period2_ML_eta, 20, uncertaintiesRel172ICHEP_e12Tvh_loose1_ML[2]);
  copyToVector(sf_e12l_ICHEP2012_period2_ML_pt, 14, efficienciesRel172ICHEP_e12Tvh_loose1_MLET[2]);
  copyToVector(errsf_e12l_ICHEP2012_period2_ML_pt, 14, uncertaintiesRel172ICHEP_e12Tvh_loose1_MLET[2]);

  copyToVector(effMC_e12l_ICHEP2012_period2_LoosePP_eta, 20, MCefficienciesRel172ICHEP_e12Tvh_loose1_LoosePP[2]);
  copyToVector(effMC_e12l_ICHEP2012_period2_LoosePP_pt, 14, MCefficienciesRel172ICHEP_e12Tvh_loose1_LoosePPET[2]);
  copyToVector(effMC_e12l_ICHEP2012_period2_MediumPP_eta, 20, MCefficienciesRel172ICHEP_e12Tvh_loose1_MediumPP[2]);
  copyToVector(effMC_e12l_ICHEP2012_period2_MediumPP_pt, 14, MCefficienciesRel172ICHEP_e12Tvh_loose1_MediumPPET[2]);
  copyToVector(effMC_e12l_ICHEP2012_period2_TightPP_eta, 20, MCefficienciesRel172ICHEP_e12Tvh_loose1_TightPP[2]);
  copyToVector(effMC_e12l_ICHEP2012_period2_TightPP_pt, 14, MCefficienciesRel172ICHEP_e12Tvh_loose1_TightPPET[2]);
  copyToVector(effMC_e12l_ICHEP2012_period2_ML_eta, 20, MCefficienciesRel172ICHEP_e12Tvh_loose1_ML[2]);
  copyToVector(effMC_e12l_ICHEP2012_period2_ML_pt, 14, MCefficienciesRel172ICHEP_e12Tvh_loose1_MLET[2]);



  // ICHEP2012 AFII
  // Raw Rel17.2 ICHEP2012 Reco+TQ SF
const float Sf_RecoTrk_ICHEP2012_AFII_Eta[]={ 100.12, 100.02, 99.55, 100.04, 99.73, 99.66, 99.46, 99.48, 99.17, 99.05,
        98.63, 99.21, 99.60, 99.63, 99.80, 99.57, 99.68, 99.91, 100.08, 101.34};
const float Sf_RecoTrk_ICHEP2012_AFII_Eta_err[]={ 0.87, 0.63, 0.67, 0.59, 0.73, 0.62, 0.59, 0.67, 0.68, 0.82,
				       0.84, 0.68, 0.67, 0.63, 0.61, 0.78, 0.62, 0.65, 0.60, 1.03};
  // Raw Rel17.2 ICHEP2012 AFII Identification SF
const float sfLoosePP_Combined_ICHEP2012_AFII_eta[] = {1.00536, 0.994938, 0.994468, 0.985223, 1.05485, 0.988859, 0.998517, 1.00914, 0.997757, 0.99701, 0.996092, 0.998474, 1.01373, 0.997058, 0.991535, 1.04435, 0.984744, 0.992036, 0.992903, 1.00537};
const float errsfLoosePP_Combined_ICHEP2012_AFII_eta[] = {0.00830261, 0.0079111, 0.00815578, 0.0057287, 0.00691225, 0.00483719, 0.00375873, 0.0052071, 0.00362453, 0.00606912, 0.00594882, 0.00383971, 0.00479793, 0.00419439, 0.00462689, 0.00642659, 0.00563032, 0.00591732, 0.00709705, 0.011418};
const float sfLoosePP_Jpsi_ICHEP2012_AFII_eta[] = {0.92312, 0.92312, 0.959987, 0.959987, 0.769775, 0.98931, 0.98931, 0.974861, 0.974861, 0.960492, 0.960492, 0.974861, 0.974861, 0.98931, 0.98931, 0.769775, 0.959987, 0.959987, 0.92312, 0.92312};
const float errsfLoosePP_Jpsi_ICHEP2012_AFII_eta[] = {0.0619849, 0.0619849, 0.0627333, 0.0627333, 0.169764, 0.0629495, 0.0629495, 0.0331372, 0.0331372, 0.0455599, 0.0455599, 0.0331372, 0.0331372, 0.0629495, 0.0629495, 0.169764, 0.0627333, 0.0627333, 0.0619849, 0.0619849};
const float sfLoosePP_Combined_ICHEP2012_AFII_pt[] = {0., 1.01247, 0.989891, 0.987096, 0.986423, 0.994262, 1.00011, 1.0037, 1.00085, 1.00114};
const float errsfLoosePP_Combined_ICHEP2012_AFII_pt[] = {1., 0.0420164, 0.030814, 0.0147216, 0.0104453, 0.00758445, 0.00678819, 0.00607888, 0.00551403, 0.0054586};
const float sfMediumPP_Combined_ICHEP2012_AFII_eta[] = {0.891543, 0.973372, 0.995542, 0.98934, 1.1718, 1.00922, 1.0217, 1.04086, 1.00237, 1.01751, 1.01623, 1.00544, 1.0456, 1.02027, 1.00525, 1.15487, 0.985426, 0.995522, 0.968347, 0.882427};
const float errsfMediumPP_Combined_ICHEP2012_AFII_eta[] = {0.00917255, 0.00724951, 0.0083111, 0.00846919, 0.0108961, 0.00559964, 0.00461614, 0.00586457, 0.00417334, 0.00716045, 0.00729451, 0.00441748, 0.00545816, 0.00513678, 0.00525796, 0.0100578, 0.00783581, 0.0066803, 0.00676512, 0.00990625};
const float sfMediumPP_Jpsi_ICHEP2012_AFII_eta[] = {0.882596, 0.882596, 0.960178, 0.960178, 0.999557, 1.01747, 1.01747, 0.967703, 0.967703, 0.94465, 0.94465, 0.967703, 0.967703, 1.01747, 1.01747, 0.999557, 0.960178, 0.960178, 0.882596, 0.882596};
const float errsfMediumPP_Jpsi_ICHEP2012_AFII_eta[] = {0.0468464, 0.0468464, 0.0650527, 0.0650527, 0.198237, 0.0554095, 0.0554095, 0.0226936, 0.0226936, 0.0433208, 0.0433208, 0.0226936, 0.0226936, 0.0554095, 0.0554095, 0.198237, 0.0650527, 0.0650527, 0.0468464, 0.0468464};
const float sfMediumPP_Combined_ICHEP2012_AFII_pt[] = {0., 0.990256, 0.986013, 0.98481, 0.977345, 0.995915, 0.997683, 1.00454, 1.00268, 1.00318};
const float errsfMediumPP_Combined_ICHEP2012_AFII_pt[] = {1., 0.049599, 0.0349645, 0.0187254, 0.0124222, 0.008784, 0.00757904, 0.00651319, 0.00560557, 0.0055328};
const float sfTightPP_Combined_ICHEP2012_AFII_eta[] = {0.945774, 0.974809, 1.00957, 1.01495, 1.22836, 1.04219, 1.03296, 1.05209, 1.00475, 1.03032, 1.02844, 1.0091, 1.05685, 1.03902, 1.04393, 1.2088, 1.00799, 1.01152, 0.970709, 0.935968};
const float errsfTightPP_Combined_ICHEP2012_AFII_eta[] = {0.00919868, 0.00628031, 0.00749176, 0.0101425, 0.0124992, 0.00668176, 0.0055057, 0.00642795, 0.00474137, 0.00819041, 0.00865954, 0.00479598, 0.00603101, 0.00592903, 0.00631112, 0.0106358, 0.00941216, 0.0078081, 0.00651701, 0.0120737};
const float sfTightPP_Jpsi_ICHEP2012_AFII_eta[] = {0.901442, 0.901442, 1.00564, 1.00564, 0.824649, 1.02911, 1.02911, 0.963459, 0.963459, 0.967251, 0.967251, 0.963459, 0.963459, 1.02911, 1.02911, 0.824649, 1.00564, 1.00564, 0.901442, 0.901442};
const float errsfTightPP_Jpsi_ICHEP2012_AFII_eta[] = {0.0564573, 0.0564573, 0.0722543, 0.0722543, 0.330133, 0.0514932, 0.0514932, 0.0216509, 0.0216509, 0.048573, 0.048573, 0.0216509, 0.0216509, 0.0514932, 0.0514932, 0.330133, 0.0722543, 0.0722543, 0.0564573, 0.0564573};
const float sfTightPP_Combined_ICHEP2012_AFII_pt[] = {0., 0.993046, 0.98408, 0.98905, 0.9767, 0.995077, 0.993795, 1.00176, 1.00533, 1.00528};
const float errsfTightPP_Combined_ICHEP2012_AFII_pt[] = {1., 0.0520844, 0.0357209, 0.0215797, 0.0148423, 0.010136, 0.00844803, 0.00703036, 0.00572107, 0.00560564};
const float sfML_Combined_ICHEP2012_AFII_eta[] = {1.01219, 0.98928, 0.989902, 0.99452, 1.05788, 1.04544, 1.02121, 1.00839, 1.00156, 1.01182, 1.00636, 1.00151, 1.01342, 1.01779, 1.04745, 1.04646, 0.996306, 0.989389, 0.986479, 1.00467};
const float errsfML_Combined_ICHEP2012_AFII_eta[] = {0.0076882, 0.00650232, 0.0078883, 0.00548956, 0.00606341, 0.00467492, 0.00379292, 0.00519546, 0.00374822, 0.00668487, 0.00651756, 0.00391394, 0.00467113, 0.00434314, 0.00445763, 0.0057212, 0.00533556, 0.00598391, 0.00543281, 0.0120516};
const float sfML_Jpsi_ICHEP2012_AFII_eta[] = {0.940147, 0.940147, 0.982131, 0.982131, 0.937241, 1.02314, 1.02314, 0.991193, 0.991193, 0.993034, 0.993034, 0.991193, 0.991193, 1.02314, 1.02314, 0.937241, 0.982131, 0.982131, 0.940147, 0.940147};
const float errsfML_Jpsi_ICHEP2012_AFII_eta[] = {0.0551854, 0.0551854, 0.0606368, 0.0606368, 0.198336, 0.0549884, 0.0549884, 0.0218532, 0.0218532, 0.0378092, 0.0378092, 0.0218532, 0.0218532, 0.0549884, 0.0549884, 0.198336, 0.0606368, 0.0606368, 0.0551854, 0.0551854};
const float sfML_Combined_ICHEP2012_AFII_pt[] = {0., 0.980582, 1.00932, 0.981102, 0.982832, 0.992376, 0.99985, 1.00439, 1.00111, 1.00089};
const float errsfML_Combined_ICHEP2012_AFII_pt[] = {1., 0.0431767, 0.0302716, 0.015195, 0.010455, 0.00764168, 0.00679229, 0.00608317, 0.0055211, 0.00547165};

  // reco+TQ 
  copyToVector(Sf_RecoTrk_ICHEP2012_AFII_Eta, 20, efficienciesRel172ICHEP_AFIIRecoTrkQual, 1.);
  copyToVector(Sf_RecoTrk_ICHEP2012_AFII_Eta_err, 20, uncertaintiesRel172ICHEP_AFIIRecoTrkQual, 1.);
 
  // Identification eta for probes between 15 and 50 GeV
  copyToVector(sfLoosePP_Combined_ICHEP2012_AFII_eta, 20, efficienciesRel172ICHEP_AFIILoosePP1550);
  copyToVector(errsfLoosePP_Combined_ICHEP2012_AFII_eta, 20, uncertaintiesRel172ICHEP_AFIILoosePP1550);
  copyToVector(sfMediumPP_Combined_ICHEP2012_AFII_eta, 20, efficienciesRel172ICHEP_AFIIMediumPP1550);
  copyToVector(errsfMediumPP_Combined_ICHEP2012_AFII_eta, 20, uncertaintiesRel172ICHEP_AFIIMediumPP1550);
  copyToVector(sfTightPP_Combined_ICHEP2012_AFII_eta, 20, efficienciesRel172ICHEP_AFIITightPP1550);
  copyToVector(errsfTightPP_Combined_ICHEP2012_AFII_eta, 20, uncertaintiesRel172ICHEP_AFIITightPP1550);
  copyToVector(sfML_Combined_ICHEP2012_AFII_eta, 20, efficienciesRel172ICHEP_AFIIML1550);
  copyToVector(errsfML_Combined_ICHEP2012_AFII_eta, 20, uncertaintiesRel172ICHEP_AFIIML1550);
  //Identification eta for low ET probes
  copyToVector(sfLoosePP_Jpsi_ICHEP2012_AFII_eta, 20, efficienciesRel172ICHEP_AFIILoosePP415);
  copyToVector(errsfLoosePP_Jpsi_ICHEP2012_AFII_eta, 20, uncertaintiesRel172ICHEP_AFIILoosePP415);
  copyToVector(sfMediumPP_Jpsi_ICHEP2012_AFII_eta, 20, efficienciesRel172ICHEP_AFIIMediumPP415);
  copyToVector(errsfMediumPP_Jpsi_ICHEP2012_AFII_eta, 20, uncertaintiesRel172ICHEP_AFIIMediumPP415);
  copyToVector(sfTightPP_Jpsi_ICHEP2012_AFII_eta, 20, efficienciesRel172ICHEP_AFIITightPP415);
  copyToVector(errsfTightPP_Jpsi_ICHEP2012_AFII_eta, 20, uncertaintiesRel172ICHEP_AFIITightPP415);
  copyToVector(sfML_Jpsi_ICHEP2012_AFII_eta, 20, efficienciesRel172ICHEP_AFIIML415);
  copyToVector(errsfML_Jpsi_ICHEP2012_AFII_eta, 20, uncertaintiesRel172ICHEP_AFIIML415);
  // ET correction
  copyToVector(sfLoosePP_Combined_ICHEP2012_AFII_pt, 10, ETCorrectionsRel172ICHEP_AFIILoosePP);
  copyToVector(errsfLoosePP_Combined_ICHEP2012_AFII_pt, 10, uncertaintiesETCorrectionsRel172ICHEP_AFIILoosePP);
  copyToVector(sfMediumPP_Combined_ICHEP2012_AFII_pt, 10, ETCorrectionsRel172ICHEP_AFIIMediumPP);
  copyToVector(errsfMediumPP_Combined_ICHEP2012_AFII_pt, 10, uncertaintiesETCorrectionsRel172ICHEP_AFIIMediumPP);
  copyToVector(sfTightPP_Combined_ICHEP2012_AFII_pt, 10, ETCorrectionsRel172ICHEP_AFIITightPP);
  copyToVector(errsfTightPP_Combined_ICHEP2012_AFII_pt, 10, uncertaintiesETCorrectionsRel172ICHEP_AFIITightPP);
  copyToVector(sfML_Combined_ICHEP2012_AFII_pt, 10, ETCorrectionsRel172ICHEP_AFIIML);
  copyToVector(errsfML_Combined_ICHEP2012_AFII_pt, 10, uncertaintiesETCorrectionsRel172ICHEP_AFIIML);

  // single electron trigger e24vhi_medium1||e60_medium1 vs. different offline and 3 data periods, plus MC efficiencies!
const float sf_e24e60_ICHEP2012_AFII_period0_LoosePP_eta[] = {0.30629, 0.9408, 0.93923, 0.9945, 0.94391, 1.0175, 1.05111, 1.0098, 1.01164, 1.05375, 1.04937, 1.022, 1.0337, 1.04541, 0.99867, 0.88836, 0.97298, 0.95449, 0.9183, 0.21785};
const float errsf_e24e60_ICHEP2012_AFII_period0_LoosePP_eta[] = {0.0199736, 0.0110409, 0.0111983, 0.0117555, 0.0322876, 0.0105915, 0.010212, 0.01032, 0.0101164, 0.0109414, 0.0116363, 0.0100907, 0.0102981, 0.01021, 0.0104403, 0.0247593, 0.0107519, 0.0112666, 0.0114127, 0.0136971};

const float effMC_e24e60_ICHEP2012_AFII_period0_LoosePP_eta[] = {0.74972, 0.8293, 0.83924, 0.8394, 0.64661, 0.88341, 0.84587, 0.88443, 0.90837, 0.85601, 0.85226, 0.90462, 0.88292, 0.84804, 0.88265, 0.64855, 0.84249, 0.83999, 0.82973, 0.75987};
const float sf_e24e60_ICHEP2012_AFII_period0_LoosePP_pt[] = {0.935354, 0.954254, 0.956228, 0.973353, 0.992362, 0.989635, 0.998579, 1.00464, 1.00197, 1.01184, 0.990002, 0.975316, 0.993939, 0.993344, 0.993344};
const float errsf_e24e60_ICHEP2012_AFII_period0_LoosePP_pt[] = {0.0132181, 0.00950952, 0.00884515, 0.00686193, 0.00879557, 0.00483905, 0.00359954, 0.0023402, 0.00114035, 0.00150724, 0.0017254, 0.00262776, 0.00477955, 0.0147551, 0.0189001};

const float effMC_e24e60_ICHEP2012_AFII_period0_LoosePP_pt[] = {0.752102, 0.885972, 0.908812, 0.925589, 0.938324, 0.956376, 0.973876, 0.986944, 1.00372, 1.01496, 1.01417, 1.08035, 1.09801, 1.10118, 1.11293};
const float sf_e24e60_ICHEP2012_AFII_period0_MediumPP_eta[] = {0.34578, 0.963, 0.94014, 0.98897, 0.84186, 1.00188, 1.03356, 0.98023, 1.00515, 1.03058, 1.02258, 1.00888, 1.00753, 1.03217, 0.9954, 0.80592, 0.98218, 0.96186, 0.9446, 0.24584};
const float errsf_e24e60_ICHEP2012_AFII_period0_MediumPP_eta[] = {0.017466, 0.0106351, 0.0110283, 0.0104317, 0.0261662, 0.0101537, 0.010132, 0.010152, 0.0100422, 0.0103401, 0.0105056, 0.0100319, 0.0100961, 0.0100934, 0.0101789, 0.0202512, 0.0103529, 0.0108193, 0.0107592, 0.0196628};

const float effMC_e24e60_ICHEP2012_AFII_period0_MediumPP_eta[] = {0.76537, 0.87694, 0.90143, 0.89388, 0.79817, 0.94808, 0.91642, 0.95402, 0.95862, 0.92637, 0.92603, 0.9586, 0.95355, 0.91872, 0.94599, 0.80136, 0.89672, 0.89941, 0.87786, 0.77501};
const float sf_e24e60_ICHEP2012_AFII_period0_MediumPP_pt[] = {0.930843, 0.938058, 0.954056, 0.959226, 0.977679, 0.991671, 0.994695, 0.998857, 1.00374, 1.00228, 1.00675, 0.996172, 0.98735, 0.994935, 0.985194};
const float errsf_e24e60_ICHEP2012_AFII_period0_MediumPP_pt[] = {0.0121258, 0.00748507, 0.00718566, 0.00595811, 0.00479044, 0.00340321, 0.00206588, 0.00155689, 0.000868268, 0.00123753, 0.00150699, 0.00163673, 0.00342317, 0.0107486, 0.0147206};

const float effMC_e24e60_ICHEP2012_AFII_period0_MediumPP_pt[] = {0.790076, 0.929163, 0.949496, 0.961737, 0.969905, 0.971538, 0.982586, 0.991399, 0.998266, 1.00482, 1.00417, 1.04785, 1.05449, 1.05439, 1.06733};
const float sf_e24e60_ICHEP2012_AFII_period0_ML_eta[] = {0.30808, 0.94799, 0.94115, 0.98665, 0.93994, 0.99523, 1.0406, 1.01146, 1.01014, 1.03966, 1.04147, 1.02025, 1.0355, 1.03493, 0.97634, 0.89133, 0.96895, 0.95418, 0.92195, 0.21727};
const float errsf_e24e60_ICHEP2012_AFII_period0_ML_eta[] = {0.0199909, 0.0109782, 0.0113839, 0.0115104, 0.0343671, 0.0105336, 0.010177, 0.01032, 0.0100921, 0.0106765, 0.0109172, 0.0100778, 0.0102181, 0.0101808, 0.0103633, 0.0248874, 0.0112391, 0.0115703, 0.0115203, 0.0150894};

const float effMC_e24e60_ICHEP2012_AFII_period0_ML_eta[] = {0.75477, 0.83859, 0.84961, 0.85182, 0.64311, 0.90848, 0.86276, 0.8882, 0.91211, 0.87968, 0.87662, 0.90782, 0.88785, 0.86421, 0.9063, 0.64525, 0.85494, 0.84993, 0.83893, 0.76351};
const float sf_e24e60_ICHEP2012_AFII_period0_ML_pt[] = {0.913255, 0.935176, 0.956629, 0.9529, 0.976187, 0.992048, 0.991469, 0.997809, 1.00509, 1.00115, 1.00951, 0.995367, 0.98164, 0.997181, 0.998557};
const float errsf_e24e60_ICHEP2012_AFII_period0_ML_pt[] = {0.0135176, 0.00917123, 0.00897185, 0.00720739, 0.00840363, 0.00506411, 0.00395758, 0.00205356, 0.00106665, 0.00142553, 0.0017545, 0.00252209, 0.00509402, 0.0152721, 0.0189107};

const float effMC_e24e60_ICHEP2012_AFII_period0_ML_pt[] = {0.748164, 0.881563, 0.904872, 0.922294, 0.934261, 0.954825, 0.972394, 0.988296, 1.00486, 1.01706, 1.01894, 1.06944, 1.08373, 1.08991, 1.09936};
const float sf_e24e60_ICHEP2012_AFII_period0_TightPP_eta[] = {0.33916, 0.96152, 0.94848, 0.98633, 0.84237, 1.00165, 1.03138, 0.97999, 1.00372, 1.02541, 1.01921, 1.00689, 1.00639, 1.03026, 0.99276, 0.80794, 0.98249, 0.95982, 0.94199, 0.24562};
const float errsf_e24e60_ICHEP2012_AFII_period0_TightPP_eta[] = {0.0168808, 0.0105211, 0.010666, 0.0104289, 0.0252542, 0.0100921, 0.0101179, 0.0101209, 0.0100259, 0.0102679, 0.0103955, 0.0100224, 0.0100659, 0.0101017, 0.0101089, 0.0193622, 0.0103607, 0.0106317, 0.0106351, 0.0199217};

const float effMC_e24e60_ICHEP2012_AFII_period0_TightPP_eta[] = {0.81448, 0.91502, 0.94134, 0.92647, 0.82525, 0.97107, 0.9342, 0.96918, 0.97309, 0.94243, 0.94164, 0.9734, 0.96779, 0.93533, 0.97014, 0.82767, 0.92995, 0.94119, 0.91783, 0.8253};
const float sf_e24e60_ICHEP2012_AFII_period0_TightPP_pt[] = {0.932536, 0.936499, 0.963548, 0.960986, 0.985884, 0.992188, 0.992358, 0.999243, 1.00348, 1.00228, 1.00603, 0.996541, 0.987765, 0.990697, 0.984392};
const float errsf_e24e60_ICHEP2012_AFII_period0_TightPP_pt[] = {0.0114981, 0.0073952, 0.00792558, 0.0054038, 0.00409288, 0.00261184, 0.00203143, 0.00119084, 0.000820577, 0.00098069, 0.00155109, 0.00136096, 0.0029921, 0.0102472, 0.0154108};

const float effMC_e24e60_ICHEP2012_AFII_period0_TightPP_pt[] = {0.802005, 0.942378, 0.963062, 0.973541, 0.978901, 0.980421, 0.988414, 0.994865, 0.997644, 1.00014, 0.997434, 1.03395, 1.03672, 1.03911, 1.04383};
const float sf_e24e60_ICHEP2012_AFII_period1_LoosePP_eta[] = {1.0678, 0.97031, 0.94946, 0.98345, 0.89855, 1.01486, 1.05193, 1.00638, 1.01331, 1.04533, 1.03807, 1.01764, 1.03521, 1.04815, 1.00484, 0.8838, 0.97508, 0.95983, 0.9743, 1.04092};
const float errsf_e24e60_ICHEP2012_AFII_period1_LoosePP_eta[] = {0.0143774, 0.0107084, 0.0110073, 0.0115005, 0.0356896, 0.0105622, 0.010177, 0.0102958, 0.0100614, 0.0106148, 0.0109577, 0.0100717, 0.0101864, 0.010177, 0.0102816, 0.0250982, 0.0111492, 0.0114466, 0.0112712, 0.0133936};

const float effMC_e24e60_ICHEP2012_AFII_period1_LoosePP_eta[] = {0.74972, 0.8293, 0.83924, 0.8394, 0.64661, 0.88341, 0.84587, 0.88443, 0.90837, 0.85601, 0.85226, 0.90462, 0.88292, 0.84804, 0.88265, 0.64855, 0.84249, 0.83999, 0.82973, 0.75987};
const float sf_e24e60_ICHEP2012_AFII_period1_LoosePP_pt[] = {0.963064, 0.96274, 0.976801, 0.982195, 0.984632, 0.991157, 1.00193, 1.00427, 1.0065, 1.00835, 0.984092, 0.969883, 0.988307, 0.959045, 0.959045};
const float errsf_e24e60_ICHEP2012_AFII_period1_LoosePP_pt[] = {0.012312, 0.0119189, 0.00822435, 0.00794922, 0.00763479, 0.00465752, 0.00211259, 0.0014739, 0.000923642, 0.00107103, 0.00155251, 0.00202415, 0.00382231, 0.011634, 0.026255};

const float effMC_e24e60_ICHEP2012_AFII_period1_LoosePP_pt[] = {0.752102, 0.885972, 0.908812, 0.925589, 0.938324, 0.956376, 0.973876, 0.986944, 1.00372, 1.01496, 1.01417, 1.08035, 1.09801, 1.10118, 1.11293};
const float sf_e24e60_ICHEP2012_AFII_period1_MediumPP_eta[] = {1.09842, 0.98414, 0.94853, 0.98107, 0.80253, 0.99774, 1.0303, 0.98051, 1.0039, 1.0167, 1.01518, 1.00445, 1.00245, 1.02464, 0.98724, 0.78495, 0.96782, 0.95633, 0.98556, 1.08619};
const float errsf_e24e60_ICHEP2012_AFII_period1_MediumPP_eta[] = {0.0140575, 0.0105462, 0.0106453, 0.01033, 0.0288768, 0.0101418, 0.0100867, 0.0101149, 0.0100288, 0.0103581, 0.0104606, 0.0100395, 0.0100989, 0.0101075, 0.0101752, 0.0215063, 0.0103275, 0.0105915, 0.0105654, 0.0149179};

const float effMC_e24e60_ICHEP2012_AFII_period1_MediumPP_eta[] = {0.76537, 0.87694, 0.90143, 0.89388, 0.79817, 0.94808, 0.91642, 0.95402, 0.95862, 0.92637, 0.92603, 0.9586, 0.95355, 0.91872, 0.94599, 0.80136, 0.89672, 0.89941, 0.87786, 0.77501};
const float sf_e24e60_ICHEP2012_AFII_period1_MediumPP_pt[] = {0.943813, 0.960286, 0.963564, 0.974404, 0.981388, 0.988979, 0.993678, 1.00087, 1.00253, 1.00376, 1.00695, 0.99036, 0.982432, 0.986286, 0.972596};
const float errsf_e24e60_ICHEP2012_AFII_period1_MediumPP_pt[] = {0.0103923, 0.00697458, 0.00611021, 0.00475901, 0.00462985, 0.00267259, 0.00153004, 0.00105314, 0.000765018, 0.00086437, 0.00121211, 0.00153004, 0.00279182, 0.0097962, 0.0175259};

const float effMC_e24e60_ICHEP2012_AFII_period1_MediumPP_pt[] = {0.790076, 0.929163, 0.949496, 0.961737, 0.969905, 0.971538, 0.982586, 0.991399, 0.998266, 1.00482, 1.00417, 1.04785, 1.05449, 1.05439, 1.06733};
const float sf_e24e60_ICHEP2012_AFII_period1_ML_eta[] = {1.06918, 0.96837, 0.95389, 0.97858, 0.89868, 0.99327, 1.03988, 1.00944, 1.01097, 1.03341, 1.03276, 1.01542, 1.03665, 1.03676, 0.98287, 0.88781, 0.96917, 0.96238, 0.97115, 1.04115};
const float errsf_e24e60_ICHEP2012_AFII_period1_ML_eta[] = {0.0140716, 0.0107191, 0.0107778, 0.0112574, 0.0375173, 0.0104232, 0.0101625, 0.0102349, 0.0100694, 0.0107409, 0.0111316, 0.0100934, 0.0101961, 0.0101827, 0.0103739, 0.0285393, 0.0111054, 0.010854, 0.0108657, 0.0139804};

const float effMC_e24e60_ICHEP2012_AFII_period1_ML_eta[] = {0.75477, 0.83859, 0.84961, 0.85182, 0.64311, 0.90848, 0.86276, 0.8882, 0.91211, 0.87968, 0.87662, 0.90782, 0.88785, 0.86421, 0.9063, 0.64525, 0.85494, 0.84993, 0.83893, 0.76351};
const float sf_e24e60_ICHEP2012_AFII_period1_ML_pt[] = {0.935477, 0.960905, 0.961389, 0.975323, 0.980053, 0.985365, 0.992673, 1.00073, 1.00288, 1.0045, 1.00665, 0.988693, 0.975688, 0.98814, 0.946695};
const float errsf_e24e60_ICHEP2012_AFII_period1_ML_pt[] = {0.0113857, 0.0109414, 0.0082554, 0.00706054, 0.00776166, 0.00494732, 0.00211323, 0.00145161, 0.000878865, 0.00104674, 0.00146148, 0.00207373, 0.00390058, 0.0120671, 0.0312738};

const float effMC_e24e60_ICHEP2012_AFII_period1_ML_pt[] = {0.748164, 0.881563, 0.904872, 0.922294, 0.934261, 0.954825, 0.972394, 0.988296, 1.00486, 1.01706, 1.01894, 1.06944, 1.08373, 1.08991, 1.09936};
const float sf_e24e60_ICHEP2012_AFII_period1_TightPP_eta[] = {1.09638, 0.98521, 0.94963, 0.98344, 0.80165, 0.9979, 1.02798, 0.97898, 1.00301, 1.01668, 1.01429, 1.00291, 1.00237, 1.02455, 0.98572, 0.7864, 0.96783, 0.95791, 0.98471, 1.07504};
const float errsf_e24e60_ICHEP2012_AFII_period1_TightPP_eta[] = {0.0129068, 0.0104176, 0.0104965, 0.0102934, 0.0271581, 0.0100921, 0.0100706, 0.0101003, 0.0100198, 0.0103766, 0.0103982, 0.0100252, 0.0100766, 0.0100975, 0.0101119, 0.0205039, 0.0103053, 0.0104346, 0.0103555, 0.0139874};

const float effMC_e24e60_ICHEP2012_AFII_period1_TightPP_eta[] = {0.81448, 0.91502, 0.94134, 0.92647, 0.82525, 0.97107, 0.9342, 0.96918, 0.97309, 0.94243, 0.94164, 0.9734, 0.96779, 0.93533, 0.97014, 0.82767, 0.92995, 0.94119, 0.91783, 0.8253};
const float sf_e24e60_ICHEP2012_AFII_period1_TightPP_pt[] = {0.948189, 0.962485, 0.969005, 0.97698, 0.983988, 0.988946, 0.995835, 1.00033, 1.00202, 1.0039, 1.00598, 0.991654, 0.985601, 0.980822, 0.980165};
const float errsf_e24e60_ICHEP2012_AFII_period1_TightPP_pt[] = {0.00985581, 0.00586371, 0.00559491, 0.00403192, 0.00371335, 0.00233951, 0.00132406, 0.000826295, 0.00068692, 0.000726742, 0.00114487, 0.00119464, 0.00246893, 0.00944764, 0.0145946};

const float effMC_e24e60_ICHEP2012_AFII_period1_TightPP_pt[] = {0.802005, 0.942378, 0.963062, 0.973541, 0.978901, 0.980421, 0.988414, 0.994865, 0.997644, 1.00014, 0.997434, 1.03395, 1.03672, 1.03911, 1.04383};
const float sf_e24e60_ICHEP2012_AFII_period2_LoosePP_eta[] = {1.0678, 0.97031, 0.94946, 0.98345, 0.89855, 1.01486, 1.05193, 1.00638, 1.01331, 1.04533, 1.03807, 1.01764, 1.03521, 1.04815, 1.00484, 0.8838, 0.97508, 0.95983, 0.9743, 1.04092};
const float errsf_e24e60_ICHEP2012_AFII_period2_LoosePP_eta[] = {0.0246315, 0.0226863, 0.0110073, 0.0115005, 0.0356896, 0.0105622, 0.010177, 0.0102958, 0.0100614, 0.0106148, 0.0109577, 0.0100717, 0.0101864, 0.010177, 0.0102816, 0.0250982, 0.0111492, 0.0114466, 0.0229574, 0.0240705};

const float effMC_e24e60_ICHEP2012_AFII_period2_LoosePP_eta[] = {0.74972, 0.8293, 0.83924, 0.8394, 0.64661, 0.88341, 0.84587, 0.88443, 0.90837, 0.85601, 0.85226, 0.90462, 0.88292, 0.84804, 0.88265, 0.64855, 0.84249, 0.83999, 0.82973, 0.75987};
const float sf_e24e60_ICHEP2012_AFII_period2_LoosePP_pt[] = {0.963064, 0.96274, 0.976801, 0.982195, 0.984632, 0.991157, 1.00193, 1.00427, 1.0065, 1.00835, 0.984092, 0.969883, 0.988307, 0.959045, 0.959045};
const float errsf_e24e60_ICHEP2012_AFII_period2_LoosePP_pt[] = {0.012312, 0.0119189, 0.00822435, 0.00794922, 0.00763479, 0.00465752, 0.00211259, 0.0014739, 0.000923642, 0.00107103, 0.00155251, 0.00202415, 0.00382231, 0.011634, 0.026255};

const float effMC_e24e60_ICHEP2012_AFII_period2_LoosePP_pt[] = {0.752102, 0.885972, 0.908812, 0.925589, 0.938324, 0.956376, 0.973876, 0.986944, 1.00372, 1.01496, 1.01417, 1.08035, 1.09801, 1.10118, 1.11293};
const float sf_e24e60_ICHEP2012_AFII_period2_MediumPP_eta[] = {1.09842, 0.98414, 0.94853, 0.98107, 0.80253, 0.99774, 1.0303, 0.98051, 1.0039, 1.0167, 1.01518, 1.00445, 1.00245, 1.02464, 0.98724, 0.78495, 0.96782, 0.95633, 0.98556, 1.08619};
const float errsf_e24e60_ICHEP2012_AFII_period2_MediumPP_eta[] = {0.0244462, 0.0226102, 0.0106453, 0.01033, 0.0288768, 0.0101418, 0.0100867, 0.0101149, 0.0100288, 0.0103581, 0.0104606, 0.0100395, 0.0100989, 0.0101075, 0.0101752, 0.0215063, 0.0103275, 0.0105915, 0.0226192, 0.0249508};

const float effMC_e24e60_ICHEP2012_AFII_period2_MediumPP_eta[] = {0.76537, 0.87694, 0.90143, 0.89388, 0.79817, 0.94808, 0.91642, 0.95402, 0.95862, 0.92637, 0.92603, 0.9586, 0.95355, 0.91872, 0.94599, 0.80136, 0.89672, 0.89941, 0.87786, 0.77501};
const float sf_e24e60_ICHEP2012_AFII_period2_MediumPP_pt[] = {0.943813, 0.960286, 0.963564, 0.974404, 0.981388, 0.988979, 0.993678, 1.00087, 1.00253, 1.00376, 1.00695, 0.99036, 0.982432, 0.986286, 0.972596};
const float errsf_e24e60_ICHEP2012_AFII_period2_MediumPP_pt[] = {0.0103923, 0.00697458, 0.00611021, 0.00475901, 0.00462985, 0.00267259, 0.00153004, 0.00105314, 0.000765018, 0.00086437, 0.00121211, 0.00153004, 0.00279182, 0.0097962, 0.0175259};

const float effMC_e24e60_ICHEP2012_AFII_period2_MediumPP_pt[] = {0.790076, 0.929163, 0.949496, 0.961737, 0.969905, 0.971538, 0.982586, 0.991399, 0.998266, 1.00482, 1.00417, 1.04785, 1.05449, 1.05439, 1.06733};
const float sf_e24e60_ICHEP2012_AFII_period2_ML_eta[] = {1.06918, 0.96837, 0.95389, 0.97858, 0.89868, 0.99327, 1.03988, 1.00944, 1.01097, 1.03341, 1.03276, 1.01542, 1.03665, 1.03676, 0.98287, 0.88781, 0.96917, 0.96238, 0.97115, 1.04115};
const float errsf_e24e60_ICHEP2012_AFII_period2_ML_eta[] = {0.0244542, 0.0226914, 0.0107778, 0.0112574, 0.0375173, 0.0104232, 0.0101625, 0.0102349, 0.0100694, 0.0107409, 0.0111316, 0.0100934, 0.0101961, 0.0101827, 0.0103739, 0.0285393, 0.0111054, 0.010854, 0.022761, 0.0244019};

const float effMC_e24e60_ICHEP2012_AFII_period2_ML_eta[] = {0.75477, 0.83859, 0.84961, 0.85182, 0.64311, 0.90848, 0.86276, 0.8882, 0.91211, 0.87968, 0.87662, 0.90782, 0.88785, 0.86421, 0.9063, 0.64525, 0.85494, 0.84993, 0.83893, 0.76351};
const float sf_e24e60_ICHEP2012_AFII_period2_ML_pt[] = {0.935477, 0.960905, 0.961389, 0.975323, 0.980053, 0.985365, 0.992673, 1.00073, 1.00288, 1.0045, 1.00665, 0.988693, 0.975688, 0.98814, 0.946695};
const float errsf_e24e60_ICHEP2012_AFII_period2_ML_pt[] = {0.0113857, 0.0109414, 0.0082554, 0.00706054, 0.00776166, 0.00494732, 0.00211323, 0.00145161, 0.000878865, 0.00104674, 0.00146148, 0.00207373, 0.00390058, 0.0120671, 0.0312738};

const float effMC_e24e60_ICHEP2012_AFII_period2_ML_pt[] = {0.748164, 0.881563, 0.904872, 0.922294, 0.934261, 0.954825, 0.972394, 0.988296, 1.00486, 1.01706, 1.01894, 1.06944, 1.08373, 1.08991, 1.09936};
const float sf_e24e60_ICHEP2012_AFII_period2_TightPP_eta[] = {1.09638, 0.98521, 0.94963, 0.98344, 0.80165, 0.9979, 1.02798, 0.97898, 1.00301, 1.01668, 1.01429, 1.00291, 1.00237, 1.02455, 0.98572, 0.7864, 0.96783, 0.95791, 0.98471, 1.07504};
const float errsf_e24e60_ICHEP2012_AFII_period2_TightPP_eta[] = {0.0238031, 0.0225505, 0.0104965, 0.0102934, 0.0271581, 0.0100921, 0.0100706, 0.0101003, 0.0100198, 0.0103766, 0.0103982, 0.0100252, 0.0100766, 0.0100975, 0.0101119, 0.0205039, 0.0103053, 0.0104346, 0.0225219, 0.0244059};

const float effMC_e24e60_ICHEP2012_AFII_period2_TightPP_eta[] = {0.81448, 0.91502, 0.94134, 0.92647, 0.82525, 0.97107, 0.9342, 0.96918, 0.97309, 0.94243, 0.94164, 0.9734, 0.96779, 0.93533, 0.97014, 0.82767, 0.92995, 0.94119, 0.91783, 0.8253};
const float sf_e24e60_ICHEP2012_AFII_period2_TightPP_pt[] = {0.948189, 0.962485, 0.969005, 0.97698, 0.983988, 0.988946, 0.995835, 1.00033, 1.00202, 1.0039, 1.00598, 0.991654, 0.985601, 0.980822, 0.980165};
const float errsf_e24e60_ICHEP2012_AFII_period2_TightPP_pt[] = {0.00985581, 0.00586371, 0.00559491, 0.00403192, 0.00371335, 0.00233951, 0.00132406, 0.000826295, 0.00068692, 0.000726742, 0.00114487, 0.00119464, 0.00246893, 0.00944764, 0.0145946};

const float effMC_e24e60_ICHEP2012_AFII_period2_TightPP_pt[] = {0.802005, 0.942378, 0.963062, 0.973541, 0.978901, 0.980421, 0.988414, 0.994865, 0.997644, 1.00014, 0.997434, 1.03395, 1.03672, 1.03911, 1.04383};

 efficienciesRel172ICHEP_AFII_e24vhi_medium1_LoosePP.resize(3);
 uncertaintiesRel172ICHEP_AFII_e24vhi_medium1_LoosePP.resize(3);
 efficienciesRel172ICHEP_AFII_e24vhi_medium1_LoosePPET.resize(3);
 uncertaintiesRel172ICHEP_AFII_e24vhi_medium1_LoosePPET.resize(3);
 
 MCefficienciesRel172ICHEP_AFII_e24vhi_medium1_LoosePP.resize(3);
 MCefficienciesRel172ICHEP_AFII_e24vhi_medium1_LoosePPET.resize(3);
 
 efficienciesRel172ICHEP_AFII_e24vhi_medium1_MediumPP.resize(3);
 uncertaintiesRel172ICHEP_AFII_e24vhi_medium1_MediumPP.resize(3);
 efficienciesRel172ICHEP_AFII_e24vhi_medium1_MediumPPET.resize(3);
 uncertaintiesRel172ICHEP_AFII_e24vhi_medium1_MediumPPET.resize(3);
 
 MCefficienciesRel172ICHEP_AFII_e24vhi_medium1_MediumPP.resize(3);
 MCefficienciesRel172ICHEP_AFII_e24vhi_medium1_MediumPPET.resize(3);
 
 efficienciesRel172ICHEP_AFII_e24vhi_medium1_TightPP.resize(3);
 uncertaintiesRel172ICHEP_AFII_e24vhi_medium1_TightPP.resize(3);
 efficienciesRel172ICHEP_AFII_e24vhi_medium1_TightPPET.resize(3);
 uncertaintiesRel172ICHEP_AFII_e24vhi_medium1_TightPPET.resize(3);
 
 MCefficienciesRel172ICHEP_AFII_e24vhi_medium1_TightPP.resize(3);
 MCefficienciesRel172ICHEP_AFII_e24vhi_medium1_TightPPET.resize(3);

 efficienciesRel172ICHEP_AFII_e24vhi_medium1_ML.resize(3);
 uncertaintiesRel172ICHEP_AFII_e24vhi_medium1_ML.resize(3);
 efficienciesRel172ICHEP_AFII_e24vhi_medium1_MLET.resize(3);
 uncertaintiesRel172ICHEP_AFII_e24vhi_medium1_MLET.resize(3);
 
 MCefficienciesRel172ICHEP_AFII_e24vhi_medium1_ML.resize(3);
 MCefficienciesRel172ICHEP_AFII_e24vhi_medium1_MLET.resize(3);

  copyToVector(sf_e24e60_ICHEP2012_AFII_period0_LoosePP_eta, 20, efficienciesRel172ICHEP_AFII_e24vhi_medium1_LoosePP[0]);
  copyToVector(errsf_e24e60_ICHEP2012_AFII_period0_LoosePP_eta, 20, uncertaintiesRel172ICHEP_AFII_e24vhi_medium1_LoosePP[0]);
  copyToVector(sf_e24e60_ICHEP2012_AFII_period0_LoosePP_pt, 15, efficienciesRel172ICHEP_AFII_e24vhi_medium1_LoosePPET[0]);
  copyToVector(errsf_e24e60_ICHEP2012_AFII_period0_LoosePP_pt, 15, uncertaintiesRel172ICHEP_AFII_e24vhi_medium1_LoosePPET[0]);

  copyToVector(sf_e24e60_ICHEP2012_AFII_period0_MediumPP_eta, 20, efficienciesRel172ICHEP_AFII_e24vhi_medium1_MediumPP[0]);
  copyToVector(errsf_e24e60_ICHEP2012_AFII_period0_MediumPP_eta, 20, uncertaintiesRel172ICHEP_AFII_e24vhi_medium1_MediumPP[0]);
  copyToVector(sf_e24e60_ICHEP2012_AFII_period0_MediumPP_pt, 15, efficienciesRel172ICHEP_AFII_e24vhi_medium1_MediumPPET[0]);
  copyToVector(errsf_e24e60_ICHEP2012_AFII_period0_MediumPP_pt, 15, uncertaintiesRel172ICHEP_AFII_e24vhi_medium1_MediumPPET[0]);

  copyToVector(sf_e24e60_ICHEP2012_AFII_period0_TightPP_eta, 20, efficienciesRel172ICHEP_AFII_e24vhi_medium1_TightPP[0]);
  copyToVector(errsf_e24e60_ICHEP2012_AFII_period0_TightPP_eta, 20, uncertaintiesRel172ICHEP_AFII_e24vhi_medium1_TightPP[0]);
  copyToVector(sf_e24e60_ICHEP2012_AFII_period0_TightPP_pt, 15, efficienciesRel172ICHEP_AFII_e24vhi_medium1_TightPPET[0]);
  copyToVector(errsf_e24e60_ICHEP2012_AFII_period0_TightPP_pt, 15, uncertaintiesRel172ICHEP_AFII_e24vhi_medium1_TightPPET[0]);

  copyToVector(sf_e24e60_ICHEP2012_AFII_period0_ML_eta, 20, efficienciesRel172ICHEP_AFII_e24vhi_medium1_ML[0]);
  copyToVector(errsf_e24e60_ICHEP2012_AFII_period0_ML_eta, 20, uncertaintiesRel172ICHEP_AFII_e24vhi_medium1_ML[0]);
  copyToVector(sf_e24e60_ICHEP2012_AFII_period0_ML_pt, 15, efficienciesRel172ICHEP_AFII_e24vhi_medium1_MLET[0]);
  copyToVector(errsf_e24e60_ICHEP2012_AFII_period0_ML_pt, 15, uncertaintiesRel172ICHEP_AFII_e24vhi_medium1_MLET[0]);

  copyToVector(effMC_e24e60_ICHEP2012_AFII_period0_LoosePP_eta, 20, MCefficienciesRel172ICHEP_AFII_e24vhi_medium1_LoosePP[0]);
  copyToVector(effMC_e24e60_ICHEP2012_AFII_period0_LoosePP_pt, 15, MCefficienciesRel172ICHEP_AFII_e24vhi_medium1_LoosePPET[0]);
  copyToVector(effMC_e24e60_ICHEP2012_AFII_period0_MediumPP_eta, 20, MCefficienciesRel172ICHEP_AFII_e24vhi_medium1_MediumPP[0]);
  copyToVector(effMC_e24e60_ICHEP2012_AFII_period0_MediumPP_pt, 15, MCefficienciesRel172ICHEP_AFII_e24vhi_medium1_MediumPPET[0]);
  copyToVector(effMC_e24e60_ICHEP2012_AFII_period0_TightPP_eta, 20, MCefficienciesRel172ICHEP_AFII_e24vhi_medium1_TightPP[0]);
  copyToVector(effMC_e24e60_ICHEP2012_AFII_period0_TightPP_pt, 15, MCefficienciesRel172ICHEP_AFII_e24vhi_medium1_TightPPET[0]);
  copyToVector(effMC_e24e60_ICHEP2012_AFII_period0_ML_eta, 20, MCefficienciesRel172ICHEP_AFII_e24vhi_medium1_ML[0]);
  copyToVector(effMC_e24e60_ICHEP2012_AFII_period0_ML_pt, 15, MCefficienciesRel172ICHEP_AFII_e24vhi_medium1_MLET[0]);

  copyToVector(sf_e24e60_ICHEP2012_AFII_period1_LoosePP_eta, 20, efficienciesRel172ICHEP_AFII_e24vhi_medium1_LoosePP[1]);
  copyToVector(errsf_e24e60_ICHEP2012_AFII_period1_LoosePP_eta, 20, uncertaintiesRel172ICHEP_AFII_e24vhi_medium1_LoosePP[1]);
  copyToVector(sf_e24e60_ICHEP2012_AFII_period1_LoosePP_pt, 15, efficienciesRel172ICHEP_AFII_e24vhi_medium1_LoosePPET[1]);
  copyToVector(errsf_e24e60_ICHEP2012_AFII_period1_LoosePP_pt, 15, uncertaintiesRel172ICHEP_AFII_e24vhi_medium1_LoosePPET[1]);

  copyToVector(sf_e24e60_ICHEP2012_AFII_period1_MediumPP_eta, 20, efficienciesRel172ICHEP_AFII_e24vhi_medium1_MediumPP[1]);
  copyToVector(errsf_e24e60_ICHEP2012_AFII_period1_MediumPP_eta, 20, uncertaintiesRel172ICHEP_AFII_e24vhi_medium1_MediumPP[1]);
  copyToVector(sf_e24e60_ICHEP2012_AFII_period1_MediumPP_pt, 15, efficienciesRel172ICHEP_AFII_e24vhi_medium1_MediumPPET[1]);
  copyToVector(errsf_e24e60_ICHEP2012_AFII_period1_MediumPP_pt, 15, uncertaintiesRel172ICHEP_AFII_e24vhi_medium1_MediumPPET[1]);

  copyToVector(sf_e24e60_ICHEP2012_AFII_period1_TightPP_eta, 20, efficienciesRel172ICHEP_AFII_e24vhi_medium1_TightPP[1]);
  copyToVector(errsf_e24e60_ICHEP2012_AFII_period1_TightPP_eta, 20, uncertaintiesRel172ICHEP_AFII_e24vhi_medium1_TightPP[1]);
  copyToVector(sf_e24e60_ICHEP2012_AFII_period1_TightPP_pt, 15, efficienciesRel172ICHEP_AFII_e24vhi_medium1_TightPPET[1]);
  copyToVector(errsf_e24e60_ICHEP2012_AFII_period1_TightPP_pt, 15, uncertaintiesRel172ICHEP_AFII_e24vhi_medium1_TightPPET[1]);

  copyToVector(sf_e24e60_ICHEP2012_AFII_period1_ML_eta, 20, efficienciesRel172ICHEP_AFII_e24vhi_medium1_ML[1]);
  copyToVector(errsf_e24e60_ICHEP2012_AFII_period1_ML_eta, 20, uncertaintiesRel172ICHEP_AFII_e24vhi_medium1_ML[1]);
  copyToVector(sf_e24e60_ICHEP2012_AFII_period1_ML_pt, 15, efficienciesRel172ICHEP_AFII_e24vhi_medium1_MLET[1]);
  copyToVector(errsf_e24e60_ICHEP2012_AFII_period1_ML_pt, 15, uncertaintiesRel172ICHEP_AFII_e24vhi_medium1_MLET[1]);

  copyToVector(effMC_e24e60_ICHEP2012_AFII_period1_LoosePP_eta, 20, MCefficienciesRel172ICHEP_AFII_e24vhi_medium1_LoosePP[1]);
  copyToVector(effMC_e24e60_ICHEP2012_AFII_period1_LoosePP_pt, 15, MCefficienciesRel172ICHEP_AFII_e24vhi_medium1_LoosePPET[1]);
  copyToVector(effMC_e24e60_ICHEP2012_AFII_period1_MediumPP_eta, 20, MCefficienciesRel172ICHEP_AFII_e24vhi_medium1_MediumPP[1]);
  copyToVector(effMC_e24e60_ICHEP2012_AFII_period1_MediumPP_pt, 15, MCefficienciesRel172ICHEP_AFII_e24vhi_medium1_MediumPPET[1]);
  copyToVector(effMC_e24e60_ICHEP2012_AFII_period1_TightPP_eta, 20, MCefficienciesRel172ICHEP_AFII_e24vhi_medium1_TightPP[1]);
  copyToVector(effMC_e24e60_ICHEP2012_AFII_period1_TightPP_pt, 15, MCefficienciesRel172ICHEP_AFII_e24vhi_medium1_TightPPET[1]);
  copyToVector(effMC_e24e60_ICHEP2012_AFII_period1_ML_eta, 20, MCefficienciesRel172ICHEP_AFII_e24vhi_medium1_ML[1]);
  copyToVector(effMC_e24e60_ICHEP2012_AFII_period1_ML_pt, 15, MCefficienciesRel172ICHEP_AFII_e24vhi_medium1_MLET[1]);

  copyToVector(sf_e24e60_ICHEP2012_AFII_period2_LoosePP_eta, 20, efficienciesRel172ICHEP_AFII_e24vhi_medium1_LoosePP[2]);
  copyToVector(errsf_e24e60_ICHEP2012_AFII_period2_LoosePP_eta, 20, uncertaintiesRel172ICHEP_AFII_e24vhi_medium1_LoosePP[2]);
  copyToVector(sf_e24e60_ICHEP2012_AFII_period2_LoosePP_pt, 15, efficienciesRel172ICHEP_AFII_e24vhi_medium1_LoosePPET[2]);
  copyToVector(errsf_e24e60_ICHEP2012_AFII_period2_LoosePP_pt, 15, uncertaintiesRel172ICHEP_AFII_e24vhi_medium1_LoosePPET[2]);

  copyToVector(sf_e24e60_ICHEP2012_AFII_period2_MediumPP_eta, 20, efficienciesRel172ICHEP_AFII_e24vhi_medium1_MediumPP[2]);
  copyToVector(errsf_e24e60_ICHEP2012_AFII_period2_MediumPP_eta, 20, uncertaintiesRel172ICHEP_AFII_e24vhi_medium1_MediumPP[2]);
  copyToVector(sf_e24e60_ICHEP2012_AFII_period2_MediumPP_pt, 15, efficienciesRel172ICHEP_AFII_e24vhi_medium1_MediumPPET[2]);
  copyToVector(errsf_e24e60_ICHEP2012_AFII_period2_MediumPP_pt, 15, uncertaintiesRel172ICHEP_AFII_e24vhi_medium1_MediumPPET[2]);

  copyToVector(sf_e24e60_ICHEP2012_AFII_period2_TightPP_eta, 20, efficienciesRel172ICHEP_AFII_e24vhi_medium1_TightPP[2]);
  copyToVector(errsf_e24e60_ICHEP2012_AFII_period2_TightPP_eta, 20, uncertaintiesRel172ICHEP_AFII_e24vhi_medium1_TightPP[2]);
  copyToVector(sf_e24e60_ICHEP2012_AFII_period2_TightPP_pt, 15, efficienciesRel172ICHEP_AFII_e24vhi_medium1_TightPPET[2]);
  copyToVector(errsf_e24e60_ICHEP2012_AFII_period2_TightPP_pt, 15, uncertaintiesRel172ICHEP_AFII_e24vhi_medium1_TightPPET[2]);

  copyToVector(sf_e24e60_ICHEP2012_AFII_period2_ML_eta, 20, efficienciesRel172ICHEP_AFII_e24vhi_medium1_ML[2]);
  copyToVector(errsf_e24e60_ICHEP2012_AFII_period2_ML_eta, 20, uncertaintiesRel172ICHEP_AFII_e24vhi_medium1_ML[2]);
  copyToVector(sf_e24e60_ICHEP2012_AFII_period2_ML_pt, 15, efficienciesRel172ICHEP_AFII_e24vhi_medium1_MLET[2]);
  copyToVector(errsf_e24e60_ICHEP2012_AFII_period2_ML_pt, 15, uncertaintiesRel172ICHEP_AFII_e24vhi_medium1_MLET[2]);

  copyToVector(effMC_e24e60_ICHEP2012_AFII_period2_LoosePP_eta, 20, MCefficienciesRel172ICHEP_AFII_e24vhi_medium1_LoosePP[2]);
  copyToVector(effMC_e24e60_ICHEP2012_AFII_period2_LoosePP_pt, 15, MCefficienciesRel172ICHEP_AFII_e24vhi_medium1_LoosePPET[2]);
  copyToVector(effMC_e24e60_ICHEP2012_AFII_period2_MediumPP_eta, 20, MCefficienciesRel172ICHEP_AFII_e24vhi_medium1_MediumPP[2]);
  copyToVector(effMC_e24e60_ICHEP2012_AFII_period2_MediumPP_pt, 15, MCefficienciesRel172ICHEP_AFII_e24vhi_medium1_MediumPPET[2]);
  copyToVector(effMC_e24e60_ICHEP2012_AFII_period2_TightPP_eta, 20, MCefficienciesRel172ICHEP_AFII_e24vhi_medium1_TightPP[2]);
  copyToVector(effMC_e24e60_ICHEP2012_AFII_period2_TightPP_pt, 15, MCefficienciesRel172ICHEP_AFII_e24vhi_medium1_TightPPET[2]);
  copyToVector(effMC_e24e60_ICHEP2012_AFII_period2_ML_eta, 20, MCefficienciesRel172ICHEP_AFII_e24vhi_medium1_ML[2]);
  copyToVector(effMC_e24e60_ICHEP2012_AFII_period2_ML_pt, 15, MCefficienciesRel172ICHEP_AFII_e24vhi_medium1_MLET[2]);

  // electron trigger e12Tvh_loose1 vs. different offline and 3 data periods, plus MC efficiencies!
const float sf_e12l_ICHEP2012_AFII_period0_LoosePP_eta[] = {1.0088, 1.0008, 0.9894, 1.0089, 0.925, 1.0004, 1.0018, 0.9826, 0.9989, 0.9988, 1.0007, 0.9994, 0.9988, 1.0015, 1.0032, 0.9691, 1.0069, 0.9921, 0.9974, 0.9839};
const float errsf_e12l_ICHEP2012_AFII_period0_LoosePP_eta[] = {0.0125603, 0.0118191, 0.012093, 0.0108853, 0.0255392, 0.0101789, 0.0101119, 0.0101435, 0.0101119, 0.0100717, 0.0101272, 0.0100975, 0.0101607, 0.0101435, 0.0102391, 0.0237118, 0.0109659, 0.0116619, 0.0113177, 0.0125};

const float effMC_e12l_ICHEP2012_AFII_period0_LoosePP_eta[] = {0.875, 0.9441, 0.9395, 0.9432, 0.8444, 0.973, 0.9827, 0.9858, 0.9876, 0.9876, 0.9876, 0.9879, 0.9861, 0.9831, 0.9715, 0.8426, 0.9448, 0.9392, 0.945, 0.8866};
const float sf_e12l_ICHEP2012_AFII_period0_LoosePP_pt[] = {0.976665, 0.979769, 0.991886, 0.994089, 0.999898, 1.0019, 1.0027, 1.0028, 1.0023, 1.0012, 1.0007, 1.0037, 0.991886, 0.999096};
const float errsf_e12l_ICHEP2012_AFII_period0_LoosePP_pt[] = {0.0366941, 0.0218959, 0.00560784, 0.00270378, 0.00190266, 0.00190266, 0.00260364, 0.00290406, 0.0040056, 0.00380532, 0.00370518, 0.00310434, 0.0040056, 0.00971358};

const float effMC_e12l_ICHEP2012_AFII_period0_LoosePP_pt[] = {0.810737, 0.880594, 0.921259, 0.951783, 0.970221, 0.983434, 0.992141, 1.00085, 1.01027, 1.01222, 1.01375, 1.01027, 1.01447, 1.01211};
const float sf_e12l_ICHEP2012_AFII_period0_MediumPP_eta[] = {1.0294, 1.0028, 0.9909, 1.0081, 0.9452, 0.9997, 1.0006, 0.9827, 0.999, 0.9991, 1.0011, 0.9995, 0.9981, 1.0011, 1.0031, 0.9685, 1.0061, 0.9912, 0.998, 1.0042};
const float errsf_e12l_ICHEP2012_AFII_period0_MediumPP_eta[] = {0.0125, 0.0119269, 0.0122642, 0.0108853, 0.0233497, 0.0101435, 0.0100975, 0.0101435, 0.0101119, 0.0100717, 0.0101119, 0.0100841, 0.0101435, 0.0101272, 0.0101789, 0.0238025, 0.0108853, 0.0117661, 0.0113649, 0.0125};

const float effMC_e12l_ICHEP2012_AFII_period0_MediumPP_eta[] = {0.8793, 0.9476, 0.946, 0.9505, 0.8952, 0.9785, 0.9867, 0.9886, 0.9895, 0.9896, 0.9895, 0.9897, 0.989, 0.9863, 0.9763, 0.8822, 0.9521, 0.9461, 0.949, 0.8901};
const float sf_e12l_ICHEP2012_AFII_period0_MediumPP_pt[] = {1.00808, 0.995612, 1.0008, 1.0009, 1.0023, 1.0004, 1.0004, 1.0001, 0.998605, 0.997507, 0.997108, 0.999702, 0.988828, 0.991921};
const float errsf_e12l_ICHEP2012_AFII_period0_MediumPP_pt[] = {0.0331764, 0.0210559, 0.00369115, 0.00209498, 0.00159617, 0.00189545, 0.00269354, 0.00309258, 0.00409019, 0.00389067, 0.00369115, 0.00309258, 0.00399043, 0.00957703};

const float effMC_e12l_ICHEP2012_AFII_period0_MediumPP_pt[] = {0.823197, 0.891277, 0.931348, 0.958028, 0.974691, 0.985935, 0.9935, 1.00086, 1.00894, 1.01047, 1.0118, 1.00842, 1.01241, 1.01354};
const float sf_e12l_ICHEP2012_AFII_period0_ML_eta[] = {1.0169, 1.001, 0.9911, 1.0083, 0.9546, 0.9976, 1.001, 0.9823, 0.9983, 0.9994, 1.0008, 0.9997, 0.9995, 1.0006, 1.0011, 0.9859, 1.0059, 0.9928, 0.9973, 0.9872};
const float errsf_e12l_ICHEP2012_AFII_period0_ML_eta[] = {0.0122066, 0.0117661, 0.0119269, 0.0107703, 0.0266475, 0.0101789, 0.0100975, 0.0101435, 0.0100841, 0.0100717, 0.0101119, 0.0100717, 0.0101119, 0.0101119, 0.010198, 0.0248966, 0.0108462, 0.0116108, 0.0112254, 0.0122642};

const float effMC_e12l_ICHEP2012_AFII_period0_ML_eta[] = {0.8863, 0.944, 0.9397, 0.9446, 0.8136, 0.9746, 0.9851, 0.986, 0.9868, 0.9864, 0.9861, 0.9866, 0.9862, 0.985, 0.9724, 0.8186, 0.9462, 0.9402, 0.9451, 0.8987};
const float sf_e12l_ICHEP2012_AFII_period0_ML_pt[] = {0.952277, 0.980323, 0.992343, 0.997452, 1.00066, 1.00136, 1.00176, 1.00146, 1.00146, 1.00016, 0.999856, 1.00206, 0.993946, 0.996049};
const float errsf_e12l_ICHEP2012_AFII_period0_ML_pt[] = {0.0397271, 0.0219792, 0.00450746, 0.00280464, 0.00150249, 0.00180299, 0.00240398, 0.00280464, 0.00390647, 0.00370614, 0.00340564, 0.00300498, 0.00360597, 0.00911509};

const float effMC_e12l_ICHEP2012_AFII_period0_ML_pt[] = {0.793408, 0.879703, 0.919225, 0.955071, 0.973454, 0.985607, 0.993266, 1.00093, 1.0092, 1.01114, 1.01236, 1.0091, 1.01226, 1.01247};
const float sf_e12l_ICHEP2012_AFII_period0_TightPP_eta[] = {1.0246, 1.0002, 0.9884, 1.0019, 0.9457, 0.9984, 0.9996, 0.9814, 0.9982, 0.9988, 1.001, 0.9988, 0.9976, 0.9996, 0.9988, 0.9524, 1.0022, 0.9882, 0.9967, 1.0035};
const float errsf_e12l_ICHEP2012_AFII_period0_TightPP_eta[] = {0.0109659, 0.0100717, 0.0101607, 0.0100603, 0.022809, 0.0100245, 0.010008, 0.0100499, 0.0100045, 0.0100319, 0.010018, 0.0100045, 0.010018, 0.010008, 0.0100245, 0.0232594, 0.0100603, 0.0101789, 0.0100717, 0.0110923};

const float effMC_e12l_ICHEP2012_AFII_period0_TightPP_eta[] = {0.9052, 0.9707, 0.9716, 0.9728, 0.9241, 0.9921, 0.9948, 0.995, 0.9947, 0.9947, 0.9947, 0.9948, 0.9949, 0.9944, 0.9904, 0.9231, 0.9739, 0.9717, 0.9727, 0.9161};
const float sf_e12l_ICHEP2012_AFII_period0_TightPP_pt[] = {1.00959, 0.996198, 1.0001, 1.00099, 1.00239, 0.999995, 0.999995, 1.0004, 0.999696, 0.998996, 0.998796, 1.00209, 0.989902, 0.991301};
const float errsf_e12l_ICHEP2012_AFII_period0_TightPP_pt[] = {0.0328942, 0.0208796, 0.00289825, 0.00139915, 0.000799517, 0.000599638, 0.000399758, 0.000399758, 0.000399758, 0.000599638, 0.000899456, 0.00239855, 0.0037977, 0.00839493};

const float effMC_e12l_ICHEP2012_AFII_period0_TightPP_pt[] = {0.856965, 0.92799, 0.960966, 0.979432, 0.989579, 0.995159, 0.999015, 1.00155, 1.00419, 1.00399, 1.005, 1.00125, 1.00551, 1.00855};
const float sf_e12l_ICHEP2012_AFII_period1_LoosePP_eta[] = {0.9974, 0.9995, 0.9833, 1.004, 0.8934, 1.002, 1.0002, 0.9823, 0.9979, 0.9992, 0.999, 0.9989, 0.9992, 0.9997, 1.0022, 0.944, 1.0069, 0.992, 1.0006, 0.9852};
const float errsf_e12l_ICHEP2012_AFII_period1_LoosePP_eta[] = {0.012381, 0.0116619, 0.0114612, 0.0108079, 0.0207663, 0.0102181, 0.0100841, 0.0101119, 0.0100975, 0.0101272, 0.0100603, 0.0101119, 0.0100841, 0.0100975, 0.0101607, 0.0200689, 0.0106977, 0.0113649, 0.0114612, 0.0119817};

const float effMC_e12l_ICHEP2012_AFII_period1_LoosePP_eta[] = {0.875, 0.9441, 0.9395, 0.9432, 0.8444, 0.973, 0.9827, 0.9858, 0.9876, 0.9876, 0.9876, 0.9879, 0.9861, 0.9831, 0.9715, 0.8426, 0.9448, 0.9392, 0.945, 0.8866};
const float sf_e12l_ICHEP2012_AFII_period1_LoosePP_pt[] = {0.971629, 0.984966, 0.991685, 0.99349, 0.997902, 1.00211, 1.00302, 1.00302, 1.00201, 1.00181, 1.00211, 1.00141, 1.00101, 1.00803};
const float errsf_e12l_ICHEP2012_AFII_period1_LoosePP_pt[] = {0.0335599, 0.0223285, 0.00511436, 0.00230648, 0.00150422, 0.00170479, 0.00210591, 0.0027076, 0.0038107, 0.00431211, 0.00391098, 0.00330929, 0.00361014, 0.00481352};

const float effMC_e12l_ICHEP2012_AFII_period1_LoosePP_pt[] = {0.810264, 0.88008, 0.920721, 0.951228, 0.969655, 0.98286, 0.991562, 1.00026, 1.00968, 1.01163, 1.01316, 1.00968, 1.01388, 1.01152};
const float sf_e12l_ICHEP2012_AFII_period1_MediumPP_eta[] = {1.0128, 1.0013, 0.9831, 1.0035, 0.8995, 1.0011, 0.9999, 0.9822, 0.998, 0.9991, 0.9993, 0.999, 0.9984, 1, 1.0021, 0.9601, 1.0061, 0.9932, 1.0016, 1.0092};
const float errsf_e12l_ICHEP2012_AFII_period1_MediumPP_eta[] = {0.0125, 0.0118191, 0.0115603, 0.0108079, 0.0201556, 0.0101607, 0.0100603, 0.0100975, 0.0100717, 0.0101272, 0.0100499, 0.0100975, 0.0100841, 0.0100841, 0.0101435, 0.0183619, 0.0106977, 0.0115104, 0.0115603, 0.0119269};

const float effMC_e12l_ICHEP2012_AFII_period1_MediumPP_eta[] = {0.8793, 0.9476, 0.946, 0.9505, 0.8952, 0.9785, 0.9867, 0.9886, 0.9895, 0.9896, 0.9895, 0.9897, 0.989, 0.9863, 0.9763, 0.8822, 0.9521, 0.9461, 0.949, 0.8901};
const float sf_e12l_ICHEP2012_AFII_period1_MediumPP_pt[] = {0.995148, 1.00204, 1.00184, 0.999442, 1.00054, 1.00094, 1.00104, 1.00004, 0.998244, 0.997844, 0.998044, 0.997046, 0.996846, 1.00044};
const float errsf_e12l_ICHEP2012_AFII_period1_MediumPP_pt[] = {0.0316502, 0.0207672, 0.00269634, 0.00149796, 0.00129824, 0.00179756, 0.00229688, 0.00289607, 0.00389471, 0.00439403, 0.00389471, 0.00339539, 0.00359512, 0.00459376};

const float effMC_e12l_ICHEP2012_AFII_period1_MediumPP_pt[] = {0.82296, 0.891021, 0.93108, 0.957753, 0.97441, 0.985651, 0.993213, 1.00057, 1.00864, 1.01018, 1.01151, 1.00813, 1.01212, 1.01324};
const float sf_e12l_ICHEP2012_AFII_period1_ML_eta[] = {1.0023, 1.0005, 0.9835, 1.004, 0.9225, 0.9993, 0.9993, 0.9817, 0.997, 0.999, 0.9986, 0.9988, 0.9994, 0.9996, 0.9997, 0.9705, 1.0063, 0.9936, 1.001, 0.9973};
const float errsf_e12l_ICHEP2012_AFII_period1_ML_eta[] = {0.0122642, 0.0115603, 0.0113649, 0.0106977, 0.0207663, 0.010198, 0.0100603, 0.0100717, 0.0100603, 0.0100975, 0.0100499, 0.0100841, 0.0100717, 0.0100841, 0.0101435, 0.0201556, 0.0106283, 0.0112712, 0.0113649, 0.0117661};

const float effMC_e12l_ICHEP2012_AFII_period1_ML_eta[] = {0.8863, 0.944, 0.9397, 0.9446, 0.8136, 0.9746, 0.9851, 0.986, 0.9868, 0.9864, 0.9861, 0.9866, 0.9862, 0.985, 0.9724, 0.8186, 0.9462, 0.9402, 0.9451, 0.8987};
const float sf_e12l_ICHEP2012_AFII_period1_ML_pt[] = {0.940419, 0.980626, 0.992859, 0.997371, 0.999276, 1.00118, 1.00208, 1.00168, 1.00068, 1.00058, 1.00048, 1.00228, 1.00068, 1.00459};
const float errsf_e12l_ICHEP2012_AFII_period1_ML_pt[] = {0.0357545, 0.0221958, 0.00481289, 0.0019051, 0.00130349, 0.0016043, 0.00210564, 0.00260698, 0.00370994, 0.00421128, 0.00360967, 0.00300806, 0.00310832, 0.00471262};

const float effMC_e12l_ICHEP2012_AFII_period1_ML_pt[] = {0.793146, 0.879413, 0.918922, 0.954756, 0.973132, 0.985281, 0.992938, 1.00059, 1.00886, 1.0108, 1.01203, 1.00876, 1.01193, 1.01213};
const float sf_e12l_ICHEP2012_AFII_period1_TightPP_eta[] = {1.0088, 0.9975, 0.9818, 0.9993, 0.9057, 0.9976, 0.9985, 0.9812, 0.9976, 0.9988, 0.9991, 0.9985, 0.9974, 0.999, 0.9986, 0.9428, 1.001, 0.9897, 0.9977, 1.0051};
const float errsf_e12l_ICHEP2012_AFII_period1_TightPP_eta[] = {0.0105948, 0.0100404, 0.0100975, 0.0100404, 0.0192938, 0.0100125, 0.0100045, 0.0100245, 0.0100045, 0.010018, 0.010018, 0.0100045, 0.010008, 0.0100045, 0.0100125, 0.0179446, 0.0100404, 0.0100841, 0.0100404, 0.0105622};

const float effMC_e12l_ICHEP2012_AFII_period1_TightPP_eta[] = {0.9052, 0.9707, 0.9716, 0.9728, 0.9241, 0.9921, 0.9948, 0.995, 0.9947, 0.9947, 0.9947, 0.9948, 0.9949, 0.9944, 0.9904, 0.9231, 0.9739, 0.9717, 0.9727, 0.9161};
const float sf_e12l_ICHEP2012_AFII_period1_TightPP_pt[] = {1.00241, 0.999607, 1.00001, 0.999007, 1.00021, 1.00071, 1.00031, 1.00041, 0.999407, 0.999107, 0.999607, 0.999507, 0.998307, 0.999607};
const float errsf_e12l_ICHEP2012_AFII_period1_TightPP_pt[] = {0.0316559, 0.0204163, 0.00210086, 0.00100041, 0.000700285, 0.000400163, 0.000300122, 0.000300122, 0.000300122, 0.000500204, 0.000600245, 0.00180073, 0.00210086, 0.00420171};

const float effMC_e12l_ICHEP2012_AFII_period1_TightPP_pt[] = {0.857017, 0.928046, 0.961024, 0.979492, 0.989639, 0.99522, 0.999075, 1.00161, 1.00425, 1.00405, 1.00506, 1.00131, 1.00557, 1.00861};
const float sf_e12l_ICHEP2012_AFII_period2_LoosePP_eta[] = {0.9893, 1.0023, 0.9866, 1.0058, 0.9376, 1.0017, 1.0005, 0.9811, 0.9976, 0.999, 0.9991, 0.9994, 0.999, 1.0002, 1.0033, 0.9331, 1.0068, 0.9932, 1.0019, 0.9857};
const float errsf_e12l_ICHEP2012_AFII_period2_LoosePP_eta[] = {0.0119817, 0.0113649, 0.0113177, 0.0108079, 0.0197231, 0.0101789, 0.0100975, 0.0100841, 0.0101272, 0.0100975, 0.0100841, 0.0100841, 0.0101272, 0.0100841, 0.0102391, 0.0182781, 0.0108853, 0.0114612, 0.0118191, 0.0114127};

const float effMC_e12l_ICHEP2012_AFII_period2_LoosePP_eta[] = {0.875, 0.9441, 0.9395, 0.9432, 0.8444, 0.973, 0.9827, 0.9858, 0.9876, 0.9876, 0.9876, 0.9879, 0.9861, 0.9831, 0.9715, 0.8426, 0.9448, 0.9392, 0.945, 0.8866};
const float sf_e12l_ICHEP2012_AFII_period2_LoosePP_pt[] = {0.966127, 0.977752, 0.993086, 0.998097, 0.9993, 1.0014, 1.00261, 1.00281, 1.0014, 1.00171, 1.001, 1.0016, 0.993888, 1.00341};
const float errsf_e12l_ICHEP2012_AFII_period2_LoosePP_pt[] = {0.0324721, 0.0217781, 0.00501103, 0.00240529, 0.00150331, 0.00170375, 0.00210463, 0.00280618, 0.00400882, 0.00430949, 0.0039086, 0.0034075, 0.00370816, 0.00721588};

const float effMC_e12l_ICHEP2012_AFII_period2_LoosePP_pt[] = {0.810701, 0.880556, 0.921219, 0.951742, 0.970178, 0.983391, 0.992097, 1.0008, 1.01023, 1.01217, 1.01371, 1.01023, 1.01443, 1.01207};
const float sf_e12l_ICHEP2012_AFII_period2_MediumPP_eta[] = {1.0092, 1.0039, 0.9878, 1.0058, 0.919, 1.0015, 0.9995, 0.9809, 0.9978, 0.9988, 0.9999, 0.9992, 0.9984, 1.0003, 1.0038, 0.9315, 1.0061, 0.993, 1.0025, 1.0084};
const float errsf_e12l_ICHEP2012_AFII_period2_MediumPP_eta[] = {0.012037, 0.0114612, 0.0115104, 0.0108079, 0.0183619, 0.0101607, 0.0100717, 0.0100717, 0.0100975, 0.0100841, 0.0100841, 0.0100717, 0.0101119, 0.0100717, 0.010198, 0.0180278, 0.0108853, 0.0115603, 0.0119269, 0.0114127};

const float effMC_e12l_ICHEP2012_AFII_period2_MediumPP_eta[] = {0.8793, 0.9476, 0.946, 0.9505, 0.8952, 0.9785, 0.9867, 0.9886, 0.9895, 0.9896, 0.9895, 0.9897, 0.989, 0.9863, 0.9763, 0.8822, 0.9521, 0.9461, 0.949, 0.8901};
const float sf_e12l_ICHEP2012_AFII_period2_MediumPP_pt[] = {0.984494, 0.997759, 1.00105, 1.00294, 1.00125, 0.999654, 0.999654, 0.998856, 0.996961, 0.996861, 0.996263, 0.996861, 0.989281, 0.995165};
const float errsf_e12l_ICHEP2012_AFII_period2_MediumPP_pt[] = {0.0314308, 0.020565, 0.0024934, 0.00149604, 0.00119683, 0.00169551, 0.00219419, 0.00289234, 0.00408917, 0.00428865, 0.0038897, 0.00339102, 0.00369023, 0.00718099};

const float effMC_e12l_ICHEP2012_AFII_period2_MediumPP_pt[] = {0.824061, 0.892212, 0.932326, 0.959034, 0.975714, 0.98697, 0.994542, 1.00191, 1.00999, 1.01153, 1.01286, 1.00948, 1.01347, 1.0146};
const float sf_e12l_ICHEP2012_AFII_period2_ML_eta[] = {0.9966, 1.0031, 0.9869, 1.0056, 0.9625, 1, 0.999, 0.9809, 0.9973, 0.9988, 0.9993, 0.9991, 0.9994, 0.9996, 1.0018, 0.9616, 1.0051, 0.993, 1.0019, 0.9995};
const float errsf_e12l_ICHEP2012_AFII_period2_ML_eta[] = {0.0117137, 0.0112712, 0.0112254, 0.0107336, 0.0204167, 0.0101607, 0.0100603, 0.0100603, 0.0100975, 0.0100717, 0.0100603, 0.0100603, 0.0100975, 0.0100603, 0.010198, 0.0184459, 0.0107703, 0.0113177, 0.0117137, 0.0113649};

const float effMC_e12l_ICHEP2012_AFII_period2_ML_eta[] = {0.8863, 0.944, 0.9397, 0.9446, 0.8136, 0.9746, 0.9851, 0.986, 0.9868, 0.9864, 0.9861, 0.9866, 0.9862, 0.985, 0.9724, 0.8186, 0.9462, 0.9402, 0.9451, 0.8987};
const float sf_e12l_ICHEP2012_AFII_period2_ML_pt[] = {0.932294, 0.976589, 0.990218, 1.00084, 1.00004, 1.00084, 1.00174, 1.00134, 1.00044, 1.00044, 0.999738, 1.00194, 0.994627, 1.00154};
const float errsf_e12l_ICHEP2012_AFII_period2_ML_pt[] = {0.0353192, 0.021296, 0.004209, 0.00170364, 0.00120257, 0.00150321, 0.00200429, 0.00270579, 0.00380814, 0.00410879, 0.00370793, 0.00310664, 0.00370793, 0.007015};

const float effMC_e12l_ICHEP2012_AFII_period2_ML_pt[] = {0.793969, 0.880326, 0.919876, 0.955747, 0.974143, 0.986304, 0.993969, 1.00163, 1.00991, 1.01185, 1.01308, 1.00981, 1.01298, 1.01318};
const float sf_e12l_ICHEP2012_AFII_period2_TightPP_eta[] = {1.0046, 0.9994, 0.9834, 1.0009, 0.9296, 0.9988, 0.9978, 0.9804, 0.9973, 0.9987, 0.9992, 0.9987, 0.9976, 0.9988, 1.0002, 0.9303, 1.0012, 0.9911, 0.9986, 1.0077};
const float errsf_e12l_ICHEP2012_AFII_period2_TightPP_eta[] = {0.0105304, 0.0100319, 0.0100841, 0.0100319, 0.0169614, 0.010008, 0.0100045, 0.0100245, 0.0100045, 0.0100125, 0.0100125, 0.010002, 0.010008, 0.0100045, 0.0100125, 0.0171234, 0.0100404, 0.0100717, 0.0100319, 0.0104695};

const float effMC_e12l_ICHEP2012_AFII_period2_TightPP_eta[] = {0.9052, 0.9707, 0.9716, 0.9728, 0.9241, 0.9921, 0.9948, 0.995, 0.9947, 0.9947, 0.9947, 0.9948, 0.9949, 0.9944, 0.9904, 0.9231, 0.9739, 0.9717, 0.9727, 0.9161};
const float sf_e12l_ICHEP2012_AFII_period2_TightPP_pt[] = {0.991484, 0.990884, 1.00079, 1.00279, 1.00159, 1.00029, 1.00049, 1.00039, 0.998987, 0.999487, 0.998987, 0.999587, 0.992685, 0.995486};
const float errsf_e12l_ICHEP2012_AFII_period2_TightPP_pt[] = {0.0312367, 0.0203963, 0.00190055, 0.000900258, 0.000600172, 0.000400115, 0.000300086, 0.000300086, 0.000300086, 0.000400115, 0.000600172, 0.00170049, 0.00240069, 0.00480138};

const float effMC_e12l_ICHEP2012_AFII_period2_TightPP_pt[] = {0.856995, 0.928022, 0.960999, 0.979466, 0.989613, 0.995194, 0.99905, 1.00159, 1.00422, 1.00402, 1.00504, 1.00128, 1.00554, 1.00859};

 efficienciesRel172ICHEP_AFII_e12Tvh_loose1_LoosePP.resize(3);
 uncertaintiesRel172ICHEP_AFII_e12Tvh_loose1_LoosePP.resize(3);
 efficienciesRel172ICHEP_AFII_e12Tvh_loose1_LoosePPET.resize(3);
 uncertaintiesRel172ICHEP_AFII_e12Tvh_loose1_LoosePPET.resize(3);
 
 MCefficienciesRel172ICHEP_AFII_e12Tvh_loose1_LoosePP.resize(3);
 MCefficienciesRel172ICHEP_AFII_e12Tvh_loose1_LoosePPET.resize(3);
 
 efficienciesRel172ICHEP_AFII_e12Tvh_loose1_MediumPP.resize(3);
 uncertaintiesRel172ICHEP_AFII_e12Tvh_loose1_MediumPP.resize(3);
 efficienciesRel172ICHEP_AFII_e12Tvh_loose1_MediumPPET.resize(3);
 uncertaintiesRel172ICHEP_AFII_e12Tvh_loose1_MediumPPET.resize(3);
 
 MCefficienciesRel172ICHEP_AFII_e12Tvh_loose1_MediumPP.resize(3);
 MCefficienciesRel172ICHEP_AFII_e12Tvh_loose1_MediumPPET.resize(3);
 
 efficienciesRel172ICHEP_AFII_e12Tvh_loose1_TightPP.resize(3);
 uncertaintiesRel172ICHEP_AFII_e12Tvh_loose1_TightPP.resize(3);
 efficienciesRel172ICHEP_AFII_e12Tvh_loose1_TightPPET.resize(3);
 uncertaintiesRel172ICHEP_AFII_e12Tvh_loose1_TightPPET.resize(3);
 
 MCefficienciesRel172ICHEP_AFII_e12Tvh_loose1_TightPP.resize(3);
 MCefficienciesRel172ICHEP_AFII_e12Tvh_loose1_TightPPET.resize(3);

 efficienciesRel172ICHEP_AFII_e12Tvh_loose1_ML.resize(3);
 uncertaintiesRel172ICHEP_AFII_e12Tvh_loose1_ML.resize(3);
 efficienciesRel172ICHEP_AFII_e12Tvh_loose1_MLET.resize(3);
 uncertaintiesRel172ICHEP_AFII_e12Tvh_loose1_MLET.resize(3);
 
 MCefficienciesRel172ICHEP_AFII_e12Tvh_loose1_ML.resize(3);
 MCefficienciesRel172ICHEP_AFII_e12Tvh_loose1_MLET.resize(3);

  copyToVector(sf_e12l_ICHEP2012_AFII_period0_LoosePP_eta, 20, efficienciesRel172ICHEP_AFII_e12Tvh_loose1_LoosePP[0]);
  copyToVector(errsf_e12l_ICHEP2012_AFII_period0_LoosePP_eta, 20, uncertaintiesRel172ICHEP_AFII_e12Tvh_loose1_LoosePP[0]);
  copyToVector(sf_e12l_ICHEP2012_AFII_period0_LoosePP_pt, 14, efficienciesRel172ICHEP_AFII_e12Tvh_loose1_LoosePPET[0]);
  copyToVector(errsf_e12l_ICHEP2012_AFII_period0_LoosePP_pt, 14, uncertaintiesRel172ICHEP_AFII_e12Tvh_loose1_LoosePPET[0]);

  copyToVector(sf_e12l_ICHEP2012_AFII_period0_MediumPP_eta, 20, efficienciesRel172ICHEP_AFII_e12Tvh_loose1_MediumPP[0]);
  copyToVector(errsf_e12l_ICHEP2012_AFII_period0_MediumPP_eta, 20, uncertaintiesRel172ICHEP_AFII_e12Tvh_loose1_MediumPP[0]);
  copyToVector(sf_e12l_ICHEP2012_AFII_period0_MediumPP_pt, 14, efficienciesRel172ICHEP_AFII_e12Tvh_loose1_MediumPPET[0]);
  copyToVector(errsf_e12l_ICHEP2012_AFII_period0_MediumPP_pt, 14, uncertaintiesRel172ICHEP_AFII_e12Tvh_loose1_MediumPPET[0]);

  copyToVector(sf_e12l_ICHEP2012_AFII_period0_TightPP_eta, 20, efficienciesRel172ICHEP_AFII_e12Tvh_loose1_TightPP[0]);
  copyToVector(errsf_e12l_ICHEP2012_AFII_period0_TightPP_eta, 20, uncertaintiesRel172ICHEP_AFII_e12Tvh_loose1_TightPP[0]);
  copyToVector(sf_e12l_ICHEP2012_AFII_period0_TightPP_pt, 14, efficienciesRel172ICHEP_AFII_e12Tvh_loose1_TightPPET[0]);
  copyToVector(errsf_e12l_ICHEP2012_AFII_period0_TightPP_pt, 14, uncertaintiesRel172ICHEP_AFII_e12Tvh_loose1_TightPPET[0]);

  copyToVector(sf_e12l_ICHEP2012_AFII_period0_ML_eta, 20, efficienciesRel172ICHEP_AFII_e12Tvh_loose1_ML[0]);
  copyToVector(errsf_e12l_ICHEP2012_AFII_period0_ML_eta, 20, uncertaintiesRel172ICHEP_AFII_e12Tvh_loose1_ML[0]);
  copyToVector(sf_e12l_ICHEP2012_AFII_period0_ML_pt, 14, efficienciesRel172ICHEP_AFII_e12Tvh_loose1_MLET[0]);
  copyToVector(errsf_e12l_ICHEP2012_AFII_period0_ML_pt, 14, uncertaintiesRel172ICHEP_AFII_e12Tvh_loose1_MLET[0]);

  copyToVector(effMC_e12l_ICHEP2012_AFII_period0_LoosePP_eta, 20, MCefficienciesRel172ICHEP_AFII_e12Tvh_loose1_LoosePP[0]);
  copyToVector(effMC_e12l_ICHEP2012_AFII_period0_LoosePP_pt, 14, MCefficienciesRel172ICHEP_AFII_e12Tvh_loose1_LoosePPET[0]);
  copyToVector(effMC_e12l_ICHEP2012_AFII_period0_MediumPP_eta, 20, MCefficienciesRel172ICHEP_AFII_e12Tvh_loose1_MediumPP[0]);
  copyToVector(effMC_e12l_ICHEP2012_AFII_period0_MediumPP_pt, 14, MCefficienciesRel172ICHEP_AFII_e12Tvh_loose1_MediumPPET[0]);
  copyToVector(effMC_e12l_ICHEP2012_AFII_period0_TightPP_eta, 20, MCefficienciesRel172ICHEP_AFII_e12Tvh_loose1_TightPP[0]);
  copyToVector(effMC_e12l_ICHEP2012_AFII_period0_TightPP_pt, 14, MCefficienciesRel172ICHEP_AFII_e12Tvh_loose1_TightPPET[0]);
  copyToVector(effMC_e12l_ICHEP2012_AFII_period0_ML_eta, 20, MCefficienciesRel172ICHEP_AFII_e12Tvh_loose1_ML[0]);
  copyToVector(effMC_e12l_ICHEP2012_AFII_period0_ML_pt, 14, MCefficienciesRel172ICHEP_AFII_e12Tvh_loose1_MLET[0]);

  copyToVector(sf_e12l_ICHEP2012_AFII_period1_LoosePP_eta, 20, efficienciesRel172ICHEP_AFII_e12Tvh_loose1_LoosePP[1]);
  copyToVector(errsf_e12l_ICHEP2012_AFII_period1_LoosePP_eta, 20, uncertaintiesRel172ICHEP_AFII_e12Tvh_loose1_LoosePP[1]);
  copyToVector(sf_e12l_ICHEP2012_AFII_period1_LoosePP_pt, 14, efficienciesRel172ICHEP_AFII_e12Tvh_loose1_LoosePPET[1]);
  copyToVector(errsf_e12l_ICHEP2012_AFII_period1_LoosePP_pt, 14, uncertaintiesRel172ICHEP_AFII_e12Tvh_loose1_LoosePPET[1]);

  copyToVector(sf_e12l_ICHEP2012_AFII_period1_MediumPP_eta, 20, efficienciesRel172ICHEP_AFII_e12Tvh_loose1_MediumPP[1]);
  copyToVector(errsf_e12l_ICHEP2012_AFII_period1_MediumPP_eta, 20, uncertaintiesRel172ICHEP_AFII_e12Tvh_loose1_MediumPP[1]);
  copyToVector(sf_e12l_ICHEP2012_AFII_period1_MediumPP_pt, 14, efficienciesRel172ICHEP_AFII_e12Tvh_loose1_MediumPPET[1]);
  copyToVector(errsf_e12l_ICHEP2012_AFII_period1_MediumPP_pt, 14, uncertaintiesRel172ICHEP_AFII_e12Tvh_loose1_MediumPPET[1]);

  copyToVector(sf_e12l_ICHEP2012_AFII_period1_TightPP_eta, 20, efficienciesRel172ICHEP_AFII_e12Tvh_loose1_TightPP[1]);
  copyToVector(errsf_e12l_ICHEP2012_AFII_period1_TightPP_eta, 20, uncertaintiesRel172ICHEP_AFII_e12Tvh_loose1_TightPP[1]);
  copyToVector(sf_e12l_ICHEP2012_AFII_period1_TightPP_pt, 14, efficienciesRel172ICHEP_AFII_e12Tvh_loose1_TightPPET[1]);
  copyToVector(errsf_e12l_ICHEP2012_AFII_period1_TightPP_pt, 14, uncertaintiesRel172ICHEP_AFII_e12Tvh_loose1_TightPPET[1]);

  copyToVector(sf_e12l_ICHEP2012_AFII_period1_ML_eta, 20, efficienciesRel172ICHEP_AFII_e12Tvh_loose1_ML[1]);
  copyToVector(errsf_e12l_ICHEP2012_AFII_period1_ML_eta, 20, uncertaintiesRel172ICHEP_AFII_e12Tvh_loose1_ML[1]);
  copyToVector(sf_e12l_ICHEP2012_AFII_period1_ML_pt, 14, efficienciesRel172ICHEP_AFII_e12Tvh_loose1_MLET[1]);
  copyToVector(errsf_e12l_ICHEP2012_AFII_period1_ML_pt, 14, uncertaintiesRel172ICHEP_AFII_e12Tvh_loose1_MLET[1]);

  copyToVector(effMC_e12l_ICHEP2012_AFII_period1_LoosePP_eta, 20, MCefficienciesRel172ICHEP_AFII_e12Tvh_loose1_LoosePP[1]);
  copyToVector(effMC_e12l_ICHEP2012_AFII_period1_LoosePP_pt, 14, MCefficienciesRel172ICHEP_AFII_e12Tvh_loose1_LoosePPET[1]);
  copyToVector(effMC_e12l_ICHEP2012_AFII_period1_MediumPP_eta, 20, MCefficienciesRel172ICHEP_AFII_e12Tvh_loose1_MediumPP[1]);
  copyToVector(effMC_e12l_ICHEP2012_AFII_period1_MediumPP_pt, 14, MCefficienciesRel172ICHEP_AFII_e12Tvh_loose1_MediumPPET[1]);
  copyToVector(effMC_e12l_ICHEP2012_AFII_period1_TightPP_eta, 20, MCefficienciesRel172ICHEP_AFII_e12Tvh_loose1_TightPP[1]);
  copyToVector(effMC_e12l_ICHEP2012_AFII_period1_TightPP_pt, 14, MCefficienciesRel172ICHEP_AFII_e12Tvh_loose1_TightPPET[1]);
  copyToVector(effMC_e12l_ICHEP2012_AFII_period1_ML_eta, 20, MCefficienciesRel172ICHEP_AFII_e12Tvh_loose1_ML[1]);
  copyToVector(effMC_e12l_ICHEP2012_AFII_period1_ML_pt, 14, MCefficienciesRel172ICHEP_AFII_e12Tvh_loose1_MLET[1]);

  copyToVector(sf_e12l_ICHEP2012_AFII_period2_LoosePP_eta, 20, efficienciesRel172ICHEP_AFII_e12Tvh_loose1_LoosePP[2]);
  copyToVector(errsf_e12l_ICHEP2012_AFII_period2_LoosePP_eta, 20, uncertaintiesRel172ICHEP_AFII_e12Tvh_loose1_LoosePP[2]);
  copyToVector(sf_e12l_ICHEP2012_AFII_period2_LoosePP_pt, 14, efficienciesRel172ICHEP_AFII_e12Tvh_loose1_LoosePPET[2]);
  copyToVector(errsf_e12l_ICHEP2012_AFII_period2_LoosePP_pt, 14, uncertaintiesRel172ICHEP_AFII_e12Tvh_loose1_LoosePPET[2]);

  copyToVector(sf_e12l_ICHEP2012_AFII_period2_MediumPP_eta, 20, efficienciesRel172ICHEP_AFII_e12Tvh_loose1_MediumPP[2]);
  copyToVector(errsf_e12l_ICHEP2012_AFII_period2_MediumPP_eta, 20, uncertaintiesRel172ICHEP_AFII_e12Tvh_loose1_MediumPP[2]);
  copyToVector(sf_e12l_ICHEP2012_AFII_period2_MediumPP_pt, 14, efficienciesRel172ICHEP_AFII_e12Tvh_loose1_MediumPPET[2]);
  copyToVector(errsf_e12l_ICHEP2012_AFII_period2_MediumPP_pt, 14, uncertaintiesRel172ICHEP_AFII_e12Tvh_loose1_MediumPPET[2]);

  copyToVector(sf_e12l_ICHEP2012_AFII_period2_TightPP_eta, 20, efficienciesRel172ICHEP_AFII_e12Tvh_loose1_TightPP[2]);
  copyToVector(errsf_e12l_ICHEP2012_AFII_period2_TightPP_eta, 20, uncertaintiesRel172ICHEP_AFII_e12Tvh_loose1_TightPP[2]);
  copyToVector(sf_e12l_ICHEP2012_AFII_period2_TightPP_pt, 14, efficienciesRel172ICHEP_AFII_e12Tvh_loose1_TightPPET[2]);
  copyToVector(errsf_e12l_ICHEP2012_AFII_period2_TightPP_pt, 14, uncertaintiesRel172ICHEP_AFII_e12Tvh_loose1_TightPPET[2]);

  copyToVector(sf_e12l_ICHEP2012_AFII_period2_ML_eta, 20, efficienciesRel172ICHEP_AFII_e12Tvh_loose1_ML[2]);
  copyToVector(errsf_e12l_ICHEP2012_AFII_period2_ML_eta, 20, uncertaintiesRel172ICHEP_AFII_e12Tvh_loose1_ML[2]);
  copyToVector(sf_e12l_ICHEP2012_AFII_period2_ML_pt, 14, efficienciesRel172ICHEP_AFII_e12Tvh_loose1_MLET[2]);
  copyToVector(errsf_e12l_ICHEP2012_AFII_period2_ML_pt, 14, uncertaintiesRel172ICHEP_AFII_e12Tvh_loose1_MLET[2]);

  copyToVector(effMC_e12l_ICHEP2012_AFII_period2_LoosePP_eta, 20, MCefficienciesRel172ICHEP_AFII_e12Tvh_loose1_LoosePP[2]);
  copyToVector(effMC_e12l_ICHEP2012_AFII_period2_LoosePP_pt, 14, MCefficienciesRel172ICHEP_AFII_e12Tvh_loose1_LoosePPET[2]);
  copyToVector(effMC_e12l_ICHEP2012_AFII_period2_MediumPP_eta, 20, MCefficienciesRel172ICHEP_AFII_e12Tvh_loose1_MediumPP[2]);
  copyToVector(effMC_e12l_ICHEP2012_AFII_period2_MediumPP_pt, 14, MCefficienciesRel172ICHEP_AFII_e12Tvh_loose1_MediumPPET[2]);
  copyToVector(effMC_e12l_ICHEP2012_AFII_period2_TightPP_eta, 20, MCefficienciesRel172ICHEP_AFII_e12Tvh_loose1_TightPP[2]);
  copyToVector(effMC_e12l_ICHEP2012_AFII_period2_TightPP_pt, 14, MCefficienciesRel172ICHEP_AFII_e12Tvh_loose1_TightPPET[2]);
  copyToVector(effMC_e12l_ICHEP2012_AFII_period2_ML_eta, 20, MCefficienciesRel172ICHEP_AFII_e12Tvh_loose1_ML[2]);
  copyToVector(effMC_e12l_ICHEP2012_AFII_period2_ML_pt, 14, MCefficienciesRel172ICHEP_AFII_e12Tvh_loose1_MLET[2]);


  // now come new additions for HCP 2012

  // forward electrons,  2011 update
   efficienciesRel17HCPForwardLoose.push_back(101.8);
   uncertaintiesRel17HCPForwardLoose.push_back(2.5);
   efficienciesRel17HCPForwardLoose.push_back(98.4);
   uncertaintiesRel17HCPForwardLoose.push_back(1.9);
   efficienciesRel17HCPForwardLoose.push_back(95.0);
   uncertaintiesRel17HCPForwardLoose.push_back(2.9);
   efficienciesRel17HCPForwardLoose.push_back(97.0);
   uncertaintiesRel17HCPForwardLoose.push_back(3.3);
   efficienciesRel17HCPForwardLoose.push_back(98.0);
   uncertaintiesRel17HCPForwardLoose.push_back(2.0);
   efficienciesRel17HCPForwardLoose.push_back(99.5);
   uncertaintiesRel17HCPForwardLoose.push_back(1.7);
   efficienciesRel17HCPForwardLoose.push_back(0.0);
   uncertaintiesRel17HCPForwardLoose.push_back(100.0);
   efficienciesRel17HCPForwardLoose.push_back(99.4);
   uncertaintiesRel17HCPForwardLoose.push_back(5.3);
   efficienciesRel17HCPForwardLoose.push_back(96.1);
   uncertaintiesRel17HCPForwardLoose.push_back(4.3);
   efficienciesRel17HCPForwardLoose.push_back(83.9);
   uncertaintiesRel17HCPForwardLoose.push_back(4.6);

   efficienciesRel17HCPForwardMedium.push_back(99.5);
   uncertaintiesRel17HCPForwardMedium.push_back(3.1);
   efficienciesRel17HCPForwardMedium.push_back(94.3);
   uncertaintiesRel17HCPForwardMedium.push_back(2.2);
   efficienciesRel17HCPForwardMedium.push_back(87.3);
   uncertaintiesRel17HCPForwardMedium.push_back(2.7);
   efficienciesRel17HCPForwardMedium.push_back(93.1);
   uncertaintiesRel17HCPForwardMedium.push_back(1.9);
   efficienciesRel17HCPForwardMedium.push_back(91.0);
   uncertaintiesRel17HCPForwardMedium.push_back(2.9);
   efficienciesRel17HCPForwardMedium.push_back(95.2);
   uncertaintiesRel17HCPForwardMedium.push_back(2.3);
   efficienciesRel17HCPForwardMedium.push_back(0.0);
   uncertaintiesRel17HCPForwardMedium.push_back(100.0);
   efficienciesRel17HCPForwardMedium.push_back(96.5);
   uncertaintiesRel17HCPForwardMedium.push_back(5.5);
   efficienciesRel17HCPForwardMedium.push_back(93.6);
   uncertaintiesRel17HCPForwardMedium.push_back(3.9);
   efficienciesRel17HCPForwardMedium.push_back(80.8);
   uncertaintiesRel17HCPForwardMedium.push_back(5.1);

   efficienciesRel17HCPForwardTight.push_back(98.9);
   uncertaintiesRel17HCPForwardTight.push_back(3.7);
   efficienciesRel17HCPForwardTight.push_back(91.6);
   uncertaintiesRel17HCPForwardTight.push_back(3.1);
   efficienciesRel17HCPForwardTight.push_back(79.3);
   uncertaintiesRel17HCPForwardTight.push_back(3.5);
   efficienciesRel17HCPForwardTight.push_back(87.5);
   uncertaintiesRel17HCPForwardTight.push_back(2.4);
   efficienciesRel17HCPForwardTight.push_back(88.7);
   uncertaintiesRel17HCPForwardTight.push_back(2.5);
   efficienciesRel17HCPForwardTight.push_back(92.7);
   uncertaintiesRel17HCPForwardTight.push_back(2.6);
   efficienciesRel17HCPForwardTight.push_back(0.0);
   uncertaintiesRel17HCPForwardTight.push_back(100.0);
   efficienciesRel17HCPForwardTight.push_back(93.4);
   uncertaintiesRel17HCPForwardTight.push_back(7.9);
   efficienciesRel17HCPForwardTight.push_back(91.6);
   uncertaintiesRel17HCPForwardTight.push_back(4.1);
   efficienciesRel17HCPForwardTight.push_back(74.9);
   uncertaintiesRel17HCPForwardTight.push_back(5.7);

   // new HCP single electron trigger SF
   // period A-B3, B4-D3, C1-C5, D4+
   runranges_HCP2012.push_back(200804); // A1 - 0 -> 0
   runranges_HCP2012.push_back(203228); // B4 - 1 -> 1
   runranges_HCP2012.push_back(206248); // C1 - 2 -> 2
   runranges_HCP2012.push_back(206955); // C6 - 3 -> 1
   runranges_HCP2012.push_back(208179); // D4 - 4 -> 3
   runranges_HCP2012.push_back(299999); // end

   const float sf_e24e60_HCP2012_period0_LoosePP_eta[] = {0.29821, 0.93297, 0.96721, 0.98611, 0.98739, 1.00796, 0.9913, 0.97294, 0.99146, 0.99784, 0.99664, 0.99815, 0.99084, 0.98685, 0.99243, 0.9321, 0.9661, 0.97294, 0.9032, 0.22322};
const float errsf_e24e60_HCP2012_period0_LoosePP_eta[] = {0.0229889, 0.0108932, 0.0110537, 0.0110452, 0.0177707, 0.0104636, 0.010214, 0.010291, 0.0101288, 0.0106148, 0.010687, 0.0101017, 0.0103452, 0.0102, 0.0103819, 0.0146236, 0.0109052, 0.0111184, 0.0109252, 0.0171396};

const float effMC_e24e60_HCP2012_period0_LoosePP_eta[] = {0.77261, 0.83972, 0.82974, 0.85229, 0.6177, 0.89814, 0.90067, 0.91793, 0.92288, 0.89774, 0.89066, 0.92278, 0.92295, 0.90181, 0.89718, 0.62964, 0.8519, 0.83354, 0.84475, 0.7866};
const float sf_e24e60_HCP2012_period0_LoosePP_pt[] = {0.976612, 0.963837, 0.973025, 0.973992, 0.98763, 0.993602, 0.995431, 1.00005, 0.998936, 0.998772, 1.01109, 1.01309, 1.00502, 1.01649, 1.01649};
const float errsf_e24e60_HCP2012_period0_LoosePP_pt[] = {0.0139676, 0.00882868, 0.00711228, 0.00595088, 0.00596116, 0.00380281, 0.00296002, 0.00209668, 0.00144918, 0.00150057, 0.00231252, 0.00279558, 0.00418309, 0.0150365, 0.0210491};

const float effMC_e24e60_HCP2012_period0_LoosePP_pt[] = {0.723474, 0.8808, 0.911623, 0.927479, 0.942056, 0.956834, 0.972656, 0.98869, 1.00634, 1.01732, 1.02026, 1.05332, 1.0666, 1.08412, 1.07582};
const float sf_e24e60_HCP2012_period0_MediumPP_eta[] = {0.33647, 0.96337, 0.96926, 0.99006, 0.97836, 1.00455, 0.99722, 0.97601, 1.00068, 1.00622, 1.00266, 1.00456, 0.99895, 0.99706, 0.99864, 0.93492, 0.98434, 0.97929, 0.94042, 0.25248};
const float errsf_e24e60_HCP2012_period0_MediumPP_eta[] = {0.0195939, 0.0105273, 0.0107965, 0.0103739, 0.0141988, 0.0101485, 0.0100921, 0.010202, 0.010046, 0.010277, 0.0103151, 0.0100413, 0.0101194, 0.0100975, 0.0101697, 0.0128375, 0.0104724, 0.01073, 0.0105981, 0.0168083};

const float effMC_e24e60_HCP2012_period0_MediumPP_eta[] = {0.78796, 0.87949, 0.88694, 0.89879, 0.68671, 0.95005, 0.95268, 0.96013, 0.96193, 0.94682, 0.94489, 0.96227, 0.96176, 0.95387, 0.94919, 0.70153, 0.8984, 0.89097, 0.88307, 0.80087};
const float sf_e24e60_HCP2012_period0_MediumPP_pt[] = {1.04391, 0.994776, 0.979952, 0.986651, 0.990887, 0.993891, 0.999552, 0.998839, 1.00099, 0.998462, 0.998483, 1.00969, 1.00733, 1.00759, 0.993677};
const float errsf_e24e60_HCP2012_period0_MediumPP_pt[] = {0.0110576, 0.00673027, 0.00548807, 0.00486697, 0.00418478, 0.00262694, 0.00187348, 0.00114038, 0.000987649, 0.00120147, 0.00152729, 0.00174111, 0.00309531, 0.0105485, 0.018185};

const float effMC_e24e60_HCP2012_period0_MediumPP_pt[] = {0.75003, 0.913153, 0.938157, 0.951963, 0.961753, 0.970049, 0.98111, 0.992553, 1.00195, 1.00974, 1.01081, 1.03311, 1.03984, 1.04739, 1.04756};
const float sf_e24e60_HCP2012_period0_ML_eta[] = {0.29986, 0.94081, 0.97222, 0.98442, 0.97655, 1.008, 0.99441, 0.97306, 0.99193, 0.99955, 0.99952, 0.9989, 0.99302, 0.98926, 0.995, 0.92734, 0.9703, 0.97457, 0.91202, 0.22515};
const float errsf_e24e60_HCP2012_period0_ML_eta[] = {0.0222088, 0.0108231, 0.0109782, 0.0108735, 0.0172128, 0.0104289, 0.0101922, 0.0102863, 0.0100961, 0.0105242, 0.0106148, 0.0100881, 0.010325, 0.0101789, 0.0103503, 0.0138414, 0.0109333, 0.0112118, 0.0109536, 0.0172209};

const float effMC_e24e60_HCP2012_period0_ML_eta[] = {0.77699, 0.84691, 0.83871, 0.85945, 0.62007, 0.90214, 0.90619, 0.92306, 0.9245, 0.9091, 0.90653, 0.92407, 0.92759, 0.90766, 0.89916, 0.63294, 0.85894, 0.84263, 0.85112, 0.79018};
const float sf_e24e60_HCP2012_period0_ML_pt[] = {1.02679, 0.980202, 0.965353, 0.973944, 0.978588, 0.990395, 0.997177, 0.997496, 1.00211, 1.00052, 1.00115, 1.01336, 1.0127, 1.01276, 1.01191};
const float errsf_e24e60_HCP2012_period0_ML_pt[] = {0.0125469, 0.00839545, 0.00665881, 0.00587784, 0.00579563, 0.00415148, 0.00307251, 0.00175719, 0.00138725, 0.00143863, 0.00203464, 0.00251761, 0.00442893, 0.0146124, 0.0229667};

const float effMC_e24e60_HCP2012_period0_ML_pt[] = {0.71734, 0.875863, 0.906153, 0.923006, 0.937217, 0.955131, 0.971618, 0.989134, 1.00675, 1.01814, 1.02228, 1.04817, 1.05943, 1.07355, 1.06465};
const float sf_e24e60_HCP2012_period0_TightPP_eta[] = {0.33639, 0.96014, 0.97175, 0.98507, 0.97637, 1.00189, 0.99488, 0.97586, 0.99941, 1.00286, 1.00125, 1.0034, 0.99681, 0.99427, 0.99261, 0.93615, 0.97907, 0.97907, 0.93827, 0.25206};
const float errsf_e24e60_HCP2012_period0_TightPP_eta[] = {0.0197403, 0.010449, 0.0106014, 0.0103607, 0.014529, 0.0100854, 0.0100717, 0.0101752, 0.0100304, 0.0102327, 0.0102793, 0.0100273, 0.0100841, 0.0100671, 0.0101164, 0.0128942, 0.0103659, 0.0105719, 0.0104965, 0.015475};

const float effMC_e24e60_HCP2012_period0_TightPP_eta[] = {0.84, 0.91909, 0.92766, 0.93333, 0.71119, 0.97448, 0.97083, 0.97512, 0.97651, 0.96344, 0.96078, 0.97661, 0.97677, 0.97185, 0.9747, 0.72532, 0.93449, 0.93185, 0.92212, 0.85269};
const float sf_e24e60_HCP2012_period0_TightPP_pt[] = {1.04601, 0.991432, 0.982658, 0.98578, 0.991932, 0.994361, 0.996473, 0.998411, 1.0011, 0.999044, 0.998483, 1.01053, 1.00811, 1.01161, 0.996809};
const float errsf_e24e60_HCP2012_period0_TightPP_pt[] = {0.0109884, 0.00599922, 0.00541766, 0.00439739, 0.00379543, 0.00235684, 0.00169366, 0.000989667, 0.000867234, 0.00106109, 0.00144879, 0.00151001, 0.00280576, 0.00903964, 0.0168345};

const float effMC_e24e60_HCP2012_period0_TightPP_pt[] = {0.76245, 0.929959, 0.951405, 0.965661, 0.972209, 0.978809, 0.987696, 0.996675, 1.00145, 1.00504, 1.00405, 1.02029, 1.02265, 1.02882, 1.0289};
const float sf_e24e60_HCP2012_period1_LoosePP_eta[] = {0.94789, 0.96886, 0.96282, 0.97251, 0.93859, 0.99983, 0.9851, 0.96472, 0.98658, 0.98687, 0.98284, 0.98767, 0.9871, 0.98672, 0.99401, 0.93363, 0.97133, 0.96821, 0.96242, 0.91025};
const float errsf_e24e60_HCP2012_period1_LoosePP_eta[] = {0.0143989, 0.0138138, 0.0125845, 0.012744, 0.0207838, 0.0111272, 0.0110923, 0.0105719, 0.010284, 0.0117872, 0.0127131, 0.0102724, 0.010774, 0.011024, 0.0108501, 0.0169211, 0.0124284, 0.0126393, 0.0136561, 0.0144278};

const float effMC_e24e60_HCP2012_period1_LoosePP_eta[] = {0.77261, 0.83972, 0.82974, 0.85229, 0.6177, 0.89814, 0.90067, 0.91793, 0.92288, 0.89774, 0.89066, 0.92278, 0.92295, 0.90181, 0.89718, 0.62964, 0.8519, 0.83354, 0.84475, 0.7866};
const float sf_e24e60_HCP2012_period1_LoosePP_pt[] = {0.987443, 0.979264, 0.986394, 0.984947, 0.991282, 0.994928, 0.999369, 1.00135, 1.00087, 0.999226, 1.00353, 1.00412, 0.992402, 1.00917, 1.00917};
const float errsf_e24e60_HCP2012_period1_LoosePP_pt[] = {0.0133723, 0.0106428, 0.00941052, 0.0082393, 0.00789302, 0.00702734, 0.00597833, 0.00500061, 0.0038905, 0.00428769, 0.00554039, 0.00202672, 0.00206746, 0.00606999, 0.00941052};

const float effMC_e24e60_HCP2012_period1_LoosePP_pt[] = {0.723474, 0.8808, 0.911623, 0.927479, 0.942056, 0.956834, 0.972656, 0.98869, 1.00634, 1.01732, 1.02026, 1.05332, 1.0666, 1.08412, 1.07582};
const float sf_e24e60_HCP2012_period1_MediumPP_eta[] = {1.03714, 0.99997, 0.96803, 0.97948, 0.9355, 0.99817, 0.98982, 0.9716, 0.9964, 0.99322, 0.99132, 0.99743, 0.99404, 0.99136, 0.99288, 0.92622, 0.97786, 0.97051, 0.99737, 1.02389};
const float errsf_e24e60_HCP2012_period1_MediumPP_eta[] = {0.0110622, 0.0100778, 0.0101272, 0.0101119, 0.0172943, 0.0100319, 0.0100168, 0.0100319, 0.010008, 0.0100592, 0.0100648, 0.0100076, 0.0100218, 0.0100205, 0.0100352, 0.0126823, 0.0100881, 0.0101385, 0.0100766, 0.0108501};

const float effMC_e24e60_HCP2012_period1_MediumPP_eta[] = {0.78796, 0.87949, 0.88694, 0.89879, 0.68671, 0.95005, 0.95268, 0.96013, 0.96193, 0.94682, 0.94489, 0.96227, 0.96176, 0.95387, 0.94919, 0.70153, 0.8984, 0.89097, 0.88307, 0.80087};
const float sf_e24e60_HCP2012_period1_MediumPP_pt[] = {1.03787, 1.00127, 0.997485, 0.998756, 0.999523, 0.999443, 1.00042, 1.0012, 1.00029, 0.998817, 0.999009, 1.00024, 0.998524, 0.989634, 0.995769};
const float errsf_e24e60_HCP2012_period1_MediumPP_pt[] = {0.0068719, 0.00342081, 0.00274472, 0.00186682, 0.00167509, 0.00129163, 0.000736635, 0.000443999, 0.000363272, 0.000504545, 0.000877908, 0.000746726, 0.001221, 0.00446018, 0.00603435};

const float effMC_e24e60_HCP2012_period1_MediumPP_pt[] = {0.75003, 0.913153, 0.938157, 0.951963, 0.961753, 0.970049, 0.98111, 0.992553, 1.00195, 1.00974, 1.01081, 1.03311, 1.03984, 1.04739, 1.04756};
const float sf_e24e60_HCP2012_period1_ML_eta[] = {0.95141, 0.97585, 0.96671, 0.97434, 0.92988, 1.00072, 0.98739, 0.96556, 0.98682, 0.99007, 0.98543, 0.98789, 0.98859, 0.98777, 0.99661, 0.9274, 0.97207, 0.97261, 0.97124, 0.9144};
const float errsf_e24e60_HCP2012_period1_ML_eta[] = {0.0121894, 0.0113983, 0.0108308, 0.0111184, 0.020977, 0.0106114, 0.0103005, 0.010204, 0.0101789, 0.010291, 0.0103503, 0.0101961, 0.0102306, 0.0103452, 0.0103927, 0.0157979, 0.0109212, 0.0109618, 0.0113318, 0.0121894};

const float effMC_e24e60_HCP2012_period1_ML_eta[] = {0.77699, 0.84691, 0.83871, 0.85945, 0.62007, 0.90214, 0.90619, 0.92306, 0.9245, 0.9091, 0.90653, 0.92407, 0.92759, 0.90766, 0.89916, 0.63294, 0.85894, 0.84263, 0.85112, 0.79018};
const float sf_e24e60_HCP2012_period1_ML_pt[] = {1.01942, 0.986812, 0.980822, 0.987148, 0.98724, 0.992213, 0.99623, 1.00021, 1.00159, 1.00148, 1.00062, 1.00276, 1.00294, 0.992569, 1.01119};
const float errsf_e24e60_HCP2012_period1_ML_pt[] = {0.0115945, 0.0101401, 0.0080246, 0.00679396, 0.00647867, 0.0055328, 0.00424114, 0.00270538, 0.00158661, 0.00135269, 0.00200361, 0.00146457, 0.00186122, 0.00627526, 0.00952985};

const float effMC_e24e60_HCP2012_period1_ML_pt[] = {0.71734, 0.875863, 0.906153, 0.923006, 0.937217, 0.955131, 0.971618, 0.989134, 1.00675, 1.01814, 1.02228, 1.04817, 1.05943, 1.07355, 1.06465};
const float sf_e24e60_HCP2012_period1_TightPP_eta[] = {1.02901, 0.9952, 0.96631, 0.97722, 0.93243, 0.99542, 0.9874, 0.97071, 0.99547, 0.99175, 0.98957, 0.99627, 0.99281, 0.98921, 0.98915, 0.9268, 0.97441, 0.97058, 0.99483, 1.01237};
const float errsf_e24e60_HCP2012_period1_TightPP_eta[] = {0.0109052, 0.0101884, 0.0102327, 0.0102701, 0.0171234, 0.0101164, 0.0100921, 0.0100816, 0.0100625, 0.0101418, 0.0101241, 0.0100671, 0.0100682, 0.0100907, 0.0100592, 0.0127626, 0.0101789, 0.0102816, 0.0101715, 0.0107703};

const float effMC_e24e60_HCP2012_period1_TightPP_eta[] = {0.84, 0.91909, 0.92766, 0.93333, 0.71119, 0.97448, 0.97083, 0.97512, 0.97651, 0.96344, 0.96078, 0.97661, 0.97677, 0.97185, 0.9747, 0.72532, 0.93449, 0.93185, 0.92212, 0.85269};
const float sf_e24e60_HCP2012_period1_TightPP_pt[] = {1.0388, 0.996719, 0.997346, 0.996537, 0.998953, 0.998367, 0.999419, 1.0001, 0.999995, 0.999772, 0.999661, 1.00229, 1.00027, 0.994848, 0.997194};
const float errsf_e24e60_HCP2012_period1_TightPP_pt[] = {0.00764474, 0.00536952, 0.00462123, 0.0030943, 0.00327632, 0.00295273, 0.00215388, 0.00126401, 0.000667398, 0.000596613, 0.000980873, 0.00062695, 0.00105166, 0.00386282, 0.00521784};

const float effMC_e24e60_HCP2012_period1_TightPP_pt[] = {0.76245, 0.929959, 0.951405, 0.965661, 0.972209, 0.978809, 0.987696, 0.996675, 1.00145, 1.00504, 1.00405, 1.02029, 1.02265, 1.02882, 1.0289};
const float sf_e24e60_HCP2012_period2_LoosePP_eta[] = {0.88505, 0.96571, 0.93769, 0.96161, 0.92058, 0.98899, 0.97398, 0.95444, 0.97671, 0.97035, 0.9748, 0.97428, 0.97208, 0.97115, 0.97873, 0.89922, 0.95529, 0.94975, 0.9546, 0.85359};
const float errsf_e24e60_HCP2012_period2_LoosePP_eta[] = {0.0181694, 0.0132482, 0.0131309, 0.0117033, 0.0215329, 0.0112804, 0.0108269, 0.0108853, 0.0106081, 0.0113554, 0.0119487, 0.0105687, 0.0107409, 0.0108193, 0.0114515, 0.0235397, 0.0115653, 0.0132679, 0.0125301, 0.0169453};

const float effMC_e24e60_HCP2012_period2_LoosePP_eta[] = {0.77261, 0.83972, 0.82974, 0.85229, 0.6177, 0.89814, 0.90067, 0.91793, 0.92288, 0.89774, 0.89066, 0.92278, 0.92295, 0.90181, 0.89718, 0.62964, 0.8519, 0.83354, 0.84475, 0.7866};
const float sf_e24e60_HCP2012_period2_LoosePP_pt[] = {0.965643, 0.982737, 0.973234, 0.962197, 0.983529, 0.986265, 0.99546, 0.998824, 0.997034, 1.00338, 1.00316, 1.00634, 1.01098, 1.06307, 1.06307};
const float errsf_e24e60_HCP2012_period2_LoosePP_pt[] = {0.0240063, 0.0140294, 0.0107998, 0.0109746, 0.00959636, 0.00754955, 0.0058833, 0.00385706, 0.00272565, 0.00263309, 0.00368221, 0.00405248, 0.00647986, 0.0203344, 0.006521};

const float effMC_e24e60_HCP2012_period2_LoosePP_pt[] = {0.723474, 0.8808, 0.911623, 0.927479, 0.942056, 0.956834, 0.972656, 0.98869, 1.00634, 1.01732, 1.02026, 1.05332, 1.0666, 1.08412, 1.07582};
const float sf_e24e60_HCP2012_period2_MediumPP_eta[] = {0.98886, 0.99306, 0.94618, 0.97072, 0.91756, 0.98826, 0.97867, 0.96105, 0.98437, 0.97613, 0.97982, 0.98593, 0.98096, 0.97702, 0.98202, 0.89727, 0.96926, 0.95757, 0.99521, 0.98851};
const float errsf_e24e60_HCP2012_period2_MediumPP_eta[] = {0.0170666, 0.0109659, 0.0117713, 0.0109292, 0.0183116, 0.0104148, 0.0102435, 0.0104346, 0.0101336, 0.0108657, 0.0110622, 0.0101418, 0.0103401, 0.0102566, 0.0104519, 0.022809, 0.01097, 0.0119323, 0.0108814, 0.0163063};

const float effMC_e24e60_HCP2012_period2_MediumPP_eta[] = {0.78796, 0.87949, 0.88694, 0.89879, 0.68671, 0.95005, 0.95268, 0.96013, 0.96193, 0.94682, 0.94489, 0.96227, 0.96176, 0.95387, 0.94919, 0.70153, 0.8984, 0.89097, 0.88307, 0.80087};
const float sf_e24e60_HCP2012_period2_MediumPP_pt[] = {1.02884, 0.98562, 0.996843, 0.997332, 0.977465, 0.990299, 0.994121, 1.00003, 1.00007, 0.997353, 1.00233, 1.00267, 0.996945, 0.987822, 1.03099};
const float errsf_e24e60_HCP2012_period2_MediumPP_pt[] = {0.0150254, 0.00945967, 0.00751269, 0.00703359, 0.00644236, 0.00488274, 0.0028644, 0.00165136, 0.00154943, 0.00176349, 0.0022324, 0.00274208, 0.00516816, 0.0200712, 0.00361873};

const float effMC_e24e60_HCP2012_period2_MediumPP_pt[] = {0.75003, 0.913153, 0.938157, 0.951963, 0.961753, 0.970049, 0.98111, 0.992553, 1.00195, 1.00974, 1.01081, 1.03311, 1.03984, 1.04739, 1.04756};
const float sf_e24e60_HCP2012_period2_ML_eta[] = {0.8826, 0.9717, 0.94325, 0.96164, 0.91128, 0.98929, 0.97539, 0.9567, 0.9767, 0.97341, 0.9748, 0.97528, 0.97292, 0.97273, 0.98326, 0.89427, 0.95939, 0.95762, 0.96803, 0.85827};
const float errsf_e24e60_HCP2012_period2_ML_eta[] = {0.0184543, 0.0128, 0.0132811, 0.0117872, 0.0201383, 0.0112163, 0.0106283, 0.0107852, 0.0105242, 0.0112345, 0.0113887, 0.0104934, 0.0106351, 0.0108003, 0.0115403, 0.021968, 0.0117978, 0.0135544, 0.0126149, 0.0168969};

const float effMC_e24e60_HCP2012_period2_ML_eta[] = {0.77699, 0.84691, 0.83871, 0.85945, 0.62007, 0.90214, 0.90619, 0.92306, 0.9245, 0.9091, 0.90653, 0.92407, 0.92759, 0.90766, 0.89916, 0.63294, 0.85894, 0.84263, 0.85112, 0.79018};
const float sf_e24e60_HCP2012_period2_ML_pt[] = {1.00004, 0.961227, 0.989683, 0.984138, 0.965002, 0.985537, 0.986988, 0.999518, 1.00191, 0.999251, 1.00597, 1.00315, 1.0054, 1.01451, 1.06786};
const float errsf_e24e60_HCP2012_period2_ML_pt[] = {0.0240019, 0.0144546, 0.0104217, 0.0106172, 0.00934149, 0.00734562, 0.00585386, 0.0037654, 0.00258228, 0.00233537, 0.00336417, 0.00378598, 0.00664604, 0.0206171, 0.0071913};

const float effMC_e24e60_HCP2012_period2_ML_pt[] = {0.71734, 0.875863, 0.906153, 0.923006, 0.937217, 0.955131, 0.971618, 0.989134, 1.00675, 1.01814, 1.02228, 1.04817, 1.05943, 1.07355, 1.06465};
const float sf_e24e60_HCP2012_period2_TightPP_eta[] = {0.9893, 0.99947, 0.95342, 0.97836, 0.92478, 0.99037, 0.98377, 0.96752, 0.98953, 0.98049, 0.9872, 0.99198, 0.98754, 0.98392, 0.98529, 0.9061, 0.97002, 0.97197, 1.00221, 0.98636};
const float errsf_e24e60_HCP2012_period2_TightPP_eta[] = {0.0161566, 0.0108814, 0.0118137, 0.0107155, 0.0189358, 0.0105719, 0.0101845, 0.0104965, 0.0101625, 0.0107592, 0.0108117, 0.0101401, 0.0102391, 0.0102793, 0.010335, 0.0236574, 0.0107445, 0.0119214, 0.0108853, 0.0155515};

const float effMC_e24e60_HCP2012_period2_TightPP_eta[] = {0.84, 0.91909, 0.92766, 0.93333, 0.71119, 0.97448, 0.97083, 0.97512, 0.97651, 0.96344, 0.96078, 0.97661, 0.97677, 0.97185, 0.9747, 0.72532, 0.93449, 0.93185, 0.92212, 0.85269};
const float sf_e24e60_HCP2012_period2_TightPP_pt[] = {1.02694, 0.982004, 0.995436, 0.992679, 0.981578, 0.992263, 0.994686, 0.999288, 1.00062, 0.998305, 1.00008, 1.00359, 0.998143, 0.992091, 1.01931};
const float errsf_e24e60_HCP2012_period2_TightPP_pt[] = {0.0159568, 0.0093166, 0.00714712, 0.00608265, 0.00635637, 0.00455185, 0.00374083, 0.00174369, 0.0015308, 0.00152066, 0.00232155, 0.00219989, 0.00431868, 0.0161393, 0.00261554};

const float effMC_e24e60_HCP2012_period2_TightPP_pt[] = {0.76245, 0.929959, 0.951405, 0.965661, 0.972209, 0.978809, 0.987696, 0.996675, 1.00145, 1.00504, 1.00405, 1.02029, 1.02265, 1.02882, 1.0289};
const float sf_e24e60_HCP2012_period3_LoosePP_eta[] = {0.92837, 0.97847, 0.95977, 0.99227, 0.92689, 0.99452, 0.99197, 0.96554, 0.98875, 1.01381, 1.00612, 0.99131, 0.99383, 0.99742, 0.9976, 0.93192, 1.00052, 0.97026, 0.97478, 0.88535};
const float errsf_e24e60_HCP2012_period3_LoosePP_eta[] = {0.0135073, 0.0120761, 0.011745, 0.0119817, 0.0227192, 0.0105719, 0.0106695, 0.0104577, 0.0101961, 0.0108657, 0.0112528, 0.0102327, 0.0105056, 0.0106351, 0.010774, 0.0210649, 0.0118084, 0.0112804, 0.0118943, 0.0126638};

const float effMC_e24e60_HCP2012_period3_LoosePP_eta[] = {0.77261, 0.83972, 0.82974, 0.85229, 0.6177, 0.89814, 0.90067, 0.91793, 0.92288, 0.89774, 0.89066, 0.92278, 0.92295, 0.90181, 0.89718, 0.62964, 0.8519, 0.83354, 0.84475, 0.7866};
const float sf_e24e60_HCP2012_period3_LoosePP_pt[] = {0.991939, 0.984446, 0.986866, 0.985894, 0.993114, 0.995585, 1.00035, 1.00323, 1.00305, 1.0038, 0.994076, 0.99357, 0.977003, 0.989691, 0.989691};
const float errsf_e24e60_HCP2012_period3_LoosePP_pt[] = {0.0119795, 0.00906311, 0.00941753, 0.00802009, 0.00744289, 0.00581254, 0.00442523, 0.00372651, 0.00267336, 0.00311892, 0.00374676, 0.00201515, 0.00254172, 0.00905298, 0.0111896};

const float effMC_e24e60_HCP2012_period3_LoosePP_pt[] = {0.723474, 0.8808, 0.911623, 0.927479, 0.942056, 0.956834, 0.972656, 0.98869, 1.00634, 1.01732, 1.02026, 1.05332, 1.0666, 1.08412, 1.07582};
const float sf_e24e60_HCP2012_period3_MediumPP_eta[] = {1.03872, 1.00978, 0.96971, 0.999, 0.93718, 0.99863, 1.00139, 0.9779, 1.00359, 1.01977, 1.01707, 1.00507, 1.00229, 1.00525, 0.9984, 0.92774, 1.00283, 0.97377, 1.01091, 1.02698};
const float errsf_e24e60_HCP2012_period3_MediumPP_eta[] = {0.0109618, 0.0101104, 0.0101864, 0.0102349, 0.0212412, 0.0100413, 0.0100224, 0.010045, 0.0100101, 0.0100603, 0.0100682, 0.0100101, 0.0100288, 0.0100205, 0.0100441, 0.0188849, 0.010198, 0.0101845, 0.0101017, 0.0110115};

const float effMC_e24e60_HCP2012_period3_MediumPP_eta[] = {0.78796, 0.87949, 0.88694, 0.89879, 0.68671, 0.95005, 0.95268, 0.96013, 0.96193, 0.94682, 0.94489, 0.96227, 0.96176, 0.95387, 0.94919, 0.70153, 0.8984, 0.89097, 0.88307, 0.80087};
const float sf_e24e60_HCP2012_period3_MediumPP_pt[] = {1.0316, 0.998574, 0.994159, 0.99342, 0.994429, 0.999433, 0.999183, 1.00045, 1.00173, 1.00129, 1.00385, 0.989315, 0.986059, 0.978029, 0.98509};
const float errsf_e24e60_HCP2012_period3_MediumPP_pt[] = {0.00662194, 0.00333594, 0.00273667, 0.00249696, 0.00225725, 0.0014782, 0.000848966, 0.000529355, 0.000409501, 0.000489404, 0.000679173, 0.000838978, 0.00149818, 0.00575299, 0.00730111};

const float effMC_e24e60_HCP2012_period3_MediumPP_pt[] = {0.75003, 0.913153, 0.938157, 0.951963, 0.961753, 0.970049, 0.98111, 0.992553, 1.00195, 1.00974, 1.01081, 1.03311, 1.03984, 1.04739, 1.04756};
const float sf_e24e60_HCP2012_period3_ML_eta[] = {0.93075, 0.98549, 0.96438, 0.99304, 0.92042, 0.99507, 0.9943, 0.96647, 0.98859, 1.01516, 1.00766, 0.99137, 0.9957, 0.99871, 1.0001, 0.92611, 1.00045, 0.97417, 0.98456, 0.8893};
const float errsf_e24e60_HCP2012_period3_ML_eta[] = {0.0124165, 0.0118835, 0.0115503, 0.0114272, 0.0216925, 0.0105784, 0.0105304, 0.0102656, 0.01021, 0.0105622, 0.0107445, 0.0102243, 0.0103151, 0.0105087, 0.0106014, 0.0192083, 0.0113887, 0.0115005, 0.0120093, 0.0122238};

const float effMC_e24e60_HCP2012_period3_ML_eta[] = {0.77699, 0.84691, 0.83871, 0.85945, 0.62007, 0.90214, 0.90619, 0.92306, 0.9245, 0.9091, 0.90653, 0.92407, 0.92759, 0.90766, 0.89916, 0.63294, 0.85894, 0.84263, 0.85112, 0.79018};
const float sf_e24e60_HCP2012_period3_ML_pt[] = {1.0156, 0.988474, 0.984282, 0.984908, 0.98608, 0.992656, 0.994677, 0.999364, 1.00271, 1.00341, 1.00445, 0.993091, 0.991293, 0.974493, 0.991535};
const float errsf_e24e60_HCP2012_period3_ML_pt[] = {0.0117186, 0.00935468, 0.00881926, 0.00728372, 0.00709177, 0.00544511, 0.00467734, 0.00339435, 0.00203055, 0.00219219, 0.00259628, 0.00166687, 0.0022427, 0.00849599, 0.0117085};

const float effMC_e24e60_HCP2012_period3_ML_pt[] = {0.71734, 0.875863, 0.906153, 0.923006, 0.937217, 0.955131, 0.971618, 0.989134, 1.00675, 1.01814, 1.02228, 1.04817, 1.05943, 1.07355, 1.06465};
const float sf_e24e60_HCP2012_period3_TightPP_eta[] = {1.02701, 1.0058, 0.96884, 0.99572, 0.93505, 0.99608, 0.99864, 0.9763, 1.00142, 1.01437, 1.01379, 1.00364, 1.0004, 1.00281, 0.99445, 0.92695, 0.9979, 0.97479, 1.00763, 1.01773};
const float errsf_e24e60_HCP2012_period3_TightPP_eta[] = {0.0102223, 0.0100441, 0.0100378, 0.0108193, 0.0369104, 0.0100266, 0.0100054, 0.0100006, 0.0100002, 0.0100273, 0.010014, 0.0100003, 0.0100084, 0.0100006, 0.0100005, 0.0325159, 0.0104037, 0.0100001, 0.0100198, 0.0101352};

const float effMC_e24e60_HCP2012_period3_TightPP_eta[] = {0.84, 0.91909, 0.92766, 0.93333, 0.71119, 0.97448, 0.97083, 0.97512, 0.97651, 0.96344, 0.96078, 0.97661, 0.97677, 0.97185, 0.9747, 0.72532, 0.93449, 0.93185, 0.92212, 0.85269};
const float sf_e24e60_HCP2012_period3_TightPP_pt[] = {1.03012, 0.993538, 0.99461, 0.990244, 0.993989, 0.997624, 0.998415, 0.999827, 1.00134, 1.00173, 1.00349, 0.993188, 0.990074, 0.979529, 0.983955};
const float errsf_e24e60_HCP2012_period3_TightPP_pt[] = {0.00841158, 0.00478659, 0.00487672, 0.00333459, 0.00393542, 0.00278383, 0.00229316, 0.00131181, 0.000690952, 0.000600827, 0.000891227, 0.000690952, 0.00128177, 0.00536739, 0.00678935};

const float effMC_e24e60_HCP2012_period3_TightPP_pt[] = {0.76245, 0.929959, 0.951405, 0.965661, 0.972209, 0.978809, 0.987696, 0.996675, 1.00145, 1.00504, 1.00405, 1.02029, 1.02265, 1.02882, 1.0289};
const float sf_e24e60_HCP2012_AFII_period0_LoosePP_eta[] = {0.31881, 0.96211, 0.97145, 1.00406, 0.95811, 1.00694, 1.05258, 1.01831, 1.01114, 1.0385, 1.04073, 1.02198, 1.04156, 1.04769, 0.99261, 0.92271, 0.98429, 0.97537, 0.9357, 0.24};
const float errsf_e24e60_HCP2012_AFII_period0_LoosePP_eta[] = {0.0219146, 0.0107409, 0.0110115, 0.010673, 0.0273162, 0.0104695, 0.010214, 0.0103982, 0.0101003, 0.0107852, 0.0109948, 0.0100934, 0.0102816, 0.0102327, 0.0103686, 0.0210825, 0.0108893, 0.0114956, 0.0110967, 0.0170909};

const float effMC_e24e60_HCP2012_AFII_period0_LoosePP_eta[] = {0.72546, 0.81953, 0.82974, 0.83123, 0.63592, 0.87778, 0.83917, 0.87902, 0.90358, 0.85168, 0.84756, 0.90032, 0.87954, 0.84069, 0.87767, 0.63993, 0.83481, 0.83251, 0.82116, 0.7375};
const float sf_e24e60_HCP2012_AFII_period0_LoosePP_pt[] = {0.980361, 0.970613, 0.982584, 0.982145, 0.993349, 0.997286, 0.999798, 1.00509, 1.00419, 1.0069, 0.987627, 0.986052, 0.992123, 0.98053, 0.98053};
const float errsf_e24e60_HCP2012_AFII_period0_LoosePP_pt[] = {0.0123898, 0.00863201, 0.00713686, 0.00616002, 0.00576132, 0.00350862, 0.00269127, 0.00184402, 0.00144531, 0.00154499, 0.00216299, 0.00252182, 0.00405684, 0.0150811, 0.0205833};

const float effMC_e24e60_HCP2012_AFII_period0_LoosePP_pt[] = {0.703623, 0.880193, 0.908118, 0.921368, 0.937182, 0.954319, 0.972135, 0.987478, 1.00443, 1.01519, 1.01521, 1.08174, 1.09929, 1.10168, 1.11879};
const float sf_e24e60_HCP2012_AFII_period0_MediumPP_eta[] = {0.35769, 0.97493, 0.96266, 1.00448, 0.85481, 1.01154, 1.0421, 0.9868, 1.00722, 1.03084, 1.02565, 1.01153, 1.01138, 1.04087, 1.00642, 0.83001, 0.99437, 0.97656, 0.95393, 0.26837};
const float errsf_e24e60_HCP2012_AFII_period0_MediumPP_eta[] = {0.0196025, 0.010543, 0.0108462, 0.0103846, 0.0207926, 0.0101572, 0.0101209, 0.0101961, 0.0100469, 0.0103633, 0.0105211, 0.0100404, 0.0101256, 0.0101104, 0.0101789, 0.0179945, 0.0104461, 0.0107703, 0.0106181, 0.0172861};

const float effMC_e24e60_HCP2012_AFII_period0_MediumPP_eta[] = {0.74121, 0.86907, 0.89303, 0.88588, 0.78597, 0.94349, 0.91164, 0.94964, 0.95568, 0.92421, 0.92371, 0.95564, 0.94994, 0.91372, 0.94185, 0.79021, 0.88933, 0.89347, 0.87057, 0.75345};
const float sf_e24e60_HCP2012_AFII_period0_MediumPP_pt[] = {1.058, 0.981279, 0.971426, 0.978487, 0.984674, 0.992931, 0.995432, 0.999118, 1.00355, 1.00348, 1.00437, 0.996195, 0.992499, 0.999882, 0.981912};
const float errsf_e24e60_HCP2012_AFII_period0_MediumPP_pt[] = {0.0104363, 0.00576555, 0.00525328, 0.00435932, 0.0037667, 0.00241068, 0.00165735, 0.00100445, 0.000883918, 0.00108481, 0.00151672, 0.00147654, 0.00277229, 0.00900994, 0.0167643};

const float effMC_e24e60_HCP2012_AFII_period0_MediumPP_pt[] = {0.741495, 0.924377, 0.949175, 0.96053, 0.970022, 0.97083, 0.981991, 0.992226, 0.999222, 1.00464, 1.00456, 1.04814, 1.05631, 1.05577, 1.06644};
const float sf_e24e60_HCP2012_AFII_period0_ML_eta[] = {0.31881, 0.96211, 0.97145, 1.00406, 0.95811, 1.00694, 1.05258, 1.01831, 1.01114, 1.0385, 1.04073, 1.02198, 1.04156, 1.04769, 0.99261, 0.92271, 0.98429, 0.97537, 0.9357, 0.24};
const float errsf_e24e60_HCP2012_AFII_period0_ML_eta[] = {0.0219146, 0.0107409, 0.0110115, 0.010673, 0.0273162, 0.0104695, 0.010214, 0.0103982, 0.0101003, 0.0107852, 0.0109948, 0.0100934, 0.0102816, 0.0102327, 0.0103686, 0.0210825, 0.0108893, 0.0114956, 0.0110967, 0.0170909};

const float effMC_e24e60_HCP2012_AFII_period0_ML_eta[] = {0.73081, 0.82816, 0.83937, 0.84263, 0.632, 0.90308, 0.85611, 0.88205, 0.90694, 0.87501, 0.87063, 0.90319, 0.88436, 0.85703, 0.90133, 0.63611, 0.84673, 0.84195, 0.82958, 0.74129};
const float sf_e24e60_HCP2012_AFII_period0_ML_pt[] = {1.05444, 0.981355, 0.969261, 0.980235, 0.983576, 0.99446, 0.998991, 0.998541, 1.00401, 1.00235, 1.00434, 0.992929, 0.989888, 0.996721, 0.977014};
const float errsf_e24e60_HCP2012_AFII_period0_ML_pt[] = {0.0118342, 0.00802282, 0.00673237, 0.00595209, 0.00560197, 0.0036913, 0.002831, 0.00164058, 0.00136048, 0.00150053, 0.00197069, 0.00239084, 0.0042615, 0.0145951, 0.0224479};

const float effMC_e24e60_HCP2012_AFII_period0_ML_pt[] = {0.69905, 0.875485, 0.903181, 0.917756, 0.933161, 0.951939, 0.970581, 0.988837, 1.00558, 1.01703, 1.01978, 1.07053, 1.08465, 1.09165, 1.10351};
const float sf_e24e60_HCP2012_AFII_period0_TightPP_eta[] = {0.35657, 0.97259, 0.96571, 1.00064, 0.8546, 1.00954, 1.0392, 0.98622, 1.006, 1.02738, 1.02324, 1.00968, 1.00927, 1.03808, 1.00153, 0.83197, 0.99143, 0.97494, 0.95078, 0.26689};
const float errsf_e24e60_HCP2012_AFII_period0_TightPP_eta[] = {0.0190293, 0.0104548, 0.0106048, 0.0103175, 0.0207488, 0.0100934, 0.0101075, 0.0101679, 0.0100312, 0.010335, 0.010426, 0.0100259, 0.0100894, 0.0100803, 0.0101256, 0.0177211, 0.0103739, 0.0105751, 0.0104995, 0.0154369};

const float effMC_e24e60_HCP2012_AFII_period0_TightPP_eta[] = {0.79244, 0.90733, 0.93346, 0.91881, 0.81254, 0.96709, 0.92943, 0.96488, 0.97012, 0.94044, 0.94013, 0.97054, 0.96472, 0.93083, 0.96602, 0.81615, 0.92283, 0.9358, 0.90998, 0.80531};
const float sf_e24e60_HCP2012_AFII_period0_TightPP_pt[] = {1.058, 0.981279, 0.971426, 0.978487, 0.984674, 0.992931, 0.995432, 0.999118, 1.00355, 1.00348, 1.00437, 0.996195, 0.992499, 0.999882, 0.981912};
const float errsf_e24e60_HCP2012_AFII_period0_TightPP_pt[] = {0.0104363, 0.00576555, 0.00525328, 0.00435932, 0.0037667, 0.00241068, 0.00165735, 0.00100445, 0.000883918, 0.00108481, 0.00151672, 0.00147654, 0.00277229, 0.00900994, 0.0167643};

const float effMC_e24e60_HCP2012_AFII_period0_TightPP_pt[] = {0.753426, 0.939094, 0.961917, 0.972357, 0.978868, 0.979708, 0.988226, 0.995463, 0.998498, 1.00009, 0.997658, 1.03444, 1.0382, 1.04035, 1.04397};
const float sf_e24e60_HCP2012_AFII_period1_LoosePP_eta[] = {1.0095, 0.99273, 0.96282, 0.99715, 0.91171, 1.02303, 1.0573, 1.00743, 1.00765, 1.04024, 1.03282, 1.01231, 1.03582, 1.05846, 1.0161, 0.91862, 0.99122, 0.96941, 0.99007, 0.97085};
const float errsf_e24e60_HCP2012_AFII_period1_LoosePP_eta[] = {0.0141846, 0.0133869, 0.0128816, 0.0121837, 0.0311583, 0.0112163, 0.0111141, 0.0104577, 0.0102863, 0.0104695, 0.0104065, 0.0102679, 0.0106941, 0.0109012, 0.0109989, 0.0250157, 0.0118889, 0.0135477, 0.0139316, 0.0143989};

const float effMC_e24e60_HCP2012_AFII_period1_LoosePP_eta[] = {0.72546, 0.81953, 0.82974, 0.83123, 0.63592, 0.87778, 0.83917, 0.87902, 0.90358, 0.85168, 0.84756, 0.90032, 0.87954, 0.84069, 0.87767, 0.63993, 0.83481, 0.83251, 0.82116, 0.7375};
const float sf_e24e60_HCP2012_AFII_period1_LoosePP_pt[] = {0.991421, 0.986323, 0.996251, 0.993387, 0.99721, 0.9988, 1.00394, 1.0066, 1.00632, 1.00755, 0.980425, 0.977511, 0.979842, 0.973638, 0.973638};
const float errsf_e24e60_HCP2012_AFII_period1_LoosePP_pt[] = {0.011677, 0.00990867, 0.0089998, 0.00811069, 0.00749819, 0.00634234, 0.00542359, 0.0045246, 0.00376391, 0.00387258, 0.00499879, 0.00167944, 0.00206472, 0.00630283, 0.00839718};

const float effMC_e24e60_HCP2012_AFII_period1_LoosePP_pt[] = {0.703623, 0.880193, 0.908118, 0.921368, 0.937182, 0.954319, 0.972135, 0.987478, 1.00443, 1.01519, 1.01521, 1.08174, 1.09929, 1.10168, 1.11879};
const float sf_e24e60_HCP2012_AFII_period1_MediumPP_eta[] = {1.10255, 1.01196, 0.96143, 0.99375, 0.81736, 1.00511, 1.03438, 0.98234, 1.00291, 1.01752, 1.01404, 1.00435, 1.00641, 1.03493, 1.00062, 0.82228, 0.98782, 0.9678, 1.0117, 1.08834};
const float errsf_e24e60_HCP2012_AFII_period1_MediumPP_eta[] = {0.0111448, 0.0100894, 0.0101304, 0.0100854, 0.02612, 0.0100319, 0.0100369, 0.0100319, 0.0100084, 0.0102264, 0.0102285, 0.0100097, 0.0100344, 0.0100319, 0.0100352, 0.0200515, 0.0100854, 0.0101241, 0.0100867, 0.0111184};

const float effMC_e24e60_HCP2012_AFII_period1_MediumPP_eta[] = {0.74121, 0.86907, 0.89303, 0.88588, 0.78597, 0.94349, 0.91164, 0.94964, 0.95568, 0.92421, 0.92371, 0.95564, 0.94994, 0.91372, 0.94185, 0.79021, 0.88933, 0.89347, 0.87057, 0.75345};
const float sf_e24e60_HCP2012_AFII_period1_MediumPP_pt[] = {1.04973, 0.989031, 0.985822, 0.989766, 0.990918, 0.998546, 0.99944, 1.00145, 1.00293, 1.0038, 1.00514, 0.985812, 0.982862, 0.9817, 0.978075};
const float errsf_e24e60_HCP2012_AFII_period1_MediumPP_pt[] = {0.00541339, 0.00313877, 0.00277126, 0.0018475, 0.00173824, 0.00129127, 0.000735029, 0.000446977, 0.00038738, 0.000496641, 0.000804558, 0.000725096, 0.00120187, 0.00464856, 0.00571137};

const float effMC_e24e60_HCP2012_AFII_period1_MediumPP_pt[] = {0.741495, 0.924377, 0.949175, 0.96053, 0.970022, 0.97083, 0.981991, 0.992226, 0.999222, 1.00464, 1.00456, 1.04814, 1.05631, 1.05577, 1.06644};
const float sf_e24e60_HCP2012_AFII_period1_ML_eta[] = {1.01154, 0.99795, 0.96595, 0.99378, 0.91232, 0.99967, 1.04514, 1.01045, 1.00593, 1.02865, 1.02606, 1.01071, 1.03691, 1.04612, 0.99422, 0.92278, 0.98609, 0.9734, 0.99645, 0.9747};
const float errsf_e24e60_HCP2012_AFII_period1_ML_eta[] = {0.0123223, 0.0113365, 0.0109577, 0.0109092, 0.0322021, 0.0106385, 0.010284, 0.0102264, 0.0101827, 0.0106835, 0.0109132, 0.0101903, 0.0102264, 0.0102478, 0.0104374, 0.0240387, 0.0107703, 0.0109454, 0.0114661, 0.0121722};

const float effMC_e24e60_HCP2012_AFII_period1_ML_eta[] = {0.73081, 0.82816, 0.83937, 0.84263, 0.632, 0.90308, 0.85611, 0.88205, 0.90694, 0.87501, 0.87063, 0.90319, 0.88436, 0.85703, 0.90133, 0.63611, 0.84673, 0.84195, 0.82958, 0.74129};
const float sf_e24e60_HCP2012_AFII_period1_ML_pt[] = {1.04702, 0.988108, 0.98492, 0.993663, 0.992406, 0.996426, 0.998169, 1.00139, 1.00362, 1.00345, 1.00394, 0.982672, 0.980483, 0.976978, 0.976443};
const float errsf_e24e60_HCP2012_AFII_period1_ML_pt[] = {0.0105954, 0.00857537, 0.00765446, 0.00693159, 0.00627804, 0.00518879, 0.00382228, 0.00247557, 0.00155466, 0.00127739, 0.00179231, 0.00156456, 0.00201016, 0.00622853, 0.0091398};

const float effMC_e24e60_HCP2012_AFII_period1_ML_pt[] = {0.69905, 0.875485, 0.903181, 0.917756, 0.933161, 0.951939, 0.970581, 0.988837, 1.00558, 1.01703, 1.01978, 1.07053, 1.08465, 1.09165, 1.10351};
const float sf_e24e60_HCP2012_AFII_period1_TightPP_eta[] = {1.09077, 1.00811, 0.96031, 0.99267, 0.81613, 1.00302, 1.03139, 0.98101, 1.00203, 1.016, 1.01131, 1.00251, 1.00521, 1.0328, 0.99804, 0.82366, 0.98672, 0.96648, 1.0081, 1.07193};
const float errsf_e24e60_HCP2012_AFII_period1_TightPP_eta[] = {0.0109495, 0.0101884, 0.0102391, 0.0102456, 0.0253369, 0.010106, 0.0101046, 0.0100729, 0.0100682, 0.010277, 0.0101827, 0.0100659, 0.0100934, 0.0100989, 0.0100907, 0.0192425, 0.0101452, 0.0102747, 0.0102202, 0.0108814};

const float effMC_e24e60_HCP2012_AFII_period1_TightPP_eta[] = {0.79244, 0.90733, 0.93346, 0.91881, 0.81254, 0.96709, 0.92943, 0.96488, 0.97012, 0.94044, 0.94013, 0.97054, 0.96472, 0.93083, 0.96602, 0.81615, 0.92283, 0.9358, 0.90998, 0.80531};
const float sf_e24e60_HCP2012_AFII_period1_TightPP_pt[] = {1.05093, 0.986723, 0.986156, 0.989392, 0.991871, 0.997149, 0.998593, 1.00103, 1.00266, 1.00443, 1.00577, 0.988297, 0.984991, 0.983527, 0.982511};
const float errsf_e24e60_HCP2012_AFII_period1_TightPP_pt[] = {0.00703992, 0.00480945, 0.00443106, 0.00347515, 0.00364443, 0.00293745, 0.00191183, 0.00121481, 0.000726894, 0.000716936, 0.000886213, 0.000667149, 0.00105549, 0.00391328, 0.00508826};

const float effMC_e24e60_HCP2012_AFII_period1_TightPP_pt[] = {0.753426, 0.939094, 0.961917, 0.972357, 0.978868, 0.979708, 0.988226, 0.995463, 0.998498, 1.00009, 0.997658, 1.03444, 1.0382, 1.04035, 1.04397};
const float sf_e24e60_HCP2012_AFII_period2_LoosePP_eta[] = {0.94258, 0.9895, 0.93768, 0.98598, 0.89421, 1.01193, 1.04537, 0.99669, 0.99757, 1.02284, 1.02437, 0.99858, 1.02006, 1.04176, 1.00048, 0.88476, 0.97485, 0.95093, 0.98202, 0.91042};
const float errsf_e24e60_HCP2012_AFII_period2_LoosePP_eta[] = {0.0186564, 0.0133471, 0.0133339, 0.0116006, 0.0295909, 0.0113365, 0.0109052, 0.0109333, 0.0106114, 0.0122123, 0.0118835, 0.0105719, 0.0107815, 0.0108041, 0.0116108, 0.0321165, 0.0113887, 0.0135544, 0.0128062, 0.0177376};

const float effMC_e24e60_HCP2012_AFII_period2_LoosePP_eta[] = {0.72546, 0.81953, 0.82974, 0.83123, 0.63592, 0.87778, 0.83917, 0.87902, 0.90358, 0.85168, 0.84756, 0.90032, 0.87954, 0.84069, 0.87767, 0.63993, 0.83481, 0.83251, 0.82116, 0.7375};
const float sf_e24e60_HCP2012_AFII_period2_LoosePP_pt[] = {0.969895, 0.990206, 0.983339, 0.970803, 0.989787, 0.990475, 1.00039, 1.00444, 1.00284, 1.01211, 0.980445, 0.980046, 0.99857, 1.02604, 1.02604};
const float errsf_e24e60_HCP2012_AFII_period2_LoosePP_pt[] = {0.0239437, 0.0136336, 0.0107193, 0.0110187, 0.00976113, 0.00713621, 0.00553929, 0.00357309, 0.00267483, 0.00259498, 0.00364296, 0.00379267, 0.00632777, 0.0203806, 0.00635771};

const float effMC_e24e60_HCP2012_AFII_period2_LoosePP_pt[] = {0.703623, 0.880193, 0.908118, 0.921368, 0.937182, 0.954319, 0.972135, 0.987478, 1.00443, 1.01519, 1.01521, 1.08174, 1.09929, 1.10168, 1.11879};
const float sf_e24e60_HCP2012_AFII_period2_MediumPP_eta[] = {1.05123, 1.00497, 0.93973, 0.98486, 0.80168, 0.99514, 1.02272, 0.97167, 0.99081, 1.00001, 1.00228, 0.99276, 0.99317, 1.01995, 0.98967, 0.79658, 0.97913, 0.95489, 1.0095, 1.05073};
const float errsf_e24e60_HCP2012_AFII_period2_MediumPP_eta[] = {0.0175235, 0.0110115, 0.0118244, 0.0109052, 0.0251441, 0.0104092, 0.0102887, 0.010449, 0.0101336, 0.0110622, 0.0109052, 0.0101537, 0.0103607, 0.0102887, 0.0104636, 0.0307987, 0.0110156, 0.0120315, 0.0109132, 0.0170018};

const float effMC_e24e60_HCP2012_AFII_period2_MediumPP_eta[] = {0.74121, 0.86907, 0.89303, 0.88588, 0.78597, 0.94349, 0.91164, 0.94964, 0.95568, 0.92421, 0.92371, 0.95564, 0.94994, 0.91372, 0.94185, 0.79021, 0.88933, 0.89347, 0.87057, 0.75345};
const float sf_e24e60_HCP2012_AFII_period2_MediumPP_pt[] = {1.04072, 0.973692, 0.985303, 0.988474, 0.969166, 0.989538, 0.993271, 1.00041, 1.00284, 1.00246, 1.00859, 0.988334, 0.981439, 0.980024, 1.01279};
const float errsf_e24e60_HCP2012_AFII_period2_MediumPP_pt[] = {0.0150427, 0.00928253, 0.00744609, 0.00689416, 0.00646265, 0.00464628, 0.00284999, 0.00169594, 0.00156549, 0.00181637, 0.00229805, 0.0027095, 0.00508783, 0.0201105, 0.0034822};

const float effMC_e24e60_HCP2012_AFII_period2_MediumPP_pt[] = {0.741495, 0.924377, 0.949175, 0.96053, 0.970022, 0.97083, 0.981991, 0.992226, 0.999222, 1.00464, 1.00456, 1.04814, 1.05631, 1.05577, 1.06644};
const float sf_e24e60_HCP2012_AFII_period2_ML_eta[] = {0.93838, 0.99369, 0.9425, 0.98082, 0.89407, 0.98826, 1.03244, 1.00118, 0.99561, 1.01135, 1.01499, 0.99782, 1.02048, 1.03019, 0.9809, 0.88981, 0.97322, 0.95841, 0.99316, 0.91487};
const float errsf_e24e60_HCP2012_AFII_period2_ML_eta[] = {0.0188595, 0.0127875, 0.0134403, 0.0116568, 0.0285019, 0.0112163, 0.0106522, 0.0108308, 0.0105367, 0.0115503, 0.011626, 0.0105026, 0.0106522, 0.01073, 0.0116311, 0.0309311, 0.0117661, 0.0137244, 0.012825, 0.0176633};

const float effMC_e24e60_HCP2012_AFII_period2_ML_eta[] = {0.73081, 0.82816, 0.83937, 0.84263, 0.632, 0.90308, 0.85611, 0.88205, 0.90694, 0.87501, 0.87063, 0.90319, 0.88436, 0.85703, 0.90133, 0.63611, 0.84673, 0.84195, 0.82958, 0.74129};
const float sf_e24e60_HCP2012_AFII_period2_ML_pt[] = {1.02719, 0.962556, 0.99388, 0.990694, 0.970109, 0.989783, 0.988981, 1.00076, 1.00402, 1.00128, 1.00938, 0.983121, 0.982951, 0.998648, 1.03124};
const float errsf_e24e60_HCP2012_AFII_period2_ML_pt[] = {0.0239412, 0.0134331, 0.0103177, 0.0106984, 0.00943623, 0.00689186, 0.00546941, 0.00352607, 0.00252434, 0.00233401, 0.00337581, 0.00374644, 0.00654125, 0.0205554, 0.00714229};

const float effMC_e24e60_HCP2012_AFII_period2_ML_pt[] = {0.69905, 0.875485, 0.903181, 0.917756, 0.933161, 0.951939, 0.970581, 0.988837, 1.00558, 1.01703, 1.01978, 1.07053, 1.08465, 1.09165, 1.10351};
const float sf_e24e60_HCP2012_AFII_period2_TightPP_eta[] = {1.04867, 1.01244, 0.9475, 0.99382, 0.80944, 0.99793, 1.02759, 0.97779, 0.99605, 1.00446, 1.00888, 0.99819, 0.99988, 1.02728, 0.99414, 0.80526, 0.98227, 0.96786, 1.01557, 1.04439};
const float errsf_e24e60_HCP2012_AFII_period2_TightPP_eta[] = {0.0165761, 0.0108853, 0.0118511, 0.0107592, 0.0250524, 0.0105462, 0.0102202, 0.0104814, 0.0101715, 0.0108972, 0.0107372, 0.0101418, 0.0102611, 0.0102958, 0.0103712, 0.031253, 0.0107482, 0.0119214, 0.0109618, 0.016251};

const float effMC_e24e60_HCP2012_AFII_period2_TightPP_eta[] = {0.79244, 0.90733, 0.93346, 0.91881, 0.81254, 0.96709, 0.92943, 0.96488, 0.97012, 0.94044, 0.94013, 0.97054, 0.96472, 0.93083, 0.96602, 0.81615, 0.92283, 0.9358, 0.90998, 0.80531};
const float sf_e24e60_HCP2012_AFII_period2_TightPP_pt[] = {1.03925, 0.972459, 0.984561, 0.985859, 0.974905, 0.991352, 0.994158, 1.00052, 1.00358, 1.00324, 1.0065, 0.989864, 0.983193, 0.981096, 1.0046};
const float errsf_e24e60_HCP2012_AFII_period2_TightPP_pt[] = {0.0162268, 0.00900711, 0.00704991, 0.00613123, 0.0065007, 0.00439371, 0.00352496, 0.00171754, 0.00156776, 0.00159771, 0.00235663, 0.0021669, 0.0042639, 0.0162268, 0.00270613};

const float effMC_e24e60_HCP2012_AFII_period2_TightPP_pt[] = {0.753426, 0.939094, 0.961917, 0.972357, 0.978868, 0.979708, 0.988226, 0.995463, 0.998498, 1.00009, 0.997658, 1.03444, 1.0382, 1.04035, 1.04397};
const float sf_e24e60_HCP2012_AFII_period3_LoosePP_eta[] = {0.98871, 1.00258, 0.95977, 1.01741, 0.90034, 1.01759, 1.06468, 1.00828, 1.00987, 1.06865, 1.05728, 1.01603, 1.04288, 1.06994, 1.01977, 0.91694, 1.021, 0.97146, 1.00278, 0.94429};
const float errsf_e24e60_HCP2012_AFII_period3_LoosePP_eta[] = {0.013367, 0.0117713, 0.0119817, 0.0115203, 0.0331731, 0.0106385, 0.0106941, 0.0103607, 0.0101961, 0.0102934, 0.0102701, 0.0102264, 0.0104519, 0.0105462, 0.0109132, 0.0300903, 0.0113459, 0.0119487, 0.0121155, 0.0127502};

const float effMC_e24e60_HCP2012_AFII_period3_LoosePP_eta[] = {0.72546, 0.81953, 0.82974, 0.83123, 0.63592, 0.87778, 0.83917, 0.87902, 0.90358, 0.85168, 0.84756, 0.90032, 0.87954, 0.84069, 0.87767, 0.63993, 0.83481, 0.83251, 0.82116, 0.7375};
const float sf_e24e60_HCP2012_AFII_period3_LoosePP_pt[] = {0.995788, 0.991408, 0.996594, 0.994188, 0.998902, 0.999314, 1.00477, 1.00834, 1.00836, 1.01201, 0.971049, 0.967091, 0.964498, 0.954706, 0.954706};
const float errsf_e24e60_HCP2012_AFII_period3_LoosePP_pt[] = {0.0109015, 0.00845603, 0.0090453, 0.00799444, 0.00713999, 0.00526415, 0.00396775, 0.00329991, 0.00258297, 0.00275975, 0.00327045, 0.00160085, 0.0025044, 0.00866227, 0.0111667};

const float effMC_e24e60_HCP2012_AFII_period3_LoosePP_pt[] = {0.703623, 0.880193, 0.908118, 0.921368, 0.937182, 0.954319, 0.972135, 0.987478, 1.00443, 1.01519, 1.01521, 1.08174, 1.09929, 1.10168, 1.11879};
const float sf_e24e60_HCP2012_AFII_period3_MediumPP_eta[] = {0.98998, 1.0068, 0.96576, 1.0127, 0.90391, 0.99361, 1.0527, 1.01221, 1.00846, 1.05523, 1.04981, 1.0147, 1.04437, 1.05824, 0.99738, 0.92378, 1.01515, 0.9758, 1.00967, 0.94718};
const float errsf_e24e60_HCP2012_AFII_period3_MediumPP_eta[] = {0.0126761, 0.011313, 0.0112897, 0.0110325, 0.0329825, 0.0105242, 0.0103633, 0.0102243, 0.0101864, 0.0106249, 0.0109823, 0.010214, 0.0102391, 0.0102633, 0.0106249, 0.0277168, 0.0110837, 0.0110923, 0.0114515, 0.0120705};

const float effMC_e24e60_HCP2012_AFII_period3_MediumPP_eta[] = {0.74121, 0.86907, 0.89303, 0.88588, 0.78597, 0.94349, 0.91164, 0.94964, 0.95568, 0.92421, 0.92371, 0.95564, 0.94994, 0.91372, 0.94185, 0.79021, 0.88933, 0.89347, 0.87057, 0.75345};
const float sf_e24e60_HCP2012_AFII_period3_MediumPP_pt[] = {1.04316, 0.986161, 0.982317, 0.984264, 0.98565, 0.998329, 0.997995, 1.00049, 1.00416, 1.00607, 1.00979, 0.974837, 0.970395, 0.969982, 0.967367};
const float errsf_e24e60_HCP2012_AFII_period3_MediumPP_pt[] = {0.00552405, 0.00314537, 0.00277185, 0.00246715, 0.00233937, 0.00143507, 0.000864976, 0.000609415, 0.000432488, 0.000560268, 0.000697878, 0.000835488, 0.00148422, 0.00585824, 0.00722451};

const float effMC_e24e60_HCP2012_AFII_period3_MediumPP_pt[] = {0.741495, 0.924377, 0.949175, 0.96053, 0.970022, 0.97083, 0.981991, 0.992226, 0.999222, 1.00464, 1.00456, 1.04814, 1.05631, 1.05577, 1.06644};
const float sf_e24e60_HCP2012_AFII_period3_ML_eta[] = {0.98957, 1.0078, 0.96362, 1.01286, 0.90305, 0.99403, 1.05246, 1.01141, 1.00773, 1.05471, 1.04921, 1.01427, 1.04437, 1.05771, 0.99769, 0.92149, 1.01487, 0.97497, 1.01012, 0.94795};
const float errsf_e24e60_HCP2012_AFII_period3_ML_eta[] = {0.0125906, 0.0118458, 0.0117241, 0.0112436, 0.032792, 0.0106014, 0.0105087, 0.0102566, 0.0102161, 0.0108853, 0.0112804, 0.0102202, 0.0103005, 0.0103927, 0.0106556, 0.028633, 0.0112073, 0.0114661, 0.0121552, 0.0121495};

const float effMC_e24e60_HCP2012_AFII_period3_ML_eta[] = {0.73081, 0.82816, 0.83937, 0.84263, 0.632, 0.90308, 0.85611, 0.88205, 0.90694, 0.87501, 0.87063, 0.90319, 0.88436, 0.85703, 0.90133, 0.63611, 0.84673, 0.84195, 0.82958, 0.74129};
const float sf_e24e60_HCP2012_AFII_period3_ML_pt[] = {1.04294, 0.989642, 0.988256, 0.991265, 0.991108, 0.996733, 0.996477, 1.0004, 1.00461, 1.00524, 1.00765, 0.973062, 0.968951, 0.959057, 0.957336};
const float errsf_e24e60_HCP2012_AFII_period3_ML_pt[] = {0.0108965, 0.00788716, 0.00845756, 0.00742495, 0.00682505, 0.00515321, 0.00425828, 0.003147, 0.00198654, 0.00214389, 0.00244876, 0.00167184, 0.00236025, 0.00813302, 0.0113882};

const float effMC_e24e60_HCP2012_AFII_period3_ML_pt[] = {0.69905, 0.875485, 0.903181, 0.917756, 0.933161, 0.951939, 0.970581, 0.988837, 1.00558, 1.01703, 1.01978, 1.07053, 1.08465, 1.09165, 1.10351};
const float sf_e24e60_HCP2012_AFII_period3_TightPP_eta[] = {1.08864, 1.01884, 0.96282, 1.01146, 0.81843, 1.00369, 1.04313, 0.98666, 1.00802, 1.03917, 1.03606, 1.00993, 1.0129, 1.047, 1.00338, 0.82378, 1.01051, 0.97067, 1.02107, 1.07761};
const float errsf_e24e60_HCP2012_AFII_period3_TightPP_eta[] = {0.0112073, 0.0102243, 0.0103555, 0.0102887, 0.0308459, 0.0100921, 0.0101256, 0.0100766, 0.0100717, 0.010237, 0.0101884, 0.0100682, 0.0101017, 0.0100816, 0.0101209, 0.028427, 0.0102816, 0.0103792, 0.0102264, 0.011167};

const float effMC_e24e60_HCP2012_AFII_period3_TightPP_eta[] = {0.79244, 0.90733, 0.93346, 0.91881, 0.81254, 0.96709, 0.92943, 0.96488, 0.97012, 0.94044, 0.94013, 0.97054, 0.96472, 0.93083, 0.96602, 0.81615, 0.92283, 0.9358, 0.90998, 0.80531};
const float sf_e24e60_HCP2012_AFII_period3_TightPP_pt[] = {1.04192, 0.983354, 0.983226, 0.982911, 0.986706, 0.99618, 0.997363, 1.00053, 1.00378, 1.00617, 1.0094, 0.979095, 0.974728, 0.968162, 0.969247};
const float errsf_e24e60_HCP2012_AFII_period3_TightPP_pt[] = {0.00768954, 0.0042884, 0.00474188, 0.00371661, 0.0042884, 0.00277021, 0.00205054, 0.00127173, 0.000759096, 0.000749237, 0.000867538, 0.000690087, 0.00127173, 0.0052348, 0.00686144};

const float effMC_e24e60_HCP2012_AFII_period3_TightPP_pt[] = {0.753426, 0.939094, 0.961917, 0.972357, 0.978868, 0.979708, 0.988226, 0.995463, 0.998498, 1.00009, 0.997658, 1.03444, 1.0382, 1.04035, 1.04397};

 efficienciesRel172HCP_e24vhi_medium1_LoosePP.resize(4);
 uncertaintiesRel172HCP_e24vhi_medium1_LoosePP.resize(4);
 efficienciesRel172HCP_e24vhi_medium1_LoosePPET.resize(4);
 uncertaintiesRel172HCP_e24vhi_medium1_LoosePPET.resize(4);
 
 MCefficienciesRel172HCP_e24vhi_medium1_LoosePP.resize(4);
 MCefficienciesRel172HCP_e24vhi_medium1_LoosePPET.resize(4);
 
 efficienciesRel172HCP_e24vhi_medium1_MediumPP.resize(4);
 uncertaintiesRel172HCP_e24vhi_medium1_MediumPP.resize(4);
 efficienciesRel172HCP_e24vhi_medium1_MediumPPET.resize(4);
 uncertaintiesRel172HCP_e24vhi_medium1_MediumPPET.resize(4);
 
 MCefficienciesRel172HCP_e24vhi_medium1_MediumPP.resize(4);
 MCefficienciesRel172HCP_e24vhi_medium1_MediumPPET.resize(4);
 
 efficienciesRel172HCP_e24vhi_medium1_TightPP.resize(4);
 uncertaintiesRel172HCP_e24vhi_medium1_TightPP.resize(4);
 efficienciesRel172HCP_e24vhi_medium1_TightPPET.resize(4);
 uncertaintiesRel172HCP_e24vhi_medium1_TightPPET.resize(4);
 
 MCefficienciesRel172HCP_e24vhi_medium1_TightPP.resize(4);
 MCefficienciesRel172HCP_e24vhi_medium1_TightPPET.resize(4);

 efficienciesRel172HCP_e24vhi_medium1_ML.resize(4);
 uncertaintiesRel172HCP_e24vhi_medium1_ML.resize(4);
 efficienciesRel172HCP_e24vhi_medium1_MLET.resize(4);
 uncertaintiesRel172HCP_e24vhi_medium1_MLET.resize(4);
 
 MCefficienciesRel172HCP_e24vhi_medium1_ML.resize(4);
 MCefficienciesRel172HCP_e24vhi_medium1_MLET.resize(4);

  copyToVector(sf_e24e60_HCP2012_period0_LoosePP_eta, 20, efficienciesRel172HCP_e24vhi_medium1_LoosePP[0]);
  copyToVector(errsf_e24e60_HCP2012_period0_LoosePP_eta, 20, uncertaintiesRel172HCP_e24vhi_medium1_LoosePP[0]);
  copyToVector(sf_e24e60_HCP2012_period0_LoosePP_pt, 15, efficienciesRel172HCP_e24vhi_medium1_LoosePPET[0]);
  copyToVector(errsf_e24e60_HCP2012_period0_LoosePP_pt, 15, uncertaintiesRel172HCP_e24vhi_medium1_LoosePPET[0]);

  copyToVector(sf_e24e60_HCP2012_period0_MediumPP_eta, 20, efficienciesRel172HCP_e24vhi_medium1_MediumPP[0]);
  copyToVector(errsf_e24e60_HCP2012_period0_MediumPP_eta, 20, uncertaintiesRel172HCP_e24vhi_medium1_MediumPP[0]);
  copyToVector(sf_e24e60_HCP2012_period0_MediumPP_pt, 15, efficienciesRel172HCP_e24vhi_medium1_MediumPPET[0]);
  copyToVector(errsf_e24e60_HCP2012_period0_MediumPP_pt, 15, uncertaintiesRel172HCP_e24vhi_medium1_MediumPPET[0]);

  copyToVector(sf_e24e60_HCP2012_period0_TightPP_eta, 20, efficienciesRel172HCP_e24vhi_medium1_TightPP[0]);
  copyToVector(errsf_e24e60_HCP2012_period0_TightPP_eta, 20, uncertaintiesRel172HCP_e24vhi_medium1_TightPP[0]);
  copyToVector(sf_e24e60_HCP2012_period0_TightPP_pt, 15, efficienciesRel172HCP_e24vhi_medium1_TightPPET[0]);
  copyToVector(errsf_e24e60_HCP2012_period0_TightPP_pt, 15, uncertaintiesRel172HCP_e24vhi_medium1_TightPPET[0]);

  copyToVector(sf_e24e60_HCP2012_period0_ML_eta, 20, efficienciesRel172HCP_e24vhi_medium1_ML[0]);
  copyToVector(errsf_e24e60_HCP2012_period0_ML_eta, 20, uncertaintiesRel172HCP_e24vhi_medium1_ML[0]);
  copyToVector(sf_e24e60_HCP2012_period0_ML_pt, 15, efficienciesRel172HCP_e24vhi_medium1_MLET[0]);
  copyToVector(errsf_e24e60_HCP2012_period0_ML_pt, 15, uncertaintiesRel172HCP_e24vhi_medium1_MLET[0]);

  copyToVector(effMC_e24e60_HCP2012_period0_LoosePP_eta, 20, MCefficienciesRel172HCP_e24vhi_medium1_LoosePP[0]);
  copyToVector(effMC_e24e60_HCP2012_period0_LoosePP_pt, 15, MCefficienciesRel172HCP_e24vhi_medium1_LoosePPET[0]);
  copyToVector(effMC_e24e60_HCP2012_period0_MediumPP_eta, 20, MCefficienciesRel172HCP_e24vhi_medium1_MediumPP[0]);
  copyToVector(effMC_e24e60_HCP2012_period0_MediumPP_pt, 15, MCefficienciesRel172HCP_e24vhi_medium1_MediumPPET[0]);
  copyToVector(effMC_e24e60_HCP2012_period0_TightPP_eta, 20, MCefficienciesRel172HCP_e24vhi_medium1_TightPP[0]);
  copyToVector(effMC_e24e60_HCP2012_period0_TightPP_pt, 15, MCefficienciesRel172HCP_e24vhi_medium1_TightPPET[0]);
  copyToVector(effMC_e24e60_HCP2012_period0_ML_eta, 20, MCefficienciesRel172HCP_e24vhi_medium1_ML[0]);
  copyToVector(effMC_e24e60_HCP2012_period0_ML_pt, 15, MCefficienciesRel172HCP_e24vhi_medium1_MLET[0]);

  copyToVector(sf_e24e60_HCP2012_period1_LoosePP_eta, 20, efficienciesRel172HCP_e24vhi_medium1_LoosePP[1]);
  copyToVector(errsf_e24e60_HCP2012_period1_LoosePP_eta, 20, uncertaintiesRel172HCP_e24vhi_medium1_LoosePP[1]);
  copyToVector(sf_e24e60_HCP2012_period1_LoosePP_pt, 15, efficienciesRel172HCP_e24vhi_medium1_LoosePPET[1]);
  copyToVector(errsf_e24e60_HCP2012_period1_LoosePP_pt, 15, uncertaintiesRel172HCP_e24vhi_medium1_LoosePPET[1]);

  copyToVector(sf_e24e60_HCP2012_period1_MediumPP_eta, 20, efficienciesRel172HCP_e24vhi_medium1_MediumPP[1]);
  copyToVector(errsf_e24e60_HCP2012_period1_MediumPP_eta, 20, uncertaintiesRel172HCP_e24vhi_medium1_MediumPP[1]);
  copyToVector(sf_e24e60_HCP2012_period1_MediumPP_pt, 15, efficienciesRel172HCP_e24vhi_medium1_MediumPPET[1]);
  copyToVector(errsf_e24e60_HCP2012_period1_MediumPP_pt, 15, uncertaintiesRel172HCP_e24vhi_medium1_MediumPPET[1]);

  copyToVector(sf_e24e60_HCP2012_period1_TightPP_eta, 20, efficienciesRel172HCP_e24vhi_medium1_TightPP[1]);
  copyToVector(errsf_e24e60_HCP2012_period1_TightPP_eta, 20, uncertaintiesRel172HCP_e24vhi_medium1_TightPP[1]);
  copyToVector(sf_e24e60_HCP2012_period1_TightPP_pt, 15, efficienciesRel172HCP_e24vhi_medium1_TightPPET[1]);
  copyToVector(errsf_e24e60_HCP2012_period1_TightPP_pt, 15, uncertaintiesRel172HCP_e24vhi_medium1_TightPPET[1]);

  copyToVector(sf_e24e60_HCP2012_period1_ML_eta, 20, efficienciesRel172HCP_e24vhi_medium1_ML[1]);
  copyToVector(errsf_e24e60_HCP2012_period1_ML_eta, 20, uncertaintiesRel172HCP_e24vhi_medium1_ML[1]);
  copyToVector(sf_e24e60_HCP2012_period1_ML_pt, 15, efficienciesRel172HCP_e24vhi_medium1_MLET[1]);
  copyToVector(errsf_e24e60_HCP2012_period1_ML_pt, 15, uncertaintiesRel172HCP_e24vhi_medium1_MLET[1]);

  copyToVector(effMC_e24e60_HCP2012_period1_LoosePP_eta, 20, MCefficienciesRel172HCP_e24vhi_medium1_LoosePP[1]);
  copyToVector(effMC_e24e60_HCP2012_period1_LoosePP_pt, 15, MCefficienciesRel172HCP_e24vhi_medium1_LoosePPET[1]);
  copyToVector(effMC_e24e60_HCP2012_period1_MediumPP_eta, 20, MCefficienciesRel172HCP_e24vhi_medium1_MediumPP[1]);
  copyToVector(effMC_e24e60_HCP2012_period1_MediumPP_pt, 15, MCefficienciesRel172HCP_e24vhi_medium1_MediumPPET[1]);
  copyToVector(effMC_e24e60_HCP2012_period1_TightPP_eta, 20, MCefficienciesRel172HCP_e24vhi_medium1_TightPP[1]);
  copyToVector(effMC_e24e60_HCP2012_period1_TightPP_pt, 15, MCefficienciesRel172HCP_e24vhi_medium1_TightPPET[1]);
  copyToVector(effMC_e24e60_HCP2012_period1_ML_eta, 20, MCefficienciesRel172HCP_e24vhi_medium1_ML[1]);
  copyToVector(effMC_e24e60_HCP2012_period1_ML_pt, 15, MCefficienciesRel172HCP_e24vhi_medium1_MLET[1]);

  copyToVector(sf_e24e60_HCP2012_period2_LoosePP_eta, 20, efficienciesRel172HCP_e24vhi_medium1_LoosePP[2]);
  copyToVector(errsf_e24e60_HCP2012_period2_LoosePP_eta, 20, uncertaintiesRel172HCP_e24vhi_medium1_LoosePP[2]);
  copyToVector(sf_e24e60_HCP2012_period2_LoosePP_pt, 15, efficienciesRel172HCP_e24vhi_medium1_LoosePPET[2]);
  copyToVector(errsf_e24e60_HCP2012_period2_LoosePP_pt, 15, uncertaintiesRel172HCP_e24vhi_medium1_LoosePPET[2]);

  copyToVector(sf_e24e60_HCP2012_period2_MediumPP_eta, 20, efficienciesRel172HCP_e24vhi_medium1_MediumPP[2]);
  copyToVector(errsf_e24e60_HCP2012_period2_MediumPP_eta, 20, uncertaintiesRel172HCP_e24vhi_medium1_MediumPP[2]);
  copyToVector(sf_e24e60_HCP2012_period2_MediumPP_pt, 15, efficienciesRel172HCP_e24vhi_medium1_MediumPPET[2]);
  copyToVector(errsf_e24e60_HCP2012_period2_MediumPP_pt, 15, uncertaintiesRel172HCP_e24vhi_medium1_MediumPPET[2]);

  copyToVector(sf_e24e60_HCP2012_period2_TightPP_eta, 20, efficienciesRel172HCP_e24vhi_medium1_TightPP[2]);
  copyToVector(errsf_e24e60_HCP2012_period2_TightPP_eta, 20, uncertaintiesRel172HCP_e24vhi_medium1_TightPP[2]);
  copyToVector(sf_e24e60_HCP2012_period2_TightPP_pt, 15, efficienciesRel172HCP_e24vhi_medium1_TightPPET[2]);
  copyToVector(errsf_e24e60_HCP2012_period2_TightPP_pt, 15, uncertaintiesRel172HCP_e24vhi_medium1_TightPPET[2]);

  copyToVector(sf_e24e60_HCP2012_period2_ML_eta, 20, efficienciesRel172HCP_e24vhi_medium1_ML[2]);
  copyToVector(errsf_e24e60_HCP2012_period2_ML_eta, 20, uncertaintiesRel172HCP_e24vhi_medium1_ML[2]);
  copyToVector(sf_e24e60_HCP2012_period2_ML_pt, 15, efficienciesRel172HCP_e24vhi_medium1_MLET[2]);
  copyToVector(errsf_e24e60_HCP2012_period2_ML_pt, 15, uncertaintiesRel172HCP_e24vhi_medium1_MLET[2]);

  copyToVector(effMC_e24e60_HCP2012_period2_LoosePP_eta, 20, MCefficienciesRel172HCP_e24vhi_medium1_LoosePP[2]);
  copyToVector(effMC_e24e60_HCP2012_period2_LoosePP_pt, 15, MCefficienciesRel172HCP_e24vhi_medium1_LoosePPET[2]);
  copyToVector(effMC_e24e60_HCP2012_period2_MediumPP_eta, 20, MCefficienciesRel172HCP_e24vhi_medium1_MediumPP[2]);
  copyToVector(effMC_e24e60_HCP2012_period2_MediumPP_pt, 15, MCefficienciesRel172HCP_e24vhi_medium1_MediumPPET[2]);
  copyToVector(effMC_e24e60_HCP2012_period2_TightPP_eta, 20, MCefficienciesRel172HCP_e24vhi_medium1_TightPP[2]);
  copyToVector(effMC_e24e60_HCP2012_period2_TightPP_pt, 15, MCefficienciesRel172HCP_e24vhi_medium1_TightPPET[2]);
  copyToVector(effMC_e24e60_HCP2012_period2_ML_eta, 20, MCefficienciesRel172HCP_e24vhi_medium1_ML[2]);
  copyToVector(effMC_e24e60_HCP2012_period2_ML_pt, 15, MCefficienciesRel172HCP_e24vhi_medium1_MLET[2]);

  copyToVector(sf_e24e60_HCP2012_period3_LoosePP_eta, 20, efficienciesRel172HCP_e24vhi_medium1_LoosePP[3]);
  copyToVector(errsf_e24e60_HCP2012_period3_LoosePP_eta, 20, uncertaintiesRel172HCP_e24vhi_medium1_LoosePP[3]);
  copyToVector(sf_e24e60_HCP2012_period3_LoosePP_pt, 15, efficienciesRel172HCP_e24vhi_medium1_LoosePPET[3]);
  copyToVector(errsf_e24e60_HCP2012_period3_LoosePP_pt, 15, uncertaintiesRel172HCP_e24vhi_medium1_LoosePPET[3]);

  copyToVector(sf_e24e60_HCP2012_period3_MediumPP_eta, 20, efficienciesRel172HCP_e24vhi_medium1_MediumPP[3]);
  copyToVector(errsf_e24e60_HCP2012_period3_MediumPP_eta, 20, uncertaintiesRel172HCP_e24vhi_medium1_MediumPP[3]);
  copyToVector(sf_e24e60_HCP2012_period3_MediumPP_pt, 15, efficienciesRel172HCP_e24vhi_medium1_MediumPPET[3]);
  copyToVector(errsf_e24e60_HCP2012_period3_MediumPP_pt, 15, uncertaintiesRel172HCP_e24vhi_medium1_MediumPPET[3]);

  copyToVector(sf_e24e60_HCP2012_period3_TightPP_eta, 20, efficienciesRel172HCP_e24vhi_medium1_TightPP[3]);
  copyToVector(errsf_e24e60_HCP2012_period3_TightPP_eta, 20, uncertaintiesRel172HCP_e24vhi_medium1_TightPP[3]);
  copyToVector(sf_e24e60_HCP2012_period3_TightPP_pt, 15, efficienciesRel172HCP_e24vhi_medium1_TightPPET[3]);
  copyToVector(errsf_e24e60_HCP2012_period3_TightPP_pt, 15, uncertaintiesRel172HCP_e24vhi_medium1_TightPPET[3]);

  copyToVector(sf_e24e60_HCP2012_period3_ML_eta, 20, efficienciesRel172HCP_e24vhi_medium1_ML[3]);
  copyToVector(errsf_e24e60_HCP2012_period3_ML_eta, 20, uncertaintiesRel172HCP_e24vhi_medium1_ML[3]);
  copyToVector(sf_e24e60_HCP2012_period3_ML_pt, 15, efficienciesRel172HCP_e24vhi_medium1_MLET[3]);
  copyToVector(errsf_e24e60_HCP2012_period3_ML_pt, 15, uncertaintiesRel172HCP_e24vhi_medium1_MLET[3]);

  copyToVector(effMC_e24e60_HCP2012_period3_LoosePP_eta, 20, MCefficienciesRel172HCP_e24vhi_medium1_LoosePP[3]);
  copyToVector(effMC_e24e60_HCP2012_period3_LoosePP_pt, 15, MCefficienciesRel172HCP_e24vhi_medium1_LoosePPET[3]);
  copyToVector(effMC_e24e60_HCP2012_period3_MediumPP_eta, 20, MCefficienciesRel172HCP_e24vhi_medium1_MediumPP[3]);
  copyToVector(effMC_e24e60_HCP2012_period3_MediumPP_pt, 15, MCefficienciesRel172HCP_e24vhi_medium1_MediumPPET[3]);
  copyToVector(effMC_e24e60_HCP2012_period3_TightPP_eta, 20, MCefficienciesRel172HCP_e24vhi_medium1_TightPP[3]);
  copyToVector(effMC_e24e60_HCP2012_period3_TightPP_pt, 15, MCefficienciesRel172HCP_e24vhi_medium1_TightPPET[3]);
  copyToVector(effMC_e24e60_HCP2012_period3_ML_eta, 20, MCefficienciesRel172HCP_e24vhi_medium1_ML[3]);
  copyToVector(effMC_e24e60_HCP2012_period3_ML_pt, 15, MCefficienciesRel172HCP_e24vhi_medium1_MLET[3]);




 efficienciesRel172HCP_AFII_e24vhi_medium1_LoosePP.resize(4);
 uncertaintiesRel172HCP_AFII_e24vhi_medium1_LoosePP.resize(4);
 efficienciesRel172HCP_AFII_e24vhi_medium1_LoosePPET.resize(4);
 uncertaintiesRel172HCP_AFII_e24vhi_medium1_LoosePPET.resize(4);
 
 MCefficienciesRel172HCP_AFII_e24vhi_medium1_LoosePP.resize(4);
 MCefficienciesRel172HCP_AFII_e24vhi_medium1_LoosePPET.resize(4);
 
 efficienciesRel172HCP_AFII_e24vhi_medium1_MediumPP.resize(4);
 uncertaintiesRel172HCP_AFII_e24vhi_medium1_MediumPP.resize(4);
 efficienciesRel172HCP_AFII_e24vhi_medium1_MediumPPET.resize(4);
 uncertaintiesRel172HCP_AFII_e24vhi_medium1_MediumPPET.resize(4);
 
 MCefficienciesRel172HCP_AFII_e24vhi_medium1_MediumPP.resize(4);
 MCefficienciesRel172HCP_AFII_e24vhi_medium1_MediumPPET.resize(4);
 
 efficienciesRel172HCP_AFII_e24vhi_medium1_TightPP.resize(4);
 uncertaintiesRel172HCP_AFII_e24vhi_medium1_TightPP.resize(4);
 efficienciesRel172HCP_AFII_e24vhi_medium1_TightPPET.resize(4);
 uncertaintiesRel172HCP_AFII_e24vhi_medium1_TightPPET.resize(4);
 
 MCefficienciesRel172HCP_AFII_e24vhi_medium1_TightPP.resize(4);
 MCefficienciesRel172HCP_AFII_e24vhi_medium1_TightPPET.resize(4);

 efficienciesRel172HCP_AFII_e24vhi_medium1_ML.resize(4);
 uncertaintiesRel172HCP_AFII_e24vhi_medium1_ML.resize(4);
 efficienciesRel172HCP_AFII_e24vhi_medium1_MLET.resize(4);
 uncertaintiesRel172HCP_AFII_e24vhi_medium1_MLET.resize(4);
 
 MCefficienciesRel172HCP_AFII_e24vhi_medium1_ML.resize(4);
 MCefficienciesRel172HCP_AFII_e24vhi_medium1_MLET.resize(4);

  copyToVector(sf_e24e60_HCP2012_AFII_period0_LoosePP_eta, 20, efficienciesRel172HCP_AFII_e24vhi_medium1_LoosePP[0]);
  copyToVector(errsf_e24e60_HCP2012_AFII_period0_LoosePP_eta, 20, uncertaintiesRel172HCP_AFII_e24vhi_medium1_LoosePP[0]);
  copyToVector(sf_e24e60_HCP2012_AFII_period0_LoosePP_pt, 15, efficienciesRel172HCP_AFII_e24vhi_medium1_LoosePPET[0]);
  copyToVector(errsf_e24e60_HCP2012_AFII_period0_LoosePP_pt, 15, uncertaintiesRel172HCP_AFII_e24vhi_medium1_LoosePPET[0]);

  copyToVector(sf_e24e60_HCP2012_AFII_period0_MediumPP_eta, 20, efficienciesRel172HCP_AFII_e24vhi_medium1_MediumPP[0]);
  copyToVector(errsf_e24e60_HCP2012_AFII_period0_MediumPP_eta, 20, uncertaintiesRel172HCP_AFII_e24vhi_medium1_MediumPP[0]);
  copyToVector(sf_e24e60_HCP2012_AFII_period0_MediumPP_pt, 15, efficienciesRel172HCP_AFII_e24vhi_medium1_MediumPPET[0]);
  copyToVector(errsf_e24e60_HCP2012_AFII_period0_MediumPP_pt, 15, uncertaintiesRel172HCP_AFII_e24vhi_medium1_MediumPPET[0]);

  copyToVector(sf_e24e60_HCP2012_AFII_period0_TightPP_eta, 20, efficienciesRel172HCP_AFII_e24vhi_medium1_TightPP[0]);
  copyToVector(errsf_e24e60_HCP2012_AFII_period0_TightPP_eta, 20, uncertaintiesRel172HCP_AFII_e24vhi_medium1_TightPP[0]);
  copyToVector(sf_e24e60_HCP2012_AFII_period0_TightPP_pt, 15, efficienciesRel172HCP_AFII_e24vhi_medium1_TightPPET[0]);
  copyToVector(errsf_e24e60_HCP2012_AFII_period0_TightPP_pt, 15, uncertaintiesRel172HCP_AFII_e24vhi_medium1_TightPPET[0]);

  copyToVector(sf_e24e60_HCP2012_AFII_period0_ML_eta, 20, efficienciesRel172HCP_AFII_e24vhi_medium1_ML[0]);
  copyToVector(errsf_e24e60_HCP2012_AFII_period0_ML_eta, 20, uncertaintiesRel172HCP_AFII_e24vhi_medium1_ML[0]);
  copyToVector(sf_e24e60_HCP2012_AFII_period0_ML_pt, 15, efficienciesRel172HCP_AFII_e24vhi_medium1_MLET[0]);
  copyToVector(errsf_e24e60_HCP2012_AFII_period0_ML_pt, 15, uncertaintiesRel172HCP_AFII_e24vhi_medium1_MLET[0]);

  copyToVector(effMC_e24e60_HCP2012_AFII_period0_LoosePP_eta, 20, MCefficienciesRel172HCP_AFII_e24vhi_medium1_LoosePP[0]);
  copyToVector(effMC_e24e60_HCP2012_AFII_period0_LoosePP_pt, 15, MCefficienciesRel172HCP_AFII_e24vhi_medium1_LoosePPET[0]);
  copyToVector(effMC_e24e60_HCP2012_AFII_period0_MediumPP_eta, 20, MCefficienciesRel172HCP_AFII_e24vhi_medium1_MediumPP[0]);
  copyToVector(effMC_e24e60_HCP2012_AFII_period0_MediumPP_pt, 15, MCefficienciesRel172HCP_AFII_e24vhi_medium1_MediumPPET[0]);
  copyToVector(effMC_e24e60_HCP2012_AFII_period0_TightPP_eta, 20, MCefficienciesRel172HCP_AFII_e24vhi_medium1_TightPP[0]);
  copyToVector(effMC_e24e60_HCP2012_AFII_period0_TightPP_pt, 15, MCefficienciesRel172HCP_AFII_e24vhi_medium1_TightPPET[0]);
  copyToVector(effMC_e24e60_HCP2012_AFII_period0_ML_eta, 20, MCefficienciesRel172HCP_AFII_e24vhi_medium1_ML[0]);
  copyToVector(effMC_e24e60_HCP2012_AFII_period0_ML_pt, 15, MCefficienciesRel172HCP_AFII_e24vhi_medium1_MLET[0]);

  copyToVector(sf_e24e60_HCP2012_AFII_period1_LoosePP_eta, 20, efficienciesRel172HCP_AFII_e24vhi_medium1_LoosePP[1]);
  copyToVector(errsf_e24e60_HCP2012_AFII_period1_LoosePP_eta, 20, uncertaintiesRel172HCP_AFII_e24vhi_medium1_LoosePP[1]);
  copyToVector(sf_e24e60_HCP2012_AFII_period1_LoosePP_pt, 15, efficienciesRel172HCP_AFII_e24vhi_medium1_LoosePPET[1]);
  copyToVector(errsf_e24e60_HCP2012_AFII_period1_LoosePP_pt, 15, uncertaintiesRel172HCP_AFII_e24vhi_medium1_LoosePPET[1]);

  copyToVector(sf_e24e60_HCP2012_AFII_period1_MediumPP_eta, 20, efficienciesRel172HCP_AFII_e24vhi_medium1_MediumPP[1]);
  copyToVector(errsf_e24e60_HCP2012_AFII_period1_MediumPP_eta, 20, uncertaintiesRel172HCP_AFII_e24vhi_medium1_MediumPP[1]);
  copyToVector(sf_e24e60_HCP2012_AFII_period1_MediumPP_pt, 15, efficienciesRel172HCP_AFII_e24vhi_medium1_MediumPPET[1]);
  copyToVector(errsf_e24e60_HCP2012_AFII_period1_MediumPP_pt, 15, uncertaintiesRel172HCP_AFII_e24vhi_medium1_MediumPPET[1]);

  copyToVector(sf_e24e60_HCP2012_AFII_period1_TightPP_eta, 20, efficienciesRel172HCP_AFII_e24vhi_medium1_TightPP[1]);
  copyToVector(errsf_e24e60_HCP2012_AFII_period1_TightPP_eta, 20, uncertaintiesRel172HCP_AFII_e24vhi_medium1_TightPP[1]);
  copyToVector(sf_e24e60_HCP2012_AFII_period1_TightPP_pt, 15, efficienciesRel172HCP_AFII_e24vhi_medium1_TightPPET[1]);
  copyToVector(errsf_e24e60_HCP2012_AFII_period1_TightPP_pt, 15, uncertaintiesRel172HCP_AFII_e24vhi_medium1_TightPPET[1]);

  copyToVector(sf_e24e60_HCP2012_AFII_period1_ML_eta, 20, efficienciesRel172HCP_AFII_e24vhi_medium1_ML[1]);
  copyToVector(errsf_e24e60_HCP2012_AFII_period1_ML_eta, 20, uncertaintiesRel172HCP_AFII_e24vhi_medium1_ML[1]);
  copyToVector(sf_e24e60_HCP2012_AFII_period1_ML_pt, 15, efficienciesRel172HCP_AFII_e24vhi_medium1_MLET[1]);
  copyToVector(errsf_e24e60_HCP2012_AFII_period1_ML_pt, 15, uncertaintiesRel172HCP_AFII_e24vhi_medium1_MLET[1]);

  copyToVector(effMC_e24e60_HCP2012_AFII_period1_LoosePP_eta, 20, MCefficienciesRel172HCP_AFII_e24vhi_medium1_LoosePP[1]);
  copyToVector(effMC_e24e60_HCP2012_AFII_period1_LoosePP_pt, 15, MCefficienciesRel172HCP_AFII_e24vhi_medium1_LoosePPET[1]);
  copyToVector(effMC_e24e60_HCP2012_AFII_period1_MediumPP_eta, 20, MCefficienciesRel172HCP_AFII_e24vhi_medium1_MediumPP[1]);
  copyToVector(effMC_e24e60_HCP2012_AFII_period1_MediumPP_pt, 15, MCefficienciesRel172HCP_AFII_e24vhi_medium1_MediumPPET[1]);
  copyToVector(effMC_e24e60_HCP2012_AFII_period1_TightPP_eta, 20, MCefficienciesRel172HCP_AFII_e24vhi_medium1_TightPP[1]);
  copyToVector(effMC_e24e60_HCP2012_AFII_period1_TightPP_pt, 15, MCefficienciesRel172HCP_AFII_e24vhi_medium1_TightPPET[1]);
  copyToVector(effMC_e24e60_HCP2012_AFII_period1_ML_eta, 20, MCefficienciesRel172HCP_AFII_e24vhi_medium1_ML[1]);
  copyToVector(effMC_e24e60_HCP2012_AFII_period1_ML_pt, 15, MCefficienciesRel172HCP_AFII_e24vhi_medium1_MLET[1]);

  copyToVector(sf_e24e60_HCP2012_AFII_period2_LoosePP_eta, 20, efficienciesRel172HCP_AFII_e24vhi_medium1_LoosePP[2]);
  copyToVector(errsf_e24e60_HCP2012_AFII_period2_LoosePP_eta, 20, uncertaintiesRel172HCP_AFII_e24vhi_medium1_LoosePP[2]);
  copyToVector(sf_e24e60_HCP2012_AFII_period2_LoosePP_pt, 15, efficienciesRel172HCP_AFII_e24vhi_medium1_LoosePPET[2]);
  copyToVector(errsf_e24e60_HCP2012_AFII_period2_LoosePP_pt, 15, uncertaintiesRel172HCP_AFII_e24vhi_medium1_LoosePPET[2]);

  copyToVector(sf_e24e60_HCP2012_AFII_period2_MediumPP_eta, 20, efficienciesRel172HCP_AFII_e24vhi_medium1_MediumPP[2]);
  copyToVector(errsf_e24e60_HCP2012_AFII_period2_MediumPP_eta, 20, uncertaintiesRel172HCP_AFII_e24vhi_medium1_MediumPP[2]);
  copyToVector(sf_e24e60_HCP2012_AFII_period2_MediumPP_pt, 15, efficienciesRel172HCP_AFII_e24vhi_medium1_MediumPPET[2]);
  copyToVector(errsf_e24e60_HCP2012_AFII_period2_MediumPP_pt, 15, uncertaintiesRel172HCP_AFII_e24vhi_medium1_MediumPPET[2]);

  copyToVector(sf_e24e60_HCP2012_AFII_period2_TightPP_eta, 20, efficienciesRel172HCP_AFII_e24vhi_medium1_TightPP[2]);
  copyToVector(errsf_e24e60_HCP2012_AFII_period2_TightPP_eta, 20, uncertaintiesRel172HCP_AFII_e24vhi_medium1_TightPP[2]);
  copyToVector(sf_e24e60_HCP2012_AFII_period2_TightPP_pt, 15, efficienciesRel172HCP_AFII_e24vhi_medium1_TightPPET[2]);
  copyToVector(errsf_e24e60_HCP2012_AFII_period2_TightPP_pt, 15, uncertaintiesRel172HCP_AFII_e24vhi_medium1_TightPPET[2]);

  copyToVector(sf_e24e60_HCP2012_AFII_period2_ML_eta, 20, efficienciesRel172HCP_AFII_e24vhi_medium1_ML[2]);
  copyToVector(errsf_e24e60_HCP2012_AFII_period2_ML_eta, 20, uncertaintiesRel172HCP_AFII_e24vhi_medium1_ML[2]);
  copyToVector(sf_e24e60_HCP2012_AFII_period2_ML_pt, 15, efficienciesRel172HCP_AFII_e24vhi_medium1_MLET[2]);
  copyToVector(errsf_e24e60_HCP2012_AFII_period2_ML_pt, 15, uncertaintiesRel172HCP_AFII_e24vhi_medium1_MLET[2]);

  copyToVector(effMC_e24e60_HCP2012_AFII_period2_LoosePP_eta, 20, MCefficienciesRel172HCP_AFII_e24vhi_medium1_LoosePP[2]);
  copyToVector(effMC_e24e60_HCP2012_AFII_period2_LoosePP_pt, 15, MCefficienciesRel172HCP_AFII_e24vhi_medium1_LoosePPET[2]);
  copyToVector(effMC_e24e60_HCP2012_AFII_period2_MediumPP_eta, 20, MCefficienciesRel172HCP_AFII_e24vhi_medium1_MediumPP[2]);
  copyToVector(effMC_e24e60_HCP2012_AFII_period2_MediumPP_pt, 15, MCefficienciesRel172HCP_AFII_e24vhi_medium1_MediumPPET[2]);
  copyToVector(effMC_e24e60_HCP2012_AFII_period2_TightPP_eta, 20, MCefficienciesRel172HCP_AFII_e24vhi_medium1_TightPP[2]);
  copyToVector(effMC_e24e60_HCP2012_AFII_period2_TightPP_pt, 15, MCefficienciesRel172HCP_AFII_e24vhi_medium1_TightPPET[2]);
  copyToVector(effMC_e24e60_HCP2012_AFII_period2_ML_eta, 20, MCefficienciesRel172HCP_AFII_e24vhi_medium1_ML[2]);
  copyToVector(effMC_e24e60_HCP2012_AFII_period2_ML_pt, 15, MCefficienciesRel172HCP_AFII_e24vhi_medium1_MLET[2]);

  copyToVector(sf_e24e60_HCP2012_AFII_period3_LoosePP_eta, 20, efficienciesRel172HCP_AFII_e24vhi_medium1_LoosePP[3]);
  copyToVector(errsf_e24e60_HCP2012_AFII_period3_LoosePP_eta, 20, uncertaintiesRel172HCP_AFII_e24vhi_medium1_LoosePP[3]);
  copyToVector(sf_e24e60_HCP2012_AFII_period3_LoosePP_pt, 15, efficienciesRel172HCP_AFII_e24vhi_medium1_LoosePPET[3]);
  copyToVector(errsf_e24e60_HCP2012_AFII_period3_LoosePP_pt, 15, uncertaintiesRel172HCP_AFII_e24vhi_medium1_LoosePPET[3]);

  copyToVector(sf_e24e60_HCP2012_AFII_period3_MediumPP_eta, 20, efficienciesRel172HCP_AFII_e24vhi_medium1_MediumPP[3]);
  copyToVector(errsf_e24e60_HCP2012_AFII_period3_MediumPP_eta, 20, uncertaintiesRel172HCP_AFII_e24vhi_medium1_MediumPP[3]);
  copyToVector(sf_e24e60_HCP2012_AFII_period3_MediumPP_pt, 15, efficienciesRel172HCP_AFII_e24vhi_medium1_MediumPPET[3]);
  copyToVector(errsf_e24e60_HCP2012_AFII_period3_MediumPP_pt, 15, uncertaintiesRel172HCP_AFII_e24vhi_medium1_MediumPPET[3]);

  copyToVector(sf_e24e60_HCP2012_AFII_period3_TightPP_eta, 20, efficienciesRel172HCP_AFII_e24vhi_medium1_TightPP[3]);
  copyToVector(errsf_e24e60_HCP2012_AFII_period3_TightPP_eta, 20, uncertaintiesRel172HCP_AFII_e24vhi_medium1_TightPP[3]);
  copyToVector(sf_e24e60_HCP2012_AFII_period3_TightPP_pt, 15, efficienciesRel172HCP_AFII_e24vhi_medium1_TightPPET[3]);
  copyToVector(errsf_e24e60_HCP2012_AFII_period3_TightPP_pt, 15, uncertaintiesRel172HCP_AFII_e24vhi_medium1_TightPPET[3]);

  copyToVector(sf_e24e60_HCP2012_AFII_period3_ML_eta, 20, efficienciesRel172HCP_AFII_e24vhi_medium1_ML[3]);
  copyToVector(errsf_e24e60_HCP2012_AFII_period3_ML_eta, 20, uncertaintiesRel172HCP_AFII_e24vhi_medium1_ML[3]);
  copyToVector(sf_e24e60_HCP2012_AFII_period3_ML_pt, 15, efficienciesRel172HCP_AFII_e24vhi_medium1_MLET[3]);
  copyToVector(errsf_e24e60_HCP2012_AFII_period3_ML_pt, 15, uncertaintiesRel172HCP_AFII_e24vhi_medium1_MLET[3]);

  copyToVector(effMC_e24e60_HCP2012_AFII_period3_LoosePP_eta, 20, MCefficienciesRel172HCP_AFII_e24vhi_medium1_LoosePP[3]);
  copyToVector(effMC_e24e60_HCP2012_AFII_period3_LoosePP_pt, 15, MCefficienciesRel172HCP_AFII_e24vhi_medium1_LoosePPET[3]);
  copyToVector(effMC_e24e60_HCP2012_AFII_period3_MediumPP_eta, 20, MCefficienciesRel172HCP_AFII_e24vhi_medium1_MediumPP[3]);
  copyToVector(effMC_e24e60_HCP2012_AFII_period3_MediumPP_pt, 15, MCefficienciesRel172HCP_AFII_e24vhi_medium1_MediumPPET[3]);
  copyToVector(effMC_e24e60_HCP2012_AFII_period3_TightPP_eta, 20, MCefficienciesRel172HCP_AFII_e24vhi_medium1_TightPP[3]);
  copyToVector(effMC_e24e60_HCP2012_AFII_period3_TightPP_pt, 15, MCefficienciesRel172HCP_AFII_e24vhi_medium1_TightPPET[3]);
  copyToVector(effMC_e24e60_HCP2012_AFII_period3_ML_eta, 20, MCefficienciesRel172HCP_AFII_e24vhi_medium1_ML[3]);
  copyToVector(effMC_e24e60_HCP2012_AFII_period3_ML_pt, 15, MCefficienciesRel172HCP_AFII_e24vhi_medium1_MLET[3]);

}

std::pair<float,float> egammaSFclass::scaleFactor(float eta, float ET, int set, int range, int rel,
						  bool etcorrection, int runnumber) {

   std::vector<float> * vectEff=0;
   std::vector<float> * vectUnc=0;
   std::vector<float> * vectEtaBinning=0;

   bool doAbsEta = false;
   int runrange = -1;

   if (rel==12) { //special 2011 Forward electron update, release 17 for 2011 data and G4 FullSim MC11c
     doAbsEta = true;
     vectEtaBinning = &m_FwdEtabins;

     if (set <= 22 || (set >= 25 && set <= 46) || set > 48) { 
       std::cout << "egammaSFclass: ERROR : unsupported set " << set << " for rel=12 (HCP 2012 update of forward electrons), read documentation (and report a bug in case)" << std::endl;
       return std::make_pair(-1.,-1.);
     }
     else if (set==23) {//ForwardLoose electrons
       vectEff = &efficienciesRel17HCPForwardLoose;
       vectUnc = &uncertaintiesRel17HCPForwardLoose;
     }
     else if (set==47) {//ForwardMedium electrons
       vectEff = &efficienciesRel17HCPForwardMedium;
       vectUnc = &uncertaintiesRel17HCPForwardMedium;
     }
     else if (set==24) {//ForwardTight electrons
       vectEff = &efficienciesRel17HCPForwardTight;
       vectUnc = &uncertaintiesRel17HCPForwardTight;
     }
   } else if (rel==9 || rel==11) { //release 17.2 for 2012 data and AFII MC12a, "ICHEP/HCP 2012 recommendations"
     if ((rel==9 && set >= 31 && set <= 46)
	 || (rel==11 && set >= 39 && set <= 46))
       runrange = getRunRange(runnumber, runranges_ICHEP2012);
     else if (rel==11 && set >= 31 && set <= 38)
       runrange = getRunRange(runnumber, runranges_HCP2012);
     
     vectEtaBinning = &m_FineEtabins;
     if (set <= 3 || (set >= 8 && set <= 29) || set > 46) { 
       std::cout << "egammaSFclass: ERROR : unsupported set " << set << " for rel=9 (ICHEP2012 AFII), read documentation (and report a bug in case)" << std::endl;
       return std::make_pair(-1.,-1.);
     }
     else if (set==4) {//Reco + track quality requirements
       // this has implicit ET dependence, so don't confuse the user
       etcorrection = false;
       vectEff = &efficienciesRel172ICHEP_AFIIRecoTrkQual;
       vectUnc = &uncertaintiesRel172ICHEP_AFIIRecoTrkQual;
       if (ET<15000.) {
	 float eff=1.,unc=0.05;
	 if (fabs(eta)<1.37) {
	   eff=1.;unc=0.02;
	 }
	 return std::make_pair(eff,unc);
       }
     }
     else if (set==5) {//Loose++
       if (ET>=15000.) {
	 vectEff = &efficienciesRel172ICHEP_AFIILoosePP1550;
	 vectUnc = &uncertaintiesRel172ICHEP_AFIILoosePP1550;
       } else {
	 vectEff = &efficienciesRel172ICHEP_AFIILoosePP415;
	 vectUnc = &uncertaintiesRel172ICHEP_AFIILoosePP415;
       }
     }
     else if (set==6) {//Medium++
       if (ET>=15000.) {
	 vectEff = &efficienciesRel172ICHEP_AFIIMediumPP1550;
	 vectUnc = &uncertaintiesRel172ICHEP_AFIIMediumPP1550;
       } else {
	 vectEff = &efficienciesRel172ICHEP_AFIIMediumPP415;
	 vectUnc = &uncertaintiesRel172ICHEP_AFIIMediumPP415;
       }
     }
     else if (set==7) {//Tight++
       if (ET>=15000.) {
	 vectEff = &efficienciesRel172ICHEP_AFIITightPP1550;
	 vectUnc = &uncertaintiesRel172ICHEP_AFIITightPP1550;
       } else {
	 vectEff = &efficienciesRel172ICHEP_AFIITightPP415;
	 vectUnc = &uncertaintiesRel172ICHEP_AFIITightPP415;
       }
     }
     else if (set==30) {//MultiLepton
       if (ET>=15000.) {
	 vectEff = &efficienciesRel172ICHEP_AFIIML1550;
	 vectUnc = &uncertaintiesRel172ICHEP_AFIIML1550;
       } else {
	 vectEff = &efficienciesRel172ICHEP_AFIIML415;
	 vectUnc = &uncertaintiesRel172ICHEP_AFIIML415;
       }
     }
     else if (set==31) {//e24vhi_medium1 trigger SF MC11C w.r.t Loose++ offline
       if (rel==9) {
	 vectEff = &efficienciesRel172ICHEP_AFII_e24vhi_medium1_LoosePP[runrange];
	 vectUnc = &uncertaintiesRel172ICHEP_AFII_e24vhi_medium1_LoosePP[runrange];
       } else {
	 vectEff = &efficienciesRel172HCP_AFII_e24vhi_medium1_LoosePP[runrange];
	 vectUnc = &uncertaintiesRel172HCP_AFII_e24vhi_medium1_LoosePP[runrange];
       }
     }
     else if (set==32) {//e24vhi_medium1 MC trigger efficiency w.r.t Loose++ offline
       if (rel==9) {
	 vectEff = &MCefficienciesRel172ICHEP_AFII_e24vhi_medium1_LoosePP[runrange];
	 vectUnc = 0; // no error
       } else {
	 vectEff = &MCefficienciesRel172HCP_AFII_e24vhi_medium1_LoosePP[runrange];
	 vectUnc = 0; // no error
       }
     }
     else if (set==33) {//e24vhi_medium1 trigger SF w.r.t Medium++ offline
       if (rel==9) {
	 vectEff = &efficienciesRel172ICHEP_AFII_e24vhi_medium1_MediumPP[runrange];
	 vectUnc = &uncertaintiesRel172ICHEP_AFII_e24vhi_medium1_MediumPP[runrange];
       } else {
	 vectEff = &efficienciesRel172HCP_AFII_e24vhi_medium1_MediumPP[runrange];
	 vectUnc = &uncertaintiesRel172HCP_AFII_e24vhi_medium1_MediumPP[runrange];
       }
     }
     else if (set==34) {//e24vhi_medium1 MC trigger efficiency w.r.t Medium++ offline
       if (rel==9) {
	 vectEff = &MCefficienciesRel172ICHEP_AFII_e24vhi_medium1_MediumPP[runrange];
	 vectUnc = 0; // no error
       } else {
	 vectEff = &MCefficienciesRel172HCP_AFII_e24vhi_medium1_MediumPP[runrange];
	 vectUnc = 0; // no error
       }
     }
     else if (set==35) {//e24vhi_medium1 trigger SF w.r.t Tight++ offline
       if (rel==9) {
	 vectEff = &efficienciesRel172ICHEP_AFII_e24vhi_medium1_TightPP[runrange];
	 vectUnc = &uncertaintiesRel172ICHEP_AFII_e24vhi_medium1_TightPP[runrange];
       } else {
	 vectEff = &efficienciesRel172HCP_AFII_e24vhi_medium1_TightPP[runrange];
	 vectUnc = &uncertaintiesRel172HCP_AFII_e24vhi_medium1_TightPP[runrange];
       }
     }
     else if (set==36) {//e24vhi_medium1 MC trigger efficiency w.r.t Tight++ offline
       if (rel==9) {
	 vectEff = &MCefficienciesRel172ICHEP_AFII_e24vhi_medium1_TightPP[runrange];
	 vectUnc = 0; // no error
       } else {
	 vectEff = &MCefficienciesRel172HCP_AFII_e24vhi_medium1_TightPP[runrange];
	 vectUnc = 0; // no error
       }
     }
     else if (set==37) {//e24vhi_medium1 trigger SF w.r.t ML offline
       if (rel==9) {
	 vectEff = &efficienciesRel172ICHEP_AFII_e24vhi_medium1_ML[runrange];
	 vectUnc = &uncertaintiesRel172ICHEP_AFII_e24vhi_medium1_ML[runrange];
       } else {
	 vectEff = &efficienciesRel172HCP_AFII_e24vhi_medium1_ML[runrange];
	 vectUnc = &uncertaintiesRel172HCP_AFII_e24vhi_medium1_ML[runrange];
       }
     }
     else if (set==38) {//e24vhi_medium1 MC trigger efficiency w.r.t ML offline
       if (rel==9) {
	 vectEff = &MCefficienciesRel172ICHEP_AFII_e24vhi_medium1_ML[runrange];
	 vectUnc = 0; // no error
       } else {
	 vectEff = &MCefficienciesRel172HCP_AFII_e24vhi_medium1_ML[runrange];
	 vectUnc = 0; // no error
       }
     }
     else if (set==39) {//e12Tvh_loose1 trigger SF MC11C w.r.t Loose++ offline
       vectEff = &efficienciesRel172ICHEP_AFII_e12Tvh_loose1_LoosePP[runrange];
       vectUnc = &uncertaintiesRel172ICHEP_AFII_e12Tvh_loose1_LoosePP[runrange];
     }
     else if (set==40) {//e12Tvh_loose1 MC trigger efficiency w.r.t Loose++ offline
       vectEff = &MCefficienciesRel172ICHEP_AFII_e12Tvh_loose1_LoosePP[runrange];
       vectUnc = 0; // no error
     }
     else if (set==41) {//e12Tvh_loose1 trigger SF w.r.t Medium++ offline
       vectEff = &efficienciesRel172ICHEP_AFII_e12Tvh_loose1_MediumPP[runrange];
       vectUnc = &uncertaintiesRel172ICHEP_AFII_e12Tvh_loose1_MediumPP[runrange];
     }
     else if (set==42) {//e12Tvh_loose1 MC trigger efficiency w.r.t Medium++ offline
       vectEff = &MCefficienciesRel172ICHEP_AFII_e12Tvh_loose1_MediumPP[runrange];
       vectUnc = 0; // no error
     }
     else if (set==43) {//e12Tvh_loose1 trigger SF w.r.t Tight++ offline
       vectEff = &efficienciesRel172ICHEP_AFII_e12Tvh_loose1_TightPP[runrange];
       vectUnc = &uncertaintiesRel172ICHEP_AFII_e12Tvh_loose1_TightPP[runrange];
     }
     else if (set==44) {//e12Tvh_loose1 MC trigger efficiency w.r.t Tight++ offline
       vectEff = &MCefficienciesRel172ICHEP_AFII_e12Tvh_loose1_TightPP[runrange];
       vectUnc = 0; // no error
     }
     else if (set==45) {//e12Tvh_loose1 trigger SF w.r.t ML offline
       vectEff = &efficienciesRel172ICHEP_AFII_e12Tvh_loose1_ML[runrange];
       vectUnc = &uncertaintiesRel172ICHEP_AFII_e12Tvh_loose1_ML[runrange];
     }
     else if (set==46) {//e12Tvh_loose1 MC trigger efficiency w.r.t ML offline
       vectEff = &MCefficienciesRel172ICHEP_AFII_e12Tvh_loose1_ML[runrange];
       vectUnc = 0; // no error
     }
   } else if (rel==8 || rel==10) { //release 17.2 for 2012 data and G4 FullSim MC12a, "ICHEP/HCP 2012 recommendations"
     if ((rel==8 && set >= 31 && set <= 46)
	 || (rel==10 && set >= 39 && set <= 46))
       runrange = getRunRange(runnumber, runranges_ICHEP2012);
     else if (rel==10 && set >= 31 && set <= 38)
       runrange = getRunRange(runnumber, runranges_HCP2012);

     vectEtaBinning = &m_FineEtabins;
     if (set <= 3 || (set >= 8 && set <= 29) || set > 46) { 
       std::cout << "egammaSFclass: ERROR : unsupported set " << set << " for rel=8/10 (ICHEP/HCP 2012), read documentation (and report a bug in case)" << std::endl;
       return std::make_pair(-1.,-1.);
     }
     else if (set==4) {//Reco + track quality requirements
       // this has implicit ET dependence, so don't confuse the user
       etcorrection = false;
       vectEff = &efficienciesRel172ICHEPRecoTrkQual;
       vectUnc = &uncertaintiesRel172ICHEPRecoTrkQual;
       if (ET<15000.) {
	 float eff=1.,unc=0.05;
	 if (fabs(eta)<1.37) {
	   eff=1.;unc=0.02;
	 }
	 return std::make_pair(eff,unc);
       }
     }
     else if (set==5) {//Loose++
       if (ET>=15000.) {
	 vectEff = &efficienciesRel172ICHEPLoosePP1550;
	 vectUnc = &uncertaintiesRel172ICHEPLoosePP1550;
       } else {
	 vectEff = &efficienciesRel172ICHEPLoosePP415;
	 vectUnc = &uncertaintiesRel172ICHEPLoosePP415;
       }
     }
     else if (set==6) {//Medium++
       if (ET>=15000.) {
	 vectEff = &efficienciesRel172ICHEPMediumPP1550;
	 vectUnc = &uncertaintiesRel172ICHEPMediumPP1550;
       } else {
	 vectEff = &efficienciesRel172ICHEPMediumPP415;
	 vectUnc = &uncertaintiesRel172ICHEPMediumPP415;
       }
     }
     else if (set==7) {//Tight++
       if (ET>=15000.) {
	 vectEff = &efficienciesRel172ICHEPTightPP1550;
	 vectUnc = &uncertaintiesRel172ICHEPTightPP1550;
       } else {
	 vectEff = &efficienciesRel172ICHEPTightPP415;
	 vectUnc = &uncertaintiesRel172ICHEPTightPP415;
       }
     }
     else if (set==30) {//MultiLepton
       if (ET>=15000.) {
	 vectEff = &efficienciesRel172ICHEPML1550;
	 vectUnc = &uncertaintiesRel172ICHEPML1550;
       } else {
	 vectEff = &efficienciesRel172ICHEPML415;
	 vectUnc = &uncertaintiesRel172ICHEPML415;
       }
     }
     else if (set==31) {//e24vhi_medium1 trigger SF MC11C w.r.t Loose++ offline
       if (rel==8) {
	 vectEff = &efficienciesRel172ICHEP_e24vhi_medium1_LoosePP[runrange];
	 vectUnc = &uncertaintiesRel172ICHEP_e24vhi_medium1_LoosePP[runrange];
       } else {
	 vectEff = &efficienciesRel172HCP_e24vhi_medium1_LoosePP[runrange];
	 vectUnc = &uncertaintiesRel172HCP_e24vhi_medium1_LoosePP[runrange];
       }
     }
     else if (set==32) {//e24vhi_medium1 MC trigger efficiency w.r.t Loose++ offline
       if (rel==8) {
	 vectEff = &MCefficienciesRel172ICHEP_e24vhi_medium1_LoosePP[runrange];
	 vectUnc = 0; // no error
       } else {
	 vectEff = &MCefficienciesRel172HCP_e24vhi_medium1_LoosePP[runrange];
	 vectUnc = 0; // no error
       }
     }
     else if (set==33) {//e24vhi_medium1 trigger SF w.r.t Medium++ offline
       if (rel==8) {
	 vectEff = &efficienciesRel172ICHEP_e24vhi_medium1_MediumPP[runrange];
	 vectUnc = &uncertaintiesRel172ICHEP_e24vhi_medium1_MediumPP[runrange];
       } else {
	 vectEff = &efficienciesRel172HCP_e24vhi_medium1_MediumPP[runrange];
	 vectUnc = &uncertaintiesRel172HCP_e24vhi_medium1_MediumPP[runrange];
       }
     }
     else if (set==34) {//e24vhi_medium1 MC trigger efficiency w.r.t Medium++ offline
       if (rel==8) {
	 vectEff = &MCefficienciesRel172ICHEP_e24vhi_medium1_MediumPP[runrange];
	 vectUnc = 0; // no error
       } else {
	 vectEff = &MCefficienciesRel172HCP_e24vhi_medium1_MediumPP[runrange];
	 vectUnc = 0; // no error
       }
     }
     else if (set==35) {//e24vhi_medium1 trigger SF w.r.t Tight++ offline
       if (rel==8) {
	 vectEff = &efficienciesRel172ICHEP_e24vhi_medium1_TightPP[runrange];
	 vectUnc = &uncertaintiesRel172ICHEP_e24vhi_medium1_TightPP[runrange];
       } else {
	 vectEff = &efficienciesRel172HCP_e24vhi_medium1_TightPP[runrange];
	 vectUnc = &uncertaintiesRel172HCP_e24vhi_medium1_TightPP[runrange];
       }
     }
     else if (set==36) {//e24vhi_medium1 MC trigger efficiency w.r.t Tight++ offline
       if (rel==8) {
	 vectEff = &MCefficienciesRel172ICHEP_e24vhi_medium1_TightPP[runrange];
	 vectUnc = 0; // no error
       } else {
	 vectEff = &MCefficienciesRel172HCP_e24vhi_medium1_TightPP[runrange];
	 vectUnc = 0; // no error
       }
     }
     else if (set==37) {//e24vhi_medium1 trigger SF w.r.t ML offline
       if (rel==8) {
	 vectEff = &efficienciesRel172ICHEP_e24vhi_medium1_ML[runrange];
	 vectUnc = &uncertaintiesRel172ICHEP_e24vhi_medium1_ML[runrange];
       } else {
	 vectEff = &efficienciesRel172HCP_e24vhi_medium1_ML[runrange];
	 vectUnc = &uncertaintiesRel172HCP_e24vhi_medium1_ML[runrange];
       }
     }
     else if (set==38) {//e24vhi_medium1 MC trigger efficiency w.r.t ML offline
       if (rel==8) {
	 vectEff = &MCefficienciesRel172ICHEP_e24vhi_medium1_ML[runrange];
	 vectUnc = 0; // no error
       } else {
	 vectEff = &MCefficienciesRel172HCP_e24vhi_medium1_ML[runrange];
	 vectUnc = 0; // no error
       }
     }
     else if (set==39) {//e12Tvh_loose1 trigger SF MC11C w.r.t Loose++ offline
       vectEff = &efficienciesRel172ICHEP_e12Tvh_loose1_LoosePP[runrange];
       vectUnc = &uncertaintiesRel172ICHEP_e12Tvh_loose1_LoosePP[runrange];
     }
     else if (set==40) {//e12Tvh_loose1 MC trigger efficiency w.r.t Loose++ offline
       vectEff = &MCefficienciesRel172ICHEP_e12Tvh_loose1_LoosePP[runrange];
       vectUnc = 0; // no error
     }
     else if (set==41) {//e12Tvh_loose1 trigger SF w.r.t Medium++ offline
       vectEff = &efficienciesRel172ICHEP_e12Tvh_loose1_MediumPP[runrange];
       vectUnc = &uncertaintiesRel172ICHEP_e12Tvh_loose1_MediumPP[runrange];
     }
     else if (set==42) {//e12Tvh_loose1 MC trigger efficiency w.r.t Medium++ offline
       vectEff = &MCefficienciesRel172ICHEP_e12Tvh_loose1_MediumPP[runrange];
       vectUnc = 0; // no error
     }
     else if (set==43) {//e12Tvh_loose1 trigger SF w.r.t Tight++ offline
       vectEff = &efficienciesRel172ICHEP_e12Tvh_loose1_TightPP[runrange];
       vectUnc = &uncertaintiesRel172ICHEP_e12Tvh_loose1_TightPP[runrange];
     }
     else if (set==44) {//e12Tvh_loose1 MC trigger efficiency w.r.t Tight++ offline
       vectEff = &MCefficienciesRel172ICHEP_e12Tvh_loose1_TightPP[runrange];
       vectUnc = 0; // no error
     }
     else if (set==45) {//e12Tvh_loose1 trigger SF w.r.t ML offline
       vectEff = &efficienciesRel172ICHEP_e12Tvh_loose1_ML[runrange];
       vectUnc = &uncertaintiesRel172ICHEP_e12Tvh_loose1_ML[runrange];
     }
     else if (set==46) {//e12Tvh_loose1 MC trigger efficiency w.r.t ML offline
       vectEff = &MCefficienciesRel172ICHEP_e12Tvh_loose1_ML[runrange];
       vectUnc = 0; // no error
     }
   } else if (rel==7) { //release 17 for 2011 data and AFII MC11a/b/c, "Moriond recommendations"
     // range is ignored here
     vectEtaBinning = &m_11Etabins;
     if (set == 0 || set == 2 || set == 3 || (set > 22 && set<27) || set>29) {
       std::cout << "egammaSFclass: ERROR : unknown correction set" << std::endl;
       return std::make_pair(-1.,-1.);
     }
     else if (set==4) {//Reco + track quality requirements
       // this has implicit ET dependence, so don't confuse the user
       etcorrection = false;
       vectEff = &efficienciesRel17MoriondAFIIRecoTrkQual;
       vectUnc = &uncertaintiesRel17MoriondAFIIRecoTrkQual;
       if (ET<15000.) {
	 float eff=1.,unc=0.05;
	 if (fabs(eta)<1.37) {
	   eff=1.;unc=0.02;
	 }
	 return std::make_pair(eff,unc);
       }
     }
     else if (set==1) {//Medium
       if (ET>=15000.) {
	 vectEff = &efficienciesRel17MoriondAFIIMedium1550;
	 vectUnc = &uncertaintiesRel17MoriondAFIIMedium1550;
       } else {
	 vectEff = &efficienciesRel17MoriondAFIIMedium415;
	 vectUnc = &uncertaintiesRel17MoriondAFIIMedium415;
       }
     }
     else if (set==5) {//Loose++
       if (ET>=15000.) {
	 vectEff = &efficienciesRel17MoriondAFIILoosePP1550;
	 vectUnc = &uncertaintiesRel17MoriondAFIILoosePP1550;
       } else {
	 vectEff = &efficienciesRel17MoriondAFIILoosePP415;
	 vectUnc = &uncertaintiesRel17MoriondAFIILoosePP415;
       }
     }
     else if (set==6) {//Medium++
       if (ET>=15000.) {
	 vectEff = &efficienciesRel17MoriondAFIIMediumPP1550;
	 vectUnc = &uncertaintiesRel17MoriondAFIIMediumPP1550;
       } else {
	 vectEff = &efficienciesRel17MoriondAFIIMediumPP415;
	 vectUnc = &uncertaintiesRel17MoriondAFIIMediumPP415;
       }
     }
     else if (set==7) {//Tight++
       if (ET>=15000.) {
	 vectEff = &efficienciesRel17MoriondAFIITightPP1550;
	 vectUnc = &uncertaintiesRel17MoriondAFIITightPP1550;
       } else {
	 vectEff = &efficienciesRel17MoriondAFIITightPP415;
	 vectUnc = &uncertaintiesRel17MoriondAFIITightPP415;
       }
     }
     else if (set==8) {//e20_medium trigger SF w.r.t Medium++ offline
       vectEtaBinning = &m_FineEtabins;
       vectEff = &efficienciesRel17MoriondAFIIe20_mediumMediumPP;
       vectUnc = &uncertaintiesRel17MoriondAFIIe20_mediumMediumPP;
     }
     else if (set==9) {//e20_medium MC trigger efficiency w.r.t Medium++ offline
       vectEtaBinning = &m_FineEtabins;
       vectEff = &MCefficienciesRel17MoriondAFIIe20_mediumMediumPP;
       vectUnc = 0; // no error
     }
     else if (set==10) {//e20_medium trigger SF w.r.t Tight++ offline
       vectEtaBinning = &m_FineEtabins;
       vectEff = &efficienciesRel17MoriondAFIIe20_mediumTightPP;
       vectUnc = &uncertaintiesRel17MoriondAFIIe20_mediumTightPP;
     }
     else if (set==11) {//e20_medium MC trigger efficiency w.r.t Tight++ offline
       vectEtaBinning = &m_FineEtabins;
       vectEff = &MCefficienciesRel17MoriondAFIIe20_mediumTightPP;
       vectUnc = 0; // no error
     }
     else if (set==12) {//e22_medium trigger SF w.r.t Medium++ offline
       vectEtaBinning = &m_FineEtabins;
       vectEff = &efficienciesRel17MoriondAFIIe22_mediumMediumPP;
       vectUnc = &uncertaintiesRel17MoriondAFIIe22_mediumMediumPP;
     }
     else if (set==13) {//e22_medium MC trigger efficiency w.r.t Medium++ offline
       vectEtaBinning = &m_FineEtabins;
       vectEff = &MCefficienciesRel17MoriondAFIIe22_mediumMediumPP;
       vectUnc = 0; // no error
     }
     else if (set==14) {//e22_medium trigger SF w.r.t Tight++ offline
       vectEtaBinning = &m_FineEtabins;
       vectEff = &efficienciesRel17MoriondAFIIe22_mediumTightPP;
       vectUnc = &uncertaintiesRel17MoriondAFIIe22_mediumTightPP;
     }
     else if (set==15) {//e22_medium MC trigger efficiency w.r.t Tight++ offline
       vectEtaBinning = &m_FineEtabins;
       vectEff = &MCefficienciesRel17MoriondAFIIe22_mediumTightPP;
       vectUnc = 0; // no error
     }
     else if (set==16) {//e22vh_medium1 trigger SF w.r.t Medium++ offline
       vectEtaBinning = &m_FineEtabins;
       vectEff = &efficienciesRel17MoriondAFIIe22vh_medium1MediumPP;
       vectUnc = &uncertaintiesRel17MoriondAFIIe22vh_medium1MediumPP;
     }
     else if (set==17) {//e22vh_medium1 MC trigger efficiency w.r.t Medium++ offline
       vectEtaBinning = &m_FineEtabins;
       vectEff = &MCefficienciesRel17MoriondAFIIe22vh_medium1MediumPP;
       vectUnc = 0; // no error
     }
     else if (set==18) {//e22vh_medium1 trigger SF w.r.t Tight++ offline
       vectEtaBinning = &m_FineEtabins;
       vectEff = &efficienciesRel17MoriondAFIIe22vh_medium1TightPP;
       vectUnc = &uncertaintiesRel17MoriondAFIIe22vh_medium1TightPP;
     }
     else if (set==19) {//e22vh_medium1 MC trigger efficiency w.r.t Tight++ offline
       vectEtaBinning = &m_FineEtabins;
       vectEff = &MCefficienciesRel17MoriondAFIIe22vh_medium1TightPP;
       vectUnc = 0; // no error
     }
     else if (set==20) {//e20_medium MC trigger efficiency w.r.t Loose++ offline
       vectEtaBinning = &m_FineEtabins;
       vectEff = &MCefficienciesRel17MoriondAFIIe20_mediumLoosePP;
       vectUnc = 0; // no error
     }
     else if (set==21) {//e22_medium MC trigger efficiency w.r.t Loose++ offline
       vectEtaBinning = &m_FineEtabins;
       vectEff = &MCefficienciesRel17MoriondAFIIe22_mediumLoosePP;
       vectUnc = 0; // no error
     }
     else if (set==22) {//e22vh_medium1 MC trigger efficiency w.r.t Loose++ offline
       vectEtaBinning = &m_FineEtabins;
       vectEff = &MCefficienciesRel17MoriondAFIIe22vh_medium1LoosePP;
       vectUnc = 0; // no error
     }
     else if (set==27) {//e20_medium trigger SF ATLF w.r.t Loose++ offline
       vectEtaBinning = &m_FineEtabins;
       vectEff = &efficienciesRel17MoriondAFIIe20_mediumLoosePP;
       vectUnc = &uncertaintiesRel17MoriondAFIIe20_mediumLoosePP;
     }
     else if (set==28) {//e22_medium trigger SF ATLF w.r.t Loose++ offline
       vectEtaBinning = &m_FineEtabins;
       vectEff = &efficienciesRel17MoriondAFIIe22_mediumLoosePP;
       vectUnc = &uncertaintiesRel17MoriondAFIIe22_mediumLoosePP;
     }
     else if (set==29) {//e22vh_medium1 trigger SF ATLF w.r.t Loose++ offline
       vectEtaBinning = &m_FineEtabins;
       vectEff = &efficienciesRel17MoriondAFIIe22vh_medium1LoosePP;
       vectUnc = &uncertaintiesRel17MoriondAFIIe22vh_medium1LoosePP;
     }

   }
   else if (rel==6) { //release 17 for 2011 data and G4 FullSim MC11a/b/c, "Moriond recommendations"
     // range is ignored here
     vectEtaBinning = &m_11Etabins;
     if (set == 0 || set == 2 || set == 3 || set > 29) {
       std::cout << "egammaSFclass: ERROR : only Reco+TrackQuality, Medium, Loose++, Medium++, Tight++, FwdLoose, FwdTight and 3 single electron triggers exist" << std::endl;
       return std::make_pair(-1.,-1.);
     }
     else if (set==4) {//Reco + track quality requirements
       // this has implicit ET dependence, so don't confuse the user
       etcorrection = false;
       vectEff = &efficienciesRel17MoriondRecoTrkQual;
       vectUnc = &uncertaintiesRel17MoriondRecoTrkQual;
       if (ET<15000.) {
	 float eff=1.,unc=0.05;
	 if (fabs(eta)<1.37) {
	   eff=1.;unc=0.02;
	 }
	 return std::make_pair(eff,unc);
       }
     }
     else if (set==1) {//Medium
       if (ET>=15000.) {
	 vectEff = &efficienciesRel17MoriondMedium1550;
	 vectUnc = &uncertaintiesRel17MoriondMedium1550;
       } else {
	 vectEff = &efficienciesRel17MoriondMedium415;
	 vectUnc = &uncertaintiesRel17MoriondMedium415;
       }
     }
     else if (set==5) {//Loose++
       if (ET>=15000.) {
	 vectEff = &efficienciesRel17MoriondLoosePP1550;
	 vectUnc = &uncertaintiesRel17MoriondLoosePP1550;
       } else {
	 vectEff = &efficienciesRel17MoriondLoosePP415;
	 vectUnc = &uncertaintiesRel17MoriondLoosePP415;
       }
     }
     else if (set==6) {//Medium++
       if (ET>=15000.) {
	 vectEff = &efficienciesRel17MoriondMediumPP1550;
	 vectUnc = &uncertaintiesRel17MoriondMediumPP1550;
       } else {
	 vectEff = &efficienciesRel17MoriondMediumPP415;
	 vectUnc = &uncertaintiesRel17MoriondMediumPP415;
       }
     }
     else if (set==7) {//Tight++
       if (ET>=15000.) {
	 vectEff = &efficienciesRel17MoriondTightPP1550;
	 vectUnc = &uncertaintiesRel17MoriondTightPP1550;
       } else {
	 vectEff = &efficienciesRel17MoriondTightPP415;
	 vectUnc = &uncertaintiesRel17MoriondTightPP415;
       }
     }
     else if (set==8) {//e20_medium trigger SF w.r.t Medium++ offline
       vectEtaBinning = &m_FineEtabins;
       vectEff = &efficienciesRel17Morionde20_mediumMediumPP;
       vectUnc = &uncertaintiesRel17Morionde20_mediumMediumPP;
     }
     else if (set==9) {//e20_medium MC trigger efficiency w.r.t Medium++ offline
       vectEtaBinning = &m_FineEtabins;
       vectEff = &MCefficienciesRel17Morionde20_mediumMediumPP;
       vectUnc = 0; // no error
     }
     else if (set==10) {//e20_medium trigger SF w.r.t Tight++ offline
       vectEtaBinning = &m_FineEtabins;
       vectEff = &efficienciesRel17Morionde20_mediumTightPP;
       vectUnc = &uncertaintiesRel17Morionde20_mediumTightPP;
     }
     else if (set==11) {//e20_medium MC trigger efficiency w.r.t Tight++ offline
       vectEtaBinning = &m_FineEtabins;
       vectEff = &MCefficienciesRel17Morionde20_mediumTightPP;
       vectUnc = 0; // no error
     }
     else if (set==12) {//e22_medium trigger SF w.r.t Medium++ offline
       vectEtaBinning = &m_FineEtabins;
       vectEff = &efficienciesRel17Morionde22_mediumMediumPP;
       vectUnc = &uncertaintiesRel17Morionde22_mediumMediumPP;
     }
     else if (set==13) {//e22_medium MC trigger efficiency w.r.t Medium++ offline
       vectEtaBinning = &m_FineEtabins;
       vectEff = &MCefficienciesRel17Morionde22_mediumMediumPP;
       vectUnc = 0; // no error
     }
     else if (set==14) {//e22_medium trigger SF w.r.t Tight++ offline
       vectEtaBinning = &m_FineEtabins;
       vectEff = &efficienciesRel17Morionde22_mediumTightPP;
       vectUnc = &uncertaintiesRel17Morionde22_mediumTightPP;
     }
     else if (set==15) {//e22_medium MC trigger efficiency w.r.t Tight++ offline
       vectEtaBinning = &m_FineEtabins;
       vectEff = &MCefficienciesRel17Morionde22_mediumTightPP;
       vectUnc = 0; // no error
     }
     else if (set==16) {//e22vh_medium1 trigger SF w.r.t Medium++ offline
       vectEtaBinning = &m_FineEtabins;
       vectEff = &efficienciesRel17Morionde22vh_medium1MediumPP;
       vectUnc = &uncertaintiesRel17Morionde22vh_medium1MediumPP;
     }
     else if (set==17) {//e22vh_medium1 MC trigger efficiency w.r.t Medium++ offline
       vectEtaBinning = &m_FineEtabins;
       vectEff = &MCefficienciesRel17Morionde22vh_medium1MediumPP;
       vectUnc = 0; // no error
     }
     else if (set==18) {//e22vh_medium1 trigger SF w.r.t Tight++ offline
       vectEtaBinning = &m_FineEtabins;
       vectEff = &efficienciesRel17Morionde22vh_medium1TightPP;
       vectUnc = &uncertaintiesRel17Morionde22vh_medium1TightPP;
     }
     else if (set==19) {//e22vh_medium1 MC trigger efficiency w.r.t Tight++ offline
       vectEtaBinning = &m_FineEtabins;
       vectEff = &MCefficienciesRel17Morionde22vh_medium1TightPP;
       vectUnc = 0; // no error
     }
     else if (set==20) {//e20_medium MC trigger efficiency w.r.t Loose++ offline
       vectEtaBinning = &m_FineEtabins;
       vectEff = &MCefficienciesRel17Morionde20_mediumLoosePP;
       vectUnc = 0; // no error
     }
     else if (set==21) {//e22_medium MC trigger efficiency w.r.t Loose++ offline
       vectEtaBinning = &m_FineEtabins;
       vectEff = &MCefficienciesRel17Morionde22_mediumLoosePP;
       vectUnc = 0; // no error
     }
     else if (set==22) {//e22vh_medium1 MC trigger efficiency w.r.t Loose++ offline
       vectEtaBinning = &m_FineEtabins;
       vectEff = &MCefficienciesRel17Morionde22vh_medium1LoosePP;
       vectUnc = 0; // no error
     }
     else if (set==23) {//ForwardLoose electrons
       doAbsEta = true;
       vectEtaBinning = &m_FwdEtabins;
       vectEff = &efficienciesRel17MoriondForwardLoose;
       vectUnc = &uncertaintiesRel17MoriondForwardLoose;
     }
     else if (set==24) {//ForwardTight electrons
       doAbsEta = true;
       vectEtaBinning = &m_FwdEtabins;
       vectEff = &efficienciesRel17MoriondForwardTight;
       vectUnc = &uncertaintiesRel17MoriondForwardTight;
     }
     else if (set==25) {//ForwardLoose electrons FrozenShowers
       doAbsEta = true;
       vectEtaBinning = &m_FwdEtabins;
       vectEff = &efficienciesRel17MoriondFrozenShowersForwardLoose;
       vectUnc = &uncertaintiesRel17MoriondForwardLoose;
     }
     else if (set==26) {//ForwardTight electrons FrozenShowers
       doAbsEta = true;
       vectEtaBinning = &m_FwdEtabins;
       vectEff = &efficienciesRel17MoriondFrozenShowersForwardTight;
       vectUnc = &uncertaintiesRel17MoriondForwardTight;
     }
     else if (set==27) {//e20_medium trigger SF MC11C w.r.t Loose++ offline
       vectEtaBinning = &m_FineEtabins;
       vectEff = &efficienciesRel17Morionde20_mediumLoosePP;
       vectUnc = &uncertaintiesRel17Morionde20_mediumLoosePP;
     }
     else if (set==28) {//e22_medium trigger SF MC11C w.r.t Loose++ offline
       vectEtaBinning = &m_FineEtabins;
       vectEff = &efficienciesRel17Morionde22_mediumLoosePP;
       vectUnc = &uncertaintiesRel17Morionde22_mediumLoosePP;
     }
     else if (set==29) {//e22vh_medium trigger SF MC11C w.r.t Loose++ offline
       vectEtaBinning = &m_FineEtabins;
       vectEff = &efficienciesRel17Morionde22vh_medium1LoosePP;
       vectUnc = &uncertaintiesRel17Morionde22vh_medium1LoosePP;
     }

   }
   else if (rel==5) { //release 17 for 2011 data and MC11a, "CERN council recommendations"
     // range is ignored here
     vectEtaBinning = &m_11Etabins;
     if (set < 4 || set > 22) {
       std::cout << "egammaSFclass: ERROR : only Reco+TrackQuality, IsEM++ menu, and 3 single electron triggers exist" << std::endl;
       return std::make_pair(-1.,-1.);
     }
     else if (set==4) {//Reco + track quality requirements
       // this has implicit ET dependence, so don't confuse the user
       etcorrection = false;
       vectEff = &efficienciesRel17CCRecoTrkQual;
       vectUnc = &uncertaintiesRel17CCRecoTrkQual;
       if (ET<15000.) {
	 float eff=1.,unc=0.05;
	 if (fabs(eta)<1.37) {
	   eff=1.;unc=0.02;
	 }
	 return std::make_pair(eff,unc);
       }
     }
     else if (set==5) {//Loose++
       if (ET>=15000.) {
	 vectEff = &efficienciesRel17CCLoosePP1550;
	 vectUnc = &uncertaintiesRel17CCLoosePP1550;
       } else {
	 vectEff = &efficienciesRel17CCLoosePP415;
	 vectUnc = &uncertaintiesRel17CCLoosePP415;
       }
     }
     else if (set==6) {//Medium++
       if (ET>=15000.) {
	 vectEff = &efficienciesRel17CCMediumPP1550;
	 vectUnc = &uncertaintiesRel17CCMediumPP1550;
       } else {
	 vectEff = &efficienciesRel17CCMediumPP415;
	 vectUnc = &uncertaintiesRel17CCMediumPP415;
       }
     }
     else if (set==7) {//Tight++
       if (ET>=15000.) {
	 vectEff = &efficienciesRel17CCTightPP1550;
	 vectUnc = &uncertaintiesRel17CCTightPP1550;
       } else {
	 vectEff = &efficienciesRel17CCTightPP415;
	 vectUnc = &uncertaintiesRel17CCTightPP415;
       }
     }
     else if (set==8) {//e20_medium trigger SF w.r.t Medium++ offline
       vectEtaBinning = &m_FineEtabins;
       vectEff = &efficienciesRel17CCe20_mediumMediumPP;
       vectUnc = &uncertaintiesRel17CCe20_mediumMediumPP;
     }
     else if (set==9) {//e20_medium MC trigger efficiency w.r.t Medium++ offline
       vectEtaBinning = &m_FineEtabins;
       vectEff = &MCefficienciesRel17CCe20_mediumMediumPP;
       vectUnc = 0; // no error
     }
     else if (set==10) {//e20_medium trigger SF w.r.t Tight++ offline
       vectEtaBinning = &m_FineEtabins;
       vectEff = &efficienciesRel17CCe20_mediumTightPP;
       vectUnc = &uncertaintiesRel17CCe20_mediumTightPP;
     }
     else if (set==11) {//e20_medium MC trigger efficiency w.r.t Tight++ offline
       vectEtaBinning = &m_FineEtabins;
       vectEff = &MCefficienciesRel17CCe20_mediumTightPP;
       vectUnc = 0; // no error
     }
     else if (set==12) {//e22_medium trigger SF w.r.t Medium++ offline
       vectEtaBinning = &m_FineEtabins;
       vectEff = &efficienciesRel17CCe22_mediumMediumPP;
       vectUnc = &uncertaintiesRel17CCe22_mediumMediumPP;
     }
     else if (set==13) {//e22_medium MC trigger efficiency w.r.t Medium++ offline
       vectEtaBinning = &m_FineEtabins;
       vectEff = &MCefficienciesRel17CCe22_mediumMediumPP;
       vectUnc = 0; // no error
     }
     else if (set==14) {//e22_medium trigger SF w.r.t Tight++ offline
       vectEtaBinning = &m_FineEtabins;
       vectEff = &efficienciesRel17CCe22_mediumTightPP;
       vectUnc = &uncertaintiesRel17CCe22_mediumTightPP;
     }
     else if (set==15) {//e22_medium MC trigger efficiency w.r.t Tight++ offline
       vectEtaBinning = &m_FineEtabins;
       vectEff = &MCefficienciesRel17CCe22_mediumTightPP;
       vectUnc = 0; // no error
     }
     else if (set==16) {//e22vh_medium1 trigger SF w.r.t Medium++ offline
       vectEtaBinning = &m_FineEtabins;
       vectEff = &efficienciesRel17CCe22vh_medium1MediumPP;
       vectUnc = &uncertaintiesRel17CCe22vh_medium1MediumPP;
     }
     else if (set==17) {//e22vh_medium1 MC trigger efficiency w.r.t Medium++ offline
       vectEtaBinning = &m_FineEtabins;
       vectEff = &MCefficienciesRel17CCe22vh_medium1MediumPP;
       vectUnc = 0; // no error
     }
     else if (set==18) {//e22vh_medium1 trigger SF w.r.t Tight++ offline
       vectEtaBinning = &m_FineEtabins;
       vectEff = &efficienciesRel17CCe22vh_medium1TightPP;
       vectUnc = &uncertaintiesRel17CCe22vh_medium1TightPP;
     }
     else if (set==19) {//e22vh_medium1 MC trigger efficiency w.r.t Tight++ offline
       vectEtaBinning = &m_FineEtabins;
       vectEff = &MCefficienciesRel17CCe22vh_medium1TightPP;
       vectUnc = 0; // no error
     }
     else if (set==20) {//e20_medium MC trigger efficiency w.r.t Loose++ offline
       vectEtaBinning = &m_FineEtabins;
       vectEff = &MCefficienciesRel17CCe20_mediumLoosePP;
       vectUnc = 0; // no error
     }
     else if (set==21) {//e22_medium MC trigger efficiency w.r.t Loose++ offline
       vectEtaBinning = &m_FineEtabins;
       vectEff = &MCefficienciesRel17CCe22_mediumLoosePP;
       vectUnc = 0; // no error
     }
     else if (set==22) {//e22vh_medium1 MC trigger efficiency w.r.t Loose++ offline
       vectEtaBinning = &m_FineEtabins;
       vectEff = &MCefficienciesRel17CCe22vh_medium1LoosePP;
       vectUnc = 0; // no error
     }
   }
   else if (rel==4) { //release 16.6 numbers estimated from 2011 data, "EPS recommendations" including the low ET region
     vectEtaBinning = &m_FineEtabins;
     if (range==0) { //20-50 GeV region
       if (set==0 || set>4) {
	 std::cout << "egammaSFclass: ERROR : only Medium, Tight and trigger scale factors exist" << std::endl;
	 return std::make_pair(-1.,-1.);
       }
       else if (set==1) {//Medium
	 if (ET>=15000.) {
	   vectEff = &efficienciesRel166EPSMedium2050;
	   vectUnc = &uncertaintiesRel166EPSMedium2050;
	 }
	 else {
	   vectEtaBinning = &m_Etabins;
	   vectEff = &efficienciesRel166EPSMediumLowET;
	   vectUnc = &uncertaintiesRel166EPSMediumLowET;
	 }
       }
       else if (set==2) {//Tight
	 if (ET>=15000.) {
	   vectEff = &efficienciesRel166EPSTight2050;
	   vectUnc = &uncertaintiesRel166EPSTight2050;
	 }
	 else {
	   vectEtaBinning = &m_Etabins;
	   vectEff = &efficienciesRel166EPSTightLowET;
	   vectUnc = &uncertaintiesRel166EPSTightLowET;
	 }
       }
       else if (set==3) {//Trigger
	 vectEff = &efficienciesRel166EPSTrigger;
	 vectUnc = &uncertaintiesRel166EPSTrigger;
       }
       else if (set==4) {//Reco + track quality requirements
	 vectEff = &efficienciesRel166EPSRecoTrkQual;
	 vectUnc = &uncertaintiesRel166EPSRecoTrkQual;
	 if (ET<15000.) {
	   float eff=1.,unc=0.05;
	   if (fabs(eta)<1.37) {
	     eff=1.;unc=0.02;
	   }
	   return std::make_pair(eff,unc);
	 }
       }
     }//endif 20-50 GeV
     else {
	 std::cout << "egammaSFclass: ERROR : invalid range" << std::endl;
	 return std::make_pair(-1.,-1.);
     }
   } 
   else if (rel==3) { //release 16.6 numbers estimated from 2011 data, "EPS recommendations"
     vectEtaBinning = &m_FineEtabins;
     if (range==0) { //20-50 GeV region
       if (set==0 || set>4) {
	 std::cout << "egammaSFclass: ERROR : only Medium, Tight and trigger scale factors exist" << std::endl;
	 return std::make_pair(-1.,-1.);
       }
       else if (set==1) {//Medium
	 vectEff = &efficienciesRel166EPSMedium2050;
	 vectUnc = &uncertaintiesRel166EPSMedium2050;
       }
       else if (set==2) {//Tight
	 vectEff = &efficienciesRel166EPSTight2050;
	 vectUnc = &uncertaintiesRel166EPSTight2050;
       }
       else if (set==3) {//Trigger
	 vectEff = &efficienciesRel166EPSTrigger;
	 vectUnc = &uncertaintiesRel166EPSTrigger;
       }
       else if (set==4) {//Reco + track quality requirements
	 vectEff = &efficienciesRel166EPSRecoTrkQual;
	 vectUnc = &uncertaintiesRel166EPSRecoTrkQual;
       }
     }//endif 20-50 GeV
     else {
	 std::cout << "egammaSFclass: ERROR : invalid range" << std::endl;
	 return std::make_pair(-1.,-1.);
     }
   } 
   else if (rel==2) { //release 16.6 numbers estimated from 2010 data
     vectEtaBinning = &m_Etabins;
     if (range==0) { //20-50 GeV region
       if (set==0 || set>2) {//Loose
	 std::cout << "egammaSFclass: ERROR : only Medium and Tight scale factors exist" << std::endl;
	 return std::make_pair(-1.,-1.);
       }
       else if (set==1) {//Medium
	 vectEff = &efficienciesRel166Data2010Medium2050;
	 vectUnc = &uncertaintiesRel166Data2010Medium2050;
       }
       else if (set==2) {//Tight
	 vectEff = &efficienciesRel166Data2010Tight2050;
	 vectUnc = &uncertaintiesRel166Data2010Tight2050;
       }
     }//endif 20-50 GeV
     else if (range==1) { //30-50 GeV region
       if (set==0 || set>2) {//Loose
	 std::cout << "egammaSFclass: ERROR : only Medium and Tight scale factors exist" << std::endl;
	 return std::make_pair(-1.,-1.);
       }
       else if (set==1) {//Medium
	 vectEff = &efficienciesRel166Data2010Medium3050;
	 vectUnc = &uncertaintiesRel166Data2010Medium3050;
       }
       else if (set==2) {//Tight
	 vectEff = &efficienciesRel166Data2010Tight3050;
	 vectUnc = &uncertaintiesRel166Data2010Tight3050;
       }
     }//endif 30-50 GeV
     else {
	 std::cout << "egammaSFclass: ERROR : invalid range" << std::endl;
	 return std::make_pair(-1.,-1.);
     }
   } 
   else if (rel==1) { //release 16 numbers
     vectEtaBinning = &m_Etabins;
     if (range==0) { //20-50 GeV region
       if (set==0 || set>2) {//Loose
	 std::cout << "egammaSFclass: ERROR : only Medium and Tight scale factors exist" << std::endl;
	 return std::make_pair(-1.,-1.);
       }
       else if (set==1) {//Medium
	 vectEff = &efficienciesRel16Medium2050;
	 vectUnc = &uncertaintiesRel16Medium2050;
       }
       else if (set==2) {//Tight
	 vectEff = &efficienciesRel16Tight2050;
	 vectUnc = &uncertaintiesRel16Tight2050;
       }
     }//endif 20-50 GeV
     else if (range==1) { //30-50 GeV region
       if (set==0 || set>2) {//Loose
	 std::cout << "egammaSFclass: ERROR : only Medium and Tight scale factors exist" << std::endl;
	 return std::make_pair(-1.,-1.);
       }
       else if (set==1) {//Medium
	 vectEff = &efficienciesRel16Medium3050;
	 vectUnc = &uncertaintiesRel16Medium3050;
       }
       else if (set==2) {//Tight
	 vectEff = &efficienciesRel16Tight3050;
	 vectUnc = &uncertaintiesRel16Tight3050;
       }
     }//endif 30-50 GeV
     else {
	 std::cout << "egammaSFclass: ERROR : invalid range" << std::endl;
	 return std::make_pair(-1.,-1.);
     }
   }
   else { //release 15 numbers
     vectEtaBinning = &m_Etabins;
     if (range==0) { //20-50 GeV region
       if (set==0) {//Loose
	 vectEff = &efficienciesRel15Loose2050;
	 vectUnc = &uncertaintiesRel15Loose2050;
       }
       else if (set==1) {//Medium
	 vectEff = &efficienciesRel15Medium2050;
	 vectUnc = &uncertaintiesRel15Medium2050;
       }
       else if (set==2) {//Tight
	 vectEff = &efficienciesRel15Tight2050;
	 vectUnc = &uncertaintiesRel15Tight2050;
       }
       else {
	 std::cout << "egammaSFclass: ERROR : invalid set of cuts" << std::endl;
	 return std::make_pair(-1.,-1.);
       }
     }//endif 20-50 GeV
     else if (range==1) { //30-50 GeV region
       if (set==0) {//Loose
	 vectEff = &efficienciesRel15Loose3050;
	 vectUnc = &uncertaintiesRel15Loose3050;
       }
       else if (set==1) {//Medium
	 vectEff = &efficienciesRel15Medium3050;
	 vectUnc = &uncertaintiesRel15Medium3050;
       }
       else if (set==2) {//Tight
	 vectEff = &efficienciesRel15Tight3050;
	 vectUnc = &uncertaintiesRel15Tight3050;
       }
       else {
	 std::cout << "egammaSFclass: ERROR : invalid set of cuts" << std::endl;
	 return std::make_pair(-1.,-1.);
       }
     }//endif 30-50 GeV
     else {
	 std::cout << "egammaSFclass: ERROR : invalid range" << std::endl;
	 return std::make_pair(-1.,-1.);
     }
   }//endif rel15

   //Choice of the eta bin
   int ietabin=-1;
   if (doAbsEta)
     eta = fabs(eta);

   while (ietabin<((int)vectEtaBinning->size()-1) && eta>=vectEtaBinning->at(ietabin+1)) ietabin++;
   if (ietabin<0 || ietabin>=((int)vectEtaBinning->size()-1)) {
     std::cout << "egammaSFclass: ERROR : given eta value outside range of existing scale factors" << std::endl;
     return std::make_pair(-1.,-1.);
   }


   float effvseta = vectEff->at(ietabin)/100.;
   float uncvseta = 0.;
   if (vectUnc)
     uncvseta = vectUnc->at(ietabin)/100.;

   float eff = effvseta;
   float unc = uncvseta;

   if (etcorrection) {
     std::pair<float,float> corr = etCorrection(ET, set, rel, runrange);
     if (corr.first <= 0 || eff <= 0)
       unc = 1.;
     else
       unc = eff*corr.first * sqrt( unc*unc/(eff*eff) + corr.second*corr.second/(corr.first*corr.first) );
     eff *= corr.first;
   }

   return std::make_pair(eff,unc);
}


//Returns the ET-correction factor (and uncertainty) to the scale factor for the correspond ET bin 
std::pair<float,float> egammaSFclass::etCorrection(float ET, int set, int rel, int runrange) {
  //for backport of rel16 SF-ET-dependence to rel15
  if (rel==0) rel=1;  
  
  std::vector<float> * vectCorr=0;
  std::vector<float> * vectUncCorr=0;
  std::vector<float> * vectETBinning=0;
  vectETBinning = &m_ETbinsFullRange;
  
  if (rel==1) {
    vectETBinning = &m_ETbins;
    if (set==1) {
      vectCorr = &ETCorrectionsMediumRel16;
      vectUncCorr = &uncertaintiesETCorrectionsMediumRel16;
    }
    else if (set==2) { // tight
      vectCorr = &ETCorrectionsTightRel16;
      vectUncCorr = &uncertaintiesETCorrectionsTightRel16;
    }
  }
  else if (rel==2) {
    vectETBinning = &m_ETbins;
    if (set==1) { //Medium
      vectCorr = &ETCorrectionsMediumRel166Data2010;
      vectUncCorr = &uncertaintiesETCorrectionsMediumRel166Data2010;
    }
    else if (set==2) {
      vectCorr = &ETCorrectionsTightRel166Data2010;
      vectUncCorr = &uncertaintiesETCorrectionsTightRel166Data2010;
    }
  } 
  else if (rel==3) {
    vectETBinning = &m_ETbins;
    if (set==1) { //Medium
      vectCorr = &ETCorrectionsMediumRel166EPS;
      vectUncCorr = &uncertaintiesETCorrectionsMediumRel166EPS;
    }
    else if (set==2) {
      vectCorr = &ETCorrectionsTightRel166EPS;
      vectUncCorr = &uncertaintiesETCorrectionsTightRel166EPS;
    }
  }
  else if (rel==4) {
    if (set==1) { //Medium
      vectCorr = &ETCorrectionsMediumRel166EPSFullRange;
      vectUncCorr = &uncertaintiesETCorrectionsMediumRel166EPSFullRange;
    }
    else if (set==2) {
      vectCorr = &ETCorrectionsTightRel166EPSFullRange;
      vectUncCorr = &uncertaintiesETCorrectionsTightRel166EPSFullRange;
    }
  }
  else if (rel==5) {// Rel17CC
    if (set==5) { // Loose++
      vectETBinning = &m_ETbinsFullRange;
      vectCorr = &ETCorrectionsRel17CCLoosePP;
      vectUncCorr = &uncertaintiesETCorrectionsRel17CCLoosePP;
    }
    else if (set==6) { // Medium++
      vectETBinning = &m_ETbinsFullRange;
      vectCorr = &ETCorrectionsRel17CCMediumPP;
      vectUncCorr = &uncertaintiesETCorrectionsRel17CCMediumPP;
    }
    else if (set==7) { // Tight++
      vectETBinning = &m_ETbinsFullRange;
      vectCorr = &ETCorrectionsRel17CCTightPP;
      vectUncCorr = &uncertaintiesETCorrectionsRel17CCTightPP;
    }
    else if (set==8) { // e20_medium trigger SF w.r.t Medium++ offline
      vectETBinning = &m_ETbinsTrigger;
      vectCorr = &efficienciesRel17CCe20_mediumMediumPPET;
      vectUncCorr = &uncertaintiesRel17CCe20_mediumMediumPPET;
    }
    else if (set==9) { // e20_medium trigger MC eff w.r.t Medium++ offline
      vectETBinning = &m_ETbinsTrigger;
      vectCorr = &MCefficienciesRel17CCe20_mediumMediumPPET;
      vectUncCorr = 0;
    }
    else if (set==10) { // e20_medium trigger SF w.r.t Tight++ offline
      vectETBinning = &m_ETbinsTrigger;
      vectCorr = &efficienciesRel17CCe20_mediumTightPPET;
      vectUncCorr = &uncertaintiesRel17CCe20_mediumTightPPET;
    }
    else if (set==11) { // e20_medium trigger MC eff w.r.t Tight++ offline
      vectETBinning = &m_ETbinsTrigger;
      vectCorr = &MCefficienciesRel17CCe20_mediumTightPPET;
      vectUncCorr = 0;
    }
    else if (set==12) { // e22_medium trigger SF w.r.t Medium++ offline
      vectETBinning = &m_ETbinsTrigger;
      vectCorr = &efficienciesRel17CCe22_mediumMediumPPET;
      vectUncCorr = &uncertaintiesRel17CCe22_mediumMediumPPET;
    }
    else if (set==13) { // e22_medium trigger MC eff w.r.t Medium++ offline
      vectETBinning = &m_ETbinsTrigger;
      vectCorr = &MCefficienciesRel17CCe22_mediumMediumPPET;
      vectUncCorr = 0;
    }
    else if (set==14) { // e22_medium trigger SF w.r.t Tight++ offline
      vectETBinning = &m_ETbinsTrigger;
      vectCorr = &efficienciesRel17CCe22_mediumTightPPET;
      vectUncCorr = &uncertaintiesRel17CCe22_mediumTightPPET;
    }
    else if (set==15) { // e22_medium trigger MC eff w.r.t Tight++ offline
      vectETBinning = &m_ETbinsTrigger;
      vectCorr = &MCefficienciesRel17CCe22_mediumTightPPET;
      vectUncCorr = 0;
    }
    else if (set==16) { // e22vh_medium1 trigger SF w.r.t Medium++ offline
      vectETBinning = &m_ETbinsTrigger;
      vectCorr = &efficienciesRel17CCe22vh_medium1MediumPPET;
      vectUncCorr = &uncertaintiesRel17CCe22vh_medium1MediumPPET;
    }
    else if (set==17) { // e22vh_medium1 trigger MC eff w.r.t Medium++ offline
      vectETBinning = &m_ETbinsTrigger;
      vectCorr = &MCefficienciesRel17CCe22vh_medium1MediumPPET;
      vectUncCorr = 0;
    }
    else if (set==18) { // e22vh_medium1 trigger SF w.r.t Tight++ offline
      vectETBinning = &m_ETbinsTrigger;
      vectCorr = &efficienciesRel17CCe22vh_medium1TightPPET;
      vectUncCorr = &uncertaintiesRel17CCe22vh_medium1TightPPET;
    }
    else if (set==19) { // e22vh_medium1 trigger MC eff w.r.t Tight++ offline
      vectETBinning = &m_ETbinsTrigger;
      vectCorr = &MCefficienciesRel17CCe22vh_medium1TightPPET;
      vectUncCorr = 0;
    }
    else if (set==20) { // e20_medium trigger MC eff w.r.t Loose++ offline
      vectETBinning = &m_ETbinsTrigger;
      vectCorr = &MCefficienciesRel17CCe20_mediumLoosePPET;
      vectUncCorr = 0;
    }
    else if (set==21) { // e22_medium trigger MC eff w.r.t Loose++ offline
      vectETBinning = &m_ETbinsTrigger;
      vectCorr = &MCefficienciesRel17CCe22_mediumLoosePPET;
      vectUncCorr = 0;
    }
    else if (set==22) { // e22vh_medium1 trigger MC eff w.r.t Loose++ offline
      vectETBinning = &m_ETbinsTrigger;
      vectCorr = &MCefficienciesRel17CCe22vh_medium1LoosePPET;
      vectUncCorr = 0;
    }
  }
  else if (rel==6) {// Rel17 Moriond G4FullSim
    if (set==1) { // Medium
      vectETBinning = &m_ETbinsFullRange;
      vectCorr = &ETCorrectionsRel17MoriondMedium;
      vectUncCorr = &uncertaintiesETCorrectionsRel17MoriondMedium;
    }
    else if (set==5) { // Loose++
      vectETBinning = &m_ETbinsFullRange;
      vectCorr = &ETCorrectionsRel17MoriondLoosePP;
      vectUncCorr = &uncertaintiesETCorrectionsRel17MoriondLoosePP;
    }
    else if (set==6) { // Medium++
      vectETBinning = &m_ETbinsFullRange;
      vectCorr = &ETCorrectionsRel17MoriondMediumPP;
      vectUncCorr = &uncertaintiesETCorrectionsRel17MoriondMediumPP;
    }
    else if (set==7) { // Tight++
      vectETBinning = &m_ETbinsFullRange;
      vectCorr = &ETCorrectionsRel17MoriondTightPP;
      vectUncCorr = &uncertaintiesETCorrectionsRel17MoriondTightPP;
    }
    else if (set==8) { // e20_medium trigger SF w.r.t Medium++ offline
      vectETBinning = &m_ETbinsTrigger;
      vectCorr = &efficienciesRel17Morionde20_mediumMediumPPET;
      vectUncCorr = &uncertaintiesRel17Morionde20_mediumMediumPPET;
    }
    else if (set==9) { // e20_medium trigger MC eff w.r.t Medium++ offline
      vectETBinning = &m_ETbinsTrigger;
      vectCorr = &MCefficienciesRel17Morionde20_mediumMediumPPET;
      vectUncCorr = 0;
    }
    else if (set==10) { // e20_medium trigger SF w.r.t Tight++ offline
      vectETBinning = &m_ETbinsTrigger;
      vectCorr = &efficienciesRel17Morionde20_mediumTightPPET;
      vectUncCorr = &uncertaintiesRel17Morionde20_mediumTightPPET;
    }
    else if (set==11) { // e20_medium trigger MC eff w.r.t Tight++ offline
      vectETBinning = &m_ETbinsTrigger;
      vectCorr = &MCefficienciesRel17Morionde20_mediumTightPPET;
      vectUncCorr = 0;
    }
    else if (set==12) { // e22_medium trigger SF w.r.t Medium++ offline
      vectETBinning = &m_ETbinsTrigger;
      vectCorr = &efficienciesRel17Morionde22_mediumMediumPPET;
      vectUncCorr = &uncertaintiesRel17Morionde22_mediumMediumPPET;
    }
    else if (set==13) { // e22_medium trigger MC eff w.r.t Medium++ offline
      vectETBinning = &m_ETbinsTrigger;
      vectCorr = &MCefficienciesRel17Morionde22_mediumMediumPPET;
      vectUncCorr = 0;
    }
    else if (set==14) { // e22_medium trigger SF w.r.t Tight++ offline
      vectETBinning = &m_ETbinsTrigger;
      vectCorr = &efficienciesRel17Morionde22_mediumTightPPET;
      vectUncCorr = &uncertaintiesRel17Morionde22_mediumTightPPET;
    }
    else if (set==15) { // e22_medium trigger MC eff w.r.t Tight++ offline
      vectETBinning = &m_ETbinsTrigger;
      vectCorr = &MCefficienciesRel17Morionde22_mediumTightPPET;
      vectUncCorr = 0;
    }
    else if (set==16) { // e22vh_medium1 trigger SF w.r.t Medium++ offline
      vectETBinning = &m_ETbinsTrigger;
      vectCorr = &efficienciesRel17Morionde22vh_medium1MediumPPET;
      vectUncCorr = &uncertaintiesRel17Morionde22vh_medium1MediumPPET;
    }
    else if (set==17) { // e22vh_medium1 trigger MC eff w.r.t Medium++ offline
      vectETBinning = &m_ETbinsTrigger;
      vectCorr = &MCefficienciesRel17Morionde22vh_medium1MediumPPET;
      vectUncCorr = 0;
    }
    else if (set==18) { // e22vh_medium1 trigger SF w.r.t Tight++ offline
      vectETBinning = &m_ETbinsTrigger;
      vectCorr = &efficienciesRel17Morionde22vh_medium1TightPPET;
      vectUncCorr = &uncertaintiesRel17Morionde22vh_medium1TightPPET;
    }
    else if (set==19) { // e22vh_medium1 trigger MC eff w.r.t Tight++ offline
      vectETBinning = &m_ETbinsTrigger;
      vectCorr = &MCefficienciesRel17Morionde22vh_medium1TightPPET;
      vectUncCorr = 0;
    }
    else if (set==20) { // e20_medium trigger MC eff w.r.t Loose++ offline
      vectETBinning = &m_ETbinsTrigger;
      vectCorr = &MCefficienciesRel17Morionde20_mediumLoosePPET;
      vectUncCorr = 0;
    }
    else if (set==21) { // e22_medium trigger MC eff w.r.t Loose++ offline
      vectETBinning = &m_ETbinsTrigger;
      vectCorr = &MCefficienciesRel17Morionde22_mediumLoosePPET;
      vectUncCorr = 0;
    }
    else if (set==22) { // e22vh_medium1 trigger MC eff w.r.t Loose++ offline
      vectETBinning = &m_ETbinsTrigger;
      vectCorr = &MCefficienciesRel17Morionde22vh_medium1LoosePPET;
      vectUncCorr = 0;
    }
    else if (set==27) { // e20_medium trigger SF w.r.t Loose++ offline
      vectETBinning = &m_ETbinsTrigger;
      vectCorr = &efficienciesRel17Morionde20_mediumLoosePPET;
      vectUncCorr = &uncertaintiesRel17Morionde20_mediumLoosePPET;
    }
    else if (set==28) { // e22_medium trigger SF w.r.t Loose++ offline
      vectETBinning = &m_ETbinsTrigger;
      vectCorr = &efficienciesRel17Morionde22_mediumLoosePPET;
      vectUncCorr = &uncertaintiesRel17Morionde22_mediumLoosePPET;
    }
    else if (set==29) { // e22vh_medium1 trigger SF w.r.t Loose++ offline
      vectETBinning = &m_ETbinsTrigger;
      vectCorr = &efficienciesRel17Morionde22vh_medium1LoosePPET;
      vectUncCorr = &uncertaintiesRel17Morionde22vh_medium1LoosePPET;
    }

    else if (set==23 || set == 24 || set == 25 || set == 26) { // Forward Loose+Tight: just make sure, it's not used below 20 GeV
      if (ET < 20000.) {
	std::cout << "egammaSFclass: ERROR : Out of Et range for forward electrons" << std::endl;
	return std::make_pair(-1.,-1.);
      } else {
	return std::make_pair(1.,0.);
      }
    }
  }
  else if (rel==7) {// Rel17 Moriond AFII
    if (set==1) { // Medium
      vectETBinning = &m_ETbinsFullRange;
      vectCorr = &ETCorrectionsRel17MoriondAFIIMedium;
      vectUncCorr = &uncertaintiesETCorrectionsRel17MoriondAFIIMedium;
    }
    else if (set==5) { // Loose++
      vectETBinning = &m_ETbinsFullRange;
      vectCorr = &ETCorrectionsRel17MoriondAFIILoosePP;
      vectUncCorr = &uncertaintiesETCorrectionsRel17MoriondAFIILoosePP;
    }
    else if (set==6) { // Medium++
      vectETBinning = &m_ETbinsFullRange;
      vectCorr = &ETCorrectionsRel17MoriondAFIIMediumPP;
      vectUncCorr = &uncertaintiesETCorrectionsRel17MoriondAFIIMediumPP;
    }
    else if (set==7) { // Tight++
      vectETBinning = &m_ETbinsFullRange;
      vectCorr = &ETCorrectionsRel17MoriondAFIITightPP;
      vectUncCorr = &uncertaintiesETCorrectionsRel17MoriondAFIITightPP;
    }
    else if (set==8) { // e20_medium trigger SF w.r.t Medium++ offline
      vectETBinning = &m_ETbinsTrigger;
      vectCorr = &efficienciesRel17MoriondAFIIe20_mediumMediumPPET;
      vectUncCorr = &uncertaintiesRel17MoriondAFIIe20_mediumMediumPPET;
    }
    else if (set==9) { // e20_medium trigger MC eff w.r.t Medium++ offline
      vectETBinning = &m_ETbinsTrigger;
      vectCorr = &MCefficienciesRel17MoriondAFIIe20_mediumMediumPPET;
      vectUncCorr = 0;
    }
    else if (set==10) { // e20_medium trigger SF w.r.t Tight++ offline
      vectETBinning = &m_ETbinsTrigger;
      vectCorr = &efficienciesRel17MoriondAFIIe20_mediumTightPPET;
      vectUncCorr = &uncertaintiesRel17MoriondAFIIe20_mediumTightPPET;
    }
    else if (set==11) { // e20_medium trigger MC eff w.r.t Tight++ offline
      vectETBinning = &m_ETbinsTrigger;
      vectCorr = &MCefficienciesRel17MoriondAFIIe20_mediumTightPPET;
      vectUncCorr = 0;
    }
    else if (set==12) { // e22_medium trigger SF w.r.t Medium++ offline
      vectETBinning = &m_ETbinsTrigger;
      vectCorr = &efficienciesRel17MoriondAFIIe22_mediumMediumPPET;
      vectUncCorr = &uncertaintiesRel17MoriondAFIIe22_mediumMediumPPET;
    }
    else if (set==13) { // e22_medium trigger MC eff w.r.t Medium++ offline
      vectETBinning = &m_ETbinsTrigger;
      vectCorr = &MCefficienciesRel17MoriondAFIIe22_mediumMediumPPET;
      vectUncCorr = 0;
    }
    else if (set==14) { // e22_medium trigger SF w.r.t Tight++ offline
      vectETBinning = &m_ETbinsTrigger;
      vectCorr = &efficienciesRel17MoriondAFIIe22_mediumTightPPET;
      vectUncCorr = &uncertaintiesRel17MoriondAFIIe22_mediumTightPPET;
    }
    else if (set==15) { // e22_medium trigger MC eff w.r.t Tight++ offline
      vectETBinning = &m_ETbinsTrigger;
      vectCorr = &MCefficienciesRel17MoriondAFIIe22_mediumTightPPET;
      vectUncCorr = 0;
    }
    else if (set==16) { // e22vh_medium1 trigger SF w.r.t Medium++ offline
      vectETBinning = &m_ETbinsTrigger;
      vectCorr = &efficienciesRel17MoriondAFIIe22vh_medium1MediumPPET;
      vectUncCorr = &uncertaintiesRel17MoriondAFIIe22vh_medium1MediumPPET;
    }
    else if (set==17) { // e22vh_medium1 trigger MC eff w.r.t Medium++ offline
      vectETBinning = &m_ETbinsTrigger;
      vectCorr = &MCefficienciesRel17MoriondAFIIe22vh_medium1MediumPPET;
      vectUncCorr = 0;
    }
    else if (set==18) { // e22vh_medium1 trigger SF w.r.t Tight++ offline
      vectETBinning = &m_ETbinsTrigger;
      vectCorr = &efficienciesRel17MoriondAFIIe22vh_medium1TightPPET;
      vectUncCorr = &uncertaintiesRel17MoriondAFIIe22vh_medium1TightPPET;
    }
    else if (set==19) { // e22vh_medium1 trigger MC eff w.r.t Tight++ offline
      vectETBinning = &m_ETbinsTrigger;
      vectCorr = &MCefficienciesRel17MoriondAFIIe22vh_medium1TightPPET;
      vectUncCorr = 0;
    }
    else if (set==20) { // e20_medium trigger MC eff w.r.t Loose++ offline
      vectETBinning = &m_ETbinsTrigger;
      vectCorr = &MCefficienciesRel17MoriondAFIIe20_mediumLoosePPET;
      vectUncCorr = 0;
    }
    else if (set==21) { // e22_medium trigger MC eff w.r.t Loose++ offline
      vectETBinning = &m_ETbinsTrigger;
      vectCorr = &MCefficienciesRel17MoriondAFIIe22_mediumLoosePPET;
      vectUncCorr = 0;
    }
    else if (set==22) { // e22vh_medium1 trigger MC eff w.r.t Loose++ offline
      vectETBinning = &m_ETbinsTrigger;
      vectCorr = &MCefficienciesRel17MoriondAFIIe22vh_medium1LoosePPET;
      vectUncCorr = 0;
    }
    else if (set==27) { // e20_medium trigger SF w.r.t Loose++ offline
      vectETBinning = &m_ETbinsTrigger;
      vectCorr = &efficienciesRel17MoriondAFIIe20_mediumLoosePPET;
      vectUncCorr = &uncertaintiesRel17MoriondAFIIe20_mediumLoosePPET;
    }
    else if (set==28) { // e22_medium trigger SF w.r.t Loose++ offline
      vectETBinning = &m_ETbinsTrigger;
      vectCorr = &efficienciesRel17MoriondAFIIe22_mediumLoosePPET;
      vectUncCorr = &uncertaintiesRel17MoriondAFIIe22_mediumLoosePPET;
    }
    else if (set==29) { // e22vh_medium1 trigger SF w.r.t Loose++ offline
      vectETBinning = &m_ETbinsTrigger;
      vectCorr = &efficienciesRel17MoriondAFIIe22vh_medium1LoosePPET;
      vectUncCorr = &uncertaintiesRel17MoriondAFIIe22vh_medium1LoosePPET;
    }
  }
  else if (rel==8 || rel==10) {// Rel172 ICHEP2012 G4FullSim
    if (set==5) { // Loose++
      vectETBinning = &m_ETbinsFullRange;
      vectCorr = &ETCorrectionsRel172ICHEPLoosePP;
      vectUncCorr = &uncertaintiesETCorrectionsRel172ICHEPLoosePP;
    }
    else if (set==6) { // Medium++
      vectETBinning = &m_ETbinsFullRange;
      vectCorr = &ETCorrectionsRel172ICHEPMediumPP;
      vectUncCorr = &uncertaintiesETCorrectionsRel172ICHEPMediumPP;
    }
    else if (set==7) { // Tight++
      vectETBinning = &m_ETbinsFullRange;
      vectCorr = &ETCorrectionsRel172ICHEPTightPP;
      vectUncCorr = &uncertaintiesETCorrectionsRel172ICHEPTightPP;
    }
    else if (set==30) { // ML
      vectETBinning = &m_ETbinsFullRange;
      vectCorr = &ETCorrectionsRel172ICHEPML;
      vectUncCorr = &uncertaintiesETCorrectionsRel172ICHEPML;
    }
    else if (set==31) { // e24vhi_medium1 trigger SF w.r.t Loose++ offline
      vectETBinning = &m_ETbinsTrigger_e24;
      if (rel==8) {
	vectCorr = &efficienciesRel172ICHEP_e24vhi_medium1_LoosePPET[runrange];
	vectUncCorr = &uncertaintiesRel172ICHEP_e24vhi_medium1_LoosePPET[runrange];
      } else {
	vectCorr = &efficienciesRel172HCP_e24vhi_medium1_LoosePPET[runrange];
	vectUncCorr = &uncertaintiesRel172HCP_e24vhi_medium1_LoosePPET[runrange];
      }
    }
    else if (set==32) { // e24vhi_medium1 trigger MC eff w.r.t Loose++ offline
      vectETBinning = &m_ETbinsTrigger_e24;
      if (rel==8) {
	vectCorr = &MCefficienciesRel172ICHEP_e24vhi_medium1_LoosePPET[runrange];
	vectUncCorr = 0;
      } else {
	vectCorr = &MCefficienciesRel172HCP_e24vhi_medium1_LoosePPET[runrange];
	vectUncCorr = 0;
      }
    }
    else if (set==33) { // e24vhi_medium1 trigger SF w.r.t Medium++ offline
      vectETBinning = &m_ETbinsTrigger_e24;
      if (rel==8) {
	vectCorr = &efficienciesRel172ICHEP_e24vhi_medium1_MediumPPET[runrange];
	vectUncCorr = &uncertaintiesRel172ICHEP_e24vhi_medium1_MediumPPET[runrange];
      } else {
	vectCorr = &efficienciesRel172HCP_e24vhi_medium1_MediumPPET[runrange];
	vectUncCorr = &uncertaintiesRel172HCP_e24vhi_medium1_MediumPPET[runrange];
      }
    }
    else if (set==34) { // e24vhi_medium1 trigger MC eff w.r.t Medium++ offline
      vectETBinning = &m_ETbinsTrigger_e24;
      if (rel==8) {
	vectCorr = &MCefficienciesRel172ICHEP_e24vhi_medium1_MediumPPET[runrange];
	vectUncCorr = 0;
      } else {
	vectCorr = &MCefficienciesRel172HCP_e24vhi_medium1_MediumPPET[runrange];
	vectUncCorr = 0;
      }
    }
    else if (set==35) { // e24vhi_medium1 trigger SF w.r.t Tight++ offline
      vectETBinning = &m_ETbinsTrigger_e24;
      if (rel==8) {
	vectCorr = &efficienciesRel172ICHEP_e24vhi_medium1_TightPPET[runrange];
	vectUncCorr = &uncertaintiesRel172ICHEP_e24vhi_medium1_TightPPET[runrange];
      } else {
	vectCorr = &efficienciesRel172HCP_e24vhi_medium1_TightPPET[runrange];
	vectUncCorr = &uncertaintiesRel172HCP_e24vhi_medium1_TightPPET[runrange];
      }
    }
    else if (set==36) { // e24vhi_medium1 trigger MC eff w.r.t Tight++ offline
      vectETBinning = &m_ETbinsTrigger_e24;
      if (rel==8) {
	vectCorr = &MCefficienciesRel172ICHEP_e24vhi_medium1_TightPPET[runrange];
	vectUncCorr = 0;
      } else {
	vectCorr = &MCefficienciesRel172HCP_e24vhi_medium1_TightPPET[runrange];
	vectUncCorr = 0;
      }
    }
    else if (set==37) { // e24vhi_medium1 trigger SF w.r.t ML offline
      vectETBinning = &m_ETbinsTrigger_e24;
      if (rel==8) {
	vectCorr = &efficienciesRel172ICHEP_e24vhi_medium1_MLET[runrange];
	vectUncCorr = &uncertaintiesRel172ICHEP_e24vhi_medium1_MLET[runrange];
      } else {
	vectCorr = &efficienciesRel172HCP_e24vhi_medium1_MLET[runrange];
	vectUncCorr = &uncertaintiesRel172HCP_e24vhi_medium1_MLET[runrange];
      }
    }
    else if (set==38) { // e24vhi_medium1 trigger MC eff w.r.t ML offline
      vectETBinning = &m_ETbinsTrigger_e24;
      if (rel==8) {
 	vectCorr = &MCefficienciesRel172ICHEP_e24vhi_medium1_MLET[runrange];
	vectUncCorr = 0;
      } else {
 	vectCorr = &MCefficienciesRel172HCP_e24vhi_medium1_MLET[runrange];
	vectUncCorr = 0;
      }
    }
    else if (set==39) { // e12Tvh_loose1 trigger SF w.r.t Loose++ offline
      vectETBinning = &m_ETbinsTrigger_e12;
      vectCorr = &efficienciesRel172ICHEP_e12Tvh_loose1_LoosePPET[runrange];
      vectUncCorr = &uncertaintiesRel172ICHEP_e12Tvh_loose1_LoosePPET[runrange];
    }
    else if (set==40) { // e12Tvh_loose1 trigger MC eff w.r.t Loose++ offline
      vectETBinning = &m_ETbinsTrigger_e12;
      vectCorr = &MCefficienciesRel172ICHEP_e12Tvh_loose1_LoosePPET[runrange];
      vectUncCorr = 0;
    }
    else if (set==41) { // e12Tvh_loose1 trigger SF w.r.t Medium++ offline
      vectETBinning = &m_ETbinsTrigger_e12;
      vectCorr = &efficienciesRel172ICHEP_e12Tvh_loose1_MediumPPET[runrange];
      vectUncCorr = &uncertaintiesRel172ICHEP_e12Tvh_loose1_MediumPPET[runrange];
    }
    else if (set==42) { // e12Tvh_loose1 trigger MC eff w.r.t Medium++ offline
      vectETBinning = &m_ETbinsTrigger_e12;
      vectCorr = &MCefficienciesRel172ICHEP_e12Tvh_loose1_MediumPPET[runrange];
      vectUncCorr = 0;
    }
    else if (set==43) { // e12Tvh_loose1 trigger SF w.r.t Tight++ offline
      vectETBinning = &m_ETbinsTrigger_e12;
      vectCorr = &efficienciesRel172ICHEP_e12Tvh_loose1_TightPPET[runrange];
      vectUncCorr = &uncertaintiesRel172ICHEP_e12Tvh_loose1_TightPPET[runrange];
    }
    else if (set==44) { // e12Tvh_loose1 trigger MC eff w.r.t Tight++ offline
      vectETBinning = &m_ETbinsTrigger_e12;
      vectCorr = &MCefficienciesRel172ICHEP_e12Tvh_loose1_TightPPET[runrange];
      vectUncCorr = 0;
    }
    else if (set==45) { // e12Tvh_loose1 trigger SF w.r.t ML offline
      vectETBinning = &m_ETbinsTrigger_e12;
      vectCorr = &efficienciesRel172ICHEP_e12Tvh_loose1_MLET[runrange];
      vectUncCorr = &uncertaintiesRel172ICHEP_e12Tvh_loose1_MLET[runrange];
    }
    else if (set==46) { // e12Tvh_loose1 trigger MC eff w.r.t ML offline
      vectETBinning = &m_ETbinsTrigger_e12;
      vectCorr = &MCefficienciesRel172ICHEP_e12Tvh_loose1_MLET[runrange];
      vectUncCorr = 0;
    }
  } else if (rel==9 || rel==11) {// Rel172 ICHEP2012 AFII
    if (set==5) { // Loose++
      vectETBinning = &m_ETbinsFullRange;
      vectCorr = &ETCorrectionsRel172ICHEP_AFIILoosePP;
      vectUncCorr = &uncertaintiesETCorrectionsRel172ICHEP_AFIILoosePP;
    }
    else if (set==6) { // Medium++
      vectETBinning = &m_ETbinsFullRange;
      vectCorr = &ETCorrectionsRel172ICHEP_AFIIMediumPP;
      vectUncCorr = &uncertaintiesETCorrectionsRel172ICHEP_AFIIMediumPP;
    }
    else if (set==7) { // Tight++
      vectETBinning = &m_ETbinsFullRange;
      vectCorr = &ETCorrectionsRel172ICHEP_AFIITightPP;
      vectUncCorr = &uncertaintiesETCorrectionsRel172ICHEP_AFIITightPP;
    }
    else if (set==30) { // ML
      vectETBinning = &m_ETbinsFullRange;
      vectCorr = &ETCorrectionsRel172ICHEP_AFIIML;
      vectUncCorr = &uncertaintiesETCorrectionsRel172ICHEP_AFIIML;
    }
    else if (set==31) { // e24vhi_medium1 trigger SF w.r.t Loose++ offline
      vectETBinning = &m_ETbinsTrigger_e24;
      if (rel==9) {
	vectCorr = &efficienciesRel172ICHEP_AFII_e24vhi_medium1_LoosePPET[runrange];
	vectUncCorr = &uncertaintiesRel172ICHEP_AFII_e24vhi_medium1_LoosePPET[runrange];
      } else {
	vectCorr = &efficienciesRel172HCP_AFII_e24vhi_medium1_LoosePPET[runrange];
	vectUncCorr = &uncertaintiesRel172HCP_AFII_e24vhi_medium1_LoosePPET[runrange];
      }
    }
    else if (set==32) { // e24vhi_medium1 trigger MC eff w.r.t Loose++ offline
      vectETBinning = &m_ETbinsTrigger_e24;
      if (rel==9) {
	vectCorr = &MCefficienciesRel172ICHEP_AFII_e24vhi_medium1_LoosePPET[runrange];
	vectUncCorr = 0;
      } else {
	vectCorr = &MCefficienciesRel172HCP_AFII_e24vhi_medium1_LoosePPET[runrange];
	vectUncCorr = 0;
      }
    }
    else if (set==33) { // e24vhi_medium1 trigger SF w.r.t Medium++ offline
      vectETBinning = &m_ETbinsTrigger_e24;
      if (rel==9) {
	vectCorr = &efficienciesRel172ICHEP_AFII_e24vhi_medium1_MediumPPET[runrange];
	vectUncCorr = &uncertaintiesRel172ICHEP_AFII_e24vhi_medium1_MediumPPET[runrange];
      } else {
	vectCorr = &efficienciesRel172HCP_AFII_e24vhi_medium1_MediumPPET[runrange];
	vectUncCorr = &uncertaintiesRel172HCP_AFII_e24vhi_medium1_MediumPPET[runrange];
      }
    }
    else if (set==34) { // e24vhi_medium1 trigger MC eff w.r.t Medium++ offline
      vectETBinning = &m_ETbinsTrigger_e24;
      if (rel==9) {
	vectCorr = &MCefficienciesRel172ICHEP_AFII_e24vhi_medium1_MediumPPET[runrange];
	vectUncCorr = 0;
      } else {
	vectCorr = &MCefficienciesRel172HCP_AFII_e24vhi_medium1_MediumPPET[runrange];
	vectUncCorr = 0;
      }
    }
    else if (set==35) { // e24vhi_medium1 trigger SF w.r.t Tight++ offline
      vectETBinning = &m_ETbinsTrigger_e24;
      if (rel==9) {
	vectCorr = &efficienciesRel172ICHEP_AFII_e24vhi_medium1_TightPPET[runrange];
	vectUncCorr = &uncertaintiesRel172ICHEP_AFII_e24vhi_medium1_TightPPET[runrange];
      } else {
	vectCorr = &efficienciesRel172HCP_AFII_e24vhi_medium1_TightPPET[runrange];
	vectUncCorr = &uncertaintiesRel172HCP_AFII_e24vhi_medium1_TightPPET[runrange];
      }
    }
    else if (set==36) { // e24vhi_medium1 trigger MC eff w.r.t Tight++ offline
      vectETBinning = &m_ETbinsTrigger_e24;
      if (rel==9) {
  	vectCorr = &MCefficienciesRel172ICHEP_AFII_e24vhi_medium1_TightPPET[runrange];
	vectUncCorr = 0;
      } else {
  	vectCorr = &MCefficienciesRel172HCP_AFII_e24vhi_medium1_TightPPET[runrange];
	vectUncCorr = 0;
      }
    }
    else if (set==37) { // e24vhi_medium1 trigger SF w.r.t ML offline
      vectETBinning = &m_ETbinsTrigger_e24;
      if (rel==9) {
 	vectCorr = &efficienciesRel172ICHEP_AFII_e24vhi_medium1_MLET[runrange];
	vectUncCorr = &uncertaintiesRel172ICHEP_AFII_e24vhi_medium1_MLET[runrange];
      } else {
 	vectCorr = &efficienciesRel172HCP_AFII_e24vhi_medium1_MLET[runrange];
	vectUncCorr = &uncertaintiesRel172HCP_AFII_e24vhi_medium1_MLET[runrange];
      }
    }
    else if (set==38) { // e24vhi_medium1 trigger MC eff w.r.t ML offline
      vectETBinning = &m_ETbinsTrigger_e24;
      if (rel==9) {
	vectCorr = &MCefficienciesRel172ICHEP_AFII_e24vhi_medium1_MLET[runrange];
	vectUncCorr = 0;
      } else {
	vectCorr = &MCefficienciesRel172HCP_AFII_e24vhi_medium1_MLET[runrange];
	vectUncCorr = 0;
      }
    }
    else if (set==39) { // e12Tvh_loose1 trigger SF w.r.t Loose++ offline
      vectETBinning = &m_ETbinsTrigger_e12;
      vectCorr = &efficienciesRel172ICHEP_AFII_e12Tvh_loose1_LoosePPET[runrange];
      vectUncCorr = &uncertaintiesRel172ICHEP_AFII_e12Tvh_loose1_LoosePPET[runrange];
    }
    else if (set==40) { // e12Tvh_loose1 trigger MC eff w.r.t Loose++ offline
      vectETBinning = &m_ETbinsTrigger_e12;
      vectCorr = &MCefficienciesRel172ICHEP_AFII_e12Tvh_loose1_LoosePPET[runrange];
      vectUncCorr = 0;
    }
    else if (set==41) { // e12Tvh_loose1 trigger SF w.r.t Medium++ offline
      vectETBinning = &m_ETbinsTrigger_e12;
      vectCorr = &efficienciesRel172ICHEP_AFII_e12Tvh_loose1_MediumPPET[runrange];
      vectUncCorr = &uncertaintiesRel172ICHEP_AFII_e12Tvh_loose1_MediumPPET[runrange];
    }
    else if (set==42) { // e12Tvh_loose1 trigger MC eff w.r.t Medium++ offline
      vectETBinning = &m_ETbinsTrigger_e12;
      vectCorr = &MCefficienciesRel172ICHEP_AFII_e12Tvh_loose1_MediumPPET[runrange];
      vectUncCorr = 0;
    }
    else if (set==43) { // e12Tvh_loose1 trigger SF w.r.t Tight++ offline
      vectETBinning = &m_ETbinsTrigger_e12;
      vectCorr = &efficienciesRel172ICHEP_AFII_e12Tvh_loose1_TightPPET[runrange];
      vectUncCorr = &uncertaintiesRel172ICHEP_AFII_e12Tvh_loose1_TightPPET[runrange];
    }
    else if (set==44) { // e12Tvh_loose1 trigger MC eff w.r.t Tight++ offline
      vectETBinning = &m_ETbinsTrigger_e12;
      vectCorr = &MCefficienciesRel172ICHEP_AFII_e12Tvh_loose1_TightPPET[runrange];
      vectUncCorr = 0;
    }
    else if (set==45) { // e12Tvh_loose1 trigger SF w.r.t ML offline
      vectETBinning = &m_ETbinsTrigger_e12;
      vectCorr = &efficienciesRel172ICHEP_AFII_e12Tvh_loose1_MLET[runrange];
      vectUncCorr = &uncertaintiesRel172ICHEP_AFII_e12Tvh_loose1_MLET[runrange];
    }
    else if (set==46) { // e12Tvh_loose1 trigger MC eff w.r.t ML offline
      vectETBinning = &m_ETbinsTrigger_e12;
      vectCorr = &MCefficienciesRel172ICHEP_AFII_e12Tvh_loose1_MLET[runrange];
      vectUncCorr = 0;
    }
  }
  else if (rel==12) {// Rel17 2011 Forward update (HCP2012)
    
    if (set==23 || set == 24 || set == 47) { // Forward Loose/Medium/Tight: just make sure, it's not used below 20 GeV
      if (ET < 20000.) {
	std::cout << "egammaSFclass: ERROR : Out of Et range for forward electrons" << std::endl;
	return std::make_pair(-1.,-1.);
      } else {
	return std::make_pair(1.,0.);
      }
    }
  }


  if (vectCorr == 0) { // catch all missing cases
    std::cout << "egammaSFclass: ERROR : ET-correction factors not implemented for given selection" << std::endl;
    return std::make_pair(-1.,-1.);
  }

  int iETbin=-1;
  while (iETbin < int(vectETBinning->size()-1)
	 && ET>=vectETBinning->at(iETbin+1))
    iETbin++;
  if (iETbin<0 || iETbin>= int(vectETBinning->size()-1)) {
    std::cout << "egammaSFclass: ERROR : given ET value (" 
	      << ET << ") outside range of existing ET-correction factors" << std::endl;
    return std::make_pair(-1.,-1.);
  }

  float eff=vectCorr->at(iETbin)/100.;
  float unc=0;
  if (vectUncCorr)
    unc=vectUncCorr->at(iETbin)/100.;
  return std::make_pair(eff, unc);
}

std::pair<float,float> egammaSFclass::scaleFactorForward(float eta, int set)
{
  if (set == 0) {
    // Forward loose
    float abseta = std::abs(eta);
    if (2.5 <= abseta && abseta <= 3.16)
      return std::make_pair(1.010, 0.039);
    else if (3.35 <= abseta && abseta <= 4.9)
      return std::make_pair(1.020, 0.059);
    else {
      std::cout << "egammaSFclass: ERROR : Out of eta range for forward electrons" << std::endl;
      return std::make_pair(-1.,-1.);
    }

  } else if (set == 2) {
    // Forward tight
    float abseta = std::abs(eta);
    if (2.5 <= abseta && abseta <= 3.16)
      return std::make_pair(0.893, 0.047);
    else if (3.35 <= abseta && abseta <= 4.9)
      return std::make_pair(0.940, 0.061);
    else {
      std::cout << "egammaSFclass: ERROR : Out of eta range for forward electrons" << std::endl;
      return std::make_pair(-1.,-1.);
    }

  } else {
    std::cout << "egammaSFclass: ERROR : Forward electrons only have Loose or Tight cuts" << std::endl;
    return std::make_pair(-1.,-1.);
  }

}

void egammaSFclass::copyToVector(const float *myarray, int n, std::vector<float> &dest, double renorm)
{
  for (int i = 0; i < n; i++)
    dest.push_back(myarray[i]*renorm);
}


int egammaSFclass::getRunRange(int runnumber, const std::vector<int> &runranges)
{
  int runrange = -1;
  if (runnumber > 0) {
    for (unsigned int i = 0; i < runranges.size()-1; i++) {
      if (runranges[i] <= runnumber && runnumber < runranges[i+1]) {
	runrange = i;
	break;
      }
    }
  }
  
  static bool warnuser = true;
  if (runrange < 0 || runrange >= int(runranges.size())) {
    if (warnuser) {
      std::cout << "egammaSFclass: WARNING : no or wrong run number " << runnumber << " given for rel=8/9/10/11 (ICHEP/HCP 2012)" << std::endl;
      std::cout << "This is needed to get the run dependent trigger SF! Program will continue with 1st run range and without further warnings!!!" << std::endl;
      warnuser = false;
    }
    runrange = 0;
  }

  // hacked special mapping for HCP run ranges, see comment when filling runranges_HCP2012
  if (runrange == 3)
    runrange = 1;
  else if (runrange == 4)
    runrange = 3;

  return runrange;
}

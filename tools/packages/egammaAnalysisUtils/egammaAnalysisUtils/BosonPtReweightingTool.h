#ifndef BOSONPTREWEIGHTINGTOOL_H
#define BOSONPTREWEIGHTINGTOOL_H

/*
  Successor of BosonPtReweightingTool originally written for W,Z 2010 analysis by Jochen Hartert
  Major extensions by Jan Kretzschmar

  Purposes (possibly to be extended):
  * W or Z boson pt reweighting
  * W or Z boson rapidity reweighting (interesting for e.g. Alpgen samples)
  * W polarisation reweight and "corrections"

  Important: in accordance with ATLAS standards,
  all energies, momenta and four vectors are to be given in MeV,
  except for functions with explicit GeV in the name!

  Input is taken from external ROOT file stored in share directory "WZBosonKinematicsReweight.root"
  (In contrast to previous version, all generators are present in that file in sub-directories)

  Generators currently present are:
  * PythiaMC10
  * McAtNloMC10
  * PowhegHerwigMC10
  * PowhegPythiaMC10
  * PythiaMC11 (DS 106043-106047)
  * McAtNloMC11 (DS 106081-106088)
  * PowhegPythiaMC11 (DS 108297-108304)
  * PowhegHerwigMC11 (DS 113184-113187)
  * PowhegPythiaMC11_MSWT2008 (generated with MSTW2008 PDF)
  * PowhegPythiaMC11_HERAPDF15 (generated with HERAPDF15 PDF)
  * PowhegPythiaMC11_NNPDF21 (generated with NNPDF21 PDF)
  * AlpgenMC11 (DS 107650-107695)
  * AlpgenMC11_CT10 (PDF reweighted to CT10)
  * AlpgenMC11_NpX and AlpgenMC11_NpX_CT10 - as above, but Alpgen samples not merged
  * Sherpa14MC11 (DS 147770-147775)
  * PowhegPythia8MC11 (MC12 configuration @ 7 TeV)
  You may configure these by the above names, e.g. "PowhegPythiaMC11", or try a string containing the DS number,
  e.g. a full DS name will work "mc11_7TeV.108297.PowHegWplusenuPythia.e825_s1372_s1370_r3108_r3109"

  MC10 generators are more limited in information, e.g. do not contain W polarisation information.
  Reweighting Alpgen to somwthing else may not work well due to the split samples.

  In addition there are two legacy reweights are included (untested!)
  * PythiaMC11 -> ResBos for Z boson pt (weights by E. Sauvan, LAPP)
  * PythiaMC11 -> PythiaMC10 for Z/gamma* pt at high masses with empirically fitted weights,
                             this is only interesting for m=120 ~ 3000 GeV, mainly high mass DY and Z'

  For Z/gamma* boson pt reweight the main option is using weights
  from the mass range 66<m<116 GeV, aka "PeakWeight".

  There is  newly added option with mass dependent weights,
  covering the region ~20-200 GeV, aka "MassBinnedWeight". This is only supported for
  MC11/MC12 samples and not the full mass range is covered for all samples:
  * PythiaMC11: 20-200 GeV
  * McAtNloMC11: 20-200 GeV
  * PowhegPythiaMC11: 30-200 GeV
  * PowhegHerwigMC11: ~38-200 GeV
  * AlpgenMC11: 40-200 GeV
  * Sherpa14MC11: 40-200 GeV
  * PowhegPythia8MC11: 20-200 GeV
  Some rebinning, smoothing and interpolation is done here to provide a smooth mass and pt dependence
  and avoid excess statistical fluctuations.
  Note that this reweight is NOT supposed to change the mass-line shape, just the boson pt
  distribution at a given mass!

  There is another option for Pythia only and very high masses, see the above mentioned "HighMassFit".

  For W boson reweighting is always "PeakWeight".

  Note: Boson Pt weight uncertainty disabled for now, use alternative generator predictions!
  Best boson pt predicitons are (in approximately that order):
     Sherpa14MC11, PowhegPythia8MC11, AlpgenMC11 and PythiaMC10
  
  Example init and usage:
  BosonPtReweightingTool *bosonpt = 
           new BosonPtReweightingTool("PowhegPythiaMC11", "PowhegPythia8MC11",
                                      PeakWeight, "share/WZBosonKinematicsReweight.root");
  ptweight = bosonpt->GetPtWeightZ(true_boson_pt[MeV]);

  BosonPtReweightingTool *bosonptmass = 
           new BosonPtReweightingTool("PowhegPythiaMC11", "PowhegPythia8MC11",
                                      MassBinnedWeight, "share/WZBosonKinematicsReweight.root");
  ptweight_massdep = bosonptmass->GetPtWeightZ(true_boson_pt[MeV], true_boson_mass[MeV]);


  BosonPtReweightingTool *bosony = 
           new BosonPtReweightingTool("AlpgenMC11_Np0", "AlpgenMC11_Np0_CT10",
                                      PeakWeight, "share/WZBosonKinematicsReweight.root");
  yweight = bosonpt->GetRapidityWeightZ(true_boson_y); //note: feed "real rapidity", NOT pseudo-rapidity



  BosonPtReweightingTool *wpol = 
           new BosonPtReweightingTool("PowhegPythiaMC11", "Sherpa14MC11",
                                      PeakWeight, "share/WZBosonKinematicsReweight.root");
  polarisationweight = wpol->GetWPolarisationWeightWplus(true_chargedlepton_fourvector[MeV], true_neutrino_fourvector[MeV]);
  
  Alternatively you may also use the "direct" W polarisation function:
  polarisationweight = wpol->GetPolarisationWeightW (true_boson_pt[MeV], true_boson_rapidity,
                                                        true_costhetastar, true_W_charge[+-1]);
  where true_costhetastar can be calculated e.g. via CosThetaRestSystem().

  The destination polarisation values can be constrained to physical values (0..1) via
  bosonpt->SetImposePhysicalWpolConstraint(true);
  This is especially relevant for Powheg destination, which has a few negative values.


  To use fitted high mass boson pt dependence:
  BosonPtReweightingTool *bosonpt =
          new BosonPtReweightingTool("PythiaMC11", "PythiaMC10", HighMassFit,
                                      "share/WZBosonKinematicsReweight.root");
  ptweight = bosonpt->GetPtWeightZ(true_boson_pt[MeV], true_boson_mass[MeV]);


  Futher auxiliary functionality:
  * Fix of observed MC@NLO generator deficit in "Z samples" in ~60-65 GeV mass region,
  simple mass dependent weight seems ok, 
  samples affected: mc11_7TeV.10608{7,8}.McAtNloZ*.e1096*
  Use weight provided by LineShapeFix_Z_McAtNlo[GeV](mass [MeV or GeV])

*/

#include <TH1.h>
#include <TH2.h>
#include <TF1.h>

#include <TVector3.h>
#include <TLorentzVector.h>

#include <string>
#include <vector>

class BosonPtReweightingTool
{
 public:
  enum ePtWeightType {PeakWeight, HighMassFit, MassBinnedWeight};

  BosonPtReweightingTool(std::string source,
			 std::string destination,
			 ePtWeightType ptweight = PeakWeight,
			 std::string filename = "WZBosonKinematicsReweight.root"
			 );
  ~BosonPtReweightingTool();
  
  double GetPtWeightWplus ( double ptWGen ) const;
  double GetPtWeightWminus( double ptWGen ) const;
  double GetPtWeightZ     ( double ptZGen, double mZGen = 91000 ) const;

  double GetRapidityWeightWplus ( double yWGen ) const;
  double GetRapidityWeightWminus( double yWGen ) const;
  double GetRapidityWeightZ     ( double yZGen ) const;

  //   double GetPtWeightErrorUpWplus ( double ptWGen );
  //   double GetPtWeightErrorUpWminus( double ptWGen );
  //   double GetPtWeightErrorUpZ     ( double ptZGen, double mZGen = 91000 );

  //   double GetPtWeightErrorLowWplus ( double ptWGen );
  //   double GetPtWeightErrorLowWminus( double ptWGen );
  //   double GetPtWeightErrorLowZ     ( double ptZGen, double mZGen = 91000 );

  // main function for W Polarisation weight with direct input
  double GetPolarisationWeightW (double ptWGen, double yWGen,
				 double cosThetaGen, int qWgen) const; // use truth boson pt in MeV
  
  // auxiliary functions for W Polarisation weight using 4-vectors
  double GetPolarisationWeightWplus (const TLorentzVector & lep1,
				     const TLorentzVector & lep2) const
  { TLorentzVector boson = lep1 + lep2;
    return GetPolarisationWeightW(boson.Pt(), boson.Rapidity(),
				  CosThetaRestSystem(lep1, lep2), +1);}
  double GetPolarisationWeightWplusGeV (const TLorentzVector & lep1,
					const TLorentzVector & lep2) const
  { TLorentzVector boson = lep1 + lep2;
    return GetPolarisationWeightW(boson.Pt()*1000., boson.Rapidity(),
				  CosThetaRestSystem(lep1, lep2), +1);}


  double GetPolarisationWeightWminus (const TLorentzVector & lep1,
				      const TLorentzVector & lep2) const
  { TLorentzVector boson = lep1 + lep2;
    return GetPolarisationWeightW(boson.Pt(), boson.Rapidity(),
				  CosThetaRestSystem(lep1, lep2), -1);}
  double GetPolarisationWeightWminusGeV (const TLorentzVector & lep1,
					 const TLorentzVector & lep2 ) const
  { TLorentzVector boson = lep1 + lep2;
    return GetPolarisationWeightW(boson.Pt()*1000., boson.Rapidity(),
				  CosThetaRestSystem(lep1, lep2), -1);}


  void SetImposePhysicalWpolConstraint (bool in)
  { m_impose_physical_wpol_constraint = in;}

  static double LineShapeFix_Z_McAtNlo(double mass)
    { return LineShapeFix_Z_McAtNloGeV(mass/1000.);}
  static double LineShapeFix_Z_McAtNloGeV(double mass);

  static std::string MapMCName(const std::string &input);
 private:
  ePtWeightType m_PtWeight;

  TH1* m_h_Ptweights_Wplus;
  TH1* m_h_Ptweights_Wminus;
  TH1* m_h_Ptweights_Z;

  TH1* m_h_Rapidityweights_Wplus;
  TH1* m_h_Rapidityweights_Wminus;
  TH1* m_h_Rapidityweights_Z;

  std::vector<TH1*> m_h_Ptweights_Z_massbinned;
  static const unsigned int m_nMassBins = 11;
  static const double m_MassCenters[m_nMassBins];
  std::vector<double> m_PtzCenters;

  TF1* m_f_Ptweights_Z;
  std::vector<TF1*> m_param_Ptweights_Z;

  std::vector<TH2*> m_h_fLfR_f0_Wpm;

  bool m_impose_physical_wpol_constraint;

  // W polarisation helper functions
 public:
  static double CosThetaBeamSystem(const TLorentzVector & lep1, 
				   const TLorentzVector & lep2);
  static double CosThetaRestSystem(const TLorentzVector & lep1,
				   const TLorentzVector & lep2);
  static double PhiStar(const TLorentzVector & lep1, 
			const TLorentzVector & lep2);

 private:
  static double WPolariationFunction(double *x, double *coef);


/*   double m_scale; */

};

#endif // BOSONPTREWEIGHTINGTOOL_H

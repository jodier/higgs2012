#include "HiggsZZ4lUtils/BkgCrossSection.h"

double CrossSections::bkgCrossSection(int RunNumber, LHCEnergy energy, bool PrintSummary)
{

  if(energy != CrossSections::SevenTeV && energy != CrossSections::EightTeV) 
    {
      std::cout << "Unknown LHC Energy" << std::endl;
      return 0.;
    }
  else if(energy == CrossSections::SevenTeV)
    return CrossSections::GetBkgCrossSection7TeV(RunNumber,PrintSummary);
  else if(energy == CrossSections::EightTeV)
    return CrossSections::GetBkgCrossSection8TeV(RunNumber,PrintSummary);

  return -1; // yes, this is an error code
  
}

double CrossSections::GetBkgCrossSection7TeV(int RunNumber,bool PrintSummary)
{
  //EVERYTHING in fb  
  double crossSection=-1.0;
  std::string name="";
  
  if (RunNumber==107650){
    name="Alpgen+Jimmy Zee + 0	partons ";
    crossSection=827375.;
  }else if (RunNumber==107651){
    name="Alpgen+Jimmy Zee + 1	partons ";
    crossSection=166625.;
  }else if (RunNumber==107652){
    name="Alpgen+Jimmy Zee + 2	partons ";
    crossSection=50375.;
  }else if (RunNumber==107653){
    name="Alpgen+Jimmy Zee + 3	partons ";
    crossSection=14000.;
  }else if (RunNumber==107654){
    name="Alpgen+Jimmy Zee + 4	partons ";
    crossSection=3375.;
  }else if (RunNumber==107655){
    name="Alpgen+Jimmy Zee + 5	partons ";
    crossSection=1000.;
  }else if (RunNumber==107660){
    name="Alpgen+Jimmy Zmumu + 0	partons ";
    crossSection=822125;
  }else if (RunNumber==107661){
    name="Alpgen+Jimmy Zmumu + 1	partons ";
    crossSection=166000.;
  }else if (RunNumber==107662){
    name="Alpgen+Jimmy Zmumu + 2	 partons ";
    crossSection=49500.;
  }else if (RunNumber==107663){
    name="Alpgen+Jimmy Zmumu + 3	partons "; 
    crossSection=13875.;
  }else if (RunNumber==107664){
    name="Alpgen+Jimmy Zmumu + 4	partons ";
    crossSection=3500.;
  }else if (RunNumber==107665){
    name="Alpgen+Jimmy Zmumu + 5	partons ";
    crossSection=1000.;
  }else if (RunNumber==107670){
    name="Alpgen+Jimmy Ztautau + 0	partons ";
    crossSection=828125.;
  }else if (RunNumber==107671){
    name="Alpgen+Jimmy Ztautau + 1	partons ";
    crossSection=167375.;
  }else if (RunNumber==107672){
    name="Alpgen+Jimmy Ztautau + 2	partons ";
    crossSection=50375.;
  }else if (RunNumber==107673){
    name="Alpgen+Jimmy Ztautau + 3	partons ";
    crossSection=13750;
  }else if (RunNumber==107674){
    name="Alpgen+Jimmy Ztautau + 4	partons ";
    crossSection=3500.;
  }else if (RunNumber==107675){
    name="Alpgen+Jimmy Ztautau + 5	partons ";
    crossSection=1000.;
  }else if (RunNumber==116960){
    name="Zbb, Z->ee (ll > 30 !GeV) + 0 parton [m_4l 60/12 !GeV] ";
    crossSection=20.701*1.4;
  }else if (RunNumber==116961){
    name="Zbb, Z->ee (ll > 30 !GeV) + 1 parton [m_4l 60/12 !GeV] ";
    crossSection=18.8029*1.4;
  }else if (RunNumber==116962){
    name="Zbb, Z->ee (ll > 30 !GeV) + 2 parton [m_4l 60/12 !GeV] ";
    crossSection=10.505*1.4;
  }else if (RunNumber==116963){
    name="Zbb, Z->ee (ll > 30 !GeV) + 3 parton [m_4l 60/12 !GeV] ";
    crossSection=7.30463*1.4;
  }else if (RunNumber==116965){
    name="Zbb, Z->mumu (ll > 30 !GeV) + 0 parton [m_4l 60/12 !GeV] ";
    crossSection=21.516*1.4;
  }else if (RunNumber==116966){ 
    name="Zbb, Z->mumu (ll > 30 !GeV) + 1 parton [m_4l 60/12 !GeV] ";
    crossSection=19.6674*1.4;
  }else if (RunNumber==116967){
    name="Zbb, Z->mumu (ll > 30 !GeV) + 2 parton [m_4l 60/12 !GeV] ";
    crossSection=10.516*1.4;
  }else if (RunNumber==116968){
    name="Zbb, Z->mumu (ll > 30 !GeV) + 3 parton [m_4l 60/12 !GeV] ";
    crossSection=7.93834*1.4;
  }else if (RunNumber==116950){
    name="Zbb, Z->ee (ll > 30 !GeV) + 0 parton 3l filter, veto on m_4l 60/12 !GeV ";
    crossSection=756.32*1.4;
  }else if (RunNumber==116951){
    name="Zbb, Z->ee (ll > 30 !GeV) + 1 parton 3l filter, veto on m_4l 60/12 !GeV ";
    crossSection=432.25*1.4;
  }else if (RunNumber==116952){
    name="Zbb, Z->ee (ll > 30 !GeV) + 2 parton 3l filter, veto on m_4l 60/12 !GeV ";
    crossSection=176*1.4;
  }else if (RunNumber==116953){ 
    name="Zbb, Z->ee (ll > 30 !GeV) + 3 parton 3l filter, veto on m_4l 60/12 !GeV ";
    crossSection=96.75*1.4;
  }else if (RunNumber==116955){ 
    name="Zbb, Z->mumu (ll > 30 !GeV) + 0 parton 3l filter, veto on m_4l 60/12 !GeV ";
    crossSection=730.24*1.4;
  }else if (RunNumber==116956){ 
    name="Zbb, Z->mumu (ll > 30 !GeV) + 1 parton 3l filter, veto on m_4l 60/12 !GeV ";
    crossSection=432.25*1.4;
  }else if (RunNumber==116957){ 
    name="Zbb, Z->mumu (ll > 30 !GeV) + 2 parton 3l filter, veto on m_4l 60/12 !GeV ";
    crossSection=179.3*1.4;
  }else if (RunNumber==116958){ 
    name="Zbb, Z->mumu (ll > 30 !GeV) + 3 parton 3l filter, veto on m_4l 60/12 !GeV ";
    crossSection=92.3962*1.4;
  }else if (RunNumber==128130){ 
    name="AlpgenJimmyLowMassDYeebbNp0_nofilter ";
    crossSection=11675*1.25*1.4;
  }else if (RunNumber==128131){ 
    name="AlpgenJimmyLowMassDYeebbNp1_nofilter ";
    crossSection=1856.6*1.25*1.4;
  }else if (RunNumber==128132){ 
    name="AlpgenJimmyLowMassDYeebbNp2_nofilter ";
    crossSection=692.62*1.25*1.4;
  }else if (RunNumber==128133){ 
    name="AlpgenJimmyLowMassDYeebbNp3_nofilter ";
    crossSection=333.27*1.25*1.4;
  }else if (RunNumber==128135){ 
    name="AlpgenJimmyLowMassDYmumubbNp0_nofilter ";
    crossSection=11675*1.25*1.4;
  }else if (RunNumber==128136){ 
    name="AlpgenJimmyLowMassDYmumubbNp1_nofilter ";
    crossSection=1856.6*1.25*1.4;
  }else if (RunNumber==128137){ 
    name="AlpgenJimmyLowMassDYmumubbNp2_nofilter ";
    crossSection=692.62*1.25*1.4;
  }else if (RunNumber==128138){ 
    name="AlpgenJimmyLowMassDYmumubbNp3_nofilter ";
    crossSection=333.27*1.25*1.4;
  }else if (RunNumber==128140){ 
    name="AlpgenJimmyLowMassDYtautaubbNp0_nofilter ";
    crossSection=11675*1.25*1.4;
  }else if (RunNumber==128141){ 
    name="AlpgenJimmyLowMassDYtautaubbNp1_nofilter ";
    crossSection=1856.6*1.25*1.4;
  }else if (RunNumber==128142){ 
    name="AlpgenJimmyLowMassDYtautaubbNp2_nofilter ";
    crossSection=692.62*1.25*1.4;
  }else if (RunNumber==128143){ 
    name="AlpgenJimmyLowMassDYtautaubbNp3_nofilter ";
    crossSection=333.27*1.25*1.4;
  }else if (RunNumber==105200){ 
    name="ttbar (at least 1lepton filter) ";
    crossSection=91550.6;
  }else if (RunNumber==109345){ 
    name="ttbar (with Mll > 60 !GeV filter) ";
    crossSection=12707.2;
  }else if (RunNumber==109346){ 
    name="ttbar (with Mll > 60 !GeV filter and Mll > 12 !GeV) ";
    crossSection=515.2;
  }else if (RunNumber==109292){ 
    name="ZZ->4l 3LepFilter ";
    crossSection=91.54;
  }else if (RunNumber==126399){ 
    name="PowHegBoxZZeemm_Pythia_mll025_m4l40 ";
    crossSection=-1; // don't use this sample
  }else if (RunNumber==126400){ 
    name="PowHegBoxZZeeee_Pythia_mll025_m4l40 ";
    crossSection=-1; // don't use this sample
  }else if (RunNumber==126401){ 
    name="PowHegBoxZmmmm_Pythia_mll025_m4l40 ";
    crossSection=-1; // don't use this sample
  }else if (RunNumber==126859){ 
    name="PowHegZZ_4e_trilep5GeV_Pythia ";
    crossSection=46.6; 
  } else if (RunNumber==126860){ 
    name="PowHegZZ_4mu_trilep5GeV_Pythia ";
    crossSection=46.6; 
  }else if (RunNumber==126861){ 
    name="PowHegZZ_2e2mu_trilep5GeV_Pythia ";
    crossSection=99.1; 
  }else if (RunNumber==126862){ 
    name="PowHegZZ_2mu2tau_trilep5GeV_Pythia ";
    crossSection=99.1*0.124/0.617; 
  }else if (RunNumber==126863){ 
    name="PowHegZZ_2e2tau_trilep5GeV_Pythia ";
    crossSection=99.1*0.124/0.617; 
  }else if (RunNumber==126864){ 
    name="PowHegZZ_4tau_trilep5GeV_Pythia ";
    crossSection=44.6*0.0126/0.705; 
  }else if (RunNumber==128813){ 
    name="SherpaZZllll ";
    crossSection=-1;
  }else if (RunNumber==161988){ 
    name="Sherpa_CT10_llll_ZZ_EW6_noHiggs ";
    crossSection=0.77; // https://savannah.cern.ch/task/index.php?30125
  }else if (RunNumber==116600){ 
    name="gg2ZZ_JIMMY_ZZ4lep [2e2mu,2e2tau,2mu2tau] (gg2ZZv2.0) ";
    crossSection=-1; // don't use this sample - check 116601,116602,116603
  }else if (RunNumber==116601){ 
    name="gg2ZZ_JIMMY_ZZ4lep [4e] (gg2ZZv2.0) ";
    crossSection=0.86/2.;
  }else if (RunNumber==116602){ 
    name="gg2ZZ_JIMMY_ZZ4lep [4mu] (gg2ZZv2.0) ";
    crossSection=0.86/2.;
  }else if (RunNumber==116603){ 
    name="gg2ZZ_JIMMY_ZZ4lep [2e2mu] (gg2ZZv2.0) ";
    crossSection=0.86;
  }else if (RunNumber==128593){ 
    name="PythiaZZall_EF_15_5 ";
    crossSection=9.23e3*1.56*0.14657;
  }else if (RunNumber==109300){ 
    name="AlpgenJimmyZeebbNp0_nofilter ";
    crossSection=6520*1.25*1.4;
  }else if (RunNumber==109301){ 
    name="AlpgenJimmyZeebbNp1_nofilter ";
    crossSection=2470*1.25*1.4;
  }else if (RunNumber==109302){ 
    name="AlpgenJimmyZeebbNp2_nofilter ";
    crossSection=880*1.25*1.4;
  }else if (RunNumber==109303){ 
    name="AlpgenJimmyZeebbNp3_nofilter ";
    crossSection=387*1.25*1.4;
  }else if (RunNumber==109305){ 
    name="AlpgenJimmyZmumubbNp0_nofilter ";
    crossSection=6520*1.25*1.4;
  }else if (RunNumber==109306){ 
    name="AlpgenJimmyZmumubbNp1_nofilter ";
    crossSection=2470*1.25*1.4;
  }else if (RunNumber==109307){ 
    name="AlpgenJimmyZmumubbNp2_nofilter ";
    crossSection=880*1.25*1.4;
  }else if (RunNumber==109308){ 
    name="AlpgenJimmyZmumubbNp3_nofilter ";
    crossSection=387*1.25*1.4;
  }else if (RunNumber==109310){ 
    name="AlpgenJimmyZtautaubbNp0_nofilter ";
    crossSection=6520*1.25*1.4;
  }else if (RunNumber==109311){ 
    name="AlpgenJimmyZtautaubbNp1_nofilter ";
    crossSection=2470*1.25*1.4;
  }else if (RunNumber==109312){ 
    name="AlpgenJimmyZtautaubbNp2_nofilter ";
    crossSection=880*1.25*1.4;
  }else if (RunNumber==109313){ 
    name="AlpgenJimmyZtautaubbNp3_nofilter ";
    crossSection=387*1.25*1.4;
  }else if (RunNumber==116250){ 
    name="ZeeNp0 M10to40 pt20 ";
    crossSection=3051620*1.22;
  }else if (RunNumber==116251){ 
    name="ZeeNp1 M10to40 pt20 ";
    crossSection=87870*1.22;
  }else if (RunNumber==116252){ 
    name="ZeeNp2 M10to40 pt20 ";
    crossSection=41100*1.22;
  }else if (RunNumber==116253){ 
    name="ZeeNp3 M10to40 pt20 ";
    crossSection=8460*1.22;
  }else if (RunNumber==116254){ 
    name="ZeeNp4 M10to40 pt20 ";
    crossSection=1840*1.22;
  }else if (RunNumber==116255){ 
    name="ZeeNp5 M10to40 pt20 ";
    crossSection=460*1.22;
  }else if (RunNumber==116260){ 
    name="ZmumuNp0 M10to40 pt20 ";
    crossSection=3051620*1.22;
  }else if (RunNumber==116261){ 
    name="ZmumuNp1 M10to40 pt20 ";
    crossSection=87870*1.22;
  }else if (RunNumber==116262){ 
    name="ZmumuNp2 M10to40 pt20 ";
    crossSection=40950*1.22;
  }else if (RunNumber==116263){ 
    name="ZmumuNp3 M10to40 pt20 ";
    crossSection=8410*1.22;
  }else if (RunNumber==116264){ 
    name="ZmumuNp4 M10to40 pt20 ";
    crossSection=1850*1.22;
  }else if (RunNumber==116265){ 
    name="ZmumuNp5 M10to40 pt20 ";
    crossSection=460*1.22;
  }else if (RunNumber==116270){ 
    name="ZtautauNp0 M10to40 pt20 ";
    crossSection=3051620*1.22;
  }else if (RunNumber==116271){ 
    name="ZtautauNp1 M10to40 pt20 ";
    crossSection=87870*1.22;
  }else if (RunNumber==116272){ 
    name="ZtautauNp2 M10to40 pt20 ";
    crossSection=41100*1.22;
  }else if (RunNumber==116273){ 
    name="ZtautauNp3 M10to40 pt20 ";
    crossSection=8460*1.22;
  }else if (RunNumber==116274){ 
    name="ZtautauNp4 M10to40 pt20 ";
    crossSection=1840*1.22;
  }else if (RunNumber==116275){ 
    name="ZtautauNp5 M10to40 pt20 ";
    crossSection=460*1.22;
  }else if (RunNumber==128971){
    name="mc11_7TeV.128971.PythiaWZ_inclusive ";
    crossSection=12.006e3;
  }
  
  if (PrintSummary){
    if (crossSection!=-1){
      std::cout <<"-----------------------------------------------------------"<<std::endl;
      std::cout <<" Cross section for background process " << std::endl;
      std::cout <<"-----------------------------------------------------------"<<std::endl;
      std::cout <<"-----------------------------------------------------------"<<std::endl;
      std::cout <<"               Run Number                      = "<< RunNumber << std::endl;
      std::cout <<"               process                         = "<< name << std::endl;
      std::cout <<"               Cross section x Branching Ratio = "<< crossSection <<" fb^-1 "<< std::endl;
      std::cout <<"-----------------------------------------------------------"<<std::endl;
    }else{
      std::cout <<"-----------------------------------------------------------"<<std::endl;
      std::cout <<" Cross section for background process " << std::endl;
      std::cout <<"-----------------------------------------------------------"<<std::endl;
      std::cout <<"-----------------------------------------------------------"<<std::endl;
      std::cout <<"               Run Number                      = "<< RunNumber << std::endl;
      std::cout <<"               process                         = "<< name << std::endl;
      std::cout <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
      std::cout <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
      std::cout <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
      std::cout <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
      std::cout <<"                    NO Cross section !!!  " << std::endl;
      std::cout <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
      std::cout <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
      std::cout <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
      std::cout <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
    }
  }
  return crossSection;
}

double CrossSections::GetBkgCrossSection8TeV(int RunNumber,bool /*PrintSummary*/)
{

  //EVERYTHING in fb  
  double crossSection=-1.0;
  std::string name="";
  
  if (RunNumber==105200){
    name="McAtNloJimmy_CT10_ttbar_LeptonFilter";
    crossSection=238.06e3*0.648;
  }
  else if (RunNumber==110001){
    name="McAtNloJimmy_CT10_ttbar_dilepton";
    crossSection=238.06e3*0.1045;
  }
  else if (RunNumber==146369){
    name="ttbar_4LepMass_Mll50GeV12GeV";
    crossSection=238.06e3*0.1045*0.0306;
  }
  else if (RunNumber==126937){
    name="PowhegPythia8_AU2CT10_ZZ_4e_mll4_2pt5";
    crossSection=69.75;
  }
  else if (RunNumber==126938){
    name="PowhegPythia8_AU2CT10_ZZ_2e2mu_mll4_2pt5";
    crossSection=145.37;
  }
  else if (RunNumber==126939){
    name="PowhegPythia8_AU2CT10_ZZ_2e2tau_mll4_2pt5";
    crossSection=103.06;
  }
  else if (RunNumber==126940){
    name="PowhegPythia8_AU2CT10_ZZ_4mu_mll4_2pt5";
    crossSection=69.75;
  }
  else if (RunNumber==126941){
    name="PowhegPythia8_AU2CT10_ZZ_2mu2tau_mll4_2pt5";
    crossSection=103.06;
  }
  else if (RunNumber==126942){
    name="PowhegPythia8_AU2CT10_ZZ_4tau_mll4_2pt5";
    crossSection=8.15;
  }
  else if (RunNumber==116601){
    name="gg2ZZJimmy_AUET2CT10_ZZ4e";
    crossSection=1.345/2.; // From N. Kauer
  }
  else if (RunNumber==116602){
    name="gg2ZZJimmy_AUET2CT10_ZZ4mu";
    crossSection=1.345/2.; // From N. Kauer
  }
  else if (RunNumber==116603){
    name="gg2ZZJimmy_AUET2CT10_ZZ2e2mu";
    crossSection=1.345; // From N. Kauer
  }else if (RunNumber==161988){ 
    name="Sherpa_CT10_llll_ZZ_EW6_noHiggs ";
    crossSection=1.05; // https://savannah.cern.ch/task/index.php?30125
  }else if (RunNumber==107650){
    name="AlpgenJimmy_AUET2CTEQ6L1_ZeeNp0";
    crossSection=712000.*1.23;
  }
  else if (RunNumber==107651){
    name="AlpgenJimmy_AUET2CTEQ6L1_ZeeNp1";
    crossSection=155000.*1.23;
  }
  else if (RunNumber==107652){
    name="AlpgenJimmy_AUET2CTEQ6L1_ZeeNp2";
    crossSection=48800.*1.23;
  }
  else if (RunNumber==107653){
    name="AlpgenJimmy_AUET2CTEQ6L1_ZeeNp3";
    crossSection=14200.*1.23;
  }
  else if (RunNumber==107654){
    name="AlpgenJimmy_AUET2CTEQ6L1_ZeeNp4";
    crossSection=3770.*1.23;
  }
  else if (RunNumber==107655){
    name="AlpgenJimmy_AUET2CTEQ6L1_ZeeNp5";
    crossSection=1120.*1.23;
  }
  else if (RunNumber==107660){
    name="AlpgenJimmy_AUET2CTEQ6L1_ZmumuNp0";
    crossSection=712000.*1.23;
  }
  else if (RunNumber==107661){
    name="AlpgenJimmy_AUET2CTEQ6L1_ZmumuNp1";
    crossSection=155000.*1.23;
  }
  else if (RunNumber==107662){
    name="AlpgenJimmy_AUET2CTEQ6L1_ZmumuNp2";
    crossSection=48800.*1.23;
  }
  else if (RunNumber==107663){
    name="AlpgenJimmy_AUET2CTEQ6L1_ZmumuNp3";
    crossSection=14200.*1.23;
  }
  else if (RunNumber==107664){
    name="AlpgenJimmy_AUET2CTEQ6L1_ZmumuNp4";
    crossSection=3770.*1.23;
  }
  else if (RunNumber==107665){
    name="AlpgenJimmy_AUET2CTEQ6L1_ZmumuNp5";
    crossSection=1120.*1.23;
  }
  else if (RunNumber==107670){
    name="AlpgenJimmy_AUET2CTEQ6L1_ZtautauNp0";
    crossSection=712000.*1.23;
  }
  else if (RunNumber==107671){
    name="AlpgenJimmy_AUET2CTEQ6L1_ZtautauNp1";
    crossSection=155000.*1.23;
  }
  else if (RunNumber==107672){
    name="AlpgenJimmy_AUET2CTEQ6L1_ZtautauNp2";
    crossSection=48800.*1.23;
  }
  else if (RunNumber==107673){
    name="AlpgenJimmy_AUET2CTEQ6L1_ZtautauNp3";
    crossSection=14200.*1.23;
  }
  else if (RunNumber==107674){
    name="AlpgenJimmy_AUET2CTEQ6L1_ZtautauNp4";
    crossSection=3770.*1.23;
  }
  else if (RunNumber==107675){
    name="AlpgenJimmy_AUET2CTEQ6L1_ZtautauNp5";
    crossSection=1120.*1.23;
  }
  else if (RunNumber==147808){
    name="PowhegPythia8_AU2CT10_Ztautau";
    crossSection=1.109e6*1.04;
  }
  else if (RunNumber==147807){
    name="PowhegPythia8_AU2CT10_Zmumu";
    crossSection=1.109e6*1.04;
  }
  else if (RunNumber==147806){
    name="PowhegPythia8_AU2CT10_Zee";
    crossSection=1.109e6*1.04;
  }
  else if(RunNumber==146830){
    name="";
    crossSection=3.48e6*1.19;
  }
  else if(RunNumber==146831){
    name="";
    crossSection=0.11e6*1.19;
  }
  else if(RunNumber==146832){
    name="";
    crossSection=0.0523e6*1.19;
  }
  else if(RunNumber==146833){
    name="";
    crossSection=0.0113e6*1.19;
  }
  else if(RunNumber==146834){
    name="";
    crossSection=2.59e3*1.19;
  }
  else if(RunNumber==146835){
    name="";
    crossSection=6.93e2*1.19;
  }
  else if(RunNumber==146840){
    name="";
    crossSection=3.48e6*1.19;
  }
  else if(RunNumber==146841){
    name="";
    crossSection=0.11e6*1.19;
  }
  else if(RunNumber==146842){
    name="";
    crossSection=0.0523e6*1.19;
  }
  else if(RunNumber==146843){
    name="";
    crossSection=0.0113e6*1.19;
  }
  else if(RunNumber==146844){
    name="";
    crossSection=2.59e3*1.19;
  }
  else if(RunNumber==146845){
    name="";
    crossSection=6.93e2*1.19;
  }
  else if(RunNumber==146850){
    name="";
    crossSection=3.48e6*1.19;
  }
  else if(RunNumber==146851){
    name="";
    crossSection=0.11e6*1.19;
  }
  else if(RunNumber==146852){
    name="";
    crossSection=0.0523e6*1.19;
  }
  else if(RunNumber==146853){
    name="";
    crossSection=0.0113e6*1.19;
  }
  else if(RunNumber==146854){
    name="";
    crossSection=2.59e3*1.19;
  }
  else if(RunNumber==146980){
    name="Zbb, Z->ee + 0 partons (4 Leptons Mass)";
    crossSection=1.6*30.2473;
  }
  else if(RunNumber==146981){
    name="Zbb, Z->ee + 1 partons (4 Leptons Mass)";
    crossSection=1.6*25.9125;
  }
  else if(RunNumber==146982){
    name="Zbb, Z->ee + 2 partons (4 Leptons Mass)";
    crossSection=1.6*15.0649;
  }
  else if(RunNumber==146985){
    name="Zbb, Z->mumu + 0 partons (4 Leptons Mass)";
    crossSection=1.6*30.4634;
  }
  else if(RunNumber==146986){
    name="Zbb, Z->mumu + 1 partons (4 Leptons Mass)";
    crossSection=1.6*26.0188;
  }
  else if(RunNumber==146987){
    name="Zbb, Z->mumu + 2 partons (4 Leptons Mass)";
    crossSection=1.6*14.9299;
  }
  else if(RunNumber==146990){
    name="Zbb, Z->ee + 0 partons (4 Leptons Mass Veto + Pass 3 Leptons)";
    crossSection=1.6*749.9056;
  }
  else if(RunNumber==146991){
    name="Zbb, Z->ee + 1 partons (4 Leptons Mass Veto + Pass 3 Leptons)";
    crossSection=1.6*449.5598;
  }
  else if(RunNumber==146992){
    name="Zbb, Z->ee + 2 partons (4 Leptons Mass Veto + Pass 3 Leptons)";
    crossSection=1.6*192.7407;
  }
  else if(RunNumber==146995){
    name="Zbb, Z->mumu + 0 partons (4 Leptons Mass Veto + Pass 3 Leptons)";
    crossSection=1.6*752.9395;
  }
  else if(RunNumber==146996){
    name="Zbb, Z->mumu + 1 partons (4 Leptons Mass Veto + Pass 3 Leptons)";
    crossSection=1.6*449.7719;
  }
  else if(RunNumber==146997){
    name="Zbb, Z->mumu + 2 partons (4 Leptons Mass Veto + Pass 3 Leptons)";
    crossSection=1.6*192.7161;
  }
  else if(RunNumber==167162 ) {
    name="Powheg ZZ->4e with 100-150 mass filter";
    crossSection=5.22;
  }
  else if(RunNumber==167165 ) {
    name="Powheg ZZ->4mu with 100-150 mass filter";
    crossSection=5.45;
  }
  else if(RunNumber==167163 ) {
    name="Powheg ZZ->2e2mu with 100-150 mass filter";
    crossSection=10.69;
  }
  else if(RunNumber==161961 ) {
    name="mc12_8TeV.161961.Sherpa_CT10_lllnu_WZ";
    crossSection=2.5126e3;
  }
  else if(RunNumber==126894){
    name="Sherpa_CT10_llll_ZZ ";
    crossSection=8.7403e3;
  }  
  /**
  else if(RunNumber==146833){
    name="";
    crossSection=0.0113e6*1.19;
  }
  else if(RunNumber==146834){
    name="";
    crossSection=2.59e3*1.19;
  }
  else if(RunNumber==146835){
    name="";
    crossSection=6.93e2*1.19;
  }
  **/
  
  return crossSection;
}

double CrossSections::GetBkgCrossSection(int RunNumber,bool PrintSummary){
  //EVERYTHING in fb  
  double crossSection=-1.0;
  std::string name="";
  
  if (RunNumber==107650){
    name="Alpgen+Jimmy Zee + 0	partons ";
    crossSection=827375.;
  }else if (RunNumber==107651){
    name="Alpgen+Jimmy Zee + 1	partons ";
    crossSection=166625.;
  }else if (RunNumber==107652){
    name="Alpgen+Jimmy Zee + 2	partons ";
    crossSection=50375.;
  }else if (RunNumber==107653){
    name="Alpgen+Jimmy Zee + 3	partons ";
    crossSection=14000.;
  }else if (RunNumber==107654){
    name="Alpgen+Jimmy Zee + 4	partons ";
    crossSection=3375.;
  }else if (RunNumber==107655){
    name="Alpgen+Jimmy Zee + 5	partons ";
    crossSection=1000.;
  }else if (RunNumber==107660){
    name="Alpgen+Jimmy Zmumu + 0	partons ";
    crossSection=822125;
  }else if (RunNumber==107661){
    name="Alpgen+Jimmy Zmumu + 1	partons ";
    crossSection=166000.;
  }else if (RunNumber==107662){
    name="Alpgen+Jimmy Zmumu + 2	 partons ";
    crossSection=49500.;
  }else if (RunNumber==107663){
    name="Alpgen+Jimmy Zmumu + 3	partons "; 
    crossSection=13875.;
  }else if (RunNumber==107664){
    name="Alpgen+Jimmy Zmumu + 4	partons ";
    crossSection=3500.;
  }else if (RunNumber==107665){
    name="Alpgen+Jimmy Zmumu + 5	partons ";
    crossSection=1000.;
  }else if (RunNumber==107670){
    name="Alpgen+Jimmy Ztautau + 0	partons ";
    crossSection=828125.;
  }else if (RunNumber==107671){
    name="Alpgen+Jimmy Ztautau + 1	partons ";
    crossSection=167375.;
  }else if (RunNumber==107672){
    name="Alpgen+Jimmy Ztautau + 2	partons ";
    crossSection=50375.;
  }else if (RunNumber==107673){
    name="Alpgen+Jimmy Ztautau + 3	partons ";
    crossSection=13750;
  }else if (RunNumber==107674){
    name="Alpgen+Jimmy Ztautau + 4	partons ";
    crossSection=3500.;
  }else if (RunNumber==107675){
    name="Alpgen+Jimmy Ztautau + 5	partons ";
    crossSection=1000.;
  }else if (RunNumber==116960){
    name="Zbb, Z->ee (ll > 30 !GeV) + 0 parton [m_4l 60/12 !GeV] ";
    crossSection=20.701*1.4;
  }else if (RunNumber==116961){
    name="Zbb, Z->ee (ll > 30 !GeV) + 1 parton [m_4l 60/12 !GeV] ";
    crossSection=18.8029*1.4;
  }else if (RunNumber==116962){
    name="Zbb, Z->ee (ll > 30 !GeV) + 2 parton [m_4l 60/12 !GeV] ";
    crossSection=10.505*1.4;
  }else if (RunNumber==116963){
    name="Zbb, Z->ee (ll > 30 !GeV) + 3 parton [m_4l 60/12 !GeV] ";
    crossSection=7.30463*1.4;
  }else if (RunNumber==116965){
    name="Zbb, Z->mumu (ll > 30 !GeV) + 0 parton [m_4l 60/12 !GeV] ";
    crossSection=21.516*1.4;
  }else if (RunNumber==116966){ 
    name="Zbb, Z->mumu (ll > 30 !GeV) + 1 parton [m_4l 60/12 !GeV] ";
    crossSection=19.6674*1.4;
  }else if (RunNumber==116967){
    name="Zbb, Z->mumu (ll > 30 !GeV) + 2 parton [m_4l 60/12 !GeV] ";
    crossSection=10.516*1.4;
  }else if (RunNumber==116968){
    name="Zbb, Z->mumu (ll > 30 !GeV) + 3 parton [m_4l 60/12 !GeV] ";
    crossSection=7.93834*1.4;
  }else if (RunNumber==116950){
    name="Zbb, Z->ee (ll > 30 !GeV) + 0 parton 3l filter, veto on m_4l 60/12 !GeV ";
    crossSection=756.32*1.4;
  }else if (RunNumber==116951){
    name="Zbb, Z->ee (ll > 30 !GeV) + 1 parton 3l filter, veto on m_4l 60/12 !GeV ";
    crossSection=432.25*1.4;
  }else if (RunNumber==116952){
    name="Zbb, Z->ee (ll > 30 !GeV) + 2 parton 3l filter, veto on m_4l 60/12 !GeV ";
    crossSection=176*1.4;
  }else if (RunNumber==116953){ 
    name="Zbb, Z->ee (ll > 30 !GeV) + 3 parton 3l filter, veto on m_4l 60/12 !GeV ";
    crossSection=96.75*1.4;
  }else if (RunNumber==116955){ 
    name="Zbb, Z->mumu (ll > 30 !GeV) + 0 parton 3l filter, veto on m_4l 60/12 !GeV ";
    crossSection=730.24*1.4;
  }else if (RunNumber==116956){ 
    name="Zbb, Z->mumu (ll > 30 !GeV) + 1 parton 3l filter, veto on m_4l 60/12 !GeV ";
    crossSection=432.25*1.4;
  }else if (RunNumber==116957){ 
    name="Zbb, Z->mumu (ll > 30 !GeV) + 2 parton 3l filter, veto on m_4l 60/12 !GeV ";
    crossSection=179.3*1.4;
  }else if (RunNumber==116958){ 
    name="Zbb, Z->mumu (ll > 30 !GeV) + 3 parton 3l filter, veto on m_4l 60/12 !GeV ";
    crossSection=92.3962*1.4;
  }else if (RunNumber==128130){ 
    name="AlpgenJimmyLowMassDYeebbNp0_nofilter ";
    crossSection=11675*1.25*1.4;
  }else if (RunNumber==128131){ 
    name="AlpgenJimmyLowMassDYeebbNp1_nofilter ";
    crossSection=1856.6*1.25*1.4;
  }else if (RunNumber==128132){ 
    name="AlpgenJimmyLowMassDYeebbNp2_nofilter ";
    crossSection=692.62*1.25*1.4;
  }else if (RunNumber==128133){ 
    name="AlpgenJimmyLowMassDYeebbNp3_nofilter ";
    crossSection=333.27*1.25*1.4;
  }else if (RunNumber==128135){ 
    name="AlpgenJimmyLowMassDYmumubbNp0_nofilter ";
    crossSection=11675*1.25*1.4;
  }else if (RunNumber==128136){ 
    name="AlpgenJimmyLowMassDYmumubbNp1_nofilter ";
    crossSection=1856.6*1.25*1.4;
  }else if (RunNumber==128137){ 
    name="AlpgenJimmyLowMassDYmumubbNp2_nofilter ";
    crossSection=692.62*1.25*1.4;
  }else if (RunNumber==128138){ 
    name="AlpgenJimmyLowMassDYmumubbNp3_nofilter ";
    crossSection=333.27*1.25*1.4;
  }else if (RunNumber==128140){ 
    name="AlpgenJimmyLowMassDYtautaubbNp0_nofilter ";
    crossSection=11675*1.25*1.4;
  }else if (RunNumber==128141){ 
    name="AlpgenJimmyLowMassDYtautaubbNp1_nofilter ";
    crossSection=1856.6*1.25*1.4;
  }else if (RunNumber==128142){ 
    name="AlpgenJimmyLowMassDYtautaubbNp2_nofilter ";
    crossSection=692.62*1.25*1.4;
  }else if (RunNumber==128143){ 
    name="AlpgenJimmyLowMassDYtautaubbNp3_nofilter ";
    crossSection=333.27*1.25*1.4;
  }else if (RunNumber==105200){ 
    name="ttbar (at least 1lepton filter) ";
    crossSection=91550.6;
  }else if (RunNumber==109345){ 
    name="ttbar (with Mll > 60 !GeV filter) ";
    crossSection=12707.2;
  }else if (RunNumber==109346){ 
    name="ttbar (with Mll > 60 !GeV filter and Mll > 12 !GeV) ";
    crossSection=515.2;
  }else if (RunNumber==109292){ 
    name="ZZ->4l 3LepFilter ";
    crossSection=91.54;
  }else if (RunNumber==126399){ 
    name="PowHegBoxZZeemm_Pythia_mll025_m4l40 ";
    crossSection=-1; // don't use this sample
  }else if (RunNumber==126400){ 
    name="PowHegBoxZZeeee_Pythia_mll025_m4l40 ";
    crossSection=-1; // don't use this sample
  }else if (RunNumber==126401){ 
    name="PowHegBoxZmmmm_Pythia_mll025_m4l40 ";
    crossSection=-1; // don't use this sample
  }else if (RunNumber==126859){ 
    name="PowHegZZ_4e_trilep5GeV_Pythia ";
    crossSection=46.6; 
  } else if (RunNumber==126860){ 
    name="PowHegZZ_4mu_trilep5GeV_Pythia ";
    crossSection=46.6; 
  }else if (RunNumber==126861){ 
    name="PowHegZZ_2e2mu_trilep5GeV_Pythia ";
    crossSection=99.1; 
  }else if (RunNumber==126862){ 
    name="PowHegZZ_2mu2tau_trilep5GeV_Pythia ";
    crossSection=99.1; 
  }else if (RunNumber==126863){ 
    name="PowHegZZ_2e2tau_trilep5GeV_Pythia ";
    crossSection=99.1; 
  }else if (RunNumber==126864){ 
    name="PowHegZZ_4tau_trilep5GeV_Pythia ";
    crossSection=44.6; 
  }else if (RunNumber==128813){ 
    name="SherpaZZllll ";
    crossSection=-1;
  }else if (RunNumber==116600){ 
    name="gg2ZZ_JIMMY_ZZ4lep [2e2mu,2e2tau,2mu2tau] (gg2ZZv2.0) ";
    crossSection=-1; // don't use this sample - check 116601,116602,116603
  }else if (RunNumber==116601){ 
    name="gg2ZZ_JIMMY_ZZ4lep [4e] (gg2ZZv2.0) ";
    crossSection=0.86/2.;
  }else if (RunNumber==116602){ 
    name="gg2ZZ_JIMMY_ZZ4lep [4mu] (gg2ZZv2.0) ";
    crossSection=0.86/2.;
  }else if (RunNumber==116603){ 
    name="gg2ZZ_JIMMY_ZZ4lep [2e2mu] (gg2ZZv2.0) ";
    crossSection=0.86;
  }else if (RunNumber==128593){ 
    name="PythiaZZall_EF_15_5 ";
    crossSection=-1;
  }else if (RunNumber==109300){ 
    name="AlpgenJimmyZeebbNp0_nofilter ";
    crossSection=6520*1.25*1.4;
  }else if (RunNumber==109301){ 
    name="AlpgenJimmyZeebbNp1_nofilter ";
    crossSection=2470*1.25*1.4;
  }else if (RunNumber==109302){ 
    name="AlpgenJimmyZeebbNp2_nofilter ";
    crossSection=880*1.25*1.4;
  }else if (RunNumber==109303){ 
    name="AlpgenJimmyZeebbNp3_nofilter ";
    crossSection=387*1.25*1.4;
  }else if (RunNumber==109305){ 
    name="AlpgenJimmyZmumubbNp0_nofilter ";
    crossSection=6520*1.25*1.4;
  }else if (RunNumber==109306){ 
    name="AlpgenJimmyZmumubbNp1_nofilter ";
    crossSection=2470*1.25*1.4;
  }else if (RunNumber==109307){ 
    name="AlpgenJimmyZmumubbNp2_nofilter ";
    crossSection=880*1.25*1.4;
  }else if (RunNumber==109308){ 
    name="AlpgenJimmyZmumubbNp3_nofilter ";
    crossSection=387*1.25*1.4;
  }else if (RunNumber==109310){ 
    name="AlpgenJimmyZtautaubbNp0_nofilter ";
    crossSection=6520*1.25*1.4;
  }else if (RunNumber==109311){ 
    name="AlpgenJimmyZtautaubbNp1_nofilter ";
    crossSection=2470*1.25*1.4;
  }else if (RunNumber==109312){ 
    name="AlpgenJimmyZtautaubbNp2_nofilter ";
    crossSection=880*1.25*1.4;
  }else if (RunNumber==109313){ 
    name="AlpgenJimmyZtautaubbNp3_nofilter ";
    crossSection=387*1.25*1.4;
  }else if (RunNumber==116250){ 
    name="ZeeNp0 M10to40 pt20 ";
    crossSection=3051620*1.22;
  }else if (RunNumber==116251){ 
    name="ZeeNp1 M10to40 pt20 ";
    crossSection=87870*1.22;
  }else if (RunNumber==116252){ 
    name="ZeeNp2 M10to40 pt20 ";
    crossSection=41100*1.22;
  }else if (RunNumber==116253){ 
    name="ZeeNp3 M10to40 pt20 ";
    crossSection=8460*1.22;
  }else if (RunNumber==116254){ 
    name="ZeeNp4 M10to40 pt20 ";
    crossSection=1840*1.22;
  }else if (RunNumber==116255){ 
    name="ZeeNp5 M10to40 pt20 ";
    crossSection=460*1.22;
  }else if (RunNumber==116260){ 
    name="ZmumuNp0 M10to40 pt20 ";
    crossSection=3051620*1.22;
  }else if (RunNumber==116261){ 
    name="ZmumuNp1 M10to40 pt20 ";
    crossSection=87870*1.22;
  }else if (RunNumber==116262){ 
    name="ZmumuNp2 M10to40 pt20 ";
    crossSection=40950*1.22;
  }else if (RunNumber==116263){ 
    name="ZmumuNp3 M10to40 pt20 ";
    crossSection=8410*1.22;
  }else if (RunNumber==116264){ 
    name="ZmumuNp4 M10to40 pt20 ";
    crossSection=1850*1.22;
  }else if (RunNumber==116265){ 
    name="ZmumuNp5 M10to40 pt20 ";
    crossSection=460*1.22;
  }else if (RunNumber==116270){ 
    name="ZtautauNp0 M10to40 pt20 ";
    crossSection=3051620*1.22;
  }else if (RunNumber==116271){ 
    name="ZtautauNp1 M10to40 pt20 ";
    crossSection=87870*1.22;
  }else if (RunNumber==116272){ 
    name="ZtautauNp2 M10to40 pt20 ";
    crossSection=41100*1.22;
  }else if (RunNumber==116273){ 
    name="ZtautauNp3 M10to40 pt20 ";
    crossSection=8460*1.22;
  }else if (RunNumber==116274){ 
    name="ZtautauNp4 M10to40 pt20 ";
    crossSection=1840*1.22;
  }else if (RunNumber==116275){ 
    name="ZtautauNp5 M10to40 pt20 ";
    crossSection=460*1.22;
  }

  if (PrintSummary){
    if (crossSection!=-1){
      std::cout <<"-----------------------------------------------------------"<<std::endl;
      std::cout <<" Cross section for background process " << std::endl;
      std::cout <<"-----------------------------------------------------------"<<std::endl;
      std::cout <<"-----------------------------------------------------------"<<std::endl;
      std::cout <<"               Run Number                      = "<< RunNumber << std::endl;
      std::cout <<"               process                         = "<< name << std::endl;
      std::cout <<"               Cross section x Branching Ratio = "<< crossSection <<" fb^-1 "<< std::endl;
      std::cout <<"-----------------------------------------------------------"<<std::endl;
    }else{
      std::cout <<"-----------------------------------------------------------"<<std::endl;
      std::cout <<" Cross section for background process " << std::endl;
      std::cout <<"-----------------------------------------------------------"<<std::endl;
      std::cout <<"-----------------------------------------------------------"<<std::endl;
      std::cout <<"               Run Number                      = "<< RunNumber << std::endl;
      std::cout <<"               process                         = "<< name << std::endl;
      std::cout <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
      std::cout <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
      std::cout <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
      std::cout <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
      std::cout <<"                    NO Cross section !!!  " << std::endl;
      std::cout <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
      std::cout <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
      std::cout <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
      std::cout <<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
    }
  }
  return crossSection;
  
}


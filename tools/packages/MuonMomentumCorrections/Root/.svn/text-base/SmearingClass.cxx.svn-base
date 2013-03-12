/////////////////////////////////////////////////////////////////////////////
//           SmearingClass.cxx -- ATLAS Experiment Software               //
////////////////////////////////////////////////////////////////////////////
///
/// class providing corrections to the simulated muon pT to match pT in data.
/// Resolution smearing and scale shift numbers are preliminary
///
/// responsible: atlas-perf-muons-conveners (at) cern.ch
///
#include <cstdlib>
#include <sstream>
#include <cassert>
#include <cmath>
#include "MuonMomentumCorrections/SmearingClass.h"

using namespace MuonSmear;

TRandom3* SmearingClass::m_rand = 0;

SmearingClass::SmearingClass(){
  if(!m_rand) {
    m_rand = new TRandom3();
  }
  m_nb_regions = 4;
  m_CallSetClass=false;
}


SmearingClass::SmearingClass(std::string Data,
			     std::string Algo,
			     std::string SmearType,
			     std::string Rel,
			     std::string Dir) {
  
  if(!m_rand ) {
    m_rand = new TRandom3();
  }
  m_CallSetClass=true;
  m_nb_regions = 4;
  Initialize(Data,Algo,SmearType,Rel,Dir);
}


SmearingClass::SmearingClass(const SmearingClass& _rhs){
  const std::string SmearType = _rhs.Tsmear==SMEAR_QPT ? "q_pT" : "pT";
  m_nb_regions = 4;
  Initialize(_rhs.m_DataYear,_rhs.m_Algorithm,SmearType,_rhs.m_Release,_rhs.m_Fdir);
}


SmearingClass::~SmearingClass(){
  Finalize();
}


void SmearingClass::Initialize(std::string data,
			       std::string algo,
			       std::string smearType,
			       std::string rel,
			       std::string dir) {
  GeV=1000;
  m_pTmax=100000000;
  m_rand->SetSeed(0);
  useTan2=true;
  useScale=true;
  detRegion=0;
  scaleRegion=0;
  restrictCurvCorrSigma=0.0;
  m_ScaleType="";
  apply_to_data=false;
  useImprovedCombine=true;
  smearDeltaMS=0;
  smearDeltaID=0;
  smearDeltaCB=0;
  ptms=0;
  ptid=0;
  ptcb=0;
  eta=0;
  charge=0;
  if(m_CallSetClass){
    Tscale = SCALE_DEFAULT;
    SetAlgoSmearRelDir(data,algo,smearType,rel,dir);
  }
}


void SmearingClass::Finalize(){
  m_scale_ID.clear();
  m_scaleSyst_ID.clear();
  m_scale_MS.clear();
  m_scaleSyst_MS.clear();
  m_scale_CB.clear();
  m_scaleSyst_CB.clear();
  m_p1_ID.clear();
  m_p2_ID.clear();
  m_p2_ID_TAN.clear();
  m_p1_MS.clear();
  m_p2_MS.clear();
  m_E_p1_ID.clear();
  m_E_p2_ID.clear();
  m_E_p2_ID_TAN.clear();
  m_E_p1_MS.clear();
  m_E_p2_MS.clear();
  m_S_p1_ID.clear();
  m_S_p2_ID.clear();
  m_S_p2_ID_TAN.clear();
  m_S_p1_MS.clear();
  m_S_p2_MS.clear();
  m_MC_p1_ID.clear();
  m_MC_p2_ID.clear();
  m_MC_p2_ID_TAN.clear();
  m_MC_p0_MS.clear();
  m_MC_p1_MS.clear();
  m_MC_p2_MS.clear();
  m_CorrMatC0.clear();
  m_CorrMatC1.clear();
  m_CorrMatC2.clear();
  m_CorrMatC3.clear();
  m_CorrMatC4.clear();
  m_CorrMatC5.clear();
  m_CorrMatTanC0.clear();
  m_CorrMatTanC1.clear();
  m_CorrMatTanC2.clear();
  m_CorrMatTanC3.clear();
  m_CorrMatTanC4.clear();
  m_CorrMatTanC5.clear();
  InValues.clear();
}

void SmearingClass::CleanScales(){
  apply_to_data = false;
  Tscale = SCALE_DEFAULT;
  m_scaleBins.clear();
  m_S1_ID.clear();
  m_S2_ID.clear();
  m_S1_MS.clear();
  m_S2_MS.clear();
  m_S1_CB.clear();
  m_S2_CB.clear();
  m_S1Corr_ID.clear();
  m_S2Corr_ID.clear();
  m_S1Corr_MS.clear();
  m_S2Corr_MS.clear();
  m_S1Corr_CB.clear();
  m_S2Corr_CB.clear();
  m_S1ACorr_ID.clear();
  m_S2ACorr_ID.clear();
  m_S1ACorr_MS.clear();
  m_S2ACorr_MS.clear();
  m_S1ACorr_CB.clear();
  m_S2ACorr_CB.clear();
}

void SmearingClass::Clean(){
  
  m_scale_ID.clear();
  m_scaleSyst_ID.clear();
  m_scale_MS.clear();
  m_scaleSyst_MS.clear();
  m_scale_CB.clear();
  m_scaleSyst_CB.clear();
  CleanScales();
  m_p1_ID.clear();
  m_p2_ID.clear();
  m_p2_ID_TAN.clear();
  m_p1_MS.clear();
  m_p2_MS.clear();
  m_E_p1_ID.clear();
  m_E_p2_ID.clear();
  m_E_p2_ID_TAN.clear();
  m_E_p1_MS.clear();
  m_E_p2_MS.clear();
  m_S_p1_ID.clear();
  m_S_p2_ID.clear();
  m_S_p2_ID_TAN.clear();
  m_S_p1_MS.clear();
  m_S_p2_MS.clear();
  m_MC_p1_ID.clear();
  m_MC_p2_ID.clear();
  m_MC_p2_ID_TAN.clear();
  m_MC_p0_MS.clear();
  m_MC_p1_MS.clear();
  m_MC_p2_MS.clear();
  m_CorrMatC0.clear();
  m_CorrMatC1.clear();
  m_CorrMatC2.clear();
  m_CorrMatC3.clear();
  m_CorrMatC4.clear();
  m_CorrMatC5.clear();
  m_CorrMatTanC0.clear();
  m_CorrMatTanC1.clear();
  m_CorrMatTanC2.clear();
  m_CorrMatTanC3.clear();
  m_CorrMatTanC4.clear();
  m_CorrMatTanC5.clear();
  InValues.clear();
 
}


void SmearingClass::SetAlgoSmearRelDir(std::string Data,
				       std::string Algo,
				       std::string SmearType,
				       std::string Rel,
				       std::string Dir) {
  
  if(!m_CallSetClass){
    Initialize(Data,Algo,SmearType,Rel,Dir);
  }
  
  /*Checking DataType*/
  m_DataYear=Data;
  Tdata=SetData(m_DataYear);
  std::cout<<"SmearingClass INFO:: using " << m_DataYear <<std::endl;
  
  /*Checking algorithm*/
  if(Algo=="muid" || Algo=="staco" || Algo=="muons"){
    m_Algorithm=Algo;
    Talgo=SetAlgorithm(m_Algorithm);
    std::cout<<"SmearingClass INFO:: using " << m_Algorithm << " Algorithm "<<std::endl;
  }
  else{
    std::cerr<<__FILE__<<" line:"<<__LINE__<<" "<<"SmearingClass ERROR:: wrong Algorithm in input "<<Algo<<std::endl;
    std::cout<<"                      possible values are: "<<std::endl;
    std::cout<<"                               muid or staco or muons (only 2012)"<<std::endl;
    return;
  }
  
  /*Checking smearing type*/
  if(SmearType=="pT") {
    Tsmear=SMEAR_PT;
    std::cout<<"SmearingClass INFO:: using " << SmearType << " Smearing "<<std::endl;
  }
  else if(SmearType=="q_pT"){
    Tsmear=SMEAR_QPT;
    std::cout<<"SmearingClass INFO:: using " << SmearType << " Smearing "<<std::endl;
  }
  else{
    std::cerr<<__FILE__<<" line:"<<__LINE__<<" "<<"SmearingClass ERROR:: wrong Smear Type in input "<<SmearType<<std::endl;
    std::cout<<"                      possible values are: "<<std::endl;
    std::cout<<"                               pT ot q_pT "<<std::endl;
    return;
  }

  /*Checking reconstruction release*/
  if(Rel=="Rel16.6" || Rel=="Rel17" || Rel=="Rel17.2" || Rel == "Rel17.2Repro"){
    m_Release=Rel;
    Trel=SetRelease(m_Release);
    std::cout<<"SmearingClass INFO:: using " << m_Release << " Release "<<std::endl;
  }
  else{
    std::cerr<<__FILE__<<" line:"<<__LINE__<<" "<<"SmearingClass ERROR:: wrong Release in input "<<Rel<<std::endl;
    std::cout<<"                      possible values are: "<<std::endl;
    std::cout<<"                               Rel16.6, Rel17, Rel17.2"<<std::endl;
    return;
  }
  
  /*Checking path*/
  if(Dir!=""){
    m_Fdir=Dir;
    std::cout<<"SmearingClass INFO:: Using user defined path!"<<std::endl;
    std::cout<<"                     "<<m_Fdir<<std::endl;
  }
  else{
    char *tmparea=getenv("TestArea");
    std::string testarea="";
    if(tmparea==NULL){
      tmparea=getenv("ROOTCOREDIR");
      if(tmparea==NULL){
	m_Fdir="/InstallArea/share/";
      }
      else{
	testarea = tmparea;
	m_Fdir = testarea + "/../MuonMomentumCorrections/share/";
      }
    } 
    else{
      /* Athena running */
      testarea=tmparea;
      m_Fdir=testarea+"/InstallArea/share/";
    }
    std::cout<<"SmearingClass INFO:: Using default path!"<<std::endl;
    std::cout<<"                     "<<m_Fdir<<std::endl;
  }

  if(m_Algorithm=="muons" && m_DataYear!="Data12"){
    std::cerr<<__FILE__<<" line:"<<__LINE__<<" "<<"SmearingClass ERROR:: wrong settings:"<<std::endl;
    std::cout<<"                           'muons' algorithm available only for 2012 Data!"<<std::endl;
  }

  /*Filling Regions*/
  SetRegions();
  
  /*Filling Corrections Values*/
  FillValues();
}


void SmearingClass::SetRegions(){
  
  m_eta_min.clear();
  m_eta_max.clear();
  m_phi_min.clear();
  m_phi_max.clear();
  
  double tmpval;
  int i=0;
  std::string tmpname;
  std::string regions = m_Fdir+"Regions.dat";
  if (Trel == REL17_2_REPRO) 
    regions = m_Fdir+"RegionsRepro.dat";

  InValues.open(regions.c_str());
  i=0;
  if(!InValues.good()){
    std::cerr<<__FILE__<<" line:"<<__LINE__<<" "<<"SmearingClass ERROR:: File "<<regions<<" NOT FOUND!!"<<std::endl;
    std::cout<<"                      Please provide a correct path!"<<std::endl;
    return;
  }
  else{
    while(!InValues.eof()){
      tmpval=0;
      if(i==0){
	getline(InValues,tmpname);
      }
      if(InValues.eof()) break;

      InValues>>tmpval;
      m_eta_min.push_back(tmpval);
      InValues>>tmpval;
      m_eta_max.push_back(tmpval);
      InValues>>tmpval;
      m_phi_min.push_back(tmpval);
      InValues>>tmpval;
      m_phi_max.push_back(tmpval);
      ++i;
    }
  }
  InValues.close();
  InValues.clear();
  
  if(Trel<REL17){
    m_nb_regions=4;
  }
  else{
    m_nb_regions=m_eta_min.size();
  }
  
}


void SmearingClass::FillValues(){
  /* Choose MuID or Staco Algorithm Values */
  
  Clean();
  double tmpval;
  int i=0;
  std::string tmpname;
  std::string scale_val = m_Fdir+"Scale_values_"+m_Algorithm+"_"+m_Release+".dat";
  std::string data_val  = m_Fdir+m_DataYear+"_values_"+m_Algorithm+"_"+m_Release+".dat";
  std::string mc_val    = m_Fdir+"MC_values_"+m_Algorithm+"_"+m_Release+".dat";
  std::string corr_val  = m_Fdir+m_DataYear+"_CorrMatrix_"+m_Algorithm+"_"+m_Release+".dat";
  
  /* filling scale vectors*/
  InValues.open(scale_val.c_str());
  i=0;
  if(!InValues.good()){
    std::cerr<<__FILE__<<" line:"<<__LINE__<<" "<<"SmearingClass ERROR:: File "<<scale_val<<" NOT FOUND!!"<<std::endl;
    std::cout<<"                      Please provide a correct path!"<<std::endl;
    return;
  }
  else{
    while(InValues.good() && i<m_nb_regions){
      tmpval=0;
      if(i==0){
	getline(InValues,tmpname);
      }
      InValues>>tmpval;
      m_scale_ID.push_back(tmpval);
      InValues>>tmpval;
      m_scaleSyst_ID.push_back(tmpval);
      InValues>>tmpval;
      m_scale_MS.push_back(tmpval);
      InValues>>tmpval;
      m_scaleSyst_MS.push_back(tmpval);
      InValues>>tmpval;
      m_scale_CB.push_back(tmpval);
      InValues>>tmpval;
      m_scaleSyst_CB.push_back(tmpval);
      i++;
    }
  }
  InValues.close();
  InValues.clear();
  
  /* filling data vectors*/
  InValues.open(data_val.c_str());
  i=0;
  if(!InValues.good()){
    std::cerr<<__FILE__<<" line:"<<__LINE__<<" "<<"SmearingClass ERROR:: File "<<data_val<<" NOT FOUND!!"<<std::endl;
    std::cout<<"                      Please provide a correct path!"<<std::endl;
    return;
  }
  else{
    while(InValues.good()&& i<m_nb_regions){
      /*main values*/
      tmpval=0;
      if(i==0){
	getline(InValues,tmpname);
      }
      InValues>>tmpval;
      m_p1_ID.push_back(tmpval);
      InValues>>tmpval;
      m_p2_ID.push_back(tmpval);
      InValues>>tmpval;
      m_p2_ID_TAN.push_back(tmpval);
      InValues>>tmpval;
      m_p1_MS.push_back(tmpval);
      InValues>>tmpval;
      m_p2_MS.push_back(tmpval);
      /*errors*/
      InValues>>tmpval;
      m_E_p1_ID.push_back(tmpval);
      InValues>>tmpval;
      m_E_p2_ID.push_back(tmpval);
      InValues>>tmpval;
      m_E_p2_ID_TAN.push_back(tmpval);
      InValues>>tmpval;
      m_E_p1_MS.push_back(tmpval);
      InValues>>tmpval;
      m_E_p2_MS.push_back(tmpval);
      /*systematic*/
      InValues>>tmpval;
      m_S_p1_ID.push_back(tmpval);
      InValues>>tmpval;
      m_S_p2_ID.push_back(tmpval);
      InValues>>tmpval;
      m_S_p2_ID_TAN.push_back(tmpval);
      InValues>>tmpval;
      m_S_p1_MS.push_back(tmpval);
      InValues>>tmpval;
      m_S_p2_MS.push_back(tmpval);
    }
  }
  InValues.close();
  InValues.clear();
  
  /* filling mc vectors*/
  InValues.open(mc_val.c_str());
  i=0;
  if(!InValues.good()){
    std::cerr<<__FILE__<<" line:"<<__LINE__<<" "<<"SmearingClass ERROR:: File "<<mc_val<<" NOT FOUND!!"<<std::endl;
    std::cout<<"                      Please provide a correct path!"<<std::endl;
    return;
  }
  else{
    while(InValues.good() && i<m_nb_regions){
      tmpval=0;
      if(i==0){
	getline(InValues,tmpname);
      }
      InValues>>tmpval;
      m_MC_p1_ID.push_back(tmpval);
      InValues>>tmpval;
      m_MC_p2_ID.push_back(tmpval);
      InValues>>tmpval;
      m_MC_p2_ID_TAN.push_back(tmpval);
      InValues>>tmpval;
      m_MC_p0_MS.push_back(tmpval);
      InValues>>tmpval;
      m_MC_p1_MS.push_back(tmpval);
      InValues>>tmpval;
      m_MC_p2_MS.push_back(tmpval);
    }
  }
  InValues.close();
  InValues.clear();
  
  /* filling correlation vectors*/
  InValues.open(corr_val.c_str());
  i=0;
  if(!InValues.good()){
    std::cerr<<__FILE__<<" line:"<<__LINE__<<" "<<"SmearingClass ERROR:: File "<<corr_val<<" NOT FOUND!!"<<std::endl;
    std::cout<<"                      Please provide a correct path!"<<std::endl;
    return;
  }
  else{
    while(InValues.good() && i<m_nb_regions){
      tmpval=0;
      if(i==0){
	getline(InValues,tmpname);
      }
      InValues>>tmpval;
      m_CorrMatC0.push_back(tmpval);
      m_CorrMatTanC0.push_back(tmpval);
      
      InValues>>tmpval;
      m_CorrMatC1.push_back(tmpval);
      m_CorrMatTanC1.push_back(tmpval);
      
      InValues>>tmpval;
      m_CorrMatC2.push_back(tmpval);
      m_CorrMatTanC2.push_back(tmpval);
    
      InValues>>tmpval;
      m_CorrMatC3.push_back(tmpval);
      m_CorrMatTanC3.push_back(tmpval);
    
      InValues>>tmpval;
      m_CorrMatC4.push_back(tmpval);
      m_CorrMatTanC4.push_back(tmpval);
      
      InValues>>tmpval;
      m_CorrMatC5.push_back(tmpval);
      m_CorrMatTanC5.push_back(tmpval);
    }
  }
  InValues.close();
  InValues.clear();
  
}


void SmearingClass::PrintValues(){
  
  std::cout<<"SmearingClass INFO:: Checking if all variables are filled ... "<<std::endl;
  for(UInt_t i=0; i<m_scale_CB.size(); i++){
    std::cout<<std::endl;
    
    std::cout<<"  scale_ID["<<i<<"] "<<m_scale_ID[i]<<std::endl;
    std::cout<<"  scaleSyst_ID["<<i<<"] "<<m_scaleSyst_ID[i]<<std::endl;
    std::cout<<"  scale_MS["<<i<<"] "<<m_scale_MS[i]<<std::endl;
    std::cout<<"  scaleSyst_MS["<<i<<"] "<<m_scaleSyst_MS[i]<<std::endl;
    std::cout<<"  scale_CB["<<i<<"] "<<m_scale_CB[i]<<std::endl;
    std::cout<<"  scaleSyst_CB["<<i<<"] "<<m_scaleSyst_CB[i]<<std::endl;
    
    std::cout<<std::endl;
    
    std::cout<<"  p1_ID["<<i<<"] "<<m_p1_ID[i]<<std::endl;
    std::cout<<"  p2_ID["<<i<<"] "<<m_p2_ID[i]<<std::endl;
    std::cout<<"  p2_ID_TAN["<<i<<"] "<<m_p2_ID_TAN[i]<<std::endl;
    std::cout<<"  p1_MS["<<i<<"] " <<m_p1_MS[i]<<std::endl;
    std::cout<<"  p2_MS["<<i<<"] " <<m_p2_MS[i]<<std::endl;
    
    std::cout<<std::endl;
    
    std::cout<<"  E_p1_ID["<<i<<"] "<<m_E_p1_ID[i]<<std::endl;
    std::cout<<"  E_p2_ID["<<i<<"] "<<m_E_p2_ID[i]<<std::endl;
    std::cout<<"  E_p2_ID_TAN["<<i<<"] "<<m_E_p2_ID_TAN[i]<<std::endl;
    std::cout<<"  E_p1_MS["<<i<<"] "<<m_E_p1_MS[i]<<std::endl;
    std::cout<<"  E_p2_MS["<<i<<"] "<<m_E_p2_MS[i]<<std::endl;
    
    std::cout<<std::endl;
    
    std::cout<<"  S_p1_ID["<<i<<"] "<<m_S_p1_ID[i]<<std::endl;
    std::cout<<"  S_p2_ID["<<i<<"] "<<m_S_p2_ID[i]<<std::endl;
    std::cout<<"  S_p2_ID_TAN["<<i<<"] "<<m_S_p2_ID_TAN[i]<<std::endl;
    std::cout<<"  S_p1_MS["<<i<<"] "<<m_S_p1_MS[i]<<std::endl;
    std::cout<<"  S_p2_MS["<<i<<"] "<<m_S_p2_MS[i]<<std::endl;
    
    std::cout<<std::endl;
    
    std::cout<<"  MC_p1_ID["<<i<<"] "<<m_MC_p1_ID[i]<<std::endl;
    std::cout<<"  MC_p2_ID["<<i<<"] "<<m_MC_p2_ID[i]<<std::endl;
    std::cout<<"  MC_p2_ID_TAN["<<i<<"] "<<m_MC_p2_ID_TAN[i] << std::endl;
    std::cout<<"  MC_p0_MS["<<i<<"] "<<m_MC_p0_MS[i]<<std::endl;
    std::cout<<"  MC_p1_MS["<<i<<"] "<<m_MC_p1_MS[i]<<std::endl;
    std::cout<<"  MC_p2_MS["<<i<<"] "<<m_MC_p2_MS[i]<<std::endl;
    
    std::cout<<std::endl;
    
    std::cout<<"  CorrMatC0["<<i<<"] "<<m_CorrMatC0[i]<<std::endl;
    std::cout<<"  CorrMatC1["<<i<<"] "<<m_CorrMatC1[i]<<std::endl;
    std::cout<<"  CorrMatC2["<<i<<"] "<<m_CorrMatC2[i]<<std::endl;
    std::cout<<"  CorrMatC3["<<i<<"] "<<m_CorrMatC3[i]<<std::endl;
    std::cout<<"  CorrMatC4["<<i<<"] "<<m_CorrMatC4[i]<<std::endl;
    std::cout<<"  CorrMatC5["<<i<<"] "<<m_CorrMatC5[i]<<std::endl;

    std::cout<<""<<std::endl;
    
    std::cout<<"  CorrMatTanC0["<<i<<"] "<<m_CorrMatTanC0[i]<<std::endl;
    std::cout<<"  CorrMatTanC1["<<i<<"] "<<m_CorrMatTanC1[i]<<std::endl;
    std::cout<<"  CorrMatTanC2["<<i<<"] "<<m_CorrMatTanC2[i]<<std::endl;
    std::cout<<"  CorrMatTanC3["<<i<<"] "<<m_CorrMatTanC3[i]<<std::endl;
    std::cout<<"  CorrMatTanC4["<<i<<"] "<<m_CorrMatTanC4[i]<<std::endl;
    std::cout<<"  CorrMatTanC5["<<i<<"] "<<m_CorrMatTanC5[i]<<std::endl;

  }
}

int SmearingClass::GetScaleRegion(){
  
  if(m_scaleBins.empty()) return -1;
  double _min = m_scaleBins[0];
  double _max = m_scaleBins[m_scaleBins.size()-1];
  if( eta<_min ) { return 0; }
  if( eta>=_max ) { return m_scaleBins.size() - 1; }
  std::vector<double>::iterator lb = std::lower_bound(m_scaleBins.begin(),m_scaleBins.end(),eta+1e-9); // [first,last)
  return( std::min( static_cast<int>( std::distance(m_scaleBins.begin(),lb) ) , static_cast<int>(m_scaleBins.size()-1) ) );
}


void SmearingClass::FillScales(std::string Scaletype, bool ApplyScalesToData){
  
  m_ScaleType=Scaletype;
  /*Checking momentum scaling type*/
  if(m_ScaleType==""     || m_ScaleType=="default" || 
     m_ScaleType=="kpkm" || m_ScaleType=="KC"      || 
     m_ScaleType=="K"    || m_ScaleType=="C" ){
    
    std::cout<<"SmearingClass INFO:: using " << m_ScaleType << " Scaling "<<std::endl;
  }
  else{
    std::cerr<<__FILE__<<" line:"<<__LINE__<<" "<<"SmearingClass ERROR:: wrong Scale Type in input "<<m_ScaleType<<std::endl;
    std::cout<<"                      possible values are: {default,KC,K,C,kpkm} "<<std::endl;
    return;
  }
  /* Clean up old scale arrays */
  CleanScales();
  
  /* old non-charge-separated scales have already been loaded */
  if(m_ScaleType=="default" || m_ScaleType=="") return;
  /* Choose MuID or Staco Algorithm Values */
  std::string tmpname;
  /* correct charge-dependent momentum scale (k+ and k-) */
  std::string scale_val  = m_Fdir+m_DataYear+"_Scale_kpkm_values_"+m_Algorithm+"_"+m_Release+".dat";
  
  /* correct overall momentum scale and charge-dependent split (k and C) */
  if(m_ScaleType=="KC" || m_ScaleType=="K" || m_ScaleType=="C") {
    scale_val  = m_Fdir+m_DataYear+"_Scale_KC_values_"+m_Algorithm+"_"+m_Release+".dat";
  }
  std::cout<<"SmearingClass INFO:: loading scales from: " << scale_val << std::endl;
  apply_to_data = ApplyScalesToData;

  /* filling scale or shift vectors*/
  InValues.open(scale_val.c_str());
  if(!InValues.good()){
    std::cerr<<__FILE__<<" line:"<<__LINE__<<" "<<"SmearingClass ERROR:: File "<<scale_val<<" NOT FOUND!!"<<std::endl;
    std::cout<<"                      Please provide a correct path!"<<std::endl;
    return;
  }
  if(m_ScaleType=="kpkm") Tscale=SCALE_KPKM;
  else if(m_ScaleType=="KC") Tscale=SCALE_KC;
  else if(m_ScaleType=="K") Tscale=SCALE_K;
  else if(m_ScaleType=="C") Tscale=SCALE_C;

  // skip information line
  getline(InValues,tmpname);

  // retrieve binning
  getline(InValues,tmpname);
  std::istringstream iss(tmpname);
  iss >> tmpname; // skip lower bound of first bin (since it won't be used)
  copy(std::istream_iterator<double>(iss), std::istream_iterator<double>(), back_inserter(m_scaleBins));
  std::cout << "Loading muon momentum scales in " << m_scaleBins.size() << " bins" << std::endl;

  std::string curname = "cmb";
  double v1,v2,v3,w1,w2,w3;
  int ibin=0;
  while( getline(InValues,tmpname) ) {
    if(tmpname=="cmb" || tmpname=="exms" || tmpname=="id") {
      curname=tmpname;
      continue;
    }
    std::istringstream iss(tmpname);
    iss >> v1 >> v2 >> v3 >> w1 >> w2 >> w3;
    const double ss = restrictCurvCorrSigma;
    if(curname=="cmb") {
      m_S1_CB.push_back(v1);
      m_S1Corr_CB.push_back(v2);
      m_S1ACorr_CB.push_back(v3);
      // special handling is user requested to restrict curvature
      // corrections to bins where they are significant
      if(Tscale>=SCALE_KC && ss>0) {
	m_S2_CB.push_back(fabs(w1)>=w2*ss ? w1 : 0.0);
      }
      else m_S2_CB.push_back(w1);
      m_S2Corr_CB.push_back(w2);
      m_S2ACorr_CB.push_back(w3);
    }
    if(curname=="id") {
      m_S1_ID.push_back(v1);
      m_S1Corr_ID.push_back(v2);
      m_S1ACorr_ID.push_back(v3);
      // special handling is user requested to restrict curvature
      // corrections to bins where they are significant
      if(Tscale>=SCALE_KC && ss>0) {
	m_S2_ID.push_back(fabs(w1)>=w2*ss ? w1 : 0.0);
      }
      else m_S2_ID.push_back(w1);
      m_S2Corr_ID.push_back(w2);
      m_S2ACorr_ID.push_back(w3);
    }
    if(curname=="exms") {
      m_S1_MS.push_back(v1);
      m_S1Corr_MS.push_back(v2);
      m_S1ACorr_MS.push_back(v3);
      // special handling is user requested to restrict curvature
      // corrections to bins where they are significant
      if(Tscale>=SCALE_KC && ss>0) {
	m_S2_MS.push_back(fabs(w1)>=w2*ss ? w1 : 0.0);
      }
      else m_S2_MS.push_back(w1);
      m_S2Corr_MS.push_back(w2);
      m_S2ACorr_MS.push_back(w3);
    }
    ibin++;
  }
  assert(m_S1_MS.size() == m_S1_ID.size());
  assert(m_S1_MS.size() == m_S1_CB.size());
  assert(m_S1_MS.size() == m_scaleBins.size());

  InValues.close();
  InValues.clear();  
}


void SmearingClass::SetSeed(int seed) {
  m_rand->SetSeed(seed);
}


void SmearingClass::SetSeed(int evtnum,
			    int muon_index,
			    int offset) {
  
  m_rand->SetSeed(offset + evtnum + muon_index*100);
  
}


void SmearingClass::UseTan2(bool U) {
  /* use pT/tan(theta)^2 parameterization for CSC region */ 
  
  useTan2=U;
}


void SmearingClass::UseGeV() {
  /* if input momenta are in GeV */
  
  GeV=1;
}


void SmearingClass::UseScale(bool applyScale) {
  /* also use momentum scale, set as default */
  
  useScale=applyScale;
}


void SmearingClass::RestrictCurvatureCorrections(double nsigma) {
  /* if "KC" or "C" scale corrections are used,
     the curvature shift correction is applied only in bins
     where the correction has a >2.5 sigma effect
  */

  assert(m_scaleBins.empty() && "ERROR: RestrictCurvatureCorrections() must be called BEFORE FillScales()");
  restrictCurvCorrSigma=nsigma;
}


void SmearingClass::UseImprovedCombine() {
  /* also use improved combine */
  
  useImprovedCombine=true;
}


void SmearingClass::ApplyToData(bool U) {
  /* use pT/tan(theta)^2 parameterization for CSC region */ 
  
  apply_to_data=U;
}


void SmearingClass::Event(const TLorentzVector &p, 
			  std::string DetType,
                          double Charge) {
  
  Event(p.Pt(), p.Eta(), DetType, Charge, p.Phi());
  return;
}


void SmearingClass::Event(double Pt,
			  double Eta,
			  std::string DetType,
			  double Charge,
			  double Phi) {
  
  /* MS or ID smearing only. DetType="MS","ID" */
  
  ptms=0;
  ptid=0;
  ptcb=0;
  
  if(DetType=="MS"){ 
    Tdet=DET_MS;
    ptms = Pt;
  }
  else if(DetType=="ID"){
    Tdet=DET_ID;
    ptid = Pt;
  }
  else std::cerr<<__FILE__<<" line:"<<__LINE__<<" "<<"SmearingClass ERROR: wrong DetType in input "<<DetType<<std::endl;
  
  eta=Eta;   
  phi = Phi;
  charge = Charge;
  Event();
}

void SmearingClass::Event(const TLorentzVector & p_MS,
			  const TLorentzVector & p_ID,
			  const TLorentzVector & p_CB,
			  double Charge) {
  
  Event(p_MS.Pt(),p_ID.Pt(), p_CB.Pt(), p_CB.Eta(), Charge, p_CB.Phi());
  return;
  
}

void SmearingClass::Event(double PtMS,
			  double PtID,
			  double PtCB,
			  double Eta,
			  double Charge,
			  double Phi) {
  
  /* For full MS ID and CB smearing */
  ptms=0;
  ptid=0;
  ptcb=0;
  if(PtMS<=0 && PtID>0){
    std::cout<<__FILE__<<" line:"<<__LINE__<<" "<<"SmearingClass WARNING:: pTMS="<<PtMS<<"( <=0 ); pTID="<<PtID<<" ..."
	     <<" applying ID smearing only!"<<std::endl;
    Tdet=DET_ID;
    ptid=PtID;
    eta=Eta;
    phi=Phi;
    charge = Charge;
    Event();
  }
  else if(PtID<=0 && PtMS>0){
    std::cout<<__FILE__<<" line:"<<__LINE__<<" "<<"SmearingClass WARNING:: pTID <=0 ..."
	     <<" applying MS smearing only!"<<std::endl;
    Tdet=DET_MS;
    ptms=PtMS;
    eta=Eta;
    phi=Phi;
    charge = Charge;
    Event();
  }
  else if(PtID<=0 && PtMS<=0){
    std::cout<<__FILE__<<" line:"<<__LINE__<<" "<<"SmearingClass ERROR:: both pTID & pTMS <=0 ..."
	     <<" smearing NOT APPLICABLE!"<<std::endl;
  }
  else{
    Tdet=DET_CB;
    ptms=PtMS;
    ptid=PtID;
    ptcb=PtCB;
    eta=Eta;
    phi=Phi;
    charge = Charge;
    Event();
  }
}


void SmearingClass::Event() {
  
  smearDeltaMS=0;
  smearDeltaID=0;
  smearDeltaCB=0;
  
  /* Detector Region */
  if(Trel<REL17){
    detRegion = getRegionOld(eta);
  }
  else{
    detRegion = getRegion(eta,phi);
  }
  
  /* Scale Region */
  scaleRegion = GetScaleRegion();
  
  if(false) { 
    /* debugging */
    std::cerr << m_scaleBins.size() << " : " << "eta = " << eta << " ; region = " << scaleRegion << "; S1 = " << m_S1_CB[scaleRegion] << std::endl;
  }
  
  /* If SmearingClass is applied to data, smearing makes no sense
     (there is no way to "unsmear" the data to make it match MC)
     However, the momentum scale or curvature corrections are still valid
     and will be applied accordingly in pTCB, pTMS, pTID methods.
   */
  if(apply_to_data) return;
  
  g1 = m_rand->Gaus(0,1);
  g2 = m_rand->Gaus(0,1);
  g3 = m_rand->Gaus(0,1);
  g4 = m_rand->Gaus(0,1);

  /** Definition: pT'=pT(1+smear) **/
  smearDeltaMS=Smearing(DET_MS);
  smearDeltaID=Smearing(DET_ID);
  if (Tdet==DET_CB){ 
    smearDeltaCB=ICombine(smearDeltaMS,smearDeltaID);
  }
  ErrorMatrix();
}


double SmearingClass::Smearing(int DetType) {
  
  if (detRegion<0 || detRegion>=m_nb_regions) { 
    return 0; 
  }
  
  if (DetType==DET_MS){
    if(ptms==0) return 0;
    else return ( m_p1_MS[detRegion]*g1 + m_p2_MS[detRegion]*g2*ptms/GeV );
  }
  else if(DetType==DET_ID){
    if (useTan2 && m_p2_ID_TAN[detRegion]!=0){
      return ( m_p1_ID[detRegion]*g3 + m_p2_ID_TAN[detRegion]*g4*ptid/GeV*sinh(eta)*sinh(eta) );
    }
    else{
      return ( m_p1_ID[detRegion]*g3 + m_p2_ID[detRegion]*g4*ptid/GeV );
    }
  }
  else{ 
    std::cerr<<__FILE__<<" line:"<<__LINE__<<" "<<"SmearingClass ERROR:: DetType not defined "<<DetType<<std::endl;
  }
  return 0;
}

//Smearing with systematic variation not using the error matrix (no correlations)
double SmearingClass::SmearingSYSVar(int DetType, double var){
  
  if(var != 1. && var != -1 ){
    std::cerr<<__FILE__<<" line:"<<__LINE__<<" "<<"SmearingClass ERROR:: sys variation not +1 not -1 "<<std::endl;
    return 0;
  }

  if (detRegion<0 || detRegion>=m_nb_regions) { 
    return 0; 
  }
  double p1_MS_var=0., p2_MS_var=0., p1_ID_var=0., p2_ID_var=0.;
  
  if (DetType==DET_MS){
    if(ptms==0) return 0;
    else {
      p1_MS_var = m_p1_MS[detRegion] + var*pow(m_E_p1_MS[detRegion]*m_E_p1_MS[detRegion]+
					       m_S_p1_MS[detRegion]*m_S_p1_MS[detRegion],0.5);
      
      p2_MS_var = m_p2_MS[detRegion] + var*pow(m_E_p2_MS[detRegion]*m_E_p2_MS[detRegion]+
					       m_S_p2_MS[detRegion]*m_S_p2_MS[detRegion],0.5);
      
      if(p1_MS_var < 0. ) p1_MS_var = 0.; //Truncation of unphysical variations
      if(p2_MS_var < 0. ) p2_MS_var = 0.;
	    
      return (p1_MS_var*g1 + p2_MS_var*g2*ptms/GeV );
    }
  }
  else if(DetType==DET_ID){
    p1_ID_var = m_p1_ID[detRegion] + var*pow(m_E_p1_ID[detRegion]*m_E_p1_ID[detRegion]+
					     m_S_p1_ID[detRegion]*m_S_p1_ID[detRegion],0.5);
    if(p1_ID_var < 0. ) p1_ID_var = 0.; //Truncation of unphysical variations
    
    if (useTan2 && m_p2_ID_TAN[detRegion]!=0){      
      p2_ID_var = m_p2_ID_TAN[detRegion] + var*pow(m_E_p2_ID_TAN[detRegion]*m_E_p2_ID_TAN[detRegion]+
						   m_S_p2_ID_TAN[detRegion]*m_S_p2_ID_TAN[detRegion],0.5);
      if(p2_ID_var < 0. ) p2_ID_var = 0.;//Truncation of unphysical variations

      return ( p1_ID_var*g3 + p2_ID_var*g4*ptid/GeV*sinh(eta)*sinh(eta) );
    } else{      
      p2_ID_var = m_p2_ID[detRegion] + var*pow(m_E_p2_ID[detRegion]*m_E_p2_ID[detRegion]+
					       m_S_p2_ID[detRegion]*m_S_p2_ID[detRegion],0.5);
      if(p2_ID_var < 0. ) p2_ID_var = 0.;//Truncation of unphysical variations
      
      return ( p1_ID_var*g3 + p2_ID_var*g4*ptid/GeV );
    }
  }
  else{ 
    std::cerr<<__FILE__<<" line:"<<__LINE__<<" "<<"SmearingClass ERROR:: DetType not defined "<<DetType<<std::endl;
  }
  return 0;
}



double SmearingClass::ICombine(double inSmearMS, 
			       double inSmearID) {
  
  if(!useImprovedCombine) 
    return Combine(inSmearMS,inSmearID);
  else 
    return Combine2(inSmearMS,inSmearID);
  
}

double SmearingClass::ExpectedResolution(std::string DetType, bool mc) const {
  
  if(DetType=="MS"){ 
    return ExpectedResolution(DET_MS,mc);
  }
  else if(DetType=="ID"){
    return ExpectedResolution(DET_ID,mc);
  }
  else if(DetType=="CB"){
    return ExpectedResolution(DET_CB,mc);
  }
  else {
    std::cerr<<__FILE__<<" line:"<<__LINE__<<" "<<"SmearingClass ERROR: wrong DetType in input "<<DetType<<std::endl;
    return 0.;
  }

}

double SmearingClass::ExpectedResolution(int DetType, bool mc) const {
  
  /** do the average with the EXPECTED resolutions **/
  
  if (detRegion<0||detRegion>3) {
    return 0; 
  }
  if (ptcb==0) { 
    std::cout<<__FILE__<<" line:"<<__LINE__<<" "<<"SmearingClass WARNING:: ptcb==0"<<std::endl;
  }

  if (DetType == DET_MS) {
    // Calculate MC resolution
    double res2 = pow(m_MC_p0_MS[detRegion]/ptms*GeV,2) +
      pow(m_MC_p1_MS[detRegion],2) +
      pow(m_MC_p2_MS[detRegion]*ptms/GeV,2);
    if (!mc) {
      // Add data/MC smearing in quadrature
      res2 += pow(m_p1_MS[detRegion],2) +
	pow(m_p2_MS[detRegion]*ptms/GeV,2);
    }
    return pow(res2, 0.5);
  } 
  else if (DetType == DET_ID) {
    if (m_MC_p2_ID_TAN[detRegion]!=0 && useTan2) {
      double seta = sinh(eta);
      double res2 = pow(m_MC_p1_ID[detRegion],2)+
	pow(m_MC_p2_ID_TAN[detRegion]*ptid/GeV*seta*seta,2);
      if (!mc) {
	// Add data/MC smearing in quadrature
	res2 += pow(m_p1_ID[detRegion],2) +
	  pow(m_p2_ID_TAN[detRegion]*ptid/GeV*seta*seta,2);
      }
      return pow(res2, 0.5);
    } 
    else {
      double res2 = pow(m_MC_p1_ID[detRegion],2) +
	pow(m_MC_p2_ID[detRegion]*ptid/GeV,2);
      if (!mc) {
	// Add data/MC smearing in quadrature
	res2 += pow(m_p1_ID[detRegion],2)+
	  pow(m_p2_ID[detRegion]*ptid/GeV,2);
      }
      return pow(res2, 0.5);
    }
  } 
  else if (DetType == DET_CB) {
    
    // Due to complicated maths, the expected combined resolution
    // is given by this equation (note: all sigmas are fractional uncertainties):
    // sigma_CB = sqrt(2) * sigma_ID * sigma_MS * pTMS * pTID / {pTCB * sqrt({sigma_ID*pTID}^2 + {sigma_MS*pTMS}^2)}
    
    // Do a little recursive calling to make things easier to read
    // Turn these into *absolute* uncertainties to make life easier
    double sigmaID = ExpectedResolution(DET_ID, mc) * ptid/GeV;
    double sigmaMS = ExpectedResolution(DET_MS, mc) * ptms/GeV;
    
    double denominator = (ptcb/GeV) * std::sqrt(sigmaID*sigmaID + sigmaMS*sigmaMS);
    
    return denominator ? std::sqrt(2.) * sigmaID * sigmaMS / denominator : 0.;
  }
  else {
    std::cerr<<__FILE__<<" line:"<<__LINE__<<" "<<"SmearingClass ERROR: wrong DetType in input "<<DetType<<std::endl;
    return 0.;
  }
}
  
double SmearingClass::Combine(double SmearMS, 
			      double SmearID) {
  
  if (detRegion<0||detRegion>=m_nb_regions){
    return 0;
  }
  if (ptcb==0) { 
    std::cout<<__FILE__<<" line:"<<__LINE__<<" "<<"SmearingClass WARNING:: ptcb==0"<<std::endl;
    return 0; 
  }
  
  /*double SigmaMS=pow(					      
    pow(m_MC_p0_MS[detRegion]/ptcb*GeV,2)+     
    pow(m_MC_p1_MS[detRegion],2)+	      
    pow(m_MC_p2_MS[detRegion]*ptcb/GeV,2),0.5);*/
    
  double SigmaMS=pow(
		     pow(m_MC_p0_MS[detRegion]/ptms*GeV,2)+
		     pow(m_MC_p1_MS[detRegion],2)+
		     pow(m_MC_p2_MS[detRegion]*ptms/GeV,2),0.5);
  
  /*double SigmaID=pow(					      
    pow(m_MC_p1_ID[detRegion],2)+	      
    pow(m_MC_p2_ID[detRegion]*ptcb/GeV,2),0.5);*/
  
  double SigmaID=pow(					      
  		     pow(m_MC_p1_ID[detRegion],2)+	      
  		     pow(m_MC_p2_ID[detRegion]*ptid/GeV,2),0.5);
  
  if (m_MC_p2_ID_TAN[detRegion]!=0 && useTan2) {
    /*SigmaID=pow(
      pow(m_MC_p1_ID[detRegion],2)+
      pow(m_MC_p2_ID_TAN[detRegion]*ptcb/GeV*sinh(eta)*sinh(eta),2),0.5);*/
    
    SigmaID=pow(
    		pow(m_MC_p1_ID[detRegion],2)+
    		pow(m_MC_p2_ID_TAN[detRegion]*ptid/GeV*sinh(eta)*sinh(eta),2),0.5);
    
  }
  
  /*wMS=1./SigmaMS/SigmaMS;*/
  wMS=1./SigmaMS/SigmaMS/ptms/ptms;
  
  /*wID=1./SigmaID/SigmaID;*/
  wID=1./SigmaID/SigmaID/ptid/ptid;
  
  /*return (SmearMS*wMS+SmearID*wID)/(wMS+wID);*/
  return (SmearMS*wMS*ptms/ptcb+SmearID*wID*ptid/ptcb)/(wMS+wID);
}


double SmearingClass::Combine2(double SmearMS, 
			       double SmearID) {
  
  /** do the average with the EXPECTED resolutions **/
  
  if (detRegion<0 || detRegion>=m_nb_regions){
    return 0; 
  }
  if (ptcb==0) { 
    std::cout<<__FILE__<<" line:"<<__LINE__<<" "<<"SmearingClass WARNING:: ptcb==0"<<std::endl;
    return 0; 
  }
  
  double SmearCB=0;
  
  double SigmaMS=pow(
		     pow(m_MC_p0_MS[detRegion]/ptcb*GeV,2)+
		     pow(m_MC_p1_MS[detRegion],2)+
		     pow(m_MC_p2_MS[detRegion]*ptcb/GeV,2),0.5);
  
  double SigmaID=pow(
		     pow(m_MC_p1_ID[detRegion],2)+
		     pow(m_MC_p2_ID[detRegion]*ptcb/GeV,2),0.5);
  
  if(m_MC_p2_ID_TAN[detRegion]!=0 && useTan2) {
    SigmaID=pow(
		pow(m_MC_p1_ID[detRegion],2)+
		pow(m_MC_p2_ID_TAN[detRegion]*ptcb/GeV*sinh(eta)*sinh(eta),2),0.5);
  }
  
  double Nsigma=4;
  if (fabs(ptcb-ptms)<Nsigma*SigmaMS*ptcb&&
      fabs(ptcb-ptid)<Nsigma*SigmaID*ptcb) {
    SmearCB=Combine(SmearMS,SmearID);
    return SmearCB;
  }
  
  double R=1;
  
  if (fabs(ptcb-ptms)!=0&&fabs(ptcb-ptms)>fabs(ptcb-ptid)) {
    R=(ptid-ptcb)/(ptcb-ptms); /* R~wMS/wID */
    double rplus=1+R;
    if (rplus!=0 && R>0) SmearCB=(SmearID+R*SmearMS)/rplus;    
    else SmearCB=Combine(SmearMS,SmearID);
  }
  else if (fabs(ptcb-ptid)!=0&&fabs(ptcb-ptms)<fabs(ptcb-ptid)){
    R=(ptms-ptcb)/(ptcb-ptid); /* R~wID/wMS */
    double rplus=1+R;
    if (rplus!=0 && R>0) SmearCB=(SmearMS+R*SmearID)/rplus;    
    else SmearCB=Combine(SmearMS,SmearID);
  } else {
    SmearCB=Combine(SmearMS,SmearID);
  }
  
  return SmearCB;
}


void SmearingClass::ErrorMatrix() {
  
  vms=0;
  vid=0;
  corr=0;
  double s1=0, s2=0, s3=0, s4=0;
  if (detRegion<0 || detRegion>=m_nb_regions) 
    return;

  // tan2 parametrization only applies in CSC region
  if (!useTan2 || m_E_p2_ID_TAN[detRegion]==0) {
    if(ptms==0){
      vms=0;
    } else{
      s1 = pow(m_E_p1_MS[detRegion]*m_E_p1_MS[detRegion]+
	       m_S_p1_MS[detRegion]*m_S_p1_MS[detRegion],0.5);
      
      s2 = pow(m_E_p2_MS[detRegion]*m_E_p2_MS[detRegion]+
	       m_S_p2_MS[detRegion]*m_S_p2_MS[detRegion],0.5);
      
      vms = g1*g1*s1*s1+
	g2*g2*s2*s2*ptms/GeV*ptms/GeV+
	2.0*g1*g2*ptms/GeV*s1*s2*m_CorrMatC0[detRegion];
      
      vms = pow(fabs(vms),0.5);
    }
    
    s3 = pow(m_E_p1_ID[detRegion]*m_E_p1_ID[detRegion]+
	     m_S_p1_ID[detRegion]*m_S_p1_ID[detRegion],0.5);
    
    s4 = pow(m_E_p2_ID[detRegion]*m_E_p2_ID[detRegion]+
	     m_S_p2_ID[detRegion]*m_S_p2_ID[detRegion],0.5);
    
    vid = g3*g3*s3*s3+g4*g4*s4*s4*ptid/GeV*ptid/GeV+
      2.0*g3*g4*s3*s4*ptid/GeV*m_CorrMatC5[detRegion];
    
    vid = pow(fabs(vid),0.5);
    
    if (vms*vid!=0) {
      corr = (g1*s1*(g3*s3*m_CorrMatC1[detRegion]+
		     g4*s4*ptid/GeV*m_CorrMatC2[detRegion])+
	      g2*s2*ptms/GeV*(g3*s3*m_CorrMatC3[detRegion]+
			      g4*s4*ptid/GeV*m_CorrMatC4[detRegion]))/vms/vid;
    }
  } else {
    if(ptms==0){
      vms=0;
    } else{
      s1 = pow(m_E_p1_MS[detRegion]*m_E_p1_MS[detRegion]+
	       m_S_p1_MS[detRegion]*m_S_p1_MS[detRegion],0.5);
      
      s2 = pow(m_E_p2_MS[detRegion]*m_E_p2_MS[detRegion]+
	       m_S_p2_MS[detRegion]*m_S_p2_MS[detRegion],0.5);
      
      vms = g1*g1*s1*s1+
	g2*g2*s2*s2*ptms/GeV*ptms/GeV+
	2.0*g1*g2*ptms/GeV*s1*s2*m_CorrMatTanC0[detRegion];
      
      vms = pow(fabs(vms),0.5);
    }
    
    s3 = pow(m_E_p1_ID[detRegion]*m_E_p1_ID[detRegion]+
	     m_S_p1_ID[detRegion]*m_S_p1_ID[detRegion],0.5);
    
    s4 = pow(m_E_p2_ID_TAN[detRegion]*m_E_p2_ID_TAN[detRegion]+
	     m_S_p2_ID_TAN[detRegion]*m_S_p2_ID_TAN[detRegion],0.5);
    
    vid = g3*g3*s3*s3+g4*g4*s4*s4*ptid/GeV*ptid/GeV*sinh(eta)*sinh(eta)*sinh(eta)*sinh(eta)
      +2.0*g3*g4*s3*s4*ptid/GeV*sinh(eta)*sinh(eta)*m_CorrMatTanC5[detRegion];
    
    vid = pow(fabs(vid),0.5);
    
    if (vms*vid!=0) {
      corr = (g1*s1*(g3*s3*m_CorrMatTanC1[detRegion]+g4*s4*ptid/GeV*sinh(eta)*sinh(eta)*m_CorrMatTanC2[detRegion])+
	      g2*s2*ptms/GeV*(g3*s3*m_CorrMatTanC3[detRegion]+g4*s4*ptid/GeV*sinh(eta)*sinh(eta)*m_CorrMatTanC4[detRegion]))/vms/vid;
    }
  }
}


double SmearingClass::pTMS() {
  
  /* smeared muon spectrometer pT */
  return pTMS(smearDeltaMS);
}


double SmearingClass::pTMS(double SmearMS, bool doScale) {
  
  /* smeared muon spectrometer pT */
  if(Tsmear==SMEAR_PT){
    return doScale ? ScaleMS(ptms*(1+SmearMS)) : ptms*(1+SmearMS); 
  }
  else if(Tsmear==SMEAR_QPT){
    double tmp=1-SmearMS;
    if(tmp!=0) 
      return doScale ? ScaleMS(fabs(ptms/tmp)) : fabs(ptms/tmp); 
    else 
      return m_pTmax;
  }
  return ptms;
}


double SmearingClass::pTID() {
  /* smeared inner detector pT */
  
  return pTID(smearDeltaID);
}


double SmearingClass::pTID(double SmearID, bool doScale) {
  
  /* smeared inner detector pT */
  if(Tsmear==SMEAR_PT){
    return doScale ? ScaleID(ptid*(1+SmearID)) : ptid*(1+SmearID);
  }
  else if(Tsmear==SMEAR_QPT){
    double tmp=1-SmearID;
    if(tmp!=0) return doScale ? ScaleID(fabs(ptid/tmp)) : fabs(ptid/tmp);
    else return m_pTmax;
  }
  return ptid;
}


double SmearingClass::pTCB() {
  
  /* smeared combined pT*/
  
  return pTCB(smearDeltaCB);
}


double SmearingClass::pTCB(double SmearCB, bool doScale) {
  
  /* smeared combined pT*/
  if(Tsmear==SMEAR_PT){
    return doScale ? ScaleCB(ptcb*(1+SmearCB)) : ptcb*(1+SmearCB);
  }
  else if(Tsmear==SMEAR_QPT){
    double tmp=1-SmearCB;
    if(tmp!=0) return doScale ? ScaleCB(fabs(ptcb/tmp)) : fabs(ptcb/tmp);
    else return m_pTmax;
  }
  return ScaleCB(ptcb);
}


double SmearingClass::ScaleMS(double pt) const{
  
  /* scale/curvature correction for MS tracks*/
  double scaleMS = 0;
  if(m_scale_MS[detRegion]!=-1){
    scaleMS = (detRegion<0 || detRegion>=m_nb_regions) ? 1.0 : m_scale_MS[detRegion];
  }
  else{
    scaleMS = 1;
  }
  
  return m_scaleBins.empty() ? ScaleApply(pt,0,0,scaleMS) : ScaleApply(pt,m_S1_MS[scaleRegion],m_S2_MS[scaleRegion],scaleMS);

}


double SmearingClass::ScaleID(double pt) const{
  
  /* scale/curvature correction for ID tracks*/
  double scaleID = 0;
  if(m_scale_ID[detRegion]!=-1){
    scaleID = (detRegion<0 || detRegion>=m_nb_regions) ? 1.0 : m_scale_ID[detRegion];
  }
  else{
    scaleID = 1;
  }
  
  return m_scaleBins.empty() ? ScaleApply(pt,0,0,scaleID) : ScaleApply(pt,m_S1_ID[scaleRegion],m_S2_ID[scaleRegion],scaleID);
}


double SmearingClass::ScaleCB(double pt) const{
  
  /* scale/curvature correction for CB tracks*/
  
  double scaleCB = 0;
  if(m_scale_CB[detRegion]!=-1){
    scaleCB = (detRegion<0 || detRegion>=m_nb_regions) ? 1.0 : m_scale_CB[detRegion];
  } else{
    if(pt==0){
      scaleCB=0;
    } else{
      double sigma_ID2 = (pow(m_MC_p1_ID[detRegion],2)+
			  pow(m_MC_p2_ID[detRegion]*pt/GeV,2));
      
      double sigma_MS2 = (pow(m_MC_p0_MS[detRegion]/pt*GeV,2) +
			  pow(m_MC_p1_MS[detRegion],2) +
			  pow(m_MC_p2_MS[detRegion]*pt/GeV,2));
      
      scaleCB=( (m_scale_ID[detRegion]/sigma_ID2+
		 m_scale_MS[detRegion]/sigma_MS2)/
		(1.0/sigma_ID2+1.0/sigma_MS2));
    }
  }
  
  if(m_ScaleType!=""){
    if(unsigned(scaleRegion)>=m_S1_CB.size() || unsigned(scaleRegion)>=m_S2_CB.size()){
      std::cerr<<__FILE__<<" line:"<<__LINE__<<" "<<"SmearingClass ERROR:: "<<scaleRegion<<" length of scaleRegion1: "<<m_S1_CB.size()<<std::endl;
      std::cerr<<__FILE__<<" line:"<<__LINE__<<" "<<"SmearingClass ERROR:: "<<scaleRegion<<" length of scaleRegion2: "<<m_S2_CB.size()<<std::endl;
      return -1;
    }
  }
  
  return m_scaleBins.empty() ? ScaleApply(pt,0,0,scaleCB) : ScaleApply(pt,m_S1_CB[scaleRegion],m_S2_CB[scaleRegion],scaleCB);
}


double SmearingClass::ScaleApply(double pt, double S1, double S2, double S) const{
  /* general-purpose function to apply scale/curvature corrections */

  if(!useScale) return pt;
  // default momentum scale (using Oliver's original values)
  if(Tscale==SCALE_DEFAULT) {
    return apply_to_data ? pt/S : pt*S;
  }
  // charge-dependent scales: kp,km == pt(data)/pt(mc)
  if(Tscale==SCALE_KPKM) {
    if(charge==0) {
      std::cerr<<__FILE__<<" line:"<<__LINE__<<" "<<"ERROR: must provide muon charge via Event() to use advanced pT scaling" << std::endl;
      return pt;
    }
    const double kpkm = (charge>0 ? S1 : S2)/100.0;
    return apply_to_data ? pt/kpkm : pt*kpkm;
  }
  // overall scale: K == pt(data)/pt(mc) and curvature split: 2*C == 1/pt+ - 1/pt-
  // both corrections can be applied one after another or one at a time
  if(Tscale>=SCALE_KC) {
    if(charge==0) {
      std::cerr<<__FILE__<<" line:"<<__LINE__<<" "<<"ERROR: must provide muon charge via Event() to use advanced pT scaling" << std::endl;
      return pt;
    }
    const double K = S1/100.0;
    const double C = S2/GeV/1e6;
    // scale pt (unless only curvature splitting is requested)
    const double ptsc = (Tscale==SCALE_C) ? pt : (apply_to_data ? pt/K : pt*K);
    // calculate curvature and apply a correction, if needed:
    double curv=1/ptsc;
    if(Tscale!=SCALE_K) {
      // if correcting a curvature offset in data:
      if(apply_to_data) curv += charge<0 ? C  : -C;
      // if putting a curvature offset into MC to better match the data
      else curv += charge<0 ? -C  : +C;
    }
    return curv==0 ? m_pTmax : fabs(1.0/curv);
  }
  return pt;
}


double SmearingClass::ChargeFlip(double Smear){
  
  if(Tsmear==SMEAR_PT){
    return 1;
  }
  else if (Tsmear==SMEAR_QPT){
    return Sign(1-Smear);
  }
  return 1;
}


double SmearingClass::ChargeFlipMS(){
  
  return ChargeFlip(smearDeltaMS);
}


double SmearingClass::ChargeFlipID(){
  
  return ChargeFlip(smearDeltaID);
}


double SmearingClass::ChargeFlipCB(){
  
  return ChargeFlip(smearDeltaCB);
}


double SmearingClass::SMS() {
  return smearDeltaMS;
}


double SmearingClass::SID() {
  return smearDeltaID;
}


double SmearingClass::SCB() {
  return smearDeltaCB;
}


double SmearingClass::VMS() {
  /* error smearDeltaMS */
  
  return vms;  
}


double SmearingClass::VID() {
  /* error smearDeltaID */
  
  return vid;
}


double SmearingClass::Corr() {
  /* correlation between smearDeltaMS and smearDeltaID */
  
  return corr;
}


void SmearingClass::MSUP(double &PtMS, bool useErrMatrix){
  double varSmearMS = 0.;
  if(useErrMatrix){
    varSmearMS = smearDeltaMS + Sign(smearDeltaMS)*vms;
  } else {
    varSmearMS =  SmearingSYSVar(DET_MS, 1.);
  }

  PtMS=pTMS(varSmearMS);
}


void SmearingClass::MSUP(double &PtMS,
			 double &PtID,
			 double &PtCB, bool useErrMatrix) {
  double varSmearMS = 0.;    
  double varSmearID = 0.;
  if(useErrMatrix){
    varSmearMS = smearDeltaMS + Sign(smearDeltaMS)* vms;
    varSmearID = smearDeltaID + Sign(smearDeltaID)* vid*corr;
  } else {
    varSmearMS =  SmearingSYSVar(DET_MS, 1.);
    varSmearID = smearDeltaID; //No correlation!! ++++++++TODO
  } 
  
  
  PtMS=pTMS(varSmearMS);
  PtID=pTID(varSmearID);
  if(Tdet==DET_CB){
    double varSmearCB=ICombine(varSmearMS,varSmearID);
    PtCB=pTCB(varSmearCB);
  }
}


void SmearingClass::MSLOW(double &PtMS, bool useErrMatrix) {
  double varSmearMS = 0.;
  if(useErrMatrix){
    varSmearMS = smearDeltaMS - Sign(smearDeltaMS)*vms;
  } else {
    varSmearMS =  SmearingSYSVar(DET_MS, -1.);
  }

  PtMS=pTMS(varSmearMS);
}


void SmearingClass::MSLOW(double &PtMS,
			  double &PtID,
			  double &PtCB, bool useErrMatrix) {
  double varSmearMS = 0.;    
  double varSmearID = 0.;
  if(useErrMatrix){
    varSmearMS = smearDeltaMS - Sign(smearDeltaMS)* vms;
    varSmearID = smearDeltaID - Sign(smearDeltaID)* vid*corr;
  } else {
    varSmearMS =  SmearingSYSVar(DET_MS, -1.);
    varSmearID = smearDeltaID; //No correlation!! ++++++++TODO
  } 

  PtMS=pTMS(varSmearMS);
  PtID=pTID(varSmearID);
  if(Tdet==DET_CB){
    double varSmearCB=ICombine(varSmearMS,varSmearID);
    PtCB=pTCB(varSmearCB);
  }
}


void SmearingClass::IDUP(double &PtID, bool useErrMatrix) {
  double varSmearID = 0.;
  if(useErrMatrix){
    varSmearID = smearDeltaID + Sign(smearDeltaID)*vid;
  } else {
    varSmearID =  SmearingSYSVar(DET_ID, 1.);
  }
  
  PtID=pTID(varSmearID);
}


void SmearingClass::IDUP(double &PtMS,
			 double &PtID,
			 double &PtCB, bool useErrMatrix) {
  double varSmearMS = 0.;    
  double varSmearID = 0.;
  if(useErrMatrix){
    varSmearMS = smearDeltaMS + Sign(smearDeltaMS)* vms*corr;
    varSmearID = smearDeltaID + Sign(smearDeltaID)* vid;
  } else {
    varSmearMS = smearDeltaMS; //No correlation!! ++++++++TODO
    varSmearID = SmearingSYSVar(DET_ID, 1.);
  } 
  
  PtMS=pTMS(varSmearMS);
  PtID=pTID(varSmearID);
  if(Tdet==DET_CB){
    double varSmearCB=ICombine(varSmearMS,varSmearID);
    PtCB=pTCB(varSmearCB);
  }
}


void SmearingClass::IDLOW(double &PtID, bool useErrMatrix) {
  double varSmearID = 0.;
  if(useErrMatrix){
    varSmearID = smearDeltaID - Sign(smearDeltaID)*vid;
  } else {
    varSmearID =  SmearingSYSVar(DET_ID, -1.);
  }

  PtID=pTID(varSmearID);
}


void SmearingClass::IDLOW(double &PtMS,
			  double &PtID,
			  double &PtCB, bool useErrMatrix) {
  double varSmearMS = 0.;    
  double varSmearID = 0.;
  if(useErrMatrix){
    varSmearMS = smearDeltaMS - Sign(smearDeltaMS)* vms*corr;
    varSmearID = smearDeltaID - Sign(smearDeltaID)* vid;
  } else {
    varSmearMS = smearDeltaMS; //No correlation!! ++++++++TODO
    varSmearID = SmearingSYSVar(DET_ID, -1.);
  } 

  PtMS=pTMS(varSmearMS);
  PtID=pTID(varSmearID);
  if(Tdet==DET_CB){
    double varSmearCB=ICombine(varSmearMS,varSmearID);
    PtCB=pTCB(varSmearCB);
  }
}


SYSTTYPE SmearingClass::SelectFun(std::string fun){
  
  if(fun=="IDUP") { Tfun=ID_UP;}
  else if(fun=="IDLOW") { Tfun=ID_LOW; }
  else if(fun=="MSUP") { Tfun=MS_UP; }
  else if(fun=="MSLOW") { Tfun=MS_LOW; }
  else if(fun=="SCALEUP") { Tfun=SCALE_UP; }
  else if(fun=="SCALELOW") { Tfun=SCALE_LOW; }
  return Tfun;
}

DATATYPE SmearingClass::SetData(std::string data){
  
  if(data=="Data10") { Tdata=DATA10; }
  else if(data=="Data11"){ Tdata=DATA11; }
  else if(data=="Data12"){ Tdata=DATA12; }
  return Tdata;
}

ALGOTYPE SmearingClass::SetAlgorithm(std::string algo){
  
  if(algo=="muid"){ Talgo=MUID; }
  else if(algo=="staco"){ Talgo=STACO; }
  else if(algo=="muons"){ Talgo=MUONS; }
  return Talgo;
}

RELTYPE SmearingClass::SetRelease(std::string rel){
  
  if(rel=="Rel16.6"){ Trel=REL16_6; }
  else if(rel=="Rel17"){ Trel=REL17; }
  else if(rel=="Rel17.2"){ Trel=REL17_2; }
  else if(rel=="Rel17.2Repro"){ Trel=REL17_2_REPRO; }
  return Trel;
}


void SmearingClass::PTVar(double &Pt,
			  std::string fun) {

  Tfun=SelectFun(fun);
  
  if (Tfun==ID_UP) { IDUP(Pt); }
  else if (Tfun==ID_LOW) { IDLOW(Pt); }
  else if (Tfun==MS_UP) { MSUP(Pt); }
  else if (Tfun==MS_LOW) { MSLOW(Pt); }
}


void SmearingClass::PTVar(double &PtMS,
			  double &PtID,
			  double &PtCB,
			  std::string fun) {
  
  Tfun=SelectFun(fun);
  
  if (Tfun==ID_UP) {
    if(Tdet==DET_CB){ IDUP(PtMS,PtID,PtCB); return; }
    else if(Tdet==DET_ID){ IDUP(PtID); return; }

  } else if (Tfun==ID_LOW) { 
    if(Tdet==DET_CB){ IDLOW(PtMS,PtID,PtCB); return; }
    else if(Tdet==DET_ID){ IDLOW(PtID); return; }

  } else if (Tfun==MS_UP) { 
    if(Tdet==DET_CB){ MSUP(PtMS,PtID,PtCB); return; }
    else if(Tdet==DET_MS){ MSUP(PtMS); return; }

  } else if (Tfun==MS_LOW) { 
    if(Tdet==DET_CB){ MSLOW(PtMS,PtID,PtCB); return; }
    else if(Tdet==DET_MS){ MSLOW(PtMS); return; }

  } else if (Tfun==SCALE_UP || Tfun==SCALE_LOW) {
    const double s = (Tfun==SCALE_UP) ? 1.0 : -1.0;

    if(Tscale==SCALE_DEFAULT) {

      if(Tdet==DET_ID || Tdet==DET_CB){
	PtID = ScaleApply(pTID(smearDeltaID,0), 0., 0., m_scale_ID[detRegion] + s*m_scaleSyst_ID[detRegion]);
      } 
      if(Tdet==DET_MS || Tdet==DET_CB){
	PtMS = ScaleApply(pTMS(smearDeltaMS,0), 0., 0., m_scale_MS[detRegion] + s*m_scaleSyst_MS[detRegion]);
      }

      if(Tdet==DET_CB){
	const double scaleSys_CB_toUse = (m_scaleSyst_CB[detRegion] == -1) ? 0 : s*m_scaleSyst_CB[detRegion];
	//If default values are in for the CB, then use them as in the ID and MS case
	if(m_scale_CB[detRegion] != -1){ 
	  const double SCB = m_scale_CB[detRegion] + scaleSys_CB_toUse;
	  PtCB = ScaleApply(pTCB(smearDeltaCB,0), 0., 0., SCB);
	} else {
	  //Otherwise go for the variation depending on the ID and MS and recompute the combination, In case an additional
	  //error is available for CB only, use also that
	  const double newSmearID = (PtID - ptid)/ptid;
	  const double newSmearMS = (PtMS - ptms)/ptms;
	  smearDeltaCB=ICombine(newSmearMS,newSmearID);
	  PtCB = ScaleApply(pTCB(smearDeltaCB,0), 0., 0., 1. + scaleSys_CB_toUse);
	}
      }

      return;
    }
    else if(Tscale==SCALE_KC || Tscale==SCALE_K) {
      // here, we scale up or down the overall pT scale
      PtMS = ScaleApply(pTMS(smearDeltaMS,0),m_S1_MS[scaleRegion] + s*m_S1Corr_MS[scaleRegion],m_S2_MS[scaleRegion]);
      PtID = ScaleApply(pTID(smearDeltaID,0),m_S1_ID[scaleRegion] + s*m_S1Corr_ID[scaleRegion],m_S2_ID[scaleRegion]);
      PtCB = ScaleApply(pTCB(smearDeltaCB,0),m_S1_CB[scaleRegion] + s*m_S1Corr_CB[scaleRegion],m_S2_CB[scaleRegion]);
      return;
    }    
    else if(Tscale==SCALE_KPKM) {
      // here, we scale up or down the component of kp/km error from Z mass fit
      PtMS = ScaleApply(pTMS(smearDeltaMS,0),m_S1_MS[scaleRegion] + s*m_S1Corr_MS[scaleRegion],m_S2_MS[scaleRegion] - s*m_S2Corr_MS[scaleRegion]);
      PtID = ScaleApply(pTID(smearDeltaID,0),m_S1_ID[scaleRegion] + s*m_S1Corr_ID[scaleRegion],m_S2_ID[scaleRegion] - s*m_S2Corr_ID[scaleRegion]);
      PtCB = ScaleApply(pTCB(smearDeltaCB,0),m_S1_CB[scaleRegion] + s*m_S1Corr_CB[scaleRegion],m_S2_CB[scaleRegion] - s*m_S2Corr_CB[scaleRegion]);
      return;
    }    
    else if(Tscale==SCALE_KC || Tscale==SCALE_K) {
      // here, we scale up or down the curvature offset
      PtMS = ScaleApply(pTMS(smearDeltaMS,0),m_S1_MS[scaleRegion],m_S2_MS[scaleRegion] + s*m_S2Corr_MS[scaleRegion]);
      PtID = ScaleApply(pTID(smearDeltaID,0),m_S1_ID[scaleRegion],m_S2_ID[scaleRegion] + s*m_S2Corr_ID[scaleRegion]);
      PtCB = ScaleApply(pTCB(smearDeltaCB,0),m_S1_CB[scaleRegion],m_S2_CB[scaleRegion] + s*m_S2Corr_CB[scaleRegion]);
      return;
    }
    else if(Tscale==SCALE_KPKM) {
      // here, we scale up or down the component of kp/km error from R0 fit
      PtMS = ScaleApply(pTMS(smearDeltaMS,0),m_S1_MS[scaleRegion] + s*m_S1ACorr_MS[scaleRegion],m_S2_MS[scaleRegion] + s*m_S2ACorr_MS[scaleRegion]);
      PtID = ScaleApply(pTID(smearDeltaID,0),m_S1_ID[scaleRegion] + s*m_S1ACorr_ID[scaleRegion],m_S2_ID[scaleRegion] + s*m_S2ACorr_ID[scaleRegion]);
      PtCB = ScaleApply(pTCB(smearDeltaCB,0),m_S1_CB[scaleRegion] + s*m_S1ACorr_CB[scaleRegion],m_S2_CB[scaleRegion] + s*m_S2ACorr_CB[scaleRegion]);
      return;
    } else {
      // do nothing if SCALECUP and SCALECLOW don't apply
      return;
    }
  }//if (Tfun==ID_UP) { IDUP(PtMS,PtID,PtCB); return; } 
}


double SmearingClass::Sign(double x){
  
  return (x<0? -1 : 1);
}


double SmearingClass::ptms_orig() {
  return ptms;
}


double SmearingClass::ptid_orig() {
  return ptid;
}


double SmearingClass::ptcb_orig() {
  return ptcb;
}


double SmearingClass::ETA() {
  return eta;
}


int SmearingClass::DetRegion() {
  return detRegion;
}


std::vector<double> SmearingClass::getScale_ID() {
  return m_scale_ID;
}


std::vector<double> SmearingClass::getScaleSyst_ID(){
  return m_scaleSyst_ID;
}


std::vector<double> SmearingClass::getScale_MS() {
  return m_scale_MS;
}


std::vector<double> SmearingClass::getScaleSyst_MS(){
  return m_scaleSyst_MS;
}


std::vector<double> SmearingClass::getScale_CB() {
  return m_scale_CB;
}


std::vector<double> SmearingClass::getScaleSyst_CB(){
  return m_scaleSyst_CB;
}


std::vector<double> SmearingClass::getp1_ID(){
  return m_p1_ID;
}


std::vector<double> SmearingClass::getp2_ID(){
  return m_p2_ID;
}


std::vector<double> SmearingClass::getp2_ID_TAN(){
  return m_p2_ID_TAN;
}


std::vector<double> SmearingClass::getp1_MS(){
  return m_p1_MS;
}


std::vector<double> SmearingClass::getp2_MS(){ 
  return m_p2_MS;
}


std::vector<double> SmearingClass::getE_p1_ID(){ 
  return m_E_p1_ID;
}


std::vector<double> SmearingClass::getE_p2_ID(){ 
  return m_E_p2_ID;
}


std::vector<double> SmearingClass::getE_p2_ID_TAN(){ 
  return m_E_p2_ID_TAN;
}


std::vector<double> SmearingClass::getE_p1_MS(){ 
  return m_E_p1_MS;
}


std::vector<double> SmearingClass::getE_p2_MS(){ 
  return m_E_p2_MS;
}


std::vector<double> SmearingClass::getS_p1_ID(){ 
  return m_S_p1_ID;
}


std::vector<double> SmearingClass::getS_p2_ID(){ 
  return m_S_p2_ID;
}


std::vector<double> SmearingClass::getS_p2_ID_TAN(){ 
  return m_S_p2_ID_TAN;
}


std::vector<double> SmearingClass::getS_p1_MS(){ 
  return m_S_p1_MS;
}


std::vector<double> SmearingClass::getS_p2_MS(){ 
  return m_S_p2_MS;
}


std::vector<double> SmearingClass::getMC_p1_ID(){ 
  return m_MC_p1_ID;
}


std::vector<double> SmearingClass::getMC_p2_ID(){ 
  return m_MC_p2_ID;
}


std::vector<double> SmearingClass::getMC_p2_ID_TAN(){ 
  return m_MC_p2_ID_TAN;
}


std::vector<double> SmearingClass::getMC_p0_MS(){ 
  return m_MC_p0_MS;
}


std::vector<double> SmearingClass::getMC_p1_MS(){ 
  return m_MC_p1_MS;
}


std::vector<double> SmearingClass::getMC_p2_MS(){ 
  return m_MC_p2_MS;
}

std::vector<double> SmearingClass::getCorrMatC0(){ 
  return m_CorrMatC0;
}


std::vector<double> SmearingClass::getCorrMatC1(){ 
  return m_CorrMatC1; 
}


std::vector<double> SmearingClass::getCorrMatC2(){ 
  return m_CorrMatC2;
}


std::vector<double> SmearingClass::getCorrMatC3(){
  return m_CorrMatC3;
}


std::vector<double> SmearingClass::getCorrMatC4(){
  return m_CorrMatC4;
}


std::vector<double> SmearingClass::getCorrMatC5(){
  return m_CorrMatC5;
}


std::vector<double> SmearingClass::getCorrMatTanC0(){
  return m_CorrMatTanC0;
}


std::vector<double> SmearingClass::getCorrMatTanC1(){
  return m_CorrMatTanC1;
}


std::vector<double> SmearingClass::getCorrMatTanC2(){
  return m_CorrMatTanC2;
}


std::vector<double> SmearingClass::getCorrMatTanC3(){
 return m_CorrMatTanC3;
}


std::vector<double> SmearingClass::getCorrMatTanC4(){
  return m_CorrMatTanC4;
}


std::vector<double> SmearingClass::getCorrMatTanC5(){ 
  return m_CorrMatTanC5;
}

int SmearingClass::getRegion(double eta,double phi){
  
  for(UInt_t k=0; k<m_nb_regions; ++k){
    
    if( eta>=m_eta_min[k] && eta<m_eta_max[k] &&
	phi>=m_phi_min[k] && phi<m_phi_max[k] ){
      return k;
    }
  }
  
  return -1;
}

int SmearingClass::getRegionOld(double eta){
  
  if (fabs(eta)<1.05) { return 0; }
  else if (fabs(eta)<1.7) { return 1; }
  else if (fabs(eta)<2.0) { return 2; }
  else if (fabs(eta)<2.7) { return 3; }
  else { return -1; }
  
}

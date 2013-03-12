//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 31.10.2011, MCP working group
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//////////////////
// HEADER FILES //
//////////////////

#include <fstream>
#include <iostream>
#include <string>
#include "MuonEfficiencyCorrections/AnalysisMuonConfigurableScaleFactors.h"
#include "TRandom3.h"
#include "TObjArray.h"
#include "TObjString.h"

using namespace std;

//*****************************************************************************

/////////////////////////
// DEFAULT CONSTRUCTOR //
/////////////////////////

Analysis::AnalysisMuonConfigurableScaleFactors::AnalysisMuonConfigurableScaleFactors(void) {

  m_region.push_back(std::vector<int>());
  m_eta_min.push_back(std::vector<double>());  
  m_eta_max.push_back(std::vector<double>());
  m_phi_min.push_back(std::vector<double>());
  m_phi_max.push_back(std::vector<double>());
  m_pt_min.push_back(std::vector<double>());
  m_pt_max.push_back(std::vector<double>());
  m_charge.push_back(std::vector<int>());  
  m_sf.push_back(std::vector<double>());
  m_sf_stat_err.push_back(std::vector<double>());
  m_sf_syst_err.push_back(std::vector<double>());
  m_effdata.push_back(std::vector<double>());
  m_effdata_stat_err.push_back(std::vector<double>());
  m_effdata_syst_err.push_back(std::vector<double>());


  m_region[0].push_back(100);
  m_phi_min[0].push_back(-4);
  m_phi_max[0].push_back(4);
  m_eta_min[0].push_back(-4);
  m_eta_max[0].push_back(4);
  m_charge[0].push_back(0);
  m_sf[0].push_back(1.);
  m_sf_stat_err[0].push_back(0.);
  m_sf_syst_err[0].push_back(0.);
  m_effdata[0].push_back(1.);
  m_effdata_stat_err[0].push_back(0.);
  m_effdata_syst_err[0].push_back(0.);

  m_configuration=Default;
  m_unit= 0.001;

  m_run_min=-1000000;
  m_run_max=1000000;

  m_EnergyDependentSystematic=0.;
  m_usingDefaultLumi=true;
  m_UseChargeDependentSF=false;
  m_FileWithEffi=false;
}



//*****************************************************************************

/////////////////
// CONSTRUCTOR //
/////////////////


Analysis::AnalysisMuonConfigurableScaleFactors::AnalysisMuonConfigurableScaleFactors(
										     std::string directory,
										     std::string file,
										     const std::string & unit,	     
										     Configuration conf
									     )
{
  this->init(directory,file,unit,conf);
}

//*****************************************************************************

////////////////////////
// Pseudo CONSTRUCTOR //
////////////////////////

void Analysis::AnalysisMuonConfigurableScaleFactors::init(
							  std::string directory,
							  std::string file,
							  const std::string & unit,				      
							  Configuration conf
						      )
{
  /////////////////
  // CHECK INPUT //
  /////////////////

  m_run_min=-1000000;
  m_run_max=1000000;
  m_EnergyDependentSystematic=0.;
  m_usingDefaultLumi=true;
  m_UseChargeDependentSF=false;
  m_configuration=conf;

  if(m_configuration!=Default && m_configuration !=PerPeriod && m_configuration!=PerRun && m_configuration !=AverageOverPeriods && m_configuration !=AverageOverRuns )
    {
      cerr<<conf<<" not valid!"<<endl;
      cerr << "Class AnalysisMuonConfigurableScaleFactors, constructor: ERROR!"
	 << endl
	 << "Unsupported configuration "<< conf<<", must be : Default, PerPeriod, PerRun, AverageOverPeriods, AverageOverRuns"<<endl;
      exit(1);
    }

  if (unit=="MeV") 
    {
      m_unit = 0.001;
    }
  if(unit=="GeV") 
    {
      m_unit = 1;
    }
  if (unit!="MeV" && unit!="GeV") {
    cerr << "Class AnalysisMuonConfigurableScaleFactors, constructor: ERROR!"
	 << endl
	 << "Unsupported unit " << unit <<"!\n"
             << "Allowed units are MeV and GeV.\n";
    exit(1);
  }

  //now setting the correct path for the file
  if (directory == "") {
    char *m_tmparea=getenv("TestArea");
    if (m_tmparea != NULL) {
      directory =  string(m_tmparea)+"/InstallArea/share/";
      std::cout<< "AnalysisMuonEfficiencyScaleFactors: Using default dir: "<<directory <<endl;
    }
  }
  else {
    std::cout<<"AnalysisMuonEfficiencyScaleFactors:: Using user defined path!"<<std::endl;
    std::cout<<"                     "<<directory<<std::endl;
  }

  std::string file_path=directory+file;

///////////////
// VARIABLES //
///////////////


///////////////////////////////////
// READ SCALE FACTORS FROM FILES //
///////////////////////////////////

    vector<vector<int> >    region_muon;
    vector<vector<double> >  eta_min_muon;
    vector<vector<double> >  eta_max_muon;
    vector<vector<double> >  phi_min_muon;
    vector<vector<double> >  phi_max_muon;
    vector<vector<double> >  pt_min_muon;
    vector<vector<double> >  pt_max_muon;
    vector<vector<int> >    charge_muon;
    vector<vector<double> >  sf_muon;
    vector<vector<double> >  sf_stat_err_muon;
    vector<vector<double> > sf_syst_err_muon;
    vector<vector<double> >  effdata_muon;
    vector<vector<double> >  effdata_stat_err_muon;
    vector<vector<double> > effdata_syst_err_muon;
    std::vector<TString> period; //
    std::vector<int> run; //
    std::map<TString, double> period_lumi;
    std::map<int, double> run_lumi;


    read_file(
	      m_configuration,
	      file_path, 
	      region_muon,
	      eta_min_muon, 
	      eta_max_muon,
	      phi_min_muon, 
	      phi_max_muon,
	      pt_min_muon, 
	      pt_max_muon,
	      charge_muon,
	      sf_muon, 
	      sf_stat_err_muon, 
	      sf_syst_err_muon,
	      effdata_muon, 
	      effdata_stat_err_muon, 
	      effdata_syst_err_muon,
	      period,
	      run,
	      period_lumi,
	      run_lumi,
	      m_EnergyDependentSystematic,
	      m_UseChargeDependentSF,
	      m_FileWithEffi
	      );
    if(m_UseChargeDependentSF) //generate average SFs if charge is not provided
      {
	for(unsigned int i=0; i<charge_muon.size(); i++)
	  {
	    unsigned int orig_size=charge_muon[i].size();

	    for(unsigned int j=0; j<orig_size; j++)
	      {
		if(charge_muon[i][j]>99) continue;
		if(charge_muon[i][j]==0) 
		  {
		    cout<<"AnalysisMuonEfficiencyScaleFactors Error in configuration file: expected charges taht are not provided!!!!"<<endl;
		    continue;
		  }
		if(charge_muon[i][j]<0) continue;

		for(unsigned int k=0; k<orig_size; k++)
		  {
		    if(charge_muon[i][k]>0) continue;
		    if(charge_muon[i][k]>99) continue;
		    if(charge_muon[i][k]==0) 
		      {
			cout<<"AnalysisMuonEfficiencyScaleFactors Error in configuration file: expected charges taht are not provided!!!!"<<endl;
			continue;
		      }
		    
		    if(region_muon[i][j]==region_muon[i][k] && 
		       pt_min_muon[i][j]==pt_min_muon[i][k] &&
		       pt_max_muon[i][j]==pt_max_muon[i][k] &&
		       eta_min_muon[i][j]==eta_min_muon[i][k] &&
		       eta_max_muon[i][j]==eta_max_muon[i][k] &&
		       phi_min_muon[i][j]==phi_min_muon[i][k] &&
		       phi_max_muon[i][j]==phi_max_muon[i][k] )
		      {
			double sf1=sf_muon[i][j];
			double sf2=sf_muon[i][k];
			double err1=sf_stat_err_muon[i][j];
			double err2=sf_stat_err_muon[i][k];
			double systerr1=sf_syst_err_muon[i][j];
			double systerr2=sf_syst_err_muon[i][k];

			double AvgSF=(sf1+sf2)/2.;
			double AvgErr=sqrt(pow(err1,2)+pow(err2,2))/2;
			double SystErr=(systerr1+systerr2)/2;

			double effdata1=effdata_muon[i][j];
			double effdata2=effdata_muon[i][k];
			double effdata_err1=effdata_stat_err_muon[i][j];
			double effdata_err2=effdata_stat_err_muon[i][k];
			double effdata_systerr1=effdata_syst_err_muon[i][j];
			double effdata_systerr2=effdata_syst_err_muon[i][k];

			double AvgEffdata=(effdata1+effdata2)/2.;
			double AvgErrEffdata=sqrt(pow(effdata_err1,2)+pow(effdata_err2,2))/2;
			double SystErrEffdata=(effdata_systerr1+effdata_systerr2)/2;


			region_muon[i].push_back(region_muon[i][j]);
			pt_min_muon[i].push_back(pt_min_muon[i][j]);
			pt_max_muon[i].push_back(pt_max_muon[i][j]);
			eta_min_muon[i].push_back(eta_min_muon[i][j]);
			eta_max_muon[i].push_back(eta_max_muon[i][j]);
			phi_min_muon[i].push_back(phi_min_muon[i][j]);
			phi_max_muon[i].push_back(phi_max_muon[i][j]);
			charge_muon[i].push_back(100);
			sf_muon[i].push_back(AvgSF);
			sf_stat_err_muon[i].push_back(AvgErr);
			sf_syst_err_muon[i].push_back(SystErr);
			effdata_muon[i].push_back(AvgEffdata);
			effdata_stat_err_muon[i].push_back(AvgErrEffdata);
			effdata_syst_err_muon[i].push_back(SystErrEffdata);


		      }
		  }
	      }
	  }

	for(unsigned int i=0; i<charge_muon.size(); i++)
	  {
	    for(unsigned int j=0; j<charge_muon[i].size(); j++)
	      {
		if(charge_muon[i][j]>99) charge_muon[i][j]=0;
	      }
	  }
	
      }//end of  if(m_UseChargeDependentSF)
   

// copying in vectors //
    m_region= region_muon;
    m_eta_min = eta_min_muon;
    m_eta_max = eta_max_muon;
    m_phi_min = phi_min_muon;
    m_phi_max = phi_max_muon;
    m_pt_min = pt_min_muon;
    m_pt_max = pt_max_muon;
    m_charge=charge_muon;
    m_sf = sf_muon;
    m_sf_stat_err = sf_stat_err_muon;
    m_sf_syst_err = sf_syst_err_muon;
    m_effdata = effdata_muon;
    m_effdata_stat_err = effdata_stat_err_muon;
    m_effdata_syst_err = effdata_syst_err_muon;
    m_period=period;
    m_run=run;
    m_period_lumi=period_lumi;
    m_run_lumi=run_lumi;


}

void Analysis::AnalysisMuonConfigurableScaleFactors::addPeriod(TString period, double lumi)
{
  if(m_usingDefaultLumi)
  {
    m_usingDefaultLumi=false;
    m_run_lumi.clear();
  }

  TString temp=period;
  temp.ToLower();
  m_period_lumi[temp]=lumi;
}

void Analysis::AnalysisMuonConfigurableScaleFactors::addRun(int runnumber, double lumi)
{
  if(m_usingDefaultLumi)
  {
    m_usingDefaultLumi=false;
    m_run_lumi.clear();
  }
  m_run_lumi[runnumber]=lumi;
}

void Analysis::AnalysisMuonConfigurableScaleFactors::Initialise()
{

  cout<<"---Initlialising MCP AnalysisMuonConfigurableScaleFactors Tool---"<<endl;

  if(m_configuration == AverageOverPeriods) this->InitialiseAverageOverPeriods();
  if(m_configuration == AverageOverRuns) this->InitialiseAverageOverRuns();

  return;

}



void Analysis::AnalysisMuonConfigurableScaleFactors::InitialiseAverageOverPeriods()
{
  if(m_configuration != AverageOverPeriods) return; //for now no need of initialisation
  if(m_period_lumi.size()<1) 
    {
      cerr<<"AnalysisMuonConfigurableScaleFactors::Initialise -> NO LUMI PERIODS GIVEN!!! "<<endl;
      exit(1); 
    }
  double TotLum=0;
  std::map<TString, double>::const_iterator end =  m_period_lumi.end(); 
  std::vector<double> weights;

  std::vector<bool> LumiGiven;

  for(unsigned int i=0; i<m_period.size(); i++)
    {
      LumiGiven.push_back(false);
      weights.push_back(0);
    }

  for (std::map<TString, double>::const_iterator it = m_period_lumi.begin(); it != end; ++it) 
    {
      TString per=it->first;
      double lum=it->second;
      bool isIn=false;

    for(unsigned int jj=0; jj<m_period.size(); jj++)
	{
	  if(m_period[jj]==per)
	    {
	      LumiGiven[jj]=true;
	      weights[jj]=lum;
	      TotLum+=lum;
	      isIn=true;
	    }
	}      
    if(!isIn)
      {
	cerr<<"AnalysisMuonConfigurableScaleFactors::Initialise -> Given Luminosity for a period not in the config file!!! "<<endl;
	exit(1);
      }
    }
  if(TotLum==0)
    {
      cerr<<"AnalysisMuonConfigurableScaleFactors::Initialise -> Given 0 Luminosity!!! "<<endl;
	exit(1);
    }

  for(unsigned int i=0; i<weights.size(); i++) weights[i]/=TotLum;

  for(unsigned int i=0; i<m_period.size(); i++)
    {
      if(!LumiGiven[i]) 
	{
	  cout<<"AnalysisMuonConfigurableScaleFactors::Initialise -> WARNING!!! Period "<<m_period[i]<<" luminosisty not given!!! 0 assumed"<<endl;
	  m_period_lumi[m_period[i]]=0.;
	}
    }

  std::vector<int> vregion;
  std::vector<double> vpt_min, vpt_max; // bin boundaries in pt
  std::vector<double> veta_min, veta_max; // bin boundaries in pt
  std::vector<double> vphi_min, vphi_max; // bin boundaries in pt
  std::vector<int> vcharge;
  std::vector<double> vsf; // scale factors
  std::vector<double> vsf_stat_err; // statistical errors of the scale
  // factors
  std::vector<double> vsf_syst_err; // systematic errors of the scale 
                                       // factors
  std::vector<double> veffdata, veffdata_stat_err, veffdata_syst_err;

  for(unsigned int i=0; i<m_region[0].size(); i++)
    {
  
      double sf=0;
      double sf_stat_err=0;
      double sf_syst_err=0;
      double effdata=0;
      double effdata_stat_err=0;
      double effdata_syst_err=0;

      for(unsigned int j=0; j<m_period.size(); j++)
	{
	  int index =-1;
	  for(unsigned int k=0; k<m_region[j].size(); k++)
	    {
	      /*
	      cout<<m_region[0][i]<<" "<<m_region[j][k]<<endl;
	      cout<<m_pt_min[0][i]<<" "<<m_pt_min[j][k]<<endl;
	      cout<<m_pt_max[0][i]<<" "<<m_pt_max[j][k]<<endl;
	      cout<<m_eta_min[0][i]<<" "<<m_eta_min[j][k]<<endl;
	      cout<<m_eta_max[0][i]<<" "<<m_eta_max[j][k]<<endl;
	      cout<<m_phi_min[0][i]<<" "<<m_phi_min[j][k]<<endl;
	      cout<<m_phi_max[0][i]<<" "<<m_phi_max[j][k]<<endl;
	      */
	     if(m_region[0][i]==m_region[j][k] && 
		 m_pt_min[0][i]==m_pt_min[j][k] &&
		 m_pt_max[0][i]==m_pt_max[j][k] &&
		 m_eta_min[0][i]==m_eta_min[j][k] &&
		 m_eta_max[0][i]==m_eta_max[j][k] &&
		 m_phi_min[0][i]==m_phi_min[j][k] &&
		 m_phi_max[0][i]==m_phi_max[j][k] &&
		 m_charge[0][i]==m_charge[j][k])
		{
		  index=k;
		  break;
		}
	    }
  
	  if(index<0)
	    {
	      cerr<<"AnalysisMuonConfigurableScaleFactors::Initialise -> region in first period not found in other periods!!!! Error in config file!"<<endl;
	      cerr<<m_region[0][i]<<endl;
	      exit(1);
	    }
	  sf+=(m_sf[j][index]*weights[j]);
	  sf_stat_err+=pow((m_sf_stat_err[j][index]*weights[j]),2);
	  sf_syst_err+=(m_sf_syst_err[j][index]*weights[j]);

	  effdata+=(m_effdata[j][index]*weights[j]);
	  effdata_stat_err+=pow((m_effdata_stat_err[j][index]*weights[j]),2);
	  effdata_syst_err+=(m_effdata_syst_err[j][index]*weights[j]);
	}

      sf_stat_err=sqrt(sf_stat_err);
      effdata_stat_err=sqrt(effdata_stat_err);

      vregion=m_region[0];
      vpt_min=m_pt_min[0];
      vpt_max=m_pt_max[0];
      veta_min=m_eta_min[0];
      veta_max=m_eta_max[0];
      vphi_min=m_phi_min[0];
      vphi_max=m_phi_max[0];
      vcharge=m_charge[0];
      vsf.push_back(sf);
      vsf_stat_err.push_back(sf_stat_err);
      vsf_syst_err.push_back(sf_syst_err);
      veffdata.push_back(effdata);
      veffdata_stat_err.push_back(effdata_stat_err);
      veffdata_syst_err.push_back(effdata_syst_err);


    }

  m_region.clear();
  m_eta_min.clear();
  m_eta_max.clear();
  m_phi_min.clear();
  m_phi_max.clear();
  m_pt_min.clear();
  m_pt_max.clear();
  m_charge.clear();
  m_sf.clear();
  m_sf_stat_err.clear();
  m_sf_syst_err.clear();
  m_effdata.clear();
  m_effdata_stat_err.clear();
  m_effdata_syst_err.clear();

  m_region.push_back(vregion);
  m_eta_min.push_back(veta_min);
  m_eta_max.push_back(veta_max);  
  m_phi_min.push_back(vphi_min);
  m_phi_max.push_back(vphi_max); 
  m_pt_min.push_back(vpt_min);
  m_pt_max.push_back(vpt_max);
  m_charge.push_back(vcharge);
  m_sf.push_back(vsf);
  m_sf_stat_err.push_back(vsf_stat_err);
  m_sf_syst_err.push_back(vsf_syst_err);
  m_effdata.push_back(veffdata);
  m_effdata_stat_err.push_back(veffdata_stat_err);
  m_effdata_syst_err.push_back(veffdata_syst_err);


}


void Analysis::AnalysisMuonConfigurableScaleFactors::InitialiseAverageOverRuns()
{
  if(m_configuration != AverageOverRuns) return;
  if(m_run_lumi.size()<1) 
    {
      cerr<<"AnalysisMuonConfigurableScaleFactors::Initialise -> NO LUMI PERIODS GIVEN!!! "<<endl;
      exit(1); 
    }
  double TotLum=0;
  std::map<int, double>::const_iterator end =  m_run_lumi.end(); 
  std::vector<double> weights;

  std::vector<bool> LumiGiven;

  for(unsigned int i=0; i<m_run.size(); i++)
    {
      LumiGiven.push_back(false);
      weights.push_back(0);
    }

  for (std::map<int, double>::const_iterator it = m_run_lumi.begin(); it != end; ++it) 
    {
      int run=it->first;
      double lum=it->second;
      bool isIn=false;

      if(m_run_min>0 && (run<m_run_min || run>m_run_max)) lum=0;

      for(unsigned int jj=0; jj<m_run.size(); jj++)
	{
	  if(m_run[jj]==run)
	    {
	      LumiGiven[jj]=true;
	      weights[jj]=lum;
	      TotLum+=lum;
	      isIn=true;
	    }
	}      
    if(!isIn)
      {
	cerr<<"AnalysisMuonConfigurableScaleFactors::Initialise -> Given Luminosity for a run not in the config file!!! "<<endl;
	exit(1);
      }
    }
  if(TotLum==0)
    {
      cerr<<"AnalysisMuonConfigurableScaleFactors::Initialise -> Given 0 Luminosity!!! "<<endl;
	exit(1);
    }

  for(unsigned int i=0; i<weights.size(); i++) weights[i]/=TotLum;

  for(unsigned int i=0; i<m_run.size(); i++)
    {
      if(!LumiGiven[i]) 
	{
	  cout<<"AnalysisMuonConfigurableScaleFactors::Initialise -> WARNING!!! Run "<<m_run[i]<<" luminosisty not given!!! 0 assumed"<<endl;
	  m_run_lumi[m_run[i]]=0.;
	}
    }

  std::vector<int> vregion;
  std::vector<double> vpt_min, vpt_max; // bin boundaries in pt
  std::vector<double> veta_min, veta_max; // bin boundaries in pt
  std::vector<double> vphi_min, vphi_max; // bin boundaries in pt
  std::vector<int> vcharge;
  std::vector<double> vsf; // scale factors
  std::vector<double> vsf_stat_err; // statistical errors of the scale
  // factors
  std::vector<double> vsf_syst_err; // systematic errors of the scale 
                                       // factors
  std::vector<double> veffdata, veffdata_stat_err, veffdata_syst_err;

  for(unsigned int i=0; i<m_region[0].size(); i++)
    {
  
      double sf=0;
      double sf_stat_err=0;
      double sf_syst_err=0;
      double effdata=0;
      double effdata_stat_err=0;
      double effdata_syst_err=0;

    for(unsigned int j=0; j<m_run.size(); j++)
	{
	  int index =-1;
	  for(unsigned int k=0; k<m_region[j].size(); k++)
	    {
	     if(m_region[0][i]==m_region[j][k] && 
		 m_pt_min[0][i]==m_pt_min[j][k] &&
		 m_pt_max[0][i]==m_pt_max[j][k] &&
		 m_eta_min[0][i]==m_eta_min[j][k] &&
		 m_eta_max[0][i]==m_eta_max[j][k] &&
		 m_phi_min[0][i]==m_phi_min[j][k] &&
		 m_phi_max[0][i]==m_phi_max[j][k] &&
		 m_charge[0][i]==m_charge[j][k])
		{
		  index=k;
		  break;
		}
	    }
  
	  if(index<0)
	    {
	      cerr<<"AnalysisMuonConfigurableScaleFactors::Initialise -> region in first period not found in other periods!!!! Error in config file!"<<endl;
	      exit(1);
	    }
	  sf+=(m_sf[j][index]*weights[j]);
	  sf_stat_err+=pow((m_sf_stat_err[j][index]*weights[j]),2);
	  sf_syst_err+=(m_sf_syst_err[j][index]*weights[j]);

	  effdata+=(m_effdata[j][index]*weights[j]);
	  effdata_stat_err+=pow((m_effdata_stat_err[j][index]*weights[j]),2);
	  effdata_syst_err+=(m_effdata_syst_err[j][index]*weights[j]);
	}

      sf_stat_err=sqrt(sf_stat_err);
      effdata_stat_err=sqrt(effdata_stat_err);

      vregion=m_region[0];
      vpt_min=m_pt_min[0];
      vpt_max=m_pt_max[0];
      veta_min=m_eta_min[0];
      veta_max=m_eta_max[0];
      vphi_min=m_phi_min[0];
      vphi_max=m_phi_max[0];
      vcharge=m_charge[0];
      vsf.push_back(sf);
      vsf_stat_err.push_back(sf_stat_err);
      vsf_syst_err.push_back(sf_syst_err);
      veffdata.push_back(effdata);
      veffdata_stat_err.push_back(effdata_stat_err);
      veffdata_syst_err.push_back(effdata_syst_err);

    }

  m_region.clear();
  m_eta_min.clear();
  m_eta_max.clear();
  m_phi_min.clear();
  m_phi_max.clear();
  m_pt_min.clear();
  m_pt_max.clear();
  m_charge.clear();
  m_sf.clear();
  m_sf_stat_err.clear();
  m_sf_syst_err.clear();
  m_effdata.clear();
  m_effdata_stat_err.clear();
  m_effdata_syst_err.clear();

  m_region.push_back(vregion);
  m_eta_min.push_back(veta_min);
  m_eta_max.push_back(veta_max);  
  m_phi_min.push_back(vphi_min);
  m_phi_max.push_back(vphi_max); 
  m_pt_min.push_back(vpt_min);
  m_pt_max.push_back(vpt_max);
  m_charge.push_back(vcharge);
  m_sf.push_back(vsf);
  m_sf_stat_err.push_back(vsf_stat_err);
  m_sf_syst_err.push_back(vsf_syst_err);
  m_effdata.push_back(veffdata);
  m_effdata_stat_err.push_back(veffdata_stat_err);
  m_effdata_syst_err.push_back(veffdata_syst_err);

}
//*****************************************************************************

////////////////////////
// METHOD scaleFactor //
////////////////////////

double Analysis::AnalysisMuonConfigurableScaleFactors::scaleFactor(int charge,
								   const TLorentzVector & tlv) const {


  if(m_configuration!=Default &&m_configuration!=AverageOverPeriods && m_configuration!=AverageOverRuns) cout<<"ERROR in AnalysisMuonConfigurableScaleFactors; Using wrong scaleFactor method for configuration"<<endl;

  std::pair<int,int> bin=get_pt_eta_phi_bin_index(charge,tlv);
  if(bin.first<0 || bin.second<0) return 1.;
  return m_sf[bin.first][bin.second];

}

//*****************************************************************************

///////////////////////////////////
// METHOD scaleFactorUncertainty //
///////////////////////////////////

double Analysis::AnalysisMuonConfigurableScaleFactors::scaleFactorUncertainty(int charge,
									      const TLorentzVector & tlv) const {

  if(m_configuration!=Default &&m_configuration!=AverageOverPeriods && m_configuration!=AverageOverRuns) cout<<"ERROR in AnalysisMuonConfigurableScaleFactors; Using wrong scaleFactorUncertainty method for configuration"<<endl;
  std::pair<int,int> bin=get_pt_eta_phi_bin_index(charge,tlv);
  if(bin.first<0 || bin.second<0) return 0.;
  return m_sf_stat_err[bin.first][bin.second];


}

//*****************************************************************************

/////////////////////////////////////////////
// METHOD scaleFactorSystematicUncertainty //
/////////////////////////////////////////////

double Analysis::AnalysisMuonConfigurableScaleFactors::scaleFactorSystematicUncertainty(int charge,
											const TLorentzVector & tlv) const {

  if(m_configuration!=Default &&m_configuration!=AverageOverPeriods && m_configuration!=AverageOverRuns ) cout<<"ERROR in AnalysisMuonConfigurableScaleFactors; Using wrong scaleFactorSystematicUncertainty method for configuration"<<endl;

  std::pair<int,int> bin=get_pt_eta_phi_bin_index(charge,tlv);
  if(bin.first<0 || bin.second<0) return 0.;
  return m_sf_syst_err[bin.first][bin.second]+m_EnergyDependentSystematic*m_unit*tlv.E();

}

//*****************************************************************************

////////////////////////
// METHOD scaleFactor //
////////////////////////

double Analysis::AnalysisMuonConfigurableScaleFactors::scaleFactor(int charge,
								   const TLorentzVector & tlv,
								   std::string period) const {

  if(m_configuration!=PerPeriod) cout<<"ERROR in AnalysisMuonConfigurableScaleFactors; Using wrong scaleFactor method for configuration"<<endl;
  TString temp=period;
  temp.ToLower();

  std::pair<int,int> bin=get_pt_eta_phi_bin_index(charge,tlv,temp);
  if(bin.first<0 || bin.second<0) return 1.;
  return m_sf[bin.first][bin.second];


}

//*****************************************************************************

///////////////////////////////////
// METHOD scaleFactorUncertainty //
///////////////////////////////////

double Analysis::AnalysisMuonConfigurableScaleFactors::scaleFactorUncertainty(int charge,
									      const TLorentzVector & tlv, std::string period) const {

  if(m_configuration!=PerPeriod) cout<<"ERROR in AnalysisMuonConfigurableScaleFactors; Using wrong scaleFactorUncertainty method for configuration"<<endl;
  TString temp=period;
  temp.ToLower();

  std::pair<int,int> bin=get_pt_eta_phi_bin_index(charge,tlv,temp);
  if(bin.first<0 || bin.second<0) return 0.;
  return m_sf_stat_err[bin.first][bin.second];

}

//*****************************************************************************

/////////////////////////////////////////////
// METHOD scaleFactorSystematicUncertainty //
/////////////////////////////////////////////

double Analysis::AnalysisMuonConfigurableScaleFactors::scaleFactorSystematicUncertainty(int charge,
											const TLorentzVector & tlv, std::string period ) const {

  if(m_configuration!=PerPeriod) cout<<"ERROR in AnalysisMuonConfigurableScaleFactors; Using wrong scaleFactorSystematicUncertainty method for configuration"<<endl;
  TString temp=period;
  temp.ToLower();

  std::pair<int,int> bin=get_pt_eta_phi_bin_index(charge,tlv,temp);
  if(bin.first<0 || bin.second<0) return 0.;
  return m_sf_syst_err[bin.first][bin.second]+m_EnergyDependentSystematic*m_unit*tlv.E();

}

////////////////////////
// METHOD scaleFactor //
////////////////////////

double Analysis::AnalysisMuonConfigurableScaleFactors::scaleFactor(int charge, const TLorentzVector & tlv,
								   int run) const {


  if(m_configuration!=PerRun) cout<<"ERROR in AnalysisMuonConfigurableScaleFactors; Using wrong scaleFactor method for configuration"<<endl;
  std::pair<int,int> bin=get_pt_eta_phi_bin_index(charge,tlv,"",run);
  if(bin.first<0 || bin.second<0) return 1.;
  return m_sf[bin.first][bin.second];

}

//*****************************************************************************

///////////////////////////////////
// METHOD scaleFactorUncertainty //
///////////////////////////////////

double Analysis::AnalysisMuonConfigurableScaleFactors::scaleFactorUncertainty(int charge,
									      const TLorentzVector & tlv, int run) const {

  if(m_configuration!=PerRun) cout<<"ERROR in AnalysisMuonConfigurableScaleFactors; Using wrong scaleFactorUncertainty method for configuration"<<endl;

  std::pair<int,int> bin=get_pt_eta_phi_bin_index(charge,tlv,"",run);
  if(bin.first<0 || bin.second<0) return 0.;
  return m_sf_stat_err[bin.first][bin.second];

}

//*****************************************************************************

/////////////////////////////////////////////
// METHOD scaleFactorSystematicUncertainty //
/////////////////////////////////////////////

double Analysis::AnalysisMuonConfigurableScaleFactors::scaleFactorSystematicUncertainty(int charge,
											const TLorentzVector & tlv, int run ) const {

  if(m_configuration!=PerRun) cout<<"ERROR in AnalysisMuonConfigurableScaleFactors; Using wrong scaleFactorSystematicUncertainty method for configuration"<<endl;

  std::pair<int, int> bin=get_pt_eta_phi_bin_index(charge,tlv,"",run);
  if(bin.first<0 || bin.second<0) return 0.;
  return m_sf_syst_err[bin.first][bin.second]+m_EnergyDependentSystematic*m_unit*tlv.E();

}

//*****************************************************************************

//////////////////////
// METHOD read_file //
//////////////////////

void Analysis::AnalysisMuonConfigurableScaleFactors::read_file(
							   Configuration conf,
							   const std::string & name,
							   std::vector<vector<int> > & region,
							   std::vector<vector<double> > & eta_min,
							   std::vector<vector<double> >& eta_max,
							   std::vector<vector<double> >& phi_min,
							   std::vector<vector<double> >& phi_max,
							   std::vector<vector<double> >& pt_min,
							   std::vector<vector<double> >& pt_max,
							   std::vector<vector<int> > & charge,
							   std::vector<vector<double> >& sf,
							   std::vector<vector<double> >& sf_stat_err,
							   std::vector<vector<double> >& sf_syst_err,
							   std::vector<vector<double> >& effdata,
							   std::vector<vector<double> >& effdata_stat_err,
							   std::vector<vector<double> >& effdata_syst_err,
							   std::vector<TString> &period,
							   std::vector<int> &run,
							   std::map<TString, double> &period_lumi,
							   std::map<int, double> &run_lumi,
							   double &EnergyDependentSystematic,
							   bool &UseChargeDependentSF,
							   bool &FileWithEffi
							   ) const 
{
  
  ///////////
  // CLEAR //
  ///////////
  EnergyDependentSystematic=0;
  UseChargeDependentSF=false;
  FileWithEffi=false;

  region.clear();
  eta_min.clear();
  eta_max.clear();
  phi_min.clear();
  phi_max.clear();
  pt_min.clear();
  pt_max.clear();
  charge.clear();
  sf.clear();
  sf_stat_err.clear();
  sf_syst_err.clear();
  effdata.clear();
  effdata_stat_err.clear();
  effdata_syst_err.clear();
  period.clear();
  run.clear();
  
  ////////////////////
  // OPEN DATA FILE //
  ////////////////////
  
  ifstream infile(name.c_str());
  if (infile.fail()) {
    std::cerr << "Class ConfigurableScaleFactors, "
	      << "method read_file.\n"
	      << "ERROR! Could not open file " << name
	      << std::endl;
    exit(1);
  }
  
  // read data file //
  double r_eta_min, r_eta_max, r_phi_min, r_phi_max, r_pt_min, r_pt_max, r_sf;
  double r_sf_err, r_sf_syst_err;
  double r_effdata, r_effdata_err, r_effdata_syst_err;
  int r_region;
  int r_charge=0;
  string r_period="";
  int r_run=0;
  double r_lumi=0;

  region.push_back(std::vector<int>());
  eta_min.push_back(std::vector<double>());  
  eta_max.push_back(std::vector<double>());
  phi_min.push_back(std::vector<double>());
  phi_max.push_back(std::vector<double>());
  pt_min.push_back(std::vector<double>());
  pt_max.push_back(std::vector<double>());
  charge.push_back(std::vector<int>());
  sf.push_back(std::vector<double>());
  sf_stat_err.push_back(std::vector<double>());
  sf_syst_err.push_back(std::vector<double>());
  effdata.push_back(std::vector<double>());
  effdata_stat_err.push_back(std::vector<double>());
  effdata_syst_err.push_back(std::vector<double>());

  bool FirstLine=true;

  if(conf==Default)
    {
      while (!infile.eof()) 
	{

	  if(FirstLine&& (infile.peek()=='#' || infile.peek()=='s'))
	    {
	      char line[256];
	      infile.getline(line,256);	  

	      TString tline=line;
	      if(tline[0]=='#') continue;

	      TObjArray *strobj = tline.Tokenize(" "); 
	      
	      if(strobj->GetEntries()!=3)
		{
		  std::cerr << "Class ConfigurableScaleFactors, "
			    << "method read_file.\n"
			    << "ERROR! Wrong parameter line! Correct Config File! " << name
			    << std::endl;
		  exit(1);

		}

	      TString command= ((TObjString *)strobj->At(0))->GetString();
	      TString parameter= ((TObjString *)strobj->At(1))->GetString();
	      TString value= ((TObjString *)strobj->At(2))->GetString();

	      if(command=="set")
		{
		  if(parameter=="EnergyDependentSystematic")
		    {
		      double v=value.Atof();
		      cout<<"Setting EnergyDependentSystematic to "<<v<<endl;
		      EnergyDependentSystematic=v;
		    }
		  if(parameter=="UseChargeDependentSF")
		    {
		      double v=value.Atof();
		      if(v>0.5)
			{
			  cout<<"Using Charge Dependent SFs"<<endl;
			  UseChargeDependentSF=true;
			}
		    }
		  if(parameter=="FileWithEffi")
		    {
		      double v=value.Atof();
		      if(v>0.5)
			{
			  cout<<"File with Efficiencies"<<endl;
			  FileWithEffi=true;
			}
		    }

		}

	      delete strobj;
 
	      continue;
	    }
	  FirstLine=false;

	  infile >> r_pt_min >> r_pt_max >> r_region
		 >> r_eta_min >> r_eta_max
		 >> r_phi_min >> r_phi_max 
		 >> r_sf >> r_sf_err >> r_sf_syst_err;
	  if(FileWithEffi)
	    {
	      infile>>r_effdata>> r_effdata_err >> r_effdata_syst_err;
	    }
	  else
	    {
	      r_effdata=1.;
	      r_effdata_err=0.;
	      r_effdata_syst_err=0.;
	    }
	  
	  if (infile.eof())
	    break;
	  
	  if(m_UseChargeDependentSF)
	    {
	      r_charge=1;
	      if(r_pt_min<0) r_charge=-1;
	      r_pt_min=fabs(r_pt_min);
	      r_pt_max=fabs(r_pt_max);
	    }
	  charge[0].push_back(r_charge);
	  region[0].push_back(r_region);
	  pt_min[0].push_back(r_pt_min);
	  pt_max[0].push_back(r_pt_max);
	  eta_min[0].push_back(r_eta_min);
	  eta_max[0].push_back(r_eta_max);
	  phi_min[0].push_back(r_phi_min);
	  phi_max[0].push_back(r_phi_max);
	  sf[0].push_back(r_sf);
	  sf_stat_err[0].push_back(r_sf_err);
	  sf_syst_err[0].push_back(r_sf_syst_err);
	  effdata[0].push_back(r_effdata);
	  effdata_stat_err[0].push_back(r_effdata_err);
	  effdata_syst_err[0].push_back(r_effdata_syst_err);
	  period.push_back(r_period);
	  run.push_back(r_run);
	}
    }   
  
  if(conf==PerPeriod || conf==AverageOverPeriods)
    {
      while (!infile.eof()) 
	{

	  if(FirstLine&& (infile.peek()=='#' || infile.peek()=='s'))
	    {
	      char line[256];
	      infile.getline(line,256);	  

	      TString tline=line;
	      if(tline[0]=='#') continue;

	      TObjArray *strobj = tline.Tokenize(" "); 
	      
	      if(strobj->GetEntries()!=3)
		{
		  std::cerr << "Class ConfigurableScaleFactors, "
			    << "method read_file.\n"
			    << "ERROR! Wrong parameter line! Correct Config File! " << name
			    << std::endl;
		  exit(1);

		}

	      TString command= ((TObjString *)strobj->At(0))->GetString();
	      TString parameter= ((TObjString *)strobj->At(1))->GetString();
	      TString value= ((TObjString *)strobj->At(2))->GetString();

	      if(command=="set")
		{
		  if(parameter=="EnergyDependentSystematic")
		    {
		      double v=value.Atof();
		      cout<<"Setting EnergyDependentSystematic to "<<v<<endl;
		      EnergyDependentSystematic=v;
		    }

		
		  if(parameter=="UseChargeDependentSF")
		    {
		      double v=value.Atof();
		      if(v>0.5)
			{
			  cout<<"Using Charge Dependent SFs"<<endl;
			  UseChargeDependentSF=true;
			}
		    }		  
		  if(parameter=="FileWithEffi")
		    {
		      double v=value.Atof();
		      if(v>0.5)
			{
			  cout<<"File with Efficiencies"<<endl;
			  FileWithEffi=true;
			}
		    }
		}
	      delete strobj;
 
	      continue;
	    }
	  FirstLine=false;
	  
	  infile >> r_period >> r_lumi >> r_pt_min >> r_pt_max >> r_region
		 >> r_eta_min >> r_eta_max
		 >> r_phi_min >> r_phi_max 
		 >> r_sf >> r_sf_err >> r_sf_syst_err;
	  if(FileWithEffi)
	    {
	      infile>>r_effdata>> r_effdata_err >> r_effdata_syst_err;
	    }
	  else
	    {
	      r_effdata=1.;
	      r_effdata_err=0.;
	      r_effdata_syst_err=0.;
	    }
	  if (infile.eof())
	    break;

	  //cout<<"reading line "<< r_period <<" "<< r_lumi <<" "<< r_pt_min <<" "<< r_pt_max <<" "<< r_region<<" " << r_eta_min <<" " << r_eta_max<<" "	 << r_phi_min <<" "<< r_phi_max <<" " << r_sf <<" "<< r_sf_err <<" syst="<< r_sf_syst_err<<endl;

	  int index=-1;
	  for(unsigned int i=0; i<period.size(); i++)
	    {
	      TString temp_period=r_period;
	      temp_period.ToLower();
	      if(period[i]==temp_period)
		{
		  index=i;
		  //cout<<"period already in with index "<<index<<endl;
		}
	    }
	  if(index<0) 
	    {
	      TString per=r_period;	
	      per.ToLower();      
	      period.push_back(per);
	      
	      period_lumi[per] =r_lumi;

	      //cout<<"Adding vectors"<<endl;

	      index=period.size()-1;
	      if(region.size()<period.size())
		{
		  region.push_back(std::vector<int>());
		  eta_min.push_back(std::vector<double>());  
		  eta_max.push_back(std::vector<double>());
		  phi_min.push_back(std::vector<double>());
		  phi_max.push_back(std::vector<double>());
		  pt_min.push_back(std::vector<double>());
		  pt_max.push_back(std::vector<double>());
		  charge.push_back(std::vector<int>());
		  sf.push_back(std::vector<double>());
		  sf_stat_err.push_back(std::vector<double>());
		  sf_syst_err.push_back(std::vector<double>());
		  effdata.push_back(std::vector<double>());
		  effdata_stat_err.push_back(std::vector<double>());
		  effdata_syst_err.push_back(std::vector<double>());
		}
	    }
	  //cout<<"Filling ind="<<index<<endl;
	  if(m_UseChargeDependentSF)
	    {
	      r_charge=1;
	      if(r_pt_min<0) r_charge=-1;
	      r_pt_min=fabs(r_pt_min);
	      r_pt_max=fabs(r_pt_max);
	    }
	  charge[index].push_back(r_charge);
	  region[index].push_back(r_region);
	  pt_min[index].push_back(r_pt_min);
	  pt_max[index].push_back(r_pt_max);
	  eta_min[index].push_back(r_eta_min);
	  eta_max[index].push_back(r_eta_max);
	  phi_min[index].push_back(r_phi_min);
	  phi_max[index].push_back(r_phi_max);
	  sf[index].push_back(r_sf);
	  sf_stat_err[index].push_back(r_sf_err);
	  sf_syst_err[index].push_back(r_sf_syst_err);
	  effdata[index].push_back(r_effdata);
	  effdata_stat_err[index].push_back(r_effdata_err);
	  effdata_syst_err[index].push_back(r_effdata_syst_err);

	  //cout<<"Added period="<<period[index]<<" lumi="<<period_lumi[period[index] ]<<" "<<region[index][region.size()-1]<<" "<<pt_min[index][pt_min.size()-1]<<" "<<pt_max[index][pt_max.size()-1]<<" "<<eta_min[index][eta_min.size()-1]<<" "<<eta_max[index][eta_max.size()-1]<<" "<<phi_min[index][phi_min.size()-1]<<" "<<phi_max[index][phi_max.size()-1]<<" "<<sf[index][sf.size()-1]<<" "<<sf_stat_err[index][sf_stat_err.size()-1]<<" syst="<<sf_syst_err[index][sf_syst_err.size()-1]<<endl;
	}

      for(unsigned int i=1; i<period.size(); i++)
	{
	  if(region[i].size()!=region[0].size()) 
	    {
	      cout<<"Analysis::AnalysisMuonConfigurableScaleFactors::read_file -> One of the periods has less bins, check config file!"<<endl;
	      cout<<region[0].size()<<" "<<region[i].size()<<endl;
	    }
	}

      
    }
 

   if(conf==PerRun || conf==AverageOverRuns)
    {
      while (!infile.eof()) 
	{

	  if(FirstLine&& (infile.peek()=='#' || infile.peek()=='s'))
	    {
	      char line[256];
	      infile.getline(line,256);	  

	      TString tline=line;
	      if(tline[0]=='#') continue;

	      TObjArray *strobj = tline.Tokenize(" "); 
	      
	      if(strobj->GetEntries()!=3)
		{
		  std::cerr << "Class ConfigurableScaleFactors, "
			    << "method read_file.\n"
			    << "ERROR! Wrong parameter line! Correct Config File! " << name
			    << std::endl;
		  exit(1);

		}

	      TString command= ((TObjString *)strobj->At(0))->GetString();
	      TString parameter= ((TObjString *)strobj->At(1))->GetString();
	      TString value= ((TObjString *)strobj->At(2))->GetString();

	      if(command=="set")
		{
		  if(parameter=="EnergyDependentSystematic")
		    {
		      double v=value.Atof();
		      cout<<"Setting EnergyDependentSystematic to "<<v<<endl;
		      EnergyDependentSystematic=v;
		    }
		  if(parameter=="UseChargeDependentSF")
		    {
		      double v=value.Atof();
		      if(v>0.5)
			{
			  cout<<"Using Charge Dependent SFs"<<endl;
			  UseChargeDependentSF=true;
			}
		    }		  
		  if(parameter=="FileWithEffi")
		    {
		      double v=value.Atof();
		      if(v>0.5)
			{
			  cout<<"File with Efficiencies"<<endl;
			  FileWithEffi=true;
			}
		    }
		}

	      delete strobj;
 
	      continue;
	    }
	  FirstLine=false;

	  infile >> r_run >> r_lumi >> r_pt_min >> r_pt_max >> r_region
		 >> r_eta_min >> r_eta_max
		 >> r_phi_min >> r_phi_max 
		 >> r_sf >> r_sf_err >> r_sf_syst_err;	  
	  if(FileWithEffi)
	    {
	      infile>>r_effdata>> r_effdata_err >> r_effdata_syst_err;
	    }
	  else
	    {
	      r_effdata=1.;
	      r_effdata_err=0.;
	      r_effdata_syst_err=0.;
	    }
	  if (infile.eof())
	    break;

	  int index=-1;
	  for(unsigned int i=0; i<run.size(); i++)
	    {
	      if(run[i]==r_run)
		{
		  if(index>-1) cout<<"Analysis::AnalysisMuonConfigurableScaleFactors::read_file ->ERROR! SAME RUN ADDED TWICE!"<<endl;
		  index=i;
		}
	    }
	  if(index<0) 
	    {
	      run.push_back(r_run);

	      run_lumi[r_run]=r_lumi;

	      index=run.size()-1;
	      if(region.size()<run.size())
		{
		  region.push_back(std::vector<int>());
		  eta_min.push_back(std::vector<double>());  
		  eta_max.push_back(std::vector<double>());
		  phi_min.push_back(std::vector<double>());
		  phi_max.push_back(std::vector<double>());
		  pt_min.push_back(std::vector<double>());
		  pt_max.push_back(std::vector<double>());
		  charge.push_back(std::vector<int>());
		  sf.push_back(std::vector<double>());
		  sf_stat_err.push_back(std::vector<double>());
		  sf_syst_err.push_back(std::vector<double>());
		  effdata.push_back(std::vector<double>());
		  effdata_stat_err.push_back(std::vector<double>());
		  effdata_syst_err.push_back(std::vector<double>());
		}
	    }
	  if(m_UseChargeDependentSF)
	    {
	      r_charge=1;
	      if(r_pt_min<0) r_charge=-1;
	      r_pt_min=fabs(r_pt_min);
	      r_pt_max=fabs(r_pt_max);
	    }
	  charge[index].push_back(r_charge);
	  region[index].push_back(r_region);
	  pt_min[index].push_back(r_pt_min);
	  pt_max[index].push_back(r_pt_max);
	  eta_min[index].push_back(r_eta_min);
	  eta_max[index].push_back(r_eta_max);
	  phi_min[index].push_back(r_phi_min);
	  phi_max[index].push_back(r_phi_max);
	  sf[index].push_back(r_sf);
	  sf_stat_err[index].push_back(r_sf_err);
	  sf_syst_err[index].push_back(r_sf_syst_err);	  
	  effdata[index].push_back(r_effdata);
	  effdata_stat_err[index].push_back(r_effdata_err);
	  effdata_syst_err[index].push_back(r_effdata_syst_err);
	}

      for(unsigned int i=1; i<run.size(); i++)
	{
	  if(region[i].size()!=region[0].size()) 
	    {
	      cout<<"Analysis::AnalysisMuonConfigurableScaleFactors::read_file -> One of the runs has less bins, check config file!"<<endl;
	    }
	}

      
    }

  
  for(unsigned int i=0; i<period.size(); i++) period[i].ToLower();
   
  return;
  
}

//*****************************************************************************

/////////////////////////////////////
// METHOD get_pt_eta_phi_bin_index //
/////////////////////////////////////

std::pair<int,int> Analysis::AnalysisMuonConfigurableScaleFactors::get_pt_eta_phi_bin_index(
											    int charge,
											    const TLorentzVector & tlv,
											    TString period,
											    int runnumber) const {

  //cout<<endl<<"--------------------------"<<endl;				    
  int region_bin=m_EPbin.symmetricBin(&tlv);
  if(tlv.Eta()<0) region_bin=-region_bin;

  std::pair<int,int> indexes;
  indexes=std::make_pair(-1,-1);
  int index=0;
  //cout<<"period "<<period<<endl;
  //cout<<m_period.size()<<endl;
  if(charge!=0 && !m_UseChargeDependentSF)
    {

      cerr<<"Analysis::AnalysisMuonConfigurableScaleFactors::get_pt_eta_phi_bin_index ->ERROR: the config file does not have charge dependent SFs"<<endl;
      return indexes;

    }

  if(charge==0 && m_UseChargeDependentSF)
    {
      cout<<"Analysis::AnalysisMuonConfigurableScaleFactors::get_pt_eta_phi_bin_index ->WARNING: the config file contains SFs per charge, the charge of the muon should be provided"<<endl;
    }
  if(charge<-1.5 || charge >1.5) 
    {
      cerr<<"Analysis::AnalysisMuonConfigurableScaleFactors::get_pt_eta_phi_bin_index ->ERROR: charge provided must be -1 or +1"<<endl;
      return indexes;
    }
  
  TString inperiod=period;
  inperiod.ToLower();
  if(inperiod!=""&& m_configuration==PerPeriod )
    {
      index=-1;

      for(unsigned int i=0; i<m_period.size(); i++)
	{ 	  
	  //cout<<"m_period[i] "<<m_period[i]<<endl;
	  if(inperiod!=m_period[i]) continue;
	  else index=i;
	}
      
      if(index<0) cerr<<"Analysis::AnalysisMuonConfigurableScaleFactors::get_pt_eta_phi_bin_index ->ERROR: period not found in config file"<<endl;
    

    }

  if( runnumber> 1000 && m_configuration==PerRun)
    {
      index=-1;
      for(unsigned int i=0; i<m_run.size(); i++)
	{ 	  
	  //cout<<"m_period[i] "<<m_period[i]<<endl;
	  if(runnumber!=m_run[i]) continue;
	  else index=i;
	}
      
      if(index<0) cerr<<"Analysis::AnalysisMuonConfigurableScaleFactors::get_pt_eta_phi_bin_index ->ERROR: run not found in config file"<<endl;
    }

  if(index<0) 
    {
      cerr<<"Analysis::AnalysisMuonConfigurableScaleFactors -> required period or run not available in config file! "<<period<<" "<<runnumber<<endl;
      cerr<<"The SF used will be the one of firts period/run"<<endl;
      return indexes;
    }	
    
  for (unsigned int k=0; k<m_pt_min[index].size(); k++) 
    {

      if (m_unit*tlv.Pt()<m_pt_min[index][k] || m_unit*tlv.Pt()>m_pt_max[index][k]) {
	continue;
      }

       if(charge!=m_charge[index][k]) continue;

      if(m_region[index][k]<100)
	{
	  if(region_bin==0) continue;
	  if(region_bin==m_region[index][k])
	    {

	      indexes=std::make_pair(index,k);
	      return indexes;
	    }
	  else continue;
	}

      if (tlv.Eta()<m_eta_min[index][k] || tlv.Eta()>m_eta_max[index][k]) {
	continue;
      }
 

      if (tlv.Phi()<m_phi_min[index][k] || tlv.Phi()>m_phi_max[index][k]) {
	continue;
      }
      


      indexes=std::make_pair(index,k);
      return indexes;
    }
  
  
  std::cerr << "Class AnalysisMuonEfficiencyScaleFactors, "
	    << "get_pt_eta_phi_bin_index!\n"
	    << "ERROR! No bin with scale factor information could be found."
	    << "\npt, eta, phi: "
	    << m_unit*tlv.Pt() << "\t"
	    << tlv.Eta() << "\t"
	    << tlv.Phi()
	    <<"charge "<<charge
	    << std::endl;
  
  return indexes;
  //exit(1);
  
}


void Analysis::AnalysisMuonConfigurableScaleFactors::generateReplicas(int nreplica, int seed)
{
  m_nreplica=nreplica;
  m_sf_replica.clear();
  m_effdata_replica.clear();

  TRandom3 Rndm(seed);

  for(unsigned int i=0; i<m_sf.size(); ++i) 
    {
      m_sf_replica.push_back( std::vector<std::vector<double> >() );    
      m_effdata_replica.push_back( std::vector<std::vector<double> >() );

      for(unsigned int j=0; j<m_sf[i].size(); ++j) 
	{      
	  m_sf_replica[i].push_back( std::vector<double>() );
	  m_effdata_replica[i].push_back( std::vector<double>() );

	  for(int k=0; k<nreplica; ++k) 
	    {
	      m_sf_replica[i][j].push_back( Rndm.Gaus( m_sf[i][j], m_sf_stat_err[i][j] ) ); 
	      m_effdata_replica[i][j].push_back( Rndm.Gaus( m_effdata[i][j], m_effdata_stat_err[i][j] ) );   
	    }
	}
    }

  return;
}


//*****************************************************************************

////////////////////////
// METHOD scaleFactorReplica //
////////////////////////

double Analysis::AnalysisMuonConfigurableScaleFactors::scaleFactorReplica(int charge,
									  const TLorentzVector & tlv, int nr) const {


  if(m_configuration!=Default &&m_configuration!=AverageOverPeriods && m_configuration!=AverageOverRuns) cout<<"ERROR in AnalysisMuonConfigurableScaleFactors; Using wrong scaleFactorReplica method for configuration"<<endl;

  if(nr>=m_nreplica) 
    {
      cout<<"ERROR in AnalysisMuonConfigurableScaleFactors: Replica required not generated! Max replica is : "<<m_nreplica<<endl;
      nr=m_nreplica-1;
      if(nr<0) nr=0;
    }

  std::pair<int,int> bin=get_pt_eta_phi_bin_index(charge,tlv);
  if(bin.first<0 || bin.second<0) return 1.;
  return m_sf_replica[bin.first][bin.second][nr];

}


//*****************************************************************************

////////////////////////
// METHOD scaleFactorReplica //
////////////////////////

double Analysis::AnalysisMuonConfigurableScaleFactors::scaleFactorReplica(int charge, const TLorentzVector & tlv,
									  std::string period, int nr) const {

  if(m_configuration!=PerPeriod) cout<<"ERROR in AnalysisMuonConfigurableScaleFactors; Using wrong scaleFactorReplica method for configuration"<<endl;

  if(nr>=m_nreplica) 
    {
      cout<<"ERROR in AnalysisMuonConfigurableScaleFactors: Replica required not generated! Max replica is : "<<m_nreplica<<endl;
      nr=m_nreplica-1;  
      if(nr<0) nr=0;
    }

  TString temp=period;
  temp.ToLower();

  std::pair<int,int> bin=get_pt_eta_phi_bin_index(charge,tlv,temp);
  if(bin.first<0 || bin.second<0) return 1.;
  return m_sf_replica[bin.first][bin.second][nr];


}


////////////////////////
// METHOD scaleFactorReplica //
////////////////////////

double Analysis::AnalysisMuonConfigurableScaleFactors::scaleFactorReplica(int charge, const TLorentzVector & tlv,
									  int run, int nr) const {

  if(m_configuration!=PerRun) cout<<"ERROR in AnalysisMuonConfigurableScaleFactors; Using wrong scaleFactorReplica method for configuration"<<endl;

  if(nr>=m_nreplica) 
    {
      cout<<"ERROR in AnalysisMuonConfigurableScaleFactors: Replica required not generated! Max replica is : "<<m_nreplica<<endl;
      nr=m_nreplica-1;
      if(nr<0) nr=0;
    }

  std::pair<int,int> bin=get_pt_eta_phi_bin_index(charge,tlv,"",run);
  if(bin.first<0 || bin.second<0) return 1.;
  return m_sf_replica[bin.first][bin.second][nr];

}

////////////////////////////////////
////////////////////////////////////
//DataEff methods
////////////////////////////////////
////////////////////////////////////

double Analysis::AnalysisMuonConfigurableScaleFactors::dataEff(int charge,
								   const TLorentzVector & tlv) const {


  if(m_configuration!=Default &&m_configuration!=AverageOverPeriods && m_configuration!=AverageOverRuns) cout<<"ERROR in AnalysisMuonConfigurableScaleFactors; Using wrong dataEff method for configuration"<<endl;
  if(!m_FileWithEffi) cout<<"ERROR in AnalysisMuonConfigurableScaleFactors::dataEff method: input file has no efficiency information"<<endl;

  std::pair<int,int> bin=get_pt_eta_phi_bin_index(charge,tlv);
  if(bin.first<0 || bin.second<0) return 1.;
  return m_effdata[bin.first][bin.second];

}

//*****************************************************************************

///////////////////////////////////
// METHOD dataEffUncertainty //
///////////////////////////////////

double Analysis::AnalysisMuonConfigurableScaleFactors::dataEffUncertainty(int charge,
									      const TLorentzVector & tlv) const {

  if(m_configuration!=Default &&m_configuration!=AverageOverPeriods && m_configuration!=AverageOverRuns) cout<<"ERROR in AnalysisMuonConfigurableScaleFactors; Using wrong dataEffUncertainty method for configuration"<<endl;
  if(!m_FileWithEffi) cout<<"ERROR in AnalysisMuonConfigurableScaleFactors::dataEff method: input file has no efficiency information"<<endl;
  std::pair<int,int> bin=get_pt_eta_phi_bin_index(charge,tlv);
  if(bin.first<0 || bin.second<0) return 0.;
  return m_effdata_stat_err[bin.first][bin.second];


}

//*****************************************************************************

/////////////////////////////////////////////
// METHOD dataEffSystematicUncertainty //
/////////////////////////////////////////////

double Analysis::AnalysisMuonConfigurableScaleFactors::dataEffSystematicUncertainty(int charge,
											const TLorentzVector & tlv) const {

  if(m_configuration!=Default &&m_configuration!=AverageOverPeriods && m_configuration!=AverageOverRuns ) cout<<"ERROR in AnalysisMuonConfigurableScaleFactors; Using wrong dataEffSystematicUncertainty method for configuration"<<endl;
  if(!m_FileWithEffi) cout<<"ERROR in AnalysisMuonConfigurableScaleFactors::dataEff method: input file has no efficiency information"<<endl;
  std::pair<int,int> bin=get_pt_eta_phi_bin_index(charge,tlv);
  if(bin.first<0 || bin.second<0) return 0.;
  return m_effdata_syst_err[bin.first][bin.second]+m_EnergyDependentSystematic*m_unit*tlv.E();

}

//*****************************************************************************

////////////////////////
// METHOD dataEff //
////////////////////////

double Analysis::AnalysisMuonConfigurableScaleFactors::dataEff(int charge,
								   const TLorentzVector & tlv,
								   std::string period) const {

  if(m_configuration!=PerPeriod) cout<<"ERROR in AnalysisMuonConfigurableScaleFactors; Using wrong dataEff method for configuration"<<endl;
  if(!m_FileWithEffi) cout<<"ERROR in AnalysisMuonConfigurableScaleFactors::dataEff method: input file has no efficiency information"<<endl;
  TString temp=period;
  temp.ToLower();

  std::pair<int,int> bin=get_pt_eta_phi_bin_index(charge,tlv,temp);
  if(bin.first<0 || bin.second<0) return 1.;
  return m_effdata[bin.first][bin.second];


}

//*****************************************************************************

///////////////////////////////////
// METHOD dataEffUncertainty //
///////////////////////////////////

double Analysis::AnalysisMuonConfigurableScaleFactors::dataEffUncertainty(int charge,
									      const TLorentzVector & tlv, std::string period) const {

  if(m_configuration!=PerPeriod) cout<<"ERROR in AnalysisMuonConfigurableScaleFactors; Using wrong dataEffUncertainty method for configuration"<<endl;
  if(!m_FileWithEffi) cout<<"ERROR in AnalysisMuonConfigurableScaleFactors::dataEff method: input file has no efficiency information"<<endl;
  TString temp=period;
  temp.ToLower();

  std::pair<int,int> bin=get_pt_eta_phi_bin_index(charge,tlv,temp);
  if(bin.first<0 || bin.second<0) return 0.;
  return m_effdata_stat_err[bin.first][bin.second];

}

//*****************************************************************************

/////////////////////////////////////////////
// METHOD dataEffSystematicUncertainty //
/////////////////////////////////////////////

double Analysis::AnalysisMuonConfigurableScaleFactors::dataEffSystematicUncertainty(int charge,
											const TLorentzVector & tlv, std::string period ) const {

  if(m_configuration!=PerPeriod) cout<<"ERROR in AnalysisMuonConfigurableScaleFactors; Using wrong dataEffSystematicUncertainty method for configuration"<<endl;
  if(!m_FileWithEffi) cout<<"ERROR in AnalysisMuonConfigurableScaleFactors::dataEff method: input file has no efficiency information"<<endl;
  TString temp=period;
  temp.ToLower();

  std::pair<int,int> bin=get_pt_eta_phi_bin_index(charge,tlv,temp);
  if(bin.first<0 || bin.second<0) return 0.;
  return m_effdata_syst_err[bin.first][bin.second]+m_EnergyDependentSystematic*m_unit*tlv.E();

}

////////////////////////
// METHOD dataEff //
////////////////////////

double Analysis::AnalysisMuonConfigurableScaleFactors::dataEff(int charge, const TLorentzVector & tlv,
								   int run) const {


  if(m_configuration!=PerRun) cout<<"ERROR in AnalysisMuonConfigurableScaleFactors; Using wrong dataEff method for configuration"<<endl;
  if(!m_FileWithEffi) cout<<"ERROR in AnalysisMuonConfigurableScaleFactors::dataEff method: input file has no efficiency information"<<endl;
  std::pair<int,int> bin=get_pt_eta_phi_bin_index(charge,tlv,"",run);
  if(bin.first<0 || bin.second<0) return 1.;
  return m_effdata[bin.first][bin.second];

}

//*****************************************************************************

///////////////////////////////////
// METHOD dataEffUncertainty //
///////////////////////////////////

double Analysis::AnalysisMuonConfigurableScaleFactors::dataEffUncertainty(int charge,
									      const TLorentzVector & tlv, int run) const {

  if(m_configuration!=PerRun) cout<<"ERROR in AnalysisMuonConfigurableScaleFactors; Using wrong dataEffUncertainty method for configuration"<<endl;
  if(!m_FileWithEffi) cout<<"ERROR in AnalysisMuonConfigurableScaleFactors::dataEff method: input file has no efficiency information"<<endl;

  std::pair<int,int> bin=get_pt_eta_phi_bin_index(charge,tlv,"",run);
  if(bin.first<0 || bin.second<0) return 0.;
  return m_effdata_stat_err[bin.first][bin.second];

}

//*****************************************************************************

/////////////////////////////////////////////
// METHOD dataEffSystematicUncertainty //
/////////////////////////////////////////////

double Analysis::AnalysisMuonConfigurableScaleFactors::dataEffSystematicUncertainty(int charge,
											const TLorentzVector & tlv, int run ) const {

  if(m_configuration!=PerRun) cout<<"ERROR in AnalysisMuonConfigurableScaleFactors; Using wrong dataEffSystematicUncertainty method for configuration"<<endl;
  if(!m_FileWithEffi) cout<<"ERROR in AnalysisMuonConfigurableScaleFactors::dataEff method: input file has no efficiency information"<<endl;

  std::pair<int, int> bin=get_pt_eta_phi_bin_index(charge,tlv,"",run);
  if(bin.first<0 || bin.second<0) return 0.;
  return m_effdata_syst_err[bin.first][bin.second]+m_EnergyDependentSystematic*m_unit*tlv.E();

}

//*****************************************************************************

////////////////////////
// METHOD scaleFactorReplica //
////////////////////////

double Analysis::AnalysisMuonConfigurableScaleFactors::dataEffReplica(int charge,
									  const TLorentzVector & tlv, int nr) const {


  if(m_configuration!=Default &&m_configuration!=AverageOverPeriods && m_configuration!=AverageOverRuns) cout<<"ERROR in AnalysisMuonConfigurableScaleFactors; Using wrong dataEffReplica method for configuration"<<endl;
  if(!m_FileWithEffi) cout<<"ERROR in AnalysisMuonConfigurableScaleFactors::dataEff method: input file has no efficiency information"<<endl;
  if(nr>=m_nreplica) 
    {
      cout<<"ERROR in AnalysisMuonConfigurableScaleFactors: Replica required not generated! Max replica is : "<<m_nreplica<<endl;
      nr=m_nreplica-1;
      if(nr<0) nr=0;
    }

  std::pair<int,int> bin=get_pt_eta_phi_bin_index(charge,tlv);
  if(bin.first<0 || bin.second<0) return 1.;
  return m_effdata_replica[bin.first][bin.second][nr];

}


//*****************************************************************************

////////////////////////
// METHOD dataEffReplica //
////////////////////////

double Analysis::AnalysisMuonConfigurableScaleFactors::dataEffReplica(int charge, const TLorentzVector & tlv,
									  std::string period, int nr) const {

  if(m_configuration!=PerPeriod) cout<<"ERROR in AnalysisMuonConfigurableScaleFactors; Using wrong dataEffReplica method for configuration"<<endl;
  if(!m_FileWithEffi) cout<<"ERROR in AnalysisMuonConfigurableScaleFactors::dataEff method: input file has no efficiency information"<<endl;
  if(nr>=m_nreplica) 
    {
      cout<<"ERROR in AnalysisMuonConfigurableScaleFactors: Replica required not generated! Max replica is : "<<m_nreplica<<endl;
      nr=m_nreplica-1;  
      if(nr<0) nr=0;
    }

  TString temp=period;
  temp.ToLower();

  std::pair<int,int> bin=get_pt_eta_phi_bin_index(charge,tlv,temp);
  if(bin.first<0 || bin.second<0) return 1.;
  return m_effdata_replica[bin.first][bin.second][nr];


}


////////////////////////
// METHOD dataEffReplica //
////////////////////////

double Analysis::AnalysisMuonConfigurableScaleFactors::dataEffReplica(int charge, const TLorentzVector & tlv,
									  int run, int nr) const {

  if(m_configuration!=PerRun) cout<<"ERROR in AnalysisMuonConfigurableScaleFactors; Using wrong dataEffReplica method for configuration"<<endl;
  if(!m_FileWithEffi) cout<<"ERROR in AnalysisMuonConfigurableScaleFactors::dataEff method: input file has no efficiency information"<<endl;
  if(nr>=m_nreplica) 
    {
      cout<<"ERROR in AnalysisMuonConfigurableScaleFactors: Replica required not generated! Max replica is : "<<m_nreplica<<endl;
      nr=m_nreplica-1;
      if(nr<0) nr=0;
    }

  std::pair<int,int> bin=get_pt_eta_phi_bin_index(charge,tlv,"",run);
  if(bin.first<0 || bin.second<0) return 1.;
  return m_effdata_replica[bin.first][bin.second][nr];

}

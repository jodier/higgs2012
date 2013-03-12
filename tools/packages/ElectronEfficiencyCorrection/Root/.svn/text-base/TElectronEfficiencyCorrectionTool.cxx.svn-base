/**
   @class TElectronEfficiencyCorrectionTool
   @brief Calculate the egamma scale factors in pure ROOT

   @author Karsten Koeneke, Felix Buehrer
   @date   July 2012
*/


// This class header
#include "ElectronEfficiencyCorrection/TElectronEfficiencyCorrectionTool.h"

// STL includes
#include <iostream>
#include <cfloat>
#include <math.h>
#include <limits.h>

// ROOT includes
#include "TString.h"
#include "TSystem.h"
#include "TObjString.h"
#include "TROOT.h"
#include "TFile.h"
#include "TH2.h"
#include "TClass.h"


//=============================================================================
// Constructor
//=============================================================================
Root::TElectronEfficiencyCorrectionTool::TElectronEfficiencyCorrectionTool(const char* name) :
  Root::TCalculatorToolBase(name),
  m_debug(false),
  m_isInitialized(false),
  m_resultPrefix("efficiencySF_"),
  m_resultName(""),
  m_position_eff(0),
  m_position_err(0),
  objsFull(0),
  objsFast(0)
{
}



//=============================================================================
// Destructor
//=============================================================================
Root::TElectronEfficiencyCorrectionTool::~TElectronEfficiencyCorrectionTool()
{
  if (objsFull) delete objsFull;
  if (objsFast) delete objsFast;
}




//=============================================================================
// Initialize this correction tool
//=============================================================================
int Root::TElectronEfficiencyCorrectionTool::initialize()
{
  // use an int as a StatusCode
  int sc(1);

  if (m_corrFileNameList.size() == 0) {
      std::cerr << "ERROR in " << this->getName() 
                << " (file: " << __FILE__ << ", line: " << __LINE__ << ") "
                << "! No file added!" << std::endl;
      return 0;
  }
  if (m_debug){ std::cout << this->getName() << " initialized with " << m_corrFileNameList.size() << " configuration file(s" << std::endl; }

  // Load the needed histograms
  if ( 0 == this->getHistograms() )
    {
      std::cerr << "ERROR in " << this->getName() 
                << " (file: " << __FILE__ << ", line: " << __LINE__ << ") "
                << "! Problem when calling getHistograms()!" << std::endl;
      return 0;
    }

  // --------------------------------------------------------------------------
  // Register the cuts and check that the registration worked:
  // NOTE: THE ORDER IS IMPORTANT!!! Cut0 corresponds to bit 0, Cut1 to bit 1,...
  m_position_eff = m_result.addResult( (m_resultPrefix+m_resultName).c_str(), "efficiency scale factor" );
  if ( m_position_eff < 0 ) sc = 0; // Exceeded the number of allowed results

  m_position_err = m_result.addResult( (m_resultPrefix+m_resultName+"_err").c_str(), "efficiency scale factor uncertainty" );
  if ( m_position_err < 0 ) sc = 0; // Exceeded the number of allowed results

  // Set the results to default values
  m_result.setResult( m_position_eff, 1.0  );
  m_result.setResult( m_position_err, 0.0  );

  m_isInitialized = kTRUE;
  return sc;
}






//=============================================================================
// Calculate the actual accept of each cut individually.
//=============================================================================
const Root::TResult& Root::TElectronEfficiencyCorrectionTool::calculate( const PATCore::ParticleDataType::DataType dataType,
                                                                         const unsigned int runnumber,
                                                                         const double cluster_eta,
                                                                         const double et /* in MeV */
                                                                         )
{
  //check if a file is given and tool correctly initialized
  if ( !m_isInitialized ) {
      std::cerr << "ERROR in " << this->getName() 
                << " (file: " << __FILE__ << ", line: " << __LINE__ << ") "
                << " Tool not correctly initialized or no scale factor file given. "
                << " Returning 0!" << std::endl;
      return m_result;
  }
    
  // Reset the results to default values
  m_result.setResult( m_position_eff, 1.0  );
  m_result.setResult( m_position_err, 0.0  );

  // If we have real data, we don't need to scale anything and return the default values
  if ( dataType == PATCore::ParticleDataType::Data ) return m_result;

  // Check if we have fast simulation at hand
  if ( dataType == PATCore::ParticleDataType::FastShower )
  {
      std::cerr << "ERROR in " << this->getName() 
                << " (file: " << __FILE__ << ", line: " << __LINE__ << ") "
                << " Fast shower scale factors not available. Please check your data type "
                << " Returning default scale factor 1.0 with uncertainty 0.0" << std::endl;
      return m_result;


  }
  bool isFastSim(false);
  if ( dataType == PATCore::ParticleDataType::Fast )
    {
      isFastSim = true;
    }


  // Find the right run number range and the corresponding histogram
  const TObjArray* thisHists(NULL);
  const TH2* thisHist(NULL);
  if ( isFastSim )
    {
      for ( unsigned int i=0; i<m_begRunNumberListFastSim.size(); ++i )
        {
          if ( m_begRunNumberListFastSim[i] <= runnumber && runnumber <= m_endRunNumberListFastSim[i] )
            {

              thisHists = m_fastHistList[i];
              break;
            }
        }
    }
  else
    {
      for ( unsigned int i=0; i<m_begRunNumberList.size(); ++i )
        {
          if ( m_begRunNumberList[i] <= runnumber && runnumber <= m_endRunNumberList[i] )
            {
              thisHists = m_histList[i];
              break;
            }
        }
    }


  // If no valid hist, then, run number was out of range
  if ( thisHists == 0 )
    {
      std::cerr << "ERROR in " << this->getName() 
                << " (file: " << __FILE__ << ", line: " << __LINE__ << ") "
                << "! No valid histogram found for the current run number: " << runnumber
                << " for simulation type: " << dataType
                << " Returning default scale factor 1.0 with uncertainty 0.0" << std::endl;
      return m_result;
    }

  // Get the actual scale factor and its uncertainty from the current histogram
  double xValue,xValue_old,yValue;
  xValue = et;
  xValue_old = xValue;
  yValue = cluster_eta;
  int smallEt(0), etaCov(0), nSF(0);

  bool block = kFALSE;
  bool changed = kFALSE;
  for ( int i=0; i<thisHists->GetEntries(); i++){
    TH2* tmpHist = (TH2*)thisHists->At(i);
    block = kFALSE;
    if (xValue_old < tmpHist->GetXaxis()->GetXmin()){
      smallEt++;
      block = kTRUE;
    }
    if (xValue > tmpHist->GetXaxis()->GetXmax() || changed)
    {
      if (changed){
        if (xValue_old > tmpHist->GetXaxis()->GetXmax()) {
          xValue = tmpHist->GetXaxis()->GetBinCenter(tmpHist->GetNbinsX());
        }
        else xValue = xValue_old;
      }
      else  xValue = tmpHist->GetXaxis()->GetBinCenter(tmpHist->GetNbinsX());
      changed = kTRUE;
    }

    if (TMath::Abs(yValue) > tmpHist->GetYaxis()->GetXmax()){
      etaCov++;
      block = kTRUE;
    }

    if (!block) {
      thisHist = tmpHist;
      if (!changed) nSF++;
    }
  }
  
  if (smallEt == thisHists->GetEntries())
    {
      if (m_debug){ std::cout<<"No correction factor provided for et="<<xValue<<" , returning 1.0 +- 0"<<std::endl; }
      return m_result;
    }
  if (etaCov == thisHists->GetEntries())
    {
      if (m_debug){ std::cout<<"No correction factor provided for eta="<<yValue<<" , returning 1.0 +- 0"<<std::endl; }
      return m_result;
    }

  if (nSF > 1)
    {
      std::cout<<"More than 1 SF found for eta="<<yValue<<" , et = "<<xValue_old<<" , run number = "<<runnumber<<" . Please check your input files!"<<std::endl;
    }

  
  // If SF is only given in Abs(eta) convert eta input to TMath::Abs()
  float epsilon = 1e-6;
  if (thisHist->GetYaxis()->GetBinLowEdge(1) >= 0-epsilon ){
    if (m_debug){ std::cout<<"Scale factor only measured in Abs(eta) changing eta from "<<yValue<<" to "<<TMath::Abs(yValue)<<std::endl; }
    yValue = TMath::Abs(yValue);
    }
  int globalBinNumber = thisHist->FindFixBin( xValue, yValue );
  double scaleFactor = thisHist->GetBinContent( globalBinNumber );
  double scaleFactorErr = thisHist->GetBinError( globalBinNumber );


  // Write the retrieved values into the return object
  m_result.setResult( m_position_eff, scaleFactor );
  m_result.setResult( m_position_err, scaleFactorErr );

  return m_result;
}






//=============================================================================
// Get the input histograms from the input files
//=============================================================================
int Root::TElectronEfficiencyCorrectionTool::getHistograms()
{

  // Cache the current directory in the root file
  TDirectory* origDir = gDirectory;

  //-------------------------------------------------------
  // Get the name of the first input ROOT file and 
  // interpret from that what we have:
  // efficiency vs. efficiencySF; offline vs. trigger; medium, loose,...
  //-------------------------------------------------------
  if ( !m_corrFileNameList.empty() )
    {
      TString firstFileNameAndPath = m_corrFileNameList[0].c_str();
      TObjArray* myStringList = firstFileNameAndPath.Tokenize("/");
      int lastIdx      = myStringList->GetLast();
      TString fileName = ((TObjString*)myStringList->At(lastIdx))->GetString();
      TObjArray* myFileNameTokensList = fileName.Tokenize(".");
      if ( m_resultPrefix.empty() )
        { // Only overwrite it if the user didn't explicitly set it
          m_resultPrefix = ((TObjString*)myFileNameTokensList->At(0))->GetString();
          m_resultPrefix += "_";
        }
      if ( m_resultName.empty() )
        { // Only overwrite it if the user didn't explicitly set it
          m_resultName = ((TObjString*)myFileNameTokensList->At(1))->GetString() 
            + "_" + ((TObjString*)myFileNameTokensList->At(2))->GetString();
        }
      if (m_debug){ std::cout << "Using resultPrefix: " << m_resultPrefix 
                              << " and resultName: " << m_resultName << std::endl; }
    }

  //-------------------------------------------------------
  // Get all ROOT files and histograms
  //-------------------------------------------------------

  for ( unsigned int i=0; i<m_corrFileNameList.size(); ++i )
    {
      // Load the ROOT file
      const char* fname;
      fname = gSystem->ExpandPathName( m_corrFileNameList[i].c_str() );
      TFile* rootFile = TFile::Open( fname, "READ" );
      if ( !rootFile )
        {
          std::cerr << "ERROR in " << this->getName() 
                    << " (file: " << __FILE__ << ", line: " << __LINE__ << ") "
                    << "! No ROOT file found here: " << m_corrFileNameList[i] << std::endl;
          return 0;
        }


      // Loop over all directories inside the root file (correspond to the run number ranges
      TIter nextdir(rootFile->GetListOfKeys());
      TKey *dir;
      TObject *obj;
      TObjArray* dirNameArray = 0;
      while ( (dir = (TKey*)nextdir()) )
        {          
          obj = dir->ReadObj();
          if ( obj->IsA()->InheritsFrom( "TDirectory" ) )
          {
            dirNameArray = TString(obj->GetName()).Tokenize("_");
            int lastIdx = dirNameArray->GetLast();
            if ( lastIdx != 1 )
            {
              std::cerr << "ERROR in " << this->getName() 
                        << " (file: " << __FILE__ << ", line: " << __LINE__ << ") "
                        << "! The folder name seems to have the wrong format! Directory name:"
                        << obj->GetName() << std::endl;
              return 0;
            }
            rootFile->cd(obj->GetName());
            if ( 0 == this->setupHistogramsInFolder(dirNameArray,lastIdx) )
            {
              std::cerr << "ERROR in "<<this->getName()
                        << " (file: "<< __FILE__ << ",line: "<< __LINE__ <<") "
                        << "unable to setup the histograms in directory " << dir->GetName() << std:: endl;
              return 0;
            }
          }
          else
          {
              std::cerr << "ERROR in "<<this->getName()
                        << " (file: "<< __FILE__ << ",line: "<< __LINE__ <<") "
                        << "Wrong file content! Expected only Directories " << gDirectory->cd() << std:: endl;
              return 0;
          }
          // Return to the original ROOT directory
          gDirectory = origDir;
        } // End: directory loop
        delete dirNameArray;
        delete rootFile;
      } //End: file loop


  // TO DO: Make sure that we don't have any overlapping run-number ranges


  return 1;
}

//=============================================================================
// Get the input histograms from a given folder/run number range
//=============================================================================
int Root::TElectronEfficiencyCorrectionTool::setupHistogramsInFolder(TObjArray* dirNameArray, int lastIdx)
{
  objsFull = new TObjArray();
  objsFast = new TObjArray();
  m_runNumBegin = -1;
  TString myBegRunNumString = ((TObjString*)dirNameArray->At(lastIdx-1))->GetString();
  if ( myBegRunNumString.IsDigit() )
    {
      m_runNumBegin = myBegRunNumString.Atoi();
    }
  m_runNumEnd = -1;
  TString myEndRunNumString = ((TObjString*)dirNameArray->At(lastIdx))->GetString();
  if ( myEndRunNumString.IsDigit() )
    {
      m_runNumEnd = myEndRunNumString.Atoi();
    }
  if ( m_runNumBegin < 0 || m_runNumEnd < 0 || m_runNumEnd < m_runNumBegin )
    {
      std::cerr << "ERROR in " << this->getName() 
                << " (file: " << __FILE__ << ", line: " << __LINE__ << ") "
                << "! Could NOT interpret the run number range: " << m_runNumBegin
                << " - " << m_runNumEnd << std::endl;
      return 0;
    }
  
    TIter nextkey(gDirectory->GetListOfKeys());
    TKey *key;
    TObject *obj(NULL);
    while ( (key = (TKey*)nextkey()) )
    {
      obj = key->ReadObj();
      if ( obj->IsA()->InheritsFrom( "TH1" ) )
      {
        //The histogram containing the scale factors need to end with _sf and need to contain either the string "FullSim" or "AtlFast2"!
        if ( TString(obj->GetName()).EndsWith("_sf"))
        {
          if (TString(obj->GetName()).Contains("FullSim"))
          {
            objsFull->Add(obj);

          }
          else if (TString(obj->GetName()).Contains("AtlFast2"))
          {
            objsFast->Add(obj);
          }
          else
          {
            std::cerr << "ERROR in " << this->getName() 
                      << " (file: " << __FILE__ << ", line: " << __LINE__ << ") "
                      << "! Could NOT interpret if the histogram: " << obj->GetName()
                      << " is full or fast simulation!" << std::endl;
            return 0;
          }
        }
      }
    }

    if ( 0 == this->setup( objsFull, m_histList, m_begRunNumberList, m_endRunNumberList) )
    {
      std::cerr << "ERROR in " << this->getName() 
                << " (file: " << __FILE__ << ", line: " << __LINE__ << ") "
                << "! Could NOT setup histogram " << obj->GetName()
                << " for full sim!" << std::endl;
      return 0;
    }

    if ( 0 == this->setup( objsFast, m_fastHistList, m_begRunNumberListFastSim, m_endRunNumberListFastSim) )
    {
      std::cerr << "ERROR in " << this->getName() 
                << " (file: " << __FILE__ << ", line: " << __LINE__ << ") "
                << "! Could NOT setup histogram " << obj->GetName()
                << " for fast sim" << std::endl;
      return 0;
    }


  return 1;
}


//=============================================================================
// Fill and interpret the setup, depending on which histograms are found in the input file(s)
//=============================================================================
int Root::TElectronEfficiencyCorrectionTool::setup( TObjArray* hists,
                                                    std::vector< const TObjArray* >& histList,
                                                    std::vector< unsigned int >& beginRunNumberList,
                                                    std::vector< unsigned int >& endRunNumberList )
{
  if ( !hists )
    {
      std::cerr << "ERROR in " << this->getName() 
                << " (file: " << __FILE__ << ", line: " << __LINE__ << ") "
                << "! Could NOT find histogram with name *_sf in folder" << std::endl;
      return 0;
    }
  TH2 *tmpHist(0);
  for (int i=0; i<hists->GetEntries(); i++)  {
    tmpHist = (TH2*)hists->At(i);
    tmpHist->SetDirectory(0);
  }
  // Now, we have all the needed info. Fill the vectors accordingly
  histList.push_back( hists );
  if (beginRunNumberList.size()>0){
    if (m_runNumBegin != (int)beginRunNumberList.back()) beginRunNumberList.push_back( m_runNumBegin );
  }
  else beginRunNumberList.push_back( m_runNumBegin );
  if (endRunNumberList.size()>0 ){
    if ( m_runNumEnd != (int)endRunNumberList.back()) endRunNumberList.push_back( m_runNumEnd );
  }
  else endRunNumberList.push_back( m_runNumEnd );


  return 1;
}

/**
   @class AthElectronEfficiencyCorrectionTool
   @brief Calculate the egamma scale factors in Athena

   @author Karsten Koeneke
   @date   January 2013
*/

// Include this class's header
#include "ElectronEfficiencyCorrection/AthElectronEfficiencyCorrectionTool.h"

// STL includes
#include <string>
#include <cfloat>
//#include <climits>
#include <iostream>
#include <limits.h>

// Include the return object
#include "PATCore/TResult.h"
#include "PATCore/PATCoreEnums.h"

// Atlas includes
#include "EventKernel/INavigable4Momentum.h"
#include "egammaEvent/egamma.h"
#include "CaloEvent/CaloCluster.h"
#include "EventInfo/EventInfo.h"
#include "EventInfo/EventType.h"
#include "EventInfo/EventID.h"
#include "PathResolver/PathResolver.h"
#include "Navigation/IAthenaBarCode.h"
#include "AthenaKernel/IUserDataSvc.h"

// ROOT includes
#include "TSystem.h"



// =============================================================================
// Standard constructor
// =============================================================================
AthElectronEfficiencyCorrectionTool::AthElectronEfficiencyCorrectionTool( const std::string& type,
                                                                          const std::string& name,
                                                                          const IInterface* parent ):
  AthAlgTool(type, name, parent),
  m_rootTool(0)
{
  // Declare to the framework which interface this tools has
  declareInterface<IAthCalculatorTool>(this);
  declareInterface<IUserDataCalcTool>(this);

  // Create an instance of the underlying ROOT tool
  m_rootTool = new Root::TElectronEfficiencyCorrectionTool( ("T"+(this->name())).c_str() );

  // Declare the needed properties
  declareProperty( "CorrectionFileNameList", m_corrFileNameList,
                   "List of file names that store the correction factors for simulation.");

  declareProperty( "ForceDataType", m_dataTypeOverwrite=-1,
                   "Force the DataType of the electron to specified value (to circumvent problem of incorrect DataType for forward electrons in some old releases)");

  declareProperty( "ResultPrefix",       m_resultPrefix="", "The prefix string for the result");
  declareProperty( "ResultName",         m_resultName="",                "The string for the result");

}




// =============================================================================
// Standard destructor
// =============================================================================
AthElectronEfficiencyCorrectionTool::~AthElectronEfficiencyCorrectionTool()
{
  if ( m_rootTool ) delete m_rootTool;
}




// =============================================================================
// Athena initialize method
// =============================================================================
StatusCode AthElectronEfficiencyCorrectionTool::initialize()
{
  // Do some consistency checks
  bool allOK(true);
  if ( m_corrFileNameList.empty() )
    {
      ATH_MSG_ERROR ( "FullSimCorrectionFileNameList is empty! Please configure it properly..." );
      allOK = false;
    }

  // Stop here if the user configuration is wrong
  if ( !allOK ) return StatusCode::FAILURE;


    
    // Resolve the paths to the input files for the full Geant4 simualtion corrections
  for ( unsigned int i=0; i<m_corrFileNameList.size(); ++i )
    { 
      std::string& curFName = m_corrFileNameList[i];
      const char* fname;
      if ( curFName.find("/")==0 || curFName.find("$")==0 || curFName.find(".")==0 || curFName.find(":")!=std::string::npos )
        {
          fname = gSystem->ExpandPathName( curFName.c_str() );
        }
      else
        {
          curFName = PathResolverFindXMLFile( curFName );
          if ( curFName.empty() )
            {
              ATH_MSG_WARNING ( "Could NOT resolve file name " << m_corrFileNameList[i] );
            }
          fname = curFName.c_str();
        }
      m_corrFileNameList[i] = fname;
    }


  // Configure the underlying Root tool
  for ( unsigned int i=0; i<m_corrFileNameList.size(); ++i )
    {
      m_rootTool->addFileName( m_corrFileNameList[i] );
    }

  m_rootTool->setResultPrefix( m_resultPrefix );
  m_rootTool->setResultName( m_resultName );

  // Forward the message level
  bool debug(false);
  if ( this->msgLvl(MSG::VERBOSE) || this->msgLvl(MSG::DEBUG) ){ debug = true; }
  m_rootTool->setDebug(debug);

  // We need to initialize the underlying ROOT TSelectorTool
  if ( 0 == m_rootTool->initialize() )
    {
      ATH_MSG_ERROR("Could not initialize the TElectronEfficiencyCorrectionTool!");
      return StatusCode::FAILURE;
    }

  // Copy the now filled TResult to the dummy
  m_resultDummy = m_rootTool->getTResult();

  return StatusCode::SUCCESS ;
}





// =============================================================================
// Athena finalize method
// =============================================================================
StatusCode AthElectronEfficiencyCorrectionTool::finalize()
{
  if ( !(m_rootTool->finalize()) )
    {
      ATH_MSG_ERROR("Something went wrong at finalize!");
      return StatusCode::FAILURE;
    }

  return StatusCode::SUCCESS ;
}





// =============================================================================
// The main accept method: the actual cuts are applied here 
// =============================================================================
const Root::TResult& AthElectronEfficiencyCorrectionTool::calculate( const egamma* egam )
{
  if ( !egam )
    {
      ATH_MSG_ERROR ( "Did NOT get a valid egamma pointer!" );
      return m_resultDummy;
    }
  
  // Here, you have to make the translation from the ATLAS EDM object to the variables of simple type

  // Get the run number 
  // Get the EventInfo object
  const EventInfo* eventInfo(NULL);
  if ( !((evtStore()->retrieve(eventInfo)).isSuccess()) )
    {
      ATH_MSG_ERROR ( "Could not retrieve EventInfo object!" );
      return m_resultDummy;
    }
  const unsigned int runnumber = eventInfo->event_ID()->run_number();


  // Get the needed values from the egamma object
  double cluster_eta(-9999.9);
  double et(0.0);

  const CaloCluster* cluster(NULL);
  cluster = egam->cluster();
  if ( cluster )
    {
      cluster_eta = cluster->eta(); // Not etaS2????

      // Do the by-hand et calculation (stupid!!!)
      const egamma::momentum_type& uncombined = egam->get4Mom(egamma::Uncombined);
      double trackCoshEta = cosh( uncombined.eta() );
      if ( trackCoshEta != 0.0 )
        {
          et = cluster->e()/trackCoshEta;
        }
    }

  // Get the DataType of the current egamma object
  PATCore::ParticleDataType::DataType dataType = (PATCore::ParticleDataType::DataType) (egam->dataType());
  ATH_MSG_VERBOSE( "The egamma object with author=" << egam->author()
                   << " has PATCore::ParticleDataType::DataType=" << dataType
                   << " and EventKernel::ParticleDataType::DataType=" << egam->dataType() );
  if ( m_dataTypeOverwrite >= 0 ) dataType = (PATCore::ParticleDataType::DataType)m_dataTypeOverwrite;

      
  // Call the ROOT tool to get an answer
  return m_rootTool->calculate( dataType,
                                runnumber,
                                cluster_eta,
                                et /* in MeV */
                                );
  
}



// =============================================================================
// Method to calculate the user data for each egamma object
// =============================================================================
StatusCode AthElectronEfficiencyCorrectionTool::calculateElementUserData( const IAthenaBarCode* abc )
{
  // Check that we got a valid pointer
  if ( !abc )
    {
      ATH_MSG_ERROR ( "Did not get a valid IAthenaBarCode pointer!" );
      return StatusCode::FAILURE;
    }

  // Make sure we have an egamma object
  const egamma* egam = dynamic_cast<const egamma*>(abc);
  if ( !egam )
    {
      ATH_MSG_ERROR ( "Could not cast to const egamma pointer!" );
      return StatusCode::FAILURE;
    }

  // Calculate the scale factor and uncertainty
  const Root::TResult& myTResult = this->calculate( egam );

  // Extract the scale factor, its uncertainty, and their names
  const double scaleFactor = myTResult.getScaleFactor();
  const double scaleFactorErr = myTResult.getTotalUncertainty();
  const std::string& scaleFactorName = (myTResult.getResultName(0)).Data();
  const std::string& scaleFactorErrName = (myTResult.getResultName(1)).Data();

  // Store both the scale factor and its uncertainty into UserData
  ATH_CHECK( userStore()->record( *abc, scaleFactorName, scaleFactor ) );
  ATH_MSG_DEBUG ( "Recorded " << scaleFactorName << " to UserData with value: " << scaleFactor );
  ATH_CHECK( userStore()->record( *abc, scaleFactorErrName, scaleFactorErr ) );
  ATH_MSG_DEBUG ( "Recorded " << scaleFactorErrName << " to UserData with value: " << scaleFactorErr );


  return StatusCode::SUCCESS;
}

// Dear emacs, this is -*-c++-*-

#ifndef __ATHELECTRONEFFICIENCYCORRECTIONTOOL__
#define __ATHELECTRONEFFICIENCYCORRECTIONTOOL__

/**
   @class AthElectronEfficiencyCorrectionTool
   @brief Calculate the egamma scale factors in Athena

   @author Karsten Koeneke
   @date   January 2013
*/

// STL includes
#include <vector>
#include <string>

// Include the return object and the underlying ROOT tool
#include "PATCore/TResult.h"
#include "ElectronEfficiencyCorrection/TElectronEfficiencyCorrectionTool.h"

// Include the interface for this class
#include "PATCore/IAthCalculatorTool.h"
#include "UserDataUtils/IUserDataCalcTool.h"

// Atlas includes
#include "EventKernel/INavigable4Momentum.h"
#include "egammaEvent/egamma.h"

// Tools
#include "AthenaBaseComps/AthAlgTool.h"


// Forward declarations
class IUserDataSvc;
class IAthenaBarCode;




class AthElectronEfficiencyCorrectionTool
  : virtual public IAthCalculatorTool,
    virtual public IUserDataCalcTool,
            public AthAlgTool
{

public:
  /// Standard constructor
  AthElectronEfficiencyCorrectionTool ( const std::string& type,
                                              const std::string& name,
                                              const IInterface* parent );

  /// Standard destructor
  virtual ~AthElectronEfficiencyCorrectionTool();


public:
  /// Gaudi Service Interface method implementations
  virtual StatusCode initialize();

  /// Gaudi Service Interface method implementations
  virtual StatusCode finalize();


  // Main methods from IUserDataCalcTool
public:
  /// Method to calculate the user data for each egamma object
  virtual StatusCode calculateElementUserData( const IAthenaBarCode *abc );

  /// Method to calculate event user data
  virtual StatusCode calculateEventUserData( );


  // Main methods from IAthCalculatorTool
public:
  /// The main calculate method: the actual correction factors are determined here
  const Root::TResult& calculate( const INavigable4Momentum* part );
  const Root::TResult& calculate( const egamma* egam );


  // Public methods
public:
  /// Method to get the underlying ROOT tool
  inline Root::TElectronEfficiencyCorrectionTool* getRootTool() { return m_rootTool; }


  /// Method to get the plain TResult
  virtual const Root::TResult& getTResult( )
  {
    return this->getRootTool()->getTResult();
  }


  // Private tools
private:

  

  // Private member variables
private:
  /// Pointer to the underlying ROOT based tool
  Root::TElectronEfficiencyCorrectionTool* m_rootTool;

  /// A dummy return TResult object
  Root::TResult m_resultDummy;


  // Properties

  /// The list of file names
  std::vector< std::string > m_corrFileNameList;


  /// The prefix string for the result
  std::string m_resultPrefix;

  /// The string for the result
  std::string m_resultName;

  /// Force the data type to a given value
  int m_dataTypeOverwrite;


}; // End: class definition


inline StatusCode AthElectronEfficiencyCorrectionTool::calculateEventUserData( )
{
  ATH_MSG_DEBUG ( "There is no point in trying to calculate event user date in this tool..." );
  return StatusCode::SUCCESS;
}



inline const Root::TResult& AthElectronEfficiencyCorrectionTool::calculate( const INavigable4Momentum* part )
{
  const egamma* egam = dynamic_cast<const egamma*>(part);
  if ( egam )
    {
      return calculate(egam);
    } 
  else
    {
      ATH_MSG_ERROR ( " Could not cast to const egamma pointer!" );
      return m_resultDummy;
    }
}

#endif


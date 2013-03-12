#ifndef __TELECTRONEFFICIENCYCORRECTIONTOOL__
#define __TELECTRONEFFICIENCYCORRECTIONTOOL__

/**
   @class TElectronEfficiencyCorrectionTool
   @brief Calculate the egamma scale factors in pure ROOT
   For each scale factor declare a tool and use addFileName to add root files containing scale factors. 
   After adding root files call initialize()
   In the event loop use calculate(const PATCore::ParticleDataType::DataType dataType, const unsigned int runnumber, const double cluster_eta, const double et)
   This returns a TResult. The scale factor and its uncertainty are obtained by calling getScaleFactor() or getTotalUncertainty (See header file of TResult in package PATCore)
   For a short documentation see the included README file

   @author Karsten Koeneke, Felix Buehrer
   @date   January 2013
*/


// STL includes
#include <vector>
#include <string>

// ROOT includes
#include <TString.h>
#include "TKey.h"
#include "TObjArray.h"

// Include the return object and the base class
#include "PATCore/TResult.h"
#include "PATCore/TCalculatorToolBase.h"
#include "PATCore/PATCoreEnums.h"



namespace Root {
  class TElectronEfficiencyCorrectionTool : public Root::TCalculatorToolBase
  {

  public: 
    /** Standard constructor */
    TElectronEfficiencyCorrectionTool( const char* name="TElectronEfficiencyCorrectionTool" );

    /** Standard destructor */
    ~TElectronEfficiencyCorrectionTool();


    // Main methods
  public:
    /** Initialize this class */
    int initialize();

    /** Finalize this class; everything that should be done after the event loop should go here */
    inline int finalize() { return 1; }

    /** The main calculate method: the actual cuts are applied here */
    const Root::TResult& calculate( const PATCore::ParticleDataType::DataType dataType,
                                    const unsigned int runnumber,
                                    const double cluster_eta,
                                    const double et /* in MeV */
                                    );


    // Public methods
  public:
    /// Add an input file
    inline void addFileName ( const std::string& val ) 
      { m_corrFileNameList.push_back(val); }
        


    /// Set the prefix of the result name
    inline void setResultPrefix ( const std::string& val ) { m_resultPrefix = val; }

    /// The string for the result
    inline void setResultName ( const std::string& val ) { m_resultName = val; }


    /// Set the debug flag
    inline void setDebug ( const bool val ){ m_debug = val; }



    // Private methods
  private:
    /// Load all histograms from the input file(s)
    int getHistograms();
    int getHistogramInDirectory( TKey *key );
    int setupHistogramsInFolder( TObjArray* dirNameArray, int lastIdx );

    /// Fill and interpret the setup, depending on which histograms are found in the input file(s)
    int setup( TObjArray* hist,
               std::vector< const TObjArray* >& histList,
               std::vector< unsigned int >& beginRunNumberList,
               std::vector< unsigned int >& endRunNumberList );
    


    // Public members
    //public:
    


    // Private members
  private:

    /// A debug flag: if true, print out more statements
    bool m_debug;
    
    bool m_isInitialized;


    /// The list of file names
    std::vector< std::string > m_corrFileNameList;
    
    /// List of run numbers where histgrams become valid for full simulation
    std::vector< unsigned int > m_begRunNumberList;
    
    /// List of run numbers where histgrams stop being valid for full simulation
    std::vector< unsigned int > m_endRunNumberList;
    

    int m_runNumBegin, m_runNumEnd;
    /// List of run numbers where histgrams become valid for fast simulation
    std::vector< unsigned int > m_begRunNumberListFastSim;
    
    /// List of run numbers where histgrams stop being valid for fast simulation
    std::vector< unsigned int > m_endRunNumberListFastSim;
    
    
    /// List of histograms for full Geant4 simulation
    std::vector< const TObjArray* > m_histList;

    /// List of histograms for fast simulation
    std::vector< const TObjArray* > m_fastHistList;


    /// The prefix string for the result
    std::string m_resultPrefix;

    /// The string for the result
    std::string m_resultName;


    /// The position of the efficiency scale factor in the result
    int m_position_eff; 

    /// The position of the efficiency scale factor uncertainty in the result
    int m_position_err; 

    /// Object arrays holding the sf histograms for full and fast sim
    TObjArray *objsFull, *objsFast;
    
    
  }; // End: class definition
  
} // End: namespace Root

#endif


// Dear emacs, this is -*-c++-*-

#ifndef __TSELECTORTOOLBASE__
#define __TSELECTORTOOLBASE__

/**
   @class TSelectorToolBase
   @brief Bsse class for tools to select objects in pure ROOT

   @author Karsten Koeneke (CERN)
   @date   April 2011
*/

// ROOT includes
#include "TString.h"

// Include the return object
#include "TAccept.h"

// include the configuration in RootCore environment
// if this does not exist, call $ROOTCOREDIR/scripts/compile.sh
// don't just comment out this line
#ifdef ROOTCORE
#include <PATCore/config.h>
#endif

class TObject;


namespace Root {
  class TSelectorToolBase
  {

  public: 
    /** Standard constructor */
    TSelectorToolBase(const char* name="TSelectorToolBase") :
      m_name(name),
      m_accept( Form("%s_TAccept",name) )
    {
    }
    
    /** Standard destructor */
    virtual ~TSelectorToolBase(){}
  

    // Main methods
  public:
    /** Initialize this class */
    virtual int initialize() = 0;

    /** Finalize this class; everything that should be done after the event loop should go here */
    virtual int finalize() = 0;


    /** Get the name of the class instance */
    inline const char* getName() const { return m_name.Data(); };


    /** Method to get the plain TAccept */
    const Root::TAccept& getTAccept( )
    {
      return m_accept;
    }

#ifdef PAT_CORE_D3PDREADER
    /** The generic D3PDReader accept method */
    virtual const Root::TAccept& accept( const TObject& d3pd ) = 0;
#endif


#ifdef ROOTCORE 
    /** For convenient PROOF support */
    ClassDef(TSelectorToolBase,1); 
#endif 


    // Protected members
  protected:
    /** The name of the class instance */
    TString m_name;

    /** The return TAccept object */
    TAccept m_accept;//!


  }; // End: class definition


} // End: namespace Root

#endif

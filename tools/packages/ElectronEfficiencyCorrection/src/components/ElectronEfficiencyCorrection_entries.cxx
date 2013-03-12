#include "GaudiKernel/DeclareFactoryEntries.h"

#include "ElectronEfficiencyCorrection/AthElectronEfficiencyCorrectionTool.h"

DECLARE_TOOL_FACTORY( AthElectronEfficiencyCorrectionTool )


DECLARE_FACTORY_ENTRIES( ElectronEfficiencyCorrection ) 
{
  DECLARE_ALGTOOL( AthElectronEfficiencyCorrectionTool )
}



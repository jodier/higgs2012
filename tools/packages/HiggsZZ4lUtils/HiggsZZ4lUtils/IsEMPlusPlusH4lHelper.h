#ifndef ISEMPLUSPLUSH4LHELPER_H
#define ISEMPLUSPLUSH4LHELPER_H

/********************************************************************


*********************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include "egammaEvent/egamma.h"

namespace isEMPlusPlusH4lHelper{

  bool IsLoosePlusPlusH4l(const egamma* eg,
                          bool debug=false,
                          bool isTrigger=false);

 
}

#endif //

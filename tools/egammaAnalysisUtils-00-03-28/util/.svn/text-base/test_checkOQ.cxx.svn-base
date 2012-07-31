#include <iostream>

#include "egammaAnalysisUtils/checkOQ.h"

using namespace std;

int main(int /* argc */, char** /* argv */){


  double Per1 = 100.;
  double Per2 = 900.;
  double Per3 = 500.;
  double Per4 = 500.;

  egammaOQ myOQ;
  myOQ.setLumiVec(Per1,Per2,Per3,Per4);

  cout << "Run Weight Period 1: " << myOQ.getOQWeight(180164) << endl;
  cout << "Run Weight Period 2: " << myOQ.getOQWeight(183003) << endl;
  cout << "Run Weight Period 3: " << myOQ.getOQWeight(185649) << endl;
  cout << "Run Weight Period 4: " << myOQ.getOQWeight(185761) << endl;
  return 0;


}

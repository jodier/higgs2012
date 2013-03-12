#ifndef ISEMPLUSPLUSH4lDEFS_H
#define ISEMPLUSPLUSH4lDEFS_H

#include <fstream>
#include <iostream>
//----------------------------------------------------------------------------------------

/**

*/
//-------------------------------------------------------------------------------------------------------
class H4l2011Defs{

 public:

  H4l2011Defs(){};
  ~H4l2011Defs(){};

  bool passH4l2011(double eta, double eT,
            double rHad, double rHad1, double Reta, double w2,
            double f1, double wstot, double DEmaxs1, double deltaEta, int nSi,
            int nSiOutliers, int nPix, int nPixOutliers,  bool debug = false,bool isTrigger = false );
  
  
  

 private:
  // Loose++ Helper Functions 
  bool passRHad_looseH4l(double rhad, double rhad1, unsigned int etbin, unsigned int etabin);
  bool passReta_looseH4l(double reta, unsigned int etbin, unsigned int etabin);
  bool passW2_looseH4l(double w2, unsigned int etbin, unsigned int etabin);
  bool passWstot_looseH4l(double wstot, unsigned int etbin, unsigned int etabin);
  bool passEratio_looseH4l(double demaxs1, unsigned int etbin, unsigned int etabin);
  bool passDeltaEta_looseH4l(double deltaEta);
  
  
  // Helper Fuctions
  unsigned int getEtaBinH4l(double eta);
  unsigned int getEtBinH4l(double eT);
}; 
//----------------------------------------------------------------------------------------
#endif

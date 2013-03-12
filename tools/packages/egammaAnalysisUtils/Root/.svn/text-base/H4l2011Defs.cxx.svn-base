#include "egammaAnalysisUtils/H4l2011Defs.h"
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;
//----------------------------------------------------------------------------------------
bool H4l2011Defs::passH4l2011(double eta, double eT,
                                               double rHad, double rHad1, double Reta, double w2, 
                                               double f1, double wstot, double DEmaxs1, double deltaEta, int nSi, int nSiOutliers, 
                                               int nPix, int nPixOutliers, bool debug, bool isTrigger  
                                               ) {
  
  unsigned int eTBin = getEtBinH4l(eT);
  // The e20_loose++ trigger uses the 20-30 GeV bin cuts for all electrons. 
  if(isTrigger){
    eTBin = getEtBinH4l(21*1000);
  }
  
  unsigned int etaBin = getEtaBinH4l(eta);

  // RHad
  if(!passRHad_looseH4l(rHad,rHad1,eTBin,etaBin)){
    if(debug){
      std::cout << "Failed RHad " << rHad << " " << eT << " " << eta << " " << std::endl;
    }
    return false;
  }

  // Reta 
  if(!passReta_looseH4l(Reta,eTBin,etaBin)){
    if(debug){
      std::cout << "Failed Reta " << Reta << " " << eT << " " << eta << " " << std::endl;
    }
    return false;
  }

  // w2
  if(!passW2_looseH4l(w2,eTBin,etaBin)){
    if(debug)
      std::cout << "Failed w2 " << w2 << " " << eT << " " << eta << " " << std::endl;
    return false;
  }

  // Check the energy in the strips before cutting on it
  if(f1 > 0.005){
    // wstot
    if(!passWstot_looseH4l(wstot,eTBin,etaBin)){
      if(debug)
	std::cout << "Failed wstot " << wstot << " " << eT << " " << eta << " " << std::endl;
      return false;
    }

    // Eratio
    if(!passEratio_looseH4l(DEmaxs1,eTBin,etaBin)){
      if(debug){
	std::cout << "Failed DEmaxs1 " << DEmaxs1 << " " << eT << " " << eta << " " << std::endl;
      }
      return false;
    }
  }
  
  // Delta Eta
  if(!passDeltaEta_looseH4l(deltaEta)){
    if(debug){
      std::cout << "Failed dEta " << deltaEta << " " << eT << " " << eta << " " << std::endl;
    }
    return false;
  }

  // Si
  if(nSi + nSiOutliers  < 7){
    if(debug){
      std::cout << "Failed nSi " << nSi + nSiOutliers << " " << eT << " " << eta << " " << std::endl;
    }
    return false;
  }
 
  // Pix
  if(nPix+nPixOutliers < 1){
    if(debug){
	std::cout << "Failed nPix " << nPix << " " << eT << " " << eta << " " << std::endl;
    }
      return false;
  }


  return true;
}


//---------------------------------------------------------------------------------------
// Gets the Eta bin [0-9] given the eta
unsigned int H4l2011Defs::getEtaBinH4l(double eta){
  const unsigned int nEtaBins = 10;
  const double etaBins[nEtaBins] = {0.1,0.6,0.8,1.15,1.37,1.52,1.81,2.01,2.37,2.47};
  
  for(unsigned int etaBin = 0; etaBin < nEtaBins; ++etaBin){
    if(fabs(eta) < etaBins[etaBin])
      return etaBin;
  }
  return 9;
}


//---------------------------------------------------------------------------------------
// Gets the Et bin [0-10] given the et (MeV)
unsigned int H4l2011Defs::getEtBinH4l(double eT){
  const unsigned int nEtBins = 11;
  const double GeV = 1000;
  const double eTBins[nEtBins] = {5*GeV,10*GeV,15*GeV,20*GeV,30*GeV,40*GeV,50*GeV,60*GeV,70*GeV,80*GeV};
  
  for(unsigned int eTBin = 0; eTBin < nEtBins; ++eTBin){
    if(eT < eTBins[eTBin])
      return eTBin;
  }
  
  return 10;
}

//----------------------------------------------------------------------------------------
bool H4l2011Defs::passRHad_looseH4l(double rhad, double rhad1,unsigned int etbin,unsigned int etabin){

  // new values cut on rhad (rows are et bins, columns are eta bins)
  //                               0.0   0.1    0.6    0.8   1.15   1.37   1.52   1.81   2.01  2.37    2.47
  const double cutrhad[11][10]  = {{ 0.031, 0.031, 0.021, 0.021, 0.019, 0.028, 0.065, 0.065, 0.046, 0.034}// < 5
				   ,{0.018, 0.018, 0.016, 0.015, 0.016, 0.028, 0.053, 0.038, 0.028, 0.025} // 5-10 
				   ,{0.018, 0.018, 0.018, 0.020, 0.016, 0.033, 0.036, 0.033, 0.024, 0.025} //10-15
				   ,{0.015, 0.015, 0.015, 0.016, 0.014, 0.029, 0.033, 0.022, 0.019, 0.018} //15-20
				   ,{0.012, 0.012, 0.012, 0.012, 0.012, 0.015, 0.030, 0.022, 0.016, 0.016} //20-30
				   ,{0.011, 0.011, 0.011, 0.011, 0.011, 0.011, 0.021, 0.021, 0.015, 0.015} //30-40
				   ,{0.011, 0.011, 0.011, 0.011, 0.011, 0.011, 0.015, 0.015, 0.010, 0.010} //40-50
				   ,{0.011, 0.011, 0.011, 0.011, 0.011, 0.011, 0.015, 0.015, 0.010, 0.010}// 50-60 
				   ,{0.011, 0.011, 0.011, 0.011, 0.011, 0.011, 0.015, 0.015, 0.010, 0.010}// 60-70 
				   ,{0.011, 0.011, 0.011, 0.011, 0.011, 0.011, 0.015, 0.015, 0.010, 0.010}// 70-80 
				   ,{0.011, 0.011, 0.011, 0.011, 0.011, 0.011, 0.015, 0.015, 0.010, 0.010}};// > 80

  //if 0.8 < event.el_cl_eta and event.el_cl_eta < 1.37:
  //               self.rhad = event.el_ethad/event.el_cl_et

  if(etabin == 3 || etabin == 4){
    if (rhad > cutrhad[etbin][etabin])
      return false;
  } else{
    if(rhad1 > cutrhad[etbin][etabin])
      return false;
  }

  return true;
}

//----------------------------------------------------------------------------------------
bool H4l2011Defs::passReta_looseH4l(double rEta, unsigned int eTBin, unsigned int etaBin){
  // New values cut on ratio e237/e277 (rows are eT bins, columns are eta bins)
  //                               0.0   0.1    0.6    0.8   1.15   1.37   1.52   1.81    2.01   2.37   2.47
  const double cutReta37[11][10] = {{ 0.700, 0.700, 0.700, 0.700, 0.700, 0.690, 0.848, 0.876, 0.870, 0.888}  // < 5
				    ,{0.700, 0.700, 0.700, 0.700, 0.700, 0.715, 0.860, 0.880, 0.880, 0.880}  // 5-10
				    ,{0.875 ,0.875 ,0.875 ,0.875 ,0.875 ,0.740 ,0.860 ,0.875 ,0.870 ,0.870}  //10-15
				    ,{0.900 ,0.900 ,0.895 ,0.895 ,0.890 ,0.740 ,0.880 ,0.900 ,0.880 ,0.880}  //15-20
				    ,{0.910 ,0.910 ,0.910 ,0.910 ,0.910 ,0.750 ,0.890 ,0.900 ,0.890 ,0.890}  //20-30
				    ,{0.920 ,0.920 ,0.920 ,0.915 ,0.915 ,0.790 ,0.895 ,0.915 ,0.895 ,0.890}  //30-40
				    ,{0.920 ,0.920 ,0.920 ,0.915 ,0.915 ,0.790 ,0.895 ,0.915 ,0.895 ,0.890}  //40-50
				    ,{0.920 ,0.920 ,0.920 ,0.915 ,0.915 ,0.790 ,0.895 ,0.915 ,0.895 ,0.890}  // 50-60
				    ,{0.920 ,0.920 ,0.920 ,0.915 ,0.915 ,0.790 ,0.895 ,0.915 ,0.895 ,0.890}  // 60-70 
				    ,{0.920 ,0.920 ,0.920 ,0.915 ,0.915 ,0.790 ,0.895 ,0.915 ,0.895 ,0.890}  // 70-80 
				    ,{0.920 ,0.920 ,0.920 ,0.915 ,0.915 ,0.790 ,0.895 ,0.915 ,0.895 ,0.890}};// 80<   

  if(rEta < cutReta37[eTBin][etaBin])
    return false;

  return true;
}

//----------------------------------------------------------------------------------------
bool H4l2011Defs::passW2_looseH4l(double w2, unsigned int eTBin, unsigned int etaBin){
  
  //New values for cut on shower width in 2nd sampling (rows are eT bins, columns are eta bins)
  //                               0.0   0.1    0.6    0.8   1.15   1.37   1.52   1.81    2.01   2.37   2.47
  const double cutWeta2[11][10] = { {0.014, 0.014, 0.014, 0.014, 0.014, 0.028, 0.017, 0.014, 0.014, 0.014}// < 5 
				   ,{0.014, 0.014, 0.014, 0.014, 0.014, 0.026, 0.017, 0.014, 0.014, 0.014}// 5-10
				   ,{0.014, 0.014 ,0.015 ,0.016 ,0.017 ,0.025 ,0.017 ,0.015 ,0.015 ,0.015}//10-15
				   ,{0.013, 0.013 ,0.015 ,0.016 ,0.017 ,0.025 ,0.017 ,0.015 ,0.015 ,0.014}//15-20
				   ,{0.013 ,0.013 ,0.014 ,0.015 ,0.015 ,0.025 ,0.016 ,0.015 ,0.015 ,0.014}//20-30
				   ,{0.012 ,0.012 ,0.013 ,0.013 ,0.013 ,0.025 ,0.015 ,0.014 ,0.014 ,0.013}//30-40
				   ,{0.011 ,0.011 ,0.012 ,0.013 ,0.013 ,0.025 ,0.015 ,0.014 ,0.014 ,0.013}//40-50
				   ,{0.011 ,0.011 ,0.012 ,0.013 ,0.013 ,0.025 ,0.015 ,0.014 ,0.014 ,0.013}// 50-60
				   ,{0.011 ,0.011 ,0.012 ,0.013 ,0.013 ,0.025 ,0.015 ,0.014 ,0.014 ,0.013}// 60-70 
				   ,{0.011 ,0.011 ,0.012 ,0.013 ,0.013 ,0.025 ,0.015 ,0.014 ,0.014 ,0.013}// 70-80 
				   ,{0.011 ,0.011 ,0.012 ,0.013 ,0.013 ,0.025 ,0.015 ,0.014 ,0.014 ,0.013}};// 80<   

  if(w2 > cutWeta2[eTBin][etaBin])
    return false;
    
  return  true;
}

//----------------------------------------------------------------------------------------
bool H4l2011Defs::passWstot_looseH4l(double wstot, unsigned int eTBin, unsigned int etaBin){
  
  //New values for cut on shower width in 2nd sampling (rows are eT bins, columns are eta bins)
  //                               0.0   0.1    0.6    0.8   1.15   1.37   1.52   1.81    2.01   2.37   2.47
  const double cutWstot[11][10]  = { {9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999.,  9999.} // < 5    GeV
				    ,{9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999.,  9999.} // 5-10   
				    ,{3.20, 3.20, 3.20, 3.85, 3.85, 9999., 3.80, 3.00, 2.00, 9999} //10-15
				    ,{3.00, 3.00, 3.00, 3.75, 3.75, 9999., 3.80, 3.00, 2.00, 9999} //15-20
				    ,{2.90, 2.90, 2.90, 3.50, 3.50, 9999., 3.80, 3.00, 2.00, 9999} //20-30
				    ,{2.80, 2.80, 2.80, 3.30, 3.40, 9999., 3.70, 3.00, 1.70, 9999} //30-40
				    ,{2.80, 2.80, 2.80, 3.20, 3.40, 9999., 3.70, 2.90, 1.60, 9999} //40-50
				    ,{2.80 ,2.80 ,2.80 ,3.20 ,3.40, 9999 , 3.70 ,2.90 ,1.60 ,9999} // 50-60  
				    ,{2.80 ,2.80 ,2.80 ,3.20 ,3.40, 9999 , 3.70 ,2.90 ,1.60 ,9999} // 60-70   
				    ,{2.80 ,2.80 ,2.80 ,3.20 ,3.40, 9999 , 3.70 ,2.90 ,1.60 ,9999} // 70-80   
				    ,{2.80 ,2.80 ,2.80 ,3.20 ,3.40, 9999 , 3.70 ,2.90 ,1.60 ,9999}};// 80<    

  if(wstot > cutWstot[eTBin][etaBin])
    return false;
    
  return  true;
}
//----------------------------------------------------------------------------------------
bool H4l2011Defs::passEratio_looseH4l(double DEmaxs1, unsigned int eTBin, unsigned int etaBin){
  
  //cut on (Emax - Emax2)/(Emax + Emax2) in 1st sampling 
     //                          0.0     0.1    0.6    0.8   1.15   1.37   1.52   1.81    2.01   2.37   2.47 
  const double cutDEmaxs1[11][10] = {{0.390 ,0.390 ,0.200, 0.070 ,0.060, -9999,  0.070, 0.430 ,0.750 ,-9999} // < 5  
				     ,{0.650 ,0.660 ,0.560 ,0.460 ,0.530 ,-9999, 0.600 ,0.680 ,0.750 ,-9999} // 5-10  
				     ,{0.790 ,0.790 ,0.750 ,0.590 ,0.530 ,-9999, 0.600 ,0.790 ,0.840 ,-9999} //10-15
				     ,{0.790 ,0.790 ,0.790 ,0.700 ,0.580 ,-9999, 0.600 ,0.790 ,0.850 ,-9999} //15-20
				     ,{0.800 ,0.800 ,0.820 ,0.720 ,0.650 ,-9999, 0.780 ,0.790 ,0.850 ,-9999} //20-30
				     ,{0.800 ,0.800 ,0.825 ,0.720 ,0.690 ,-9999, 0.780 ,0.810 ,0.880 ,-9999} //30-40
				     ,{0.800 ,0.800 ,0.825 ,0.730 ,0.690 ,-9999, 0.790 ,0.810 ,0.880 ,-9999} //40-50
				     ,{0.800 ,0.800 ,0.825 ,0.730 ,0.690 ,-9999, 0.790 ,0.810 ,0.880 ,-9999} // 50-60  
				     ,{0.800 ,0.800 ,0.825 ,0.730 ,0.690 ,-9999, 0.790 ,0.810 ,0.880 ,-9999} // 60-70
				     ,{0.800 ,0.800 ,0.825 ,0.730 ,0.690 ,-9999, 0.790 ,0.810 ,0.880 ,-9999} // 70-80
				     ,{0.800 ,0.800 ,0.825 ,0.730 ,0.690 ,-9999, 0.790 ,0.810 ,0.880 ,-9999}};// 80<  

  if(DEmaxs1 < cutDEmaxs1[eTBin][etaBin])
    return false;
    
  return  true;
}


//----------------------------------------------------------------------------------------
bool H4l2011Defs::passDeltaEta_looseH4l(double deltaEta){
  
  const double cutDeltaEta = 0.015;

  if(fabs(deltaEta) > cutDeltaEta)
    return false;
    
  return  true;
}

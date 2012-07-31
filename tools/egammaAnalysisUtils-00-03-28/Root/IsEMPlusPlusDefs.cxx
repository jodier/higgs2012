#include "egammaAnalysisUtils/IsEMPlusPlusDefs.h"
#include <iostream>
#include <iomanip>
#include <cmath>


//----------------------------------------------------------------------------------------
bool isTightPlusPlus(double eta, double eT,double f3,
			double rHad, double rHad1, double Reta, double w2, 
			double f1, double wstot, double DEmaxs1, double deltaEta, double d0,
			double TRratio, int nTRT, int nTRTOutliers,
			int nSi,int nSiOutliers, int nPix, int nPixOutliers, 
			int nBlayer, int nBlayerOutliers, bool expectBlayer, double eOverP, double deltaPhi, int convBit,
			egammaMenu::egMenu menu, bool debug, bool isTrigger ){
	
  // testing menu flag
  if (menu != egammaMenu::eg2012 && menu != egammaMenu::eg2011) {
    std::cout << "Menu either needs to be 2012 or 2011: Returning fail" << std::endl;
    return false; 
  }

  // getting et and eta bins  
  unsigned int eTBin = getEtBin(eT);
  unsigned int etaBin = getEtaBin(eta);

  // if primary electron trigger, set et bin constant for 20-30 
  if(isTrigger){
    eTBin = getEtBin(24*1000);
  }
  
  // RHad
  if(!passRHad_tight(rHad,rHad1,eTBin,etaBin, menu)){
    if(debug) std::cout << "Failed RHad " << rHad << " " << eT << " " << eta << " " << std::endl;
    return false;
  }

  // Reta 
  if(!passReta_tight(Reta,eTBin,etaBin, menu)){
    if(debug) std::cout << "Failed Reta " << Reta << " " << eT << " " << eta << " " << std::endl;
    return false;
  }

  // w2
  if(!passW2_tight(w2,eTBin,etaBin, menu)){
    if(debug) std::cout << "Failed w2 " << w2 << " " << eT << " " << eta << " " << std::endl;
    return false;
  }

  // Check the energy in the strips before cutting on it
  if(f1 > 0.005){
    
    // wstot
    if(!passWstot_tight(wstot,eTBin,etaBin, menu)){
      if(debug) std::cout << "Failed wstot " << wstot << " " << eT << " " << eta << " " << std::endl;
      return false;
    }

    // Eratio
    if(!passEratio_tight(DEmaxs1,eTBin,etaBin, menu)){
      if(debug) std::cout << "Failed DEmaxs1 " << DEmaxs1 << " " << eT << " " << eta << " " << std::endl;
      return false;
    }
  }
  
  // Delta Eta--same cuts as medium
  if(!passDeltaEta_med(deltaEta)){
    if(debug) std::cout << "Failed dEta " << deltaEta << " " << eT << " " << eta << " " << std::endl;
    return false;
  }

  // TR
  if(!passTR_tight(TRratio,fabs(eta), menu)){
    if(debug) std::cout << "Failed TR " << TRratio << " " << eT << " " << eta << " " << std::endl;
    return false;
  }

  // Si
  if(nSi+nSiOutliers < 7){
    if(debug) std::cout << "Failed nSi " << nSi+nSiOutliers << " " << eT << " " << eta << " " << std::endl;
    return false;
    }

  // Pix
  if(!passNPix_med(nPix+nPixOutliers, etaBin, menu)) {
    if(debug) std::cout << "Failed nPix " << nPix << " " << eT << " " << eta << " " << std::endl;
    return false;
    }

  // Blayer
  if(expectBlayer && !passNBlayer_tight(nBlayer+nBlayerOutliers,etaBin)){
    if(debug) std::cout << "Failed Bl " << nBlayer << " " << eT << " " << eta << " " << std::endl;
    return false;
  }

  // d0
  if(fabs(d0) > 1){
    if(debug) std::cout << "Failed d0 " << d0 << " " << eT << " " << eta << " " << std::endl;
    return false;
  }

  //E/p
  if(!passEOverP_tight(eOverP,eTBin, etaBin)){
    if(debug) std::cout << "Failed eOverP " << eOverP << " " << eT << " " << eta << " " << std::endl;
    return false;
    }

  //deltaphi
  if(!passDeltaPhi_tight(deltaPhi, eTBin,etaBin)){
    if(debug) std::cout << "Failed deltaPhi " << deltaPhi << " " << eT << " " << eta << " " << std::endl;
    return false;
    }
  
  //convBit
  if (convBit) {
    if(debug) std::cout << "Failed Conversion Bit " << eT << " " << eta << " " << std::endl;
    return false; 
  }

  //nTRT Hits
  if (!passNTRT_tight(nTRT+nTRTOutliers, fabs(eta))) { 
    if(debug) std::cout << "Failed nTRT" << eT << " " << eta << " " << std::endl;
    return false; 
  }

  //pass f3 (energy back compartment) - only for 2012
  if (menu == egammaMenu::eg2012){
    if (!passf3_med(f3, eTBin, etaBin)) { 
      if(debug) std::cout << "Failed f3" << eT << " " << eta << " " << std::endl;
      return false; 
    }
  }

  return true;
}
//-------------------------------------------------------------------------------------------------------
bool isMediumPlusPlus(double eta, double eT, double f3, 
			double rHad, double rHad1, double Reta, double w2, 
			double f1, double wstot, double DEmaxs1, double deltaEta, double d0,
			double TRratio, int nTRT, int nTRTOutliers,
			int nSi, int nSiOutliers, int nPix, int nPixOutliers, 
			int nBlayer, int nBlayerOutliers, bool expectBlayer, 
			egammaMenu::egMenu menu, bool debug, bool isTrigger ){
		      
  // testing menu flag
  if (menu != egammaMenu::eg2012 &&  menu != egammaMenu::eg2011) {
    std::cout << "Menu either needs to be 2012 or 2011: Returning fail" << std::endl;
    return false; 
  }

  unsigned int eTBin = getEtBin(eT);
  unsigned int etaBin = getEtaBin(eta);
  
  // The e24_medium1 trigger uses the 20-30 GeV bin cuts for all electrons. 
  if(isTrigger){
    eTBin = getEtBin(24*1000);
  }

  // RHad
  if(!passRHad_med(rHad,rHad1,eTBin,etaBin, menu)){
    if(debug) std::cout << "Failed RHad " << rHad << " " << eT << " " << eta << " " << std::endl;
    return false;
  }

  // Reta 
  if(!passReta_med(Reta,eTBin,etaBin, menu)){
    if(debug) std::cout << "Failed Reta " << Reta << " " << eT << " " << eta << " " << std::endl;
    return false;
  }

  // w2
  if(!passW2_med(w2,eTBin,etaBin, menu)){
    if(debug) std::cout << "Failed w2 " << w2 << " " << eT << " " << eta << " " << std::endl;
    return false;
  }

  // Check the energy in the strips before cutting on it
  if(f1 > 0.005){

    // wstot
    if(!passWstot_med(wstot,eTBin,etaBin, menu)){
      if(debug) std::cout << "Failed wstot " << wstot << " " << eT << " " << eta << " " << std::endl;
      return false;
    }

    // Eratio
    if(!passEratio_med(DEmaxs1,eTBin,etaBin, menu)){
      if(debug) std::cout << "Failed DEmaxs1 " << DEmaxs1 << " " << eT << " " << eta << " " << std::endl;
      return false;
    }
  }
 
  // f3 (energy back compartment - only for 2012
  if (menu == egammaMenu::eg2012)
  {
    if(!passf3_med(f3,eTBin,etaBin)){
      if(debug) std::cout << "Failed f3 " << f3 << " " << eT << " " << eta << " " << std::endl;
      return false;
    }
  }

  // Delta Eta
  if(!passDeltaEta_med(deltaEta)){
    if(debug) std::cout << "Failed dEta " << deltaEta << " " << eT << " " << eta << " " << std::endl;
    return false;
  }

  // TR
  if(!passTR_med(TRratio,fabs(eta),nTRT+nTRTOutliers, menu)){
    if(debug) std::cout << "Failed TR " << TRratio << " " << eT << " " << eta << " " << std::endl;
    return false;
  }

  // Si
  if(nSi+nSiOutliers < 7){
    if(debug) std::cout << "Failed nSi " << nSi+nSiOutliers << " " << eT << " " << eta << " " << std::endl;
    return false;
  }

  // Pix
   if(!passNPix_med(nPix+nPixOutliers, etaBin, menu)) {
      if(debug)
	    std::cout << "Failed nPix " << nPix << " " << eT << " " << eta << " " << std::endl;
      return false;
    }

  // Blayer
  if(expectBlayer && !passNBlayer_med(nBlayer+nBlayerOutliers,etaBin, menu)){
    if(debug) std::cout << "Failed Bl " << nBlayer << " " << eT << " " << eta << " " << std::endl;
    return false;
  }

  // d0
  if(fabs(d0) > 5){
    if(debug) std::cout << "Failed d0 " << d0 << " " << eT << " " << eta << " " << std::endl;
    return false;
  }

  return true;
}
//----------------------------------------------------------------------------------------
bool isLoosePlusPlus0(double eta, double eT,
		     double rHad, double rHad1, double Reta, double w2, 
		     double f1, double wstot, double DEmaxs1, double deltaEta, int nSi, int nSiOutliers, 
		     int nPix, int nPixOutliers, egammaMenu::egMenu menu, bool debug, bool isTrigger) {

  if (menu != egammaMenu::eg2012 && menu != egammaMenu::eg2011) {
    std::cout << "Menu either needs to be 2012 or 2011: Returning fail" << std::endl;
    return false; 
  } 

  unsigned int eTBin = getEtBin(eT);
  unsigned int etaBin = getEtaBin(eta);
  
  // The e24_loose++ trigger uses the 20-30 GeV bin cuts for all electrons. 
  if(isTrigger){
    eTBin = getEtBin(24*1000);
  }

  // RHad
  if(!passRHad_loose(rHad,rHad1,eTBin,etaBin,menu)){
    if(debug) std::cout << "Failed RHad " << rHad << " " << eT << " " << eta << " " << std::endl;
    return false;
  }

  // Reta 
  if(!passReta_loose(Reta,eTBin,etaBin, menu)){
    if(debug) std::cout << "Failed Reta " << Reta << " " << eT << " " << eta << " " << std::endl;
    return false;
  }

  // w2
  if(!passW2_loose(w2,eTBin,etaBin, menu)){
    if(debug) std::cout << "Failed w2 " << w2 << " " << eT << " " << eta << " " << std::endl;
    return false;
  }

  // Check the energy in the strips before cutting on it
  if(f1 > 0.005){

    // wstot
    if(!passWstot_loose(wstot,eTBin,etaBin,menu)){
      if(debug) std::cout << "Failed wstot " << wstot << " " << eT << " " << eta << " " << std::endl;
      return false;
    }

    // Eratio
    if(!passEratio_loose(DEmaxs1,eTBin,etaBin,menu)){
      if(debug) std::cout << "Failed DEmaxs1 " << DEmaxs1 << " " << eT << " " << eta << " " << std::endl;
      return false;
    }
  }
  
  // Delta Eta
  if(!passDeltaEta_loose(deltaEta)){
    if(debug) std::cout << "Failed dEta " << deltaEta << " " << eT << " " << eta << " " << std::endl;
    return false;
  }

  // Si
  if(nSi+nSiOutliers  < 7){
    if(debug) std::cout << "Failed nSi " << nSi + nSiOutliers << " " << eT << " " << eta << " " << std::endl;
    return false;
    }
 
  // Pix
  if(nPix+nPixOutliers < 1){
    if(debug) std::cout << "Failed nPix " << nPix << " " << eT << " " << eta << " " << std::endl;
    return false;
    }

  return true;
}
//----------------------------------------------------------------------------------------
bool isLoosePlusPlus1(double eta, double eT,
		     double rHad, double rHad1, double Reta, double w2, 
		     double f1, double wstot, double DEmaxs1, double deltaEta, int nSi, int nSiOutliers, 
		     int nPix, int nPixOutliers, egammaMenu::egMenu menu, bool debug, bool isTrigger) {
  
  if (menu != egammaMenu::eg2012 && menu != egammaMenu::eg2011) {
    std::cout << "Menu either needs to be 2012 or 2011: Returning fail" << std::endl;
    return false; 
  } 

  unsigned int eTBin = getEtBin(eT);
  unsigned int etaBin = getEtaBin(eta);
  
  // The e24_loose++ trigger uses the 20-30 GeV bin cuts for all electrons. 
  if(isTrigger){
    eTBin = getEtBin(24*1000);
  }

  // RHad
  if(!passRHad_med(rHad,rHad1,eTBin,etaBin, menu)){
    if(debug) std::cout << "Failed RHad " << rHad << " " << eT << " " << eta << " " << std::endl;
    return false;
  }

  // Reta 
  if(!passReta_med(Reta,eTBin,etaBin, menu)){
    if(debug) std::cout << "Failed Reta " << Reta << " " << eT << " " << eta << " " << std::endl;
    return false;
  }

  // w2
  if(!passW2_loose(w2,eTBin,etaBin, menu)){
    if(debug) std::cout << "Failed w2 " << w2 << " " << eT << " " << eta << " " << std::endl;
    return false;
  }

  // Check the energy in the strips before cutting on it
  if(f1 > 0.005){

    // wstot
    if(!passWstot_loose(wstot,eTBin,etaBin, menu)){
      if(debug) std::cout << "Failed wstot " << wstot << " " << eT << " " << eta << " " << std::endl;
      return false;
    }

    // Eratio
    if(!passEratio_loose(DEmaxs1,eTBin,etaBin, menu)){
      if(debug) std::cout << "Failed DEmaxs1 " << DEmaxs1 << " " << eT << " " << eta << " " << std::endl;
      return false;
    }
  }
  
  // Delta Eta
  if(!passDeltaEta_loose(deltaEta)){
    if(debug) std::cout << "Failed dEta " << deltaEta << " " << eT << " " << eta << " " << std::endl;
    return false;
  }

  // Si
  if(nSi + nSiOutliers  < 7){
    if(debug) std::cout << "Failed nSi " << nSi + nSiOutliers << " " << eT << " " << eta << " " << std::endl;
    return false;
    }
 
  // Pix
  if(nPix+nPixOutliers < 1){
      if(debug) std::cout << "Failed nPix " << nPix << " " << eT << " " << eta << " " << std::endl;
      return false;
    }

  return true;
}
//----------------------------------------------------------------------------------------
bool isLoosePlusPlus(double eta, double eT,
		     double rHad, double rHad1, double Reta, double w2, 
		     double f1, double wstot, double DEmaxs1, double deltaEta, int nSi, int nSiOutliers, 
		     int nPix, int nPixOutliers, egammaMenu::egMenu menu, bool debug, bool isTrigger) {
  
  if (menu == egammaMenu::eg2012)
  {
     if (!isLoosePlusPlus1(eta, eT, rHad, rHad1, Reta, w2, 
		     f1, wstot, DEmaxs1, deltaEta, nSi, nSiOutliers, 
		     nPix, nPixOutliers, menu, debug, isTrigger)) return false; 
  }
  else
  {
     if (!isLoosePlusPlus0(eta, eT, rHad, rHad1, Reta, w2, 
		     f1, wstot, DEmaxs1, deltaEta, nSi, nSiOutliers, 
		     nPix, nPixOutliers, menu, debug, isTrigger)) return false; 
  } 
  return true;
}
//---------------------------------------------------------------------------------------
// Gets the Eta bin [0-9] given the eta
unsigned int getEtaBin(double eta){
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
unsigned int getEtBin(double eT){
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
bool passRHad_tight(double rhad, double rhad1,unsigned int etbin,unsigned int etabin, egammaMenu::egMenu menu){
  
  // values cut on rhad (rows are et bins, columns are eta bins)
  //                               0.0   0.1    0.6    0.8   1.15   1.37   1.52   1.81   2.01  2.37    2.47

  const double cutrhad2011[11][10]  = {{ 0.031, 0.031, 0.021, 0.021, 0.019, 0.028, 0.065, 0.065, 0.046, 0.034}// < 5
				                          ,{0.018, 0.018, 0.016, 0.0150, 0.016, 0.028, 0.053, 0.038, 0.028, 0.025}// 5-10 
				                          ,{0.014, 0.014, 0.014, 0.0145, 0.012, 0.033, 0.030, 0.025, 0.013, 0.013}// 10-15 
                                  ,{0.012, 0.012, 0.012, 0.0130, 0.010, 0.029, 0.022, 0.018, 0.010, 0.010}// 15-20 
                                  ,{0.010, 0.010, 0.010, 0.0100, 0.010, 0.010, 0.020, 0.015, 0.008, 0.008}// 20-30 
				                          ,{0.008, 0.008, 0.008, 0.0080, 0.008, 0.010, 0.015, 0.015, 0.008, 0.008}// 30-40 
				                          ,{0.008, 0.008, 0.008, 0.0080, 0.008, 0.010, 0.015, 0.015, 0.008, 0.008}// 40-50
				                          ,{0.008, 0.008, 0.008, 0.0080, 0.008, 0.010, 0.015, 0.015, 0.008, 0.008}// 50-60 
				                          ,{0.008, 0.008, 0.008, 0.0080, 0.008, 0.010, 0.015, 0.015, 0.008, 0.008}// 60-70 
				                          ,{0.008, 0.008, 0.008, 0.0080, 0.008, 0.010, 0.015, 0.015, 0.008, 0.008}// 70-80 
				                          ,{0.008, 0.008, 0.008, 0.0080, 0.008, 0.010, 0.015, 0.015, 0.008, 0.008}};// 80< 

  const double cutrhad2012[11][10] = {{0.12800, 0.15600, 0.15200, 0.11600, 0.15600, 0.04275, 0.13200, 0.15200, 0.15600, 0.14000}// < 5
				                          ,{0.12800, 0.15600, 0.15200, 0.11600, 0.15600, 0.04275, 0.13200, 0.15200, 0.15600, 0.14000} // 5-10 
			                            ,{0.03225, 0.03225, 0.03075, 0.03575, 0.02575, 0.04275, 0.04325, 0.04525, 0.04325, 0.03675}  // 10-15
                                  ,{0.02925, 0.02925, 0.02775, 0.03175, 0.02375, 0.03875, 0.04025, 0.03425, 0.03825, 0.02975}  // 15-20
                                  ,{0.02425, 0.02425, 0.02275, 0.02575, 0.01975, 0.01975, 0.02725, 0.02725, 0.02725, 0.01975}  // 20-30
                                  ,{0.02275, 0.02275, 0.02125, 0.01975, 0.01825, 0.01825, 0.02425, 0.02575, 0.02425, 0.01675}  // 30-40
                                  ,{0.01825, 0.01825, 0.01975, 0.01525, 0.01675, 0.01675, 0.02125, 0.02275, 0.01975, 0.01675}  // 40-50
                                  ,{0.01825, 0.01825, 0.01975, 0.01525, 0.01675, 0.01675, 0.02125, 0.02275, 0.01975, 0.01675}  // 50-60
                                  ,{0.01825, 0.01825, 0.01975, 0.01525, 0.01675, 0.01675, 0.02125, 0.02275, 0.01975, 0.01675}  // 60-70
                                  ,{0.01825, 0.01825, 0.01975, 0.01525, 0.01675, 0.01675, 0.02125, 0.02275, 0.01975, 0.01675}  // 70-80
                                  ,{0.01825, 0.01825, 0.01975, 0.01525, 0.01675, 0.01675, 0.02125, 0.02275, 0.01975, 0.01675}}; // >80
                                 

  if(etabin == 3 || etabin == 4){
    if (rhad > (menu == egammaMenu::eg2012?cutrhad2012[etbin][etabin]:cutrhad2011[etbin][etabin]))
      return false;
  } else{
    if(rhad1 > (menu == egammaMenu::eg2012?cutrhad2012[etbin][etabin]:cutrhad2011[etbin][etabin]))
      return false;
  }

  return true;
}
//----------------------------------------------------------------------------------------
bool passRHad_med(double rhad, double rhad1,unsigned int etbin,unsigned int etabin, egammaMenu::egMenu menu){
  
  // values cut on rhad (rows are et bins, columns are eta bins)
  //                               0.0   0.1    0.6    0.8   1.15   1.37   1.52   1.81   2.01  2.37    2.47

  const double cutrhad2011[11][10] = {{ 0.031, 0.031, 0.021, 0.021, 0.019, 0.028, 0.065, 0.065, 0.046, 0.034}// < 5
				                              ,{0.018, 0.018, 0.016, 0.015, 0.016, 0.028, 0.053, 0.038, 0.028, 0.025} // 5-10 
				                              ,{0.015 ,0.015 ,0.015 ,0.015 ,0.013 ,0.033 ,0.030 ,0.028 ,0.015 ,0.015} //10-15
				                              ,{0.0125 ,0.0125 ,0.012 ,0.012 ,0.0115 ,0.029 ,0.027 ,0.020 ,0.011 ,0.011} //15-20
				                              ,{0.010, 0.010, 0.010, 0.010, 0.010, 0.010, 0.020, 0.015, 0.008, 0.008}// 20-30 
				                              ,{0.008, 0.008, 0.008, 0.008, 0.008, 0.010, 0.015, 0.015, 0.008, 0.008}// 30-40 
				                              ,{0.008, 0.008, 0.008, 0.008, 0.008, 0.010, 0.015, 0.015, 0.008, 0.008}// 40-50
				                              ,{0.008, 0.008, 0.008, 0.008, 0.008, 0.010, 0.015, 0.015, 0.008, 0.008}// 50-60 
				                              ,{0.008, 0.008, 0.008, 0.008, 0.008, 0.010, 0.015, 0.015, 0.008, 0.008}// 60-70 
				                              ,{0.008, 0.008, 0.008, 0.008, 0.008, 0.010, 0.015, 0.015, 0.008, 0.008}// 70-80 
				                              ,{0.008, 0.008, 0.008, 0.008, 0.008, 0.010, 0.015, 0.015, 0.008, 0.008}};// 80< 

  const double cutrhad2012[11][10] = {{0.12800, 0.15600, 0.15200, 0.11600, 0.15600, 0.04275, 0.13200, 0.15200, 0.15600, 0.14000}// < 5
				                          ,{0.12800, 0.15600, 0.15200, 0.11600, 0.15600, 0.04275, 0.13200, 0.15200, 0.15600, 0.14000} // 5-10 
			                            ,{0.03225, 0.03225, 0.03075, 0.03575, 0.02575, 0.04275, 0.04325, 0.04525, 0.04325, 0.03675}  // 10-15
                                  ,{0.02925, 0.02925, 0.02775, 0.03175, 0.02375, 0.03875, 0.04025, 0.03425, 0.03825, 0.02975}  // 15-20
                                  ,{0.02425, 0.02425, 0.02275, 0.02575, 0.01975, 0.01975, 0.02725, 0.02725, 0.02725, 0.01975}  // 20-30
                                  ,{0.02275, 0.02275, 0.02125, 0.01975, 0.01825, 0.01825, 0.02425, 0.02575, 0.02425, 0.01675}  // 30-40
                                  ,{0.01825, 0.01825, 0.01975, 0.01525, 0.01675, 0.01675, 0.02125, 0.02275, 0.01975, 0.01675}  // 40-50
                                  ,{0.01825, 0.01825, 0.01975, 0.01525, 0.01675, 0.01675, 0.02125, 0.02275, 0.01975, 0.01675}  // 50-60
                                  ,{0.01825, 0.01825, 0.01975, 0.01525, 0.01675, 0.01675, 0.02125, 0.02275, 0.01975, 0.01675}  // 60-70
                                  ,{0.01825, 0.01825, 0.01975, 0.01525, 0.01675, 0.01675, 0.02125, 0.02275, 0.01975, 0.01675}  // 70-80
                                  ,{0.01825, 0.01825, 0.01975, 0.01525, 0.01675, 0.01675, 0.02125, 0.02275, 0.01975, 0.01675}}; // >80
                                 

  if(etabin == 3 || etabin == 4){
    if (rhad > (menu == egammaMenu::eg2012?cutrhad2012[etbin][etabin]:cutrhad2011[etbin][etabin]))
      return false;
  } else{
    if(rhad1 > (menu == egammaMenu::eg2012?cutrhad2012[etbin][etabin]:cutrhad2011[etbin][etabin]))
      return false;
  }

  return true;
}
//----------------------------------------------------------------------------------------
bool passReta_tight(double rEta, unsigned int eTBin, unsigned int etaBin, egammaMenu::egMenu menu){
  // New values cut on ratio e237/e277 (rows are eT bins, columns are eta bins)
  //                               0.0   0.1      0.6    0.8   1.15   1.37   1.52   1.81    2.01   2.37   2.47
  const double cutReta372012[11][10] = {{0.6800, 0.5600, 0.6000, 0.6800, 0.7200, 0.440, 0.7600, 0.7200, 0.7600, 0.7475}  // < 5
				                           ,{0.6800, 0.5600, 0.6000, 0.6800, 0.7200, 0.440, 0.7600, 0.7200, 0.7600, 0.7475}  // 5-10
				                           ,{0.8475, 0.8475, 0.8425, 0.8175, 0.8475, 0.740, 0.8275, 0.8675, 0.8675, 0.7475} // 10-15
                                   ,{0.8675, 0.8675, 0.8675, 0.8475, 0.8725, 0.740, 0.8525, 0.8775, 0.8775, 0.7575} // 15-20
                                   ,{0.8825, 0.8825, 0.8825, 0.8575, 0.8875, 0.750, 0.8725, 0.9025, 0.8875, 0.7575} // 20-30
                                   ,{0.9075, 0.9075, 0.8975, 0.8875, 0.8875, 0.790, 0.8925, 0.9075, 0.8975, 0.8075} // 30-40
                                   ,{0.9175, 0.9175, 0.9125, 0.9075, 0.9025, 0.790, 0.8975, 0.9125, 0.9025, 0.8625} // 40-50
                                   ,{0.9175, 0.9175, 0.9125, 0.9075, 0.9025, 0.790, 0.8975, 0.9125, 0.9025, 0.8625} // 50-60
                                   ,{0.9175, 0.9175, 0.9125, 0.9075, 0.9025, 0.790, 0.8975, 0.9125, 0.9025, 0.8625} // 60-70
                                   ,{0.9175, 0.9175, 0.9125, 0.9075, 0.9025, 0.790, 0.8975, 0.9125, 0.9025, 0.8625} // 70-80
                                   ,{0.9175, 0.9175, 0.9125, 0.9075, 0.9025, 0.790, 0.8975, 0.9125, 0.9025, 0.8625}}; // >80
				    
 const double cutReta372011[11][10] = {{ 0.700, 0.700, 0.700, 0.700, 0.700, 0.690, 0.848, 0.876, 0.870, 0.888}  // < 5
                       				     ,{0.700, 0.700, 0.700, 0.700, 0.700, 0.715, 0.860, 0.880, 0.880, 0.880} // 5-10
                       				     ,{0.905, 0.905, 0.900, 0.895, 0.895, 0.740, 0.880, 0.900, 0.900, 0.900} //10-15 
                                   ,{0.915, 0.915, 0.915, 0.910, 0.910, 0.740, 0.895, 0.910, 0.900, 0.910} //15-20 
                       				     ,{0.930, 0.930, 0.930, 0.925, 0.925, 0.750, 0.915, 0.915, 0.910, 0.910}// 20-30
                       				     ,{0.930, 0.930, 0.930, 0.925, 0.925, 0.790, 0.915, 0.920, 0.910, 0.910}// 30-40
                       				     ,{0.930, 0.930, 0.930, 0.925, 0.925, 0.790, 0.915, 0.920, 0.910, 0.910}// 40-50
                       				     ,{0.930, 0.930, 0.930, 0.930, 0.925, 0.790, 0.915, 0.920, 0.910, 0.910}// 50-60
                       				     ,{0.930, 0.930, 0.930, 0.930, 0.925, 0.790, 0.915, 0.920, 0.910, 0.910}// 60-70
                       				     ,{0.930, 0.930, 0.930, 0.930, 0.925, 0.790, 0.915, 0.920, 0.910, 0.910}// 70-80
                       				     ,{0.930, 0.930, 0.930, 0.930, 0.925, 0.790, 0.915, 0.920, 0.910, 0.910}};// 80<



  if(rEta < (menu == egammaMenu::eg2012?cutReta372012[eTBin][etaBin]:cutReta372011[eTBin][etaBin]))
    return false;

  return true;
}
//----------------------------------------------------------------------------------------
bool passReta_med(double rEta, unsigned int eTBin, unsigned int etaBin, egammaMenu::egMenu menu){
  // New values cut on ratio e237/e277 (rows are eT bins, columns are eta bins)
  //                               0.0   0.1      0.6    0.8   1.15   1.37   1.52   1.81    2.01   2.37   2.47
  const double cutReta372012[11][10] = {{0.6800, 0.5600, 0.6000, 0.6800, 0.7200, 0.440, 0.7600, 0.7200, 0.7600, 0.7475}  // < 5
				                           ,{0.6800, 0.5600, 0.6000, 0.6800, 0.7200, 0.440, 0.7600, 0.7200, 0.7600, 0.7475}  // 5-10
				                           ,{0.8475, 0.8475, 0.8425, 0.8175, 0.8475, 0.740, 0.8275, 0.8675, 0.8675, 0.7475} // 10-15
                                   ,{0.8675, 0.8675, 0.8675, 0.8475, 0.8725, 0.740, 0.8525, 0.8775, 0.8775, 0.7575} // 15-20
                                   ,{0.8825, 0.8825, 0.8825, 0.8575, 0.8875, 0.750, 0.8725, 0.9025, 0.8875, 0.7575} // 20-30
                                   ,{0.9075, 0.9075, 0.8975, 0.8875, 0.8875, 0.790, 0.8925, 0.9075, 0.8975, 0.8075} // 30-40
                                   ,{0.9175, 0.9175, 0.9125, 0.9075, 0.9025, 0.790, 0.8975, 0.9125, 0.9025, 0.8625} // 40-50
                                   ,{0.9175, 0.9175, 0.9125, 0.9075, 0.9025, 0.790, 0.8975, 0.9125, 0.9025, 0.8625} // 50-60
                                   ,{0.9175, 0.9175, 0.9125, 0.9075, 0.9025, 0.790, 0.8975, 0.9125, 0.9025, 0.8625} // 60-70
                                   ,{0.9175, 0.9175, 0.9125, 0.9075, 0.9025, 0.790, 0.8975, 0.9125, 0.9025, 0.8625} // 70-80
                                   ,{0.9175, 0.9175, 0.9125, 0.9075, 0.9025, 0.790, 0.8975, 0.9125, 0.9025, 0.8625}}; // >80
				    
  const double cutReta372011[11][10] = {{ 0.700, 0.700, 0.700, 0.700, 0.700, 0.690, 0.848, 0.876, 0.870, 0.888}  // < 5
				                            ,{0.700, 0.700, 0.700, 0.700, 0.700, 0.715, 0.860, 0.880, 0.880, 0.880} // 5-10
				                            ,{0.895 ,0.895 ,0.890 ,0.885 ,0.885 ,0.740 ,0.870 ,0.885 ,0.890 ,0.900} //10-15
				                            ,{0.915 ,0.915 ,0.915 ,0.915 ,0.910 ,0.740 ,0.895 ,0.900 ,0.900 ,0.910} //15-20
				                            ,{0.930, 0.930, 0.930, 0.925, 0.925, 0.750, 0.915, 0.915, 0.910, 0.910}// 20-30
				                            ,{0.930, 0.930, 0.930, 0.925, 0.925, 0.790, 0.915, 0.920, 0.910, 0.910}// 30-40
				                            ,{0.930, 0.930, 0.930, 0.925, 0.925, 0.790, 0.915, 0.920, 0.910, 0.910}// 40-50
				                            ,{0.930, 0.930, 0.930, 0.930, 0.925, 0.790, 0.915, 0.920, 0.910, 0.910}// 50-60
				                            ,{0.930, 0.930, 0.930, 0.930, 0.925, 0.790, 0.915, 0.920, 0.910, 0.910}// 60-70
				                            ,{0.930, 0.930, 0.930, 0.930, 0.925, 0.790, 0.915, 0.920, 0.910, 0.910}// 70-80
				                            ,{0.930, 0.930, 0.930, 0.930, 0.925, 0.790, 0.915, 0.920, 0.910, 0.910}};// 80<

  if(rEta < (menu == egammaMenu::eg2012?cutReta372012[eTBin][etaBin]:cutReta372011[eTBin][etaBin]))
    return false;

  return true;
}

//----------------------------------------------------------------------------------------
bool passWstot_med(double wstot, unsigned int eTBin, unsigned int etaBin, egammaMenu::egMenu menu){
  
  //New values for cut on shower width in 2nd sampling (rows are eT bins, columns are eta bins)
  //                               0.0   0.1    0.6    0.8   1.15   1.37   1.52   1.81    2.01   2.37   2.47
  const double cutWstot2012[11][10]  = {{3.48, 3.48, 3.78, 3.96, 4.20, 9999., 4.02, 2.70, 1.86,  9999.} // < 5    GeV
				                           ,{3.18, 3.18, 3.54, 3.90, 4.02, 9999., 3.96, 2.70, 1.80,  9999.} // 5-10   
				                           ,{2.85, 2.85, 3.2, 3.4, 3.6, 9999.0, 3.7, 2.4, 1.72, 9999.0}     // 10-15
                                   ,{2.76, 2.76, 2.92, 3.3, 3.45, 9999.0, 3.67, 2.4, 1.72, 9999.0}  // 15-20
                                   ,{2.5, 2.5, 2.65, 3.0, 3.2, 9999.0, 3.3, 2.15, 1.49, 9999.0}     // 20-30
                                   ,{2.5, 2.5, 2.65, 3.0, 3.2, 9999.0, 3.3, 2.15, 1.49, 9999.0}     // 30-40
                                   ,{2.5, 2.5, 2.65, 3.0, 3.2, 9999.0, 3.3, 2.15, 1.49, 9999.0}     // 40-50
                                   ,{2.5, 2.5, 2.65, 3.0, 3.2, 9999.0, 3.3, 2.15, 1.49, 9999.0}     // 50-60
                                   ,{2.5, 2.5, 2.65, 3.0, 3.2, 9999.0, 3.3, 2.15, 1.49, 9999.0}     // 60-70
                                   ,{2.5, 2.5, 2.65, 3.0, 3.2, 9999.0, 3.3, 2.15, 1.49, 9999.0}     // 70-80
                                   ,{2.5, 2.5, 2.65, 3.0, 3.2, 9999.0, 3.3, 2.15, 1.49, 9999.0}};   // >80
  
  const double cutWstot2011[11][10]  = {{3.48, 3.48, 3.78, 3.96, 4.20, 9999., 4.02, 2.70, 1.86,  9999.} // < 5    GeV
                      				    ,{3.18, 3.18, 3.54, 3.90, 4.02, 9999., 3.96, 2.70, 1.80,  9999.} // 5-10   
                      				    ,{2.85 ,2.85 ,3.20 ,3.40 ,3.60 ,9999. ,3.70 ,2.40 ,1.72 ,9999}  //10-15
                      				    ,{2.76 ,2.76 ,2.92 ,3.30 ,3.45 ,9999. ,3.67 ,2.40 ,1.72 ,9999}  //15-20
                      				    ,{2.50, 2.50, 2.70, 3.14, 3.23, 9999., 3.58, 2.32, 1.59,  9999.} // 20-30  
                      				    ,{2.45, 2.45, 2.70, 2.98, 3.17, 9999., 3.52, 2.25, 1.58,  9999.} // 30-40  
                      				    ,{2.27, 2.27, 2.61, 2.90, 3.17, 9999., 3.36, 2.25, 1.55,  9999.} // 40-50  
                      				    ,{2.27, 2.27, 2.61, 2.90, 3.17, 9999., 3.36, 2.25, 1.55,  9999.} // 50-60  
                      				    ,{2.27, 2.27, 2.61, 2.90, 3.17, 9999., 3.36, 2.25, 1.55,  9999.} // 60-70  
                      				    ,{2.27, 2.27, 2.61, 2.90, 3.17, 9999., 3.36, 2.25, 1.55,  9999.} // 70-80  
                      				    ,{2.27, 2.27, 2.61, 2.90, 3.17, 9999., 3.36, 2.25, 1.55,  9999.}};  // 80<    


  if(wstot > (menu==egammaMenu::eg2012?cutWstot2012[eTBin][etaBin]:cutWstot2011[eTBin][etaBin]))
    return false;
    
  return  true;
}
//----------------------------------------------------------------------------------------
bool passf3_med(double f3, unsigned int eTBin, unsigned int etaBin){
  
  //New values for cut on shower width in 2nd sampling (rows are eT bins, columns are eta bins)
  //                               0.0      0.1    0.6      0.8     1.15   1.37   1.52   1.81    2.01   2.37   2.47
  const double cutf3[11][10]  =  {{0.0215, 0.0215, 0.0175, 0.0175, 0.0235, 9999., 0.0175, 0.0285, 0.0268, 0.0383}// < 5
                                 ,{0.0215, 0.0215, 0.0175, 0.0175, 0.0235, 9999., 0.0175, 0.0285, 0.0268, 0.0383}  // 5-10
                                 ,{0.0215, 0.0215, 0.0175, 0.0175, 0.0235, 9999., 0.0175, 0.0285, 0.0268, 0.0383}  // 10-15
                                 ,{0.0215, 0.0215, 0.0175, 0.0175, 0.0235, 9999., 0.0175, 0.0285, 0.0268, 0.0383}  // 15-20
                                 ,{0.0215, 0.0215, 0.0175, 0.0175, 0.0235, 9999., 0.0175, 0.0285, 0.0268, 0.0383}  // 20-30
                                 ,{0.0255, 0.0255, 0.0195, 0.0215, 0.0245, 9999., 0.0205, 0.0285, 0.0268, 0.0383}  // 30-40
                                 ,{0.0265, 0.0265, 0.0195, 0.0215, 0.0245, 9999., 0.0255, 0.0285, 0.0293, 0.0383}  // 40-50
                                 ,{0.0265, 0.0265, 0.0195, 0.0215, 0.0245, 9999., 0.0255, 0.0285, 0.0293, 0.0383}  // 50-60
                                 ,{0.0265, 0.0265, 0.0195, 0.0215, 0.0245, 9999., 0.0255, 0.0285, 0.0293, 0.0383}  // 60-70
                                 ,{0.0265, 0.0265, 0.0195, 0.0215, 0.0245, 9999., 0.0255, 0.0285, 0.0293, 0.0383}  // 70-80
                                 ,{9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999.}};// >80


  if(f3 > cutf3[eTBin][etaBin])
    return false;
    
  return  true;
}


//----------------------------------------------------------------------------------------
bool passReta_loose(double rEta, unsigned int eTBin, unsigned int etaBin, egammaMenu::egMenu menu){
  // New values cut on ratio e237/e277 (rows are eT bins, columns are eta bins)
  //                               0.0   0.1      0.6    0.8   1.15   1.37   1.52   1.81    2.01   2.37   2.47
  const double cutReta372012[11][10] = {{0.6800, 0.5600, 0.6000, 0.6800, 0.7200, 0.440, 0.7600, 0.7200, 0.7600, 0.7175}  // < 5        
                                   ,{0.6800, 0.5600, 0.6000, 0.6800, 0.7200, 0.440, 0.7600, 0.7200, 0.7600, 0.7175}   // 5-10
                                   ,{0.8275, 0.8275, 0.8275, 0.8075, 0.8375, 0.740, 0.8175, 0.8625, 0.8475, 0.7175}  // 10-15
                                   ,{0.8525, 0.8525, 0.8475, 0.8275, 0.8525, 0.740, 0.8375, 0.8625, 0.8575, 0.7275}  // 15-20
                                   ,{0.8625, 0.8625, 0.8625, 0.8425, 0.8725, 0.750, 0.8475, 0.8875, 0.8675, 0.7375}  // 20-30
                                   ,{0.8975, 0.8975, 0.8875, 0.8775, 0.8775, 0.790, 0.8725, 0.8875, 0.8825, 0.7875}  // 30-40
                                   ,{0.9075, 0.9075, 0.9025, 0.8975, 0.8925, 0.790, 0.8775, 0.9025, 0.8875, 0.8425}  // 40-50
                                   ,{0.9075, 0.9075, 0.9025, 0.8975, 0.8925, 0.790, 0.8775, 0.9025, 0.8875, 0.8425}  // 50-60
                                   ,{0.9075, 0.9075, 0.9025, 0.8975, 0.8925, 0.790, 0.8775, 0.9025, 0.8875, 0.8425}  // 60-70
                                   ,{0.9075, 0.9075, 0.9025, 0.8975, 0.8925, 0.790, 0.8775, 0.9025, 0.8875, 0.8425}  // 70-80
                                   ,{0.9075, 0.9075, 0.9025, 0.8975, 0.8925, 0.790, 0.8775, 0.9025, 0.8875, 0.8425}};    // >80

  const double cutReta372011[11][10] = {{ 0.700, 0.700, 0.700, 0.700, 0.700, 0.690, 0.848, 0.876, 0.870, 0.888}  // < 5
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
                       

  if(rEta < (menu == egammaMenu::eg2012?cutReta372012[eTBin][etaBin]:cutReta372011[eTBin][etaBin]))
    return false;

  return true;
}
//----------------------------------------------------------------------------------------
bool passRHad_loose(double rhad, double rhad1,unsigned int etbin,unsigned int etabin, egammaMenu::egMenu menu){
  
  // new values cut on rhad (rows are et bins, columns are eta bins)
  //                               0.0   0.1    0.6    0.8   1.15   1.37   1.52   1.81   2.01  2.37    2.47
  const double cutrhad2012[11][10]={{0.12800, 0.15600, 0.15200, 0.11600, 0.15600, 0.04775, 0.13200, 0.15200, 0.15600, 0.14000} // < 5 
                                  ,{0.12800, 0.15600, 0.15200, 0.11600, 0.15600, 0.04775, 0.13200, 0.15200, 0.15600, 0.14000} // 5-10
                                  ,{0.03425, 0.03425, 0.03275, 0.03775, 0.02775, 0.04775, 0.05325, 0.05225, 0.05125, 0.04475} // 10-15
                                  ,{0.03125, 0.03125, 0.02975, 0.03375, 0.02575, 0.04375, 0.05025, 0.04125, 0.04625, 0.03775} // 15-20
                                  ,{0.02625, 0.02625, 0.02475, 0.02775, 0.02175, 0.02475, 0.03725, 0.03425, 0.03525, 0.02775} // 20-30
                                  ,{0.02375, 0.02375, 0.02225, 0.02075, 0.01925, 0.01925, 0.02525, 0.03175, 0.03125, 0.02375} // 30-40
                                  ,{0.01925, 0.01925, 0.02075, 0.01625, 0.01775, 0.01775, 0.02275, 0.02575, 0.02175, 0.01875} // 40-50
                                  ,{0.01925, 0.01925, 0.02075, 0.01625, 0.01775, 0.01775, 0.02275, 0.02575, 0.02175, 0.01875} // 50-60
                                  ,{0.01925, 0.01925, 0.02075, 0.01625, 0.01775, 0.01775, 0.02275, 0.02575, 0.02175, 0.01875} // 60-70
                                  ,{0.01925, 0.01925, 0.02075, 0.01625, 0.01775, 0.01775, 0.02275, 0.02575, 0.02175, 0.01875} // 70-80
                                  ,{0.01925, 0.01925, 0.02075, 0.01625, 0.01775, 0.01775, 0.02275, 0.02575, 0.02175, 0.01875}}; // >80

  const double cutrhad2011[11][10]= {{ 0.031, 0.031, 0.021, 0.021, 0.019, 0.028, 0.065, 0.065, 0.046, 0.034}// < 5
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

  if(etabin == 3 || etabin == 4){
    if (rhad > (menu == egammaMenu::eg2012?cutrhad2012[etbin][etabin]:cutrhad2011[etbin][etabin]))
      return false;
  } else{
    if(rhad1 > (menu == egammaMenu::eg2012?cutrhad2012[etbin][etabin]:cutrhad2011[etbin][etabin]))
      return false;
  }

  return true;
}
//----------------------------------------------------------------------------------------
bool passW2_tight(double w2, unsigned int eTBin, unsigned int etaBin, egammaMenu::egMenu menu){
  
  //New values for cut on shower width in 2nd sampling (rows are eT bins, columns are eta bins)
  //                               0.0   0.1    0.6    0.8   1.15   1.37   1.52   1.81    2.01   2.37   2.47
  const double cutWeta22012[11][10] = {{0.017, 0.016, 0.018, 0.016, 0.019, 0.031, 0.017, 0.016, 0.0155, 0.0155} // < 5 
				                              ,{0.017, 0.016, 0.018, 0.016, 0.019, 0.031, 0.017, 0.016, 0.0155, 0.0155} // 5-10
				                              ,{0.013, 0.013, 0.013, 0.013, 0.013, 0.025, 0.014, 0.014, 0.0135, 0.014} // 10-15 
                                      ,{0.012, 0.012, 0.013, 0.013, 0.013, 0.025, 0.014, 0.014, 0.0135, 0.014} // 15-20 
                                      ,{0.011, 0.011, 0.012, 0.012, 0.013, 0.025, 0.013, 0.0125, 0.013, 0.0135} // 20-30
				                              ,{0.011, 0.011, 0.012, 0.012, 0.012, 0.025, 0.013, 0.0125, 0.013, 0.0135} // 30-40
				                              ,{0.011, 0.011, 0.012, 0.012, 0.012, 0.025, 0.013, 0.0125, 0.013, 0.0135} // 40-50
				                              ,{0.011, 0.011, 0.012, 0.012, 0.012, 0.025, 0.013, 0.012, 0.013, 0.0135} // 50-60
				                              ,{0.011, 0.011, 0.012, 0.012, 0.012, 0.025, 0.013, 0.012, 0.013, 0.0135} // 60-70
				                              ,{0.011, 0.011, 0.012, 0.012, 0.012, 0.025, 0.013, 0.012, 0.013, 0.0135} // 70-80
				                              ,{0.011, 0.011, 0.012, 0.012, 0.012, 0.025, 0.013, 0.012, 0.013, 0.0135}}; // 80<  

  const double cutWeta22011[11][10] = {{ 0.014, 0.014, 0.014, 0.014, 0.014, 0.028, 0.017, 0.014, 0.014, 0.014} // < 5 
	                          			   ,{0.013, 0.013, 0.014, 0.014, 0.014, 0.026, 0.017, 0.014, 0.014, 0.014} // 5-10
	                          			   ,{0.013, 0.013, 0.014, 0.014, 0.013, 0.025, 0.014, 0.014, 0.013, 0.013} // 10-15 
                                     ,{0.012, 0.012, 0.013, 0.013, 0.013, 0.025, 0.014, 0.014, 0.013, 0.013} // 15-20 
                                     ,{0.011, 0.011, 0.012, 0.012, 0.013, 0.025, 0.014, 0.013, 0.0125, 0.0125} // 20-30
	                          			   ,{0.011, 0.011, 0.012, 0.012, 0.012, 0.025, 0.013, 0.013, 0.0125, 0.0125} // 30-40
	                          			   ,{0.011, 0.011, 0.012, 0.012, 0.012, 0.025, 0.013, 0.013, 0.0125, 0.0125} // 40-50
	                          			   ,{0.011, 0.011, 0.012, 0.012, 0.012, 0.025, 0.013, 0.012, 0.0125, 0.0125} // 50-60
	                          			   ,{0.011, 0.011, 0.012, 0.012, 0.012, 0.025, 0.013, 0.012, 0.0125, 0.0125} // 60-70
	                          			   ,{0.011, 0.011, 0.012, 0.012, 0.012, 0.025, 0.013, 0.012, 0.0125, 0.0125} // 70-80
	                          			   ,{0.011, 0.011, 0.012, 0.012, 0.012, 0.025, 0.013, 0.012, 0.0125, 0.0125}}; // 80<  

  if(w2 > ( menu ==egammaMenu::eg2012?cutWeta22012[eTBin][etaBin]:cutWeta22011[eTBin][etaBin]))
    return false;
    
  return  true;
}
//----------------------------------------------------------------------------------------
bool passW2_med(double w2, unsigned int eTBin, unsigned int etaBin, egammaMenu::egMenu menu){
  
  //New values for cut on shower width in 2nd sampling (rows are eT bins, columns are eta bins)
  //                               0.0   0.1    0.6    0.8   1.15   1.37   1.52   1.81    2.01   2.37   2.47
  const double cutWeta22012[11][10] = {{0.017, 0.016, 0.018, 0.016, 0.019, 0.031, 0.017, 0.016, 0.0155, 0.0155}// < 5 
				                              ,{0.017, 0.016, 0.018, 0.016, 0.019, 0.031, 0.017, 0.016, 0.0155, 0.0155} // 5-10
				                              ,{0.013, 0.013, 0.013, 0.013, 0.013, 0.025, 0.014, 0.014, 0.0135, 0.014}    //10-15
				                              ,{0.012, 0.012, 0.013, 0.013, 0.013, 0.025, 0.014, 0.014, 0.0135, 0.014}    //15-20
				                              ,{0.011, 0.011, 0.012, 0.012, 0.013, 0.025, 0.013, 0.0125, 0.013, 0.0135} // 20-30
				                              ,{0.011, 0.011, 0.012, 0.012, 0.013, 0.025, 0.013, 0.0125, 0.013, 0.0135} // 30-40
				                              ,{0.011, 0.011, 0.012, 0.012, 0.013, 0.025, 0.013, 0.0125, 0.013, 0.0135} // 40-50
				                              ,{0.011, 0.011, 0.012, 0.012, 0.013, 0.025, 0.013, 0.0125, 0.013, 0.0135} // 50-60
				                              ,{0.011, 0.011, 0.012, 0.012, 0.013, 0.025, 0.013, 0.0125, 0.013, 0.0135} // 60-70
				                              ,{0.011, 0.011, 0.012, 0.012, 0.013, 0.025, 0.013, 0.0125, 0.013, 0.0135} // 70-80
				                              ,{0.011, 0.011, 0.012, 0.012, 0.013, 0.025, 0.013, 0.0125, 0.013, 0.0135} }; // 80<  

  const double cutWeta22011[11][10] = {{ 0.014, 0.014, 0.014, 0.014, 0.014, 0.028, 0.017, 0.014, 0.014, 0.014} // < 5 
				                              ,{0.013, 0.013, 0.014, 0.014, 0.014, 0.026, 0.017, 0.014, 0.014, 0.014} // 5-10
				                              ,{0.013 ,0.013 ,0.013 ,0.013,0.013 ,0.025 ,0.0140 ,0.014 ,0.013 ,0.013} //10-15
				                              ,{0.012 ,0.012 ,0.013 ,0.013 ,0.013 ,0.025 ,0.0140,0.014 ,0.013 ,0.013 } //15-20
				                              ,{0.011, 0.011, 0.012, 0.012, 0.013, 0.025, 0.014, 0.013, 0.0125, 0.0125} // 20-30
				                              ,{0.011, 0.011, 0.012, 0.012, 0.012, 0.025, 0.013, 0.013, 0.0125, 0.0125} // 30-40
				                              ,{0.011, 0.011, 0.012, 0.012, 0.012, 0.025, 0.013, 0.013, 0.0125, 0.0125} // 40-50
				                              ,{0.011, 0.011, 0.012, 0.012, 0.012, 0.025, 0.013, 0.012, 0.0125, 0.0125} // 50-60
				                              ,{0.011, 0.011, 0.012, 0.012, 0.012, 0.025, 0.013, 0.012, 0.0125, 0.0125} // 60-70
				                              ,{0.011, 0.011, 0.012, 0.012, 0.012, 0.025, 0.013, 0.012, 0.0125, 0.0125} // 70-80
				                              ,{0.011, 0.011, 0.012, 0.012, 0.012, 0.025, 0.013, 0.012, 0.0125, 0.0125}}; // 80<  


  if(w2 > ( menu ==egammaMenu::eg2012?cutWeta22012[eTBin][etaBin]:cutWeta22011[eTBin][etaBin]))
    return false;
       
  return  true;
}
//----------------------------------------------------------------------------------------
bool passW2_loose(double w2, unsigned int eTBin, unsigned int etaBin, egammaMenu::egMenu menu){
  
  //New values for cut on shower width in 2nd sampling (rows are eT bins, columns are eta bins)
  //                               0.0   0.1    0.6    0.8   1.15   1.37   1.52   1.81    2.01   2.37   2.47
  const double cutWeta22012[11][10] = {{0.017, 0.016, 0.018, 0.016, 0.019, 0.031, 0.017, 0.016, 0.0155, 0.0155}   // < 5 
				                              ,{0.017, 0.016, 0.018, 0.016, 0.019, 0.031, 0.017, 0.016, 0.0155, 0.0155} // 5-10
				                              ,{0.014 ,0.014 ,0.015 ,0.016 ,0.017 ,0.025 ,0.017 ,0.015 ,0.015 ,0.0145} //10-15
				                              ,{0.0135 ,0.0135 ,0.0145 ,0.016 ,0.017 ,0.025 ,0.017 ,0.015 ,0.015 ,0.0145} //15-20
				                              ,{0.013 ,0.013 ,0.014 ,0.015 ,0.015 ,0.025 ,0.016 ,0.015 ,0.015 ,0.014 } //20-30
				                              ,{0.012 ,0.012 ,0.013 ,0.013 ,0.013 ,0.025 ,0.015 ,0.014 ,0.014 ,0.0135} //30-40
				                              ,{0.011 ,0.011 ,0.012 ,0.013 ,0.013 ,0.025 ,0.015 ,0.014 ,0.014 ,0.0135} //40-50
				                              ,{0.011 ,0.011 ,0.012 ,0.013 ,0.013 ,0.025 ,0.015 ,0.014 ,0.014 ,0.0135}// 50-60
				                              ,{0.011 ,0.011 ,0.012 ,0.013 ,0.013 ,0.025 ,0.015 ,0.014 ,0.014 ,0.0135}// 60-70 
				                              ,{0.011 ,0.011 ,0.012 ,0.013 ,0.013 ,0.025 ,0.015 ,0.014 ,0.014 ,0.0135}// 70-80 
				                              ,{0.011 ,0.011 ,0.012 ,0.013 ,0.013 ,0.025 ,0.015 ,0.014 ,0.014 ,0.0135}};// 80<   

  const double cutWeta22011[11][10] = {{ 0.014, 0.014, 0.014, 0.014, 0.014, 0.028, 0.017, 0.014, 0.014, 0.014}   // < 5 
				                          ,{0.013, 0.013, 0.014, 0.014, 0.014, 0.026, 0.017, 0.014, 0.014, 0.014}  // 5-10
				                          ,{0.014 ,0.014 ,0.015 ,0.016 ,0.017 ,0.025 ,0.017 ,0.015 ,0.015 ,0.0145} //10-15
				                          ,{0.0135 ,0.0135 ,0.0145 ,0.016 ,0.017 ,0.025 ,0.017 ,0.015 ,0.015 ,0.0145} //15-20
				                          ,{0.013 ,0.013 ,0.014 ,0.015 ,0.015 ,0.025 ,0.016 ,0.015 ,0.015 ,0.014 } //20-30
				                          ,{0.012 ,0.012 ,0.013 ,0.013 ,0.013 ,0.025 ,0.015 ,0.014 ,0.014 ,0.013 } //30-40
				                          ,{0.011 ,0.011 ,0.012 ,0.013 ,0.013 ,0.025 ,0.015 ,0.014 ,0.014 ,0.013 } //40-50
				                          ,{0.011 ,0.011 ,0.012 ,0.013 ,0.013 ,0.025 ,0.015 ,0.014 ,0.014 ,0.013}// 50-60
				                          ,{0.011 ,0.011 ,0.012 ,0.013 ,0.013 ,0.025 ,0.015 ,0.014 ,0.014 ,0.013}// 60-70 
				                          ,{0.011 ,0.011 ,0.012 ,0.013 ,0.013 ,0.025 ,0.015 ,0.014 ,0.014 ,0.013}// 70-80 
				                          ,{0.011 ,0.011 ,0.012 ,0.013 ,0.013 ,0.025 ,0.015 ,0.014 ,0.014 ,0.013}};// 80<   


  if(w2 > ( menu ==egammaMenu::eg2012?cutWeta22012[eTBin][etaBin]:cutWeta22011[eTBin][etaBin]))
    return false;
          
  return  true;
}
//----------------------------------------------------------------------------------------
bool passWstot_tight(double wstot, unsigned int eTBin, unsigned int etaBin, egammaMenu::egMenu menu){
  
  //New values for cut on shower width in 2nd sampling (rows are eT bins, columns are eta bins)
  //                               0.0   0.1    0.6    0.8   1.15   1.37   1.52   1.81    2.01   2.37   2.47
  const double cutWstot2012[11][10]  = {{3.48, 3.48, 3.78, 3.96, 4.20, 9999., 4.02, 2.70, 1.86,  9999.} // < 5    GeV
				    ,{3.18, 3.18, 3.54, 3.90, 4.02, 9999., 3.96, 2.70, 1.80,  9999.} //5-10   
				    ,{2.80, 2.80, 3.10, 3.30, 3.50, 9999., 3.70, 2.40, 1.70,  9999.} // 10-15 
            ,{2.70, 2.70, 2.92, 3.24, 3.40, 9999., 3.60, 2.40, 1.70,  9999.} // 15-20 
            ,{2.50, 2.50, 2.65, 3.00, 3.20, 9999., 3.30, 2.15, 1.49,  9999.} // 20-30  
				    ,{2.45, 2.45, 2.65, 2.98, 3.17, 9999., 3.30, 2.15, 1.49,  9999.} // 30-40  
				    ,{2.27, 2.27, 2.61, 2.90, 3.17, 9999., 3.30, 2.15, 1.49,  9999.} // 40-50  
				    ,{2.27, 2.27, 2.61, 2.90, 3.17, 9999., 3.30, 2.15, 1.49,  9999.} // 50-60  
				    ,{2.27, 2.27, 2.61, 2.90, 3.17, 9999., 3.30, 2.15, 1.49,  9999.} // 60-70  
				    ,{2.27, 2.27, 2.61, 2.90, 3.17, 9999., 3.30, 2.15, 1.49,  9999.} // 70-80  
				    ,{2.27, 2.27, 2.61, 2.90, 3.17, 9999., 3.30, 2.15, 1.49,  9999.}};  // 80<    
  
  const double cutWstot2011[11][10]  = {{3.48, 3.48, 3.78, 3.96, 4.20, 9999., 4.02, 2.70, 1.86,  9999.} // < 5    GeV
				    ,{3.18, 3.18, 3.54, 3.90, 4.02, 9999., 3.96, 2.70, 1.80,  9999.} //5-10   
				    ,{2.80, 2.80, 3.10, 3.30, 3.50, 9999., 3.70, 2.40, 1.70,  9999.} // 10-15 
            ,{2.70, 2.70, 2.92, 3.24, 3.40, 9999., 3.60, 2.40, 1.70,  9999.} // 15-20 
            ,{2.50, 2.50, 2.70, 3.14, 3.23, 9999., 3.58, 2.32, 1.59,  9999.} // 20-30  
				    ,{2.45, 2.45, 2.70, 2.98, 3.17, 9999., 3.52, 2.25, 1.58,  9999.} // 30-40  
				    ,{2.27, 2.27, 2.61, 2.90, 3.17, 9999., 3.36, 2.25, 1.55,  9999.} // 40-50  
				    ,{2.27, 2.27, 2.61, 2.90, 3.17, 9999., 3.36, 2.25, 1.55,  9999.} // 50-60  
				    ,{2.27, 2.27, 2.61, 2.90, 3.17, 9999., 3.36, 2.25, 1.55,  9999.} // 60-70  
				    ,{2.27, 2.27, 2.61, 2.90, 3.17, 9999., 3.36, 2.25, 1.55,  9999.} // 70-80  
				    ,{2.27, 2.27, 2.61, 2.90, 3.17, 9999., 3.36, 2.25, 1.55,  9999.}};  // 80<    


  if(wstot > (menu == egammaMenu::eg2012?cutWstot2012[eTBin][etaBin]:cutWstot2011[eTBin][etaBin]))
    return false;
    
  return  true;
}

//----------------------------------------------------------------------------------------
bool passWstot_loose(double wstot, unsigned int eTBin, unsigned int etaBin, egammaMenu::egMenu menu){
  
  //New values for cut on shower width in 2nd sampling (rows are eT bins, columns are eta bins)
  //                               0.0   0.1    0.6    0.8   1.15   1.37   1.52   1.81    2.01   2.37   2.47
  const double cutWstot2012[11][10]  = {{9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999.,  9999.} // < 5    GeV
				    ,{9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999.,  9999.} // 5-10   
				    ,{3.20, 3.20, 3.20, 3.85, 3.85, 9999., 3.80, 3.000, 2.00, 9999} //10-15
				    ,{3.00, 3.00, 3.00, 3.75, 3.75, 9999., 3.80, 3.000, 2.00, 9999} //15-20
				    ,{2.90, 2.90, 2.90, 3.50, 3.50, 9999., 3.80, 3.000, 2.00, 9999} //20-30
				    ,{2.80, 2.80, 2.80, 3.30, 3.40, 9999., 3.70, 3.000, 1.70, 9999} //30-40
				    ,{2.80, 2.80, 2.80, 3.20, 3.40, 9999., 3.70, 2.900, 1.60, 9999} //40-50
				    ,{2.80 ,2.80 ,2.80 ,3.20 ,3.40, 9999 ,3.70 ,2.900 ,1.60 ,9999}  // 50-60  
				    ,{2.80 ,2.80 ,2.80 ,3.20 ,3.40, 9999 ,3.70 ,2.900 ,1.60 ,9999}  // 60-70   
				    ,{2.80 ,2.80 ,2.80 ,3.20 ,3.40, 9999 ,3.70 ,2.900 ,1.60 ,9999}  // 70-80   
				    ,{2.80 ,2.80 ,2.80 ,3.20 ,3.40, 9999 ,3.70 ,2.900 ,1.60 ,9999}};   // 80<    

  const double cutWstot2011[11][10]  = {{9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999.,  9999.} // < 5    GeV
            ,{9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999., 9999.,  9999.} // 5-10   
            ,{3.20, 3.20, 3.20, 3.85, 3.85, 9999., 3.80, 3.000, 2.00, 9999} //10-15
            ,{3.00, 3.00, 3.00, 3.75, 3.75, 9999., 3.80, 3.000, 2.00, 9999} //15-20
            ,{2.90, 2.90, 2.90, 3.50, 3.50, 9999., 3.80, 3.000, 2.00, 9999} //20-30
            ,{2.80, 2.80, 2.80, 3.30, 3.40, 9999., 3.70, 3.000, 1.70, 9999} //30-40
            ,{2.80, 2.80, 2.80, 3.20, 3.40, 9999., 3.70, 2.900, 1.60, 9999} //40-50
            ,{2.80 ,2.80 ,2.80 ,3.20 ,3.40, 9999 ,3.70 ,2.900 ,1.60 ,9999}  // 50-60 
            ,{2.80 ,2.80 ,2.80 ,3.20 ,3.40, 9999 ,3.70 ,2.900 ,1.60 ,9999}  // 60-70   
            ,{2.80 ,2.80 ,2.80 ,3.20 ,3.40, 9999 ,3.70 ,2.900 ,1.60 ,9999}  // 70-80   
            ,{2.80 ,2.80 ,2.80 ,3.20 ,3.40, 9999 ,3.70 ,2.900 ,1.60 ,9999}};   // 80<   
  

  if(wstot > (menu == egammaMenu::eg2012?cutWstot2012[eTBin][etaBin]:cutWstot2011[eTBin][etaBin]))
    return false;
  
  return  true;
}
//----------------------------------------------------------------------------------------
bool passEratio_tight(double DEmaxs1, unsigned int eTBin, unsigned int etaBin, egammaMenu::egMenu menu){
  
  
  //cut on (Emax - Emax2)/(Emax + Emax2) in 1st sampling 
  //                               0.0   0.1    0.6    0.8   1.15   1.37   1.52   1.81    2.01   2.37   2.47
  const double cutDEmaxs12012[11][10] = {{0.640, 0.600, 0.560, 0.36, 0.24, -9999., 0.320, 0.640, 0.760, -9999.  }// < 5  
				     ,{0.640, 0.600, 0.560, 0.36, 0.24, -9999., 0.320, 0.640, 0.760, -9999.  } // 5-10
				     ,{0.810, 0.810, 0.810, 0.66, 0.68, -9999., 0.700, 0.880, 0.900, -9999.  }  //10-15 
             ,{0.835, 0.835, 0.835, 0.73 , 0.70, -9999., 0.750, 0.900, 0.900, -9999. }  //15-20 
             ,{0.835, 0.835, 0.835, 0.80,  0.80,  -9999., 0.8,   0.9 ,  0.91,  -9999.} // 20-30 
				     ,{0.835, 0.835, 0.835, 0.80,  0.80,  -9999., 0.8,   0.9 ,  0.91,  -9999.} // 30-40
				     ,{0.835, 0.835, 0.835, 0.80,  0.80,  -9999., 0.8,   0.9 ,  0.91,  -9999.} // 40-50
				     ,{0.835, 0.835, 0.835, 0.80,  0.80,  -9999., 0.8,   0.9 ,  0.91,  -9999.} // 50-60 
				     ,{0.835, 0.835, 0.835, 0.80,  0.80,  -9999., 0.8,   0.9 ,  0.91,  -9999.} // 60-70
				     ,{0.835, 0.835, 0.835, 0.80,  0.80,  -9999., 0.8,   0.9 ,  0.91,  -9999.} // 70-80
				     ,{0.835, 0.835, 0.835, 0.80,  0.80,  -9999., 0.8,   0.9 ,  0.91,  -9999.}}; // 80<
  
  const double cutDEmaxs12011[11][10] = {{0.39,   0.39,  0.20,  0.07, 0.06,  -9999.,  0.07,  0.43,   0.75, -9999.} // < 5  
				     ,{0.61,  0.61,  0.32,  0.11, 0.13,  -9999.,  0.12,  0.51,   0.62, -9999.} // 5-10
				     ,{0.810, 0.810, 0.810, 0.66, 0.68, -9999., 0.700, 0.880, 0.900, -9999.}  //10-15 
             ,{0.835, 0.835, 0.835, 0.73 , 0.70, -9999., 0.750, 0.900, 0.900, -9999.}  //15-20 
             ,{0.835, 0.835, 0.835, 0.73,  0.70,  -9999., 0.8,   0.9 ,  0.91,  -9999.} // 20-30 
				     ,{0.835, 0.835, 0.835, 0.73,  0.70,  -9999., 0.8,   0.9 ,  0.91,  -9999.} // 30-40
				     ,{0.835, 0.835, 0.835, 0.73,  0.70,  -9999., 0.8,   0.9 ,  0.91,  -9999.} // 40-50
				     ,{0.835, 0.835, 0.835, 0.73,  0.70,  -9999., 0.8,   0.9 ,  0.91,  -9999.} // 50-60 
				     ,{0.835, 0.835, 0.835, 0.73,  0.70,  -9999., 0.8,   0.9 ,  0.91,  -9999.} // 60-70
				     ,{0.835, 0.835, 0.835, 0.73,  0.70,  -9999., 0.8,   0.9 ,  0.91,  -9999.} // 70-80
				     ,{0.835, 0.835, 0.835, 0.73,  0.70,  -9999., 0.8,   0.9 ,  0.91,  -9999.}}; // 80<



  if(DEmaxs1 < (menu ==egammaMenu::eg2012?cutDEmaxs12012[eTBin][etaBin]:cutDEmaxs12011[eTBin][etaBin]))
    return false;
    
  return  true;
}

//----------------------------------------------------------------------------------------
bool passEratio_med(double DEmaxs1, unsigned int eTBin, unsigned int etaBin, egammaMenu::egMenu menu){
  
  
  //cut on (Emax - Emax2)/(Emax + Emax2) in 1st sampling 
  //                               0.0   0.1    0.6    0.8   1.15   1.37   1.52   1.81    2.01   2.37   2.47
  const double cutDEmaxs12012[11][10] = {{0.640, 0.600, 0.560, 0.36, 0.24, -9999., 0.320, 0.640, 0.760, -9999.  }// < 5  
				     ,{0.640, 0.600, 0.560, 0.36, 0.24, -9999., 0.320, 0.640, 0.760, -9999.  }// 5-10
				     ,{0.8, 0.8, 0.79, 0.61, 0.6, -9999.0, 0.65, 0.86, 0.85, -9999.0}   //10-15
				     ,{0.83, 0.83, 0.825, 0.7, 0.65, -9999.0, 0.75, 0.9, 0.89, -9999.0} //15-20
				     ,{0.835, 0.835, 0.835, 0.8, 0.8, -9999.0, 0.8, 0.9, 0.91, -9999.0} // 20-30 
				     ,{0.835, 0.835, 0.835, 0.8, 0.8, -9999.0, 0.8, 0.9, 0.91, -9999.0} // 30-40
				     ,{0.835, 0.835, 0.835, 0.8, 0.8, -9999.0, 0.8, 0.9, 0.91, -9999.0} // 40-50
				     ,{0.835, 0.835, 0.835, 0.8, 0.8, -9999.0, 0.8, 0.9, 0.91, -9999.0} // 50-60 
				     ,{0.835, 0.835, 0.835, 0.8, 0.8, -9999.0, 0.8, 0.9, 0.91, -9999.0}  // 60-70
				     ,{0.835, 0.835, 0.835, 0.8, 0.8, -9999.0, 0.8, 0.9, 0.91, -9999.0} // 70-80
				     ,{0.835, 0.835, 0.835, 0.8, 0.8, -9999.0, 0.8, 0.9, 0.91, -9999.0} }; // 80<

  const double cutDEmaxs12011[11][10] = { {0.39,  0.39,  0.20,  0.07, 0.06,  -9999.,  0.07,  0.43,   0.75,  -9999.}// < 5  
				     ,{0.61,  0.61,  0.32,  0.11, 0.13,  -9999.,  0.12,  0.51,   0.62,  -9999.}// 5-10
				     ,{0.800 ,0.800 ,0.790 ,0.660 ,0.650, -9999 ,0.650 ,0.860 ,0.850, -9999.} //10-15
				     ,{0.830 ,0.830 ,0.825 ,0.730 ,0.670, -9999 ,0.750 ,0.900 ,0.890, -9999.} //15-20
				     ,{0.835, 0.835, 0.835, 0.73,  0.70,  -9999., 0.8,   0.9 ,  0.91,  -9999.} // 20-30 
				     ,{0.835, 0.835, 0.835, 0.73,  0.70,  -9999., 0.8,   0.9 ,  0.91,  -9999.} // 30-40
				     ,{0.835, 0.835, 0.835, 0.73,  0.70,  -9999., 0.8,   0.9 ,  0.91,  -9999.} // 40-50
				     ,{0.835, 0.835, 0.835, 0.73,  0.70,  -9999., 0.8,   0.9 ,  0.91,  -9999.} // 50-60 
				     ,{0.835, 0.835, 0.835, 0.73,  0.70,  -9999., 0.8,   0.9 ,  0.91,  -9999.} // 60-70
				     ,{0.835, 0.835, 0.835, 0.73,  0.70,  -9999., 0.8,   0.9 ,  0.91,  -9999.} // 70-80
				     ,{0.835, 0.835, 0.835, 0.73,  0.70,  -9999., 0.8,   0.9 ,  0.91,  -9999.}}; // 80<


  if(DEmaxs1 < (menu ==egammaMenu::eg2012?cutDEmaxs12012[eTBin][etaBin]:cutDEmaxs12011[eTBin][etaBin]))
    return false;
    
  return  true;
}

//----------------------------------------------------------------------------------------
bool passEratio_loose(double DEmaxs1, unsigned int eTBin, unsigned int etaBin, egammaMenu::egMenu menu){
  
  
  //cut on (Emax - Emax2)/(Emax + Emax2) in 1st sampling 
  //                               0.0   0.1    0.6    0.8   1.15   1.37   1.52   1.81    2.01   2.37   2.47
  const double cutDEmaxs12012[11][10] = {{0.640, 0.600, 0.560, 0.36, 0.24, -9999., 0.320, 0.640, 0.760, -9999.  } // < 5  
				     ,{0.640, 0.600, 0.560, 0.36, 0.24, -9999., 0.320, 0.640, 0.760, -9999.  } // 5-10  
				     ,{0.790 ,0.790 ,0.750 ,0.590 ,0.530, -9999 ,0.600 ,0.790 ,0.840, -9999.} //10-15
				     ,{0.790 ,0.790 ,0.790 ,0.600 ,0.550, -9999 ,0.600 ,0.790 ,0.850, -9999.} //15-20
				     ,{0.800 ,0.800 ,0.820 ,0.720 ,0.650, -9999 ,0.780 ,0.790 ,0.850, -9999 } //20-30
				     ,{0.800 ,0.800 ,0.825 ,0.720 ,0.690, -9999 ,0.780 ,0.810 ,0.880, -9999 } //30-40
				     ,{0.800 ,0.800 ,0.825 ,0.730 ,0.690, -9999 ,0.790 ,0.810 ,0.880, -9999 } //40-50
				     ,{0.800 ,0.800 ,0.825 ,0.730 ,0.690 ,-9999. ,0.790 ,0.810 ,0.880 ,-9999.}// 50-60  
				     ,{0.800 ,0.800 ,0.825 ,0.730 ,0.690 ,-9999. ,0.790 ,0.810 ,0.880 ,-9999.}// 60-70
				     ,{0.800 ,0.800 ,0.825 ,0.730 ,0.690 ,-9999. ,0.790 ,0.810 ,0.880 ,-9999.}// 70-80
				     ,{0.800 ,0.800 ,0.825 ,0.730 ,0.690 ,-9999. ,0.790 ,0.810 ,0.880 ,-9999.}};// 80<  
  
  const double cutDEmaxs12011[11][10] = {{-9999., -9999.,-9999., -9999., -9999.,-9999.,-9999.,-9999., -9999., -9999.} // < 5  
				     ,{-9999.,   -9999.,  -9999.,  -9999., -9999.,  -9999.,  -9999.,  -9999.,   -9999., -9999.}	 // 5-10  
				     ,{0.790 ,0.790 ,0.750 ,0.590 ,0.530, -9999 ,0.600 ,0.790 ,0.840, -9999.} //10-15
				     ,{0.790 ,0.790 ,0.790 ,0.700 ,0.580, -9999 ,0.600 ,0.790 ,0.850, -9999.} //15-20
				     ,{0.800 ,0.800 ,0.820 ,0.720 ,0.650, -9999 ,0.780 ,0.790 ,0.850, -9999 } //20-30
				     ,{0.800 ,0.800 ,0.825 ,0.720 ,0.690, -9999 ,0.780 ,0.810 ,0.880, -9999 } //30-40
				     ,{0.800 ,0.800 ,0.825 ,0.730 ,0.690, -9999 ,0.790 ,0.810 ,0.880, -9999 } //40-50
				     ,{0.800 ,0.800 ,0.825 ,0.730 ,0.690 ,-9999. ,0.790 ,0.810 ,0.880 ,-9999.}// 50-60  
				     ,{0.800 ,0.800 ,0.825 ,0.730 ,0.690 ,-9999. ,0.790 ,0.810 ,0.880 ,-9999.}// 60-70
				     ,{0.800 ,0.800 ,0.825 ,0.730 ,0.690 ,-9999. ,0.790 ,0.810 ,0.880 ,-9999.}// 70-80
				     ,{0.800 ,0.800 ,0.825 ,0.730 ,0.690 ,-9999. ,0.790 ,0.810 ,0.880 ,-9999.}};// 80<  


  if(DEmaxs1 < (menu ==egammaMenu::eg2012?cutDEmaxs12012[eTBin][etaBin]:cutDEmaxs12011[eTBin][etaBin]))
    return false;

  return  true;
}

//----------------------------------------------------------------------------------------
bool passDeltaEta_med(double deltaEta ){
  
  const double cutDeltaEta = 0.005;
  
  if(fabs(deltaEta) > cutDeltaEta)
    return false;
    
  return  true;
}

//----------------------------------------------------------------------------------------
bool passDeltaEta_loose(double deltaEta){
  
  const double cutDeltaEta = 0.015;

  if(fabs(deltaEta) > cutDeltaEta)
    return false;
    
  return  true;
}
//----------------------------------------------------------------------------------------
bool passNPix_med(int nPix, unsigned int etaBin, egammaMenu::egMenu menu){
  
  //New values for cut on nPixHits (when nblayer cut is dropped at high eta)
  //                          0.0   0.1    0.6    0.8   1.15   1.37   1.52   1.81    2.01   2.37   2.47
  const double cutNPix2011[10] = { 1, 1, 1, 1, 1, 1, 1, 1, 2, 2};   
  const double cutNPix2012[10] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};   
				    
  if(nPix < (menu==egammaMenu::eg2012?cutNPix2012[etaBin]:cutNPix2011[etaBin]))
    return false;
    
  return  true;
}

//----------------------------------------------------------------------------------------
bool passNBlayer_tight(int nBlayer, unsigned int etaBin){
  
  //New values for cut on nPixHits (when nblayer cut is dropped at high eta)
  //                          0.0   0.1    0.6    0.8   1.15   1.37   1.52   1.81    2.01   2.37   2.47
  const double cutNBlayer[10] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};   
				    
  if(nBlayer < cutNBlayer[etaBin])
    return false;
    
  return  true;
}

//----------------------------------------------------------------------------------------
bool passNBlayer_med(int nBlayer, unsigned int etaBin, egammaMenu::egMenu menu){
  
  //New values for cut on nPixHits (when nblayer cut is dropped at high eta)
  //                          0.0   0.1    0.6    0.8   1.15   1.37   1.52   1.81    2.01   2.37   2.47
  const double cutNBlayer2012[10] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 0};   
  const double cutNBlayer2011[10] = { 1, 1, 1, 1, 1, 1, 1, 1, 0, 0};   
				    
  if(nBlayer < (menu==egammaMenu::eg2012?cutNBlayer2012[etaBin]:cutNBlayer2011[etaBin]))
    return false;
    
  return  true;
}
//----------------------------------------------------------------------------------------
bool passTR_med(double TRratio, double eta, unsigned int  nTRT, egammaMenu::egMenu menu ){

 
  int ibin_eta_TRT = -1;
  
  if (nTRT == 0) return true; 
  double CutTR2012[6] = {0.05, 0.08, 0.075, 0.09, 0.105, 0.110};
  double CutTR2011[6] = {0.05, 0.05, 0.05, 0.06, 0.08, 0.08};
  
  double CutBinEta_TRT[6] = {0.1, 0.625, 1.07, 1.304, 1.752, 2.0};

 for (unsigned int ibinEta=0;ibinEta<6;ibinEta++) 
 {
    if ( ibinEta == 0 )
    {
      if ( eta < CutBinEta_TRT[ibinEta] ) 
         {
	           ibin_eta_TRT = ibinEta;
         }
    } 
    else 
    {
      if ( eta >= CutBinEta_TRT[ibinEta-1] && eta < CutBinEta_TRT[ibinEta] ) 
         {
	           ibin_eta_TRT = ibinEta;
         }
    }
  }
  if (ibin_eta_TRT >= 0) {
     if (float(TRratio) < float(menu==egammaMenu::eg2012?CutTR2012[ibin_eta_TRT]:CutTR2011[ibin_eta_TRT])) return false; 
  } 
   return true;
}

//----------------------------------------------------------------------------------------
bool passTR_tight(double TRratio, double eta, egammaMenu::egMenu menu){

 
  int ibin_eta_TRT = -1;
  double CutTR2012[6] = {0.09, 0.105, 0.11, 0.125, 0.145, 0.16};
  double CutTR2011[6] = {0.08, 0.085, 0.085, 0.115, 0.13, 0.155};
  
  double CutBinEta_TRT[6] = {0.1, 0.625, 1.07, 1.304, 1.752, 2.0};

 for (unsigned int ibinEta=0;ibinEta<6;ibinEta++) 
 {
    if ( ibinEta == 0 )
    {
      if ( eta < CutBinEta_TRT[ibinEta] ) 
         {
	           ibin_eta_TRT = ibinEta;
         }
    } 
    else 
    {
      if ( eta >= CutBinEta_TRT[ibinEta-1] && eta < CutBinEta_TRT[ibinEta] ) 
         {
	           ibin_eta_TRT = ibinEta;
         }
    }
  }
  if (ibin_eta_TRT >= 0) {

     if (float(TRratio) < float(menu==egammaMenu::eg2012?CutTR2012[ibin_eta_TRT]:CutTR2011[ibin_eta_TRT])) return false; 
  } 
   return true;
}

//----------------------------------------------------------------------------------------
bool passEOverP_tight(double eOverP, unsigned int eTBin, unsigned int etaBin){

  // Minimum Cut on E/p 
  const double minEp[11][10]  = {{0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.80, 0.60, 0.60} // < 5 GeV
             ,{0.800, 0.800, 0.800, 0.800, 0.800, 0.800, 0.700, 0.700, 0.600, 0.600}  // 5-10  
             ,{0.800, 0.800, 0.800, 0.775, 0.775, 0.775, 0.525, 0.625, 0.575, 0.525}  // 10-15
             ,{0.775, 0.775, 0.775, 0.775, 0.700, 0.700, 0.525, 0.575, 0.575, 0.525}  // 15-20
             ,{0.700, 0.700, 0.700, 0.700, 0.675, 0.675, 0.500, 0.500, 0.450, 0.450}  // 20-30
             ,{0.700, 0.700, 0.700, 0.700, 0.625, 0.675, 0.500, 0.500, 0.450, 0.450}  // 30-40
             ,{0.700, 0.700, 0.700, 0.700, 0.625, 0.675, 0.500, 0.500, 0.450, 0.450}  // 40-50
             ,{0.700, 0.700, 0.700, 0.700, 0.625, 0.675, 0.500, 0.500, 0.450, 0.450}  // 50-60
             ,{0.700, 0.700, 0.700, 0.700, 0.625, 0.675, 0.500, 0.500, 0.450, 0.450}  // 60-70
             ,{0.700, 0.700, 0.700, 0.700, 0.625, 0.675, 0.500, 0.500, 0.450, 0.450}  // 70-80
             ,{0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000}};// > 80  
                  

  // Max cut on E/p
  const double maxEp[11][10]  = {{2.3, 2.3, 2.3, 2.3, 2.3, 2.5, 2.5, 2.5, 3.0, 3.0} // < 5 GeV
             ,{2.3, 2.3, 2.3, 2.3, 2.3, 2.5, 2.5, 2.5, 3.0, 3.0} // 5-10  
             ,{2.3, 2.3, 2.3, 2.3, 2.3, 3.0, 2.5, 2.5, 3.0, 3.5} // 10-15
             ,{2.5, 2.5, 2.5, 2.5, 2.5, 3.0, 3.0, 3.0, 3.5, 3.5} // 15-20
             ,{2.5, 2.5, 2.5, 2.5, 2.5, 3.0, 3.0, 3.0, 4.0, 4.0} // 20-30
             ,{3.0, 3.0, 3.0, 3.0, 3.0, 3.5, 3.5, 3.5, 4.0, 4.0} // 30-40
             ,{3.0, 3.0, 3.0, 3.0, 3.0, 3.5, 3.5, 4.0, 4.5, 4.5} // 40-50
             ,{5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 4.0, 5.0, 5.0, 5.0} // 50-60
             ,{5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0} // 60-70
             ,{5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0} // 70-80
             ,{10., 10., 10., 10., 10., 10., 10., 10., 10., 10.}}; // > 80    
             
  if ((eOverP < minEp[eTBin][etaBin]) || (eOverP > maxEp[eTBin][etaBin])) 
    return false;

  return true; 
}

//----------------------------------------------------------------------------------------
bool passDeltaPhi_tight(double deltaPhi, unsigned int eTBin, unsigned int etaBin){

  // cut max on delta phi
  const double maxDeltaPhi[11][10]  = {{ 0.015, 0.015, 0.015, 0.015, 0.015, 0.015, 0.015, 0.015, 0.015, 0.015} // < 5 GeV 
             ,{0.015, 0.015, 0.015, 0.015, 0.015, 0.015, 0.015, 0.015, 0.015, 0.015} // 5-10 
             ,{0.015, 0.015, 0.015, 0.015, 0.015, 0.015, 0.015, 0.015, 0.015, 0.015} // 10-15
             ,{0.0125, 0.0125, 0.0125, 0.0125, 0.0125, 0.0125, 0.0125, 0.0125, 0.0125, 0.0125} // 15-20
             ,{0.010, 0.010, 0.010, 0.010, 0.010, 0.010, 0.010, 0.010, 0.010, 0.010} // 20-30
             ,{0.010, 0.010, 0.010, 0.010, 0.010, 0.010, 0.010, 0.010, 0.010, 0.010} // 30-40
             ,{0.010, 0.010, 0.010, 0.010, 0.010, 0.010, 0.010, 0.010, 0.010, 0.010} // 40-50
             ,{0.010, 0.010, 0.010, 0.010, 0.010, 0.010, 0.010, 0.010, 0.010, 0.010} // 50-60
             ,{0.010, 0.010, 0.010, 0.010, 0.010, 0.010, 0.010, 0.010, 0.010, 0.010} // 60-70
             ,{0.010, 0.010, 0.010, 0.010, 0.010, 0.010, 0.010, 0.010, 0.010, 0.010} // 70-80
             ,{0.010, 0.010, 0.010, 0.010, 0.010, 0.010, 0.010, 0.010, 0.010, 0.010}}; // > 80 

                                     
  // cut min on deltaphi 
  const double minDeltaPhi[11][10]  = {{-0.03, -0.03, -0.03, -0.04, -0.04, -0.04, -0.04, -0.04, -0.04, -0.04} // < 5 GeV
             ,{-0.03, -0.03, -0.03, -0.04, -0.04, -0.04, -0.04, -0.04, -0.04, -0.04} // 5-10 
             ,{-0.03, -0.03, -0.03, -0.04, -0.04, -0.04, -0.04, -0.04, -0.04, -0.04} // 10-15
             ,{-0.03, -0.03, -0.03, -0.04, -0.04, -0.04, -0.04, -0.04, -0.04, -0.04} // 15-20
             ,{-0.03, -0.03, -0.03, -0.04, -0.04, -0.04, -0.04, -0.04, -0.04, -0.04} // 20-30
             ,{-0.03, -0.03, -0.03, -0.04, -0.04, -0.04, -0.04, -0.04, -0.04, -0.04} // 30-40
             ,{-0.03, -0.03, -0.03, -0.04, -0.04, -0.04, -0.04, -0.04, -0.04, -0.04} // 40-50
             ,{-0.03, -0.03, -0.03, -0.04, -0.04, -0.04, -0.04, -0.04, -0.04, -0.04} // 50-60
             ,{-0.03, -0.03, -0.03, -0.04, -0.04, -0.04, -0.04, -0.04, -0.04, -0.04} // 60-70
             ,{-0.03, -0.03, -0.03, -0.04, -0.04, -0.04, -0.04, -0.04, -0.04, -0.04} // 70-80
             ,{-0.03, -0.03, -0.03, -0.04, -0.04, -0.04, -0.04, -0.04, -0.04, -0.04}}; // > 80  
                               
   if ((deltaPhi < minDeltaPhi[eTBin][etaBin]) || (deltaPhi > maxDeltaPhi[eTBin][etaBin]))
     return false; 

   return true; 
}
//----------------------------------------------------------------------------------------
bool passNTRT_tight(int nTRT,  double eta){ 
//nTRT Hits
  double DeltaNum = -100;
  // coefficients to aproximate Number of TRT hits:
  // zone 0: eta<0.1 parabolic
  const double a0 = 33.14 ; const double b0 = -129.1 ; const double c0 = 1455.;
  // zone 1: eta<0.625 cubic
  const double a1 = 29.42 ; const double b1 = 27.93 ; const double c1 = -89.96; const double d1 = 91.51;
  // zone 2: eta<1.07 parabolic
  const double a2 = 196.3; const double b2 = -403.; const double c2 = 230.2;
  // zone 3: eta <1.304 linear
  const double a3 = -10.59; const double b3 = 37.29;
  // zone 4: eta <1.752 cubic
  const double a4 = -640.9; const double b4 = 1323.; const double c4 = -851.8; const double d4 = 180.8;
  // zone 5: eta <2.0 linear
  const double a5 = 159.8; const double b5 = -70.9;
  
  int ibin_eta_TRT = -1;
  // loop on eta range

  double CutBinEta_TRT[6] = {0.1, 0.625, 1.07, 1.304, 1.752, 2.0};

  double CutNumTRT = -15.; 

 for (unsigned int ibinEta=0;ibinEta<6;ibinEta++) 
 {
    if ( ibinEta == 0 )
    {
      if ( eta < CutBinEta_TRT[ibinEta] ) 
         {
	           ibin_eta_TRT = ibinEta;
         }
    } 
    else 
    {
      if ( eta >= CutBinEta_TRT[ibinEta-1] && eta < CutBinEta_TRT[ibinEta] ) 
         {
	           ibin_eta_TRT = ibinEta;
         }
    }
  }
  if (ibin_eta_TRT >= 0) {
    switch (ibin_eta_TRT) {
      
    case 0:
      DeltaNum = nTRT - (a0 + b0*eta + c0*eta*eta);
      break;
      
    case 1:
      DeltaNum = nTRT - (a1 + b1*eta + c1*eta*eta + d1*eta*eta*eta);
      break;
      
    case 2:
      DeltaNum = nTRT - (a2 + b2*eta + c2*eta*eta) ;
      break;
      
    case 3:
      DeltaNum = nTRT - (a3 + b3*eta);
      break;
      
    case 4: 
      DeltaNum = nTRT - (a4 + b4*eta + c4*eta*eta + d4*eta*eta*eta);
      break;
      
    case 5: 
      DeltaNum = nTRT - (a5 + b5*eta);
    }
    
    if (DeltaNum <CutNumTRT) 
      {
	     return false; 
      }
    }

return true;


}

//----------------------------------------------------------------------------------------
bool passTrackIso(double ptcone20, double et){ 

  if (et == 0) return false;

  double ptcone20pt = ptcone20/et; 

  if (ptcone20pt > 0.1) return false; 

  return true;  
}


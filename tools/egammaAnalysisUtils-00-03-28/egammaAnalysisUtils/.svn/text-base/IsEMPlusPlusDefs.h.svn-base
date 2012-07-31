#ifndef ISEMPLUSPLUSDEFS_H
#define ISEMPLUSPLUSDEFS_H

#include <fstream>
#include <iostream>

//enum for menu decision 
namespace egammaMenu {
  enum egMenu {
     eg2011,
     eg2012
       };
}

//-------------------------------------------------------------------------------------------------------
bool isLoosePlusPlus0(double eta, double eT,
		     double rHad, double rHad1, double Reta, double w2,
		     double f1, double wstot, double DEmaxs1, double deltaEta, int nSi,
         int nSiOutliers, int nPix, int nPixOutliers, egammaMenu::egMenu menu = egammaMenu::eg2012,  bool debug = false, bool isTrigger = false );
//-------------------------------------------------------------------------------------------------------
bool isLoosePlusPlus1(double eta, double eT,
		     double rHad, double rHad1, double Reta, double w2,
		     double f1, double wstot, double DEmaxs1, double deltaEta, int nSi,
         int nSiOutliers, int nPix, int nPixOutliers,  egammaMenu::egMenu menu = egammaMenu::eg2012, bool debug = false,bool isTrigger = false );
//-------------------------------------------------------------------------------------------------------
bool isLoosePlusPlus(double eta, double eT,
		     double rHad, double rHad1, double Reta, double w2,
		     double f1, double wstot, double DEmaxs1, double deltaEta, int nSi,
         int nSiOutliers, int nPix, int nPixOutliers, egammaMenu::egMenu menu = egammaMenu::eg2012,  bool debug = false, bool isTrigger = false );
//-------------------------------------------------------------------------------------------------------
bool isMediumPlusPlus(double eta, double eT, double f3,
		      double rHad, double rHad1, double Reta, double w2, 
		      double f1, double wstot, double DEmaxs1, double deltaEta, double d0,
		      double TRratio, int nTRT, int nTRTOutliers,
		      int nSi, int nSiOutliers, int nPix, int nPixOutliers, 
		      int nBlayer, int nBlayerOutliers, bool expectBlayer, 
		      egammaMenu::egMenu menu = egammaMenu::eg2012, bool debug = false, bool isTrigger = false );
//-------------------------------------------------------------------------------------------------------
bool isTightPlusPlus(double eta, double eT, double f3,
		      double rHad, double rHad1, double Reta, double w2, 
		      double f1, double wstot, double DEmaxs1, double deltaEta, double d0, 
		      double TRratio, int nTRT, int nTRTOutliers,
		      int nSi, int nSiOutliers, int nPix, int nPixOutliers, 
		      int nBlayer, int nBlayerOutliers, bool expectBlayer,
          double eOverp, double deltaphi, int convBit,   
		      egammaMenu::egMenu menu = egammaMenu::eg2012, bool debug = false, bool isTrigger = false );


// Loose++ Helper Functions 
bool passRHad_loose(double rhad, double rhad1, unsigned int etbin, unsigned int etabin, egammaMenu::egMenu menu = egammaMenu::eg2012);
bool passReta_loose(double reta, unsigned int etbin, unsigned int etabin, egammaMenu::egMenu menu = egammaMenu::eg2012);
bool passW2_loose(double w2, unsigned int etbin, unsigned int etabin, egammaMenu::egMenu menu = egammaMenu::eg2012);
bool passWstot_loose(double wstot, unsigned int etbin, unsigned int etabin, egammaMenu::egMenu menu = egammaMenu::eg2012);
bool passEratio_loose(double demaxs1, unsigned int etbin, unsigned int etabin, egammaMenu::egMenu menu = egammaMenu::eg2012);
bool passDeltaEta_loose(double deltaEta);

// Medium++ Helper Functions 
bool passRHad_med(double rHad, double rHad1, unsigned int eTBin, unsigned int etaBin, egammaMenu::egMenu menu = egammaMenu::eg2012);
bool passReta_med(double rEta, unsigned int eTBin, unsigned int etaBin, egammaMenu::egMenu menu = egammaMenu::eg2012);
bool passW2_med(double w2, unsigned int eTBin, unsigned int etaBin, egammaMenu::egMenu menu = egammaMenu::eg2012);
bool passWstot_med(double wstot, unsigned int eTBin, unsigned int etaBin, egammaMenu::egMenu menu = egammaMenu::eg2012);
bool passEratio_med(double DEmaxs1, unsigned int eTBin, unsigned int etaBin, egammaMenu::egMenu menu = egammaMenu::eg2012);
bool passDeltaEta_med(double deltaEta);
bool passTR_med(double TRratio, double eta, unsigned int nTRT, egammaMenu::egMenu menu = egammaMenu::eg2012);
bool passNPix_med(int nPix, unsigned int etaBin, egammaMenu::egMenu menu = egammaMenu::eg2012);
bool passNBlayer_med(int nBlayer, unsigned int etaBin, egammaMenu::egMenu menu = egammaMenu::eg2012); 
bool passf3_med(double f3, unsigned int eTBin, unsigned int etaBin);

// Tight++ Helper Functions 
bool passRHad_tight(double rHad, double rHad1, unsigned int eTBin, unsigned int etaBin, egammaMenu::egMenu menu = egammaMenu::eg2012);
bool passReta_tight(double rEta, unsigned int eTBin, unsigned int etaBin, egammaMenu::egMenu menu = egammaMenu::eg2012);
bool passW2_tight(double w2, unsigned int eTBin, unsigned int etaBin, egammaMenu::egMenu menu = egammaMenu::eg2012);
bool passWstot_tight(double wstot, unsigned int eTBin, unsigned int etaBin, egammaMenu::egMenu menu = egammaMenu::eg2012);
bool passEratio_tight(double DEmaxs1, unsigned int eTBin, unsigned int etaBin, egammaMenu::egMenu menu = egammaMenu::eg2012);
bool passTR_tight(double TRratio, double eta,  egammaMenu::egMenu menu = egammaMenu::eg2012);
bool passNBlayer_tight(int nBlayer, unsigned int etaBin); 
bool passDeltaPhi_tight(double deltaPhi, unsigned int eTBin, unsigned int etaBin); 
bool passEOverP_tight(double eOverp, unsigned int eTBin, unsigned int etaBin); 
bool passNTRT_tight(int nTRT, double eta); 

// Isolation Helper Functions
bool passTrackIso(double ptcone20, double et);


// Helper Fuctions
unsigned int getEtaBin(double eta);
unsigned int getEtBin(double eT);

//----------------------------------------------------------------------------------------
#endif

#ifndef MULTILEPTON_H
#define MULTILEPTON_H
//-------------------------------------------------------------------------------------------------------
bool passMultiLepton(double eta, double eT,
		     double rHad, double rHad1, double Reta, double w2, 
		     double f1, double f3, double wstot, double DEmaxs1, 
		     double deltaEta, int nSi, int nSiDeadSensors, int nPix, 
		     int nPixDeadSensors, double deltaPhiRes, double dpOverp, 
		     double TRratio,  int nTRTTotal,  int nBlayerHits, bool expectBlayer,bool debug=false ); 
//Helper Functions 
bool passRHad(double rhad, double rhad1, unsigned int etbin, unsigned int etabin);
bool passF3(double f3, unsigned int etbin, unsigned int etabin);
bool passReta(double reta, unsigned int etbin, unsigned int etabin);
bool passW2(double w2, unsigned int etbin, unsigned int etabin);
bool passWstot(double wstot, unsigned int etbin, unsigned int etabin);
bool passEratio(double demaxs1, unsigned int etbin, unsigned int etabin);
bool passDeltaEta(double deltaEta, unsigned int etbin, unsigned int etabin);
bool passDeltaPhiRes(double deltaPhiRes, bool isBrem, unsigned int etbin, unsigned int etabin);
bool passTR(double TRratio, double eta, unsigned int  nTRTTotal );
bool passConversion(double deltaPhiRes, bool expectBlayer,  int nBlayerHits ,unsigned int eTBin, unsigned int etaBin);
// Helper Fuctions
unsigned int getEtaBinH4l(double eta);
unsigned int getEtBinH4l(double eT);
bool getBremCategoryH4l(double dpOverp, unsigned int etbin, unsigned int etabin);

//----------------------------------------------------------------------------------------
#endif

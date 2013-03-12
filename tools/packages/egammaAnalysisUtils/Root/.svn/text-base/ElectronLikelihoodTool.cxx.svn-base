#include "egammaAnalysisUtils/ElectronLikelihoodTool.h"
//#include "egammaAnalysisUtils/IsEMPlusPlusDefs.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cassert>

/** 
    Author : Kurt Brendlinger <kurb@sas.upenn.edu>
    Please see ElectronLikelihoodTool.h for usage.
*/

//const double ElectronLikelihoodTool::fIpBounds[IP_BINS+1] = {0.,10.,500.};
const double ElectronLikelihoodTool::fIpBounds[IP_BINS+1] = {0.,500.};

//---------------------------------------------------------------------------------------
// Gets the IP bin
unsigned int ElectronLikelihoodTool::getIpBin(double ip){
  for(unsigned int ipBin = 0; ipBin < IP_BINS; ++ipBin){
    if(ip < fIpBounds[ipBin+1])
      return ipBin;
  }
  return 0;
}
//---------------------------------------------------------------------------------------
// Gets the Eta bin [0-9] given the eta
unsigned int getLikelihoodEtaBin(double eta){
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
unsigned int getLikelihoodEtBin(double eT){
  const unsigned int nEtBins = 6; // 11
  const double GeV = 1000;
  //const double eTBins[nEtBins] = {5*GeV,10*GeV,15*GeV,20*GeV,30*GeV,40*GeV,50*GeV,60*GeV,70*GeV,80*GeV};
  const double eTBins[nEtBins] = {10*GeV,15*GeV,20*GeV,30*GeV,40*GeV,50*GeV};  

  for(unsigned int eTBin = 0; eTBin < nEtBins; ++eTBin){
    if(eT < eTBins[eTBin])
      return eTBin;
  }
  
  return 5; // 10 // Return the last bin if > the last bin.
}

//---------------------------------------------------------------------------------------
// Gets the Et bin [0-10] given the et (MeV)
unsigned int getLikelihoodEtFineBin(double eT){
  const unsigned int nEtBins = 9; // 11
  const double GeV = 1000;
  //const double eTBins[nEtBins] = {5*GeV,10*GeV,15*GeV,20*GeV,30*GeV,40*GeV,50*GeV,60*GeV,70*GeV,80*GeV};
  const double eTBins[nEtBins] = {10*GeV,15*GeV,20*GeV,25*GeV,30*GeV,35*GeV,40*GeV,45*GeV,50*GeV};  

  for(unsigned int eTBin = 0; eTBin < nEtBins; ++eTBin){
    if(eT < eTBins[eTBin])
      return eTBin;
  }
  
  return 8; // Return the last bin if > the last bin.
}

//---------------------------------------------------------------------------------------
// Gets the bin name 
void ElectronLikelihoodTool::getBinName(char* buffer, int etbin,int etabin, int ipbin, std::string iptype){
  double eta_bounds[9] = {0.0,0.6,0.8,1.15,1.37,1.52,1.81,2.01,2.37};
  //int et_bounds[11] = {7,10,15,20,30,40,50,60,70,80,500};
  int et_bounds[6] = {7,10,15,20,30,40};
  if (!iptype.empty())
    sprintf(buffer, "%s%det%02deta%0.2f", iptype.c_str(), int(fIpBounds[ipbin]), et_bounds[etbin], eta_bounds[etabin]);
  else 
    sprintf(buffer, "et%deta%0.2f", et_bounds[etbin], eta_bounds[etabin]);
  return;
}
//----------------------------------------------------------------------------------------
ElectronLikelihoodTool& ElectronLikelihoodTool::Instance(std::string wfile,std::string vars,std::string ipbinning)
{
  static ElectronLikelihoodTool instance(wfile,vars,ipbinning);
  return instance;
}
//----------------------------------------------------------------------------------------
ElectronLikelihoodTool GetElectronLikelihoodTool(std::string wfile,std::string vars,std::string ipbinning)
{
  ElectronLikelihoodTool instance(wfile,vars,ipbinning);
  return instance;
}

//----------------------------------------------------------------------------------------
unsigned int ElectronLikelihoodTool::GetLikelihoodBitmask(std::string vars,bool debug){
  unsigned int mask = 0x0;
  if (debug) std::cout << "Variables to be used: ";
  for(unsigned int var = 0; var < fnVariables; var++){
    if (vars.find(fVariables[var]) != std::string::npos){
      if (debug) std::cout << fVariables[var] << " ";
      mask = mask | 0x1 << var;
    }
  }
  if (debug) std::cout << "mask: " << mask << std::endl;
  return mask;
}

//----------------------------------------------------------------------------------------
ElectronLikelihoodTool::ElectronLikelihoodTool() : 
  fDebug(false)
  ,fPDFfilename("")
  ,fVariableMask(0x0)
  ,fIpBinning("")
{  
}

ElectronLikelihoodTool::ElectronLikelihoodTool(std::string wfile,std::string vars,std::string ipbinning):
  fDebug(false)
  ,fPDFfilename(wfile)  
  ,fVariableMask(0x0)
  ,fIpBinning(ipbinning)
{
  std::cout << "egammaAnalysisUtils: pdf file (!!!): " << wfile << std::endl;
  fPDFfile = new TFile(wfile.c_str(),"READ");
  std::cout << "file booked (April 30)." << std::endl;

  fVariableMask = GetLikelihoodBitmask(vars,true);

  for(unsigned int s_or_b = 0; s_or_b < 2; s_or_b++){
    for (unsigned int ip = 0; ip < IP_BINS; ip++){ ////HERE!!!!!
      for(unsigned int et = 0; et < fnEtBins; et++){
	for(unsigned int eta = 0; eta < fnEtaBins; eta++){

	  std::string sig_bkg = (s_or_b==0) ? "sig" : "bkg" ;	  
	  // Because eta bins in the root file don't match up exactly with cut menu
	  // definitions, the second eta bin is an exact copy of the first,
	  // and all subsequent eta bins are pushed back by one.
	  unsigned int eta_tmp = (eta > 0) ? eta-1 : eta ;
	  unsigned int et_tmp = (eta == 5 && et == 0) ? 1 : et;
	  char binname[200];
	  getBinName(binname,et_tmp,eta_tmp,ip,fIpBinning);

	  //if (std::string(binname).find("1.37") != std::string::npos) 
	  //  continue;

	  for(unsigned int var = 0; var < fnVariables; var++){

	    std::string vstr = fVariables[var];
	    if (((std::string(binname).find("2.01") != std::string::npos) || (std::string(binname).find("2.37") != std::string::npos))
		&& (vstr.find("TRT") != std::string::npos))
	      continue;

	    char pdf[500];
	    sprintf(pdf,"%s/%s/%s_%s_smoothed_hist_from_KDE_%s",vstr.c_str(),sig_bkg.c_str(),vstr.c_str(),sig_bkg.c_str(),binname);
	    TH1F* hist = (TH1F*)fPDFfile->Get(pdf);

	    if (hist) {
	      std::string histname = hist->GetName();
	      fPDFbins[s_or_b][ip][et][eta][var] = (TH1F*)hist->Clone(histname.c_str());
	      fPDFbins[s_or_b][ip][et][eta][var]->SetDirectory(0);
	      int nbins = fPDFbins[s_or_b][ip][et][eta][var]->GetNbinsX();
	      fPDFIntegrals[s_or_b][ip][et][eta][var] = fPDFbins[s_or_b][ip][et][eta][var]->Integral(1,nbins);
	    }
	    else {
	      std::cout << "Warning: Object " << pdf << " does not exist." << std::endl;
	    }
	  }
	}
      }  
    }
  }
  fPDFfile->Close();
  std::cout << "Initialization complete" << std::endl;
}

ElectronLikelihoodTool::~ElectronLikelihoodTool(){
  //fPDFfile->Close();
}

bool ElectronLikelihoodTool::passLikelihood(LikeEnum::Menu operating_point,
						 double eta, double eT,double f3, double rHad, double rHad1,
						 double Reta, double w2, double f1, double DEmaxs1,
						 double deltaEta, double d0, double TRratio,
						 double d0sigma,
						 double rphi, double ws3,
						 //
						 double deltaPoverP ,double deltaphires,
						 //
						 //int nTRT, int nTRTOutliers,
						 int nSi,int nSiDeadSensors, int nPix, int nPixDeadSensors,
						 int nBlayer, int nBlayerOutliers, bool expectBlayer,
						 int convBit, double ip){

  // These values are not used in the likelihood, but 
  // the macro needs them to be present for technical reasons.
  double wstot = -9999.;
  double fside = -9999.;
  double eOverP = -9999.;  
  double deltaPhi = -9999.;  
  double ptcone20 = -9999.;
  //int nTRT = -9999;
  //int nTRTOutliers = -9999;

  if (fDebug) std::cout << "Likelihood macro: Using operating point " << operating_point << std::endl;

  if (eT < 7000.) {
    if (fDebug) std::cout << "Error! This electron is less than 7 GeV. Returning False." << std::endl;
    return false;
  }
  
  unsigned int etbin = getLikelihoodEtFineBin(eT);
  unsigned int etabin = getLikelihoodEtaBin(eta);
  unsigned int ipbin  = 0;
  unsigned int bitmask = 0;

  // sanity
  if (etbin  >= fnFineEtBins) {
    std::cout << "Cannot evaluate likelihood for Et " << eT;
    std::cout << ". Returning false.." << std::endl;
    return false;
  }

  // Tight cut requirements
  if ((operating_point == LikeEnum::Tight) ||
      (operating_point == LikeEnum::Very_Tight) ||
      (operating_point == LikeEnum::Tight_FixedBkgRejection) ||
      (operating_point == LikeEnum::Tight_FixedSignalEfficiency)) {
    if (expectBlayer) {
      const double cutNBlayerTight[10] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
      if(nBlayer + nBlayerOutliers < cutNBlayerTight[etabin]) {
	if (fDebug) std::cout << "Likelihood macro: Blayer Failed." << std::endl;
	return false;
      }
    }
    if (nPix+nPixDeadSensors < 1){
      if (fDebug) std::cout << "Likelihood macro: Pixels Failed." << std::endl;
      return false;
    }
    if (nSi + nSiDeadSensors < 7){
      if (fDebug) std::cout << "Likelihood macro: Silicon Failed." << std::endl;
      return false;
    }
    if (convBit){
      if (fDebug) std::cout << "Likelihood macro: Conversion Bit Failed." << std::endl;
      return false;
    }
    bitmask = LikelihoodTightBitmask();
  }

  // Medium cut requirements
  if ((operating_point == LikeEnum::Medium) ||
      (operating_point == LikeEnum::Medium_FixedBkgRejection) ||
      (operating_point == LikeEnum::Medium_FixedSignalEfficiency)) {
    if (expectBlayer) {
      const double cutNBlayerMedium[10] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 0};
      if(nBlayer + nBlayerOutliers < cutNBlayerMedium[etabin]) {
	if (fDebug) std::cout << "Likelihood macro: Blayer Failed." << std::endl;
	return false;
      }
    }
    if (nPix+nPixDeadSensors < 1){
      if (fDebug) std::cout << "Likelihood macro: Pixels Failed." << std::endl;
      return false;
    }
    if (nSi + nSiDeadSensors < 7){
      if (fDebug) std::cout << "Likelihood macro: Silicon Failed." << std::endl;
      return false;
    }
    bitmask = LikelihoodMediumBitmask();
  }

  // Loose / Multilepton cut requirements
  if ((operating_point == LikeEnum::Loose) ||
      (operating_point == LikeEnum::Very_Loose) ||
      (operating_point == LikeEnum::Loose1_FixedBkgRejection) ||
      (operating_point == LikeEnum::Loose1_FixedSignalEfficiency)) {
    if (nSi + nSiDeadSensors < 7){
      if (fDebug) std::cout << "Likelihood macro: Silicon Failed." << std::endl;
      return false;
    }
    if (nPix+nPixDeadSensors < 1){
      if (fDebug) std::cout << "Likelihood macro: Pixels Failed." << std::endl;
      return false;
    }
    bitmask = LikelihoodLooseBitmask();
  }

  // Loose + BL + Pix requirement
  if (operating_point == LikeEnum::Loose_BL_Pix) {
    if (nSi + nSiDeadSensors < 7){
      if (fDebug) std::cout << "Likelihood macro: Silicon Failed." << std::endl;
      return false;
    }
    if (expectBlayer) {
      const double cutNBlayerAllEta[10] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
      if(nBlayer + nBlayerOutliers < cutNBlayerAllEta[etabin]) {
	if (fDebug) std::cout << "Likelihood macro: Blayer Failed." << std::endl;
	return false;
      }
    }
    if (nPix+nPixDeadSensors < 2){
      if (fDebug) std::cout << "Likelihood macro: Pixels Failed." << std::endl;
      return false;
    }
    bitmask = LikelihoodLooseBitmask();
  }

  if ((operating_point == LikeEnum::Multilepton_FixedBkgRejection) ||
      (operating_point == LikeEnum::Multilepton_FixedSignalEfficiency)) {
    if (nSi + nSiDeadSensors < 7){
      if (fDebug) std::cout << "Likelihood macro: Silicon Failed." << std::endl;
      return false;
    }
    if (nPix+nPixDeadSensors < 1){
      if (fDebug) std::cout << "Likelihood macro: Pixels Failed." << std::endl;
      return false;
    }
    bitmask = LikelihoodMultileptonBitmask();
  }
  
  double cutDiscriminant = -999.;
  
  if ((operating_point == LikeEnum::Tight_FixedBkgRejection) || (operating_point == LikeEnum::Tight)) {
    cutDiscriminant  = Disc_Tight_FBR[ipbin][etbin][etabin];
    cutDiscriminant += ip*Disc_Tight_FBR_b[ipbin][etbin][etabin];
  }
  if ((operating_point == LikeEnum::Tight_FixedSignalEfficiency) || (operating_point == LikeEnum::Very_Tight)) {
    cutDiscriminant  = Disc_Tight_FSE[ipbin][etbin][etabin];
    cutDiscriminant += ip*Disc_Tight_FSE_b[ipbin][etbin][etabin];
  }
  if (operating_point == LikeEnum::Medium_FixedBkgRejection) {
    cutDiscriminant  = Disc_Medium_FBR[ipbin][etbin][etabin];
    cutDiscriminant += ip*Disc_Medium_FBR_b[ipbin][etbin][etabin];
  }
  if ((operating_point == LikeEnum::Medium_FixedSignalEfficiency) || (operating_point == LikeEnum::Medium)) {
    cutDiscriminant  = Disc_Medium_FSE[ipbin][etbin][etabin];
    cutDiscriminant += ip*Disc_Medium_FSE_b[ipbin][etbin][etabin];
  }
  if (operating_point == LikeEnum::Loose1_FixedBkgRejection) {
    cutDiscriminant  = Disc_Loose1_FBR[ipbin][etbin][etabin];
    cutDiscriminant += ip*Disc_Loose1_FBR_b[ipbin][etbin][etabin];
    std::cout << "Error! Loose is currently deprecated!" << std::endl;
    return -999.;
  }   
  if (operating_point == LikeEnum::Loose1_FixedSignalEfficiency) {
    cutDiscriminant  = Disc_Loose1_FSE[ipbin][etbin][etabin];
    cutDiscriminant += ip*Disc_Loose1_FSE_b[ipbin][etbin][etabin];
    std::cout << "Error! Loose is currently deprecated!" << std::endl;
    return -999.;
  }
  if ((operating_point == LikeEnum::Loose1_FixedBkgRejection) || (operating_point == LikeEnum::Very_Loose)) {
    cutDiscriminant  = Disc_Multilepton_FBR[ipbin][etbin][etabin];
    cutDiscriminant += ip*Disc_Multilepton_FBR_b[ipbin][etbin][etabin];
  }
  if ((operating_point == LikeEnum::Loose1_FixedSignalEfficiency) 
      || (operating_point == LikeEnum::Loose)
      || (operating_point == LikeEnum::Loose_BL_Pix)) {
    cutDiscriminant  = Disc_Multilepton_FSE[ipbin][etbin][etabin];
    cutDiscriminant += ip*Disc_Multilepton_FSE_b[ipbin][etbin][etabin];
  }
  
  double response = EvaluateLikelihood(eta,eT,f3,rHad,rHad1,Reta,w2,f1,wstot,DEmaxs1,
				       deltaEta,d0,TRratio,eOverP,deltaPhi,d0sigma,fside,
				       ptcone20,rphi,ws3,
				       deltaPoverP,deltaphires,
				       0,bitmask);
  
  if (fDebug) std::cout << "Likelihood macro: Discriminant:" << response << std::endl;
  
  if (response < cutDiscriminant) {
    if (fDebug) std::cout << "Likelihood macro: Disciminant Cut Failed." << std::endl;
    return false;
  }
  return true;
}

double ElectronLikelihoodTool::EvaluateLikelihood(double eta, double eT,double f3, double rHad, double rHad1,
						       double Reta, double w2, double f1, double wstot, double DEmaxs1,
						       double deltaEta, double d0, double TRratio, double eOverP,
						       double deltaPhi, double d0sigma, double fside,
						       double ptcone20, double rphi, double ws3,
						       double deltaPoverP ,double deltaphires,
						       double ip, unsigned int mask){

  wstot = -9999.;
  eOverP = -9999.;
  deltaPhi = -9999.;
  fside = -9999.;
  
  unsigned int etabin = getLikelihoodEtaBin(eta);
  double rhad_corr;
  if(etabin == 3 || etabin == 4) rhad_corr = rHad;
  else rhad_corr = rHad1;
  double d0significance = d0sigma == 0 ? 0. : fabs(d0)/d0sigma;

//   double arr[] = {d0significance,DEmaxs1,deltaEta,deltaPhi
// 		  ,eOverP,f1,f3,fside
// 		  ,ptcone20/eT,Reta,rhad_corr,rphi
// 		  ,d0,TRratio,w2,ws3,wstot
// 		  ,deltaPoverP,deltaphires};
  double arr[] = {d0significance,DEmaxs1,deltaEta
		  ,f1,f3
		  ,ptcone20/eT,Reta,rhad_corr,rphi
		  ,d0,TRratio,w2,ws3
		  ,deltaPoverP,deltaphires};
  std::vector<double> vec (arr, arr + sizeof(arr) / sizeof(double) );

  return EvaluateLikelihood(vec,eT,eta,ip,mask);
}
  

double ElectronLikelihoodTool::EvaluateLikelihood(std::vector<float> varVector,double et,double eta,double ip,unsigned int mask)
{
  std::vector<double> vec;
  for(unsigned int var = 0; var < fnVariables; var++){
    vec.push_back(varVector[var]);
  }
  return EvaluateLikelihood(vec,et,eta,ip,mask);  
}
double ElectronLikelihoodTool::EvaluateLikelihood(std::vector<double> varVector,double et,double eta,double ip,unsigned int mask)
{

  unsigned int etbin = getLikelihoodEtBin(et);
  unsigned int etabin = getLikelihoodEtaBin(eta);
  unsigned int ipbin  = getIpBin(ip);

  if (fDebug) std::cout << "et: " << et << " eta: " << eta 
			<< " etbin: " << etbin << " etabin: " << etabin << std::endl;

  if (etbin >= fnFineEtBins) {
    std::cout << "skipping etbin " << etbin << ", et " << et << std::endl;
    return -999.;
  }
  if (etabin >= fnEtaBins) {
    std::cout << "skipping etabin " << etabin << ", eta " << eta << std::endl;
    return -999.;
  }
//   if (etabin == 5) {
//     std::cout << "skipping etabin " << etabin << std::endl;
//     return -999.;
//   }

  if (varVector.size() != fnVariables) 
    std::cout << "Error! Variable vector size mismatch! Check your vector!" << std::endl;
  if (!mask) mask = fVariableMask;
  
  double SigmaS = 1.;
  double SigmaB = 1.;
  for(unsigned int var = 0; var < fnVariables; var++){

    std::string varstr = fVariables[var];

    // Skip variables that are masked off (not used) in the likelihood
    if (!(mask & (0x1 << var))){
      continue;
    }
    // Don't use TRT for outer eta bins (2.01,2.37)
    if (((etabin == 8) || (etabin == 9)) && (varstr.find("TRT") != std::string::npos)){
      continue;
    }
    // Don't use f3 for outer eta bin (2.37)
    if ((etabin == 9) && (varstr.find("el_f3") != std::string::npos)){
      continue;
    }
    for (unsigned int s_or_b=0; s_or_b<2;s_or_b++) {

      std::string sig_bkg = (s_or_b==0) ? "sig" : "bkg" ;

      int nbins = fPDFbins[s_or_b][ipbin][etbin][etabin][var]->GetNbinsX();
      int bin = fPDFbins[s_or_b][ipbin][etbin][etabin][var]->FindBin(varVector[var]);
      if (bin <  1)    bin = 1;
      if (bin > nbins) bin = nbins;

      double integral = double(fPDFIntegrals[s_or_b][ipbin][etbin][etabin][var]);
      if (integral == 0) {
	std::cout << "Error! PDF integral == 0!" << std::endl;
	return -1.35;
      }

      double prob = double(fPDFbins[s_or_b][ipbin][etbin][etabin][var]->GetBinContent(bin)) / integral;

      if   (s_or_b == 0) SigmaS *= prob;
      else if (s_or_b == 1) SigmaB *= prob;
    }
  }
  return TransformLikelihoodOutput( SigmaS, SigmaB );
}

// --------------------------------------------
double ElectronLikelihoodTool::TransformLikelihoodOutput(double ps,double pb) {
  // returns transformed or non-transformed output
  // (Taken mostly from TMVA likelihood code)
  double fEpsilon = 1e-99;
 // If both signal and bkg are 0, we want it to fail.
  if (ps < fEpsilon) ps = 0;
  if (pb < fEpsilon) pb = fEpsilon;
  double r = ps/double(ps + pb);
  if (r >= 1.0) r = 1. - 1.e-15;
  if (true) {
    
    if (r <= 0.0) r = fEpsilon;
    else if (r >= 1. - 1.e-15) r = 1. - 1.e-15;
    
    double tau = 15.0;
    r = - log(1.0/r - 1.0)/double(tau);
    
  }
  if (fDebug) std::cout << "r is " << r << std::endl;
  return r;
}

// These are the variables availalble in the likelihood.
const char* ElectronLikelihoodTool::fVariables[15] = {"el_d0Sig"
							   ,"el_deltaEmax2"
							   ,"el_deltaeta1"
							   //,"el_deltaphi2"
							   //,"el_EoverP"
							   ,"el_f1"
							   ,"el_f3"
							   //,"el_fside"
							   ,"el_ptcone20pt"
							   ,"el_reta"
							   ,"el_rhad"
							   ,"el_rphi"
							   ,"el_trackd0"
						           ,"el_TRTHighTHitsRatio" // Use HTOutliersRatio, though!
							   ,"el_weta2"
							   ,"el_ws3"
							   //,"el_wstot"
							   ,"el_DeltaPoverP"
							   ,"el_deltaphiRescaled"};

// These are the discriminant values to compare against for various operating points.
// Binning : [mu or nvtx][Et][eta]
// Note that the second bin is an exact copy of the first, since they are one bin in the pdf histograms.

const double ElectronLikelihoodTool::Disc_Tight_FBR[1][9][10] = {{{  0.141,  0.141,  0.243,  0.273,  0.212,  0.134,  0.219,  0.230,  0.239,  0.154},
								       {  0.470,  0.470,  0.386,  0.362,  0.357,  0.177,  0.402,  0.481,  0.435,  0.288},
								       {  0.555,  0.555,  0.591,  0.532,  0.477,  0.248,  0.494,  0.488,  0.523,  0.396},
								       {  0.538,  0.538,  0.534,  0.524,  0.495,  0.256,  0.476,  0.507,  0.442,  0.342},
								       {  0.539,  0.539,  0.538,  0.614,  0.496,  0.236,  0.475,  0.591,  0.444,  0.394},
								       {  0.567,  0.567,  0.492,  0.470,  0.555,  0.249,  0.481,  0.569,  0.462,  0.307},
								       {  0.530,  0.530,  0.632,  0.520,  0.602,  0.197,  0.667,  0.703,  0.481,  0.268},
								       {  0.720,  0.720,  0.513,  0.528,  0.507,  0.417,  0.413,  0.712,  0.480,  0.243},
								       {  0.687,  0.687,  0.688,  0.541,  0.651,  0.226,  0.471,  0.526,  0.520,  0.478}}};

const double ElectronLikelihoodTool::Disc_Tight_FSE[1][9][10] = {{{  0.362,  0.362,  0.300,  0.320,  0.239,  0.140,  0.243,  0.277,  0.277,  0.191}, // was .153 in crack
								       {  0.540,  0.540,  0.479,  0.481,  0.422,  0.243,  0.443,  0.537,  0.460,  0.301},
								       {  0.585,  0.585,  0.548,  0.555,  0.551,  0.325,  0.571,  0.599,  0.543,  0.406},
								       {  0.596,  0.596,  0.577,  0.537,  0.541,  0.320,  0.543,  0.601,  0.534,  0.385},
								       {  0.621,  0.621,  0.596,  0.576,  0.574,  0.320,  0.562,  0.637,  0.559,  0.441},
								       {  0.672,  0.672,  0.613,  0.604,  0.600,  0.338,  0.582,  0.648,  0.601,  0.457},
								       {  0.694,  0.694,  0.664,  0.658,  0.655,  0.346,  0.629,  0.679,  0.626,  0.496},
								       {  0.753,  0.753,  0.699,  0.669,  0.671,  0.326,  0.588,  0.665,  0.631,  0.519},
								       {  0.797,  0.797,  0.760,  0.733,  0.726,  0.342,  0.639,  0.740,  0.654,  0.573}}};

const double ElectronLikelihoodTool::Disc_Medium_FBR[1][9][10] = {{{ -0.045, -0.045,  0.068,  0.058,  0.116,  0.092,  0.128,  0.132,  0.125,  0.085},
									{  0.259,  0.259,  0.272,  0.215,  0.251,  0.088,  0.253,  0.230,  0.222,  0.120},
									{  0.325,  0.325,  0.375,  0.261,  0.324,  0.097,  0.286,  0.283,  0.212,  0.057},
									{  0.350,  0.350,  0.377,  0.320,  0.300,  0.092,  0.270,  0.304,  0.278,  0.085},
									{  0.344,  0.344,  0.322,  0.350,  0.272,  0.110,  0.296,  0.330,  0.260,  0.101},
									{  0.258,  0.258,  0.306,  0.234,  0.229,  0.020,  0.222,  0.245,  0.272,  0.026},
									{  0.282,  0.282,  0.271,  0.234,  0.282,  0.036,  0.290,  0.256,  0.238,  0.084},
									{  0.234,  0.234,  0.222,  0.224,  0.212, -0.012,  0.172,  0.234,  0.312,  0.074},
									{  0.244,  0.244,  0.305,  0.204,  0.240,  0.008,  0.140,  0.187,  0.244,  0.002}}};

const double ElectronLikelihoodTool::Disc_Medium_FSE[1][9][10] = {{{  0.311,  0.311,  0.273,  0.263,  0.164,  0.130,  0.179,  0.199,  0.181,  0.131},
									{  0.418,  0.418,  0.401,  0.364,  0.325,  0.201,  0.322,  0.384,  0.314,  0.200},
									{  0.439,  0.439,  0.457,  0.412,  0.418,  0.242,  0.392,  0.417,  0.348,  0.221},
									{  0.497,  0.497,  0.486,  0.454,  0.440,  0.259,  0.445,  0.444,  0.428,  0.257},
									{  0.519,  0.519,  0.501,  0.479,  0.462,  0.262,  0.463,  0.479,  0.446,  0.325},
									{  0.519,  0.519,  0.487,  0.482,  0.453,  0.262,  0.457,  0.475,  0.469,  0.342},
									{  0.544,  0.544,  0.538,  0.521,  0.487,  0.276,  0.482,  0.499,  0.494,  0.388},
									{  0.528,  0.528,  0.534,  0.508,  0.482,  0.219,  0.409,  0.473,  0.476,  0.401},
									{  0.589,  0.589,  0.608,  0.586,  0.562,  0.236,  0.454,  0.535,  0.520,  0.499}}};

const double ElectronLikelihoodTool::Disc_Loose1_FBR[1][9][10] = {{{ 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000},  //  7
									{ 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000},  // 10
									{ 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000},  // 15
									{ 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000},  // 20
									{ 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000},  // 25
									{ 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000},  // 30
									{ 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000},  // 35
									{ 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000},  // 40
									{ 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000}}};// 45

const double ElectronLikelihoodTool::Disc_Loose1_FSE[1][9][10] = {{{ 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000},  //  7
									{ 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000},  // 10
									{ 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000},  // 15
									{ 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000},  // 20
									{ 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000},  // 25
									{ 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000},  // 30
									{ 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000},  // 35
									{ 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000},  // 40
									{ 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000}}};// 45

const double ElectronLikelihoodTool::Disc_Multilepton_FBR[1][9][10] = {{{ -0.016, -0.016,  0.068, -0.022, -0.028,  0.008,  0.020,  0.062,  0.110,  0.026},
									     {  0.140,  0.140,  0.176,  0.104,  0.038,  0.014,  0.074,  0.146,  0.206,  0.062},
									     {  0.218,  0.218,  0.290,  0.200,  0.128,  0.014,  0.128,  0.146,  0.194,  0.032},
									     {  0.200,  0.200,  0.206,  0.194,  0.074, -0.028,  0.122,  0.176,  0.194,  0.056},
									     {  0.206,  0.206,  0.236,  0.212,  0.110,  0.002,  0.152,  0.194,  0.188,  0.068},
									     {  0.116,  0.116,  0.188,  0.092,  0.056, -0.088,  0.074,  0.134,  0.152,  0.032},
									     {  0.122,  0.122,  0.176,  0.134,  0.038, -0.082,  0.074,  0.134,  0.200,  0.056},
									     {  0.152,  0.152,  0.200,  0.170,  0.086, -0.154, -0.016,  0.170,  0.242,  0.128},
									     {  0.134,  0.134,  0.260,  0.140,  0.086, -0.148,  0.092,  0.152,  0.224,  0.056}}};

const double ElectronLikelihoodTool::Disc_Multilepton_FSE[1][9][10] = {{{  0.128,  0.128,  0.188,  0.062,  0.056,  0.065,  0.050,  0.110,  0.128,  0.056}, // was .074 in crack
									     {  0.260,  0.260,  0.278,  0.194,  0.152,  0.068,  0.152,  0.218,  0.212,  0.098},
									     {  0.326,  0.326,  0.344,  0.278,  0.266,  0.110,  0.224,  0.260,  0.254,  0.116},
									     {  0.302,  0.302,  0.320,  0.272,  0.224,  0.104,  0.242,  0.266,  0.260,  0.140},
									     {  0.338,  0.338,  0.368,  0.308,  0.272,  0.116,  0.278,  0.314,  0.302,  0.188},
									     {  0.350,  0.350,  0.368,  0.326,  0.296,  0.074,  0.278,  0.338,  0.332,  0.152},
									     {  0.392,  0.392,  0.428,  0.386,  0.356,  0.098,  0.308,  0.368,  0.380,  0.170},
									     {  0.386,  0.386,  0.416,  0.356,  0.356,  0.032,  0.284,  0.344,  0.380,  0.242},
									     {  0.446,  0.446,  0.494,  0.440,  0.440,  0.080,  0.344,  0.398,  0.428,  0.284}}};
//
// Vertex-dependent term d = a + bx where x is number of vertices
//
const double ElectronLikelihoodTool::Disc_Tight_FBR_b[1][9][10] = {{{ -0.00608, -0.00608, -0.00416, -0.00608,  0.00000,  0.00000, -0.00448, -0.00304, -0.00832, -0.00336},
									 { -0.00416, -0.00416,  0.00000, -0.00272,  0.00000, -0.00016, -0.00128, -0.00624, -0.00464, -0.00144},
									 { -0.00208, -0.00208, -0.00016, -0.00144, -0.00432,  0.00000, -0.00304, -0.00048, -0.00384, -0.00112},
									 { -0.00192, -0.00192, -0.00288, -0.00112, -0.00192, -0.00144, -0.00096, -0.00320, -0.00160,  0.00000},
									 { -0.00096, -0.00096, -0.00144, -0.00096, -0.00160,  0.00000, -0.00064, -0.00240, -0.00112, -0.00224},
									 { -0.00240, -0.00240, -0.00032, -0.00208, -0.00128, -0.00096, -0.00144, -0.00208, -0.00240, -0.00208},
									 { -0.00112, -0.00112, -0.00096, -0.00208, -0.00208, -0.00048, -0.00128, -0.00144, -0.00208,  0.00000},
									 { -0.00160, -0.00160, -0.00208, -0.00128, -0.00208, -0.00096, -0.00128, -0.00208, -0.00272, -0.00208},
									 { -0.00176, -0.00176, -0.00192, -0.00176, -0.00240, -0.00096, -0.00048, -0.00288, -0.00160, -0.00032}}};

const double ElectronLikelihoodTool::Disc_Tight_FSE_b[1][9][10] = {{{  0.00000,  0.00000, -0.00198, -0.00220,  0.00000, -0.00044, -0.00440, -0.00440, -0.01012, -0.00462},
									 { -0.00550, -0.00550, -0.00110, -0.00330,  0.00000, -0.00044, -0.00110, -0.00594, -0.00506, -0.00176},
									 { -0.00374, -0.00374,  0.00000, -0.00198, -0.00220, -0.00088, -0.00286, -0.00088, -0.00440, -0.00066},
									 { -0.00220, -0.00220, -0.00330, -0.00154, -0.00286, -0.00154, -0.00110, -0.00286, -0.00242,  0.00000},
									 { -0.00110, -0.00110, -0.00154, -0.00154, -0.00242,  0.00000, -0.00066, -0.00264, -0.00220, -0.00198},
									 { -0.00308, -0.00308, -0.00132, -0.00198, -0.00176, -0.00132, -0.00154, -0.00242, -0.00330, -0.00132},
									 { -0.00176, -0.00176, -0.00154, -0.00264, -0.00308, -0.00088, -0.00220, -0.00198, -0.00242, -0.00066},
									 { -0.00220, -0.00220, -0.00308, -0.00220, -0.00286, -0.00154, -0.00176, -0.00286, -0.00330, -0.00176},
									 { -0.00198, -0.00198, -0.00264, -0.00198, -0.00264, -0.00110, -0.00110, -0.00352, -0.00176, -0.00044}}};

const double ElectronLikelihoodTool::Disc_Medium_FBR_b[1][9][10] = {{{ 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000},  //  7
									  { 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000},  // 10
									  { 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000},  // 15
									  { 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000},  // 20
									  { 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000},  // 25
									  { 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000},  // 30
									  { 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000},  // 35
									  { 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000},  // 40
									  { 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000}}};// 45

const double ElectronLikelihoodTool::Disc_Medium_FSE_b[1][9][10] = {{{  0.00000,  0.00000, -0.00056, -0.00088,  0.00000,  0.00000, -0.00216, -0.00200, -0.00344, -0.00144},
									  { -0.00200, -0.00200, -0.00016, -0.00104,  0.00000, -0.00024, -0.00128, -0.00424, -0.00376, -0.00232},
									  { -0.00208, -0.00208,  0.00000, -0.00104, -0.00176, -0.00016, -0.00192, -0.00104, -0.00240,  0.00000},
									  { -0.00096, -0.00096, -0.00152, -0.00048, -0.00072, -0.00072, -0.00040, -0.00136, -0.00088, -0.00016},
									  { -0.00056, -0.00056, -0.00080, -0.00072, -0.00104,  0.00000, -0.00040, -0.00096, -0.00072, -0.00080},
									  { -0.00128, -0.00128, -0.00024, -0.00104, -0.00056, -0.00032, -0.00040, -0.00080, -0.00120, -0.00088},
									  { -0.00064, -0.00064, -0.00048, -0.00096, -0.00120, -0.00040, -0.00064, -0.00112, -0.00088, -0.00072},
									  { -0.00088, -0.00088, -0.00104, -0.00064, -0.00104, -0.00056, -0.00040, -0.00112, -0.00104, -0.00024},
									  { -0.00080, -0.00080, -0.00104, -0.00088, -0.00104, -0.00064,  0.00000, -0.00112, -0.00088, -0.00016}}};

const double ElectronLikelihoodTool::Disc_Loose1_FBR_b[1][9][10] = {{{ 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000},  //  7
									  { 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000},  // 10
									  { 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000},  // 15
									  { 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000},  // 20
									  { 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000},  // 25
									  { 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000},  // 30
									  { 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000},  // 35
									  { 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000},  // 40
									  { 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000}}};// 45

const double ElectronLikelihoodTool::Disc_Loose1_FSE_b[1][9][10] = {{{ 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000},  //  7
									  { 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000},  // 10
									  { 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000},  // 15
									  { 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000},  // 20
									  { 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000},  // 25
									  { 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000},  // 30
									  { 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000},  // 35
									  { 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000},  // 40
									  { 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000}}};// 45

const double ElectronLikelihoodTool::Disc_Multilepton_FBR_b[1][9][10] = {{{ 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000},  //  7
									       { 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000},  // 10
									       { 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000},  // 15
									       { 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000},  // 20
									       { 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000},  // 25
									       { 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000},  // 30
									       { 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000},  // 35
									       { 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000},  // 40
									       { 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000}}};// 45

const double ElectronLikelihoodTool::Disc_Multilepton_FSE_b[1][9][10] = {{{ 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000},  //  7
									       { 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000},  // 10
									       { 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000},  // 15
									       { 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000},  // 20
									       { 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000},  // 25
									       { 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000},  // 30
									       { 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000},  // 35
									       { 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000},  // 40
									       { 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000}}};// 45

#include "egammaAnalysisUtils/ElectronLikelihoodTool.h"
#include "egammaAnalysisUtils/IsEMPlusPlusDefs.h"
#include <iostream>
#include <iomanip>
#include <cmath>

//---------------------------------------------------------------------------------------
// Gets the Et bin [0-10] given the et (MeV)
unsigned int ElectronLikelihoodTool::getIpBin(double ip){
  const unsigned int nIpBins = 1;
  const double ipBins[nIpBins] = {500.};
  
  for(unsigned int ipBin = 0; ipBin < nIpBins; ++ipBin){
    if(ip < ipBins[ipBin])
      return ipBin;
  }
  
  return 0;
}

//---------------------------------------------------------------------------------------
// Gets the bin name 
void ElectronLikelihoodTool::getBinName(char* buffer, int etbin,int etabin, int ipbin, std::string iptype){
  double eta_bounds[10] = {0.0,0.6,0.8,1.15,1.37,1.52,1.81,2.01,2.37,2.47};
  int et_bounds[10] = {10,15,20,30,40,50,60,70,80,500};
  int ip_bounds[2] = {0,500};
  if (!iptype.empty())
    sprintf(buffer, "%s%02det%02deta%0.2f", iptype.c_str(), ip_bounds[ipbin], et_bounds[etbin], eta_bounds[etabin]);
  else 
    sprintf(buffer, "et%02deta%0.2f", et_bounds[etbin], eta_bounds[etabin]);
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
ElectronLikelihoodTool::ElectronLikelihoodTool(std::string wfile,std::string vars,std::string ipbinning):
  fPDFfilename(wfile)  
  ,fVariableMask(0x0)
  ,fIpBinning(ipbinning)
{
  std::cout << "Pdf file: " << wfile << std::endl;
  fPDFfile = new TFile(wfile.c_str(),"READ");
  std::cout << "file booked." << std::endl;

  fVariableMask = GetLikelihoodBitmask(vars,true);

//   std::cout << "Other Options : " << std::endl;
//   std::cout << "Tight : " << std::endl;
//   LikelihoodTightBitmask(true);
//   std::cout << "Medium : " << std::endl;
//   LikelihoodMediumBitmask(true);
//   std::cout << "Loose : " << std::endl;
//   LikelihoodLooseBitmask(true);

  for(unsigned int s_or_b = 0; s_or_b < 2; s_or_b++){
    for (unsigned int ip = 0; ip < fnIpBins; ip++){ ////HERE!!!!!
      for(unsigned int et = 0; et < fnEtBins; et++){
	for(unsigned int eta = 0; eta < fnEtaBins; eta++){

	  std::string sig_bkg = (s_or_b==0) ? "sig" : "bkg" ;	  
	  // Because eta bins in the root file don't match up exactly with cut menu
	  // definitions, the second eta bin is an exact copy of the first,
	  // and all subsequent eta bins are pushed back by one.
	  unsigned int eta_tmp = (eta > 0) ? eta-1 : eta ;
	  char binname[200];
	  getBinName(binname,et,eta_tmp,ip,fIpBinning);

	  if (std::string(binname).find("1.37") != std::string::npos) 
	    continue;

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
	      int nbins = fPDFbins[s_or_b][ip][et][eta][var]->GetNbinsX();
	      fPDFIntegrals[s_or_b][ip][et][eta][var] = fPDFbins[s_or_b][ip][et][eta][var]->Integral(1,nbins);
	    }
	    else {
	      std::cout << "Object" << pdf << "does not exist." << std::endl;
	    }
	  }
	}
      }  
    }
  }
  std::cout << "Initialization complete" << std::endl;
}

ElectronLikelihoodTool::~ElectronLikelihoodTool(){
  //fPDFfile->Close();
}

bool ElectronLikelihoodTool::passLikelihood(std::string operating_point,
				    double eta, double eT,double f3, double rHad, double rHad1,
				    double Reta, double w2, double f1, double wstot, double DEmaxs1,
				    double deltaEta, double d0, double TRratio, double eOverP,
				    double deltaPhi, double d0sig, double fside,
				    double ptcone20, double rphi, double ws3,
				    //
				    int nTRT, int nTRTOutliers,
				    int nSi,int nSiOutliers, int nPix, int nPixOutliers,
				    int nBlayer, int nBlayerOutliers, bool expectBlayer,
				    int convBit, bool debug){
  
  std::string operating_pt_options[6] = {"Tight_FixedBkgRejection"
					 ,"Tight_FixedSignalEfficency"
					 ,"Medium_FixedBkgRejection"
					 ,"Medium_FixedSignalEfficiency"
					 ,"Loose1_FixedBkgRejection"
					 ,"Loose1_FixedSignalEfficiency"};

  if (debug) std::cout << "Likelihood macro: Using operating point " << operating_point << std::endl;
  // Check to see that a suitable operating point was specified.
  bool exists = false;
  for(unsigned int i = 0; i < sizeof(operating_pt_options)/sizeof(std::string); i++){
    if (operating_point.find(operating_pt_options[i]) != std::string::npos) exists = true;
  }
  if (!exists){
    std::cout << "Error! Must specify a correct operating point! Options are:" << std::endl;
    for(unsigned int i = 0; i < sizeof(operating_pt_options)/sizeof(std::string); i++){
      std::cout << "   " << operating_pt_options[i] << std::endl;
    }
  }

  unsigned int etbin = getEtBin(eT)-2;
  unsigned int etabin = getEtaBin(eta);
  unsigned int ipbin  = 0;
  unsigned int bitmask = 0;

  // If the electron Et is greater / less than the range of the pdfs,
  // 10 < et_range < 50 (to be extended)
  // we cannot evaluate the likelihood. In this case, we'll return the
  // value from the cut menus.
  bool return_cut_response = false;
  if (etbin  >= fnEtBins ) {
    if (debug) std::cout << "Cannot evaluate likelihood for Et " << eT;
    if (debug) std::cout << "Returning cut menu response instead." << std::endl;
    return_cut_response = true;
    etbin = fnEtBins-1; // Avoid coverity warning.
  }
  if (etabin == 5) {
    if (debug) std::cout << "Cannot evaluate likelihood for eta " << eta;
    if (debug) std::cout << "Returning cut menu response instead." << std::endl;
    return_cut_response = true;
  }

  // Tight cut requirements
  if (operating_point.find("Tight") != std::string::npos) {
    if (return_cut_response) 
      return isTightPlusPlus(eta,  eT,  f3,
			     rHad,  rHad1,  Reta,  w2, 
			     f1,  wstot,  DEmaxs1,  deltaEta,  d0, 
			     TRratio, nTRT, nTRTOutliers,
			     nSi, nSiOutliers, nPix, nPixOutliers, 
			     nBlayer, nBlayerOutliers, expectBlayer,
			     eOverP, deltaPhi, convBit);
    
    if (expectBlayer && !passNBlayer_tight(nBlayer+nBlayerOutliers,etabin)){
      if (debug) std::cout << "Likelihood macro: Blayer Failed." << std::endl;
      return false;
    }
    if (nPix+nPixOutliers < 1){
      if (debug) std::cout << "Likelihood macro: Pixels Failed." << std::endl;
      return false;
    }
    if (nSi + nSiOutliers < 7){
      if (debug) std::cout << "Likelihood macro: Silicon Failed." << std::endl;
      return false;
    }
    if (convBit){
      if (debug) std::cout << "Likelihood macro: Conversion Bit Failed." << std::endl;
      return false;
    }
    bitmask = LikelihoodTightBitmask();
  }

  // Medium cut requirements
  if (operating_point.find("Medium") != std::string::npos) {
    if (return_cut_response) 
      return isMediumPlusPlus(eta, eT, f3,
			      rHad, rHad1, Reta, w2, 
			      f1, wstot, DEmaxs1, deltaEta, d0,
			      TRratio, nTRT, nTRTOutliers,
			      nSi, nSiOutliers, nPix, nPixOutliers, 
			      nBlayer, nBlayerOutliers, expectBlayer);
    
    if (expectBlayer) {
      const double cutNBlayer[10] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 0};
      if(nBlayer + nBlayerOutliers < cutNBlayer[etabin]) {
	if (debug) std::cout << "Likelihood macro: Blayer Failed." << std::endl;
	return false;
      }
    }
    if (nPix+nPixOutliers < 1){
      if (debug) std::cout << "Likelihood macro: Pixels Failed." << std::endl;
      return false;
    }
    if (nSi + nSiOutliers < 7){
      if (debug) std::cout << "Likelihood macro: Silicon Failed." << std::endl;
      return false;
    }
    bitmask = LikelihoodMediumBitmask();
  }

  // Loose cut requirements
  if (operating_point.find("Loose") != std::string::npos) {
    if (return_cut_response) 
      return isLoosePlusPlus1(eta, eT,
			      rHad, rHad1, Reta, w2,
			      f1, wstot, DEmaxs1, deltaEta, nSi,
			      nSiOutliers, nPix, nPixOutliers);

    if (nSi + nSiOutliers < 7){
      if (debug) std::cout << "Likelihood macro: Silicon Failed." << std::endl;
      return false;
    }
    bitmask = LikelihoodLooseBitmask();
  }
  
  double cutDiscriminant = -999.;
  
  if (operating_point.find("Tight_FixedBkgRejection") != std::string::npos) {
    cutDiscriminant  = Disc_Tight_FixedBkgRejection[ipbin][etbin][etabin];
  }
  if (operating_point.find("Tight_FixedSignalEfficency") != std::string::npos) {
    cutDiscriminant  = Disc_Tight_FixedSignalEfficency[ipbin][etbin][etabin];
  }
  if (operating_point.find("Medium_FixedBkgRejection") != std::string::npos) {
    cutDiscriminant  = Disc_Medium_FixedBkgRejection[ipbin][etbin][etabin];
  }
  if (operating_point.find("Medium_FixedSignalEfficiency") != std::string::npos) {
    cutDiscriminant  = Disc_Medium_FixedSignalEfficiency[ipbin][etbin][etabin];
  }
  if (operating_point.find("Loose1_FixedBkgRejection") != std::string::npos) {
    cutDiscriminant  = Disc_Loose1_FixedBkgRejection[ipbin][etbin][etabin];
  }   
  if (operating_point.find("Loose1_FixedSignalEfficiency") != std::string::npos) {
    cutDiscriminant  = Disc_Loose1_FixedSignalEfficiency[ipbin][etbin][etabin];
  }
  
  double response = EvaluateLikelihood(eta,eT,f3,rHad,rHad1,Reta,w2,f1,wstot,DEmaxs1,
						       deltaEta,d0,TRratio,eOverP,deltaPhi,d0sig,fside,
						       ptcone20,rphi,ws3,bitmask);
  
  if (debug) std::cout << "Likelihood macro: Discriminant:" << response << std::endl;
  
  if (response < cutDiscriminant) {
    if (debug) std::cout << "Likelihood macro: Disciminant Cut Failed." << std::endl;
    return false;
  }
  return true;
}

double ElectronLikelihoodTool::EvaluateLikelihood(double eta, double eT,double f3, double rHad, double rHad1,
					  double Reta, double w2, double f1, double wstot, double DEmaxs1,
					  double deltaEta, double d0, double TRratio, double eOverP,
					  double deltaPhi, double d0sig, double fside,
					  double ptcone20, double rphi, double ws3,
					  unsigned int mask){

  unsigned int etabin = getEtaBin(eta);
  double rhad_corr;
  if(etabin == 3 || etabin == 4) rhad_corr = rHad;
  else rhad_corr = rHad1;

  double arr[] = {d0sig,DEmaxs1,deltaEta,deltaPhi
		  ,eOverP,f1,f3,fside
		  ,ptcone20/eT,Reta,rhad_corr,rphi
		  ,d0,TRratio,w2,ws3,wstot};
  std::vector<double> vec (arr, arr + sizeof(arr) / sizeof(double) );

  return EvaluateLikelihood(vec,eT,eta,0,mask);
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

  unsigned int etbin = getEtBin(et)-2;
  unsigned int etabin = getEtaBin(eta);
  unsigned int ipbin  = getIpBin(ip);
  if (etbin  >= fnEtBins ) {
    std::cout << "skipping etbin " << etbin << std::endl;
    return -999.;
  }
  if (etabin >= fnEtaBins) {
    std::cout << "skipping etabin " << etabin << std::endl;
    return -999.;
  }
  if (etabin == 5) {
    std::cout << "skipping etabin " << etabin << std::endl;
    return -999.;
  }
    
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
  return r;
}

// These are the variables availalble in the likelihood.
const char* ElectronLikelihoodTool::fVariables[17] = {"el_d0Sig"
					      ,"el_deltaEmax2"
					      ,"el_deltaeta1"
					      ,"el_deltaphi2"
					      ,"el_EoverP"
					      ,"el_f1"
					      ,"el_f3"
					      ,"el_fside"
					      ,"el_ptcone20pt"
					      ,"el_reta"
					      ,"el_rhad"
					      ,"el_rphi"
					      ,"el_trackd0"
					      ,"el_TRTHighTHitsRatio"
					      ,"el_weta2"
					      ,"el_ws3"
					      ,"el_wstot"};


// These are the discriminant values to compare against for various operating points.
// Binning : [mu or nvtx][Et][eta]
// Note that the second bin is an exact copy of the first, since they are one bin in the pdf histograms.

const double ElectronLikelihoodTool::Disc_Tight_FixedBkgRejection[1][5][10] = {{{ 0.198, 0.198, 0.180, 0.175, 0.183, 0.000, 0.179, 0.200, 0.158, 0.145}, //#10-15
										{ 0.216, 0.216, 0.208, 0.191, 0.195, 0.000, 0.172, 0.219, 0.159, 0.164}, //#15-20
										{ 0.195, 0.195, 0.175, 0.154, 0.169, 0.000, 0.153, 0.197, 0.153, 0.180}, //#20-30
										{ 0.183, 0.183, 0.155, 0.121, 0.135, 0.000, 0.162, 0.144, 0.196, 0.124}, //#30-40
										{ 0.193, 0.193, 0.084, 0.114, 0.123, 0.000, 0.230, 0.129, 0.191, 0.227}}}; //#40-500

const double ElectronLikelihoodTool::Disc_Tight_FixedSignalEfficency[1][5][10] = {{{ 0.257, 0.257, 0.265, 0.235, 0.236, 0.000, 0.213, 0.241, 0.179, 0.158}, //#10-15
										   { 0.288, 0.288, 0.287, 0.283, 0.292, 0.000, 0.259, 0.289, 0.201, 0.197}, //#15-20
										   { 0.340, 0.340, 0.316, 0.318, 0.308, 0.000, 0.285, 0.311, 0.272, 0.246}, //#20-30
										   { 0.387, 0.387, 0.357, 0.348, 0.347, 0.000, 0.322, 0.356, 0.337, 0.281}, //#30-40
										   { 0.481, 0.481, 0.421, 0.411, 0.382, 0.000, 0.310, 0.388, 0.367, 0.330}}}; //#40-500

const double ElectronLikelihoodTool::Disc_Medium_FixedBkgRejection[1][5][10] = {{{ 0.200, 0.200, 0.184, 0.178, 0.168, 0.000, 0.159, 0.171, 0.137, 0.090}, //#10-15
										 { 0.251, 0.251, 0.204, 0.204, 0.181, 0.000, 0.154, 0.131, 0.120, 0.039}, //#15-20
										 { 0.232, 0.232, 0.194, 0.169, 0.169, 0.000, 0.123, 0.132, 0.136, 0.072}, //#20-30
										 { 0.210, 0.210, 0.169, 0.124, 0.130, 0.000, 0.111, 0.085, 0.168, 0.032}, //#30-40
										 { 0.166, 0.166, 0.149, 0.095, 0.081, 0.000, 0.144, 0.111, 0.178, 0.061}}}; //#40-500

const double ElectronLikelihoodTool::Disc_Medium_FixedSignalEfficiency[1][5][10] = {{{ 0.207, 0.207, 0.232, 0.203, 0.194, 0.000, 0.181, 0.187, 0.140, 0.120}, //#10-15
										     { 0.221, 0.221, 0.222, 0.232, 0.219, 0.000, 0.201, 0.208, 0.139, 0.114}, //#15-20
										     { 0.261, 0.261, 0.247, 0.255, 0.232, 0.000, 0.214, 0.193, 0.206, 0.178}, //#20-30
										     { 0.270, 0.270, 0.262, 0.256, 0.229, 0.000, 0.214, 0.213, 0.238, 0.205}, //#30-40
										     { 0.304, 0.304, 0.289, 0.279, 0.234, 0.000, 0.164, 0.246, 0.254, 0.234}}}; //#40-500

const double ElectronLikelihoodTool::Disc_Loose1_FixedBkgRejection[1][5][10] = {{{ 0.003, 0.003,-0.006,-0.002,-0.019, 0.000, 0.012, 0.036, 0.033,-0.069}, //#10-15
										 {-0.013,-0.013,-0.013,-0.068,-0.102, 0.000,-0.060, 0.017,-0.008,-0.163}, //#15-20
									 {-0.076,-0.076,-0.085,-0.116,-0.133, 0.000,-0.054,-0.014,-0.068,-0.222}, //#20-30
									 {-0.088,-0.088,-0.089,-0.142,-0.154, 0.000,-0.036,-0.016,-0.031,-0.221}, //#30-40
									 {-0.083,-0.083,-0.121,-0.147,-0.179, 0.000,-0.042,-0.006,-0.005,-0.225}}}; //#40-500

const double ElectronLikelihoodTool::Disc_Loose1_FixedSignalEfficiency[1][5][10] = {{{ 0.107, 0.107, 0.113, 0.094, 0.073, 0.000, 0.062, 0.054, 0.010,-0.006}, //#10-15
									     { 0.084, 0.084, 0.108, 0.050, 0.082, 0.000, 0.016, 0.023, 0.012, 0.003}, //#15-20
									     { 0.048, 0.048, 0.089, 0.053, 0.050, 0.000, 0.034, 0.010,-0.004, 0.031}, //#20-30
									     { 0.074, 0.074, 0.104, 0.073, 0.052, 0.000, 0.045, 0.046, 0.072, 0.102}, //#30-40
									     { 0.118, 0.118, 0.099, 0.083, 0.041, 0.000, 0.011, 0.068, 0.116, 0.134}}}; //#40-500


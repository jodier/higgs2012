#include "egammaAnalysisUtils/ElectronEfficiencySFTool.h"

// #include "TObject.h"
#include <TMath.h>
#include <TROOT.h>
#include <TAxis.h>
#include <string>
#include <iostream>
#include <TRandom3.h>
//------------------------------------------------------
ElectronEfficiencySFTool::ElectronEfficiencySFTool(std::string fileName, std::string folderName){
  // basic init
  statErr = 0;
  sf = 0;
  corrSyst = 0;
  uncorrSyst = 0;
  uncorrToyMCSyst = 0;
  seed = 1;

    // Set default values for the SF and uncertainties
    defSF = 1.;
    defSFuncert = 0.;

    // Constructor
    TFile* weightfile = new TFile(fileName.c_str());

    if (weightfile == NULL ) {
        Error("ElectronEfficiencySFTool::ElectronEfficiencySFTool", (fileName + " not found").c_str() );
    } else {
    	Info("ElectronEfficiencySFTool::ElectronEfficiencySFTool", ("Open root file: "+ fileName).c_str() );
    }

    // Read number of systematics
    nSys = 1;
    sLevel[ElectronEfficiencySFTool::simple] = 0;
    sLevel[ElectronEfficiencySFTool::medium] = 0;
    sLevel[ElectronEfficiencySFTool::detailed] = 0;

    TH1D* eig = (TH1D*)weightfile->Get( (folderName+"/eig").c_str() );
    if (eig != NULL) {
        nSys = eig->GetNbinsX() - 1;
        double sign = 0;

        // Calculate details level
        for (int i = nSys + 1; i >= 2; i--) {
            sign += eig->GetBinContent(i);
            if (sign > 0.8 && sLevel[ElectronEfficiencySFTool::simple] == 0) {
                sLevel[ElectronEfficiencySFTool::simple] = i - 2;
            }
            if (sign > 0.95 && sLevel[ElectronEfficiencySFTool::medium] == 0) {
                sLevel[ElectronEfficiencySFTool::medium] = i - 2;
            }
        }
    }

    // Read stat uncertainties
    statErr = (TH2D*) weightfile->Get((folderName + "/stat").c_str());
    if (statErr == NULL) {
        Error("ElectronEfficiencySFTool::ElectronEfficiencySFTool", "Histogramme: stat Not found");
        return;
    }
    statErr->SetDirectory(gROOT);

    // Read scale factors
    sf = (TH2D*) weightfile->Get((folderName + "/sf").c_str());
    if (sf == NULL) {
        Error("ElectronEfficiencySFTool::ElectronEfficiencySFTool", "Histogramme: sf Not found");
        return;
    }
    sf->SetDirectory(0);

    // Read all systematics from root file
    corrSyst = new TH2D*[nSys];
    for (int i = 0; i < nSys; i++) {
        TString name = folderName + "/corr";
        name += i;
        corrSyst[i] = (TH2D*) weightfile->Get(name);
        if (corrSyst[i] == NULL) {
            Error("ElectronEfficiencySFTool::ElectronEfficiencySFTool", "Histogramme: corr_ %i Not found", i);
            return;
        }
        corrSyst[i]->SetDirectory(gROOT);
    }

    // Read uncorrelated uncertainties, if they are exist as a separate numbers
    uncorrSyst = (TH2D*) weightfile->Get((folderName + "/uncorr").c_str());
    if (uncorrSyst != NULL) {
        uncorrSyst->SetDirectory(gROOT);
    }

    weightfile->Close();
    delete weightfile;

}

//------------------------------------------------------
ElectronEfficiencySFTool::~ElectronEfficiencySFTool(){
  delete corrSyst;
  if (uncorrToyMCSyst)
    delete uncorrToyMCSyst;
}

//------------------------------------------------------
void ElectronEfficiencySFTool::SetSeed(int s){
  seed = s;
}

//------------------------------------------------------
void ElectronEfficiencySFTool::BookToyMCScaleFactors(int nToyMC, int detailLevel) {

    if (!statErr || !corrSyst || !sf)
        return;

    Info("ElectronEfficiencySFTool::BookToyMCScaleFactors", "Create tables for %3d ToyMC systematics ", nToyMC);

    //Create ToyMC SFs
    TRandom3 *m_Rndm = new TRandom3(seed);
    uncorrToyMCSyst = new TH2D*[nToyMC];

    int nBins = (statErr->GetNbinsX() + 2) * (statErr->GetNbinsY() + 2);

    for (int i = 0; i < nToyMC; i++) {
        uncorrToyMCSyst[i] = (TH2D*) corrSyst[0]->Clone();
    }

    // Loop over all bins
    for (int bin = 0; bin < nBins; bin++) {

        double val = statErr->GetBinContent(bin);

        // Add uncorrelated systematics
        if (uncorrSyst != NULL) {
            double valAdd = uncorrSyst->GetBinContent(bin);
            val = sqrt(val * val + valAdd * valAdd);
        }

        // Add smaller correlated systematics as uncorrelated
        for (int i = 0; i < sLevel[detailLevel]; i++) {
            if (corrSyst[i] != NULL) {
                double valAdd = corrSyst[i]->GetBinContent(bin);
                val = sqrt(val * val + valAdd * valAdd);
            }
        }

        // Loop over ToyMC tables
        for (int i = 0; i < nToyMC; i++) {
            uncorrToyMCSyst[i]->SetBinContent(bin, (val * m_Rndm->Gaus(0, 1)) + 1);
        }
    }

}

//------------------------------------------------------
void ElectronEfficiencySFTool::BookCombToyMCScaleFactors(int nToyMC, int detailLevel){

  if (!statErr || !corrSyst || !sf)
        return;

    Info("ElectronEfficiencySFTool::BookCombToyMCScaleFactors", "Create tables for %3d combined ToyMC systematics ", nToyMC);

    //Create ToyMC SFs
    TRandom3 *m_Rndm = new TRandom3(seed);
    uncorrToyMCSyst = new TH2D*[nToyMC];

    int nBins = (statErr->GetNbinsX() + 2) * (statErr->GetNbinsY() + 2);

    for (int i = 0; i < nToyMC; i++) {
        uncorrToyMCSyst[i] = (TH2D*) corrSyst[0]->Clone();
    }

    // Loop over ToyMC tables
    for (int i = 0; i < nToyMC; i++) {

        // Create random numbers for the corr. uncertainties
        double *rnd = new double[nSys];
        for (int s = 0; s < nSys; s++) {
            rnd[s] = m_Rndm->Gaus(0, 1);
        }

        // Loop over all bins
        for (int bin = 0; bin < nBins; bin++) {

            double val = statErr->GetBinContent(bin);

            // Add uncorrelated systematics
            if (uncorrSyst != NULL) {
                double valAdd = uncorrSyst->GetBinContent(bin);
                val = sqrt(val * val + valAdd * valAdd);
            }

            // Add smaller correlated systematics as uncorrelated
            for (int s = 0; s < sLevel[detailLevel]; s++) {
                if (corrSyst[s] != NULL) {
                    double valAdd = corrSyst[s]->GetBinContent(bin);
                    val = sqrt(val * val + valAdd * valAdd);
                }
            }

            val = val * m_Rndm->Gaus(0, 1);

            // Add larger correlated systematics
            for (int s = sLevel[detailLevel]; s < nSys; s++) {
                if (corrSyst[s] != NULL) {
                    val += corrSyst[s]->GetBinContent(bin) * rnd[s];
                }
            }

            uncorrToyMCSyst[i]->SetBinContent(bin, val + 1);

        }
    }

    std::cout << "[ElectronEfficiencySFTool::BookCombToyMCScaleFactors] m_Rndm->Uniform(0, 1) after booking " << nToyMC << "SFs: " << m_Rndm->Uniform(0, 1) << std::endl;

}

//------------------------------------------------------
double ElectronEfficiencySFTool::GetCorrSyst(int sys, double eta, double pt){

  if (!statErr || !corrSyst || !sf)
    return defSF;

	if( (sys > (nSys-1)) || (sys<0) ){
		Warning("ElectronEfficiencySFTool::GetCorrSyst", "There is no systematics # %6i", sys);
		return defSFuncert;
	}

	//find bins in eta and pt;
	int bin = corrSyst[nSys-sys-1]->FindBin(pt, eta);
	double val = corrSyst[nSys-sys-1]->GetBinContent(bin);

    // Check range
	if( pt > corrSyst[nSys-sys-1]->GetXaxis()->GetXmax() || pt < corrSyst[nSys-sys-1]->GetXaxis()->GetXmin() ||
		eta > corrSyst[nSys-sys-1]->GetYaxis()->GetXmax() || eta < corrSyst[nSys-sys-1]->GetYaxis()->GetXmin() ){

		val = defSFuncert;
	}

	return val;
}

//------------------------------------------------------
double ElectronEfficiencySFTool::GetScaleFactor(double eta, double pt){

  if (!statErr || !corrSyst || !sf)
    return defSF;

	//find bins in eta and pt;
	int bin = sf->FindBin(pt, eta);
	double val = sf->GetBinContent(bin);

	// Check range
	if( pt > sf->GetXaxis()->GetXmax() || pt < sf->GetXaxis()->GetXmin() ||
		eta > sf->GetYaxis()->GetXmax() || eta < sf->GetYaxis()->GetXmin() ){

		val = defSF;
	}

	return val;
}

//------------------------------------------------------
double ElectronEfficiencySFTool::GetToyMCScaleFactor(int nSF, double eta, double pt){

	if( uncorrToyMCSyst[nSF] == NULL ){
		Warning("ElectronEfficiencySFTool::GetToyMCScaleFactor", "There is no ToyMS systematics # %6i", nSF);
		return defSF;
	}

	//find bins in eta and pt;
	int bin = uncorrToyMCSyst[nSF]->FindBin(pt, eta);
	double val = uncorrToyMCSyst[nSF]->GetBinContent(bin);

	// Check range
	if( pt > uncorrToyMCSyst[nSF]->GetXaxis()->GetXmax() || pt < uncorrToyMCSyst[nSF]->GetXaxis()->GetXmin() ||
		eta > uncorrToyMCSyst[nSF]->GetYaxis()->GetXmax() || eta < uncorrToyMCSyst[nSF]->GetYaxis()->GetXmin() ){

		val = defSF;
	}

	return val;

}
//------------------------------------------------------
double ElectronEfficiencySFTool::GetUncorrSyst(int detailLevel, double eta, double pt){

  if (!statErr || !corrSyst || !sf)
    return defSFuncert;

	//find bins in eta and pt;
	int bin = statErr->FindBin(pt, eta);
	double val  = statErr->GetBinContent(bin);

	// Add uncorrelated systematics
	if(uncorrSyst != NULL){
		double valAdd = uncorrSyst->GetBinContent(bin);
		val = sqrt(val*val + valAdd*valAdd);
	}

	// Add correlated systematics
    for(int i=0; i<sLevel[detailLevel]; i++){
    	double valAdd = corrSyst[i]->GetBinContent(bin);
    	val = sqrt(val*val + valAdd*valAdd);
    }

	// Check range
	if( pt > statErr->GetXaxis()->GetXmax() || pt < statErr->GetXaxis()->GetXmin() ||
		eta > statErr->GetYaxis()->GetXmax() || eta < statErr->GetYaxis()->GetXmin() ){

		val = defSFuncert;
	}

	return val;
}



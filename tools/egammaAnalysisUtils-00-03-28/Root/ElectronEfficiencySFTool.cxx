#include "egammaAnalysisUtils/ElectronEfficiencySFTool.h"

#include "TObject.h"
#include <TMath.h>
#include <TROOT.h>
#include <TAxis.h>
#include <string>
#include <iostream>
#include <TRandom3.h>
//------------------------------------------------------
ElectronEfficiencySFTool::ElectronEfficiencySFTool(std::string fileName, std::string folderName){

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
    if (eig != NULL ) {
    	nSys = eig->GetNbinsX() - 1;
    	double sign = 0;

    	// Calculate details level
    	for(int i=nSys+1; i>=1; i--){
    	    sign+= eig->GetBinContent(i);
    	    if(sign > 0.9  &&  sLevel[ElectronEfficiencySFTool::simple]==0){
    	    	sLevel[ElectronEfficiencySFTool::simple] = i-2;
    	    }
    	    if(sign > 0.95  &&  sLevel[ElectronEfficiencySFTool::medium]==0){
    	    	sLevel[ElectronEfficiencySFTool::medium] = i-2;
    	    }
    	}
    }

    // Read stat uncertainties
    statErr = (TH2D*)weightfile->Get( (folderName+"/stat").c_str() );
    if (statErr == NULL ) {
        Error("ElectronEfficiencySFTool::ElectronEfficiencySFTool", "Histogramme: stat Not found");
    }
    statErr ->SetDirectory(gROOT);

    // Read scale factors
    sf = (TH2D*)weightfile->Get( (folderName+"/sf").c_str() );
    if (sf == NULL ) {
        Error("ElectronEfficiencySFTool::ElectronEfficiencySFTool", "Histogramme: sf Not found");
    }
    sf->SetDirectory(0);

    // Read all systematics from root file
    corrSyst = new TH2D*[nSys];
    for(int i=0; i<nSys; i++){
    	TString name = folderName+"/corr";
    	name += i;
    	corrSyst[i] = (TH2D*)weightfile->Get( name );
        if (corrSyst[i] == NULL ) {
            Error("ElectronEfficiencySFTool::ElectronEfficiencySFTool", "Histogramme: corr_ %6.0f Not found", i);
        }
        corrSyst[i]   ->SetDirectory(gROOT);
    }

    // Read uncorrelated uncertainties, if they are exist as a separate numbers
    uncorrSyst   = (TH2D*)weightfile->Get( (folderName+"/uncorr").c_str() );
    if (uncorrSyst != NULL ) {
    	uncorrSyst ->SetDirectory(gROOT);
    }

    weightfile->Close();
    delete weightfile;

    // Set default values for the SF and uncertainties
    defSF = 1;
    defSFuncert = 0;

}

//------------------------------------------------------
ElectronEfficiencySFTool::~ElectronEfficiencySFTool(){

}

//------------------------------------------------------
void ElectronEfficiencySFTool::BookToyMCScaleFactors(int nToyMC, int detailLevel){

	Info("ElectronEfficiencySFTool::BookToyMCScaleFactors", "Create tables for %3d ToyMC systematics ", nToyMC);

    //Create ToyMC SFs
    TRandom3 *m_Rndm = new TRandom3(1);
    uncorrToyMCSyst = new TH2D*[nToyMC];

    int nBins = (uncorrSyst->GetNbinsX() + 2) * (uncorrSyst->GetNbinsY() + 2 );

	for(int i=0; i<nToyMC; i++){
		uncorrToyMCSyst[i] = (TH2D*)corrSyst[0] -> Clone();
	}

	// Loop over all bins
    for(int bin=0; bin<nBins; bin++){

    	double val  = statErr->GetBinContent(bin);

    	// Add uncorrelated systematics
    	if(uncorrSyst != NULL){
    		double valAdd = uncorrSyst->GetBinContent(bin);
    		val += sqrt(val*val + valAdd*valAdd);
    	}

    	// Add correlated systematics
        for(int i=0; i<sLevel[detailLevel]; i++){
        	if(corrSyst[i] != NULL ){
        		double valAdd = corrSyst[i]->GetBinContent(bin);
        	    val = sqrt(val*val + valAdd*valAdd);
        	}
        }

    	for(int i=0; i<nToyMC; i++){
    		double newval = (val * m_Rndm->Gaus(0,1)) + 1;
    		uncorrToyMCSyst[i] -> SetBinContent(bin, newval );
    	}
    }

}
//------------------------------------------------------
double ElectronEfficiencySFTool::GetCorrSyst(int sys, double eta, double pt){

	if( (sys > (nSys-1)) || (sys<0) ){
		Warning("ElectronEfficiencySFTool::GetCorrSyst", "There is no systematics # %6i", sys);
		return defSFuncert;
	}

	//find bins in eta and pt;
	int bin = corrSyst[nSys-sys-1]->FindBin(pt, eta);
	double val = corrSyst[nSys-sys-1]->GetBinContent(bin);

	// Check range
	if( eta > corrSyst[nSys-sys-1]->GetXaxis()->GetXmax() || eta < corrSyst[nSys-sys-1]->GetXaxis()->GetXmin() ||
		pt > corrSyst[nSys-sys-1]->GetYaxis()->GetXmax() || pt < corrSyst[nSys-sys-1]->GetYaxis()->GetXmin() ){

		val = defSFuncert;
	}

	return val;
}

//------------------------------------------------------
double ElectronEfficiencySFTool::GetScaleFactor(double eta, double pt){

	//find bins in eta and pt;
	int bin = sf->FindBin(pt, eta);
	double val = sf->GetBinContent(bin);

	// Check range
	if( eta > sf->GetXaxis()->GetXmax() || eta < sf->GetXaxis()->GetXmin() ||
		pt > sf->GetYaxis()->GetXmax() || pt < sf->GetYaxis()->GetXmin() ){

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
	if( eta > uncorrToyMCSyst[nSF]->GetXaxis()->GetXmax() || eta < uncorrToyMCSyst[nSF]->GetXaxis()->GetXmin() ||
		pt > uncorrToyMCSyst[nSF]->GetYaxis()->GetXmax() || pt < uncorrToyMCSyst[nSF]->GetYaxis()->GetXmin() ){

		val = defSF;
	}

	return val;

}
//------------------------------------------------------
double ElectronEfficiencySFTool::GetUncorrSyst(int detailLevel, double eta, double pt){

	//find bins in eta and pt;
	int bin = statErr->FindBin(pt, eta);
	double val  = statErr->GetBinContent(bin);

	// Add uncorrelated systematics
	if(uncorrSyst != NULL){
		double valAdd = uncorrSyst->GetBinContent(bin);
		val += sqrt(val*val + valAdd*valAdd);
	}

	// Add correlated systematics
    for(int i=0; i<sLevel[detailLevel]; i++){
    	double valAdd = corrSyst[i]->GetBinContent(bin);
    	val = sqrt(val*val + valAdd*valAdd);
    }

	// Check range
	if( eta > statErr->GetXaxis()->GetXmax() || eta < statErr->GetXaxis()->GetXmin() ||
		pt > statErr->GetYaxis()->GetXmax() || pt < statErr->GetYaxis()->GetXmin() ){

		val = defSFuncert;
	}

	return val;
}



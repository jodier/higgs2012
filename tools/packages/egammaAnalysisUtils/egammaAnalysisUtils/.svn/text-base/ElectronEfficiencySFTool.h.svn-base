#ifndef __ELECTRONEFFICIENCYSFTOOL_H
#define __ELECTRONEFFICIENCYSFTOOL_H

/*
////////////////////////////////////////////////////////
Name    : ElectronEfficiencySFTool.h

This class provide an interface for the SFs and their uncorrelated and correlated uncertainties.
Written by M. Karnevskiy.

The input root file should contain SFs, statistical and one or several systematic uncertainties (2D in bins of eta and pT).
In case of several systematic uncertainties, the eigen-vector (1D) should provide an information about total number of systematics and their significance.
In additional, uncorrelated uncertainties can be accessed from the input root file.

Several detailed levels define the detail level of the uncertainties propagation.

This class provide a SFs for ToyMC method of the uncertainties propagation.

BookToyMCScaleFactors - Create a SFs for ToyMC
GetToyMCScaleFactor - Return SF with respect of the electrons kinematic and ToyMC number

*/

#include "TFile.h"
#include "TH1.h"
#include "TH2D.h"
#include <string>


class ElectronEfficiencySFTool{

public:
	ElectronEfficiencySFTool(std::string fileName, std::string folderName);
	~ElectronEfficiencySFTool();

	enum DetailLevel{simple, medium, detailed};

	// Return number of systematics, which corresponds to a given detail level
	int GetNSyst(int detailLevel){
		return nSys-sLevel[detailLevel];
	}

	// Create histograms for usual and combined ToyMC method of the uncertainty propagation
	void BookToyMCScaleFactors(int nToyMC, int detailLevel);
    void BookCombToyMCScaleFactors(int nToyMC, int detailLevel);

	// Return correlated systematic uncertainties #n in given eta and pt bin
	double GetCorrSyst(int sys, double eta, double pt);

	// Return scale factor in given eta and pt bin
	double GetScaleFactor(double eta, double pt);

	// Return SF for the ToyMC systematics
	double GetToyMCScaleFactor(int nSF, double eta, double pt);

	// Return uncorrelated systematic uncertainties in given bin
	double GetUncorrSyst(int detailLevel, double eta, double pt);

        void SetSeed(int s);

private:
        // Avoid coverity warnings.
        ElectronEfficiencySFTool (const ElectronEfficiencySFTool&);
        ElectronEfficiencySFTool& operator= (const ElectronEfficiencySFTool&);

	TH2D** corrSyst;
	TH2D* uncorrSyst;
	TH2D** uncorrToyMCSyst;
	TH2D* sf;
	TH2D* statErr;

	int sLevel[3];
	int nSys;

	int defSF;
	int defSFuncert;
  
        int seed;

};


#endif // ElectronEfficiencySFTool

#include "egammaAnalysisUtils/ElectronMCChargeCorrector.h"

#include <TMath.h>
#include <TROOT.h>
#include <iostream>

//------------------------------------------------------
ElectronMCChargeCorrector::ElectronMCChargeCorrector(std::string sim_id, std::string fileName) {
    // Constructor
    chMID_data = chMID_mc = corr = 0;

    TFile* weightfile = TFile::Open(fileName.c_str());

    if (weightfile == NULL) {
        Error("ElectronMCChargeCorrector", (fileName + " not found").c_str());
    } else {
        Info("ElectronMCChargeCorrector", ("Open root file: " + fileName).c_str());
    }

    // Read info from external file
    chMID_data = (TH1*) weightfile->Get((sim_id + "/" + "chmid_data").c_str());
    chMID_mc = (TH1*) weightfile->Get((sim_id + "/" + "chmid_mc").c_str());
    corr = (TH1*) weightfile->Get((sim_id + "/" + "corr").c_str());
    if (chMID_data == NULL || chMID_mc == NULL || corr == NULL) {
        Error("ElectronMCChargeCorrector::ElectronMCChargeCorrector",
                "Histogram: chmid_data or chmid_mc or corr not found");
        return;
    }
    chMID_data->SetDirectory(gROOT);
    chMID_mc->SetDirectory(gROOT);
    corr->SetDirectory(gROOT);

    weightfile->Close();
    delete weightfile;

    m_Rndm = new TRandom3(1);
}

//------------------------------------------------------
ElectronMCChargeCorrector::~ElectronMCChargeCorrector() {
    if (chMID_data)
        delete chMID_data;
    if (chMID_mc)
        delete chMID_mc;
    if (corr)
        delete corr;
}

//------------------------------------------------------
int ElectronMCChargeCorrector::GetCorrectedCharge(double etaclus_rec,
        int charge_rec, int charge_true, eChargeCorrection type) const {
    if (chMID_data == NULL || chMID_mc == NULL || corr == NULL) {
        return charge_rec;
    }

    int bin = chMID_data->FindBin(etaclus_rec);
    double val_data = chMID_data->GetBinContent(bin);
    double val_mc = chMID_mc->GetBinContent(bin);

    if (type == chg_sysup) {
        val_data += corr->GetBinContent(bin);
    } else if (type == chg_sysdown) {
        val_data -= corr->GetBinContent(bin);
    }

    double rmd = m_Rndm->Rndm();

    // three cases:
    // 1. more chMID in MC than data: randomly "correct" the charge, if wrongly reconstructed
    // 2. less chMID in MC than data: randomly "flip" the charge, if rightly reconstructed
    // 3. leave everything untouched
    if (val_mc > val_data && (charge_rec != charge_true) && rmd < ((val_mc - val_data) / val_mc)) {
        return charge_true;
    } else if (val_mc < val_data && (charge_rec == charge_true) && rmd < ((val_data - val_mc) / (1 - val_mc))) {
        return -charge_rec;
    } else {
        return charge_rec;
    }

}

//------------------------------------------------------
int ElectronMCChargeCorrector::GetTruthCharge(const TLorentzVector & el_fourv_rec, const std::vector<TLorentzVector> & el_fourv_true,
        const std::vector<int> & el_charge_true) {
    // truth charge is defined as truth electron closest in dR
    // returns a silent 0, in case the truth electron array is empty or something else is strange

    if (el_fourv_true.size() != el_charge_true.size())
        return 0;

    double drmin = 999.;
    int true_charge = 0;

    for (unsigned int i = 0; i < el_fourv_true.size(); i++) {
        double dr = el_fourv_rec.DeltaR(el_fourv_true[i]);
        if (dr < drmin) {
            drmin = dr;
            true_charge = el_charge_true[i];
        }
    }

    return true_charge;
}

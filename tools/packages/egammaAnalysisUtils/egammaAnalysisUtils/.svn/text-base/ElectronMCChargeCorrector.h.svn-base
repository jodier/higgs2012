#ifndef __ELECTRONMCCHARGECORRECTOR_H
#define __ELECTRONMCCHARGECORRECTOR_H

/*
  Tool to correct adapt the charge misidentification on MC to data level

  Written by M. Karnevskiy, J. Kretzschmar

  This correction is for MC only and needs the "true electron charge" information!
  Correction is specific to the chosen Electron ID level
  and (probably) also to the simulation flavour and year

  For now corrections are provided for simulation types:
  * MC11c_G4FullSim

  The following basic electron ID levels can be chosen:
  * MediumPP
  * TightPP
  In addition there are three levels with extra isolation cuts as defined in the Eiso tool:
  * MediumPP_Eiso97Ptcone40
  * TightPP_Eiso97Ptcone40
  * TightPP_Eiso97Ptcone40_Eiso98Etcone20

  Give one string for "[simulation type]/[ID levels]".
  The necessary input is stored in share directory, file ChargeMID.root

  Example usage:
  
  ElectronMCChargeCorrector *corr = new ElectronMCChargeCorrector("MC11c_G4FullSim/MediumPP", "share/ChargeMID.root");
  
  if (ismc)
    el_charge_rec = corr->GetCorrectedCharge(el_etaclus, el_charge_rec, el_charge_true, ElectronMCChargeCorrector::chg_nominal);

  This assumes, that you have yourself determined the "true" charge of the reconstructed electron as el_charge_true.

  An alternative call, which will perform a simple truth matching for you, starts instead from a list of
  your true signal electrons (e.g. 2 for Z->ee, 1 for W->enu, 4 for H->4e etc.)
  std::vector<TLorentzVector> true_electrons_fourv;
  std::vector<int> true_electrons_charge;
  true_electrons_fourv.push_back(first_true_el_fourv);
  true_electrons_charge.push_back(first_true_el_pdgid == +11 ? -1 : +1);
  true_electrons_fourv.push_back(second_true_el_fourv);
  true_electrons_charge.push_back(second_true_el_pdgid == +11 ? -1 : +1);
  ...

  and then call
  
  if (ismc)
    el_charge_rec = corr->GetCorrectedCharge(el_etaclus, el_charge_rec,
                                             true_electrons_fourv, true_electrons_charge,
					     ElectronMCChargeCorrector::chg_nominal);

*/

#include "TFile.h"
#include "TH1.h"
#include <string>
#include <TRandom3.h>
#include "TLorentzVector.h"

class ElectronMCChargeCorrector {

public:
    enum eChargeCorrection {
        chg_nominal, chg_sysup, chg_sysdown
    };

    ElectronMCChargeCorrector(std::string sim_id, std::string fileName);
    ~ElectronMCChargeCorrector();

    // Return corrected charge of the electron
    int GetCorrectedCharge(double etaclus_rec, int charge_rec,
            int charge_true, eChargeCorrection type = chg_nominal) const;

    int GetCorrectedCharge(double etaclus_rec, int charge_rec, const TLorentzVector & el_fourv_rec,
            const std::vector<TLorentzVector> & el_fourv_true, const std::vector<int> & el_charge_true,
            eChargeCorrection type = chg_nominal) const {
        return GetCorrectedCharge(etaclus_rec, charge_rec,
                GetTruthCharge(el_fourv_rec, el_fourv_true, el_charge_true), type);
    }

    void SetRndSeed(int seed){
        m_Rndm->SetSeed(seed);
    }

    // Return true charge of the electron given list of reco and true four vectors and charges
    static int GetTruthCharge(const TLorentzVector & el_fourv_rec,
            const std::vector<TLorentzVector> & el_fourv_true, const std::vector<int> & el_charge_true);

private:

    TH1* chMID_data;
    TH1* chMID_mc;
    TH1* corr;
    TRandom3 *m_Rndm;
};


#endif // ElectronMCChargeCorrector

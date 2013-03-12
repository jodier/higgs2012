//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 30.08.2012, AUTHOR: OLIVER KORTNER
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifndef HiggsZZ4lUtils_MuonResolutionAndMomentumScaleFactorsH
#define HiggsZZ4lUtils_MuonResolutionAndMomentumScaleFactorsH

//:::::::::::::::::::::::::::::::::::::::::::::::::
//:: CLASS MuonResolutionAndMomentumScaleFactors ::
//:::::::::::::::::::::::::::::::::::::::::::::::::

/// \class MuonResolutionAndMomentumScaleFactors
///
/// This class provides scale factors to the estimated errors of combined,
/// segment tagged and calorimeter tagged muons as well as scale factors for
/// momentum scale.
///
/// \date 30.08.2012
///
/// \author Oliver.Kortner@CERN.Ch

//::::::::::::::::::
//:: HEADER FILES ::
//::::::::::::::::::

// STL //
#include <vector>
#include <string>

// ROOT //
#include "TLorentzVector.h"

namespace HiggsZZ4lUtils {

class MuonResolutionAndMomentumScaleFactors {

public:
// Constructor //
    MuonResolutionAndMomentumScaleFactors(const std::string & data_filename);
    ///< Constructor.
    ///< \param data_filename   Name of the file holding the scale factors.

// Methods //
    double getResolutionScaleFactor(const TLorentzVector & p,
                                    int type);
    ///< Get the resolution scale factor.
    ///< \param p   Four momentum of the muon.
    ///< \param type    type = 1 for combined muons,
    ///<                     = 2 for segment or calorimeter tagged muons.

    double getResolutionScaleFactorError(const TLorentzVector & p,
                                    int type);
    ///< Get the error of the resolution scale factor.
    ///< \param p   Four momentum of the muon.
    ///< \param type    type = 1 for combined muons,
    ///<                     = 2 for segment or calorimeter tagged muons.
    double getMomentumScaleFactor(const TLorentzVector & p,
                                    int type);
    ///< Get the momentum scale factor.
    ///< Meaning of the scale factor: p_rec = (scale factor)*p_generator_level.
    ///< \param p   Four momentum of the muon.
    ///< \param type    type = 1 for combined muons,        
    ///<                     = 2 for segment or calorimeter tagged muons.

    double getMomentumScaleFactorError(const TLorentzVector & p,
                                    int type);
    ///< Get the error of the momentum scale factor.
    ///< \param p   Four momentum of the muon.
    ///< \param type    type = 1 for combined muons,
    ///<                     = 2 for segment or calorimeter tagged muons.

private:
    std::vector<double> m_eta_min, m_eta_max;

    std::vector<double> m_res_SF_CB, m_res_SF_CB_err;
    std::vector<double> m_mom_SF_CB, m_mom_SF_CB_err;

    std::vector<double> m_res_SF_ID, m_res_SF_ID_err;
    std::vector<double> m_mom_SF_ID, m_mom_SF_ID_err; 

    unsigned int getEtaBin(const TLorentzVector & p);

};

}

#endif


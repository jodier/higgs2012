/********************************************************************

NAME:     EMErrorDetail.cxx
PACKAGE:  offline/Reconstruction/egamma/egammaEvent

AUTHORS:  T. Cuhadar Donszelmann
CREATED:  May 2009
PURPOSE:  Build track/conv. tracks/photon error matrices
UPDATED:  Jun 22, 2009 (TCD/FD) fix in caloEta()
********************************************************************/

#include "egammaEvent/EMErrorDetail.h"
#include "GaudiKernel/GaudiException.h"
#include "egammaEvent/EMShower.h"
#include "DataModel/ClassName.h"
#include "DataModel/ElementLink.h"
#include "TrkTrack/Track.h" 
#include "TrkParametersBase/ParametersBase.h"
#include "TrkParticleBase/TrackParticleBase.h"
#include "TrkParameters/MeasuredPerigee.h"
#include "TrkEventPrimitives/ErrorMatrix.h" 
#include "VxVertex/VxTrackAtVertex.h"
#include "VxVertex/VxCandidate.h"
#include "TrkNeutralParameters/MeasuredNeutralPerigee.h"
#include "CaloUtils/CaloClusterVertexCorrection.h"
#include "TrkEventPrimitives/GlobalPosition.h"
#include "egammaConditions/EMClusterErrorsParametrizations.h"
#include "SGTools/BaseInfo.h"

#include <cmath>

using CLHEP::HepVector;

const double DEFAULT_MOMENTUM = 1e11;

EMErrorDetail::EMErrorDetail() : egDetail() { }

EMErrorDetail::~EMErrorDetail() { }

/** interfaces */
std::string EMErrorDetail::s_className = ClassName<EMErrorDetail>::name();

const std::string& EMErrorDetail::className() const {
  return s_className;
}

// ===============================================================
int EMErrorDetail::intParameter(egammaParameters::ParamDef key) const {


  typedef std::pair<egammaParameters::ParamDef,int> elParams;

  int result = (int)egammaParameters::EgParamUndefined;
  std::vector<elParams>::const_iterator p = m_parametersInt.begin();
 
  for (;p !=m_parametersInt.end(); p++) {
    if ( (*p).first == key ){
      result = (*p).second;
      break;
    }
  }
  return result;
}

// ==================================================================
double EMErrorDetail::parameter(egammaParameters::ParamDef key) const {

  if ( hasIntParameter(key) ) {
    return (double) intParameter(key);
  }

  typedef std::pair<egammaParameters::ParamDef,double> elParams;

  double result = egammaParameters::EgParamUndefined;
  std::vector<elParams>::const_iterator p = m_parameters.begin();
 
  for (;p !=m_parameters.end(); p++) {
    if ( (*p).first == key ) {
      result = (*p).second;
      break;
    }
  }

  return result;
}

// ===================================================================
void EMErrorDetail::set_parameterInt(egammaParameters::ParamDef key, int value, bool overwrite) {

  typedef std::pair<egammaParameters::ParamDef,int> elParams;

  std::vector<elParams>::iterator p = m_parametersInt.begin();
 
  for (;p !=m_parametersInt.end(); p++) {
    if ( (*p).first == key ) break;
  }

  if ( p == m_parametersInt.end() ) {
    m_parametersInt.push_back( elParams(key,value) );
  }
  else {
    if ( overwrite ) {
      (*p).second = value;
    }
    else {      
      throw GaudiException("parameter not saved", "EMErrorDetail::set_parameter(...)", false);
    }
  }
}

// ======================================================================
void EMErrorDetail::set_parameter(egammaParameters::ParamDef key, double value, bool overwrite) {

  if ( hasIntParameter(key) ) {
    set_parameterInt(key,(int)value,overwrite);
  }

  typedef std::pair<egammaParameters::ParamDef,double> elParams;
  std::vector<elParams>::iterator p = m_parameters.begin();
 
  for (;p !=m_parameters.end(); p++) {
    if ( (*p).first == key ) break;
  }

  if ( p == m_parameters.end() ) {
    m_parameters.push_back( elParams(key,value) );
  }
  else {
    if ( overwrite ) {
      (*p).second = value;
    }
    else {      
      throw GaudiException("parameter not saved", "EMErrorDetail::set_parameter(...)", false);
    }
  }

}

// =======================================================================
void EMErrorDetail::fillEMErrorDetail(const egamma* eg, const Trk::ParametersBase* pb, 
				      const EMClusterErrorsParametrizations* pars, 
				      const HepGeom::Point3D<double>& vx) {
  
  if ( eg == NULL ) return;

  // first clear the old, in case we are overwriting anything.
  m_parameters.clear();
  m_parametersInt.clear();

  if (eg->author(egammaParameters::AuthorElectron |
		 egammaParameters::AuthorSofte |
		 egammaParameters::AuthorTrigElectron)) { //Electron case
    if ( pb && eg->trackParticle() != 0 ){
      // it is a track 
      fillTrackPerigeeMatrixElements(pb);
      // fill for track cluster
      fillPhotonMatrixElements(eg, pars, vx);    
    } else {
      // this is the case where electrons are treaded as
      // photons for test purposes or for trigger electrons
      fillPhotonMatrixElements(eg, pars, vx, true);
    }
  } else if ( eg->conversion() != 0) {
    // it is a converted photon 
    fillConvertedPhotonMatrixElements(pb);	
     // fill for track cluster
    fillPhotonMatrixElements(eg, pars, vx);	
  } else {
    // It is unconverted photon  
    fillPhotonMatrixElements(eg, pars, vx);
  }

  return;
}

// =======================================================================
bool EMErrorDetail::isElectron(const egamma* eg, bool forcePhoton) const
{
  return (!forcePhoton && ((eg->conversion() != 0) || (eg->trackParticle() != 0)));
}

// =======================================================================
double EMErrorDetail::getClusterEtaPosError(const egamma* eg, 
					    const EMClusterErrorsParametrizations* pars,
					    bool forcePhoton) const
{

  EMClusterErrorsParametrizations::Type tp = isElectron(eg, forcePhoton) ? 
    EMClusterErrorsParametrizations::ELECTRON : 
    EMClusterErrorsParametrizations::PHOTON;

  double clusterE = 1;
  double eta = 0;
  const CaloCluster* aCluster = eg->cluster();
  if (aCluster) {
    clusterE = eg->cluster()->e();
    if (clusterE < 1) clusterE = 1;
    eta = aCluster->eta();
  }
  if (!pars) {
    return 0.30e-3*sqrt(100./(clusterE*0.001));
  } else {
    const EMClusterEtaPosErrorsMatrix& mat = pars->getEtaPosMatrix(tp);
    const double err = mat.getError(eta, clusterE);
    if (err != -1.0) {
      return err;
    } else {
      // it actually was not found
      // use old parametrization.
      return 0.30e-3*sqrt(100./(clusterE*0.001));
    }
  }
}


// =======================================================================
double EMErrorDetail::getClusterEnergyError(const egamma* eg, 
					    const EMClusterErrorsParametrizations* pars, 
					    bool forcePhoton ) const
{

  EMClusterErrorsParametrizations::Type tp = isElectron(eg, forcePhoton) ? 
    EMClusterErrorsParametrizations::ELECTRON : 
    EMClusterErrorsParametrizations::PHOTON;

  const CaloCluster* aCluster = eg->cluster();
  if (aCluster == NULL || pars == NULL) return 1e-3; // in merging, use cluster energy

  // note, the parametrization is in cluster eta, not pointing eta 
  return pars->getEnergyMatrix(tp).getError(aCluster->eta(), aCluster->energy());
} 

// =======================================================================
double EMErrorDetail::getClusterEtaError(const egamma* eg, 
					 const EMClusterErrorsParametrizations* pars, 
					 bool forcePhoton ) const 
{

  EMClusterErrorsParametrizations::Type tp = isElectron(eg, forcePhoton) ? 
    EMClusterErrorsParametrizations::ELECTRON : 
    EMClusterErrorsParametrizations::PHOTON;

  const CaloCluster* aCluster = eg->cluster();
  double eta = (aCluster) ?  caloEta(eg, aCluster->eta()) : 0;
  if (fabs(eta) > 8) eta = 8.0;
  if (pars == NULL) {
    // fall back to hardcoded old-style errors.
    //    const double clusterEnergyGeV = aCluster->energy()/1000.0; //GeV
    const double clusterEnergyGeV = 100.0; //GeV - just use 100 as the default
    const double sigma_theta = 0.07 /sqrt(clusterEnergyGeV);
    const double theta = 2.*atan(exp(eta));
    return ( fabs(sigma_theta/sin(theta)) );
  }
  // the parametrization of theta error is only in energy; eta is used to convert
  // between theta error and eta error
  return pars->getEtaMatrix(tp).getError(eta, 
                                         aCluster ? aCluster->energy(): 0);
}

// =======================================================================
double EMErrorDetail::getClusterPhiError(const egamma* eg, 
					 const EMClusterErrorsParametrizations* pars, 
					 bool forcePhoton ) const 
{

  EMClusterErrorsParametrizations::Type tp = isElectron(eg, forcePhoton) ? 
    EMClusterErrorsParametrizations::ELECTRON : 
    EMClusterErrorsParametrizations::PHOTON;

  const CaloCluster* aCluster = eg->cluster();
  if (aCluster == NULL || pars == NULL) return 1e10; // use track phi

  // note, the parametrization is really only in energy; eta is ignored
  return pars->getPhiMatrix(tp).getError(caloEta(eg, aCluster->eta()), aCluster->energy());
}

// ======================================================================
// Fill Error matrix for converted photons
bool EMErrorDetail::fillConvertedPhotonMatrixElements(const Trk::ParametersBase* pb) {
  
  if(pb == 0) return false;

//   double clusterEnergy;
//   clusterEnergy = eg->cluster()->energy();

  const Trk::MeasuredNeutralPerigee* measuredneutralperigee = dynamic_cast<const Trk::MeasuredNeutralPerigee*>(pb);
  const Trk::MeasuredPerigee* measuredperigee = dynamic_cast<const Trk::MeasuredPerigee*>(pb);
  // if(measuredneutralperigee == NULL || measuredperigee == NULL) return false;

  if (measuredneutralperigee) {

    EMconvertedphoton_perigee_d0(measuredneutralperigee->parameters()[Trk::d0]);
    EMconvertedphoton_perigee_z0(measuredneutralperigee->parameters()[Trk::z0]);
    EMconvertedphoton_perigee_phi0(measuredneutralperigee->parameters()[Trk::phi]);
    EMconvertedphoton_perigee_theta(measuredneutralperigee->parameters()[Trk::theta]);
//     EMconvertedphoton_perigee_Eclus(clusterEnergy);
    EMconvertedphoton_perigee_eta(measuredneutralperigee->eta());
    const double qOverP = measuredneutralperigee->parameters()[Trk::qOverP];
    if (qOverP != 0) {
      EMconvertedphoton_perigee_momentum(fabs(1./ qOverP));
    } else {
      EMconvertedphoton_perigee_momentum(DEFAULT_MOMENTUM);
    }
 
    if ( !(fillConvertedPhotonErrorMatrix(measuredneutralperigee->localErrorMatrix())) ) {
      /* Error matrix failed */
      return false;
    }
    
  } else if (measuredperigee) {

    EMconvertedphoton_perigee_d0(measuredperigee->parameters()[Trk::d0]);
    EMconvertedphoton_perigee_z0(measuredperigee->parameters()[Trk::z0]);
    EMconvertedphoton_perigee_phi0(measuredperigee->parameters()[Trk::phi]);
    EMconvertedphoton_perigee_theta(measuredperigee->parameters()[Trk::theta]);
//     EMconvertedphoton_perigee_Eclus(clusterEnergy);
    EMconvertedphoton_perigee_eta(measuredperigee->eta());
    const double qOverP = measuredperigee->parameters()[Trk::qOverP];
    if (qOverP != 0) {
      EMconvertedphoton_perigee_momentum(fabs(1./ qOverP));
    } else {
      EMconvertedphoton_perigee_momentum(DEFAULT_MOMENTUM);
    } 
        
    if ( !(fillConvertedPhotonErrorMatrix(measuredperigee->localErrorMatrix())) ) {
      /* Error matrix failed */
      return false;
    }
  } else {
    return false;
  }

  return true;

}

// =======================================================================
bool EMErrorDetail::fillConvertedPhotonErrorMatrix(const Trk::ErrorMatrix& errorMatrix) {

  EMconvertedphoton_perigee_Covd0d0          ( errorMatrix.covValue(Trk::d0,    Trk::d0))     ;
  EMconvertedphoton_perigee_Covd0z0          ( errorMatrix.covValue(Trk::d0,    Trk::z0))     ;
  EMconvertedphoton_perigee_Covd0phi         ( errorMatrix.covValue(Trk::d0,    Trk::phi))    ;
  EMconvertedphoton_perigee_Covd0theta       ( errorMatrix.covValue(Trk::d0,    Trk::theta))  ;
//   EMconvertedphoton_perigee_Covd0Eclus       ( 0. ) ;
  EMconvertedphoton_perigee_Covz0z0          ( errorMatrix.covValue(Trk::z0,    Trk::z0))     ;
  EMconvertedphoton_perigee_Covz0phi         ( errorMatrix.covValue(Trk::z0,    Trk::phi))    ;
  EMconvertedphoton_perigee_Covz0theta       ( errorMatrix.covValue(Trk::z0,    Trk::theta))  ;
//   EMconvertedphoton_perigee_Covz0Eclus       ( 0. ) ;
  EMconvertedphoton_perigee_Covphiphi        ( errorMatrix.covValue(Trk::phi,   Trk::phi))    ;
  EMconvertedphoton_perigee_Covphitheta      ( errorMatrix.covValue(Trk::phi,   Trk::theta))  ;
//   EMconvertedphoton_perigee_CovphiEclus      ( 0. ) ;
  EMconvertedphoton_perigee_Covthetatheta    ( errorMatrix.covValue(Trk::theta, Trk::theta))  ;
//   EMconvertedphoton_perigee_CovthetaEclus    ( 0. ) ;

//   double clusterEnergyError = getClusterEnergyError(eg, pars);
//   EMconvertedphoton_perigee_CovEclusEclus (clusterEnergyError * clusterEnergyError ) ;

  return true;
}


// =====================================================================
// Fill Error matrix for track candidates
bool EMErrorDetail::fillTrackPerigeeMatrixElements(const Trk::ParametersBase* pb) {
  if(pb == 0) return false;
  
  const Trk::MeasuredPerigee* measuredperigee = dynamic_cast<const Trk::MeasuredPerigee*>(pb);
 
//   double clusterEnergy;
//   clusterEnergy = eg->cluster()->energy();

  CLHEP::HepVector v(5,0);
  if (measuredperigee){
    EMtrack_perigee_d0(measuredperigee->parameters()[Trk::d0]);
    EMtrack_perigee_z0(measuredperigee->parameters()[Trk::z0]);
    EMtrack_perigee_phi0(measuredperigee->parameters()[Trk::phi]);
    EMtrack_perigee_theta(measuredperigee->parameters()[Trk::theta]);
//     EMtrack_perigee_Eclus(clusterEnergy);
    EMtrack_perigee_eta(measuredperigee->eta());
    const double qOverP = measuredperigee->parameters()[Trk::qOverP];
    if (qOverP != 0) {
      EMtrack_perigee_momentum(fabs(1./ qOverP));
    } else {
      EMtrack_perigee_momentum(DEFAULT_MOMENTUM);
    }
    
    if ( !(fillTrackPerigeeErrorMatrix(measuredperigee->localErrorMatrix())) ) {
      /* Error matrix failed */
      return false;
    }
    return true;
  } else {
    return false;
  }

  return true;

}

// =======================================================================
bool EMErrorDetail::fillTrackPerigeeErrorMatrix(const Trk::ErrorMatrix& errorMatrix) {

  EMtrack_perigee_Covd0d0          ( errorMatrix.covValue(Trk::d0,    Trk::d0))     ;
  EMtrack_perigee_Covd0z0          ( errorMatrix.covValue(Trk::d0,    Trk::z0))     ;
  EMtrack_perigee_Covd0phi         ( errorMatrix.covValue(Trk::d0,    Trk::phi))    ;
  EMtrack_perigee_Covd0theta       ( errorMatrix.covValue(Trk::d0,    Trk::theta))  ;
//   EMtrack_perigee_Covd0Eclus       ( 0. ) ;
  EMtrack_perigee_Covz0z0          ( errorMatrix.covValue(Trk::z0,    Trk::z0))     ;
  EMtrack_perigee_Covz0phi         ( errorMatrix.covValue(Trk::z0,    Trk::phi))    ;
  EMtrack_perigee_Covz0theta       ( errorMatrix.covValue(Trk::z0,    Trk::theta))  ;
//   EMtrack_perigee_Covz0Eclus       ( 0. ) ;
  EMtrack_perigee_Covphiphi        ( errorMatrix.covValue(Trk::phi,   Trk::phi))    ;
  EMtrack_perigee_Covphitheta      ( errorMatrix.covValue(Trk::phi,   Trk::theta))  ;
//   EMtrack_perigee_CovphiEclus      ( 0. ) ;
  EMtrack_perigee_Covthetatheta    ( errorMatrix.covValue(Trk::theta, Trk::theta))  ;
//   EMtrack_perigee_CovthetaEclus    ( 0. ) ;

//   double clusterEnergyError;
//   clusterEnergyError = getClusterEnergyError(eg, pars);

//   EMtrack_perigee_CovEclusEclus (clusterEnergyError * clusterEnergyError ) ;

  return true;
}


// ===================================================================
double EMErrorDetail::caloEta(const egamma* eg, double clusterEta) const {

  const double etaPointing = eg->detailValue(egammaParameters::etap);
  if ( fabs(etaPointing - clusterEta ) < 0.15 ) {
    return etaPointing;
  } else {
    return clusterEta;
  }
}

// ======================================================================
// Fill Error matrix for calorimeter values. It gets called for all egamma particles.
// if forcePhotons (default=false) is set to true, it forces photon errors
bool EMErrorDetail::fillPhotonMatrixElements(const egamma* eg, const EMClusterErrorsParametrizations* pars, 
					     const HepGeom::Point3D<double>& vtx, bool forcePhoton) {

  const CaloCluster* aCluster = eg->cluster();
  if (aCluster == NULL) return false;


   // ideally CaloClusterChangeVertexState would be changed to take a
   // GlobalPosition (HepGeom::Point3D<double>) or at least a
   // HepGeom::BasicVector3D to avoid creating this vector.
   const HepGeom::Vector3D<double> vect(vtx);

   CaloClusterChangeVertexState mychange(aCluster, &vect);
 
   const double clusterPhi = aCluster->phi();
   const double clusterEta = aCluster->eta();
   const double clusterEnergy = aCluster->energy();

   EMphoton_eta(caloEta(eg, clusterEta));
   EMphoton_phi0(clusterPhi);
   EMphoton_Eclus(clusterEnergy);

   if ( !(fillPhotonErrorMatrix(eg, pars, forcePhoton)) ) {
     /* Error matrix failed */
     return false;
   } 

   return true;
}

// =======================================================================
bool EMErrorDetail::fillPhotonErrorMatrix(const egamma* eg, const EMClusterErrorsParametrizations* pars, bool forcePhoton) {

  const double clusterEtaError = getClusterEtaError(eg, pars, forcePhoton);
  const double clusterPhiError = getClusterPhiError(eg, pars, forcePhoton);
  const double clusterEnergyError = getClusterEnergyError(eg, pars, forcePhoton);

  EMphoton_Covetaeta     ( clusterEtaError*clusterEtaError) ;
  EMphoton_Covetaphi     ( 0. ) ;
  EMphoton_CovetaEclus   ( 0. ) ;  
  EMphoton_Covphiphi     ( clusterPhiError*clusterPhiError)  ;
  EMphoton_CovphiEclus   ( 0. ) ;
  EMphoton_CovEclusEclus ( clusterEnergyError*clusterEnergyError ) ;

  return true;
}

// ====================================================================
CLHEP::HepSymMatrix EMErrorDetail::getEMPhotonErrorMatrix() const {

  // Make a 3x3 matrix that is filled with zero's alternatively we could fill it with the identity matrix;
  // Chosen the identity matrix option (second argument = 1)
  CLHEP::HepSymMatrix hepSymMatrix(3, 1);
  // Fill the matrix E,eta,phi,M
  hepSymMatrix(1,1) = EMphoton_CovEclusEclus();
  hepSymMatrix(1,2) = EMphoton_CovetaEclus();
  hepSymMatrix(1,3) = EMphoton_CovphiEclus();
  hepSymMatrix(2,2) = EMphoton_Covetaeta();
  hepSymMatrix(2,3) = EMphoton_Covetaphi();
  hepSymMatrix(3,3) = EMphoton_Covphiphi(); 
  
   return hepSymMatrix;
   
}

// =======================================================================
bool EMErrorDetail::fillEMTrackCombinedErrorMatrix(const CLHEP::HepSymMatrix& combinedMatrix) {


  EMtrack_comb_Covd0d0    ( combinedMatrix(1,1) );
  EMtrack_comb_Covd0z0    ( combinedMatrix(1,2) );
  EMtrack_comb_Covd0phi   ( combinedMatrix(1,3) );
  EMtrack_comb_Covd0eta   ( combinedMatrix(1,4) ) ;
  EMtrack_comb_Covd0P     ( combinedMatrix(1,5) );
  EMtrack_comb_Covz0z0    ( combinedMatrix(2,2) );
  EMtrack_comb_Covz0phi   ( combinedMatrix(2,3) );
  EMtrack_comb_Covz0eta   ( combinedMatrix(2,4) );
  EMtrack_comb_Covz0P     ( combinedMatrix(2,5) );
  EMtrack_comb_Covphiphi  ( combinedMatrix(3,3) );
  EMtrack_comb_Covphieta  ( combinedMatrix(3,4) );
  EMtrack_comb_CovphiP    ( combinedMatrix(3,5) );
  EMtrack_comb_Covetaeta  ( combinedMatrix(4,4) );
  EMtrack_comb_CovetaP    ( combinedMatrix(4,5) );
  EMtrack_comb_CovPP      ( combinedMatrix(5,5) );

  return true;
}

// ====================================================================
CLHEP::HepSymMatrix EMErrorDetail::getCombinedErrorMatrix() const 
{
  // see if combined matrix exists, if so, return it, otherwise,
  // it's an unconverted photon, so just return the photon error
  // matrix.
  if (EMtrack_comb_CovPP() == egammaParameters::EgParamUndefined) {
    return getEMPhotonErrorMatrix();
  } else {
    return getEMTrackCombinedErrorMatrix();
  }
}

// ====================================================================
CLHEP::HepSymMatrix EMErrorDetail::getUncombinedErrorMatrix() const 
{
  // this still looks for combined matrix to make the decision
  if (EMtrack_comb_CovPP() == egammaParameters::EgParamUndefined) {
    return getEMPhotonErrorMatrix();
  } else {
    return getEMTrackUncombinedErrorMatrix();
  }
}

// ====================================================================
CLHEP::HepSymMatrix EMErrorDetail::get4x4CombinedErrorMatrix() const 
{
  // see if combined matrix exists, if so, return it, otherwise,
  // it's an unconverted photon, so just return the photon error
  // matrix.
  if (EMtrack_comb_CovPP() == egammaParameters::EgParamUndefined) {
    return get4x4EMPhotonErrorMatrix();
  } else {
    return get4x4EMTrackCombinedErrorMatrix();
  }
}

// ====================================================================
CLHEP::HepSymMatrix EMErrorDetail::get4x4UncombinedErrorMatrix() const 
{
  // this still looks for combined matrix to make the decision
  if (EMtrack_comb_CovPP() == egammaParameters::EgParamUndefined) {
    return get4x4EMPhotonErrorMatrix();
  } else {
    return get4x4EMTrackUncombinedErrorMatrix();
  }
}

// ====================================================================
CLHEP::HepSymMatrix EMErrorDetail::getEMTrackCombinedErrorMatrix() const {

  // Make a 5x5 matrix that is filled with zero's alternatively we could fill it with the identity matrix;
  // Chosen the identity matrix option
  CLHEP::HepSymMatrix hepSymMatrix(5, 1);
  // Fill the matrix
  hepSymMatrix(1,1) = EMtrack_comb_Covd0d0();
  hepSymMatrix(1,2) = EMtrack_comb_Covd0z0();
  hepSymMatrix(1,3) = EMtrack_comb_Covd0phi();
  hepSymMatrix(1,4) = EMtrack_comb_Covd0eta();
  hepSymMatrix(1,5) = EMtrack_comb_Covd0P();
  hepSymMatrix(2,2) = EMtrack_comb_Covz0z0();
  hepSymMatrix(2,3) = EMtrack_comb_Covz0phi();
  hepSymMatrix(2,4) = EMtrack_comb_Covz0eta();
  hepSymMatrix(2,5) = EMtrack_comb_Covz0P();
  hepSymMatrix(3,3) = EMtrack_comb_Covphiphi();
  hepSymMatrix(3,4) = EMtrack_comb_Covphieta();
  hepSymMatrix(3,5) = EMtrack_comb_CovphiP();
  hepSymMatrix(4,4) = EMtrack_comb_Covetaeta();
  hepSymMatrix(4,5) = EMtrack_comb_CovetaP();
  hepSymMatrix(5,5) = EMtrack_comb_CovPP();
    
  return hepSymMatrix;  
}

// ====================================================================
CLHEP::HepSymMatrix EMErrorDetail::getEMTrackUncombinedErrorMatrix() const {

  // Make a 5x5 matrix that is filled with zero's alternatively we could fill it with the identity matrix;
  // Chosen the identity matrix option
  // Fill the matrix
  if (hasSiliconHits()) {
    CLHEP::HepSymMatrix hepSymMatrix(5, 1);
    // use tracks for everything but energy
    hepSymMatrix(1,1) = EMtrack_perigee_Covd0d0();
    hepSymMatrix(1,2) = EMtrack_perigee_Covd0z0();
    hepSymMatrix(1,3) = EMtrack_perigee_Covd0phi();
    hepSymMatrix(1,4) = EMtrack_perigee_Covd0theta(); // note theta
    hepSymMatrix(1,5) = 0.0;
    hepSymMatrix(2,2) = EMtrack_perigee_Covz0z0();
    hepSymMatrix(2,3) = EMtrack_perigee_Covz0phi();
    hepSymMatrix(2,4) = EMtrack_perigee_Covz0theta();
    hepSymMatrix(2,5) = 0.0;
    hepSymMatrix(3,3) = EMtrack_perigee_Covphiphi();
    hepSymMatrix(3,4) = EMtrack_perigee_Covphitheta();
    hepSymMatrix(3,5) = 0.0;
    hepSymMatrix(4,4) = EMtrack_perigee_Covthetatheta();
    hepSymMatrix(4,5) = 0.0;
    hepSymMatrix(5,5) = EMphoton_CovEclusEclus();

    const CLHEP::HepSymMatrix jacob = P5Jacobiand0z0PhiThetaE2d0z0PhiEtaE(EMtrack_perigee_theta());

    return hepSymMatrix.similarity(jacob);

  } else {
    CLHEP::HepSymMatrix hepSymMatrix(5, 1);
    // use cluster for energy and eta
    hepSymMatrix(1,1) = EMtrack_perigee_Covd0d0();
    hepSymMatrix(1,2) = EMtrack_perigee_Covd0z0();
    hepSymMatrix(1,3) = EMtrack_perigee_Covd0phi();
    hepSymMatrix(1,4) = 0.0;
    hepSymMatrix(1,5) = 0.0;
    hepSymMatrix(2,2) = EMtrack_perigee_Covz0z0();
    hepSymMatrix(2,3) = EMtrack_perigee_Covz0phi();
    hepSymMatrix(2,4) = 0.0;
    hepSymMatrix(2,5) = 0.0;
    hepSymMatrix(3,3) = EMtrack_perigee_Covphiphi();
    hepSymMatrix(3,4) = 0.0;
    hepSymMatrix(3,5) = 0.0;
    hepSymMatrix(4,4) = EMphoton_Covetaeta();
    hepSymMatrix(4,5) = EMphoton_CovetaEclus();
    hepSymMatrix(5,5) = EMphoton_CovEclusEclus();
    return hepSymMatrix;
  }

}

// ====================================================================
CLHEP::HepSymMatrix EMErrorDetail::get4x4EMTrackCombinedErrorMatrix() const {

  // E,eta,phi,M representation.
  CLHEP::HepSymMatrix hepSymMatrix(4,0);
  // Fill the matrix
  hepSymMatrix(1,1) = EMtrack_comb_CovPP();
  hepSymMatrix(1,2) = EMtrack_comb_CovetaP();
  hepSymMatrix(1,3) = EMtrack_comb_CovphiP();
  hepSymMatrix(2,2) = EMtrack_comb_Covetaeta();
  hepSymMatrix(2,3) = EMtrack_comb_Covphieta();
  hepSymMatrix(3,3) = EMtrack_comb_Covphiphi();

  return hepSymMatrix;
}

// ====================================================================
CLHEP::HepSymMatrix EMErrorDetail::get4x4EMTrackUncombinedErrorMatrix() const {

  // E,eta,phi,M representation.
  if (hasSiliconHits()) {
    CLHEP::HepSymMatrix hepSymMatrix(4, 0);
    // use tracks for everything but energy
    hepSymMatrix(1,1) = EMphoton_CovEclusEclus();

    hepSymMatrix(2,2) = EMtrack_perigee_Covthetatheta();
    hepSymMatrix(2,3) = EMtrack_perigee_Covphitheta();
    hepSymMatrix(3,3) = EMtrack_perigee_Covphiphi();

    const CLHEP::HepSymMatrix jacob = P4JacobiandEThetaPhiM2EEtaPhiM(EMtrack_perigee_theta());

    return hepSymMatrix.similarity(jacob);

  } else {
    CLHEP::HepSymMatrix hepSymMatrix(4, 0);
    // use cluster for energy and eta
    hepSymMatrix(1,1) = EMphoton_CovEclusEclus();
    hepSymMatrix(1,2) = EMphoton_CovetaEclus();

    hepSymMatrix(2,2) = EMphoton_Covetaeta();
    hepSymMatrix(3,3) = EMtrack_perigee_Covphiphi();

    return hepSymMatrix;
  }

}

// ====================================================================
CLHEP::HepSymMatrix EMErrorDetail::get4x4EMPhotonErrorMatrix() const {
  
  // E,eta,phi,M representation.
  CLHEP::HepSymMatrix hepSymMatrix(4,0);
  // Fill the matrix
  hepSymMatrix(1,1) = EMphoton_CovEclusEclus();
  hepSymMatrix(1,2) = EMphoton_CovetaEclus();
  hepSymMatrix(1,3) = EMphoton_CovphiEclus();
  hepSymMatrix(2,2) = EMphoton_Covetaeta();
  hepSymMatrix(2,3) = EMphoton_Covetaphi();
  hepSymMatrix(3,3) = EMphoton_Covphiphi();
  
  return hepSymMatrix;

}
// ======================================================================
bool EMErrorDetail::hasIntParameter(egammaParameters::ParamDef key) const {
  switch(key) {
  case egammaParameters::linkIndex:
  case egammaParameters::hasSiliconHits:               
    return true;
  default:
    return false;
  }
}    

// =======================================================================
bool EMErrorDetail::hasParameter(egammaParameters::ParamDef key) const {
  if(hasIntParameter(key)) return true;
  switch (key) {
  case egammaParameters::EMConvertedPhoton_d0:
  case egammaParameters::EMConvertedPhoton_phi0:
  case egammaParameters::EMConvertedPhoton_z0:         
  case egammaParameters::EMConvertedPhoton_theta:      
  case egammaParameters::EMConvertedPhoton_eta:      
  case egammaParameters::EMConvertedPhoton_momentum:  
  case egammaParameters::EMConvertedPhoton_Covd0d0:    
  case egammaParameters::EMConvertedPhoton_Covd0z0:    
  case egammaParameters::EMConvertedPhoton_Covd0phi:   
  case egammaParameters::EMConvertedPhoton_Covd0theta: 
  case egammaParameters::EMConvertedPhoton_Covz0z0:    
  case egammaParameters::EMConvertedPhoton_Covz0phi:   
  case egammaParameters::EMConvertedPhoton_Covz0theta:  
  case egammaParameters::EMConvertedPhoton_Covphiphi:  
  case egammaParameters::EMConvertedPhoton_Covphitheta:  
  case egammaParameters::EMConvertedPhoton_Covthetatheta:  

  case egammaParameters::EMTrack_d0:         
  case egammaParameters::EMTrack_phi0:       
  case egammaParameters::EMTrack_z0:         
  case egammaParameters::EMTrack_theta:      
  case egammaParameters::EMTrack_eta:      
  case egammaParameters::EMTrack_momentum:    
  case egammaParameters::EMTrack_Covd0d0:    
  case egammaParameters::EMTrack_Covd0z0:    
  case egammaParameters::EMTrack_Covd0phi:   
  case egammaParameters::EMTrack_Covd0theta: 
  case egammaParameters::EMTrack_Covz0z0:    
  case egammaParameters::EMTrack_Covz0phi:   
  case egammaParameters::EMTrack_Covz0theta: 
  case egammaParameters::EMTrack_Covphiphi:  
  case egammaParameters::EMTrack_Covphitheta:  
  case egammaParameters::EMTrack_Covthetatheta:  

  case egammaParameters::EMTrack_Combined_Covd0d0:    
  case egammaParameters::EMTrack_Combined_Covd0z0:    
  case egammaParameters::EMTrack_Combined_Covd0phi:   
  case egammaParameters::EMTrack_Combined_Covd0eta: 
  case egammaParameters::EMTrack_Combined_Covd0P: 
  case egammaParameters::EMTrack_Combined_Covz0z0:    
  case egammaParameters::EMTrack_Combined_Covz0phi:   
  case egammaParameters::EMTrack_Combined_Covz0eta: 
  case egammaParameters::EMTrack_Combined_Covz0P:  
  case egammaParameters::EMTrack_Combined_Covphiphi:  
  case egammaParameters::EMTrack_Combined_Covphieta:  
  case egammaParameters::EMTrack_Combined_CovphiP:  
  case egammaParameters::EMTrack_Combined_Covetaeta:  
  case egammaParameters::EMTrack_Combined_CovetaP:  
  case egammaParameters::EMTrack_Combined_CovPP:
  
  case egammaParameters::EMPhoton_eta:
  case egammaParameters::EMPhoton_phi0:       
  case egammaParameters::EMPhoton_Eclus:     

  case egammaParameters::EMPhoton_Covetaeta:  
  case egammaParameters::EMPhoton_Covetaphi:  
  case egammaParameters::EMPhoton_CovetaEclus:  
  case egammaParameters::EMPhoton_Covphiphi:  
  case egammaParameters::EMPhoton_CovphiEclus:  
  case egammaParameters::EMPhoton_CovEclusEclus:
    return true;
    // the following are depricated
  case egammaParameters::EMConvertedPhoton_Eclus:
  case egammaParameters::EMConvertedPhoton_Covd0Eclus:
  case egammaParameters::EMConvertedPhoton_Covz0Eclus:
  case egammaParameters::EMConvertedPhoton_CovphiEclus:
  case egammaParameters::EMConvertedPhoton_CovthetaEclus:
  case egammaParameters::EMConvertedPhoton_CovEclusEclus:
  case egammaParameters::EMTrack_Eclus:
  case egammaParameters::EMTrack_Covd0Eclus:
  case egammaParameters::EMTrack_Covz0Eclus:
  case egammaParameters::EMTrack_CovphiEclus:
  case egammaParameters::EMTrack_CovthetaEclus:
  case egammaParameters::EMTrack_CovEclusEclus:
    return true;
  default:
    return false;           
  }
}  


/* Get parameters of unconverted photon */
double EMErrorDetail::EMconvertedphoton_perigee_d0    ()  const {return parameter(egammaParameters::EMConvertedPhoton_d0)  ;}
double EMErrorDetail::EMconvertedphoton_perigee_phi0  ()  const {return parameter(egammaParameters::EMConvertedPhoton_phi0)  ;}
// double EMErrorDetail::EMconvertedphoton_perigee_Eclus()  const {return parameter(egammaParameters::EMConvertedPhoton_Eclus)  ;}
double EMErrorDetail::EMconvertedphoton_perigee_z0    ()  const {return parameter(egammaParameters::EMConvertedPhoton_z0)  ;}
double EMErrorDetail::EMconvertedphoton_perigee_theta ()  const {return parameter(egammaParameters::EMConvertedPhoton_theta)  ;}
double EMErrorDetail::EMconvertedphoton_perigee_eta    ()  const {return parameter(egammaParameters::EMConvertedPhoton_eta)  ;}
double EMErrorDetail::EMconvertedphoton_perigee_momentum ()  const {return parameter(egammaParameters::EMConvertedPhoton_momentum) ;}

double EMErrorDetail::EMconvertedphoton_perigee_Covd0d0         () const {return parameter(egammaParameters::EMConvertedPhoton_Covd0d0)  ;}
double EMErrorDetail::EMconvertedphoton_perigee_Covd0z0         () const {return parameter(egammaParameters::EMConvertedPhoton_Covd0z0)  ;}
double EMErrorDetail::EMconvertedphoton_perigee_Covd0phi        () const {return parameter(egammaParameters::EMConvertedPhoton_Covd0phi)  ;}
double EMErrorDetail::EMconvertedphoton_perigee_Covd0theta      () const {return parameter(egammaParameters::EMConvertedPhoton_Covd0theta)  ;}
// double EMErrorDetail::EMconvertedphoton_perigee_Covd0Eclus     () const {return parameter(egammaParameters::EMConvertedPhoton_Covd0Eclus)  ;}
double EMErrorDetail::EMconvertedphoton_perigee_Covz0z0         () const {return parameter(egammaParameters::EMConvertedPhoton_Covz0z0)  ;}
double EMErrorDetail::EMconvertedphoton_perigee_Covz0phi        () const {return parameter(egammaParameters::EMConvertedPhoton_Covz0phi)  ;}
double EMErrorDetail::EMconvertedphoton_perigee_Covz0theta      () const {return parameter(egammaParameters::EMConvertedPhoton_Covz0theta)  ;}
// double EMErrorDetail::EMconvertedphoton_perigee_Covz0Eclus     () const {return parameter(egammaParameters::EMConvertedPhoton_Covz0Eclus)  ;}
double EMErrorDetail::EMconvertedphoton_perigee_Covphiphi       () const {return parameter(egammaParameters::EMConvertedPhoton_Covphiphi)  ;}
double EMErrorDetail::EMconvertedphoton_perigee_Covphitheta     () const {return parameter(egammaParameters::EMConvertedPhoton_Covphitheta)  ;}
// double EMErrorDetail::EMconvertedphoton_perigee_CovphiEclus    () const {return parameter(egammaParameters::EMConvertedPhoton_CovphiEclus)  ;}
double EMErrorDetail::EMconvertedphoton_perigee_Covthetatheta   () const {return parameter(egammaParameters::EMConvertedPhoton_Covthetatheta)  ;}
// double EMErrorDetail::EMconvertedphoton_perigee_CovthetaEclus  () const {return parameter(egammaParameters::EMConvertedPhoton_CovthetaEclus)  ;}
// double EMErrorDetail::EMconvertedphoton_perigee_CovEclusEclus () const {return parameter(egammaParameters::EMConvertedPhoton_CovEclusEclus)  ;}

/* Set parameters of unconverted photons */
void EMErrorDetail::EMconvertedphoton_perigee_d0    (double x)  {set_parameter(egammaParameters::EMConvertedPhoton_d0, x, true)  ;}
void EMErrorDetail::EMconvertedphoton_perigee_phi0  (double x)  {set_parameter(egammaParameters::EMConvertedPhoton_phi0, x, true)  ;}
// void EMErrorDetail::EMconvertedphoton_perigee_Eclus (double x)  {set_parameter(egammaParameters::EMConvertedPhoton_Eclus, x, true)  ;}
void EMErrorDetail::EMconvertedphoton_perigee_z0    (double x)  {set_parameter(egammaParameters::EMConvertedPhoton_z0, x, true)  ;}
void EMErrorDetail::EMconvertedphoton_perigee_theta (double x)  {set_parameter(egammaParameters::EMConvertedPhoton_theta, x, true)  ;}
void EMErrorDetail::EMconvertedphoton_perigee_eta    (double x)  {set_parameter(egammaParameters::EMConvertedPhoton_eta, x, true)  ;}
void EMErrorDetail::EMconvertedphoton_perigee_momentum (double x)  {set_parameter(egammaParameters::EMConvertedPhoton_momentum, x, true)  ;}

void EMErrorDetail::EMconvertedphoton_perigee_Covd0d0         (double x) {set_parameter(egammaParameters::EMConvertedPhoton_Covd0d0, x, true)  ;}
void EMErrorDetail::EMconvertedphoton_perigee_Covd0z0         (double x) {set_parameter(egammaParameters::EMConvertedPhoton_Covd0z0, x, true)  ;}
void EMErrorDetail::EMconvertedphoton_perigee_Covd0phi        (double x) {set_parameter(egammaParameters::EMConvertedPhoton_Covd0phi, x, true)  ;}
void EMErrorDetail::EMconvertedphoton_perigee_Covd0theta      (double x) {set_parameter(egammaParameters::EMConvertedPhoton_Covd0theta, x, true)  ;}
// void EMErrorDetail::EMconvertedphoton_perigee_Covd0Eclus     (double x) {set_parameter(egammaParameters::EMConvertedPhoton_Covd0Eclus, x, true)  ;}
void EMErrorDetail::EMconvertedphoton_perigee_Covz0z0         (double x) {set_parameter(egammaParameters::EMConvertedPhoton_Covz0z0, x, true)  ;}
void EMErrorDetail::EMconvertedphoton_perigee_Covz0phi        (double x) {set_parameter(egammaParameters::EMConvertedPhoton_Covz0phi, x, true)  ;}
void EMErrorDetail::EMconvertedphoton_perigee_Covz0theta      (double x) {set_parameter(egammaParameters::EMConvertedPhoton_Covz0theta, x, true)  ;}
// void EMErrorDetail::EMconvertedphoton_perigee_Covz0Eclus     (double x) {set_parameter(egammaParameters::EMConvertedPhoton_Covz0Eclus, x, true)  ;}
void EMErrorDetail::EMconvertedphoton_perigee_Covphiphi       (double x) {set_parameter(egammaParameters::EMConvertedPhoton_Covphiphi, x, true)  ;}
void EMErrorDetail::EMconvertedphoton_perigee_Covphitheta     (double x) {set_parameter(egammaParameters::EMConvertedPhoton_Covphitheta, x, true)  ;}
// void EMErrorDetail::EMconvertedphoton_perigee_CovphiEclus    (double x) {set_parameter(egammaParameters::EMConvertedPhoton_CovphiEclus, x, true)  ;}
void EMErrorDetail::EMconvertedphoton_perigee_Covthetatheta   (double x) {set_parameter(egammaParameters::EMConvertedPhoton_Covthetatheta, x, true)  ;}
// void EMErrorDetail::EMconvertedphoton_perigee_CovthetaEclus  (double x) {set_parameter(egammaParameters::EMConvertedPhoton_CovthetaEclus, x, true)  ;}
// void EMErrorDetail::EMconvertedphoton_perigee_CovEclusEclus (double x) {set_parameter(egammaParameters::EMConvertedPhoton_CovEclusEclus, x, true)  ;}


/* Get parameters of tracks */
double EMErrorDetail::EMtrack_perigee_d0    ()  const {return parameter(egammaParameters::EMTrack_d0)  ;}
double EMErrorDetail::EMtrack_perigee_phi0  ()  const {return parameter(egammaParameters::EMTrack_phi0)  ;}
// double EMErrorDetail::EMtrack_perigee_Eclus()  const {return parameter(egammaParameters::EMTrack_Eclus)  ;}
double EMErrorDetail::EMtrack_perigee_z0    ()  const {return parameter(egammaParameters::EMTrack_z0)  ;}
double EMErrorDetail::EMtrack_perigee_theta ()  const {return parameter(egammaParameters::EMTrack_theta)  ;}
double EMErrorDetail::EMtrack_perigee_eta    ()  const {return parameter(egammaParameters::EMTrack_eta)  ;}
double EMErrorDetail::EMtrack_perigee_momentum ()  const {return parameter(egammaParameters::EMTrack_momentum)  ;}

double EMErrorDetail::EMtrack_perigee_Covd0d0         () const {return parameter(egammaParameters::EMTrack_Covd0d0)  ;}
double EMErrorDetail::EMtrack_perigee_Covd0z0         () const {return parameter(egammaParameters::EMTrack_Covd0z0)  ;}
double EMErrorDetail::EMtrack_perigee_Covd0phi        () const {return parameter(egammaParameters::EMTrack_Covd0phi)  ;}
double EMErrorDetail::EMtrack_perigee_Covd0theta      () const {return parameter(egammaParameters::EMTrack_Covd0theta)  ;}
// double EMErrorDetail::EMtrack_perigee_Covd0Eclus     () const {return parameter(egammaParameters::EMTrack_Covd0Eclus)  ;}
double EMErrorDetail::EMtrack_perigee_Covz0z0         () const {return parameter(egammaParameters::EMTrack_Covz0z0)  ;}
double EMErrorDetail::EMtrack_perigee_Covz0phi        () const {return parameter(egammaParameters::EMTrack_Covz0phi)  ;}
double EMErrorDetail::EMtrack_perigee_Covz0theta      () const {return parameter(egammaParameters::EMTrack_Covz0theta)  ;}
// double EMErrorDetail::EMtrack_perigee_Covz0Eclus     () const {return parameter(egammaParameters::EMTrack_Covz0Eclus)  ;}
double EMErrorDetail::EMtrack_perigee_Covphiphi       () const {return parameter(egammaParameters::EMTrack_Covphiphi)  ;}
double EMErrorDetail::EMtrack_perigee_Covphitheta     () const {return parameter(egammaParameters::EMTrack_Covphitheta)  ;}
// double EMErrorDetail::EMtrack_perigee_CovphiEclus    () const {return parameter(egammaParameters::EMTrack_CovphiEclus)  ;}
double EMErrorDetail::EMtrack_perigee_Covthetatheta   () const {return parameter(egammaParameters::EMTrack_Covthetatheta)  ;}
// double EMErrorDetail::EMtrack_perigee_CovthetaEclus  () const {return parameter(egammaParameters::EMTrack_CovthetaEclus)  ;}
// double EMErrorDetail::EMtrack_perigee_CovEclusEclus () const {return parameter(egammaParameters::EMTrack_CovEclusEclus)  ;}

/* Get parameters of tracks from the combined method (track and cluster information combined)*/
double EMErrorDetail::EMtrack_comb_Covd0d0         () const {return parameter(egammaParameters::EMTrack_Combined_Covd0d0)  ;}
double EMErrorDetail::EMtrack_comb_Covd0z0         () const {return parameter(egammaParameters::EMTrack_Combined_Covd0z0)  ;}
double EMErrorDetail::EMtrack_comb_Covd0phi        () const {return parameter(egammaParameters::EMTrack_Combined_Covd0phi)  ;}
double EMErrorDetail::EMtrack_comb_Covd0eta      () const {return parameter(egammaParameters::EMTrack_Combined_Covd0eta)  ;}
double EMErrorDetail::EMtrack_comb_Covd0P     () const {return parameter(egammaParameters::EMTrack_Combined_Covd0P)  ;}
double EMErrorDetail::EMtrack_comb_Covz0z0         () const {return parameter(egammaParameters::EMTrack_Combined_Covz0z0)  ;}
double EMErrorDetail::EMtrack_comb_Covz0phi        () const {return parameter(egammaParameters::EMTrack_Combined_Covz0phi)  ;}
double EMErrorDetail::EMtrack_comb_Covz0eta      () const {return parameter(egammaParameters::EMTrack_Combined_Covz0eta)  ;}
double EMErrorDetail::EMtrack_comb_Covz0P     () const {return parameter(egammaParameters::EMTrack_Combined_Covz0P)  ;}
double EMErrorDetail::EMtrack_comb_Covphiphi       () const {return parameter(egammaParameters::EMTrack_Combined_Covphiphi)  ;}
double EMErrorDetail::EMtrack_comb_Covphieta     () const {return parameter(egammaParameters::EMTrack_Combined_Covphieta)  ;}
double EMErrorDetail::EMtrack_comb_CovphiP    () const {return parameter(egammaParameters::EMTrack_Combined_CovphiP)  ;}
double EMErrorDetail::EMtrack_comb_Covetaeta   () const {return parameter(egammaParameters::EMTrack_Combined_Covetaeta)  ;}
double EMErrorDetail::EMtrack_comb_CovetaP  () const {return parameter(egammaParameters::EMTrack_Combined_CovetaP)  ;}
double EMErrorDetail::EMtrack_comb_CovPP    () const {return parameter(egammaParameters::EMTrack_Combined_CovPP)  ;}



/* Set parameters of tracks */
void EMErrorDetail::EMtrack_perigee_d0    (double x)  {set_parameter(egammaParameters::EMTrack_d0, x, true)  ;}
void EMErrorDetail::EMtrack_perigee_phi0  (double x)  {set_parameter(egammaParameters::EMTrack_phi0, x, true)  ;}
// void EMErrorDetail::EMtrack_perigee_Eclus (double x)  {set_parameter(egammaParameters::EMTrack_Eclus, x, true)  ;}
void EMErrorDetail::EMtrack_perigee_z0    (double x)  {set_parameter(egammaParameters::EMTrack_z0, x, true)  ;}
void EMErrorDetail::EMtrack_perigee_theta (double x)  {set_parameter(egammaParameters::EMTrack_theta, x, true)  ;}
void EMErrorDetail::EMtrack_perigee_eta    (double x)  {set_parameter(egammaParameters::EMTrack_eta, x, true)  ;}
void EMErrorDetail::EMtrack_perigee_momentum (double x)  {set_parameter(egammaParameters::EMTrack_momentum, x, true)  ;}

void EMErrorDetail::EMtrack_perigee_Covd0d0        (double x) {set_parameter(egammaParameters::EMTrack_Covd0d0, x, true)  ;}
void EMErrorDetail::EMtrack_perigee_Covd0z0        (double x) {set_parameter(egammaParameters::EMTrack_Covd0z0, x, true)  ;}
void EMErrorDetail::EMtrack_perigee_Covd0phi       (double x) {set_parameter(egammaParameters::EMTrack_Covd0phi, x, true)  ;}
void EMErrorDetail::EMtrack_perigee_Covd0theta     (double x) {set_parameter(egammaParameters::EMTrack_Covd0theta, x, true)  ;}
// void EMErrorDetail::EMtrack_perigee_Covd0Eclus     (double x) {set_parameter(egammaParameters::EMTrack_Covd0Eclus, x, true)  ;}
void EMErrorDetail::EMtrack_perigee_Covz0z0        (double x) {set_parameter(egammaParameters::EMTrack_Covz0z0, x, true)  ;}
void EMErrorDetail::EMtrack_perigee_Covz0phi       (double x) {set_parameter(egammaParameters::EMTrack_Covz0phi, x, true)  ;}
void EMErrorDetail::EMtrack_perigee_Covz0theta     (double x) {set_parameter(egammaParameters::EMTrack_Covz0theta, x, true)  ;}
// void EMErrorDetail::EMtrack_perigee_Covz0Eclus     (double x) {set_parameter(egammaParameters::EMTrack_Covz0Eclus, x, true)  ;}
void EMErrorDetail::EMtrack_perigee_Covphiphi      (double x) {set_parameter(egammaParameters::EMTrack_Covphiphi, x, true)  ;}
void EMErrorDetail::EMtrack_perigee_Covphitheta    (double x) {set_parameter(egammaParameters::EMTrack_Covphitheta, x, true)  ;}
// void EMErrorDetail::EMtrack_perigee_CovphiEclus    (double x) {set_parameter(egammaParameters::EMTrack_CovphiEclus, x, true)  ;}
void EMErrorDetail::EMtrack_perigee_Covthetatheta  (double x) {set_parameter(egammaParameters::EMTrack_Covthetatheta, x, true)  ;}
// void EMErrorDetail::EMtrack_perigee_CovthetaEclus  (double x) {set_parameter(egammaParameters::EMTrack_CovthetaEclus, x, true)  ;}
// void EMErrorDetail::EMtrack_perigee_CovEclusEclus  (double x) {set_parameter(egammaParameters::EMTrack_CovEclusEclus, x, true)  ;}


void EMErrorDetail::EMtrack_comb_Covd0d0    (double x) {set_parameter(egammaParameters::EMTrack_Combined_Covd0d0, x, true)  ;}
void EMErrorDetail::EMtrack_comb_Covd0z0    (double x) {set_parameter(egammaParameters::EMTrack_Combined_Covd0z0, x, true)  ;}
void EMErrorDetail::EMtrack_comb_Covd0phi   (double x) {set_parameter(egammaParameters::EMTrack_Combined_Covd0phi, x, true)  ;}
void EMErrorDetail::EMtrack_comb_Covd0eta   (double x) {set_parameter(egammaParameters::EMTrack_Combined_Covd0eta, x, true)  ;}
void EMErrorDetail::EMtrack_comb_Covd0P     (double x) {set_parameter(egammaParameters::EMTrack_Combined_Covd0P, x, true)  ;}
void EMErrorDetail::EMtrack_comb_Covz0z0    (double x) {set_parameter(egammaParameters::EMTrack_Combined_Covz0z0, x, true)  ;}
void EMErrorDetail::EMtrack_comb_Covz0phi   (double x) {set_parameter(egammaParameters::EMTrack_Combined_Covz0phi, x, true)  ;}
void EMErrorDetail::EMtrack_comb_Covz0eta   (double x) {set_parameter(egammaParameters::EMTrack_Combined_Covz0eta, x, true)  ;}
void EMErrorDetail::EMtrack_comb_Covz0P     (double x) {set_parameter(egammaParameters::EMTrack_Combined_Covz0P, x, true)  ;}
void EMErrorDetail::EMtrack_comb_Covphiphi  (double x) {set_parameter(egammaParameters::EMTrack_Combined_Covphiphi, x, true)  ;}
void EMErrorDetail::EMtrack_comb_Covphieta  (double x) {set_parameter(egammaParameters::EMTrack_Combined_Covphieta, x, true)  ;}
void EMErrorDetail::EMtrack_comb_CovphiP    (double x) {set_parameter(egammaParameters::EMTrack_Combined_CovphiP, x, true)  ;}
void EMErrorDetail::EMtrack_comb_Covetaeta  (double x) {set_parameter(egammaParameters::EMTrack_Combined_Covetaeta, x, true)  ;}
void EMErrorDetail::EMtrack_comb_CovetaP    (double x) {set_parameter(egammaParameters::EMTrack_Combined_CovetaP, x, true)  ;}
void EMErrorDetail::EMtrack_comb_CovPP      (double x) {set_parameter(egammaParameters::EMTrack_Combined_CovPP, x, true)  ;}

/* Get parameters of photons */
double EMErrorDetail::EMphoton_eta ()  const {return parameter(egammaParameters::EMPhoton_eta)  ;}
double EMErrorDetail::EMphoton_phi0  ()  const {return parameter(egammaParameters::EMPhoton_phi0)  ;}
double EMErrorDetail::EMphoton_Eclus()  const {return parameter(egammaParameters::EMPhoton_Eclus)  ;}

double EMErrorDetail::EMphoton_Covetaeta   () const {return parameter(egammaParameters::EMPhoton_Covetaeta)  ;}
double EMErrorDetail::EMphoton_Covetaphi     () const {return parameter(egammaParameters::EMPhoton_Covetaphi)  ;}
double EMErrorDetail::EMphoton_CovetaEclus     () const {return parameter(egammaParameters::EMPhoton_CovetaEclus)  ;}
double EMErrorDetail::EMphoton_Covphiphi       () const {return parameter(egammaParameters::EMPhoton_Covphiphi)  ;}
double EMErrorDetail::EMphoton_CovphiEclus     () const {return parameter(egammaParameters::EMPhoton_CovphiEclus)  ;}
double EMErrorDetail::EMphoton_CovEclusEclus () const {return parameter(egammaParameters::EMPhoton_CovEclusEclus)  ;}

/* Set parameters of photons */
void EMErrorDetail::EMphoton_eta (double x)  {set_parameter(egammaParameters::EMPhoton_eta, x, true)  ;}
void EMErrorDetail::EMphoton_phi0  (double x)  {set_parameter(egammaParameters::EMPhoton_phi0, x, true)  ;}
void EMErrorDetail::EMphoton_Eclus (double x)  {set_parameter(egammaParameters::EMPhoton_Eclus, x, true)  ;}

void EMErrorDetail::EMphoton_Covetaeta   (double x) {set_parameter(egammaParameters::EMPhoton_Covetaeta, x, true)  ;}
void EMErrorDetail::EMphoton_Covetaphi   (double x) {set_parameter(egammaParameters::EMPhoton_Covetaphi, x, true)  ;}
void EMErrorDetail::EMphoton_CovetaEclus   (double x) {set_parameter(egammaParameters::EMPhoton_CovetaEclus, x, true)  ;}
void EMErrorDetail::EMphoton_Covphiphi       (double x) {set_parameter(egammaParameters::EMPhoton_Covphiphi, x, true)  ;}
void EMErrorDetail::EMphoton_CovphiEclus    (double x) {set_parameter(egammaParameters::EMPhoton_CovphiEclus, x, true)  ;}
void EMErrorDetail::EMphoton_CovEclusEclus    (double x) {set_parameter(egammaParameters::EMPhoton_CovEclusEclus, x, true)  ;}

int EMErrorDetail::linkIndex ()  const {return intParameter(egammaParameters::linkIndex)  ;}
void EMErrorDetail::set_linkIndex (int x)  {set_parameterInt(egammaParameters::linkIndex, x, true)  ;}

int EMErrorDetail::hasSiliconHits()  const {return intParameter(egammaParameters::hasSiliconHits)  ;}
void EMErrorDetail::set_hasSiliconHits (int x)  {set_parameterInt(egammaParameters::hasSiliconHits, x, true)  ;}


CLHEP::HepSymMatrix EMErrorDetail::P5Jacobiand0z0PhiThetaE2d0z0PhiEtaE(const double theta) const
{
  CLHEP::HepSymMatrix m(5,1);

  m[3][3] = (-1./sin(theta));     // deta/dtheta
  return m;
}

CLHEP::HepSymMatrix EMErrorDetail::P4JacobiandEThetaPhiM2EEtaPhiM(const double theta) const
{
  CLHEP::HepSymMatrix m(4,1);

  m[1][1] = (-1./sin(theta));     // deta/dtheta
  return m;
}

SG_ADD_BASE (EMErrorDetail, egDetail);

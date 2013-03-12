#include "egammaAnalysisUtils/IsEMForwardDefs.h"

#include <TMath.h>

// 2011 optimised cuts
// Define cuts for EMEC and FCAL - [4 bins in pile-up][for the 6 var's]
const unsigned int nvtx_bins_2011 = 4;
const double cuts_nvtx_2011[nvtx_bins_2011+1] = {-0.5,3.5,6.5,10.5,1e200};
const unsigned int nvariables     = 6;

// 2^0: <pho_{E}^{1}>: not used
// 2^1: <lambda^{2}>; 2^2: lateral; 2^3: longitudinal;
// 2^4: f_{max}; 2^5: <R^{2}>; 2^6: lambda_{Center}
// 2^7 - out of eta range
// 2^8 - out of pVtx range; should not happen

const double Cuts_EMEC_Loose_2011[nvtx_bins_2011][nvariables] =
  { { 4000,.60,.49,-.22,3500,255},
    { 4200,.64,.48,-.22,3500,255},
    { 4200,.69,.48,-.18,3900,260},
    { 4500,.69,.55,-.22,3900,255} };
const double Cuts_FCAL_Loose_2011[nvtx_bins_2011][nvariables] = 
  { { 6700,.38,.38,-.28, 900,250},
    { 7900,.40,.49,-.28,1100,250},
    { 8900,.42,.59,-.28,1400,246},
    {10000,.63,.73,-.23,1900,252} };

const double Cuts_EMEC_Medium_2011[nvtx_bins_2011][nvariables] =
  { { 3600,.54,.25,-.26,2600,255},
    { 4200,.58,.26,-.25,2700,255},
    { 4000,.62,.27,-.24,3000,250},
    { 4500,.64,.29,-.23,3300,255} };
const double Cuts_FCAL_Medium_2011[nvtx_bins_2011][nvariables] =
  { { 4300,.38,.28,-.30, 900,244},
    { 5500,.40,.33,-.29, 950,246},
    { 6600,.42,.40,-.29,1050,246},
    { 9700,.45,.52,-.26,1200,250} };

const double Cuts_EMEC_Tight_2011[nvtx_bins_2011][nvariables] = 
  { { 3000,.48,.25,-.26,2200,255},
    { 3000,.54,.25,-.41,2300,250},
    { 3200,.55,.27,-.26,2600,250},
    { 2800,.64,.24,-.39,3000,250} };
const double Cuts_FCAL_Tight_2011[nvtx_bins_2011][nvariables] = 
  { { 3000,.38,.22,-.30, 850,243},
    { 4000,.40,.27,-.30, 950,244},
    { 4500,.42,.31,-.29,1000,246},
    { 7500,.42,.41,-.28,1100,250} };

bool isForward_Loose(int vxp_n, float el_cl_eta,
		     float el_secondlambda,float el_lateral,float el_longitudinal,
		     float el_cellmaxfrac, float el_secondR,float el_centerlambda,
		     egammaForwardMenu::egForwardMenu menu)
{
  return (Forward_IsEM(vxp_n, el_cl_eta,
		       el_secondlambda, el_lateral, el_longitudinal,
		       el_cellmaxfrac, el_secondR, el_centerlambda,
		       egammaForwardMenu::Loose, menu) == 0);
}

bool isForward_Medium(int vxp_n, float el_cl_eta,
		      float el_secondlambda,float el_lateral,float el_longitudinal,
		      float el_cellmaxfrac, float el_secondR,float el_centerlambda,
		      egammaForwardMenu::egForwardMenu menu)
{
  return (Forward_IsEM(vxp_n, el_cl_eta,
		       el_secondlambda, el_lateral, el_longitudinal,
		       el_cellmaxfrac, el_secondR, el_centerlambda,
		       egammaForwardMenu::Medium, menu) == 0);
}

bool isForward_Tight(int vxp_n, float el_cl_eta,
		     float el_secondlambda,float el_lateral,float el_longitudinal,
		     float el_cellmaxfrac, float el_secondR,float el_centerlambda,
		     egammaForwardMenu::egForwardMenu menu)
{
  return (Forward_IsEM(vxp_n, el_cl_eta,
		       el_secondlambda, el_lateral, el_longitudinal,
		       el_cellmaxfrac, el_secondR, el_centerlambda,
		       egammaForwardMenu::Tight, menu) == 0);
}

unsigned int Forward_IsEM(int vxp_n, float el_cl_eta,
			  float el_secondlambda,float el_lateral,float el_longitudinal,
			  float el_cellmaxfrac, float el_secondR,float el_centerlambda,
			  egammaForwardMenu::egForwardCut cut,
			  egammaForwardMenu::egForwardMenu menu)
{
  // put variables in array to allow access via index
  double variables[nvariables] = {el_secondlambda,el_lateral,el_longitudinal,
				  -el_cellmaxfrac,el_secondR,el_centerlambda};

  int emec_fcal_bin = getFwdEtaBin(el_cl_eta, menu);
  if (emec_fcal_bin < 0)
    return 128;

  int nvtx_bin = getNvtxBin(vxp_n, menu);
  if (nvtx_bin < 0)
    return 256;

  if (menu == egammaForwardMenu::eg2011) {
    if (emec_fcal_bin == 0 && cut == egammaForwardMenu::Loose) {
      return Forward_ID(Cuts_EMEC_Loose_2011[nvtx_bin], variables);
    } else if (emec_fcal_bin == 1 && cut == egammaForwardMenu::Loose) {
      return Forward_ID(Cuts_FCAL_Loose_2011[nvtx_bin], variables);
      
    } else if (emec_fcal_bin == 0 && cut == egammaForwardMenu::Medium) {
      return Forward_ID(Cuts_EMEC_Medium_2011[nvtx_bin], variables);
    } else if (emec_fcal_bin == 1 && cut == egammaForwardMenu::Medium) {
      return Forward_ID(Cuts_FCAL_Medium_2011[nvtx_bin], variables);

    } else if (emec_fcal_bin == 0 && cut == egammaForwardMenu::Tight) {
      return Forward_ID(Cuts_EMEC_Tight_2011[nvtx_bin], variables);
    } else if (emec_fcal_bin == 1 && cut == egammaForwardMenu::Tight) {
      return Forward_ID(Cuts_FCAL_Tight_2011[nvtx_bin], variables);
    }
    
  }

  // non-2011 period selected or other strange configuration
  return 512;
}

int getNvtxBin(int vxp_n,
	       egammaForwardMenu::egForwardMenu menu)
{
  // get nvertex bin number, non-2011 defaults right now to bin number=0
  if (menu == egammaForwardMenu::eg2011) {
    for (unsigned int i=0; i<nvtx_bins_2011; i++){
      if ( vxp_n>cuts_nvtx_2011[i] && vxp_n<cuts_nvtx_2011[i+1] ) {
        return i;
      }
    }
    return -1;
  } else {
    return 0;
  }
}


int getFwdEtaBin(float el_cl_eta,
		 egammaForwardMenu::egForwardMenu menu)
{
  // Forward eta bin choice
  // coded as year dependendt, but actually it is not (yet)

  el_cl_eta = TMath::Abs(el_cl_eta);

  if (menu == egammaForwardMenu::eg2011) {
    if ( el_cl_eta>=2.5 && el_cl_eta<3.2 ) {
      // Electron in EMEC
      return 0;
    } else if ( el_cl_eta>=3.2 && el_cl_eta<4.9 ) {
      // Electron in FCAL
      return 1;
    }
  } else {
    if ( el_cl_eta>=2.5 && el_cl_eta<3.2 ) {
      // Electron in EMEC
      return 0;
    } else if ( el_cl_eta>=3.2 && el_cl_eta<4.9 ) {
      // Electron in FCAL
      return 1;
    }
  }
  return -1;
}

unsigned int Forward_ID (const double *cuts, const double *variables)
{
  // Returns IsEM style bit mask for the cuts defined by the various variables
  // 2^1: First variable; 2^2: Second variable; ...
  // bit = 1 for failed cut

  unsigned int BinOut=0;
  for (unsigned int j=0; j<nvariables; j++) {
    if ( variables[j] > cuts[j] ) {
      BinOut |= 0x0001 << (j+1);
    }
  }
  return BinOut;
}



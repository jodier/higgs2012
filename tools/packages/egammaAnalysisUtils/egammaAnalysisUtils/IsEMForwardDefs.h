#ifndef ISEMFORWARDDEFS_H
#define ISEMFORWARDDEFS_H

// Forward ID with pile-up dependent cuts
// Currently available for 2011 data, optimized on the full 2011 data set
// loose, medium and tight operating points

// Written by C. Handel, University of Mainz, May 2012
// Interface modifications by Jan Kretzschmar
// Contact: Frank.Ellinghaus@uni.mainz.de 

// inputs: 
//    * vxp_n = number of reconstructed primary vertices with at least 3 tracks
//    * el_cl_eta = forward electron eta
//    * fwd cluster shower shapes: el_secondlambda, el_lateral, el_longitudinal,
//                                 el_cellmaxfrac,  el_secondR, el_centerlambda
// example usage:
// boolean decision
// bool isloose = isForward_Loose(vxp_n, el_cl_eta,
//                                el_secondlambda, el_lateral, el_longitudinal,
//		                  el_cellmaxfrac,  el_secondR, el_centerlambda,
//		                  egammaForwardMenu::eg2011);
//
// bit mask with indivitual cuts failing marked as bit=1
// unsigned int mask = Forward_IsEM(vxp_n, el_cl_eta,
//                                  el_secondlambda, el_lateral, el_longitudinal,
//		                    el_cellmaxfrac,  el_secondR, el_centerlambda,
//                                  egammaForwardMenu::Loose,
//		                    egammaForwardMenu::eg2011);


//enum for menu decision 
namespace egammaForwardMenu {
  enum egForwardMenu {
    eg2011,
    eg2012
  };

  enum egForwardCut { Loose, Medium, Tight };
}

unsigned int Forward_IsEM(int vxp_n, float el_cl_eta,
			  float el_secondlambda,float el_lateral,float el_longitudinal,
			  float el_cellmaxfrac, float el_secondR,float el_centerlambda,
			  egammaForwardMenu::egForwardCut cut,
			  egammaForwardMenu::egForwardMenu menu = egammaForwardMenu::eg2011);

bool isForward_Loose(int vxp_n, float el_cl_eta,
		     float el_secondlambda,float el_lateral,float el_longitudinal,
		     float el_cellmaxfrac, float el_secondR,float el_centerlambda,
		     egammaForwardMenu::egForwardMenu menu = egammaForwardMenu::eg2011);

bool isForward_Medium(int vxp_n, float el_cl_eta,
		      float el_secondlambda,float el_lateral,float el_longitudinal,
		      float el_cellmaxfrac, float el_secondR,float el_centerlambda,
		      egammaForwardMenu::egForwardMenu menu = egammaForwardMenu::eg2011);

bool isForward_Tight(int vxp_n, float el_cl_eta,
		     float el_secondlambda,float el_lateral,float el_longitudinal,
		     float el_cellmaxfrac, float el_secondR,float el_centerlambda,
		     egammaForwardMenu::egForwardMenu menu = egammaForwardMenu::eg2011);


//-------------------------------------------------------------------------------------------------------

// Helper Fuctions
unsigned int Forward_ID(const double *cuts, const double *variables);

int getNvtxBin(int vxp_n,
	       egammaForwardMenu::egForwardMenu menu = egammaForwardMenu::eg2011);
int getFwdEtaBin(float el_cl_eta,
		 egammaForwardMenu::egForwardMenu menu = egammaForwardMenu::eg2011);

//----------------------------------------------------------------------------------------
#endif

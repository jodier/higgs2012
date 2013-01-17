/*-------------------------------------------------------------------------*/

#include "../include/core.h"

#ifdef __YEAR2011
  #include <HiggsZZ4lUtils/IsEMPlusPlusH4lDefs.h>
#endif

#ifdef __YEAR2012
  #include <egammaAnalysisUtils/MultiLeptonDefs_HCP2012.h>
#endif

/*-------------------------------------------------------------------------*/

Bool_t TLeptonAnalysis::el_isEMOk_at(Int_t index)
{
#ifdef __YEAR2011
	float eta_s2 = el_etas2->at(index);

	float Et_cl = el_cl_E->at(index) / coshf(eta_s2);

	return isLoosePlusPlusH4l(
		eta_s2,
		Et_cl,
		el_Ethad->at(index) / Et_cl,
		el_Ethad1->at(index) / Et_cl,
		el_reta->at(index),
		el_weta2->at(index),
		el_f1->at(index),
		el_wstot->at(index),
		(el_emaxs1->at(index) - el_Emax2->at(index)) / (el_emaxs1->at(index) + el_Emax2->at(index)),
		el_deltaeta1->at(index),
		el_nSiHits->at(index),
		el_nPixelOutliers->at(index) + el_nSCTOutliers->at(index),
		el_nPixHits->at(index),
		el_nPixelOutliers->at(index),
		false,
		false
	);
#endif
#ifdef __YEAR2012

/*	double Et_cl            = el_cl_E->at(index) / cosh(el_etas2->at(index));
	double etas2            = el_etas2->at(index);
	double rHad             = el_Ethad->at(index) / Et_cl;
	double rHad1            = el_Ethad1->at(index) / Et_cl;
	double Reta             = el_reta->at(index);
	double w2               = el_weta2->at(index);
	double f1               = el_f1->at(index);
	double f3               = el_f3->at(index);
	double wstot            = el_wstot->at(index);
	double DEmaxs1          = (el_emaxs1->at(index) - el_Emax2->at(index)) / (el_emaxs1->at(index) + el_Emax2->at(index));
	double deltaEta         = el_deltaeta1->at(index);
	double deltaPhiRescaled = el_deltaphiRescaled->at(index);
	int    nSi              = el_nSiHits->at(index);
	int    nSiDeadSensors   = el_nSCTDeadSensors->at(index) + el_nPixelDeadSensors->at(index);
	int    nPix             = el_nPixHits->at(index);
	int    nPixDeadSensors  = el_nPixelDeadSensors->at(index);
	int    nTRThigh         = el_nTRTHighTHits->at(index);
	int    nTRThighOutliers = el_nTRTHighTOutliers->at(index);
	int    nTRT             = el_nTRTHits->at(index);  
	int    nTRTOutliers     = el_nTRTOutliers->at(index); 
	bool   expectBlayer     = el_expectBLayerHit->at(index); 
	int    nBlayerHits      = el_nBLHits->at(index);

	int nTRTTotal     = nTRT     + nTRTOutliers    ;
	int nTRTTotalHigh = nTRThigh + nTRThighOutliers;

	double rTRT = nTRTTotal > 0 ? double(nTRTTotalHigh) / double(nTRTTotal) : 0.0;

	double dpOverp = 0.0;

	for(unsigned int i = 0; i < el_refittedTrack_LMqoverp->at(index).size(); i++)
	{
		if(el_refittedTrack_author->at(index).at(i) == 4)
		{
			dpOverp = 1.0 - el_trackqoverp->at(index) / el_refittedTrack_LMqoverp->at(index).at(i);
		}
	}

	return passMultiLepton(
		etas2, Et_cl,
		rHad, rHad1, Reta, w2,
		f1, f3, wstot, DEmaxs1,
		deltaEta, nSi, nSiDeadSensors, nPix,
		nPixDeadSensors, deltaPhiRescaled, dpOverp,
		rTRT, nTRTTotal, nBlayerHits, expectBlayer
	);
*/

	double eta              = el_etas2->at(index);
	double Et               = el_cl_E->at(index) / coshf(eta);
	double f3               = el_f3->at(index);
	double rHad             = el_Ethad->at(index) / Et;
	double rHad1            = el_Ethad1->at(index) / Et;
	double Reta             = el_reta->at(index);
	double w2               = el_weta2->at(index);
	double f1               = el_f1->at(index);
	double DEmaxs1          = (el_emaxs1->at(index) + el_Emax2->at(index) == 0) ? 0 : (el_emaxs1->at(index) - el_Emax2->at(index)) / (el_emaxs1->at(index) + el_Emax2->at(index));
	double deltaEta         = el_deltaeta1->at(index);
	double d0		= el_trackd0pv->at(index);
	double TRratio		= el_TRTHighTOutliersRatio->at(index);
	double d0sigma		= el_tracksigd0pv->at(index);
	double rphi		= el_rphi->at(index);
	double ws3		= el_ws3->at(index);
	double deltaPoverP	= 0.0;
	for(unsigned int i = 0; i < el_refittedTrack_LMqoverp->at(index).size(); i++)
	{
		if(el_refittedTrack_author->at(index).at(i) == 4)
		{
			deltaPoverP = 1.0 - el_trackqoverp->at(index) / el_refittedTrack_LMqoverp->at(index).at(i);
		}
	}
	double deltaphires	= el_deltaphiRescaled->at(index);
	int    nSi              = el_nSiHits->at(index);

	int    nPix             = el_nPixHits->at(index);
	int    nPixDeadSensors  = el_nPixelDeadSensors->at(index);
	int    nSiDeadSensors   = el_nSCTDeadSensors->at(index) + el_nPixelDeadSensors->at(index);
	int nBlayer		= el_nBLHits->at(index);
	int nBlayerOutliers	= el_nBLayerOutliers->at(index);
	bool expectBlayer	= el_expectHitInBLayer->at(index);
	int convBit		= el_isEM->at(index)&(0x1 << egammaPID::ConversionMatch_Electron);
	double nPV2 = 0;
	for(Int_t i = 0; i < Int_t(vxp_nTracks->size()); i++)
	{
		if(vxp_nTracks->at(i) >= 2) {
			nPV2++;
		}

	}

	if(( expectBlayer && ((nBlayer + nBlayerOutliers) < 1) ) || ( (nPixDeadSensors + nPix) < 2 ))
		return 0;

	else
		return m_ElectronLikelihoodTool->passLikelihood(LikeEnum::Loose_BL_Pix,
			    eta, Et, f3, rHad, rHad1,
			    Reta, w2, f1, DEmaxs1,
			    deltaEta, d0, TRratio,
			    d0sigma, rphi, ws3,
			    deltaPoverP, deltaphires,
			    nSi, nSiDeadSensors, nPix, nPixDeadSensors,
			    nBlayer, nBlayerOutliers, expectBlayer,
			     convBit, nPV2); 

#endif
}

/*-------------------------------------------------------------------------*/


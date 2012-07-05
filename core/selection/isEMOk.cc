/*-------------------------------------------------------------------------*/

#include "../include/core.h"

#ifdef __YEAR2011
  #include <HiggsZZ4lUtils/IsEMPlusPlusH4lDefs.h>
#endif

#ifdef __YEAR2012
  #include <egammaAnalysisUtils/MultiLeptonDefs.h>
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
	double Et_cl            = el_cl_E->at(index) / cosh(el_etas2->at(index));
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
#endif
}

/*-------------------------------------------------------------------------*/


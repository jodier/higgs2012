/*-------------------------------------------------------------------------*/

#include "../include/core.h"

#ifdef __YEAR2011
  #include <egammaAnalysisUtils/H4l2011Defs.h>
#endif

#ifdef __YEAR2012
  #include <HiggsZZ4lUtils/ElectronLikelihoodToolHSG2Helper.h>
#endif

/*-------------------------------------------------------------------------*/

UInt_t TLeptonAnalysis::el_isEMOk_at(Int_t index)
{

	UInt_t isem = 0x00;
#ifdef __YEAR2011
	float eta_s2 = el_etas2->at(index);
	float Et_cl = el_cl_E->at(index) / coshf(eta_s2);

	if( passH4l2011(
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
		false) != false
	) isem |= (1 << 0);
#endif
#ifdef __YEAR2012

	double eta              = el_etas2->at(index);
	double Et               = el_cl_E->at(index) / coshf(eta);
	double rHad             = el_Ethad->at(index) / Et;
	double rHad1            = el_Ethad1->at(index) / Et;
	double Reta             = el_reta->at(index);
	double w2               = el_weta2->at(index);
	double f1               = el_f1->at(index);
	double f3               = el_f3->at(index);
	double DEmaxs1          = (el_emaxs1->at(index) + el_Emax2->at(index) == 0) ? 0 : (el_emaxs1->at(index) - el_Emax2->at(index)) / (el_emaxs1->at(index) + el_Emax2->at(index));
	double deltaEta         = el_deltaeta1->at(index);
	double d0		= el_trackd0pv->at(index);
	double TRratio		= el_TRTHighTOutliersRatio->at(index);
	double d0sigma		= el_tracksigd0pv->at(index);
	double rphi		= el_rphi->at(index);
	double wstot            = el_wstot->at(index);
	double ws3		= el_ws3->at(index);
	double deltaPoverP	= 0.0;
	for(unsigned int i = 0; i < el_refittedTrack_LMqoverp->at(index).size(); i++)
	{
		if(el_refittedTrack_author->at(index).at(i) == 4)
		{
			deltaPoverP = 1.0 - el_trackqoverp->at(index) / el_refittedTrack_LMqoverp->at(index).at(i);
		}
	}

	int    nTRThigh         = el_nTRTHighTHits->at(index);
	int    nTRThighOutliers = el_nTRTHighTOutliers->at(index);
	int    nTRT             = el_nTRTHits->at(index);  
	int    nTRTOutliers     = el_nTRTOutliers->at(index); 
	int nTRTTotal     = nTRT     + nTRTOutliers    ;
	int nTRTTotalHigh = nTRThigh + nTRThighOutliers;

	double rTRT = nTRTTotal > 0 ? double(nTRTTotalHigh) / double(nTRTTotal) : 0.0;

	double deltaphiRes	= el_deltaphiRescaled->at(index);
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

	if (m_ElectronLikelihoodTool->passLikelihood(LikeEnum::Loose_BL_Pix,
		    eta, Et, f3, rHad, rHad1,
		    Reta, w2, f1, DEmaxs1,
		    deltaEta, d0, TRratio,
		    d0sigma, rphi, ws3,
		    deltaPoverP, deltaphiRes,
		    nSi, nSiDeadSensors, nPix, nPixDeadSensors,
		    nBlayer, nBlayerOutliers, expectBlayer,
		     convBit, nPV2) != false )
		isem |= (1 << 0); 

	if (m_ElectronLikelihoodTool->passLikelihood(LikeEnum::Very_Loose,
		    eta, Et, f3, rHad, rHad1,
		    Reta, w2, f1, DEmaxs1,
		    deltaEta, d0, TRratio,
		    d0sigma, rphi, ws3,
		    deltaPoverP, deltaphiRes,
		    nSi, nSiDeadSensors, nPix, nPixDeadSensors,
		    nBlayer, nBlayerOutliers, expectBlayer,
		     convBit, nPV2)  != false )
		isem |= (1 << 1);

	if ( (el_loose->at(index) && passLikelihoodThreePointFive(m_ElectronLikelihoodTool,
		    eta, Et, f3, rHad, rHad1,
		    Reta, w2, f1, DEmaxs1,
		    deltaEta, d0, TRratio,
		    d0sigma, rphi, ws3,
		    deltaPoverP, deltaphiRes,
		    nSi, nSiDeadSensors, nPix, nPixDeadSensors,
		    nBlayer, nBlayerOutliers, expectBlayer,
		     convBit, nPV2) ) != false )
		isem |= (1 << 2);

	if (m_MultiLeptonMenu.passMultiLepton(
		    eta, Et,
		    rHad, rHad1, Reta, w2,
		    f1, f3, wstot, DEmaxs1,
		    deltaEta, nSi, nSiDeadSensors, nPix,
		    nPixDeadSensors, deltaphiRes, deltaPoverP,
		    rTRT, nTRTTotal, nBlayer, expectBlayer) != false )
		isem |= (1 << 3);

	if (0 == (m_MultiLeptonMenu.getmask() & MultiLeptonMenu::MaskForZXX))
		isem |= (1 << 4);

#endif
	return isem;
}

/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/

#include "../include/core.h"

#ifdef __YEAR2011
  #include <egammaAnalysisUtils/H4l2011Defs.h>
#endif

//#ifdef __YEAR2012
//  #include <HiggsZZ4lUtils/ElectronLikelihoodToolHSG2Helper.h>
//#endif

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
	double d0		= el_trackd0pvunbiased->at(index);
	double TRratio		= el_TRTHighTOutliersRatio->at(index);
	double d0sigma		= el_tracksigd0pvunbiased->at(index);
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
	//---------------------------//
	// LH Loose	 	     //
	//---------------------------//
	m_ElectronLH->setOperatingPoint(LikeEnum::Loose);
	double discriminantLoose = m_ElectronLH->calculate(eta, Et, f3, rHad, rHad1,
								Reta, w2, f1, DEmaxs1,
								deltaEta, d0, TRratio,
								d0sigma, rphi,
								deltaPoverP, deltaphiRes,nPV2);

	bool passLHLoose = (bool)m_ElectronLH->accept(discriminantLoose, eta, Et, nSi,
							nSiDeadSensors, nPix, nPixDeadSensors,
							nBlayer, nBlayerOutliers, expectBlayer,
							convBit, nPV2);
	if (passLHLoose != false)
		isem |= (1 << 0); 


	//---------------------------//
	// LH Loose Relaxed - 3.5    //
	//---------------------------//
	m_ElectronLH->setOperatingPoint(LikeEnum::LooseRelaxed);
	double discriminantLooseRelaxed = m_ElectronLH->calculate(eta, Et, f3, rHad, rHad1,
								Reta, w2, f1, DEmaxs1,
								deltaEta, d0, TRratio,
								d0sigma, rphi,
								deltaPoverP, deltaphiRes,nPV2);
	bool passLHLooseRelaxed = (bool)m_ElectronLH->accept(discriminantLooseRelaxed, eta, Et, nSi,
							nSiDeadSensors, nPix, nPixDeadSensors,
							nBlayer, nBlayerOutliers, expectBlayer,
							convBit, nPV2);

	if (passLHLooseRelaxed  != false)
		isem |= (1 << 1);

	//---------------------------//
	// LH VeryLoose	 	     //
	//---------------------------//
	m_ElectronLH->setOperatingPoint(LikeEnum::VeryLoose);
	double discriminantVeryLoose = m_ElectronLH->calculate(eta, Et, f3, rHad, rHad1,
								Reta, w2, f1, DEmaxs1,
								deltaEta, d0, TRratio,
								d0sigma, rphi,
								deltaPoverP, deltaphiRes,nPV2);
	bool passLHVeryLoose = (bool)m_ElectronLH->accept(discriminantVeryLoose,  eta, Et, nSi,
							nSiDeadSensors, nPix, nPixDeadSensors,
							nBlayer, nBlayerOutliers, expectBlayer,
							convBit, nPV2) ;

	if (passLHVeryLoose != false)
		isem |= (1 << 2);

	//---------------------------//
	// ML		 	     //
	//---------------------------//
	Root::TAccept taccept;
	taccept = ml_2013->accept(eta, Et,
		    rHad, rHad1, Reta, w2,
		    f1, f3, wstot, DEmaxs1,
		    deltaEta, nSi, nSiDeadSensors, nPix,
		    nPixDeadSensors, deltaphiRes, deltaPoverP,
		    rTRT, nTRTTotal, nBlayer, expectBlayer, 
                    false);
	bool isMultilepton = (bool)taccept;
	if (isMultilepton != false)
		isem |= (1 << 3);

	//---------------------------//
	// Relax ML		     //
	//---------------------------//
	Root::TAccept accept = ml_2013->accept(1, 1, 1, 1, 1, 1, 1, 1,
                                                   1, 1, 1, 1, 1,
                                                  1, 1, 1, 1, 
                                                   1, 2, 2, 2);

	unsigned int m_MaskForZXX = 0;
	m_MaskForZXX |= ( 0x1 << accept.getCutPosition("Coverage"));
	m_MaskForZXX |= ( 0x1 << accept.getCutPosition("RHad"));
	m_MaskForZXX |= ( 0x1 << accept.getCutPosition("F3"));
	m_MaskForZXX |= ( 0x1 << accept.getCutPosition("Reta"));
	m_MaskForZXX |= ( 0x1 << accept.getCutPosition("W2"));
	m_MaskForZXX |= ( 0x1 << accept.getCutPosition("Wstot"));
	m_MaskForZXX |= ( 0x1 << accept.getCutPosition("DeltaPhiRes"));
	m_MaskForZXX |= ( 0x1 << accept.getCutPosition("NSilicon"));
	m_MaskForZXX |= ( 0x1 << accept.getCutPosition("NPixel"));
	m_MaskForZXX |= ( 0x1 << accept.getCutPosition("NBLayer"));
	m_MaskForZXX |= ( 0x1 << accept.getCutPosition("TR"));

	unsigned int res    = taccept.getCutResultBitSet().to_ulong();
        unsigned int notRes = ~res;

	if (0 == (notRes &  m_MaskForZXX))
		isem |= (1 << 4);


#endif
	return isem;
}

/*-------------------------------------------------------------------------*/


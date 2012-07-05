/*-------------------------------------------------------------------------*/

#include <cmath>
#include <cstdlib>

#include "../include/core.h"

/*-------------------------------------------------------------------------*/

//#define mc_with_constant_term 1	// for MC11a, b', b
#define mc_with_constant_term 0		// for MC11c, MC12x???

/*-------------------------------------------------------------------------*/

void TLeptonAnalysis::fixeEnergy(void)
{
	/*-----------------------------------------------------------------*/

	if(core::ER != false)
	{
		for(Int_t i = 0; i < el_n; i++)
		{
#ifndef __IS_MC
			el_cl_E->at(i) = m_energyRescaler->applyEnergyCorrectionMeV(
				el_cl_eta->at(i),
				el_cl_phi->at(i),
				el_cl_E->at(i),
				electronGetEt(i),
				0,
				"ELECTRON"
			);
#endif
#ifdef __YEAR2011
			el_cl_E->at(i) = el_cl_E->at(i) * m_energyRescaler->applyMCCalibrationMeV(
				el_cl_eta->at(i),
				electronGetEt(i),
				"ELECTRON"
			);
#endif
		}
	}
#ifdef __IS_MC
	if(core::SM != false)
	{
		float pT_ME;
		float pT_ID;
		float pT_old;
		float pT_new;

		/*---------------------------------------------------------*/

		for(Int_t i = 0; i < el_n; i++)
		{
			m_energyRescaler->SetRandomSeed(EventNumber + 100 * i);

			el_cl_E->at(i) = el_cl_E->at(i) * m_energyRescaler->getSmearingCorrectionMeV(
				el_cl_eta->at(i),
				el_cl_E->at(i),
#ifdef __YEAR2011
				0, mc_with_constant_term, "2011"
#endif
#ifdef __YEAR2012
				0, mc_with_constant_term, "2012"
#endif
			);
		}

		/*---------------------------------------------------------*/

		for(Int_t i = 0; i < mu_staco_n; i++)
		{
			pT_ME = (mu_staco_me_qoverp_exPV->at(i) != 0.0f) ? sin(mu_staco_me_theta_exPV->at(i)) / fabs(mu_staco_me_qoverp_exPV->at(i)) : 0.0f;
			pT_ID = (mu_staco_id_qoverp_exPV->at(i) != 0.0f) ? sin(mu_staco_id_theta_exPV->at(i)) / fabs(mu_staco_id_qoverp_exPV->at(i)) : 0.0f;

			pT_old = pT_new = mu_staco_pt->at(i);

			m_stacoSM->SetSeed(EventNumber, i);

			/**/ if(mu_staco_isCombinedMuon->at(i) != false)
			{
				m_stacoSM->Event(
					pT_ME,
					pT_ID,
					pT_old,
					mu_staco_eta->at(i)
				);

				pT_new = m_stacoSM->pTCB();
			}
			else if(mu_staco_isSegmentTaggedMuon->at(i) != false)
			{
				m_stacoSM->Event(
					pT_old,
					mu_staco_eta->at(i),
					"ID"
				);

				pT_new = m_stacoSM->pTID();
			}
			else if(mu_staco_isStandAloneMuon->at(i) != false)
			{
				m_stacoSM->Event(
					pT_old,
					mu_staco_eta->at(i),
					"MS"
				);

				pT_new = m_stacoSM->pTMS();
			}

			mu_staco_E->at(i) = (pT_new / pT_old) * mu_staco_E->at(i);
			mu_staco_pt->at(i) = pT_new;
		}

		/*---------------------------------------------------------*/

		for(Int_t i = 0; i < mu_calo_n; i++)
		{
			pT_ME = (mu_calo_me_qoverp_exPV->at(i) != 0.0f) ? sin(mu_calo_me_theta_exPV->at(i)) / fabs(mu_calo_me_qoverp_exPV->at(i)) : 0.0f;
			pT_ID = (mu_calo_id_qoverp_exPV->at(i) != 0.0f) ? sin(mu_calo_id_theta_exPV->at(i)) / fabs(mu_calo_id_qoverp_exPV->at(i)) : 0.0f;

			pT_old = pT_new = mu_calo_pt->at(i);

			m_stacoSM->SetSeed(EventNumber, i);

			m_stacoSM->Event(
				pT_old,
				mu_calo_eta->at(i),
				"ID"
			);

			pT_new = m_stacoSM->pTID();

			mu_calo_E->at(i) = (pT_new / pT_old) * mu_calo_E->at(i);
			mu_calo_pt->at(i) = pT_new;
		}

		/*---------------------------------------------------------*/
	}
#endif
}

/*-------------------------------------------------------------------------*/

Float_t TLeptonAnalysis::eventGetWeight1(void)
{
#ifdef __IS_MC
	Float_t weight = 1.0f;

	if(mcevt_weight[0].size() > 0)
	{
		if(mcevt_weight[0][0].size() == 1)
		{
			weight = mcevt_weight[0][0][0];
		}
	}

	if(weight == 0.0f)
	{
		weight = 1.0f;
	}

	return weight;
#else
	return 1.000f;
#endif
}

/*-------------------------------------------------------------------------*/

Float_t TLeptonAnalysis::eventGetWeight2(void)
{
#ifdef __IS_MC
	return m_pileupReweighting->GetCombinedWeight(RunNumber, mc_channel_number, averageIntPerXing);
#else
	return 1.000000000000000000000000000000000000000000000000000000000000000000000000000000000000f;
#endif
}

/*-------------------------------------------------------------------------*/

Float_t TLeptonAnalysis::eventGetWeight3(Int_t index, TLeptonType type)
{
#ifdef __IS_MC
	Float_t et;
	Float_t eta;

	TLorentzVector tlv;

	Float_t weight = 0.0;

	switch(type)
	{
		/*---------------------------------------------------------*/
		/* TYPE_ELECTRON					   */
		/*---------------------------------------------------------*/

		case TYPE_ELECTRON:
			et = electronGetEt(index);
			eta = el_cl_eta->at(index);
#ifdef __YEAR2011
			weight = \
				m_egammaSF->scaleFactor(eta, et, 5, 0, 6, 1, m_pileupReweighting->GetRandomRunNumber(RunNumber)).first
				*
				m_egammaSF->scaleFactor(eta, et, 4, 0, 6, 1, m_pileupReweighting->GetRandomRunNumber(RunNumber)).first
			;
#endif
#ifdef __YEAR2012
			weight = \
				m_egammaSF->scaleFactor(eta, et, 30, 0, 8, 1, m_pileupReweighting->GetRandomRunNumber(RunNumber)).first
				*
				m_egammaSF->scaleFactor(eta, et,  4, 0, 8, 1, m_pileupReweighting->GetRandomRunNumber(RunNumber)).first
			;
#endif
			break;

		/*---------------------------------------------------------*/
		/* MUON_STACO						   */
		/*---------------------------------------------------------*/

		case TYPE_MUON_CB_PLUS_ST:
		case TYPE_MUON_STANDALONE:
			tlv.SetPtEtaPhiE(mu_staco_pt->at(index), mu_staco_eta->at(index), mu_staco_phi->at(index), mu_staco_E->at(index));

			weight = m_stacoSCF->scaleFactor(mu_staco_charge->at(index), tlv)
				 *
				 m_stacoSASCF->scaleFactor(mu_staco_charge->at(index), tlv)
			;

			break;

		/*---------------------------------------------------------*/
		/* MUON_CALO						   */
		/*---------------------------------------------------------*/

		case TYPE_MUON_CALO:
			tlv.SetPtEtaPhiE(mu_calo_pt->at(index), mu_calo_eta->at(index), mu_calo_phi->at(index), mu_calo_E->at(index));

			weight = m_caloMuSCF->scaleFactor(mu_staco_charge->at(index), tlv);

			break;

		/*---------------------------------------------------------*/

		default:
			std::cout << "TLeptonAnalysis::eventGetWeight3() - Oula !" << std::endl;
			weight = 0.0f;
			break;

		/*---------------------------------------------------------*/
	}

	return weight;
#else
	return 1.000f;
#endif
}

/*-------------------------------------------------------------------------*/

Float_t TLeptonAnalysis::electronGetEtaDirection(Int_t index)
{
	Int_t n = el_nPixHits->at(index) + el_nSCTHits->at(index);

	return n >= 4 ? el_tracketa->at(index) : el_cl_eta->at(index);
}

/*-------------------------------------------------------------------------*/

Float_t TLeptonAnalysis::electronGetPhiDirection(Int_t index)
{
	Int_t n = el_nPixHits->at(index) + el_nSCTHits->at(index);

	return n >= 4 ? el_trackphi->at(index) : el_cl_phi->at(index);
}

/*-------------------------------------------------------------------------*/

Float_t TLeptonAnalysis::electronGetEt(Int_t index)
{
	Int_t n = el_nPixHits->at(index) + el_nSCTHits->at(index);

	return n >= 4 ? el_cl_E->at(index) / coshf(el_tracketa->at(index)) : el_cl_pt->at(index);
}

/*-------------------------------------------------------------------------*/

Bool_t TLeptonAnalysis::checkObject(
	Int_t index,
	TLeptonType type,
	Float_t __el_et,
	Float_t __mu_staco_pt,
	Float_t __mu_calo_pt
) {
	Int_t n;

	switch(type)
	{
		/*---------------------------------------------------------*/
		/* TYPE_ELECTRON					   */
		/*---------------------------------------------------------*/

		case TYPE_ELECTRON:
			if(el_author->at(index) != 1
			   &&
			   el_author->at(index) != 3
			 ) {
				goto __error;
			}

			elNr3++;

			if(el_isEMOk_at(index) == false) {
				goto __error;
			}

			elNr4++;

			if(fabs(el_cl_eta->at(index)) > 2.47f) {
				goto __error;
			}

			elNr5++;

			if(electronGetEt(index) < __el_et) {
				goto __error;
			}

			elNr6++;

			if((el_OQ->at(index) & 1446) != 0) {
				goto __error;
			}

			elNr7++;

			if(fabs(el_trackz0pvunbiased->at(index)) > 10.0f) {
				goto __error;
			}

			elNr8++;

			break;

		/*---------------------------------------------------------*/
		/* TYPE_MUON_CB_PLUS_ST					   */
		/*---------------------------------------------------------*/

		case TYPE_MUON_CB_PLUS_ST:
			if((mu_staco_author->at(index) != 6 && mu_staco_author->at(index) != 7) || mu_staco_isStandAloneMuon->at(index) != 0) {
				goto __error;
			}

			muNr3++;

			if(fabs(mu_staco_eta->at(index)) > 2.7f) {
				goto __error;
			}

			muNr4++;

			if(mu_staco_pt->at(index) < __mu_staco_pt) {
				goto __error;
			}

			muNr5++;

			if(mu_staco_expectBLayerHit->at(index) != 0 && mu_staco_nBLHits->at(index) <= 0) {
				goto __error;
			}

			muNr6++;
#ifdef __YEAR2011
			if(mu_staco_nPixHits->at(index) + mu_staco_nPixelDeadSensors->at(index) < 2) {
				goto __error;
			}
#endif
#ifdef __YEAR2012
			if(mu_staco_nPixHits->at(index) + mu_staco_nPixelDeadSensors->at(index) < 1) {
				goto __error;
			}
#endif
			muNr7++;
#ifdef __YEAR2011
			if(mu_staco_nSCTHits->at(index) + mu_staco_nSCTDeadSensors->at(index) < 6) {
				goto __error;
			}
#endif
#ifdef __YEAR2012
			if(mu_staco_nSCTHits->at(index) + mu_staco_nSCTDeadSensors->at(index) < 5) {
				goto __error;
			}
#endif
			muNr8++;

			if(mu_staco_nPixHoles->at(index) + mu_staco_nSCTHoles->at(index) > 2) {
				goto __error;
			}

			muNr9++;

			n = mu_staco_nTRTHits->at(index) + mu_staco_nTRTOutliers->at(index);

			if(fabs(mu_staco_eta->at(index)) < 1.9f)
			{
				if(n < 6 || mu_staco_nTRTOutliers->at(index) > 0.9f * n) {
					goto __error;
				}
			}
			else
			{
				if(n > 5 && mu_staco_nTRTOutliers->at(index) > 0.9f * n) {
					goto __error;
				}
			}

			muNr10++;

			if(fabs(mu_staco_d0_exPV->at(index)) > 1.0f) {
				goto __error;
			}

			muNr11++;

			if(fabs(mu_staco_z0_exPV->at(index)) > 10.0f) {
				goto __error;
			}

			muNr12++;

			break;

		/*---------------------------------------------------------*/
		/* TYPE_MUON_CB_PLUS_ST					   */
		/*---------------------------------------------------------*/

		case TYPE_MUON_STANDALONE:
			if(mu_staco_author->at(index) != 6 || mu_staco_isStandAloneMuon->at(index) == 0) {
				goto __error;
			}

			muNr3++;

			if(fabs(mu_staco_eta->at(index)) < 2.5f
			   ||
			   fabs(mu_staco_eta->at(index)) > 2.7f
			 ) {
				goto __error;
			}

			muNr4++;

			if(mu_staco_pt->at(index) < __mu_staco_pt) {
				goto __error;
			}

			muNr5++;

			if((mu_staco_nCSCEtaHits->at(index) + mu_staco_nCSCPhiHits->at(index)) <= 0 || mu_staco_nMDTEMHits->at(index) <= 0 || mu_staco_nMDTEOHits->at(index) <= 0) {
				goto __error;
			}

			muNr6++;
			muNr7++;
			muNr8++;
			muNr9++;
			muNr10++;
			muNr11++;
			muNr12++;

			break;

		/*---------------------------------------------------------*/
		/* MUON_CALO						   */
		/*---------------------------------------------------------*/

		case TYPE_MUON_CALO:
			if(mu_calo_author->at(index) != 16) {
				goto __error;
			}

			if(mu_calo_caloMuonIdTag->at(index) < 11
			   &&
			   mu_calo_caloLRLikelihood->at(index) < 0.9f
			 ) {
				goto __error;
			}

			muNr3++;

			if(fabs(mu_calo_eta->at(index)) > 0.1f) {
				goto __error;
			}

			muNr4++;

			if(mu_calo_pt->at(index) < __mu_calo_pt) {
				goto __error;
			}

			muNr5++;

			if(mu_calo_expectBLayerHit->at(index) != 0 && mu_calo_nBLHits->at(index) <= 0) {
				goto __error;
			}

			muNr6++;
#ifdef __YEAR2011
			if(mu_calo_nPixHits->at(index) + mu_calo_nPixelDeadSensors->at(index) < 2) {
				goto __error;
			}
#endif
#ifdef __YEAR2012
			if(mu_calo_nPixHits->at(index) + mu_calo_nPixelDeadSensors->at(index) < 1) {
				goto __error;
			}
#endif
			muNr7++;
#ifdef __YEAR2011
			if(mu_calo_nSCTHits->at(index) + mu_calo_nSCTDeadSensors->at(index) < 6) {
				goto __error;
			}
#endif
#ifdef __YEAR2012
			if(mu_calo_nSCTHits->at(index) + mu_calo_nSCTDeadSensors->at(index) < 5) {
				goto __error;
			}
#endif
			muNr8++;

			if(mu_calo_nPixHoles->at(index) + mu_calo_nSCTHoles->at(index) > 2) {
				goto __error;
			}

			muNr9++;

			n = mu_calo_nTRTHits->at(index) + mu_calo_nTRTOutliers->at(index);

			if(n > 5 && mu_calo_nTRTOutliers->at(index) > n * 0.9) {
				goto __error;
			}

			muNr10++;

			if(fabs(mu_calo_d0_exPV->at(index)) > 1.0f) {
				goto __error;
			}

			muNr11++;

			if(fabs(mu_calo_z0_exPV->at(index)) > 10.0f) {
				goto __error;
			}

			muNr12++;

			break;

		/*---------------------------------------------------------*/

		__error:
		default:
			return false;
	}

	return true;
}

/*-------------------------------------------------------------------------*/

#define __ELECTRON_CHECK(index) \
		if(el_author->at(index) != 1				\
		   &&							\
		   el_author->at(index) != 3				\
		 ) {							\
			continue;					\
		}							\
									\
		if(el_isEMOk_at(index) == false) {			\
			continue;					\
		}							\
									\
		if(fabs(el_cl_eta->at(index)) > 2.47f) {		\
			continue;					\
		}							\
									\
		if(electronGetEt(index) < __el_et) {			\
			continue;					\
		}							\
									\
		if((el_OQ->at(index) & 1446) != 0) {			\
			continue;					\
		}							\
									\
		if(fabs(el_trackz0pvunbiased->at(index)) > 10.0f) {	\
			continue;					\
		}

/*-------------------------------------------------------------------------*/

Bool_t TLeptonAnalysis::checkOverlapping(
	Int_t index,
	TLeptonType type,
	Float_t __el_et,
	Float_t __mu_staco_pt,
	Float_t __mu_calo_pt,
	Int_t muonIndexNr, Int_t muonIndexArray[], TLeptonType muonTypeArray[]
) {
	if(type == TYPE_ELECTRON)
	{
		/*---------------------------------------------------------*/
		/* ELECTRONS 1/2					   */
		/*---------------------------------------------------------*/

		for(Int_t xedni = 0; xedni < el_n; xedni++)
		{
			if(index != xedni
			   &&
			   el_trackd0->at(index) == el_trackd0->at(xedni)
			   &&
			   el_trackz0->at(index) == el_trackz0->at(xedni)
			   &&
			   el_tracktheta->at(index) == el_tracktheta->at(xedni)
			   &&
			   el_trackphi->at(index) == el_trackphi->at(xedni)
			   &&
			   el_trackqoverp->at(index) == el_trackqoverp->at(xedni)
			 ) {
				__ELECTRON_CHECK(xedni);

				if(electronGetEt(index) < electronGetEt(xedni))
				{
					return false;
				}
			}
		}

		elNr9++;

		/*---------------------------------------------------------*/
		/* ELECTRONS 2/2					   */
		/*---------------------------------------------------------*/
#ifdef __YEAR2012
		for(Int_t xedni = 0; xedni < el_n; xedni++)
		{
			if(index != xedni)
			{
				Float_t dEta = fabs(el_cl_eta->at(index) - el_cl_eta->at(xedni));
				Float_t dPhi = fabs(el_cl_phi->at(index) - el_cl_phi->at(xedni));

				while(dPhi >= +M_PI) dPhi -= 2.0 * M_PI;

				if(dEta < 3.0f * 0.025f
				   &&
				   dPhi < 5.0f * 0.025f
				 ) {
					__ELECTRON_CHECK(xedni);

					if(electronGetEt(index) < electronGetEt(xedni))
					{
						return false;
					}
				}
			}
		}

#endif
		elNr10++;

		/*---------------------------------------------------------*/
		/* MUONS						   */
		/*---------------------------------------------------------*/

		Float_t mu_id_eta;
		Float_t mu_id_phi;

		for(Int_t i = 0; i < muonIndexNr; i++)
		{
			Int_t xedni = muonIndexArray[i];

			switch(muonTypeArray[i])
			{
				case TYPE_MUON_CB_PLUS_ST:
				case TYPE_MUON_STANDALONE:
					mu_id_eta = -logf(tanf(0.5f * mu_staco_id_theta->at(xedni)));
					mu_id_phi = mu_staco_id_phi->at(xedni);
					break;

				case TYPE_MUON_CALO:
					mu_id_eta = -logf(tanf(0.5f * mu_calo_id_theta->at(xedni)));
					mu_id_phi = mu_calo_id_phi->at(xedni);
					break;

				default:
					return false;
			}

			if(sqrtf(__dR2(el_tracketa->at(index), mu_id_eta, el_trackphi->at(index), mu_id_phi)) < 0.02f * 0.02f)
			{
				return false;
			}
		}

		elNr11++;

		/*---------------------------------------------------------*/
	}

	return true;
}

/*-------------------------------------------------------------------------*/

Bool_t TLeptonAnalysis::truthMatch(
	Int_t index,
	TLeptonType type
) {
#ifdef __IS_MC
	switch(type)
	{
		case TYPE_ELECTRON:
			if((el_type->at(index) != 2 || (((((((((((((((((((el_origin->at(index) != 13))))))))))))))))))))
			   &&
			   (el_type->at(index) != 4 || (el_originbkg->at(index) != 13 && el_originbkg->at(index) != 40))
			 ) {
				goto __error;
			}
			break;

		case TYPE_MUON_CB_PLUS_ST:
		case TYPE_MUON_STANDALONE:
			if(abs(mu_staco_truth_type->at(index)) != 13 || mu_staco_truth_mothertype->at(index) != 23) {
				goto __error;
			}
			break;

		case TYPE_MUON_CALO:
			if(abs(mu_calo_truth_type->at(index)) != 13 || mu_calo_truth_mothertype->at(index) != 23) {
				goto __error;
			}
			break;

		__error:
		default:
			return false;
	}
#endif
	return true;
}

/*-------------------------------------------------------------------------*/


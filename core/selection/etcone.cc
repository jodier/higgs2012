/*-------------------------------------------------------------------------*/

#include "../include/core.h"

#include <egammaAnalysisUtils/CaloIsoCorrection.h>

/*-------------------------------------------------------------------------*/

Float_t TLeptonAnalysis::el_Etcone20_at(Int_t index)
{
#ifdef __YEAR2011
	return CaloIsoCorrection::GetNPVCorrectedIsolation(
		nPV2,
		el_etas2->at(index),
		20,
		__isMC,
		el_Etcone20->at(index),
		CaloIsoCorrection::ELECTRON
	);
#endif
#ifdef __YEAR2012
	return CaloIsoCorrection::GetPtEDCorrectedTopoIsolation(
		el_ED_median->at(i),
		el_cl_E->at(i),
		el_etas2->at(i),
		el_etap->at(i),
		el_cl_eta->at(i),
		20,
		__isMC,
		el_topoEtcone20->at(i),
		false,
		CaloIsoCorrection::ELECTRON
	);
#endif
}

/*-------------------------------------------------------------------------*/


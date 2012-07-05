/*-------------------------------------------------------------------------*/

#include <TRandom3.h>

#include "../include/core.h"

/*-------------------------------------------------------------------------*/

UInt_t TLeptonAnalysis::getElTrigger(void)
{
	if(core::OF == false)
	{
		elTrigger = 0x00;
#ifdef __IS_MC
  #ifdef __YEAR2011
		/**/ if(RunNumber == 180164 // B-D
			||
			RunNumber == 183003 // E-H
		 ) {
			if(EF_e20_medium) {
				elTrigger |= (1 << 0);
			}
			if(EF_2e12_medium) {
				elTrigger |= (1 << 1);
			}
		}
		else if(RunNumber == 186169) // I-K
		{
			TRandom3 random3;

			random3.SetSeed(mc_channel_number * EventNumber);

			const Float_t fracEl = (lumiPeriod2011I + lumiPeriod2011J) / (lumiPeriod2011I + lumiPeriod2011J + lumiPeriod2011K);

			if(random3.Uniform() < fracEl)
			{
				if(EF_e20_medium) {
					elTrigger |= (1 << 0);
				}
				if(EF_2e12_medium) {
					elTrigger |= (1 << 1);
				}
			}
			else
			{
				if(EF_e22_medium) {
					elTrigger |= (1 << 0);
				}
				if(EF_2e12T_medium) {
					elTrigger |= (1 << 1);
				}
			}
		}
		else if(RunNumber == 189751) // L-M
		{
			if(EF_e22vh_medium1) {
				elTrigger |= (1 << 0);
			}
			if(EF_2e12Tvh_medium) {
				elTrigger |= (1 << 1);
			}
		}
  #endif
  #ifdef __YEAR2012
		/**/ if(RunNumber == 195847) // A-B
		{
			if(EF_e24vhi_medium1 || EF_e60_medium1) {
				elTrigger |= (1 << 0);
			}
			if(EF_2e12Tvh_loose1) {
				elTrigger |= (1 << 1);
			}
		}
  #endif
#else
		char lumiPeriod = getlumiPeriod(RunNumber);
  #ifdef __YEAR2011
		/**/ if(lumiPeriod >= 'B' && lumiPeriod <= 'J')
		{
			if(EF_e20_medium) {
				elTrigger |= (1 << 0);
			}
			if(EF_2e12_medium) {
				elTrigger |= (1 << 1);
			}
		}
		else if(lumiPeriod >= 'K' && lumiPeriod <= 'K')
		{
			if(EF_e22_medium) {
				elTrigger |= (1 << 0);
			}
			if(EF_2e12T_medium) {
				elTrigger |= (1 << 1);
			}
		}
		else if(lumiPeriod >= 'L' && lumiPeriod <= 'M')
		{
			if(EF_e22vh_medium1) {
				elTrigger |= (1 << 0);
			}
			if(EF_2e12Tvh_medium) {
				elTrigger |= (1 << 1);
			}
		}
  #endif
  #ifdef __YEAR2012
		/**/ if(lumiPeriod >= 'A' && lumiPeriod <= 'B')
		{
			if(EF_e24vhi_medium1 || EF_e60_medium1) {
				elTrigger |= (1 << 0);
			}
			if(EF_2e12Tvh_loose1) {
				elTrigger |= (1 << 1);
			}
		}
  #endif
#endif
	}
	else
	{
		elTrigger = 0x03;
	}

	return elTrigger;
}

/*-------------------------------------------------------------------------*/

UInt_t TLeptonAnalysis::getMuTrigger(void)
{
	if(core::OF == false)
	{
		muTrigger = 0x00;
#ifdef __IS_MC
  #ifdef __YEAR2011
		/**/ if(RunNumber == 180164 // B-D
			||
			RunNumber == 183003 // E-H
		 ) {

			if(EF_mu18_MG) {
				muTrigger |= (1 << 0);
			}
			if(EF_2mu10_loose) {
				muTrigger |= (1 << 1);
			}
		}
		else if(RunNumber == 186169) // I-K
		{
			TRandom3 random3;

			random3.SetSeed(mc_channel_number * EventNumber);

			const Float_t fracMu = (lumiPeriod2011I) / (lumiPeriod2011I + lumiPeriod2011J + lumiPeriod2011K);

			if(random3.Uniform() < fracMu)
			{
				if(EF_mu18_MG) {
					muTrigger |= (1 << 0);
				}
				if(EF_2mu10_loose) {
					muTrigger |= (1 << 1);
				}
			}
			else
			{
				if(EF_mu18_MG_medium) {
					muTrigger |= (1 << 0);
				}
				if(EF_2mu10_loose) {
					muTrigger |= (1 << 1);
				}
			}
		}
		else if(RunNumber == 189751) // L-M
		{
			if(EF_mu18_MG_medium) {
				muTrigger |= (1 << 0);
			}
			if(EF_2mu10_loose) {
				muTrigger |= (1 << 1);
			}
		}
  #endif
  #ifdef __YEAR2012
		/**/ if(RunNumber == 195847) // A-B
		{
			if(EF_mu24i_tight || EF_mu36_tight) {
				muTrigger |= (1 << 0);
			}
			if(EF_2mu13 || EF_mu18_tight_mu8_EFFS) {
				muTrigger |= (1 << 1);
			}
		}
  #endif
#else
		char lumiPeriod = getlumiPeriod(RunNumber);
  #ifdef __YEAR2011
		/**/ if(lumiPeriod >= 'B' && lumiPeriod <= 'I')
		{
			if(EF_mu18_MG) {
				muTrigger |= (1 << 0);
			}
			if(EF_2mu10_loose) {
				muTrigger |= (1 << 1);
			}
		}
		else if(lumiPeriod >= 'J' && lumiPeriod <= 'M')
		{
			if(EF_mu18_MG_medium) {
				muTrigger |= (1 << 0);
			}
			if(EF_2mu10_loose) {
				muTrigger |= (1 << 1);
			}
		}
  #endif
  #ifdef __YEAR2012
		/**/ if(lumiPeriod >= 'A' && lumiPeriod <= 'B')
		{
			if(EF_mu24i_tight || EF_mu36_tight) {
				muTrigger |= (1 << 0);
			}
			if(EF_2mu13 || EF_mu18_tight_mu8_EFFS) {
				muTrigger |= (1 << 1);
			}
		}
  #endif
#endif
	}
	else
	{
		muTrigger = 0x03;
	}

	return muTrigger;
}

/*-------------------------------------------------------------------------*/

UInt_t TLeptonAnalysis::triggerMatch(
	Int_t index,
	TLeptonType type
) {
	UInt_t result = 0x00;

	std::string chain1_A = "";
	std::string chain1_B = "";
	std::string chain2_A = "";
	std::string chain2_B = "";

	Int_t n;

	TLorentzVector tlv1;
	TLorentzVector tlv2;

	Bool_t res1;
	Bool_t res2;

	Bool_t symmetric_A = true;
	Bool_t symmetric_B = true;

	std::pair<bool, bool> Res1;
	std::pair<bool, bool> Res2;
#ifndef __IS_MC
	char lumiPeriod = getlumiPeriod(RunNumber);
#endif
	switch(type)
	{
		/*---------------------------------------------------------*/

		case TYPE_ELECTRON:
#ifdef __IS_MC
  #ifdef __YEAR2011
			/**/ if(RunNumber == 180164 // B-D
				||
				RunNumber == 183003 // E-H
			 ) {
				chain1_A = "EF_e20_medium";
				chain1_B = "";

				chain2_A = "EF_2e12_medium";
				chain2_B = "";
			}
			else if(RunNumber == 186169) // I-K
			{
				TRandom3 random3;

				random3.SetSeed(mc_channel_number * EventNumber);

				const Float_t fracEl = (lumiPeriod2011I + lumiPeriod2011J) / (lumiPeriod2011I + lumiPeriod2011J + lumiPeriod2011K);

				if(random3.Uniform() < fracEl)
				{
					chain1_A = "EF_e20_medium";
					chain1_B = "";

					chain2_A = "EF_2e12_medium";
					chain2_B = "";
				}
				else
				{
					chain1_A = "EF_e22_medium";
					chain1_B = "";

					chain2_A = "EF_2e12T_medium";
					chain2_B = "";
				}
			}
			else if(RunNumber == 189751) // L-M
			{
				chain1_A = "EF_e22vh_medium1";
				chain1_B = "";

				chain2_A = "EF_2e12Tvh_medium";
				chain2_B = "";
			}
  #endif
  #ifdef __YEAR2012
			/**/ if(RunNumber == 195847) // A-B
			{
				chain1_A = "EF_e24vhi_medium1";
				chain1_B = "EF_e60_medium1";

				chain2_A = "EF_2e12Tvh_loose1";
				chain2_B = "";
			}
  #endif
#else
  #ifdef __YEAR2011
			/**/ if(lumiPeriod >= 'B' && lumiPeriod <= 'J')
			{
				chain1_A = "EF_e20_medium";
				chain1_B = "";

				chain2_A = "EF_2e12_medium";
				chain2_B = "";
			}
			else if(lumiPeriod >= 'K' && lumiPeriod <= 'K')
			{
				chain1_A = "EF_e22_medium";
				chain1_B = "";

				chain2_A = "EF_2e12T_medium";
				chain2_B = "";
			}
			else if(lumiPeriod >= 'L' && lumiPeriod <= 'M')
			{
				chain1_A = "EF_e22vh_medium1";
				chain1_B = "";

				chain2_A = "EF_2e12Tvh_medium";
				chain2_B = "";
			}
  #endif
  #ifdef __YEAR2012
			/**/ if(lumiPeriod >= 'A' && lumiPeriod <= 'B') // A-B
			{
				chain1_A = "EF_e24vhi_medium1";
				chain1_B = "EF_e60_medium1";

				chain2_A = "EF_2e12Tvh_loose1";
				chain2_B = "";
			}
  #endif
#endif
			if((chain1_A.length() > 0 && m_elTriggerMatching->match(el_tracketa->at(index), el_trackphi->at(index), chain1_A) != false)
			   ||
			   (chain1_B.length() > 0 && m_elTriggerMatching->match(el_tracketa->at(index), el_trackphi->at(index), chain1_B) != false)
			 ) {
				result |= (1 << 0);
			}

			tlv1.SetPtEtaPhiE(
				el_cl_E->at(index) / coshf(el_tracketa->at(index)),
				el_tracketa->at(index),
				el_trackphi->at(index),
				el_cl_E->at(index)
			);

			for(Int_t xedni = 0; xedni < el_n; xedni++)
			{
				if(index != xedni)
				{
					tlv2.SetPtEtaPhiE(
						el_cl_E->at(xedni) / coshf(el_tracketa->at(xedni)),
						el_tracketa->at(xedni),
						el_trackphi->at(xedni),
						el_cl_E->at(xedni)
					);

					if(chain2_A.length() > 0)
					{
						m_elTriggerMatching->matchDielectron(tlv1, tlv2, chain2_A, res1, res2);

						if(res1 != false && res2 != false)
						{
							result |= (1 << 1);

							break;
						}
					}

					if(chain2_B.length() > 0)
					{
						m_elTriggerMatching->matchDielectron(tlv1, tlv2, chain2_B, res1, res2);

						if(res1 != false && res2 != false)
						{
							result |= (1 << 1);

							break;
						}
					}
				}
			}

			break;

		/*---------------------------------------------------------*/

		case TYPE_MUON_CB_PLUS_ST:
		case TYPE_MUON_STANDALONE:
		case TYPE_MUON_CALO:
#ifdef __IS_MC
  #ifdef __YEAR2011
			/**/ if(RunNumber == 180164 // B-D
				||
				RunNumber == 183003 // E-H
			 ) {
				chain1_A = "EF_mu18_MG";
				chain1_B = "";

				chain2_A = "EF_2mu10";
				chain2_B = "";
			}
			else if(RunNumber == 186169) // I-K
			{
				TRandom3 random3;

				random3.SetSeed(mc_channel_number * EventNumber);

				const Float_t fracMu = (lumiPeriod2011I) / (lumiPeriod2011I + lumiPeriod2011J + lumiPeriod2011K);

				if(random3.Uniform() < fracMu)
				{
					chain1_A = "EF_mu18_MG";
					chain1_B = "";

					chain2_A = "EF_2mu10";
					chain2_B = "";
				}
				else
				{
					chain1_A = "EF_mu18_MG_medium";
					chain1_B = "";

					chain2_A = "EF_2mu10";
					chain2_B = "";
				}
			}
			else if(RunNumber == 189751) // L-M
			{
				chain1_A = "EF_mu18_MG_medium";
				chain1_B = "";

				chain2_A = "EF_2mu10";
				chain2_B = "";
			}
  #endif
  #ifdef __YEAR2012
			/**/ if(RunNumber == 195847) // A-B
			{
				chain1_A = "EF_mu24i_tight";
				chain1_B = "EF_mu36_tight";

				chain2_A = "EF_2mu13";
				chain2_B = "EF_mu18_tight_mu8_EFFS";

				symmetric_B = false;
			}
  #endif
#else
  #ifdef __YEAR2011
			/**/ if(lumiPeriod >= 'B' && lumiPeriod <= 'I')
			{
				chain1_A = "EF_mu18_MG";
				chain1_B = "";

				chain2_A = "EF_2mu10";
				chain2_B = "";
			}
			else if(lumiPeriod >= 'J' && lumiPeriod <= 'M')
			{
				chain1_A = "EF_mu18_MG_medium";
				chain1_B = "";

				chain2_A = "EF_2mu10";
				chain2_B = "";
			}
  #endif
  #ifdef __YEAR2012
			/**/ if(lumiPeriod >= 'A' && lumiPeriod <= 'B')
			{
				chain1_A = "EF_mu24i_tight";
				chain1_B = "EF_mu36_tight";

				chain2_A = "EF_2mu13";
				chain2_B = "EF_mu18_tight_mu8_EFFS";

				symmetric_B = false;
			}
  #endif
#endif
			if(type != TYPE_MUON_CALO)
			{
				if((chain1_A.length() > 0 && m_muTriggerMatching->match(mu_staco_eta->at(index), mu_staco_phi->at(index), chain1_A) != false)
				   ||
				   (chain1_B.length() > 0 && m_muTriggerMatching->match(mu_staco_eta->at(index), mu_staco_phi->at(index), chain1_B) != false)
				 ) {
					result |= (1 << 0);
				}

				tlv1.SetPtEtaPhiE(
					mu_staco_pt->at(index),
					mu_staco_eta->at(index),
					mu_staco_phi->at(index),
					mu_staco_E->at(index)
				);

				n = mu_staco_n;
			}
			else
			{
				if((chain1_A.length() > 0 && m_muTriggerMatching->match(mu_calo_eta->at(index), mu_calo_phi->at(index), chain1_A) != false)
				   ||
				   (chain1_B.length() > 0 && m_muTriggerMatching->match(mu_calo_eta->at(index), mu_calo_phi->at(index), chain1_B) != false)
				 ) {
					result |= (1 << 0);
				}

				tlv1.SetPtEtaPhiE(
					mu_calo_pt->at(index),
					mu_calo_eta->at(index),
					mu_calo_phi->at(index),
					mu_calo_E->at(index)
				);

				n = mu_calo_n;
			}

			for(Int_t xedni = 0; xedni < n; xedni++)
			{
				if(index != xedni)
				{
					if(type != TYPE_MUON_CALO)
					{
						tlv2.SetPtEtaPhiE(
							mu_staco_pt->at(xedni),
							mu_staco_eta->at(xedni),
							mu_staco_phi->at(xedni),
							mu_staco_E->at(xedni)
						);
					}
					else
					{
						tlv2.SetPtEtaPhiE(
							mu_calo_pt->at(xedni),
							mu_calo_eta->at(xedni),
							mu_calo_phi->at(xedni),
							mu_calo_E->at(xedni)
						);
					}

					if(chain2_A.length() > 0)
					{
						m_muTriggerMatching->matchDimuon(tlv1, tlv2, chain2_A, Res1, Res2);

						if(symmetric_A != false)
						{
							if(Res1.first != false
							   &&
							   Res2.first != false
							 ) {
								result |= (1 << 1);

								break;
							}
						}
						else
						{
							if((Res1.first != false && Res2.second != false)
							   ||
							   (Res1.second != false && Res2.first != false)
							 ) {
								result |= (1 << 1);

								break;
							}
						}
					}

					if(chain2_B.length() > 0)
					{
						m_muTriggerMatching->matchDimuon(tlv1, tlv2, chain2_B, Res1, Res2);

						if(symmetric_B != false)
						{
							if(Res1.first != false
							   &&
							   Res2.first != false
							 ) {
								result |= (1 << 1);

								break;
							}
						}
						else
						{
							if((Res1.first != false && Res2.second != false)
							   ||
							   (Res1.second != false && Res2.first != false)
							 ) {
								result |= (1 << 1);

								break;
							}
						}
					}
				}
			}

			break;

		/*---------------------------------------------------------*/
	}

	return result;
}

/*-------------------------------------------------------------------------*/

/* Info: use <BASE>/tools/hash to conpute the hashs
 */

Int_t TLeptonAnalysis::triggerTrace(UInt_t result[])
{
	Int_t nr = 0;

	if(core::OF != false)
	{
		/*---------------------------------------------------------*/
		/* ELECTRONS						   */
		/*---------------------------------------------------------*/
#ifdef __YEAR2011
		if(EF_e20_medium != 0) {
			result[nr++] = 0xD4CD729C;
		}

		if(EF_e22_medium != 0) {
			result[nr++] = 0xB784EC93;
		}

		if(EF_e22_medium1 != 0) {
			result[nr++] = 0xADCD942C;
		}

		if(EF_e22vh_medium1 != 0) {
			result[nr++] = 0x69EA9F52;
		}

		if(EF_2e12_medium != 0) {
			result[nr++] = 0xF48A09FA;
		}

		if(EF_2e12T_medium != 0) {
			result[nr++] = 0x80D5CCB8;
		}

		if(EF_2e12Tvh_medium != 0) {
			result[nr++] = 0xD84960ED;
		}
#endif
#ifdef __YEAR2012
		if(EF_e24vhi_medium1 != 0) {
			result[nr++] = 0x2899406B;
		}

		if(EF_e60_medium1 != 0) {
			result[nr++] = 0x420FE8F2;
		}

		if(EF_2e12Tvh_loose1 != 0) {
			result[nr++] = 0xD7D90387;
		}
#endif
		/*---------------------------------------------------------*/
		/* MUONS						   */
		/*---------------------------------------------------------*/
#ifdef __YEAR2011
		if(EF_mu18_MG != 0) {
			result[nr++] = 0x0803E760;
		}

		if(EF_mu18_MG_medium != 0) {
			result[nr++] = 0x869B9356;
		}

		if(EF_2mu10_loose != 0) {
			result[nr++] = 0xD92F4787;
		}
#endif
#ifdef __YEAR2012
		if(EF_mu24i_tight != 0) {
			result[nr++] = 0x95E7DAA9;
		}

		if(EF_mu36_tight != 0) {
			result[nr++] = 0x91932CDD;
		}

		if(EF_2mu13 != 0) {
			result[nr++] = 0x1BC06A07;
		}

		if(EF_mu18_tight_mu8_EFFS != 0) {
			result[nr++] = 0x61E98BBD;
		}
#endif
		/*---------------------------------------------------------*/
	}

	return nr;
}

/*-------------------------------------------------------------------------*/


//////////////////////////////////////////////////////////////
// Small macro to remove overlaps                          /// 
// between H->4l related                                   ///
// MC samples                                              ///
//////////////////////////////////////////////////////////////
// Usage:                                                  ///
// mc_channel_number1 : sample to remove events from       /// 
//                     (current sample)                    ///          
// mc_channel_number2 : core sample                        ///
// MC_n               : number of entries in truth record  ///
// MC_pt,             : pointer to the relevant D3PD info  ///
// MC_eta,                                                 /// 
// MC_phi,                                                 ///
// MC_m,                                                   ///
// MC_status,                                              ///
// MC_pdgId                                                ///
//////////////////////////////////////////////////////////////
// K. Nikolopoulos (U. Birmingham)                         ///
// May 23, 2012                                            ///
//////////////////////////////////////////////////////////////
// ttbar
//
// we have three samples: 
// the 1lepton filter (105200)
// the 2lepton filter (109345 in mc11, 110001 in mc12)
// the 4lepton filter (109346 in mc11, 146369 in mc12)
//
// the 2lepton filter should not be used 
// (i.e. kill all events) 
// since it has lower statistics than then 1lepton filter
//
// ZZ
// 
// we have the inclusive sample ()
// the filtered 100-150
// the filtered >500
//
// from the 1lepton filter, remove those that fall 
// in the 4lepton filter phase-space
//
//////////////////////////////////////////////////////////////
//
#include "HiggsZZ4lUtils/McOverlapRemoval.h"
using namespace std;

bool killEvent(UInt_t mc_channel_number1, UInt_t mc_channel_number2,
	       Int_t MC_n,
	       vector<float>* MC_pt,
	       vector<float>* MC_eta,
	       vector<float>* MC_phi,
	       vector<float>* MC_m,
	       vector<int>* MC_status,
	       vector<int>* MC_pdgId)
{
  
  if(mc_channel_number1==109345)// || mc_channel_number1==110001)
    return true;
  else if(mc_channel_number1==105200 || mc_channel_number1==110001)
    {
      //mc_channel_number2==109346: 
      double mcut1=60.;
      double mcut2=12.;
      if(mc_channel_number2==146369)
	{
	  mcut1= 40.;
	  mcut2= 12.;
	}

      std::vector<TLorentzVector*> temp;
      int icount=0;
      for(int i = 0; i < MC_n; i++){
	if(MC_pt->at(i)<5.e3)
	  continue;
	if(MC_status->at(i)!=1)
	  continue;
	if(TMath::Abs(MC_pdgId->at(i)) == 13 ||TMath::Abs(MC_pdgId->at(i)) == 11){
	  temp.push_back(new TLorentzVector());
	  temp.at(icount)->SetPtEtaPhiM(MC_pt->at(i)/1000.0, MC_eta->at(i), MC_phi->at(i), MC_m->at(i)/1000.0);
	  icount++;
	}
      }
      bool filter = false;
      if(icount>3){
	for(int i=0;i<icount;i++){
	  for(int j=0;j<icount;j++){
	    if(i==j)
	      continue;
	    for(int k=0;k<icount;k++){
	      if(i==k||j==k)
		continue;
	      for(int l=0;l<icount;l++){
		if(i==l||j==l||k==l)
		  continue;
		double mass1= (*temp.at(i)+ *temp.at(j)).M();
		double mass2= (*temp.at(k)+ *temp.at(l)).M();
		if(mass1>mcut1 && mass2>mcut2)
		  filter=true;
	      }
	    }
	  }
	}
      }
      for(int i=0;i<icount;i++)
	delete temp.at(i);
      if(filter)
	return true;
    }
  else if(/////// ZZ 'inclusive' ///////
	  mc_channel_number1==126937
	  || mc_channel_number1==126938
	  //mc_channel_number1==126939 || //(bug in the tau->lep forced decay for the filtered sample)
	  || mc_channel_number1==126940
	  //mc_channel_number1==126941 || //(bug in the tau->lep forced decay for the filtered sample)
	  //mc_channel_number1==126942 || //(bug in the tau->lep forced decay for the filtered sample)
	  /////// ZZ 'm4l filtered' 100 - 150  ///////
	  || mc_channel_number1==167162
	  || mc_channel_number1==167163
	  //mc_channel_number1==167164 ||  //(bug in the tau->lep forced decay for the filtered sample)
	  || mc_channel_number1==167165 
	  //mc_channel_number1==167166 ||  //(bug in the tau->lep forced decay for the filtered sample)
	  //mc_channel_number1==167167  //(bug in the tau->lep forced decay for the filtered sample)
	  /////// ZZ 'm4l filtered' 100 - 150  ///////
	  || mc_channel_number1==169690
	  || mc_channel_number1==169691
	  || mc_channel_number1==169692
          )
    {
      int isTypeZZ = 0;
      if(mc_channel_number1==167162 ||
	 mc_channel_number1==167163 ||
	 //mc_channel_number1==167164 ||  //(bug in the tau->lep forced decay for the filtered sample)
	 mc_channel_number1==167165) 
	 //mc_channel_number1==167166 || //(bug in the tau->lep forced decay for the filtered sample)
	 //mc_channel_number1==167167  //(bug in the tau->lep forced decay for the filtered sample)
	//)
	isTypeZZ = 1;
      if(mc_channel_number1==169690 
	 || mc_channel_number1==169691 
	 || mc_channel_number1==169692
	 )
	isTypeZZ = 2;
      
      double massUp   = 150.;
      double massDown = 110.;
      double massDown2= 550.;
      std::vector<TLorentzVector*> temp;
      std::vector<double> tempEta;
      int icount=0;
      for(int i = 0; i < MC_n; i++){
	if(MC_pt->at(i)<3.e3)// || fabs(MC_eta->at(i))>3.)
	  continue;
	if(MC_status->at(i)!=1)
	  continue;
	if(TMath::Abs(MC_pdgId->at(i)) == 13 ||TMath::Abs(MC_pdgId->at(i)) == 11){
	  temp.push_back(new TLorentzVector());
	  temp.at(icount)->SetPtEtaPhiM(MC_pt->at(i)/1000.0, MC_eta->at(i), MC_phi->at(i), MC_m->at(i)/1000.0);
	  tempEta.push_back(fabs(MC_eta->at(i)));
	  icount++;
	}
      }
      bool filter = false;
      if(icount>3)
	{
	  for(int i=0;i<icount;i++)
	    {
	      for(int j=0;j<icount;j++)
		{
		  if(i==j)
		    continue;
		  for(int k=0;k<icount;k++)
		    {
		      if(i==k||j==k)
			continue;
		      for(int l=0;l<icount;l++)
			{
			  if(i==l||j==l||k==l)
			    continue;
			  double mass= (*temp.at(i)+ *temp.at(j)+ *temp.at(k)+ *temp.at(l)).M();
			  if(isTypeZZ==0)
			    {
			      if( tempEta.at(i)<3. && tempEta.at(j)<3. && tempEta.at(k)<3. && tempEta.at(l)<3. && mass<massUp && mass>massDown)
				filter=true;
			      if( tempEta.at(i)<5. && tempEta.at(j)<5. && tempEta.at(k)<5. && tempEta.at(l)<5. && mass>massDown2 )
				filter=true;

			    }
			  else if(isTypeZZ==1)
			    {
			      if( !(tempEta.at(i)<3. && tempEta.at(j)<3. && tempEta.at(k)<3. && tempEta.at(l)<3.) || (mass>massUp && mass<massDown))
				filter=true;
			    }
			  else if(isTypeZZ==2)
			    {
			      if( !(tempEta.at(i)<5. && tempEta.at(j)<5. && tempEta.at(k)<5. && tempEta.at(l)<5.) || mass<massDown2)
				filter=true;
			    }
			  else
			    {
			      std::cerr<< "McOverlapRemoval:: WARNING :: what's the isTypeZZ again? "<<std::endl;
			    }
			}
		    }
		}
	    }
	}
      for(int i=0;i<icount;i++)
	delete temp.at(i);
      if(filter)
	return true;
    }
  else
    {
      //cout<< "not known overlap"<<std::endl;
      return false;
    }

    return false;
}



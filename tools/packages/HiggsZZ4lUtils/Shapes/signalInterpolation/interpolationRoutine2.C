////////////////////////////////////////////
// interface to th1fmorph for H->4l
//
//
// K. Nikolopoulos (Brookhaven National Laboratory)
// 2011
////////////////////////////////////////////

#ifndef INTERPOLATIONROUTINE
#define INTERPOLATIONROUTINE
#include <iostream>
#include <vector>
#include <sstream>
#include "TFile.h"
#include "th1fmorph.C"
int interpolate(int type=0, int year=2011);
int main()
{
  interpolate(0);
  interpolate(1);
  interpolate(2);
  interpolate(3);
  interpolate(0,2012);
  interpolate(1,2012);
  interpolate(2,2012);
  interpolate(3,2012);

  return 0;
}
int interpolate(int type, int year)
{
  TString filename("interpolationInputsZmass2011.root");
  if(year==2012)
    filename="interpolationInputsZmass2012.root";

  std::vector<double> higgsMassesVBF;
  std::vector<double> higgsMassesGGF;
  std::vector<double> higgsMassesWH;
  std::vector<double> higgsMassesZH;

  if(year==2011)
    {
      for(double mass=110.;mass<=200;mass+=5.)
	higgsMassesGGF.push_back(mass);
      higgsMassesGGF.push_back(210.);
      for(double mass=220.;mass<=600;mass+=20.)
	higgsMassesGGF.push_back(mass);
      
      for(double mass=110.;mass<=200;mass+=5.)
	higgsMassesVBF.push_back(mass);
      higgsMassesVBF.push_back(210.);
      for(double mass=220.;mass<=600;mass+=20.)
	higgsMassesVBF.push_back(mass);
      
      for(double mass=110.;mass<=200;mass+=5.)
	higgsMassesWH.push_back(mass);
      higgsMassesWH.push_back(210.);
      for(double mass=220.;mass<=300;mass+=20.)
	higgsMassesWH.push_back(mass);
      
      for(double mass=110.;mass<=200;mass+=5.)
	higgsMassesZH.push_back(mass);
      higgsMassesZH.push_back(210.);
      for(double mass=220.;mass<=300;mass+=20.)
	higgsMassesZH.push_back(mass);
    }
  else if(year==2012)
    {
      for(double mass=110.;mass<=200;mass+=5.)
	higgsMassesGGF.push_back(mass);
      for(double mass=220.;mass<=600;mass+=20.)
	higgsMassesGGF.push_back(mass);
      
      for(double mass=110.;mass<=200;mass+=5.)
	higgsMassesVBF.push_back(mass);
      for(double mass=220.;mass<=600;mass+=20.)
	higgsMassesVBF.push_back(mass);
      
      for(double mass=110.;mass<=200;mass+=5.)
	higgsMassesWH.push_back(mass);
      for(double mass=220.;mass<=300;mass+=20.)
	higgsMassesWH.push_back(mass);
      
      for(double mass=110.;mass<=200;mass+=5.)
	higgsMassesZH.push_back(mass);
      for(double mass=220.;mass<=300;mass+=20.)
	higgsMassesZH.push_back(mass);

    }

  ///
  TString * prodnames[4]={new TString("ggF"),new TString("VBF"), new TString("WH"), new TString("ZH")};
  std::vector<double> *masses[4]={&higgsMassesGGF,&higgsMassesVBF, &higgsMassesWH, &higgsMassesZH};
  std::vector<TH1F*> hist[4][3];
  std::vector<double> norm[4];
  std::vector<double> norm2[4];
  std::vector<TH1F*> histVBF;
  std::vector<double> normVBF;
  std::vector<double> normVBF2;
  std::vector<TH1F*> histWH;
  std::vector<double> normWH;
  std::vector<double> normWH2;
  std::vector<TH1F*> histZH;
  std::vector<double> normZH;
  std::vector<double> normZH2;

  TFile*f=new TFile(filename,"READ");
  for(int iprod=0;iprod<4;iprod++)
    {
      for(unsigned int i=0;i<(*(masses[iprod])).size();i++)
	{
	  TString hname("");
	  hname+=Form("%i",(int)((*(masses[iprod]))[i]*10.));
	  if(iprod==0)
	    hname+="_higgs_";
	  else if(iprod==1)
	    hname+="_higgsVBF_";
	  else if(iprod==2)
	    hname+="_higgsWH_";
	  else if(iprod==3)
	    hname+="_higgsZH_";
	  else
	    {
	      std::cout <<"BUG"<<std::endl;
	      return 0;
	    }
	    
	  
	  TString hname1("ES_lo_");
	  TString hname2("ES_hi_");
	  TString hnamesuf("");
	  hnamesuf+=Form("%i",(int)(type));
	  
	  
	  //std::cout << hname<<std::endl;
	  //std::cout << (TH1F*)f->Get(hname)<<std::endl;
	  if(!f->Get(hname+hnamesuf))
	    {
	      std::cout <<"WARNING::THIS POINT DOESN'T EXIST:: " << (*(masses[iprod]))[i]<<std::endl;
	      continue;
	    }
	  hist[iprod][0].push_back((TH1F*)f->Get(hname+hnamesuf));
	  hist[iprod][1].push_back((TH1F*)f->Get(hname+hname1+hnamesuf));
	  hist[iprod][2].push_back((TH1F*)f->Get(hname+hname2+hnamesuf));
	  
	  norm[iprod].push_back(hist[iprod][0][i]->Integral());
	  for(int j=0;j<3;j++)
	    (hist[iprod][j])[i]->Scale(1./norm[iprod][i]);
	  norm2[iprod].push_back(hist[iprod][0][i]->Integral());
	  std::cout <<  *(prodnames[iprod])<<" : "<< (*(masses[iprod]))[i]<<"\t"<<(hist[iprod][0])[i]<<"\t"<<norm[iprod][i]<<"\t"<<norm2[iprod][i]<<std::endl;
	}
    }
  //TGraph*gr=new TGraph(higgsMassesGGF.size(),&higgsMassesGGF[0],&norm[0]);
  //gr->Draw("A*");

  /***
      The mass points are the following :

	- 110-160 : 500 MeV steps
	- 160-300 : 2 GeV steps
	- 300-400 : 5 GeV steps
	- 400-600 : 10 GeV steps
  ***/
  TString outname("interpol");
  outname+=(int)type;
  if(year==2011)
    outname+="_2011";
  else if(year==2012)
    outname+="_2012";
  outname+=".root";
  TFile*gg=new TFile(outname,"RECREATE");

  std::vector<double> higgsMassesResult;
  for(double mass=110.;mass<160;mass+=0.5)
    higgsMassesResult.push_back(mass);
  for(double mass=160.;mass<300;mass+=1.)
    higgsMassesResult.push_back(mass);
  for(double mass=300.;mass<400;mass+=5.)
    higgsMassesResult.push_back(mass);
  for(double mass=400.;mass<=600;mass+=10.)
    higgsMassesResult.push_back(mass);

  for(int iprod=0;iprod<4;iprod++)
    {
      unsigned int i=0;
      for(unsigned int imass=0;imass<higgsMassesResult.size();imass++)
	{
	  unsigned int nsize = (*(masses[iprod])).size();
	  if((*(masses[iprod]))[nsize-1]<higgsMassesResult[imass])
	    continue;
	  for(i=0;i<nsize;i++)
	    if((*(masses[iprod]))[i]>higgsMassesResult[imass])
	      break;
	  i--;
	  if(i==nsize-1)
	    i--;

	  {
	    TH1F *hdf1  =hist[iprod][0][i];
	    TH1F *hdf2  =hist[iprod][0][i+1];
	    //hdf1->Draw("same");
	    //hdf2->SetLineColor(i+1);
	    //hdf2->Draw("same");     
	    double position = (higgsMassesResult[imass] - (*(masses[iprod]))[i])/((*(masses[iprod]))[i+1] - (*(masses[iprod]))[i]);
	    
	    // Prepare the new distribution
	    TH1F *ginterpnew, *ginterpprev;
	    ginterpprev = 0; 
	    ostringstream histname;
	    TString hname;
	    histname.seekp(0);
	    
	    TString iname(&hdf1->GetName()[5]);
	    iname+="_inter_";
	    iname+=Form("%i",(int)((higgsMassesResult[imass])*10.));
	    histname << iname;// << j;
	    hname = histname.str();
	    ginterpnew=(TH1F *)gROOT->FindObject(hname);
	    if (ginterpnew) delete ginterpnew; 
	    ginterpnew = (TH1F *)th1fmorph((const Char_t *)(hname.Data()),""
					   ,hdf1,hdf2,0.,1.,position,0.,0);
	    //std::cout << higgsMassesResult[imass] <<"\t"<< higgsMassesGGF[i]<<"\t"<<higgsMassesGGF[i+1]<<"\t"<<position<<std::endl;
	    ginterpnew->Draw("same");
	    // Delete the previous disttribution
	    //if (ginterpprev) delete ginterpprev;
	    // Swap what is new and previous for the next iteration
	    ginterpprev = ginterpnew;
	    //c2->Update();
	    //gSystem->Sleep(0010);
	    gg->cd();
	    
	    for(int kk = 0;kk<ginterpnew->GetNbinsX();kk++)
	      {
		if(ginterpnew->GetBinContent(kk)<0.)
		  {
		    //std::cout << ginterpnew->GetBinContent(kk)<<std::endl;
		    ginterpnew->SetBinContent(kk,0.);
		  }
	      }
	    double scalenew = ginterpnew->Integral();
	    ginterpnew->Scale(1./scalenew);
	    
	    double newnorm = norm[iprod][i] + (norm[iprod][i+1]-norm[iprod][i])*position;
	    
	    std::cout << higgsMassesResult[imass]<<"\t"<<newnorm<<std::endl;
	    ginterpnew->Scale(newnorm);
	    ginterpnew->Write();         
	  }
	  if(higgsMassesResult[imass]<150.)
	    {
	      TH1F *hdf1  =hist[iprod][1][i];
	      TH1F *hdf2  =hist[iprod][1][i+1];
	      double position = (higgsMassesResult[imass] - (*(masses[iprod]))[i])/((*(masses[iprod]))[i+1] - (*(masses[iprod]))[i]);
	      
	      // Prepare the new distribution
	      TH1F *ginterpnew, *ginterpprev;
	      ginterpprev = 0; 
	      ostringstream histname;
	      TString hname;
	      histname.seekp(0);
	      
	      TString iname(&hdf1->GetName()[5]);
	      iname+="_inter_";
	      iname+=Form("%i",(int)((higgsMassesResult[imass])*10.));
	      histname << iname;// << j;
	      hname = histname.str();
	      ginterpnew=(TH1F *)gROOT->FindObject(hname);
	      if (ginterpnew) delete ginterpnew; 
	      ginterpnew = (TH1F *)th1fmorph((const Char_t *)(hname.Data()),""
					     ,hdf1,hdf2,0.,1.,position,0.,0);
	      //std::cout << higgsMassesResult[imass] <<"\t"<< higgsMassesGGF[i]<<"\t"<<higgsMassesGGF[i+1]<<"\t"<<position<<std::endl;
	      ginterpnew->Draw("same");
	      // Delete the previous disttribution
	      //if (ginterpprev) delete ginterpprev;
	      // Swap what is new and previous for the next iteration
	      ginterpprev = ginterpnew;
	      //c2->Update();
	      //gSystem->Sleep(0010);
	      gg->cd();
	      
	      for(int kk = 0;kk<ginterpnew->GetNbinsX();kk++)
		{
		  if(ginterpnew->GetBinContent(kk)<0.)
		    {
		      //std::cout << ginterpnew->GetBinContent(kk)<<std::endl;
		      ginterpnew->SetBinContent(kk,0.);
		    }
		}
	      double scalenew = ginterpnew->Integral();
	      ginterpnew->Scale(1./scalenew);
	      
	      double newnorm = norm[iprod][i] + (norm[iprod][i+1]-norm[iprod][i])*position;
	      
	      std::cout << higgsMassesResult[imass]<<"\t"<<newnorm<<std::endl;
	      ginterpnew->Scale(newnorm);
	      ginterpnew->Write();         
	    }
	  else
	    {
	      TH1F *hdf1  =hist[iprod][1][i];
	      ostringstream histname;
	      TString hname;
	      histname.seekp(0);
	      
	      TString iname(&hdf1->GetName()[5]);
	      iname+="_inter_";
	      iname+=Form("%i",(int)((higgsMassesResult[imass])*10.));
	      histname << iname;// << j;
	      std::cout<<"##### "<< iname<<std::endl;
	      TH1F*dummy = (TH1F*) hdf1->Clone(iname);
	      dummy->Write();
	      
	    }
	  if(higgsMassesResult[imass]<150.)
	    {
	      TH1F *hdf1  =hist[iprod][2][i];
	      TH1F *hdf2  =hist[iprod][2][i+1];
	      double position = (higgsMassesResult[imass] - (*(masses[iprod]))[i])/((*(masses[iprod]))[i+1] - (*(masses[iprod]))[i]);
	      
	      // Prepare the new distribution
	      TH1F *ginterpnew, *ginterpprev;
	      ginterpprev = 0; 
	      ostringstream histname;
	      TString hname;
	      histname.seekp(0);
	      
	      TString iname(&hdf1->GetName()[5]);
	      iname+="_inter_";
	      iname+=Form("%i",(int)((higgsMassesResult[imass])*10.));
	      histname << iname;// << j;
	      hname = histname.str();
	      ginterpnew=(TH1F *)gROOT->FindObject(hname);
	      if (ginterpnew) delete ginterpnew; 
	      ginterpnew = (TH1F *)th1fmorph((const Char_t *)(hname.Data()),""
					     ,hdf1,hdf2,0.,1.,position,0.,0);
	      //std::cout << higgsMassesResult[imass] <<"\t"<< higgsMassesGGF[i]<<"\t"<<higgsMassesGGF[i+1]<<"\t"<<position<<std::endl;
	      ginterpnew->Draw("same");
	      // Delete the previous disttribution
	      //if (ginterpprev) delete ginterpprev;
	      // Swap what is new and previous for the next iteration
	      ginterpprev = ginterpnew;
	      //c2->Update();
	      //gSystem->Sleep(0010);
	      gg->cd();
	      
	      for(int kk = 0;kk<ginterpnew->GetNbinsX();kk++)
		{
		  if(ginterpnew->GetBinContent(kk)<0.)
		    {
		      //std::cout << ginterpnew->GetBinContent(kk)<<std::endl;
		      ginterpnew->SetBinContent(kk,0.);
		    }
		}
	      double scalenew = ginterpnew->Integral();
	      ginterpnew->Scale(1./scalenew);
	      
	      double newnorm = norm[iprod][i] + (norm[iprod][i+1]-norm[iprod][i])*position;
	      
	      std::cout << higgsMassesResult[imass]<<"\t"<<newnorm<<std::endl;
	      ginterpnew->Scale(newnorm);
	      ginterpnew->Write();         
	    }
	  else
	    {
	      TH1F *hdf1  =hist[iprod][2][i];
	      ostringstream histname;
	      TString hname;
	      histname.seekp(0);
	      
	      TString iname(&hdf1->GetName()[5]);
	      iname+="_inter_";
	      iname+=Form("%i",(int)((higgsMassesResult[imass])*10.));
	      histname << iname;// << j;
	      std::cout<<"##### "<< iname<<std::endl;
	      TH1F*dummy = (TH1F*)hdf1->Clone(iname);
	      dummy->Write();
	      
	    }

	}
    }
  return 0;
}
#endif

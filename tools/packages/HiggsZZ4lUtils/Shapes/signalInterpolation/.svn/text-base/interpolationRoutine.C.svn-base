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
int interpolate(int type);
int main()
{
  interpolate(0);
  interpolate(1);
  interpolate(2);
  interpolate(3);
  return 0;
}
int interpolate(int type)
{
  TString filename("interpolationInputsZmass.root");
  //TString filename("__yields_tmp_outfile.root");
  std::vector<double> higgsMassesGGF;
  for(double mass=110.;mass<=200;mass+=5.)
    higgsMassesGGF.push_back(mass);
  //higgsMassesGGF.push_back(210.);
  for(double mass=220.;mass<=600;mass+=20.)
    {
      if(fabs(mass-240.)<1. || fabs(mass-360.)<1. || fabs(mass-380.)<1 || fabs(mass-540.)<1. || fabs(mass-560.)<1.)
	continue;
      higgsMassesGGF.push_back(mass);
    }

  std::vector<double> higgsMassesVBF;
  for(double mass=110.;mass<=200;mass+=5.)
    higgsMassesVBF.push_back(mass);
  //higgsMassesVBF.push_back(210.);
  for(double mass=220.;mass<=600;mass+=20.)
    higgsMassesVBF.push_back(mass);

  std::vector<double> higgsMassesWH;
  for(double mass=110.;mass<=200;mass+=5.)
    higgsMassesWH.push_back(mass);
  //higgsMassesWH.push_back(210.);
  for(double mass=220.;mass<=300;mass+=20.)
    higgsMassesWH.push_back(mass);

  std::vector<double> higgsMassesZH;
  /**
  for(double mass=110.;mass<=200;mass+=5.)
    higgsMassesZH.push_back(mass);
  higgsMassesZH.push_back(210.);
  for(double mass=220.;mass<=300;mass+=20.)
    higgsMassesZH.push_back(mass);
  **/
  //std::vector<TFile*> file;
  std::vector<TH1F*> hist;
  //std::vector<TH1F*> histESU;
  //std::vector<TH1F*> histESD;
  std::vector<double> norm;
  std::vector<double> norm2;
  //std::vector<TFile*> fileVBF;
  std::vector<TH1F*> histVBF;
  //std::vector<TH1F*> histVBFESU;
  //std::vector<TH1F*> histVBFESD;
  std::vector<double> normVBF;
  std::vector<double> normVBF2;
  //std::vector<TFile*> fileWH;
  std::vector<TH1F*> histWH;
  std::vector<double> normWH;
  std::vector<double> normWH2;
  //std::vector<TFile*> fileZH;
  std::vector<TH1F*> histZH;
  std::vector<double> normZH;
  std::vector<double> normZH2;

  //// GGF
  TFile*f=new TFile(filename,"READ");
  for(unsigned int i=0;i<higgsMassesGGF.size();i++)
    {
      TString hname("");
      hname+=Form("%i",(int)(higgsMassesGGF[i]*10.));
      hname+="_higgs_";
      hname+=(int)type;
      //std::cout << hname<<std::endl;
      //std::cout << (TH1F*)f->Get(hname)<<std::endl;
      if(!f->Get(hname))
	{
	  std::cout << higgsMassesGGF[i]<<std::endl;
	  continue;
	}
      //continue;
      hist.push_back((TH1F*)f->Get(hname));      
      //TString hname1("ntuple_mc_powhegzz4lhistoHiggsElectronEnergyScale0");
      //hname1+=(int)type;
      //histESU.push_back((TH1F*)file[i]->Get(hname1));      
      //TString hname2("ntuple_mc_powhegzz4lhistoHiggsElectronEnergyScale1");
      //hname2+=(int)type;
      //histESD.push_back((TH1F*)file[i]->Get(hname2));      
      norm.push_back(hist[i]->Integral());
      hist[i]->Scale(1./norm[i]);
      //histESU[i]->Scale(1./norm[i]);
      //histESD[i]->Scale(1./norm[i]);
      norm2.push_back(hist[i]->Integral());
      std::cout << "ggF : "<< higgsMassesGGF[i]<<"\t"<<hist[i]<<"\t"<<norm[i]<<"\t"<<norm2[i]<<std::endl;
    }
  for(unsigned int i=0;i<higgsMassesVBF.size();i++)
    {
      TString hname("");
      hname+=Form("%i",(int)(higgsMassesVBF[i]*10.));
      hname+="_higgsVBF_";
      hname+=(int)type;

      if(!f->Get(hname))
        {
	  std::cout << higgsMassesVBF[i]<<std::endl;
          continue;
        }
      histVBF.push_back((TH1F*)f->Get(hname));      
      
      //TString hname1("ntuple_mc_powhegzz4lhistoHiggsElectronEnergyScale0");
      //hname1+=(int)type;
      //histESU.push_back((TH1F*)file[i]->Get(hname1));      
      //TString hname2("ntuple_mc_powhegzz4lhistoHiggsElectronEnergyScale1");
      //hname2+=(int)type;
      //histESD.push_back((TH1F*)file[i]->Get(hname2));      
      normVBF.push_back(histVBF[i]->Integral());
      histVBF[i]->Scale(1./normVBF[i]);
      //histESU[i]->Scale(1./normVBF[i]);
      //histESD[i]->Scale(1./normVBF[i]);
      normVBF2.push_back(histVBF[i]->Integral());
      std::cout << "VBF : "<< higgsMassesVBF[i]<<"\t"<<histVBF[i]<<"\t"<<normVBF[i]<<"\t"<<normVBF2[i]<<std::endl;
    }
  for(unsigned int i=0;i<higgsMassesWH.size();i++)
    {
      TString hname("");
      hname+=Form("%i",(int)(higgsMassesWH[i]*10.));
      hname+="_higgsWH_";
      hname+=(int)type;

      if(!f->Get(hname))
        {
	  std::cout << higgsMassesWH[i]<<std::endl;
          continue;
        }
      histWH.push_back((TH1F*)f->Get(hname));      
      
      normWH.push_back(histWH[i]->Integral());
      histWH[i]->Scale(1./normWH[i]);
      normWH2.push_back(histWH[i]->Integral());
      std::cout << "WH : "<< higgsMassesWH[i]<<"\t"<<histWH[i]<<"\t"<<normWH[i]<<"\t"<<normWH2[i]<<std::endl;
    }

  for(unsigned int i=0;i<higgsMassesZH.size();i++)
    {
      TString hname("");
      hname+=Form("%i",(int)(higgsMassesZH[i]*10.));
      hname+="_higgsZH_";
      hname+=(int)type;

      if(!f->Get(hname))
        {
	  std::cout << higgsMassesZH[i]<<std::endl;
          continue;
        }
      histZH.push_back((TH1F*)f->Get(hname));      
      
      normZH.push_back(histZH[i]->Integral());
      histZH[i]->Scale(1./normZH[i]);
      normZH2.push_back(histZH[i]->Integral());
      std::cout <<"ZH  : "<< higgsMassesZH[i]<<"\t"<<histZH[i]<<"\t"<<normZH[i]<<"\t"<<normZH2[i]<<std::endl;
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

  //double space = 1.;
  //TCanvas*c2=new TCanvas();
  //hist[0]->GetXaxis()->SetRangeUser(100.,800.);
  //hist[0]->GetXaxis()->SetTitle("m_{4l}");
  //hist[0]->GetYaxis()->SetTitle("1/GeV");
  //hist[0]->Draw();

  unsigned int i=0;
  for(unsigned int imass=0;imass<higgsMassesResult.size();imass++)
    {
      if(higgsMassesGGF[higgsMassesGGF.size()-1]<higgsMassesResult[imass])
	continue;
      for(i=0;i<higgsMassesGGF.size();i++)
	if(higgsMassesGGF[i]>higgsMassesResult[imass])
	  break;
      i--;
      if(i==higgsMassesGGF.size()-1)
	i--;
  
      {
	TH1F *hdf1  =hist[i];
	TH1F *hdf2  =hist[i+1];
	hdf1->Draw("same");
	hdf2->SetLineColor(i+1);
	hdf2->Draw("same");     
	double position = (higgsMassesResult[imass] - higgsMassesGGF[i])/(higgsMassesGGF[i+1] - higgsMassesGGF[i]);
	
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

	double newnorm = norm[i] + (norm[i+1]-norm[i])*position;

	//std::cout << higgsMassesResult[imass]<<"\t"<<newnorm<<std::endl;
	ginterpnew->Scale(newnorm);
	ginterpnew->Write();         

      }

      //////
      /*
      {
      TH1F *hdf1  =histESU[i];
      TH1F *hdf2  =histESU[i+1];
      hdf1->Draw("same");
      hdf2->SetLineColor(i+1);
      hdf2->Draw("same");     
      double position = (higgsMassesResult[imass] - higgsMassesGGF[i])/(higgsMassesGGF[i+1] - higgsMassesGGF[i]);
      
      // Prepare the new distribution
      TH1F *ginterpnew, *ginterpprev;
      ginterpprev = 0; 
      ostringstream histname;
      TString hname;
      histname.seekp(0);
      TString iname(hdf1->GetName());
      iname+="inter_";
      iname+=Form("%i",(int)((higgsMassesResult[imass])*10.));
      histname << iname;// << j;
      hname = histname.str();
      ginterpnew=(TH1F *)gROOT->FindObject(hname);
      if (ginterpnew) delete ginterpnew; 
      ginterpnew = (TH1F *)th1fmorph((Char_t *)hname,""
				     ,hdf1,hdf2,0.,1.,position,0.,0);
      std::cout << higgsMassesResult[imass] <<"\t"<< higgsMassesGGF[i]<<"\t"<<higgsMassesGGF[i+1]<<"\t"<<position<<std::endl;
      ginterpnew->Draw("same");
      // Delete the previous disttribution
      //if (ginterpprev) delete ginterpprev;
      // Swap what is new and previous for the next iteration
      ginterpprev = ginterpnew;
      c2->Update();
      //gSystem->Sleep(0010);
      gg->cd();
      
      double newnorm = norm[i] + (norm[i+1]-norm[i])*position;
      ginterpnew->Scale(newnorm);
      ginterpnew->Write();         
      }
      */
      //////
      /*
	{
      TH1F *hdf1  =histESD[i];
      TH1F *hdf2  =histESD[i+1];
      hdf1->Draw("same");
      hdf2->SetLineColor(i+1);
      hdf2->Draw("same");     
      double position = (higgsMassesResult[imass] - higgsMassesGGF[i])/(higgsMassesGGF[i+1] - higgsMassesGGF[i]);
      
      // Prepare the new distribution
      TH1F *ginterpnew, *ginterpprev;
      ginterpprev = 0; 
      ostringstream histname;
      TString hname;
      histname.seekp(0);
      TString iname(hdf1->GetName());
      iname+="inter_";
      iname+=Form("%i",(int)((higgsMassesResult[imass])*10.));
      histname << iname;// << j;
      hname = histname.str();
      ginterpnew=(TH1F *)gROOT->FindObject(hname);
      if (ginterpnew) delete ginterpnew; 
      ginterpnew = (TH1F *)th1fmorph((Char_t *)hname,""
				     ,hdf1,hdf2,0.,1.,position,0.,0);
      std::cout << higgsMassesResult[imass] <<"\t"<< higgsMassesGGF[i]<<"\t"<<higgsMassesGGF[i+1]<<"\t"<<position<<std::endl;
      ginterpnew->Draw("same");
      // Delete the previous disttribution
      //if (ginterpprev) delete ginterpprev;
      // Swap what is new and previous for the next iteration
      ginterpprev = ginterpnew;
      c2->Update();
      //gSystem->Sleep(0010);
      gg->cd();
      
      double newnorm = norm[i] + (norm[i+1]-norm[i])*position;
      ginterpnew->Scale(newnorm);
      ginterpnew->Write();         
      }

      */
    }

  ////// VBF
  /*unsigned int */i=0;
  for(unsigned int imass=0;imass<higgsMassesResult.size();imass++)
    {
      if(higgsMassesVBF[higgsMassesVBF.size()-1]<higgsMassesResult[imass])
	continue;

      for(i=0;i<higgsMassesVBF.size();i++)
	if(higgsMassesVBF[i]>higgsMassesResult[imass])
	  break;
      i--;
      if(i==higgsMassesVBF.size()-1)
	i--;

      TH1F *hdf1  =histVBF[i];
      TH1F *hdf2  =histVBF[i+1];
      hdf1->Draw("same");
      hdf2->SetLineColor(i+1);
      hdf2->Draw("same");     
      double position = (higgsMassesResult[imass] - higgsMassesVBF[i])/(higgsMassesVBF[i+1] - higgsMassesVBF[i]);
      
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
      //std::cout << higgsMassesResult[imass] <<"\t"<< higgsMassesVBF[i]<<"\t"<<higgsMassesVBF[i+1]<<"\t"<<position<<std::endl;
      // Draw the new distribution.
      ginterpnew->Draw("same");
      // Delete the previous disttribution
      //if (ginterpprev) delete ginterpprev;
      // Swap what is new and previous for the next iteration
      ginterpprev = ginterpnew;
      //c2->Update();
      //gSystem->Sleep(0010);
      gg->cd();
      
      //double newnorm = normVBF[i] + (normVBF[i+1]-normVBF[i])*position;
      //ginterpnew->Scale(newnorm);
      //ginterpnew->Write();
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
          
      double newnorm = normVBF[i] + (normVBF[i+1]-normVBF[i])*position;
      ginterpnew->Scale(newnorm);
      ginterpnew->Write();
    }
  ////// WH
  /*unsigned int */i=0;
  for(unsigned int imass=0;imass<higgsMassesResult.size();imass++)
    {
      if(higgsMassesWH[higgsMassesWH.size()-1]<higgsMassesResult[imass])
	continue;

      for(i=0;i<higgsMassesWH.size();i++)
	if(higgsMassesWH[i]>higgsMassesResult[imass])
	  break;
      i--;
      if(i==higgsMassesWH.size()-1)
	i--;

      TH1F *hdf1  =histWH[i];
      TH1F *hdf2  =histWH[i+1];
      hdf1->Draw("same");
      hdf2->SetLineColor(i+1);
      hdf2->Draw("same");     
      double position = (higgsMassesResult[imass] - higgsMassesWH[i])/(higgsMassesWH[i+1] - higgsMassesWH[i]);
      
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
      //std::cout << higgsMassesResult[imass] <<"\t"<< higgsMassesWH[i]<<"\t"<<higgsMassesWH[i+1]<<"\t"<<position<<std::endl;
      // Draw the new distribution.
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

      double newnorm = normWH[i] + (normWH[i+1]-normWH[i])*position;
      std::cout << "###### "<<  higgsMassesResult[imass] <<"\t"<< newnorm<<std::endl;
      ginterpnew->Scale(newnorm);
      ginterpnew->Write();
    }
  ////// ZH
  /*unsigned int */i=0;
  for(unsigned int imass=0;imass<higgsMassesResult.size();imass++)
    {
      if(higgsMassesZH.size()==0)
	continue;
      if(higgsMassesZH[higgsMassesZH.size()-1]<higgsMassesResult[imass])
	continue;

      for(i=0;i<higgsMassesZH.size();i++)
	if(higgsMassesZH[i]>higgsMassesResult[imass])
	  break;
      i--;
      if(i==higgsMassesZH.size()-1)
	i--;

      TH1F *hdf1  =histZH[i];
      TH1F *hdf2  =histZH[i+1];
      hdf1->Draw("same");
      hdf2->SetLineColor(i+1);
      hdf2->Draw("same");     
      double position = (higgsMassesResult[imass] - higgsMassesZH[i])/(higgsMassesZH[i+1] - higgsMassesZH[i]);
      
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
      //std::cout << higgsMassesResult[imass] <<"\t"<< higgsMassesZH[i]<<"\t"<<higgsMassesZH[i+1]<<"\t"<<position<<std::endl;
      // Draw the new distribution.
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
    
      double newnorm = normZH[i] + (normZH[i+1]-normZH[i])*position;
      ginterpnew->Scale(newnorm);
      ginterpnew->Write();
          
    }
  gg->Close();

  return 0;
}
#endif

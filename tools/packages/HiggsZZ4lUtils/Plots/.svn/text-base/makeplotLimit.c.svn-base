//////////////////////
// Plot Limits 
//
//
#include "utils.h"
int limit(const char* inname, const char* outname,int year = 2012, bool doCmp= true, const char* logname="")
{
  //TString wsDirName("standard_v1");
  //TString wsDirName("z_mass_constraint_v1");
  //TString baseDirName("/xdata05/xju/H_4L/Limits/ICHEP2012/V2");
  //
  //TString wsDirName("z_mass_constraint_v2_2012");
  //TString wsDirName("standard_v4_2011");
  //TString wsDirName("z_mass_constraint_v4_2011");
  //TString wsDirName("z_mass_constraint_2011_2012_v4");
  TString wsDirName(outname);

  //TString wsDirName("z_mass_constraint_v2_2012");
  //TString wsDirName("z_mass_constraint_v2_2011");
  //TString wsDirName("z_mass_constraint_v1_combined");
  TString baseDirName("/xdata05/xju/H_4L/Limits/ICHEP2012/V8/");

  std::vector<double> mass_new, oLt_new,eLt_new, sig2mLt_new,sig1mLt_new,sig1pLt_new,sig2pLt_new;
  //fstream filestr0 ("Limit_v2/NoZMassConstraint_limit.txt", fstream::in); //nominal Limit
  //fstream filestr0 ("limit/FirstTry2012_limit.txt", fstream::in); //nominal Limit
  fstream filestr0 (Form("%s/%s_limit.txt",baseDirName.Data(),wsDirName.Data()), fstream::in); //nominal Limit

  do
   {
     double mm,oo,m2,m1,ee,p1,p2;
     //filestr0 >> mm>> oo>> m2>>m1>>ee>>p1>>p2;
     filestr0 >> mm>> m2>>m1>>ee>>p1>>p2>>oo;
     //std::cerr<<mm<<"\t"<< oo<<"\t"<<m2<<"\t"<<m1<<"\t"<<ee<<"\t"<<p1<<"\t"<<p2<<"\n";
     mass_new.push_back(mm/10.);
     oLt_new.push_back(oo);
     eLt_new.push_back(ee);
     sig2mLt_new.push_back(m2);
     sig1mLt_new.push_back(m1);
     sig1pLt_new.push_back(p1);
     sig2pLt_new.push_back(p2);
   }
  while(!filestr0.eof());
  filestr0.close();
  const int nmass_new=mass_new.size();//-1;

  std::vector<double> oLt,eLt,mass4,sig2mLt,sig1mLt,sig1pLt,sig2pLt;
  fstream filestr (inname, fstream::in); //Used to do comparison
  do
   {
     double mm,oo,m2,m1,ee,p1,p2;
     //filestr >> mm>> oo>> m2>>m1>>ee>>p1>>p2;
     filestr >> mm>> m2>>m1>>ee>>p1>>p2>>oo;
     //std::cerr<<mm<<"\t"<< oo<<"\t"<<m2<<"\t"<<m1<<"\t"<<ee<<"\t"<<p1<<"\t"<<p2<<"\n";
     mass4.push_back(mm/10.);
     oLt.push_back(oo);
     eLt.push_back(ee);
     sig2mLt.push_back(m2);
     sig1mLt.push_back(m1);
     sig1pLt.push_back(p1);
     sig2pLt.push_back(p2);
   }
  while(!filestr.eof());
  filestr.close();
  const int nmass4=mass4.size();//-1;

  // LOUIS TOYS
  double asymmerrors4[2][2][nmass4]={0.};
  for(int i=0;i<mass4.size();i++)
    {
      asymmerrors4[0][1][i]=sig1pLt[i]-eLt[i];
      asymmerrors4[0][0][i]=eLt[i]-sig1mLt[i];
      asymmerrors4[1][1][i]=sig2pLt[i]-eLt[i];
      asymmerrors4[1][0][i]=eLt[i]-sig2mLt[i];
      for(int j=0;j<2;j++)
	for(int k=0;k<2;k++)
	  if(asymmerrors4[j][k][i]<0.)
	    asymmerrors4[j][k][i]=0.000001;
      //std::cout << mass[i]<<"\t"<< obser[i]<<"\t"<<expec[i]<<std::endl;
    }
  double asymmerrors_new[2][2][nmass_new]={0.};
  for(int i=0;i<mass_new.size();i++)
    {
      asymmerrors_new[0][1][i]=sig1pLt_new[i]-eLt_new[i];
      asymmerrors_new[0][0][i]=eLt_new[i]-sig1mLt_new[i];
      asymmerrors_new[1][1][i]=sig2pLt_new[i]-eLt_new[i];
      asymmerrors_new[1][0][i]=eLt_new[i]-sig2mLt_new[i];
      for(int j=0;j<2;j++)
	for(int k=0;k<2;k++)
	  if(asymmerrors_new[j][k][i]<0.)
	    asymmerrors_new[j][k][i]=0.000001;
    }
 

 double zeroerror[1000]={0.};
 TGraph*groLt=new TGraph(nmass4,&mass4[0],&oLt[0]);groLt->SetLineWidth(2);groLt->SetLineStyle(1);groLt->SetMarkerStyle(20);//groLt->SetLineColor(2);
 TGraph*greLt=new TGraph(nmass4,&mass4[0],&eLt[0]);greLt->SetLineWidth(2);greLt->SetLineStyle(2);greLt->SetLineStyle(2);//greLt->SetLineColor(2);

 TGraph*groLt_new=new TGraph(nmass_new,&mass_new[0],&oLt_new[0]);groLt_new->SetLineWidth(2);groLt_new->SetLineStyle(1);groLt_new->SetMarkerStyle(20);
 TGraph*greLt_new=new TGraph(nmass_new,&mass_new[0],&eLt_new[0]);greLt_new->SetLineWidth(2);greLt_new->SetLineStyle(2);greLt_new->SetLineStyle(2);
 

  TGraphAsymmErrors*gre1Lt=new TGraphAsymmErrors(nmass4,&mass4[0],&eLt[0],zeroerror,zeroerror,&asymmerrors4[0][0][0],&asymmerrors4[0][1][0]);gre1Lt->SetFillColor(kGreen);gre1Lt->SetFillStyle(1001);
  TGraphAsymmErrors*gre2Lt=new TGraphAsymmErrors(nmass4,&mass4[0],&eLt[0],zeroerror,zeroerror,&asymmerrors4[1][0][0],&asymmerrors4[1][1][0]);gre2Lt->SetFillColor(kYellow);gre2Lt->SetFillStyle(1001);
  TGraphAsymmErrors*gre1Lt_new=new TGraphAsymmErrors(nmass_new,&mass_new[0],&eLt_new[0],zeroerror,zeroerror,&asymmerrors_new[0][0][0],&asymmerrors_new[0][1][0]);gre1Lt_new->SetFillColor(kGreen);gre1Lt_new->SetFillStyle(1001);
  TGraphAsymmErrors*gre2Lt_new=new TGraphAsymmErrors(nmass_new,&mass_new[0],&eLt_new[0],zeroerror,zeroerror,&asymmerrors_new[1][0][0],&asymmerrors_new[1][1][0]);gre2Lt_new->SetFillColor(kYellow);gre2Lt_new->SetFillStyle(1001);
  TH2F*dummy=new TH2F("dummy",";m_{H} [GeV];95% CL limit on #sigma/#sigma_{SM}",500,100.,600,3000,0.0,300);
  TCanvas*c1=new TCanvas("c1","",600,600);
  c1->SetLogy();
  c1->SetMargin(0.13,0.05,0.12,0.05);

  TLegend*leg0=new TLegend(0.30,0.42,0.63,0.62); 
  leg0->SetFillColor(0);
  leg0->SetLineColor(0);
  leg0->SetTextFont(42);
  leg0->SetTextSize(0.04);
  //leg0->SetHeader("H#rightarrow ZZ^{(*)}#rightarrow llll");
  //leg0->SetHeader("H#rightarrow ZZ^{(*)}#rightarrow 4l");
  leg0->AddEntry(groLt_new,"Observed #it{CL}_{s}","l");
  leg0->AddEntry(greLt_new,"Expected #it{CL}_{s}","l");
  leg0->AddEntry(gre1Lt_new,"#pm 1 #sigma","f");
  leg0->AddEntry(gre2Lt_new,"#pm 2 #sigma","f");
  if(doCmp){
    leg0->AddEntry(groLt,Form("Observed #it{CL}_{s} %s",logname),"l");
    leg0->AddEntry(greLt,Form("Expected #it{CL}_{s} %s",logname),"l");
  }
  leg0->Draw();

  dummy->GetXaxis()->SetRangeUser(110.,600.);
  dummy->GetYaxis()->SetTitleOffset(1.25);
  dummy->GetXaxis()->SetLabelOffset(0.015);
  dummy->GetXaxis()->SetTitleOffset(1.1);
  dummy->GetXaxis()->SetNdivisions(505);
  dummy->Draw();

  //gre2Lt->Draw("3");
  //gre1Lt->Draw("3");
  gre2Lt_new->Draw("3");
  gre1Lt_new->Draw("3");
  groLt_new->Draw("L");
  greLt_new->Draw("L");
  groLt->SetLineColor(2);//Draw("L");
  greLt->SetLineColor(2);//Draw("L");
  if(doCmp){
    groLt->Draw("L");
    greLt->Draw("L");
  }

  //TLatex*tex = new TLatex(0.76,0.955,"#surds=7 TeV");
  //tex->SetNDC(kTRUE);
  //tex->SetTextFont(42);
  //tex->SetTextSize(0.05);
  //tex->Draw();

  TLatex l; //l.SetTextAlign(12); l.SetTextSize(tsize); 
  l.SetNDC();
  l.SetTextFont(42);
  l.SetTextSize(0.04);//42);
  l.SetTextColor(1);
  l.SetTextAlign(12);
  //l.DrawLatex(0.60,0.45,"ATLAS Preliminary");
  //l.DrawLatex(0.30,0.87,"ATLAS Internal");
  TLatex* l1 = l.DrawLatex(0.30,0.87,"#bf{#it{ATLAS}} Preliminary");//:Preliminary");
  //TLatex* l1 = l.DrawLatex(0.37,0.87,"#bf{#it{ATLAS}}");// Preliminary");//Internal");//:Preliminary");
  TLatex* l2 = l.DrawLatex(0.30,0.81,"H#rightarrow ZZ^{(*)}#rightarrow 4l");

  //TLatex* l3 = l.DrawLatex(0.30,0.74,"#lower[-0.15]{#scale[0.6]{#int}}Ldt = 4.8 fb^{-1}");
  //TLatex* l4 = l.DrawLatex(0.30,0.68,"#sqrt{s}=7 TeV");

  TLatex* l3;
  TLatex* l4; 
  if(year == 2012){
    l3 = l.DrawLatex(0.30,0.74,"#lower[-0.15]{#scale[0.6]{#int}}Ldt =5.8 fb^{-1}");
    l4 = l.DrawLatex(0.30,0.68,"#sqrt{s}=8 TeV");
  }else if(year == 2011){
    l3 = l.DrawLatex(0.30,0.74,"#lower[-0.15]{#scale[0.6]{#int}}Ldt = 4.8 fb^{-1}");
    l4 = l.DrawLatex(0.30,0.68,"#sqrt{s}=7 TeV");
  }else{
    l3 = l.DrawLatex(0.25,0.74,"#sqrt{s}=7 TeV: #lower[-0.15]{#scale[0.6]{#int}}Ldt =4.8 fb^{-1}");
    l4 = l.DrawLatex(0.25,0.68,"#sqrt{s}=8 TeV: #lower[-0.15]{#scale[0.6]{#int}}Ldt =5.8 fb^{-1}");
  }
  //
  TLine *line = new TLine(110,1.,600,1.);
  line->SetLineStyle(2);
  line->SetLineWidth(2);
  line->Draw();
  c1->SetLogy(kFALSE);
  dummy->GetYaxis()->SetRangeUser(0.,19.999);
  dummy->Draw("sameaxis");
  //(gPad->RedrawAxis());

  TLatex* tck=new TLatex();
  tck->SetNDC();
  tck->SetTextFont(42);
  tck->SetTextSize(0.05);
  TLatex* tck0=tck->DrawLatex(0.095,0.065,"110");//tck->DrawLatex(0.095,0.075,"110");
  //tck->DrawLatex(142,-1.75,"150");

  c1->Update();
  c1->Print(Form("%s.eps",outname));
  //c1->Print(Form("%s.png",outname));
  c1->Print(Form("%s.cxx",outname));
  delete tck0;
  
  l1->SetX(0.29-0.11);//0.235
  l2->SetX(0.23-0.05);
  l3->SetX(0.23-0.05);
  l4->SetX(0.23-0.05);
  if(year == 2012 || year == 2011){
    l1->SetX(0.29);//0.235
    l2->SetX(0.29);
    l3->SetX(0.29);
    l4->SetX(0.29);
  }
  //leg0->SetY1NDC(0.65);
  //leg0->SetY2NDC(0.90);
  //leg0->SetX1NDC(0.525);
  //leg0->SetX2NDC(0.905);
  //
  leg0->SetY1(0.68);
  leg0->SetY2(0.90);
  leg0->SetX1(0.625);
  leg0->SetX2(0.905);
  //
  //leg0->SetX1NDC(0.55);
  //leg0->SetX2NDC(0.88);
  //leg0->SetY1NDC(0.70);
  //leg0->SetY2NDC(0.92);
  leg0->Draw();
  dummy->GetXaxis()->SetRangeUser(110.,179.9);
  //dummy->GetYaxis()->SetRangeUser(0.5,299.999);
  //dummy->GetYaxis()->SetRangeUser(0.2,49.999);
  dummy->GetYaxis()->SetRangeUser(0.01,99.999);
  dummy->GetXaxis()->SetNdivisions(510);
  line->SetX2(180.);
  line->SetX1(110.);
  c1->SetLogy(kTRUE);
  dummy->Draw("sameaxis");
  //(gPad->RedrawAxis());
  c1->Update();
  c1->Print(Form("%s_LowMass.eps",outname)); 
  c1->Print(Form("%s_LowMass.cxx",outname)); 
  //c1->Print(Form("%s_LowMass.png",outname));
  l1->SetX(0.29-0.11);//0.23
  l2->SetX(0.23-0.05);
  l3->SetX(0.23-0.05);
  l4->SetX(0.23-0.05);
  if(year == 2012 || year == 2011){
    l1->SetX(0.29);//0.235
    l2->SetX(0.29);
    l3->SetX(0.29);
    l4->SetX(0.29);
  }

  dummy->GetXaxis()->SetRangeUser(180.,599.9);
  //dummy->GetYaxis()->SetRangeUser(0.5,299.999);
  dummy->GetYaxis()->SetRangeUser(0.2,99.999);
  line->SetX1(180.);
  line->SetX2(600.);
  dummy->Draw("sameaxis");
  //  (gPad->RedrawAxis());
  c1->Update();
  c1->Print(Form("%s_HighMass.eps",outname));
  c1->Print(Form("%s_HighMass.cxx",outname));
  //c1->Print(Form("%s_HighMass.png",outname));

  
  dummy->GetXaxis()->SetRangeUser(110.,599.99);
  dummy->GetXaxis()->SetNdivisions(505);
  line->SetX1(110.);  
  line->SetX2(600.);
  c1->SetLogy(kFALSE);
  dummy->GetYaxis()->SetRangeUser(0.1,99.999);
  c1->SetLogy(kTRUE);
  
  leg0->Draw();

  dummy->Draw("sameaxis");//(gPad->RedrawAxis());    

  TLatex* tck=new TLatex();
  tck->SetNDC();
  tck->SetTextFont(42);
  tck->SetTextSize(0.05);
  TLatex* tck1=tck->DrawLatex(0.095,0.065,"110");//tck->DrawLatex(0.095,0.075,"110");
  //tck.DrawLatex(142,-1.75,"150");

  c1->Update();
  c1->Print(Form("%s_Log.eps",outname));
  c1->Print(Form("%s_Log.cxx",outname));
  //c1->Print(Form("%s_Log.png",outname));
  //c1->Print(Form("%s_Log.C",outname));
  return ;

  dummy->GetYaxis()->SetRangeUser(0.5,299.999);
  gre4mu->SetLineColor(2);
  gre2e2mu->SetLineColor(3);
  gre4e->SetLineColor(4);
  gre4mu->Draw("l");
  gre2e2mu->Draw("l");
  gre4e->Draw("l");
  leg0->AddEntry(gre4e,"4e","l");
  leg0->AddEntry(gre2e2mu,"2e2mu","l");
  leg0->AddEntry(gre4mu,"4mu","l");
  c1->Update();
  c1->Print("LimitChannels.eps");
  c1->Print("LimitChannels.png");


  return;

  dummy->GetXaxis()->SetRangeUser(120,450);
  dummy->GetYaxis()->SetRangeUser(0.5,4.99);
  c1->Update();
  c1->Print("LimitZoom.eps");
  return;
  double band[54]={0.};
  double band2[54]={0.};
  double bandmass[54]={0.};
  double limit[5][nmass]={0.};
  double asymmerrors[5][2][2][nmass]={0.};
  fstream file;
  file.open("fort7.nosyst"/*"limit_h4l_7TeV_nosyst.txt"*/, fstream::in);
  int count=0;
  do
    {
      double a,b,c,d,e,f;
      file>>a>>b>>c>>d>>e>>f;
      limit[0][count]=d;
      count++;
    }
  while(!file.eof());
  file.close();

  // 8% , 4% 30%
  file.open("limit_h4l_7TeV_theory.txt", fstream::in);
  count=0;
  do
    {
      double a,b,c,d,e,f;
      file>>a>>b>>c>>d>>e>>f;
      limit[1][count]=d;
      count++;
    }
  while(!file.eof());
  file.close();
  // 8% signal 45\% (Z=>ee/mumu)
  file.open("fort.54", fstream::in);
  count=0;
  do
    {
      double a,b,c,d,e,f;
      file>>a>>b>>c>>d>>e>>f;
      if(count<nmass)
	{
	  limit[2][count]=d;
	  asymmerrors[2][0][0][count]= d-c;
	  asymmerrors[2][0][1][count]= e-d;
	  asymmerrors[2][1][0][count]= d-b;
	  asymmerrors[2][1][1][count]= f-d;
	  band[count] = c;
	  band[53-count] = e;
	  band2[count] = b;
	  band2[53-count] = f;
	  bandmass[count]=masses2[count];
	  bandmass[53-count]=masses2[count];
	}
      //std::cout << count << " "<< 27-count << " "<<band[count] << " "<< bandmass[count] << "\t"<< band[27-count] << " "<< bandmass[27-count]<<std::endl;
      count++;
    }
  while(!file.eof());
  file.close();
  file.open("fortIdeal.54", fstream::in);
  count=0;
  do
    {
      double a,b,c,d,e,f;
      file>>a>>b>>c>>d>>e>>f;
      if(count<nmass)
	{
	  limit[3][count]=d;
	  /**	  asymmerrors[2][0][0][count]= d-c;
	  asymmerrors[2][0][1][count]= e-d;
	  asymmerrors[2][1][0][count]= d-b;
	  asymmerrors[2][1][1][count]= f-d;
	  band[count] = c;
	  band[53-count] = e;
	  band2[count] = b;
	  band2[53-count] = f;
	  bandmass[count]=masses2[count];
	  bandmass[53-count]=masses2[count];
	  */
	}
      //std::cout << count << " "<< 27-count << " "<<band[count] << " "<< bandmass[count] << "\t"<< band[27-count] << " "<< bandmass[27-count]<<std::endl;
      count++;
    }
  while(!file.eof());
  file.close();
  file.open("fortLC.54", fstream::in);
  count=0;
  do
    {
      double a,b,c,d,e,f;
      file>>a>>b>>c>>d>>e>>f;
      if(count<nmass)
	{
	  limit[4][count]=d;
	}
      //std::cout << count << " "<< 27-count << " "<<band[count] << " "<< bandmass[count] << "\t"<< band[27-count] << " "<< bandmass[27-count]<<std::endl;
      count++;
    }
  while(!file.eof());
  file.close();
  file.close();
  file.open("fortLCz2.54", fstream::in);
  count=0;
  do
    {
      double a,b,c,d,e,f;
      file>>a>>b>>c>>d>>e>>f;
      if(count<nmass)
	{
	  limit[1][count]=d;
	}
      //std::cout << count << " "<< 27-count << " "<<band[count] << " "<< bandmass[count] << "\t"<< band[27-count] << " "<< bandmass[27-count]<<std::endl;
      count++;
    }
  while(!file.eof());
  file.close();
  // with pseudo experiments 
  file.open("limit_h4l_7TeV_correlated.txt", fstream::in);
  count=0;
  do
    {
      double a,b,c,d,e,f;
      file>>a>>b>>c>>d>>e>>f;
      std::cout << d<<std::endl;
      //limit[3][count]=d;
      count++;
    }
  while(!file.eof());
  file.close();

  TGraph*gr[5];
  for(int i=1;i<5;i++)
    {
     if(i==2)
	{
	  for(int j=0;j<nmass;j++)
	    std::cout <<masses2[j]<< " "<<limit[i][j]<<std::endl;
	}
     gr[i]=new TGraph(nmass,masses2,&limit[i][0]);
     gr[i]->SetMarkerStyle(20+i);
    }
  double zeroerror[1000]={0.};
  TGraphAsymmErrors*gre1=new TGraphAsymmErrors(nmass,masses2,&limit[2][0],zeroerror,zeroerror,&asymmerrors[2][0][0][0],&asymmerrors[2][0][1][0]);gre1->SetFillColor(kYellow);gre1->SetFillStyle(1001);
  TGraphAsymmErrors*gre2=new TGraphAsymmErrors(nmass,masses2,&limit[2][0],zeroerror,zeroerror,&asymmerrors[2][1][0][0],&asymmerrors[2][1][1][0]);gre2->SetFillColor(kGreen);gre2->SetFillStyle(1001);
  //  TH2F*dummy=new TH2F("dummy",";m_{H} (GeV);95% CL limit/SM for 1 fb^{-1}",500,100.,600,2000,0.5,25.);
  TH2F*dummy=new TH2F("dummy",";m_{H} [GeV];95% CL limit/SM",500,100.,600,2000,0.5,1.e3);
  TCanvas*c1=new TCanvas("c1","",800,600);
  c1->SetLogy();
  c1->SetMargin(0.11,0.05,0.11,0.05);
  dummy->GetXaxis()->SetRangeUser(120.,600.);
  dummy->Draw();
  
  double bandHD[5300]={0.};
  double bandHD2[5300]={0.};
  double bandmassHD[5300]={0.};
  for(int i=0;i<nmass;i++)
    {
      for(int j=0;j<100;j++)
	{
	  //if(i==15 && j>0)
	  //continue;
	  bandmassHD[i*100+j] = bandmass[i]+(bandmass[i+1]-bandmass[i])/100.*j;
	  bandmassHD[5300-i*100-j] = bandmass[i]-(bandmass[i]-bandmass[i+1])/100.*j;
	  //std::cout << i << " "<< j << " "<< bandmassHD[i*100+j]<< " "<< bandmassHD[3200-i*100-j]<<std::endl;
	  //std::cout << i << " "<< j << " "<< bandmass[i+1]<< " "<< bandmass[i]<<std::endl;
	  if(i==26)
	    {
	      bandHD[i*100+j]= band[i];
	      bandHD2[i*100+j]= band2[i];
	      //bandHD[3100-i*100-j]= band[31-i];
	    }
	  else
	    {
	      bandHD[i*100+j] = band[i]*TMath::Exp(j/100.*TMath::Log(band[i+1]/band[i]));
	      //bandHD[i*100+j]=band[i]+(band[i+1]-band[i])/(bandmass[i+1]-bandmass[i])*(bandmassHD[i*100+j]-bandmass[i]);
	      bandHD[5300-i*100-j] = band[53-i]*TMath::Exp(j/100.*TMath::Log(band[52-i]/band[53-i]));
	      //bandHD[3100-i*100-j] = band[31-i]-band[31-i]/band[30-i]*exp((band[31-i]-band[30-i])/(bandmass[31-i]-bandmass[30-i])*(bandmass[31-i]-bandmassHD[3100-i*100-j]);
	      bandHD2[i*100+j] = band2[i]*TMath::Exp(j/100.*TMath::Log(band2[i+1]/band2[i]));
	      //bandHD2[i*100+j]=band2[i]+(band2[i+1]-band2[i])/(bandmass[i+1]-bandmass[i])*(bandmassHD[i*100+j]-bandmass[i]);
	      bandHD2[5300-i*100-j] = band2[53-i]*TMath::Exp(j/100.*TMath::Log(band2[52-i]/band2[53-i]));
	      //bandHD2[3100-i*100-j] = band[31-i]-band[31-i]/band[30-i]*exp((band[31-i]-band[30-i])/(bandmass[31-i]-bandmass[30-i])*(bandmass[31-i]-bandmassHD[3100-i*100-j]);
	      //std::cout << i << " "<< j << " "<< bandmassHD[i*100+j]<< " "<<bandHD[i*100+j]<<" (" << band[i] << " - "<< band[i+1]<<") "<< " "<< " " <<bandmassHD[3100-i*100-j]<< " "<<bandHD[3100-i*100-j]<<" (" << band[31-i] << " - "<< band[30-i]<<") "<<bandmass[31-i]<< " "<<bandmass[30-i]<<std::endl;
	    }
	}
      bandHD[2700]=bandHD[2699];
      bandHD2[2700]=bandHD2[2699];
    }
  for(int i=0;i<5300;i++)
    {
      //std::cout << bandmassHD[i]<<"\t"<< bandHD[i]<<std::endl;
      if(bandHD[i]>dummy->GetYaxis()->GetXmax())
	bandHD[i]=dummy->GetYaxis()->GetXmax();
      if(bandHD2[i]>dummy->GetYaxis()->GetXmax())
	bandHD2[i]=dummy->GetYaxis()->GetXmax();
    }
  //for(int i=0;i<3100;i++)
  //std::cout << i<<" "<< bandmassHD[i] << " "<< bandHD[i]<<std::endl;
  TPolyLine*marker2=new TPolyLine(5300,bandmassHD,bandHD2);
  //marker2->SetFillColor(8);
  //marker2->SetFillStyle(3001);
  marker2->SetFillColor(kYellow);
  marker2->SetFillStyle(1001);
  //marker2->Draw("f");
  TPolyLine*marker=new TPolyLine(5300,bandmassHD,bandHD);
  //marker->SetFillColor(32);
  //marker->SetFillStyle(3001);
  marker->SetFillColor(kGreen);
  marker->SetFillStyle(1001);
  //marker->Draw("f");
  TLine*line=new TLine(120,1.,600.,1);
  line->SetLineStyle(2);
  line->Draw();


  //for(int i=3;i>-1;i--)
  //{
  //gr[i]->SetLineColor(i+1);
  //gr[i]->Draw("l");
  //}
  //gr[0]->SetLineWidth(2);
  //gr[0]->SetLineStyle(2);
  //gr[0]->SetMarkerStyle(20);
  //gr[0]->Draw("l");
  //gre2->Draw("f");
  //gre1->Draw("f");
  gr[2]->SetLineWidth(2);
  gr[2]->SetLineStyle(1);
  gr[2]->SetMarkerStyle(24);
  gr[2]->Draw("l");
  gr[3]->SetLineWidth(2);
  gr[3]->SetLineStyle(2);
  gr[3]->SetMarkerStyle(24);
  gr[3]->Draw("l");
  gr[4]->SetLineWidth(2);
  gr[4]->SetLineStyle(2);
  gr[4]->SetLineColor(2);
  gr[4]->Draw("l");
  gr[1]->SetLineWidth(2);
  gr[1]->SetLineStyle(1);
  gr[1]->SetLineColor(3);
  gr[1]->Draw("l");

  //TLegend*leg0=new TLegend(0.25,0.7,0.55,0.85);
  //TLegend*leg0=new TLegend(0.30,0.75,0.55,0.89);//PUB 1st edition
  TLegend*leg0=new TLegend(0.58,0.30,0.88,0.50);
  leg0->SetFillColor(0);
  leg0->SetLineColor(0);
  leg0->SetTextFont(42);
  leg0->SetTextSize(0.05);
  leg0->SetHeader("H#rightarrow ZZ^{(*)}#rightarrow 4l");
  //leg0->AddEntry(gr[0],"Median - No systematics","l");
  //leg0->AddEntry(gr[3],"Median - Systematics","l");
  leg0->AddEntry(gr[2],"Median","l");
  //leg0->AddEntry(gr[2],"Thery singal + measurement bkg","l");
  //leg0->AddEntry(gr[3],"Correlated half gaus","l");
  /////leg0->AddEntry(marker,"Median #pm 1 #sigma","f");
  /////leg0->AddEntry(marker2,"Median #pm 2 #sigma","f");
  leg0->Draw();
  TLatex*tex = new TLatex(0.80,0.955,"#sqrt{s}=7 TeV");
  tex->SetNDC(kTRUE);
  tex->SetTextFont(42);
  tex->SetTextSize(0.05);
  tex->Draw();

  TLatex l; //l.SetTextAlign(12); l.SetTextSize(tsize); 
  l.SetNDC();
  l.SetTextFont(42);
  l.SetTextColor(1);
  l.SetTextAlign(12);
  //l.DrawLatex(0.60,0.45,"ATLAS Preliminary");
  l.DrawLatex(0.30,0.85,"Very Preliminary CL_{s}");
  TLatex ll; //l.SetTextAlign(12); l.SetTextSize(tsize); 
  ll.SetNDC();
  ll.SetTextFont(42);
  ll.SetTextColor(1);
  //ll.DrawLatex(0.65,0.38,"(Simulation)");
  ll.DrawLatex(0.35,0.78,"(Expectation)");//Simulation)");
  //ATLAS_LABEL(0.7,0.15);
  c1->Print("h4lLimit7TeV.eps");

  return 0;
}

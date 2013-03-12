//////////////////
// plot p0
//
//
int makeplotP0(int type)
{
  double zeroOneSigma = 4.60172162722971012e-01;
  double zeroFiveSigma = 3.08537538725986937e-01;
  //TString wsDirName("standard_2011_2012_v2");
  //TString wsDirName("z_mass_constraint_2011_2012_v2");
  TString wsDirName("z_mass_constraint_2011_2012_v6");
  TString baseDirName("/xdata05/xju/H_4L/Limits/ICHEP2012/V8");

  std::vector<double> massOld,pvalueOld,pvalueeOld;
  cout<<"loading 2011"<<endl;
  //fstream filestr0 ("/xdata05/xju/H_4L/Limits/ICHEP2012/V4/standard_v2_2011_pvalue.txt", fstream::in);
  //fstream filestr0 ("/xdata05/xju/H_4L/Limits/ICHEP2012/V7/z_mass_constraint_v4_2011_pvalue.txt", fstream::in);
  //fstream filestr0 ("/xdata05/xju/H_4L/Limits/ICHEP2012/V8/z_mass_constraint_v6_2011_pvalue.txt", fstream::in);
  fstream filestr0("/xdata05/xju/H_4L/Limits/ICHEP2012/V9/z_mass_constraint_v7_2011_EnergyScaleSystematic_pvalue.txt", fstream::in);
  do
   {
     double mm,pv,pve, pvv , pvvv;
     filestr0 >> mm>> pv>>pve>>pvv>>pvvv;
     //std::cerr<<mm<<"\t"<< pv<<"\t"<<pve<<"\t"<<sqrt(ROOT::Math::chisquared_quantile_c(pve*2,1))<<"\n";
     //massOld.push_back(mm);
     massOld.push_back(mm/10.);
     pvalueOld.push_back(pv);
     pvalueeOld.push_back(pve);
   }
  while(!filestr0.eof());
  filestr0.close();
  
  cout<<"loading withconstraint"<<endl;
  std::vector<double> mass,pvalue_o,pvalue_e,pvalue_pao, pvalue_pah;

  //fstream filestr (Form("%s/%s_EnergyScaleSystematic_pvalue.txt",baseDirName.Data(),wsDirName.Data()), fstream::in);
  fstream filestr("/xdata05/xju/H_4L/Limits/ICHEP2012/V9/z_mass_constraint_2011_2012_v7_EnergyScaleSystematic_pvalue.txt", fstream::in);
  int upCrossing01 = 0;
  int upCrossing05 = 0;
  double pre_pvo = 0;
  int index = 0;
  do
   {
     double mm,pvo,pve,pvv,pvvv;
     filestr >> mm>> pvo>>pve>>pvv>>pvvv;
     //cout<<mm<<" "<< pvo<<endl;
     mass.push_back(mm/10.);
     pvalue_o.push_back(pvo);
     pvalue_e.push_back(pve);
     pvalue_pao.push_back(pvv);
     pvalue_pah.push_back(pvvv);
     if(index == 0) pre_pvo = pvo;
     else {
      if(pvo < zeroOneSigma && (pre_pvo-zeroOneSigma) * (pvo-zeroOneSigma) < 0) upCrossing01 ++;
      if(pvo < zeroFiveSigma && (pre_pvo-zeroFiveSigma) * (pvo-zeroFiveSigma) < 0) upCrossing05 ++;
      pre_pvo = pvo;
     }
     index ++;
   }
  while(!filestr.eof());
  filestr.close();

  cout<<"Crossing, 0.1sigma "<<upCrossing01<<endl;
  cout<<"Crossing, 0.5sigma "<<upCrossing05<<endl;

  cout<<"loading without constraint"<<endl;
  std::vector<double> mass_hugezz,pvalue_hugezz_o,pvalue_hugezz_e;
  //fstream filestr("/xdata05/xju/H_4L/Limits/ICHEP2012/V4/standard_v2_2012_pvalue.txt", fstream::in);
  //fstream filestr("/xdata05/xju/H_4L/Limits/ICHEP2012/V7/z_mass_constraint_v4_2012_pvalue.txt", fstream::in);
  fstream filestr("/xdata05/xju/H_4L/Limits/ICHEP2012/V9/z_mass_constraint_v7_2012_EnergyScaleSystematic_pvalue.txt", fstream::in);
  do
   {
     double mm,pvo,pve,pvv,pvvv;
     filestr >> mm>> pvo>>pve>>pvv>>pvvv;
     //if(mm>2800. && mm<=4000.)
       //continue;
     mass_hugezz.push_back(mm/10.);
     pvalue_hugezz_o.push_back(pvo);
     pvalue_hugezz_e.push_back(pve);
   }
  while(!filestr.eof());
  filestr.close();
  cout<<"loading free ZZ"<<endl;
  std::vector<double> mass_hugezjet,pvalue_hugezjet_o,pvalue_hugezjet_e;
  //fstream filestr (Form("%s/z_mass_constraint_100PercentErrorqqZZ_v3_pvalue.txt",baseDirName.Data()), fstream::in);
  //fstream filestr ("/xdata05/xju/H_4L/Limits/ICHEP2012/V5/z_mass_constraint_100PercentErrorqqZZ_v3_pvalue.txt", fstream::in);
  //fstream filestr("/xdata05/xju/H_4L/Limits/ICHEP2012/V8/standard_2011_2012_v6_pvalue.txt", fstream::in);
  fstream filestr("/xdata05/xju/H_4L/Limits/ICHEP2012/V9/standard_2011_2012_v7_pvalue.txt", fstream::in);
  do
   {
     double mm,pvo,pve,pvv,pvvv;
     filestr >> mm>> pvo>>pve>>pvv>>pvvv;
     //if(mm>2800. && mm<=4000.)
       //continue;
     mass_hugezjet.push_back(mm/10.);
     pvalue_hugezjet_o.push_back(pvo);
     pvalue_hugezjet_e.push_back(pve);
   }
  while(!filestr.eof());
  filestr.close();

  cout<<"loading ESS"<<endl;
  std::vector<double> mass_hugebkg,pvalue_hugebkg_o,pvalue_hugebkg_e;
  //fstream filestr ("Pvalue_v2/NoZMassConstraintHugeErrorBkg_pvalue.txt", fstream::in);//4.8/fb re-analysis
  fstream filestr (Form("%s/%s_EnergyScaleSystematic_pvalue.txt",baseDirName.Data(),wsDirName.Data()), fstream::in);
  do
   {
     double mm,pvo,pve,pvv,pvvv;
     filestr >> mm>> pvo>>pve>>pvv>>pvvv;
     //if(mm>2800. && mm<=4000.)
       //continue;
       mass_hugebkg.push_back(mm/10.);
     pvalue_hugebkg_o.push_back(pvo);
     pvalue_hugebkg_e.push_back(pve);
   }
  while(!filestr.eof());
  filestr.close();

  cout<<"loading HugeQQZZ"<<endl;
  std::vector<double> mass0,pvalue0_o,pvalue0_e;
  //fstream filestr (Form("%s/z_mass_constraint_v3_4mu_pvalue.txt",baseDirName.Data()), fstream::in);
  //fstream filestr (Form("%s/%s_4mu_pvalue.txt",baseDirName.Data(),wsDirName.Data()), fstream::in);
  //fstream filestr ("Pvalue_v2/NoZMassConstraintHugeErrorBkg_pvalue.txt", fstream::in);//4.8/fb re-analysis
  fstream filestr (Form("%s/%s_HugeErrorOnqqZZ_pvalue.txt",baseDirName.Data(),wsDirName.Data()), fstream::in);
  do
   {
     double mm,pvo,pve,pvv,pvvv;
     filestr >> mm>> pvo>>pve>>pvv>>pvvv;
     //if(mm>2800. && mm<=4000.)
       //continue;
     mass0.push_back(mm/10.);
     pvalue0_o.push_back(pvo);
     pvalue0_e.push_back(pve);
   }
  while(!filestr.eof());
  filestr.close();

  cout<<"loading HugeBKG"<<endl;
  std::vector<double> mass1,pvalue1_o,pvalue1_e;
  //fstream filestr (Form("%s/z_mass_constraint_v3_2mu2e_pvalue.txt",baseDirName.Data()), fstream::in);
  //fstream filestr (Form("%s/%s_2mu2e_pvalue.txt",baseDirName.Data(),wsDirName.Data()), fstream::in);
  fstream filestr ("Pvalue_v2/NoZMassConstraintHugeErrorBkg_pvalue.txt", fstream::in);//4.8/fb re-analysis
  do
   {
     double mm,pvo,pve,pvv,pvvv;
     filestr >> mm>> pvo>>pve>>pvv>>pvvv;
     //if(mm>2800. && mm<=4000.)
       //continue;
     mass1.push_back(mm/10.);
     pvalue1_o.push_back(pvo);
     pvalue1_e.push_back(pve);
   }
  while(!filestr.eof());
  filestr.close();

  std::vector<double> mass2,pvalue2_o,pvalue2_e;
  //fstream filestr (Form("%s/z_mass_constraint_v3_4e_pvalue.txt",baseDirName.Data()), fstream::in);
  //fstream filestr (Form("%s/%s_4e_pvalue.txt",baseDirName.Data(),wsDirName.Data()), fstream::in);
  fstream filestr ("Pvalue_v2/NoZMassConstraintHugeErrorBkg_pvalue.txt", fstream::in);//4.8/fb re-analysis
  do
   {
     double mm,pvo,pve,pvv,pvvv;
     filestr >> mm>> pvo>>pve>>pvv>>pvvv;
     //if(mm>2800. && mm<=4000.)
       //continue;
     mass2.push_back(mm/10.);
     pvalue2_o.push_back(pvo);
     pvalue2_e.push_back(pve);
   }
  while(!filestr.eof());
  filestr.close();
  std::vector<double> mass3,pvalue3_o,pvalue3_e;
  //fstream filestr (Form("%s/z_mass_constraint_v3_2e2mu_pvalue.txt",baseDirName.Data()), fstream::in);
  //fstream filestr (Form("%s/%s_2e2mu_pvalue.txt",baseDirName.Data(),wsDirName.Data()), fstream::in);
  fstream filestr ("Pvalue_v2/NoZMassConstraintHugeErrorBkg_pvalue.txt", fstream::in);//4.8/fb re-analysis
  do
   {
     double mm,pvo,pve,pvv,pvvv;
     filestr >> mm>> pvo>>pve>>pvv>>pvvv;
     //if(mm>2800. && mm<=4000.)
       //continue;
     mass3.push_back(mm/10.);
     pvalue3_o.push_back(pvo);
     pvalue3_e.push_back(pve);
   }
  while(!filestr.eof());
  filestr.close();
  
  cout<<"Loading llmumu"<<endl;
  std::vector<double> mass4,pvalue4_o,pvalue4_e;
  //fstream filestr (Form("%s/z_mass_constraint_2012_llmumu_v3_pvalue.txt",baseDirName.Data()), fstream::in);
  //fstream filestr (Form("%s/standard_2012_llmumu_v3_pvalue.txt",baseDirName.Data()), fstream::in);
  //fstream filestr ("Pvalue_v2/NoZMassConstraintHugeErrorBkg_pvalue.txt", fstream::in);//4.8/fb re-analysis
  //fstream filestr (Form("%s/%s_llmumu_pvalue.txt",baseDirName.Data(),wsDirName.Data()), fstream::in);
  fstream filestr("/xdata05/xju/H_4L/Limits/ICHEP2012/V9/z_mass_constraint_2011_2012_v7_llmumu_pvalue.txt", fstream::in);
  do
   {
     double mm,pvo,pve,pvv,pvvv;
     filestr >> mm>> pvo>>pve>>pvv>>pvvv;
     if(!filestr.good()) break;
     //if(mm>2800. && mm<=4000.)
       //continue;

     mass4.push_back(mm/10.);
     pvalue4_o.push_back(pvo);
     pvalue4_e.push_back(pve);
   }
  while(!filestr.eof());
  filestr.close();

  cout<<"Loading llee"<<endl;
  std::vector<double> mass5,pvalue5_o,pvalue5_e;
  //fstream filestr ("Pvalue_v2/NoZMassConstraintHugeErrorBkg_pvalue.txt", fstream::in);//4.8/fb re-analysis
  //fstream filestr (Form("%s/z_mass_constraint_2012_llee_v3_pvalue.txt",baseDirName.Data()), fstream::in);
  //fstream filestr (Form("%s/standard_2012_llee_v3_pvalue.txt",baseDirName.Data()), fstream::in);
  //fstream filestr (Form("%s/%s_llee_pvalue.txt",baseDirName.Data(),wsDirName.Data()), fstream::in);
  fstream filestr("/xdata05/xju/H_4L/Limits/ICHEP2012/V9/z_mass_constraint_2011_2012_v7_llee_pvalue.txt", fstream::in);
  do
   {
     double mm,pvo,pve,pvv,pvvv;
     filestr >> mm>> pvo>>pve>>pvv>>pvvv;
     if(!filestr.good()) break;
     //if(mm>2800. && mm<=4000.)
       //continue;
     mass5.push_back(mm/10.);
     pvalue5_o.push_back(pvo);
     pvalue5_e.push_back(pve);
   }
  while(!filestr.eof());
  filestr.close();

  TGraph*grOldo=new TGraph(massOld.size(),&massOld[0],&pvalueOld[0]);
  grOldo->SetLineWidth(2);
  grOldo->SetLineColor(4);
  TGraph*grOlde=new TGraph(massOld.size(),&massOld[0],&pvalueeOld[0]);
  grOlde->SetLineWidth(2);
  grOlde->SetLineStyle(2);
  grOlde->SetLineColor(4);

  TGraph*gro=new TGraph(mass.size(),&mass[0],&pvalue_o[0]);
  gro->SetLineWidth(2);
  gro->SetLineColor(2);
  TGraph*gre=new TGraph(mass.size(),&mass[0],&pvalue_e[0]);
  gre->SetLineWidth(2);
  gre->SetLineColor(2);
  gre->SetLineStyle(2);
  TGraph*grpao=new TGraph(mass.size(),&mass[0],&pvalue_pao[0]);
  grpao->SetLineWidth(2);
  grpao->SetLineStyle(9);
  TGraph*grpah=new TGraph(mass.size(),&mass[0],&pvalue_pah[0]);
  grpah->SetLineWidth(2);
  grpah->SetLineStyle(9);

  TGraph*grhugezzo=new TGraph(mass_hugezz.size(),&mass_hugezz[0],&pvalue_hugezz_o[0]);
  grhugezzo->SetLineWidth(2);
  TGraph*grhugezze=new TGraph(mass_hugezz.size(),&mass_hugezz[0],&pvalue_hugezz_e[0]);
  grhugezze->SetLineWidth(2);
  grhugezze->SetLineStyle(2);

  TGraph*grhugezjeto=new TGraph(mass_hugezjet.size(),&mass_hugezjet[0],&pvalue_hugezjet_o[0]);
  grhugezjeto->SetLineWidth(2);
  grhugezjeto->SetLineColor(4);
  TGraph*grhugezjete=new TGraph(mass_hugezjet.size(),&mass_hugezjet[0],&pvalue_hugezjet_e[0]);
  grhugezjete->SetLineWidth(2);
  grhugezjete->SetLineColor(4);
  grhugezjete->SetLineStyle(2);

  TGraph*grhugebkgo=new TGraph(mass_hugebkg.size(),&mass_hugebkg[0],&pvalue_hugebkg_o[0]);
  grhugebkgo->SetLineWidth(2);
  grhugebkgo->SetLineColor(4);
  TGraph*grhugebkge=new TGraph(mass_hugebkg.size(),&mass_hugebkg[0],&pvalue_hugebkg_e[0]);
  grhugebkge->SetLineWidth(2);
  grhugebkge->SetLineColor(4);
  grhugebkge->SetLineStyle(2);

  TGraph*grsubo[6];
  grsubo[0]=new TGraph(mass0.size(),&mass0[0],&pvalue0_o[0]);
  grsubo[1]=new TGraph(mass1.size(),&mass1[0],&pvalue1_o[0]);
  grsubo[2]=new TGraph(mass2.size(),&mass2[0],&pvalue2_o[0]);
  grsubo[3]=new TGraph(mass3.size(),&mass3[0],&pvalue3_o[0]);
  grsubo[4]=new TGraph(mass4.size(),&mass4[0],&pvalue4_o[0]);
  grsubo[5]=new TGraph(mass5.size(),&mass5[0],&pvalue5_o[0]);
  TGraph*grsube[6];
  grsube[0]=new TGraph(mass0.size(),&mass0[0],&pvalue0_e[0]);
  grsube[1]=new TGraph(mass1.size(),&mass1[0],&pvalue1_e[0]);
  grsube[2]=new TGraph(mass2.size(),&mass2[0],&pvalue2_e[0]);
  grsube[3]=new TGraph(mass3.size(),&mass3[0],&pvalue3_e[0]);
  grsube[4]=new TGraph(mass4.size(),&mass4[0],&pvalue4_e[0]);
  grsube[5]=new TGraph(mass5.size(),&mass5[0],&pvalue5_e[0]);
  for(int i=0;i<6;i++)
    {
      grsubo[i]->SetLineWidth(2);
      grsube[i]->SetLineWidth(2);
      grsube[i]->SetLineStyle(2);
      grsubo[i]->SetLineColor(6+i);
      grsube[i]->SetLineColor(6+i);
    }
      grsubo[4]->SetLineColor(2);
      grsube[4]->SetLineColor(2);
      grsubo[5]->SetLineColor(4);
      grsube[5]->SetLineColor(4);
      //
      //grsubo[4]->SetLineColor(4);
      //grsube[4]->SetLineColor(4);
      //grsubo[5]->SetLineColor(46);
      //grsube[5]->SetLineColor(46);

  ////// plotting 
  TH2F*dummy=new TH2F("dummy",";m_{H} [GeV];Local p_{0}",520,90.,610.,19000,1.e-5,1.9e3);
  //TH2F*dummy=new TH2F("dummy",";m_{H} [GeV];Local p_{0}",520,90.,610.,19000,1.e-10,99.9);
  //dummy->GetYaxis()->SetRangeUser(0.999e-5,0.999999999);
  dummy->GetYaxis()->SetRangeUser(0.999e-7,280);
  dummy->GetYaxis()->SetTitleOffset(1.26);
  dummy->GetXaxis()->SetRangeUser(110.,599.9);
  dummy->GetXaxis()->SetNdivisions(505);
  dummy->GetXaxis()->SetLabelOffset(0.015);
  dummy->GetXaxis()->SetTitleOffset(1.10);
  double onesigma = 1.58655253931457074e-01;
  double twosigma=(1.-0.954499736104)/2.;
  double threesigma=(1.-0.997300203937)/2.;
  double foursigma=3.16712418331199785e-05;
	
  vector<double> _2sigma, _3sigma, _1sigma, _4sigma;
  for(int i = 0 ; i < (int)mass_hugebkg.size(); i++){
    _1sigma.push_back(onesigma);
    _2sigma.push_back(twosigma);
    _3sigma.push_back(threesigma);
    _4sigma.push_back(foursigma);
  }
  TGraph* gr1sigma =new TGraph(mass_hugebkg.size(),&mass_hugebkg[0],&_1sigma[0]);
  TGraph* gr2sigma =new TGraph(mass_hugebkg.size(),&mass_hugebkg[0],&_2sigma[0]);
  TGraph* gr3sigma =new TGraph(mass_hugebkg.size(),&mass_hugebkg[0],&_3sigma[0]);
  TGraph* gr4sigma =new TGraph(mass_hugebkg.size(),&mass_hugebkg[0],&_4sigma[0]);

  TLine*line2=new TLine(110., twosigma, 600., twosigma);
  line2->SetLineWidth(2);
  line2->SetLineStyle(9);
  line2->SetLineColor(kRed+1);
  TLine*line3=new TLine(110., threesigma, 600., threesigma);
  line3->SetLineWidth(2);
  line3->SetLineStyle(9);
  line3->SetLineColor(kRed+1);
  ////////
  TCanvas*c1=new TCanvas("c1","",600,600);
  c1->SetMargin(0.13,0.05,0.12,0.05);
  c1->SetLogy();
  dummy->Draw();

  //TLegend*leg0=new TLegend(0.16,0.15,0.53,0.35);////0.25);
  TLegend*leg0=new TLegend(0.14,0.15+0.56,0.53,0.35+0.56);////0.25);
  leg0->SetFillColor(0);
  leg0->SetLineColor(0);
  leg0->SetTextFont(42);
  leg0->SetTextSize(0.04);
  if(type == 5){
    leg0->SetY1(0.75);
    leg0->SetY2(0.85);
  }
  
  if(type==0)
    {
      leg0->AddEntry(gro,"Observed 2012","l");
      leg0->AddEntry(gre,"Expected 2012","l");
      leg0->AddEntry(grOldo,"Observed 2011","l");
      leg0->AddEntry(grOlde,"Expected 2011","l");
      //
      //leg0->AddEntry(gro,"Observed 2012,withZConstraint","l");
      //leg0->AddEntry(gre,"Expected 2012,withZConstraint","l");
      //leg0->AddEntry(grOldo,"Observed 2012,noZConstraint","l");
      //leg0->AddEntry(grOlde,"Expected 2012,noZConstraint","l");
      //
      //leg0->AddEntry(gro,"Observed 2011,V2","l");
      //leg0->AddEntry(gre,"Expected 2011,V2","l");
      //leg0->AddEntry(grOldo,"Observed 2011,V1","l");
      //leg0->AddEntry(grOlde,"Expected 2011,V1","l");
    }
  else if(type==1)
    {
      leg0->AddEntry(gro,"Obs. with constraint","l");
      leg0->AddEntry(gre,"Exp. with constraint","l");
      //leg0->AddEntry(grhugezzo,"Obs. no constraint","l");
      //leg0->AddEntry(grhugezze,"Exp. no constraint","l");
      //
      leg0->AddEntry(grhugezjeto,"Obs. no constraint","l");
      leg0->AddEntry(grhugezjete,"Exp. no constraint","l");
      //
      //leg0->AddEntry(grsubo[2],"Observed","l");
      //leg0->AddEntry(grsube[2],"Expected","l");
      //leg0->AddEntry(grhugezzo,"Observed free ZZ","l");
      //leg0->AddEntry(grhugezze,"Expected free ZZ","l");
    }
  else if(type==2)
    {
      leg0->AddEntry(gro,"Obs.","l");
      leg0->AddEntry(gre,"Exp.","l");


      leg0->AddEntry(grsubo[0],"Obs. free ZZ","l");
      leg0->AddEntry(grsube[0],"Exp. free ZZ","l");
    }
  else if(type==3)
    {
      leg0->AddEntry(gro,"Observed","l");
      leg0->AddEntry(gre,"Expected","l");
      //leg0->AddEntry(grhugebkgo,"Observed free bkg","l");
      //leg0->AddEntry(grhugebkge,"Expected free bkg","l");
      leg0->AddEntry(grhugebkgo,"Observed ESS","l");
      leg0->AddEntry(grhugebkge,"Expected ESS","l");
    }
  else if(type==4)
    {
      leg0->AddEntry(gro,"Observed","l");
      leg0->AddEntry(gre,"Expected","l");
      leg0->AddEntry(grsubo[0],"4#mu","l");
      leg0->AddEntry(grsubo[1],"2#mu 2e","l");
      leg0->AddEntry(grsubo[2],"4e","l");
      leg0->AddEntry(grsubo[3],"2e2#mu","l");
    }
  else if (type ==5)
  {
      leg0->AddEntry(gro,"Observed","l");
      //leg0->AddEntry(gre,"Expected PA 0","l");
      //leg0->AddEntry(grpao,"Expected PA 1","l");
      //leg0->AddEntry(grpah,"Expected PA #hat{#mu}","l");
      leg0->AddEntry(gre,"Expected","l");
  }else if(type == 6){
      leg0->AddEntry(gro,"Observed","l");
      leg0->AddEntry(gre,"Expected","l");
      leg0->AddEntry(grsubo[0],"4#mu","l");
      leg0->AddEntry(grsubo[1],"2#mu 2e","l");
      leg0->AddEntry(grsubo[2],"4e","l");
      leg0->AddEntry(grsubo[3],"2e2#mu","l");
      leg0->AddEntry(grsubo[4],"#it{ll}2#mu","l");
      leg0->AddEntry(grsubo[5],"#it{ll}2e","l");
  }else if(type == 7){
      leg0->SetTextSize(0.032);
      leg0->AddEntry(gro,"Obs. combined","l");
      leg0->AddEntry(gre,"Exp. combined","l");
      leg0->AddEntry(grOldo,"Obs. 2011","l");
      leg0->AddEntry(grOlde,"Exp. 2011","l");
      leg0->AddEntry(grhugezzo,"Obs. 2012","l");
      leg0->AddEntry(grhugezze,"Exp. 2012","l");
  }else if(type == 8){
      leg0->SetTextSize(0.032);
      leg0->AddEntry(gro,"Observed","l");
      leg0->AddEntry(gre,"Expected","l");
      leg0->AddEntry(grsubo[4],"Observed #it{ll}#mu#mu","l");
      leg0->AddEntry(grsube[4],"Expected #it{ll}#mu#mu","l");
      leg0->AddEntry(grsubo[5],"Observed #it{ll}ee","l");
      leg0->AddEntry(grsube[5],"Expected #it{ll}ee","l");
  }
  leg0->Draw();

  //line2->Draw();
  //line3->Draw();
  gr1sigma ->Draw("L");
  gr2sigma ->Draw("L");
  gr3sigma ->Draw("L");
  gr4sigma ->Draw("L");

  gr2sigma->SetLineWidth(2);
  gr2sigma->SetLineStyle(5);
  //gr2sigma->SetLineColor(16);
  gr2sigma->SetLineColor(1);

  gr3sigma->SetLineWidth(2);
  gr3sigma->SetLineStyle(5);
  gr3sigma->SetLineColor(1);

  gr1sigma->SetLineWidth(2);
  gr1sigma->SetLineStyle(5);
  gr1sigma->SetLineColor(1);

  gr4sigma->SetLineWidth(2);
  gr4sigma->SetLineStyle(5);
  gr4sigma->SetLineColor(1);
  
  //gre->SetMarkerStyle(20);//temporary to indicate mass points used
  gre->SetMarkerStyle(20);//temporary to indicate mass points used
  if(type==0)
    {
      gro->Draw("L");
      gre->Draw("L");
  
      grOldo->Draw("L");
      grOlde->Draw("L");
    }
  else if(type==1) //norm vs huge ZZ
    {
      //dummy->GetYaxis()->SetRangeUser(0.999e-7,0.999999999);
      //dummy ->Draw("same");
      //grsubo[2] ->Draw("L");// 4e
      //grsube[2] ->Draw("L");// 4e
      gro->Draw("L");
      gre->Draw("L");
      //grhugezzo->Draw("L");
      //grhugezze->Draw("L");
      grhugezjeto->Draw("L");
      grhugezjete->Draw("L");
    }
  else if(type==2) //norm vs huge zjet,zbb,tt
    {
      gro->Draw("L");
      gre->Draw("L");
      //grhugezjeto->Draw("L");
      //grhugezjete->Draw("L");
      grsubo[0]->SetLineColor(4);
      grsube[0]->SetLineColor(4);
      grsubo[0]->Draw("L");
      grsube[0]->Draw("L");
    }
  else if(type==3) //norm vs huge bkg
    {
      gro->Draw("L");
      gre->Draw("L");
      grhugebkgo->Draw("L");
      grhugebkge->Draw("L");
    }
  else if(type==4) 
    {
      gro->SetLineColor(1);
      gre->SetLineColor(1);
      gro->Draw("L");
      gre->Draw("L");
      for(int i=0;i<4;i++)
	{
	  grsubo[i]->Draw("L");
	  grsube[i]->Draw("L");
	}
    }else if(type == 5){
      gro->SetLineColor(1); 
      gre->SetLineColor(1);
      grpao ->SetLineColor(8);
      grpah ->SetLineColor(4);
      gro->Draw("L");
      gre->Draw("L");
      //grpao->Draw("L");
      //grpah->Draw("L");
    }else if(type == 6){
      gro->SetLineColor(1);
      gre->SetLineColor(1);
      gro->Draw("L");
      gre->Draw("L");
      for(int i=0;i<6;i++)
      {
        grsubo[i]->Draw("L");
        grsube[i]->Draw("L");
      }

    }else if(type == 7){
      gro->SetLineColor(1);
      gre->SetLineColor(1);
      grOldo ->SetLineColor(4);
      grOlde ->SetLineColor(4);
      grhugezzo ->SetLineColor(2);
      grhugezze ->SetLineColor(2);
      gro->Draw("L");
      gre->Draw("L");

      grOldo ->Draw("L");
      grOlde ->Draw("L");
      grhugezzo ->Draw("L");
      grhugezze ->Draw("L");
    }else if(type == 8){
      gro->SetLineColor(1);
      gre->SetLineColor(1);
      gro->Draw("L");
      gre->Draw("L");
      for(int i=4;i<6;i++)
      {
        grsubo[i]->Draw("L");
        grsube[i]->Draw("L");
      }
    }


  TLatex l;
  l.SetNDC();
  l.SetTextFont(42);
  l.SetTextSize(0.04);
  l.SetTextColor(1);
  l.SetTextAlign(12);
  //TLatex* l1 = l.DrawLatex(0.57,0.33+0.56,"#bf{#it{ATLAS}}");//:Preliminary");
  TLatex* l1 = l.DrawLatex(0.57,0.33+0.56,"#bf{#it{ATLAS} Preliminary}");//:Preliminary");
  //TLatex* l1 = l.DrawLatex(0.66,0.35,"#bf{#it{ATLAS}}");//
  TLatex* l2 = l.DrawLatex(0.57,0.28+0.56,"H#rightarrow ZZ^{(*)}#rightarrow 4l");
  //TLatex* l3 = l.DrawLatex(0.63,0.23,"#lower[-0.15]{#scale[0.6]{#int}}Ldt = 4.8 fb^{-1}");
  //TLatex* l4 = l.DrawLatex(0.63,0.18,"#sqrt{s}=7 TeV");
  //TLatex* l3 = l.DrawLatex(0.63,0.23,"#lower[-0.15]{#scale[0.6]{#int}}Ldt = 4.2 fb^{-1}");
  //TLatex* l4 = l.DrawLatex(0.63,0.18,"#sqrt{s}=8 TeV");
  TLatex* l3 = l.DrawLatex(0.57,0.22+0.56,"#sqrt{s}=7 TeV: #lower[-0.15]{#scale[0.6]{#int}}Ldt =4.8 fb^{-1}");
  TLatex* l4 = l.DrawLatex(0.57,0.16+0.56,"#sqrt{s}=8 TeV: #lower[-0.15]{#scale[0.6]{#int}}Ldt =5.8 fb^{-1}");
  l.SetNDC(0);
  l.SetTextSize(0.040);
  TLatex* l5 = l.DrawLatex(605.,twosigma,"2#sigma");
  TLatex* l6 = l.DrawLatex(605.,threesigma,"3#sigma");
  TLatex* l7 = l.DrawLatex(605.,onesigma,"1#sigma");
  TLatex* l8 = l.DrawLatex(605.,foursigma,"4#sigma");

  TLatex* tck=new TLatex();
  tck->SetNDC();
  tck->SetTextFont(42);
  tck->SetTextSize(0.05);
  TLatex* tck0=tck->DrawLatex(0.095,0.065,"110");

 
  c1->Update();
  TString name(wsDirName);
  name += "_p0plot_";
  name+=type;
  //name+=".eps";
  c1->Print(Form("%s.eps",name.Data()));
  //c1->Print(Form("%s.cxx",name.Data()));
  delete tck0;

  dummy->GetXaxis()->SetNdivisions(510);
  line2->SetX1(110.);
  line2->SetX2(199.99);
  line3->SetX1(110.);
  line3->SetX2(199.99);
  l1->SetX(0.57);
  l1->SetNDC();
  double maxrange = 179.9;
  l5->SetX(maxrange + 1.0);
  l6->SetX(maxrange + 1.0);
  l7->SetX(maxrange + 1.0);
  l8->SetX(maxrange + 1.0);
  //dummy->GetXaxis()->SetRangeUser(110.,199.99);
  dummy->GetXaxis()->SetRangeUser(110.,maxrange);
  //dummy->GetYaxis()->SetRangeUser(1.e-3,0.99999);
  //delete line3;
  //delete l6;
  c1->Update();
  TString name2(wsDirName);
  name2 += "_p0plotZoom_";
  name2+=type;
  //name2+=".eps";
  c1->Print(Form("%s.eps",name2.Data()));
  //c1->Print(Form("%s.cxx",name2.Data()));
  //c1->Print(name2);
  return 0;
}

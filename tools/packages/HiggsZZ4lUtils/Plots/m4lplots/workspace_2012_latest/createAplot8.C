////////////////////////////////////////////////////
// create plot for 8 TeV datasets
//
// Kostas 
//
////////////////////////////////////////////////////
//
// >.L createAplot.c
// > createAplot2ppnew(0)
// > createAplot2ppnew(1)
// > createAplot2ppnew(2)
// > createAplot2ppnew(3)
// > createAplot2ppnew(4)
/////////////////////////////////////////////////////
bool bBW=false;
// data, total bkg, signal // type (0-3, 4 all, 5 all and full range)
int createAplot2ppnew(int typein=0,int bin=0);
int createAplot2ppnewm12(int typein=0,int bin=0);
// data, bkg contributions, signal // type (0-3, 4 all, 5 all and full range)

int createAplot2ppnew(int typein,int bin)
{
  bool docomp=true;//false;//true;
  bool addearlyData =false;
  bool fullRange=false;
  int type = typein;
  if(type==5)
    {
      type=4;
      fullRange=true;
    }

  bool doSyst = true;//false;
  TH1F*signal;
  TH1F*signal1;
  TH1F*signal2;
  TH1F*bkg;
  TH1F*bkgcomp;
  TString fname("ahistos_1250.root");
  if(fullRange)
    fname="ahistos_1250.root";
  //fname="ahistos_3600.root";
  TFile*f=new TFile(fname,"READ");
  int N = 1;
  if(bin==0 && !fullRange) N = 10;//8;//10
  else if(bin==1) N = 20;
  else if(bin==2) N = 4;
  else if(fullRange)  N = 20;//4;
  TIter nextkey(f->GetListOfKeys());
  TKey *key;
  while (key = (TKey*)nextkey()) 
  {
    TH1F*h=(TH1F*)key->ReadObj();
    h->Rebin(N);
  }
  if(type==0)
    {
      signal = (TH1F*)higgs_0->Clone("signal");
      signal->Add(higgsVBF_0);
      signal->Add(higgsWH_0);
      signal->Add(higgsZH_0);
    }
  if(type==1)
    {
      signal = (TH1F*)higgs_1->Clone("signal");
      signal->Add(higgsVBF_1);
      signal->Add(higgsWH_1);
      signal->Add(higgsZH_1);
    }
  if(type==2)
    {
      signal = (TH1F*)higgs_2->Clone("signal");
      signal->Add(higgsVBF_2);
      signal->Add(higgsWH_2);
      signal->Add(higgsZH_2);
    }
  if(type==3)
    {
      signal = (TH1F*)higgs_3->Clone("signal");
      signal->Add(higgsVBF_3);
      signal->Add(higgsWH_3);
      signal->Add(higgsZH_3);
    }
  if(type==4)
    {
      signal = (TH1F*)higgs_0->Clone("signal");
      signal->Add(higgsVBF_0);
      signal->Add(higgs_1);
      signal->Add(higgsVBF_1);
      signal->Add(higgs_2);
      signal->Add(higgsVBF_2);
      signal->Add(higgs_3);
      signal->Add(higgsVBF_3);

      if(!fullRange)
	{
	  signal->Add(higgsWH_0);
	  signal->Add(higgsZH_0);
	  signal->Add(higgsWH_1);
	  signal->Add(higgsZH_1);
	  signal->Add(higgsWH_2);
	  signal->Add(higgsZH_2);
	  signal->Add(higgsWH_3);
	  signal->Add(higgsZH_3);
	}

    }
  if(type==6)
    {
      signal = (TH1F*)higgs_1->Clone("signal");
      signal->Add(higgs_1);
      signal->Add(higgsVBF_1);
      signal->Add(higgs_3);
      signal->Add(higgsVBF_3);

      if(!fullRange)
	{
	  signal->Add(higgsWH_1);
	  signal->Add(higgsZH_1);
	  signal->Add(higgsWH_3);
	  signal->Add(higgsZH_3);
	}

    }
  int itmp = signal->GetNbinsX();
  const int bins = itmp;
  double xsecUncertainty[bins];
  double lumiUncertainty[bins];
  TH1F* systematics = new TH1F("systematics", "", bins, signal->GetBinLowEdge(1), signal->GetBinLowEdge(signal->GetNbinsX()) + signal->GetBinWidth(signal->GetNbinsX()));
  TH1F* tmp[5];
  double tmpuncert[5]={0.10,0.60,0.40,0.25,0.4};
  if(type==0)
    {
      bkg = (TH1F*)histoZZ_0->Clone("bkg");
      bkg->Add(histogg2ZZ_0);
      bkg->Add(histoZbb_0);
      bkg->Add(histoZ_0);
      bkg->Add(histott_0);
      bkgcomp = (TH1F*)histoZbb_0->Clone("bkgcomp");
      bkgcomp->Add(histoZ_0);
      bkgcomp->Add(histott_0);
      tmp[0] = (TH1F*)histoZZ_0->Clone("bkg00");
      tmp[1] = (TH1F*)histogg2ZZ_0->Clone("bkg000");
      tmp[2] = (TH1F*)histoZ_0->Clone("bkg01");
      tmp[3] = (TH1F*)histoZbb_0->Clone("bkg02");
      tmp[4] = (TH1F*)histott_0->Clone("bkg03");
    }
  else if(type==1)
    {
      bkg = (TH1F*)histoZZ_1->Clone("bkg");
      bkg->Add(histogg2ZZ_1);
      bkg->Add(histoZbb_1);
      bkg->Add(histoZ_1);
      bkg->Add(histott_1);
      bkgcomp = (TH1F*)histoZbb_1->Clone("bkgcomp");
      bkgcomp->Add(histoZ_1);
      bkgcomp->Add(histott_1);
      tmp[0] = (TH1F*)histoZZ_1->Clone("bkg00");
      tmp[1] = (TH1F*)histogg2ZZ_1->Clone("bkg000");
      tmp[2] = (TH1F*)histoZ_1->Clone("bkg01");
      tmp[3] = (TH1F*)histoZbb_1->Clone("bkg02");
      tmp[4] = (TH1F*)histott_1->Clone("bkg03");
    }
  else if(type==2)
    {
      bkg = (TH1F*)histoZZ_2->Clone("bkg");
      bkg->Add(histogg2ZZ_2);
      bkg->Add(histoZbb_2);
      bkg->Add(histoZ_2);
      bkg->Add(histott_2);
      bkgcomp = (TH1F*)histoZbb_2->Clone("bkgcomp");
      bkgcomp->Add(histoZ_2);
      bkgcomp->Add(histott_2);
      tmp[0] = (TH1F*)histoZZ_2->Clone("bkg00");
      tmp[1] = (TH1F*)histogg2ZZ_2->Clone("bkg000");
      tmp[2] = (TH1F*)histoZ_2->Clone("bkg01");
      tmp[3] = (TH1F*)histoZbb_2->Clone("bkg02");
      tmp[4] = (TH1F*)histott_2->Clone("bkg03");
    }
  else if(type==3)
    {
      bkg = (TH1F*)histoZZ_3->Clone("bkg");
      bkg->Add(histogg2ZZ_3);
      bkg->Add(histoZbb_3);
      bkg->Add(histoZ_3);
      bkg->Add(histott_3);
      bkgcomp = (TH1F*)histoZbb_3->Clone("bkgcomp");
      bkgcomp->Add(histoZ_3);
      bkgcomp->Add(histott_3);
      tmp[0] = (TH1F*)histoZZ_3->Clone("bkg00");
      tmp[1] = (TH1F*)histogg2ZZ_3->Clone("bkg000");
      tmp[2] = (TH1F*)histoZ_3->Clone("bkg01");
      tmp[3] = (TH1F*)histoZbb_3->Clone("bkg02");
      tmp[4] = (TH1F*)histott_3->Clone("bkg03");
    }
  else if(type==4)
    {
      bkg = (TH1F*)histoZZ_0->Clone("bkg");
      bkg->Add(histogg2ZZ_0);
      bkg->Add(histoZbb_0);
      bkg->Add(histoZ_0);
      bkg->Add(histott_0);
      bkg->Add(histoZZ_1);
      bkg->Add(histogg2ZZ_1);
      bkg->Add(histoZbb_1);
      bkg->Add(histoZ_1);
      bkg->Add(histott_1);
      bkg->Add(histoZZ_2);
      bkg->Add(histogg2ZZ_2);
      bkg->Add(histoZbb_2);
      bkg->Add(histoZ_2);
      bkg->Add(histott_2);
      bkg->Add(histoZZ_3);
      bkg->Add(histogg2ZZ_3);
      bkg->Add(histoZbb_3);
      bkg->Add(histoZ_3);
      bkg->Add(histott_3);
      bkgcomp = (TH1F*)histoZbb_0->Clone("bkgcomp");
      bkgcomp->Add(histoZ_0);
      bkgcomp->Add(histott_0);
      bkgcomp->Add(histoZbb_1);
      bkgcomp->Add(histoZ_1);
      bkgcomp->Add(histott_1);
      bkgcomp->Add(histoZbb_2);
      bkgcomp->Add(histoZ_2);
      bkgcomp->Add(histott_2);
      bkgcomp->Add(histoZbb_3);
      bkgcomp->Add(histoZ_3);
      bkgcomp->Add(histott_3);
      tmp[0] = (TH1F*)histoZZ_0->Clone("bkg00");
      tmp[1] = (TH1F*)histogg2ZZ_0->Clone("bkg000");
      tmp[2] = (TH1F*)histoZ_0->Clone("bkg01");
      tmp[3] = (TH1F*)histoZbb_0->Clone("bkg02");
      tmp[4] = (TH1F*)histott_0->Clone("bkg03");
      tmp[0]->Add(histoZZ_1);
      tmp[1]->Add(histogg2ZZ_1);
      tmp[2]->Add(histoZ_1);
      tmp[3]->Add(histoZbb_1);
      tmp[4]->Add(histott_1);
      tmp[0]->Add(histoZZ_2);
      tmp[1]->Add(histogg2ZZ_2);
      tmp[2]->Add(histoZ_2);
      tmp[3]->Add(histoZbb_2);
      tmp[4]->Add(histott_2);
      tmp[0]->Add(histoZZ_3);
      tmp[1]->Add(histogg2ZZ_3);
      tmp[2]->Add(histoZ_3);
      tmp[3]->Add(histoZbb_3);
      tmp[4]->Add(histott_3);
    }
  else if(type==6)
    {
      bkg = (TH1F*)histoZZ_1->Clone("bkg");
      bkg->Add(histogg2ZZ_1);
      bkg->Add(histoZbb_1);
      bkg->Add(histoZ_1);
      bkg->Add(histott_1);
      bkg->Add(histoZZ_3);
      bkg->Add(histogg2ZZ_3);
      bkg->Add(histoZbb_3);
      bkg->Add(histoZ_3);
      bkg->Add(histott_3);
      bkgcomp = (TH1F*)histoZbb_1->Clone("bkg");
      bkgcomp->Add(histoZ_1);
      bkgcomp->Add(histott_1);
      bkgcomp->Add(histoZbb_3);
      bkgcomp->Add(histoZ_3);
      bkgcomp->Add(histott_3);
      tmp[0] = (TH1F*)histoZZ_1->Clone("bkg00");
      tmp[1] = (TH1F*)histogg2ZZ_1->Clone("bkg000");
      tmp[2] = (TH1F*)histoZ_1->Clone("bkg01");
      tmp[3] = (TH1F*)histoZbb_1->Clone("bkg02");
      tmp[4] = (TH1F*)histott_1->Clone("bkg03");
      tmp[0]->Add(histoZZ_3);
      tmp[1]->Add(histogg2ZZ_3);
      tmp[2]->Add(histoZ_3);
      tmp[3]->Add(histoZbb_3);
      tmp[4]->Add(histott_3);
    }
  for (int b=0;b<bins;b++)
    {
      xsecUncertainty[b] = 0;
      lumiUncertainty[b] = 0;
      for(int i=0;i<5;i++)
	{
	  xsecUncertainty[b] += tmp[i]->GetBinContent(b + 1)*tmpuncert[i]*tmp[i]->GetBinContent(b + 1)*tmpuncert[i];
	  lumiUncertainty[b] += tmp[i]->GetBinContent(b + 1);
	}
      systematics->SetBinContent(b + 1, lumiUncertainty[b]);
      lumiUncertainty[b] = lumiUncertainty[b]*0.039*lumiUncertainty[b]*0.039;
      systematics->SetBinError(b + 1, sqrt(xsecUncertainty[b] + lumiUncertainty[b]));
    }

  TH1F*data;
  if(type==0)
    data = (TH1F*)histoDATA_0->Clone("data");
  if(type==1)
    data = (TH1F*)histoDATA_1->Clone("data");
  if(type==2)
    data = (TH1F*)histoDATA_2->Clone("data");
  if(type==3)
    data = (TH1F*)histoDATA_3->Clone("data");
  if(type==4)
    {
      data = (TH1F*)histoDATA_0->Clone("data");
      data->Add(histoDATA_1);
      data->Add(histoDATA_2);
      data->Add(histoDATA_3);
    }
  if(type==6)
    {
      data = (TH1F*)histoDATA_1->Clone("data");
      data->Add(histoDATA_3);
    }

  /*
    signal->GetXaxis()->SetRangeUser(120.,129.99);
  bkg->GetXaxis()->SetRangeUser(120.,129.99);
  data->GetXaxis()->SetRangeUser(120.,129.99);
  std::cout<< signal->Integral() << "\t"<< bkg->Integral()<<"\t"<<data->Integral()<<std::endl;
  return 0;
  */
  //std::cout <<"total = "<< data->GetEntries() <<"\t"<< data->Integral()<<std::endl;
  //return 0;

  TFile*f1;
  if(!fullRange)
    f1=new TFile("ahistos_1500.root","READ");
  else
    f1=new TFile("ahistos_5200.root","READ");
    //f1=new TFile("ahistos_5200.root","READ");
  N = 1;
  if(bin==0 && !fullRange)
    N = 10;//-8;//10;
  else if(bin==0 && fullRange)
    N = 1;
  else if(bin==1)
    N = 20;
  else if(bin==2)
    N = 4;
  else if(fullRange)
    N = 20;
  data->SetMarkerStyle(20);
  TIter nextkey2(f1->GetListOfKeys());
  TKey *key2;
  while (key2 = (TKey*)nextkey2()) 
  {
    TH1F*h=(TH1F*)key2->ReadObj();
    h->Rebin(N);
  }

  if(type==0)
    {
      signal1 = (TH1F*)higgs_0->Clone("signal1");
      signal1->Add(higgsVBF_0);
      if(!fullRange)
	{
	  signal1->Add(higgsWH_0);
	  signal1->Add(higgsZH_0);
	}
    }
  if(type==1)
    {
      signal1 = (TH1F*)higgs_1->Clone("signal1");
      signal1->Add(higgsVBF_1);
      if(!fullRange)
	{
	  signal1->Add(higgsWH_1);
	  signal1->Add(higgsZH_1);
	}
    }
  if(type==2)
    {
      signal1 = (TH1F*)higgs_2->Clone("signal1");
      signal1->Add(higgsVBF_2);
      if(!fullRange)
	{
	  signal1->Add(higgsWH_2);
	  signal1->Add(higgsZH_2);
	}
    }
  if(type==3)
    {
      signal1 = (TH1F*)higgs_3->Clone("signal1");
      signal1->Add(higgsVBF_3);
      if(!fullRange)
	{
	  signal1->Add(higgsWH_3);
	  signal1->Add(higgsZH_3);
	}
    }
  if(type==4)
    {
      signal1 = (TH1F*)higgs_0->Clone("signal1");
      signal1->Add(higgsVBF_0);
      signal1->Add(higgs_1);
      signal1->Add(higgsVBF_1);
      signal1->Add(higgs_2);
      signal1->Add(higgsVBF_2);
      signal1->Add(higgs_3);
      signal1->Add(higgsVBF_3);
      if(!fullRange)
	{
	  signal1->Add(higgsWH_0);
	  signal1->Add(higgsZH_0);
	  signal1->Add(higgsWH_1);
	  signal1->Add(higgsZH_1);
	  signal1->Add(higgsWH_2);
	  signal1->Add(higgsZH_2);
	  signal1->Add(higgsWH_3);
	  signal1->Add(higgsZH_3);
	}
    }
  if(type==6)
    {
      signal1 = (TH1F*)higgs_1->Clone("signal1");
      signal1->Add(higgsVBF_1);
      signal1->Add(higgs_3);
      signal1->Add(higgsVBF_3);
      if(!fullRange)
	{
	  signal1->Add(higgsWH_1);
	  signal1->Add(higgsZH_1);
	  signal1->Add(higgsWH_3);
	  signal1->Add(higgsZH_3);
	}
    }

  TFile*f2=new TFile("ahistos_1900.root","READ");
  N = 1;
  if(bin==0 && !fullRange)
    N = 5;//4;//5;
  else if(bin==1)
    N = 10;
  else if(bin==2)
    N = 2;
  else if(fullRange)
    N = 10;
  TIter nextkey3(f2->GetListOfKeys());
  TKey *key3;
  while (key3 = (TKey*)nextkey3()) 
  {
    TH1F*h=(TH1F*)key3->ReadObj();
    h->Rebin(N);
  }

  if(type==0)
    {
      signal2 = (TH1F*)higgs_0->Clone("signal2");
      signal2->Add(higgsVBF_0);
      signal2->Add(higgsWH_0);
      signal2->Add(higgsZH_0);
    }
  if(type==1)
    {
      signal2 = (TH1F*)higgs_1->Clone("signal2");
      signal2->Add(higgsVBF_1);
      signal2->Add(higgsWH_1);
      signal2->Add(higgsZH_1);
    }
  if(type==2)
    {
      signal2 = (TH1F*)higgs_2->Clone("signal2");
      signal2->Add(higgsVBF_2);
      signal2->Add(higgsWH_2);
      signal2->Add(higgsZH_2);
    }
  if(type==3)
    {
      signal2 = (TH1F*)higgs_3->Clone("signal2");
      signal2->Add(higgsVBF_3);
      signal2->Add(higgsWH_3);
      signal2->Add(higgsZH_3);
    }
  if(type==4)
    {
      signal2 = (TH1F*)higgs_0->Clone("signal2");
      signal2->Add(higgsVBF_0);
      signal2->Add(higgsWH_0);
      signal2->Add(higgsZH_0);
      signal2->Add(higgs_1);
      signal2->Add(higgsVBF_1);
      signal2->Add(higgsWH_1);
      signal2->Add(higgsZH_1);
      signal2->Add(higgs_2);
      signal2->Add(higgsVBF_2);
      signal2->Add(higgsWH_2);
      signal2->Add(higgsZH_2);
      signal2->Add(higgs_3);
      signal2->Add(higgsVBF_3);
      signal2->Add(higgsWH_3);
      signal2->Add(higgsZH_3);
    }
  if(type==6)
    {
      signal2 = (TH1F*)higgs_1->Clone("signal2");
      signal2->Add(higgs_1);
      signal2->Add(higgsVBF_1);
      signal2->Add(higgsWH_1);
      signal2->Add(higgsZH_1);
      signal2->Add(higgs_3);
      signal2->Add(higgsVBF_3);
      signal2->Add(higgsWH_3);
      signal2->Add(higgsZH_3);
    }



  TH1F*dataearly=NULL;
  if(addearlyData)
    {
      TFile*ff=new TFile("histoOut.root","READ");
      if(type==0)
	dataearly = (TH1F*)histoDATAearlyK0->Clone("dataearlyK");
      if(type==1)
	dataearly = (TH1F*)histoDATAearlyK1->Clone("dataearlyK");
      if(type==2)
	dataearly = (TH1F*)histoDATAearlyK2->Clone("dataearlyK");
      if(type==3)
	dataearly = (TH1F*)histoDATAearlyK3->Clone("dataearlyK");
      if(type==4)
	{
	  dataearly = (TH1F*)histoDATAearlyK0->Clone("dataearlyK");
	  dataearly->Add(histoDATAearlyK1);
	  dataearly->Add(histoDATAearlyK2);
	  dataearly->Add(histoDATAearlyK3);
	}
      if(type==6)
	{
	  dataearly = (TH1F*)histoDATAearlyK1->Clone("dataearlyK");
	  dataearly->Add(histoDATAearlyK3);
	}
      if(bin==0 && !fullRange)
	dataearly->Rebin(10);
      else if(bin==1)
	dataearly->Rebin(20);
      else if(bin==2)
	dataearly->Rebin(4);
      else if(fullRange)
	dataearly->Rebin(20);
  /**
  if(bin==0 && !fullRange)
    {
      bkg->Rebin(10);
      signal->Rebin(10);
      signal1->Rebin(10);
      signal2->Rebin(5);
      data->Rebin(10);
      dataearly->Rebin(10);
    }
  else if(bin==1)
    {
      bkg->Rebin(20);
      signal->Rebin(20);
      signal1->Rebin(20);
      signal2->Rebin(10);
      data->Rebin(20);
      dataearly->Rebin(20);
    }
  if(bin==2)
    {
      bkg->Rebin(4);
      signal->Rebin(4);
      signal1->Rebin(4);
      signal2->Rebin(2);
      data->Rebin(4);
      dataearly->Rebin(4);
    }
  if(fullRange)
    {
      bkg->Rebin(4);
      signal->Rebin(4);
      signal1->Rebin(20);
      signal2->Rebin(10);
      data->Rebin(4);
      dataearly->Rebin(20);
    }
  **/
    }
  int col_bg_f  = TColor::GetColor("#ee0000");//#dddddd");
  int col_bg_l  = TColor::GetColor("#550000");//#aaaaaa");
  int col_sig_f = TColor::GetColor("#aaccff");//#ee0000");
  int col_sig_l = TColor::GetColor("#112255");//#550000");
  int col_sig_f1 = TColor::GetColor("#ffaa00");
  int col_sig_l1 = TColor::GetColor("#552200");
  int col_sig_f2 = TColor::GetColor("#ee55cc");//#ee00bb");
  int col_sig_l2 = TColor::GetColor("#550144");
  signal->SetLineColor(col_sig_l);
  signal->SetFillColor(col_sig_f);
  signal->SetFillStyle(1001);

  if(false &&fullRange)
    {
      signal->SetLineColor(kCyan+4);
      signal->SetFillColor(kGreen+3);
    }

  signal1->SetLineColor(col_sig_l1);
  signal1->SetFillColor(col_sig_f1);
  if(fullRange)
    {
      signal1->SetLineColor(TColor::GetColor("#115588"));
      signal1->SetFillColor(TColor::GetColor("#11aaaa"));
      //signal1->SetLineColor(col_sig_l);
      //signal1->SetFillColor(col_sig_f);
    }
  signal1->SetFillStyle(1001);
  signal2->SetLineColor(12);//col_sig_l2);
  signal2->SetFillColor(34);//col_sig_f2);
  signal2->SetFillStyle(1001);

  bkg->SetLineColor(col_bg_l);
  bkg->SetFillColor(col_bg_f);
  bkg->SetFillStyle(1001);
  bkg->GetXaxis()->SetTitle("m_{4l} [GeV]");
  bkg->GetYaxis()->SetTitle("Events/5 GeV");

  ///////////////
  if(bBW)
    {
      signal->SetLineColor(1);
      signal->SetFillColor(1);
      signal->SetFillStyle(3003);
      signal1->SetLineColor(1);
      signal1->SetFillColor(1);
      signal1->SetFillStyle(3005);
      signal2->SetLineColor(1);
      signal2->SetFillColor(1);
      signal2->SetFillStyle(3004);
      
      bkg->SetLineColor(TColor::GetColor("#aaaaaa"));
      bkg->SetFillColor(TColor::GetColor("#dddddd"));
      bkg->SetFillStyle(1001);
      bkg->GetXaxis()->SetTitle("m_{4l} [GeV]");
      bkg->GetYaxis()->SetTitle("Events/10 GeV");
    }
  /////////////////

  //bkg->GetXaxis()->SetRangeUser(100.,179.99);
  //std::cout<< "===> "<< bkg->Integral()<<std::endl;
  //return 0;

  TCanvas*c1=new TCanvas("c1","",600,600);
  c1->SetMargin(0.12,0.05,0.12,0.05);
  signal->Draw();
  signal1->Draw();
  signal2->Draw();
  bkg->Draw();
  bkgcomp->Draw();
  data->Draw();
  if(addearlyData)
    dataearly->Draw();

  //bkg->GetXaxis()->SetRangeUser(150.,400.);
  THStack*stack;
  THStack*stack1=NULL;
  THStack*stack2=NULL;
  if(!bBW)
    {
      stack=new THStack("stack","");
      stack->Add(bkg);
      stack->Add(signal2);
      stack->Add(signal1);
      stack->Add(signal);
      stack->Draw();
    }
  else
    {     
      stack =new THStack("stack","");
      stack->Add(bkg);
      stack->Add(signal2);
      stack1=new THStack("stack1","");
      stack1->Add(bkg);
      stack1->Add(signal1);
      stack2=new THStack("stack2","");
      stack2->Add(bkg);
      stack2->Add(signal);
    }
  stack->Draw();
  //if(bBW)
    {
      //stack1->Draw();
      //stack2->Draw();
    }
  stack->GetXaxis()->SetRangeUser(80.,249.9);
  //stack->GetXaxis()->SetRangeUser(100.,649.9);
  stack->SetMaximum(9.);
  if(type==4)
    stack->SetMaximum(25.);
  if(fullRange)
    {
      stack->GetXaxis()->SetNdivisions(8,9,5);
      stack->GetXaxis()->SetRangeUser(80.,899.99);//649.9);
      stack->SetMaximum(21.);//13
    }
  stack->GetXaxis()->SetTitle("m_{4l} [GeV]");
  stack->GetYaxis()->SetTitle("Events/5 GeV");
  if(bin==1)
    {
      stack->GetYaxis()->SetTitle("Events/10 GeV");
    }
  if(bin==2)
    {
        stack->GetYaxis()->SetTitle("Events/2 GeV");
    }
  if(fullRange)
    stack->GetYaxis()->SetTitle("Events/10 GeV");
  std::cout << stack->GetYaxis()->GetBinWidth(1)<<std::endl;

  stack->Draw();
  stack->GetXaxis()->SetNdivisions(505);
  stack->GetXaxis()->SetLabelOffset(0.015);
  stack->GetXaxis()->SetTitleOffset(1.05);
  stack->Draw();
  if(bBW)
    {
      stack1->Draw("same");
      stack2->Draw("same");
    }
  bkgcomp->SetFillStyle(1001);
  int col_bg_f2 = kViolet-5;//TColor::GetColor("kViolet-5,");//#ee11bb");
  int col_bg_l2 = kViolet+3,;//TColor::GetColor("");//#551100");
  bkgcomp->SetFillColor(col_bg_f2);
  bkgcomp->SetLineColor(col_bg_l2);
  if(docomp)
    bkgcomp->Draw("same");
  
  systematics->SetMarkerStyle(0);
  systematics->SetLineColor(0);
  systematics->SetFillColor(1);
  systematics->SetFillStyle(3254);
  if(bBW)
    systematics->SetFillStyle(3254);
  if(doSyst)
    systematics->Draw("ae2same");
  const int nx = 200;
  double xx[nx]={0.};
  double exx[nx]={0.};
  double yy[nx]={0.};
  double eyyu[nx]={0.};
  double eyyd[nx]={0.};
  int icount =0;
  for(int i=0;i<nx;i++)
    {
      if(data->GetBinContent(i+1)>0)
	{
	  xx[icount]=data->GetBinCenter(i+1);
	  yy[icount]=data->GetBinContent(i+1);
	  eyyd[icount]=yy[icount]-0.5*TMath::ChisquareQuantile(0.1586555,2.*yy[icount]);
	  eyyu[icount]=0.5*TMath::ChisquareQuantile(1.-0.1586555,2.*(yy[icount]+1))-yy[icount];
	  icount++;

	}
    }
  TGraphAsymmErrors *gr=new TGraphAsymmErrors(icount,xx,yy,exx,exx,eyyd,eyyu);
  gr->SetLineWidth(2);
  gr->SetMarkerStyle(20);
  gr->SetMarkerColor(1);
  gr->Draw("psame");
  if(addearlyData)
    {
      dataearly->SetLineColor(kAzure+1);
      dataearly->Draw("same");
    }
  //TString thetex("#scale[0.55]{#int}Ldt = 4.5 fb^{-1}");// 1.37-1.61 fb^{-1}");
  //TString thetex("#scale[0.55]{#int}Ldt = 3.2 fb^{-1}");// 1.37-1.61 fb^{-1}");
  TString thetex("#scale[0.55]{#int}Ldt = 5.8 fb^{-1}");// 1.37-1.61 fb^{-1}");
  if(type==2)
    thetex="#scale[0.55]{#int}Ldt = 5.9 fb^{-1}";
  //TLatex*tex = new TLatex(0.23,0.57,thetex);
  TLatex*tex = new TLatex(0.26,0.47,thetex);
  tex->SetNDC(kTRUE);
  tex->SetTextFont(42);
  tex->SetTextSize(0.05);
  //if(type!=4)
    {
      tex->SetX(0.61);
      tex->SetY(0.74);
    }
  if(fullRange)
    {
      tex->SetX(0.55);
      tex->SetY(0.40);
    }
  tex->Draw();
  TString thetex2("#sqrt{s} = 8 TeV");
  TLatex*tex2 = new TLatex(0.28,0.41,thetex2);
  tex2->SetNDC(kTRUE);
  tex2->SetTextFont(42);
  tex2->SetTextSize(0.05);
  //if(type!=4)
    {
      tex2->SetX(0.64);
      tex2->SetY(0.68);
    }
  if(fullRange)
    {
      tex2->SetX(0.57);
      tex2->SetY(0.34);
    }
  tex2->Draw();
  TString name("H#rightarrowZZ^{(*)}#rightarrow4l");
  if(type==6)
    name="H#rightarrowZZ^{(*)}#rightarrow2e2#mu";
  if(type==0)
    name="H#rightarrowZZ^{(*)}#rightarrow4#mu";
  if(type==1)
    name="H#rightarrowZZ^{(*)}#rightarrow2#mu2e";
  if(type==2)
    name="H#rightarrowZZ^{(*)}#rightarrow4e";
  if(type==3)
    name="H#rightarrowZZ^{(*)}#rightarrow2e2#mu";

  TLatex *pt = new TLatex(0.27,0.53,name);
  if(type==6)
    pt->SetX(0.24);
  pt->SetNDC(kTRUE);
  pt->SetTextFont(42);
  pt->SetTextSize(0.05);
  //if(type!=4)
    {
      pt->SetX(0.62);
      pt->SetY(0.80);
    }
  if(fullRange)
    {
      pt->SetX(0.56);
      pt->SetY(0.46);
    }
  pt->Draw();
  
  //TLegend*leg0=new TLegend(0.15,0.72, 0.45,0.94); 
  TLegend*leg0=new TLegend(0.15,0.62, 0.45,0.94); 
  if(fullRange)
    {
      leg0->SetX1(0.5);
      leg0->SetX2(0.8);
      leg0->SetY1(0.54);
      leg0->SetY2(0.86);
    }
  leg0->SetFillColor(0);
  leg0->SetLineColor(0);
  leg0->SetTextFont(42);
  leg0->SetTextSize(0.04);
  leg0->AddEntry(data,"Data","p");
  if(addearlyData)
    leg0->AddEntry(dataearly,"Data #leq periodK","l");
  leg0->AddEntry(bkg,"Background ZZ^{(*)}","f");
  if(docomp)
    leg0->AddEntry(bkgcomp,"Background Z+jets, t#bar{t}","f");
  if(!fullRange)
    leg0->AddEntry(signal,"Signal (m_{H}=125 GeV)","f");
  if(!fullRange)
    leg0->AddEntry(signal1,"Signal (m_{H}=150 GeV)","f");
  if(fullRange)
    //leg0->AddEntry(signal,"Signal (m_{H}=360 GeV)","f");
    leg0->AddEntry(signal,"Signal (m_{H}=125 GeV)","f");
  leg0->AddEntry(signal2,"Signal (m_{H}=190 GeV)","f");
  if(fullRange)
    leg0->AddEntry(signal1,"Signal (m_{H}=520 GeV)","f");
  if(doSyst)
    leg0->AddEntry(systematics, "Syst.Unc.", "F");

  leg0->Draw();
  
  TLatex*tex=new TLatex(0.50,0.88,"#it{ATLAS} #bf{Preliminary}");
  //TLatex*tex=new TLatex(0.60,0.88,"#bf{#it{ATLAS}} Internal");
  //TLatex*tex=new TLatex(0.70,0.88,"#bf{#it{ATLAS}}");
  tex->SetNDC(kTRUE);
  tex->SetTextSize(0.05);
  tex->Draw();
  //

  //data->SetMarkerStyle(20);
  //data->Draw("samep");
  
  TString outname("signal125_150_190_");
  if(bin!=0)
    {
      outname+=bin;
      outname+="_";
    }
  
  if(fullRange)
    outname="signal150_190_360_";
  outname+=typein;
  if(bBW)
    {
      outname+="_BW";
    }
  c1->RedrawAxis();
  if(docomp)
    outname+="_comp";
  /*if(fullRange)
    {
      c1->SetLogx();
      c1->Update();
    }
  c1->RedrawAxis();
  */
  
  c1->Print(outname+".eps");
  c1->Print(outname+".png");
  /**
  new TCanvas();
  data->Rebin(4);
  systematics->Rebin(4);
  TH1F* ratio = new TH1F("ratio", "", data->GetNbinsX(), data->GetBinLowEdge(1), data->GetBinLowEdge(data->GetNbinsX()) + data->GetBinWidth(data->GetNbinsX()));
  for (int b=0;b<data->GetNbinsX();b++)
    {
      double aa = systematics->GetBinContent(b + 1);
      double daa= systematics->GetBinError(b + 1);
      double d  = data->GetBinContent(b+1);
      double dd = sqrt(d);
      ratio->SetBinContent(b+1, d/aa);
      ratio->SetBinError(b+1, sqrt(dd/aa*dd/aa+daa*daa*aa*aa/dd*dd));
    }
  ratio->SetMaximum(5.);
  ratio->GetXaxis()->SetRangeUser(160.,599.99);
  //ratio->SetMarkerStyle(20);
  ratio->Draw();
  **/
  return 0;
}

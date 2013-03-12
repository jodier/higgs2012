#include <vector>
#include <stdio.h>
using namespace std;

void GetX1Y1X2Y2(TCanvas *c,double x[4]){
  x[0]=c->GetFrame()->GetX1()+c->GetLeftMargin();
  x[1]=c->GetFrame()->GetY1()+c->GetBottomMargin();
  x[2]=c->GetFrame()->GetX2()-c->GetRightMargin();
  x[3]=c->GetFrame()->GetY2()-c->GetTopMargin();
}


TLegend* CreateLegend(double x_low, double y_low, double x_up, double y_up, 
		      TList* h_list, vector<TString> text, vector<TString> option,
		      double textsize) {
    TLegend *legend = new TLegend(x_low,y_low,x_up,y_up);
    legend->SetBorderSize(0);
    legend->SetTextFont(42);
    legend->SetTextSize(textsize);
    legend->SetFillStyle(0);
    legend->SetFillColor(0);
    legend->SetLineColor(0);

    TIter next(h_list);
    TObject *obj = 0;
    int i=0;
    while( obj = next() ) {
      legend->AddEntry(obj, text[i].Data(), option[i].Data());
      i++;
    }
    return legend;
}


TPaveText* CreatePaveText(double x1, double y1, double x2, double y2, vector<TString> text){
  TPaveText *tex=new TPaveText();
  tex->SetFillColor(0);tex->SetTextSize(0.05);
  tex->SetFillStyle(0);tex->SetBorderSize(0);
  int n=text.size();
  for(int i=0;i<n;i++) tex->AddText(text[i].Data());
  tex->SetX1NDC(x1);
  tex->SetY1NDC(y1);
  tex->SetX2NDC(x2);
  tex->SetY2NDC(y2);
  return tex;
}


void smoothen(double m[], double y[], int np, int N) {
  // computes the smoothened values in a new array
  double s[200];

  // First and last N entries are kept unchanged; 
  // rest obtained averaging 2N+1 neighbors
  for (int i=N+1; i<np-N-1; ++i) {
    //if (160<m[i] && m[i]<180) { s[i]=y[i]; continue; }
    if (150<m[i] && m[i]<190) { N=1; } else N=2;
    s[i] = 0;
    for (int j=-N; j<=N; ++j) s[i]+=y[i+j];
    s[i] /= (2*N+1);
  }
  
  // Copy new values back into the external array
  for (int i=N+1; i<np-N-1; ++i) y[i] = s[i];
  
}


void plotLimit(const char* filename="subchannels/NoZMassConstraint_limit_sub.txt", const char* outname="NoZMassConstraint",bool doExp = false){
  int nn = 0;
  ifstream in;
  in.open(filename, ifstream::in);
	FILE* pFile;
	pFile = fopen("limit.txt","w");

  int const N = 200;

  double n2s [N], n1s [N], p1s [N], p2s [N], median[N], observed[N], mass[N]; // from file
  double N2S [N], N1S [N], P1S [N], P2S [N], Zero[N];  // bands to plot (median is subtracted)

  // Keep original (non-smoothened) values, to plot the difference:
  double o_median[N], o_observed[N];              // original median and observed limits
  double OP2S[N], OP1S[N], ON1S[N], ON2S[N];  // bands to plot (subtracted), from untouched values

  double obs_4mu[N], obs_2mu2e[N], obs_2e2mu[N], obs_4e[N];

  int np = 0;

  if(in.is_open()){
    while(!in.eof()){
      n2s[np] = n1s[np] = p1s[np] = p2s[np] = median[np] = observed[np] = 0; 
      mass[np] = Zero[np] = 0;
      in   >> mass[np] >> n2s[np] >> n1s[np] >> median[np] >> p1s[np] >> p2s[np] >> observed[np] >>obs_4mu[np] >> obs_2mu2e[np]>>obs_2e2mu[np]>>obs_4e[np];
			mass[np] /= 10;
      // store also the original values, for comparison
      o_median[np]=median[np]; o_observed[np]=observed[np];
      // validation
      if(mass[np]<=0) continue; //if(n2s<=0) continue;
      // print to grab also the numbers in a text file
      fprintf(pFile,"%3.0f  %7.4f   %7.4f   %7.4f   %7.4f   %7.4f   %7.4f \n",
	     mass[np], n2s[np], n1s[np], median[np], p1s[np], p2s[np], observed[np] );
      ++np;
    }
  }
 
  // before smoothing, obtain the bands and store original median and observed:
  for (int i=0; i<np; ++i) {
    o_median  [i] = median[i];
    o_observed[i] = observed[i];
    ON2S[i] = o_median[i] - n2s[i];
    ON1S[i] = o_median[i] - n1s[i];
    OP1S[i] = p1s[i] - o_median[i];
    OP2S[i] = p2s[i] - o_median[i];
  }

  // smoothen what needed
  if (nn) { 
    smoothen(mass, n2s, np, nn); 
    smoothen(mass, n1s, np, nn);
    smoothen(mass, p1s, np, nn);
    smoothen(mass, p2s, np, nn);
    //smoothen(mass, median  , np, nn);
    //smoothen(mass, observed, np, nn);
  }

  cout<<"\nSmoothened (N="<<nn<<"): "<<endl;
	fprintf(pFile,"\nSmoothened (N=%d)\n",nn);

  for (int i=0; i<np; ++i)
      fprintf(pFile ,"%3.0f  %7.4f   %7.4f   %7.4f   %7.4f   %7.4f   %7.4f \n",
	     mass[i], n2s[i], n1s[i], median[i], p1s[i], p2s[i], observed[i] );
  

  // Compute values to use in TGraphAsymmErrors after smoothing
  for (int i=0; i<np; ++i) {
    N2S[i] = median[i] - n2s[i];
    N1S[i] = median[i] - n1s[i];
    P1S[i] = p1s[i] - median[i];
    P2S[i] = p2s[i] - median[i];
  }
  
  TGraph *likelihd_limit_d = new TGraph(np,mass,observed);
  likelihd_limit_d->SetLineColor(kBlack);
  likelihd_limit_d->SetLineWidth(2);
  likelihd_limit_d->SetLineStyle(1);
  TGraph *likelihd_limit_c = new TGraph(np,mass,median);
  likelihd_limit_c->SetLineColor(kBlack);
  likelihd_limit_c->SetLineStyle(2);
  likelihd_limit_c->SetLineWidth(2);

  TGraph *gr_obs_4mu = new TGraph(np,mass,obs_4mu);
  gr_obs_4mu ->SetLineColor(2);
  gr_obs_4mu ->SetLineWidth(2);
  TGraph *gr_obs_2mu2e = new TGraph(np,mass,obs_2mu2e);
  gr_obs_2mu2e ->SetLineColor(4);
  gr_obs_2mu2e ->SetLineWidth(2);
  TGraph *gr_obs_2e2mu = new TGraph(np,mass,obs_2e2mu);
  gr_obs_2e2mu ->SetLineColor(6);
  gr_obs_2e2mu ->SetLineWidth(2);
  TGraph *gr_obs_4e = new TGraph(np,mass,obs_4e);
  gr_obs_4e ->SetLineColor(8);
  gr_obs_4e ->SetLineWidth(2);
  
  TGraphAsymmErrors *likelihd_limit_1sigma = new
    TGraphAsymmErrors(np,mass,median,Zero,Zero,N1S,P1S);
  likelihd_limit_1sigma->SetFillColor(kGreen);
  TGraphAsymmErrors *likelihd_limit_2sigma = new
    TGraphAsymmErrors(np,mass,median,Zero,Zero,N2S,P2S);
  //TGraphAsymmErrors(np,mass,median,Zero,Zero,new_N2S,P2S);
  likelihd_limit_2sigma->SetFillColor(kYellow);
  
  //TMultiGraph *likelihd_limit = new TMultiGraph("exclusionlimit_p","CL_{S} Exclusion Limits ;m_{H} [GeV]; 95% C.L. limit on #sigma/#sigma_{SM}");
  TMultiGraph *likelihd_limit = new TMultiGraph("exclusionlimit_p",";m_{H} [GeV]; 95% C.L. limit on #sigma/#sigma_{SM}");
  likelihd_limit->Add(likelihd_limit_2sigma,"E3");
  likelihd_limit->Add(likelihd_limit_1sigma,"E3");
  likelihd_limit->Add(likelihd_limit_c, "L");
  likelihd_limit->Add(likelihd_limit_d, "L");
  likelihd_limit->Add(gr_obs_4mu, "L");
  likelihd_limit->Add(gr_obs_2mu2e, "L");
  likelihd_limit->Add(gr_obs_2e2mu, "L");
  likelihd_limit->Add(gr_obs_4e, "L");
  
  
  
  TCanvas *cv =new TCanvas("cv","",600,600); 
  //TCanvas *cv =new TCanvas("canvas","",1024,768); 
  //cv ->SetLogy();
  double x[4];
  GetX1Y1X2Y2(cv,x);
  double x1=x[0]; double y1=x[1]; double x2=x[2]; double y2=x[3];
  TLine* line=new TLine(95,1.0,610,1.0);
  line->SetLineColor(kRed);
  line->SetLineStyle(2);
  line->SetLineWidth(2);
  
  TList *leglist=new TList();
  vector<TString> legtext;
  vector<TString> legopt;
  leglist->Add(likelihd_limit_d);legtext.push_back("Observed");legopt.push_back("L");
  leglist->Add(likelihd_limit_c);legtext.push_back("Expected");legopt.push_back("L");
  leglist->Add(likelihd_limit_1sigma);legtext.push_back("#pm 1#sigma");legopt.push_back("F");
  leglist->Add(likelihd_limit_2sigma);legtext.push_back("#pm 2#sigma");legopt.push_back("F");
  TString logname("Observed");
  if(doExp){ logname = "Expected";}
  leglist->Add(gr_obs_4mu);legtext.push_back(Form("%s 4#mu",logname.Data()));legopt.push_back("L");
  leglist->Add(gr_obs_2mu2e);legtext.push_back(Form("%s 2#mu2e",logname.Data()));legopt.push_back("L");
  leglist->Add(gr_obs_2e2mu);legtext.push_back(Form("%s 2e2#mu",logname.Data()));legopt.push_back("L");
  leglist->Add(gr_obs_4e);legtext.push_back(Form("%s 4e",logname.Data()));legopt.push_back("L");
  

  TLegend* legend=CreateLegend(x2-0.75,y2-0.35,x2-0.50,y2-0.04,leglist,legtext,legopt,0.05);
  vector<TString> pavetext;
  pavetext.push_back("#it{ATLAS} #bf{Internal}");
  pavetext.push_back("  #bf{H#rightarrow ZZ^{(*)}#rightarrow 4l}");
  pavetext.push_back("  #bf{#lower[-0.15]{#scale[0.6]{#int}}Ldt = 4.8 fb^{-1}}");
  pavetext.push_back("  #bf{#sqrt{s}=7TeV}");
  //pavetext.push_back("  #bf{#lower[-0.15]{#scale[0.6]{#int}}Ldt = 5.8 fb^{-1}}");
  //pavetext.push_back("  #bf{#sqrt{s}=8TeV}");
  TPaveText* text=CreatePaveText(x2-0.35,y2-0.28,x2-0.1,y2-0.10,pavetext);
  
  likelihd_limit->Draw("AP");
  
 
  //likelihd_limit->GetYaxis()->SetRangeUser(0.1,900);
  likelihd_limit->GetYaxis()->SetRangeUser(0.,19.999);
  likelihd_limit->GetYaxis()->SetTitleSize(0.045);
  likelihd_limit->GetXaxis()->SetTitleSize(0.045);
  legend->Draw("same");
  text->Draw("same");
  line ->Draw("same");

  if(!doExp){
    cv->Print(Form("%s_Limit_Sub.eps",outname));
    cv->Print(Form("%s_Limit_Sub.C",outname));
  }
  else{
    cv->Print(Form("%s_Limit_SubExp.eps",outname));
    cv->Print(Form("%s_Limit_SubExp.C",outname));
  }

  likelihd_limit->GetYaxis()->SetRangeUser(0.1,900.);
  cv->SetLogy();
  cv->Update();
  if(!doExp){
    cv->Print(Form("%s_Limit_Sub_Log.eps",outname));
    cv->Print(Form("%s_Limit_Sub_Log.C",outname));
  }
  else {
    cv->Print(Form("%s_Limit_SubExp_Log.eps",outname));
    cv->Print(Form("%s_Limit_SubExp_Log.C",outname));
  }

  likelihd_limit->GetXaxis()->SetRangeUser(110,179.99);
  cv->Update();
  if(!doExp){ 
    cv->Print(Form("%s_Limit_Sub_LowMass.eps",outname));
    cv->Print(Form("%s_Limit_Sub_LowMass.C",outname));
  }else{
    cv->Print(Form("%s_Limit_SubExp_LowMass.eps",outname));
    cv->Print(Form("%s_Limit_SubExp_LowMass.C",outname));
  }

  likelihd_limit->GetXaxis()->SetRangeUser(180,599.99);
  cv->Update();
  if(!doExp){
    cv->Print(Form("%s_Limit_Sub_HighMass.eps",outname));
    cv->Print(Form("%s_Limit_Sub_HighMass.C",outname));
  }else{ 
    cv->Print(Form("%s_Limit_SubExp_HighMass.eps",outname));
    cv->Print(Form("%s_Limit_SubExp_HighMass.C",outname));
  }

	fclose(pFile);
}

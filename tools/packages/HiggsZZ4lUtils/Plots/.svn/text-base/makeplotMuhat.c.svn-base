int makeplotMuhat(const char* inname="muhat_v2/test_muhat.txt",const char* outname="NoZMassConstraint_muhat"){
  vector<double> mass, muhat, muhat_e, zero;
  //fstream filestr("muhat_v2/test_muhat.txt", fstream::in);
  fstream filestr(inname, fstream::in);
  do{
    double mm, mh, mh_e;
    filestr >> mm >> mh >> mh_e;
    mass.push_back(mm/10.);
    muhat.push_back(mh);
    muhat_e.push_back(mh_e);
    zero.push_back(0);
  }while(!filestr.eof());
  filestr.close();
  cout<<"Total: "<<mass.size()<<endl;

  TGraphErrors* grmuError = new TGraphErrors(mass.size(), &mass[0], &muhat[0],&zero[0],&muhat_e[0]);
  grmuError ->SetFillColor(kCyan);
  TGraph* grmu = new TGraph(mass.size(), &mass[0], &muhat[0]);
  TCanvas* canvas = new TCanvas("canvas","",600,600);
  canvas->SetMargin(0.13,0.05,0.12,0.05);
  //canvas->SetLogy();
  canvas ->SetGridy();
  grmu  ->SetLineWidth(2);
  grmu  ->SetLineStyle(1);
  TMultiGraph* mult = new TMultiGraph("mult",";m_{H} [GeV]; #mu");
  mult ->Add(grmuError,"E3");
  mult ->Add(grmu, "L");

  mult ->Draw("AP");
  mult ->GetYaxis()->SetRangeUser(-3,4);
  //mult ->Draw("AP");
  TLegend*leg0=new TLegend(0.16,0.15,0.53,0.35);////0.25);
  leg0->SetFillColor(0);
  leg0->SetLineColor(0);
  leg0->SetTextFont(42);
  leg0->SetTextSize(0.05);
 
  leg0 ->AddEntry(grmu,"Best Fit","l");
  leg0 ->AddEntry(grmuError,"#pm 1#sigma","f");
  leg0 ->Draw("same");

  TLatex l;
  l.SetNDC();
  l.SetTextFont(42);
  l.SetTextSize(0.05);
  l.SetTextColor(1);
  l.SetTextAlign(12);
  TLatex* l1 = l.DrawLatex(0.52,0.40,"#bf{#it{ATLAS}} Internal");//:Preliminary");
  //TLatex* l1 = l.DrawLatex(0.66,0.35,"#bf{#it{ATLAS}}");//
  TLatex* l2 = l.DrawLatex(0.63,0.30,"H#rightarrow ZZ^{(*)}#rightarrow 4l");
  //TLatex* l3 = l.DrawLatex(0.63,0.23,"#lower[-0.15]{#scale[0.6]{#int}}Ldt = 4.8 fb^{-1}");
  //TLatex* l4 = l.DrawLatex(0.63,0.18,"#sqrt{s}=7 TeV");
  //TLatex* l3 = l.DrawLatex(0.63,0.23,"#lower[-0.15]{#scale[0.6]{#int}}Ldt = 3.2 fb^{-1}");
  //TLatex* l4 = l.DrawLatex(0.63,0.18,"#sqrt{s}=8 TeV");
  TLatex* l3 = l.DrawLatex(0.63,0.23,"#lower[-0.15]{#scale[0.6]{#int}}Ldt =4.8+ 3.2 fb^{-1}");
  TLatex* l4 = l.DrawLatex(0.63,0.18,"#sqrt{s}=7+8 TeV");

  //TLatex* tck=new TLatex();
  //tck->SetNDC();
  //tck->SetTextFont(42);
  //tck->SetTextSize(0.05);
  //TLatex* tck0=tck->DrawLatex(0.095,0.065,"100");
  canvas ->SaveAs(Form("%s_muhat.eps",outname)); 

  mult ->GetXaxis()->SetRangeUser(110.,169.99);
  canvas ->Update();
  canvas ->Print(Form("%s_muhatZoom.eps",outname)); 
} 

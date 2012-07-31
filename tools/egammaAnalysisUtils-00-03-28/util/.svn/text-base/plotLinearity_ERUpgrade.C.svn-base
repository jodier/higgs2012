// eta : from cluster
// emin, emax : energies (NOT transverse), in GeV
// ptype : 0 (electron), 1 (unconverted photon), 2 (converted photon)
// year : "2011" or "2012", Z scales
// syst : use "es2010" for now
// logx : 0/1

TGraph* plotLinearity_ERUpgrade(double eta, double emin /* GeV */, double emax /* GeV */, int ptype, 
				string year, string syst, bool logx=false, TGraph* overlay=0) {

  double GeV = 1000;

   gROOT->ProcessLine(".L EnergyRescalerUpgrade.cxx");
  
   egRescaler::EnergyRescalerUpgrade ers;
   ers.Init("../share/EnergyRescalerData.root",year,syst);

   double eMin = emin*GeV;
   double eMax = emax*GeV;
   int nStep = 100;
   if( logx )
     eStep = (log(eMax)-log(eMin))/(double)nStep;
   else
     eStep = (eMax-eMin)/(double)nStep;
   double e = eMin;

   TGraph* gNom = new TGraph();        // nominal scale correction
   TGraph* gZeeUp = new TGraph();      // Zee scale uncertainty, Up
   TGraph* gZeeDown = new TGraph();    //                      , Down
   TGraph* gMATUp = new TGraph();      //       MAT uncertainty, Up
   TGraph* gMATDown = new TGraph();    //                      , Down
   TGraph* gPSUp = new TGraph();       //        ps uncertainty, Up
   TGraph* gPSDown = new TGraph();     //                      , Down
   TGraph* gLPTUp = new TGraph();       //   low pt uncertainty, Up
   TGraph* gLPTDown = new TGraph();     //                     , Down

   int i=0;

   while( e<=eMax ) {

     double eNominal    = ers.applyEnergyCorrection(eta, e*cosh(eta), ptype, egRescaler::EnergyRescalerUpgrade::Nominal);

     double eVarZeeUp   = ers.applyEnergyCorrection(eta, e*cosh(eta), ptype, egRescaler::EnergyRescalerUpgrade::ZeeMethodUp);
     double eVarZeeDown = ers.applyEnergyCorrection(eta, e*cosh(eta), ptype, egRescaler::EnergyRescalerUpgrade::ZeeMethodDown);

     double eVarMATUp   = ers.applyEnergyCorrection(eta, e*cosh(eta), ptype, egRescaler::EnergyRescalerUpgrade::R12StatUp);
     double eVarMATDown = ers.applyEnergyCorrection(eta, e*cosh(eta), ptype, egRescaler::EnergyRescalerUpgrade::R12StatDown);

     double eVarPSUp    = ers.applyEnergyCorrection(eta, e*cosh(eta), ptype, egRescaler::EnergyRescalerUpgrade::PSStatUp);
     double eVarPSDown  = ers.applyEnergyCorrection(eta, e*cosh(eta), ptype, egRescaler::EnergyRescalerUpgrade::PSStatDown);

     double eVarLPTUp   = ers.applyEnergyCorrection(eta, e*cosh(eta), ptype, egRescaler::EnergyRescalerUpgrade::LowPtUp);
     double eVarLPTDown = ers.applyEnergyCorrection(eta, e*cosh(eta), ptype, egRescaler::EnergyRescalerUpgrade::LowPtDown);


     cout << "plotL " << e << " " << eNominal << " " 
	  << (eVarZeeUp-eNominal)/eNominal << " " << (eVarZeeDown-eNominal)/eNominal << " " 
	  << (eVarMATUp-eNominal)/eNominal << " " << (eVarMATDown-eNominal)/eNominal << " " 
	  << (eVarPSUp-eNominal)/eNominal << " " << (eVarPSDown-eNominal)/eNominal << endl;

     gNom->SetPoint(i, e/GeV, 0.); 

     gZeeUp->SetPoint(i, e/GeV, (eVarZeeUp-eNominal)/eNominal); 
     gZeeDown->SetPoint(i, e/GeV, (eVarZeeDown-eNominal)/eNominal); 

     gMATUp->SetPoint(i, e/GeV, (eVarMATUp-eNominal)/eNominal); 
     gMATDown->SetPoint(i, e/GeV, (eVarMATDown-eNominal)/eNominal); 

     gPSUp->SetPoint(i, e/GeV, (eVarPSUp-eNominal)/eNominal); 
     gPSDown->SetPoint(i, e/GeV, (eVarPSDown-eNominal)/eNominal); 

     gLPTUp->SetPoint(i, e/GeV, (eVarLPTUp-eNominal)/eNominal); 
     gLPTDown->SetPoint(i, e/GeV, (eVarLPTDown-eNominal)/eNominal); 


     i++;

     if( logx )
       e *= exp(eStep);
     else
       e += eStep;

   }
 
   TCanvas* canvas = new TCanvas();
   if( logx )
     canvas->SetLogx();

   gNom->SetMaximum(.03);
   gNom->SetMinimum(-.03);
   if( abs(eta)>=1.37 && abs(eta)<=1.52 ) {
     gNom->SetMaximum(.1);
     gNom->SetMinimum(-.1);
   }

   char grafname[99];
   if( ptype==0 )
     sprintf(grafname,"ES Uncertainty (%s), #eta = %4.2f, Electrons",syst.c_str(),eta);
   else if( ptype==1 )
     sprintf(grafname,"ES Uncertainty (%s), #eta = %4.2f, Unconverted photons",syst.c_str(),eta);
   else if( ptype==2 )
     sprintf(grafname,"ES Uncertainty (%s), #eta = %4.2f, Converted photons",syst.c_str(),eta);
   gNom->SetTitle(grafname);
   
   gNom->SetLineColor(4);
   gNom->SetLineWidth(2);
   gNom->SetLineStyle(1);
   gNom->GetXaxis()->SetTitleOffset(1.2*gNom->GetXaxis()->GetTitleOffset());
   gNom->GetYaxis()->SetTitleOffset(1.2*gNom->GetYaxis()->GetTitleOffset());
   gNom->GetXaxis()->SetTitle("E_{T} [MeV]");
   gNom->GetYaxis()->SetTitle("#delta E/E");
   gNom->Draw("AL");
   
   gZeeUp->SetLineWidth(2);
   gZeeUp->SetLineStyle(3);
   gZeeUp->SetLineColor(4);
   gZeeUp->Draw("L");

   gZeeDown->SetLineWidth(2);
   gZeeDown->SetLineStyle(2);
   gZeeDown->SetLineColor(4);
   gZeeDown->Draw("L");

   gMATUp->SetLineWidth(2);
   gMATUp->SetLineStyle(3);
   gMATUp->SetLineColor(2);
   gMATUp->Draw("L");

   gMATDown->SetLineWidth(2);
   gMATDown->SetLineStyle(2);
   gMATDown->SetLineColor(2);
   gMATDown->Draw("L");

   gPSUp->SetLineWidth(2);
   gPSUp->SetLineStyle(3);
   gPSUp->SetLineColor(6);
   gPSUp->Draw("L");

   gPSDown->SetLineWidth(2);
   gPSDown->SetLineStyle(2);
   gPSDown->SetLineColor(6);
   gPSDown->Draw("L");

   gLPTUp->SetLineWidth(2);
   gLPTUp->SetLineStyle(3);
   gLPTUp->SetLineColor(8);
   gLPTUp->Draw("L");

   gLPTDown->SetLineWidth(2);
   gLPTDown->SetLineStyle(2);
   gLPTDown->SetLineColor(8);
   gLPTDown->Draw("L");

   gNom->Draw("L");

   TLegend* leg = new TLegend(.68,.15,.88,.4);
   leg->SetBorderSize(0);
   leg->SetFillColor(0);
   leg->AddEntry(gZeeUp,"#alpha, up", "l");
   leg->AddEntry(gZeeDown,"#alpha, down", "l");
   leg->AddEntry(gMATUp,"MAT, up", "l");
   leg->AddEntry(gMATDown,"MAT, down", "l");
   leg->AddEntry(gPSUp,"PS, up", "l");
   leg->AddEntry(gPSDown,"PS, down", "l");
   leg->AddEntry(gLPTUp,"Low-pt, up", "l");
   leg->AddEntry(gLPTDown,"Low-pt, down", "l");

   // if( overlay ) {
   //   for(int i=0; i<overlay->GetN(); i++) {
   //     double x,y;
   //     overlay->GetPoint(i,x,y);
   //     overlay->SetPoint(i,x*GeV/cosh(eta),y);
   //   }
   //   overlay->SetMarkerStyle(21);
   //   overlay->SetMarkerColor(1);
   //   overlay->SetMarkerSize(gZee->GetMarkerSize());
   //   overlay->Draw("psame");
   //   leg->AddEntry(overlay,"E/p", "p");
   // }

   leg->Draw("same");

   // char plotname[99];
   // sprintf(plotname,"linearity_%d_%2.1f.png",ptype,eta);
   // canvas.SaveAs(plotname);
   
   return gNom;
}




void plotloop() {

  TFile f("plotLinearityInClusterE.root");

  for(int i=0; i<24; i++) {
    char graphname[99];
    sprintf(graphname,"eBinning_graph_DATA_eta_%d",i);
    double eta = (double)i/10. + 0.05;
    TGraph* graph = (TGraph*) f.Get(graphname);
    plotLinearity_ERUpgrade(eta,25000.,70000.,0,"2011",graph);
  }

}


TGraph* plotConstantTerm_ERUpgrade(double etamin, double etamax) {

   gROOT->ProcessLine(".L EnergyRescalerUpgrade.cxx");
  
   egRescaler::EnergyRescalerUpgrade  ers;
   ers.Init("../share/EnergyRescalerData.root","2011","es2010");

   double etaMin = etamin;
   double etaMax = etamax;
   double etaStep = .01;
   double eta = etaMin;

   TGraph* gAF = new TGraph();
   int i=0;

   while( eta<=etaMax ) {

     gAF->SetPoint( i, eta, ers.dataConstantTerm(eta) );

     i++;
     eta += etaStep;

   }
 
   TCanvas * canvas = new TCanvas();

   gAF->SetMaximum(.05);
   gAF->SetMinimum(-.05);

   char grafname[99];
   sprintf(grafname,"Constant term (==smearing correction)");
   gAF->SetTitle(grafname);
   
   gAF->SetLineWidth(2);
   gAF->SetLineStyle(2);
   gAF->SetLineColor(4);
   gAF->GetXaxis()->SetTitleOffset(1.5);
   gAF->GetXaxis()->SetTitle("#eta");
   gAF->Draw("AL");
   
   char plotname[99];
   sprintf(plotname,"scale.png");
   canvas->SaveAs(plotname);

   return gAF;

}

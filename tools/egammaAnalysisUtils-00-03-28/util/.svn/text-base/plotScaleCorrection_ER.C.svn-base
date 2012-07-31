/* test the AF->G4 correction
ln -sf ../Root/EnergyRescaler.cxx
ln -sf ../egammaAnalysisUtils
root -l
.L EnergyRescaler.cxx+
.L plotScaleCorrection.C+
plotScaleCorrection( 45. )
*/

#include "egammaAnalysisUtils/EnergyRescaler.h"

#include <iostream>
#include <vector>

#include "TGraph.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TROOT.h"

TGraph* plotScaleCorrection_ER(double Energy, double etamin, double etamax, std::string year) {

   gROOT->ProcessLine(".L EnergyRescaler.cxx");
  
   eg2011::EnergyRescaler  ers;
   ers.useDefaultCalibConstants(year);

   double etaMin = etamin;
   double etaMax = etamax;
   double etaStep = .01;
   double eta = etaMin;

   TGraph* gAF = new TGraph();
   int i=0;

   while( eta<=etaMax ) {

     gAF->SetPoint( i, eta, Energy/ers.applyEnergyCorrectionGeV(eta, 0., Energy, Energy, 0, "ELECTRON")-1. );

     i++;
     eta += etaStep;

   }
 
   TCanvas * canvas = new TCanvas();

   gAF->SetMaximum(.05);
   gAF->SetMinimum(-.05);

   char grafname[99];
   sprintf(grafname,"Data calibration factor");
   gAF->SetTitle(grafname);
   
   gAF->SetLineWidth(2);
   gAF->SetLineStyle(2);
   gAF->SetLineColor(4);
   gAF->GetXaxis()->SetTitleOffset(1.5);
   gAF->GetXaxis()->SetTitle("#eta");
   gAF->GetXaxis()->SetRangeUser(etaMin, etaMax);
   gAF->Draw("AL");
   
   char plotname[99];
   sprintf(plotname,"scale.png");
   canvas->SaveAs(plotname);
   
   return gAF;
}

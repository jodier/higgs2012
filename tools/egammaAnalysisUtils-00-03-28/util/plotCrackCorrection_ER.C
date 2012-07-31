/* test the Crack correction
ln -sf ../Root/EnergyRescaler.cxx
ln -sf ../egammaAnalysisUtils
root -l
.L EnergyRescaler.cxx+
.L plotCrackCorrection.C+
plotCrackCorrection(1.5)
*/

#include "egammaAnalysisUtils/EnergyRescaler.h"

#include <iostream>
#include <vector>

#include "TGraph.h"
#include "TCanvas.h"
#include "TAxis.h"

void plotCrackCorrection(double eta){

   eg2011::EnergyRescaler  ers;

   double eMin = 0.;
   double eMax = 100.;
   double eStep = 1;
   double e = eMin;

   TGraph* gCrack = new TGraph();
   int i=0;

   while( e<=eMax ) {

     gCrack->SetPoint( i, e, ers.applyMCCalibrationGeV(eta, e, "ELECTRON") );

     i++;
     e += eStep;

   }
 
   TCanvas * canvas = new TCanvas();

   gCrack->SetMaximum(1.2);
   gCrack->SetMinimum(0.7);

   char grafname[99];
   sprintf(grafname,"ET Correction factor, #eta = %4.2f",eta);
   gCrack->SetTitle(grafname);
   
   gCrack->SetLineWidth(2);
   gCrack->SetLineStyle(2);
   gCrack->SetLineColor(4);
   gCrack->GetXaxis()->SetTitleOffset(1.5);
   gCrack->GetXaxis()->SetTitle("E_{T} [GeV]");
   gCrack->Draw("AL");
   
   char plotname[99];
   sprintf(plotname,"crack_%f.png",eta);
   canvas->SaveAs(plotname);
   
}

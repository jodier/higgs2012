/* test the smearing correction
ln -sf ../Root/EnergyRescaler.cxx
ln -sf ../egammaAnalysisUtils
root -l
.L EnergyRescaler.cxx+
.L plotEResolution.C+
plotEResolution(0.5)
*/

#include "egammaAnalysisUtils/EnergyRescaler.h"

#include <iostream>
#include <vector>

#include "TROOT.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TH1D.h"

void plotEResolution_ER(double eta){
  
   gROOT->ProcessLine(".L EnergyRescaler.cxx");
  
   eg2011::EnergyRescaler  ers;

   double eMin = 10.;
   double eMax = 1000.;
   int nPts = 25;
   double eStep = (log(eMax)-log(eMin))/nPts;
   double e = eMin;

   TGraph* gResolMC = new TGraph(nPts);
   TGraph* gResolData = new TGraph(nPts);
   TGraph* gResolUp = new TGraph(nPts);
   TGraph* gResolDown = new TGraph(nPts);
   TGraph* gTotUp = new TGraph(nPts);
   TGraph* gTotDown = new TGraph(nPts);
   TGraph* gTotRelUp = new TGraph(nPts);
   TGraph* gTotRelDown = new TGraph(nPts);
   TGraph* gCstUp = new TGraph(nPts);
   TGraph* gCstDown = new TGraph(nPts);

   TGraph* gSmearing = new TGraph(nPts);
   TGraph* gSmearingUp = new TGraph(nPts);
   TGraph* gSmearingDown = new TGraph(nPts);
   
   TGraphErrors* gToy = new TGraphErrors(nPts);
   TGraphErrors* gToyUp = new TGraphErrors(nPts);
   TGraphErrors* gToyDown = new TGraphErrors(nPts);

   TGraphErrors* gToyCT= new TGraphErrors(nPts);
   TGraphErrors* gToyCTUp = new TGraphErrors(nPts);
   TGraphErrors* gToyCTDown = new TGraphErrors(nPts);

   TH1D hsm("hsm","hsm",1000,0.75,1.25);
   TH1D hsmUp("hsmUp","hsmUp",1000,0.75,1.25);
   TH1D hsmDown("hsmDown","hsmDown",1000,0.75,1.25);

   TH1D hsmCT("hsmCT","hsmCT",1000,0.75,1.25);
   TH1D hsmCTUp("hsmCTUp","hsmCTUp",1000,0.75,1.25);
   TH1D hsmCTDown("hsmCTDown","hsmCTDown",1000,0.75,1.25);

   int i=0;

   while( i <= nPts ) {

     double erup, erdo;

     ers.resolutionError( e, eta, erup, erdo );
     gTotUp->SetPoint( i, e, erup );
     gTotDown->SetPoint( i, e, erdo );
     gTotRelUp->SetPoint( i, e, erup/ers.resolution( e, eta, true ) );
     gTotRelDown->SetPoint( i, e, erdo/ers.resolution( e, eta, true ) );

     gCstUp->SetPoint( i, e, ers.dataConstantTermUpError( eta ) );
     gCstDown->SetPoint( i, e, ers.dataConstantTermDownError( eta ) );

     gResolMC->SetPoint( i, e, ers.resolution( e, eta, false ) );
     gResolData->SetPoint( i, e, ers.resolution( e, eta, true ) );
     gResolUp->SetPoint( i, e, ers.resolution( e, eta, true ) + erup );
     gResolDown->SetPoint( i, e, ers.resolution( e, eta, true ) + erdo );

     double smearing = pow( ers.resolution( e, eta, true ), 2 ) -  pow( ers.resolution( e, eta, false ), 2 );
     if( smearing>0 )
       smearing = sqrt(smearing);
     else
       smearing = 0;
     gSmearing->SetPoint( i, e, smearing );

     double smearup = pow( ers.resolution( e, eta, true )+erup, 2 ) -  pow( ers.resolution( e, eta, false ), 2 );
     if( smearup>0 )
       smearup = sqrt(smearup);
     else
       smearup = 0;
     gSmearingUp->SetPoint( i, e, smearup );

     double smeardown = pow( ers.resolution( e, eta, true )+erdo, 2 ) -  pow( ers.resolution( e, eta, false ), 2 );
     if( smeardown>0 )
       smeardown = sqrt(smeardown);
     else
       smeardown = 0;
     gSmearingDown->SetPoint( i, e, smeardown );

     // test smearing
     hsm.Reset();
     hsmUp.Reset();
     hsmDown.Reset();
     hsmCT.Reset();
     hsmCTUp.Reset();
     hsmCTDown.Reset();
     for( int ievt=0; ievt<1000; ievt++ ) {
       double esm = ers.getSmearingCorrectionGeV(eta, e, 0, false);
       hsm.Fill( esm );
       esm = ers.getSmearingCorrectionGeV(eta, e, 1, false);
       hsmDown.Fill( esm );
       esm = ers.getSmearingCorrectionGeV(eta, e, 2, false);
       hsmUp.Fill( esm );
       esm = ers.getSmearingCorrectionGeV(eta, e, 0, true);
       hsmCT.Fill( esm );
       esm = ers.getSmearingCorrectionGeV(eta, e, 1, true);
       hsmCTDown.Fill( esm );
       esm = ers.getSmearingCorrectionGeV(eta, e, 2, true);
       hsmCTUp.Fill( esm );
     }

     gToy->SetPoint( i, e, hsm.GetRMS() );
     gToy->SetPointError( i, 0, hsm.GetRMSError() );
     gToyUp->SetPoint( i, e, hsmUp.GetRMS() );
     gToyUp->SetPointError( i, 0, hsmUp.GetRMSError() );
     gToyDown->SetPoint( i, e, hsmDown.GetRMS() );
     gToyDown->SetPointError( i, 0, hsmDown.GetRMSError() );

     gToyCT->SetPoint( i, e, hsmCT.GetRMS() );
     gToyCT->SetPointError( i, 0, hsmCT.GetRMSError() );
     gToyCTUp->SetPoint( i, e, hsmCTUp.GetRMS() );
     gToyCTUp->SetPointError( i, 0, hsmCTUp.GetRMSError() );
     gToyCTDown->SetPoint( i, e, hsmCTDown.GetRMS() );
     gToyCTDown->SetPointError( i, 0, hsmCTDown.GetRMSError() );

     i++;
     e *= exp(eStep);

   }
 
   TCanvas * canvas = new TCanvas("canvas","canvas",600,800);
   canvas->Divide(1,2);

   canvas->cd(1);
   gPad->SetLogx();

   gResolUp->SetMaximum(0.07);
   gResolUp->SetMinimum(0);
   gResolUp->GetXaxis()->SetMoreLogLabels();
   char grafname[99];
   sprintf(grafname,"#sigma/E    #eta = %3.1f",eta);
   gResolUp->SetTitle(grafname);
   
   gResolUp->SetLineWidth(2);
   gResolUp->SetLineStyle(2);
   gResolUp->SetLineColor(4);
   gResolUp->GetXaxis()->SetTitleOffset(1.5);
   gResolUp->GetXaxis()->SetTitle("E [GeV]");
   gResolUp->Draw("AL");
   
   gResolDown->SetLineWidth(2);
   gResolDown->SetLineStyle(2);
   gResolDown->SetLineColor(4);
   gResolDown->Draw("L");
   
   gResolData->SetLineWidth(2);
   gResolData->SetLineStyle(1);
   gResolData->SetLineColor(4);
   gResolData->Draw("L");
   
   gResolMC->SetLineWidth(2);
   gResolMC->SetLineStyle(1);
   gResolMC->SetLineColor(2);
   gResolMC->Draw("L");
   

   canvas->cd(2);
   gPad->SetLogx();

   gSmearingUp->SetMaximum(0.05);
   gSmearingUp->SetMinimum(0);
   sprintf(grafname,"Smearing correction (relative to Energy)    #eta = %3.1f",eta);
   gSmearingUp->SetTitle(grafname);
   gSmearingUp->SetLineWidth(2);
   gSmearingUp->SetLineStyle(2);
   gSmearingUp->SetLineColor(4);
   gSmearingUp->GetXaxis()->SetTitleOffset(1.5);
   gSmearingUp->GetXaxis()->SetTitle("E [GeV]");
   gSmearingUp->Draw("AL");
   
   gSmearingDown->SetLineWidth(2);
   gSmearingDown->SetLineStyle(2);
   gSmearingDown->SetLineColor(4);
   gSmearingDown->Draw("L");
  
   gSmearing->SetLineWidth(2);
   gSmearing->SetLineStyle(1);
   gSmearing->SetLineColor(4);
   gSmearing->Draw("L");
   
   gToy->Draw("p");
   gToyUp->Draw("p");
   gToyDown->Draw("p");

   gToyCT->SetLineColor(2);
   gToyCTUp->SetLineColor(2);
   gToyCTDown->SetLineColor(2);
   gToyCT->Draw("p");
   gToyCTUp->Draw("p");
   gToyCTDown->Draw("p");


   char plotname[99];
   sprintf(plotname,"res_1_%f.png",eta);
   canvas->SaveAs(plotname);
   

   TCanvas * canvas2 = new TCanvas("canvas2","canvas2",600,800);
   canvas2->Divide(1,2);

   canvas2->cd(1);
   gPad->SetLogx();

   gTotUp->SetMaximum(0.02);
   gTotUp->SetMinimum(-0.02);
   gTotUp->GetXaxis()->SetMoreLogLabels();
   
   sprintf(grafname,"#Delta#sigma/E    #eta = %3.1f",eta);
   gTotUp->SetTitle(grafname);
   
   gTotUp->SetLineWidth(2);
   gTotUp->SetLineStyle(1);
   gTotUp->SetLineColor(2);
   gTotUp->GetXaxis()->SetTitleOffset(1.5);
   gTotUp->GetXaxis()->SetTitle("E [GeV]");
   gTotUp->Draw("AL");
   
   gTotDown->SetLineWidth(2);
   gTotDown->SetLineStyle(1);
   gTotDown->SetLineColor(2);
   gTotDown->Draw("L");
   
   gCstUp->SetLineWidth(2);
   gCstUp->SetLineStyle(2);
   gCstUp->SetLineColor(4);
   gCstUp->Draw("L");
   
   gCstDown->SetLineWidth(2);
   gCstDown->SetLineStyle(2);
   gCstDown->SetLineColor(4);
   gCstDown->Draw("L");
   
   
   canvas2->cd(2);
   gPad->SetLogx();

   gTotRelUp->SetMaximum(0.3);
   gTotRelUp->SetMinimum(-0.3);
   gTotRelUp->GetXaxis()->SetMoreLogLabels();
   
   sprintf(grafname,"#Delta#sigma/#sigma    #eta = %3.1f",eta);
   gTotRelUp->SetTitle(grafname);
   
   gTotRelUp->SetLineWidth(2);
   gTotRelUp->SetLineStyle(1);
   gTotRelUp->SetLineColor(2);
   gTotRelUp->GetXaxis()->SetTitleOffset(1.5);
   gTotRelUp->GetXaxis()->SetTitle("E [GeV]");
   gTotRelUp->Draw("AL");
   
   gTotRelDown->SetLineWidth(2);
   gTotRelDown->SetLineStyle(1);
   gTotRelDown->SetLineColor(2);
   gTotRelDown->Draw("L");
   
   sprintf(plotname,"res_2_%f.png",eta);
   canvas2->SaveAs(plotname);
   
}

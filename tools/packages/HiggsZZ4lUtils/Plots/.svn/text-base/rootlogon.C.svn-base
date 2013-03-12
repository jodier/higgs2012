void
set_plot_style()
{
  const Int_t NRGBs = 5;
  const Int_t NCont = 255;
  
  Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
  Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
  Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
  Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
  TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
  gStyle->SetNumberContours(NCont);
}
rootlogon()
{
  TStyle *plain = new TStyle("Plain","Plain Style");
 
  plain->SetPadTickX(1);
  plain->SetPadTickY(1);
  plain->SetCanvasBorderMode(0);
  plain->SetCanvasColor(0);
  plain->SetPadBorderMode(0);
  plain->SetPadColor(0);
  plain->SetCanvasColor(0);
  //plain->SetTitleColor(0);
  //plain->SetCanvasDefH(700);
  //plain->SetCanvasDefH(780);
  //plain->SetCanvasDefW(700);
  //plain->SetCanvasDefW(1260);
  //plain->SetFillColor(0);
  plain->SetOptStat(0);
  plain->SetStatFont(42);
  plain->SetOptFit(0);
  //plain->SetStatColor(0);
  //plain->SetOptTitle(0);
  plain->SetAxisColor(1); 
  plain->SetLabelColor(1);
  plain->SetTitleFont(42, "xyz");
  plain->SetLabelFont(42, "xyz");  

  //plain->SetTitleXOffset(1.3);
  //plain->SetTitleYOffset(1.3);
 
  plain->SetMarkerStyle(20);
  plain->SetMarkerSize(1.2);
  plain->SetHistLineWidth(2);
  plain->SetLineStyleString(2,"[12 12]");
  plain->SetEndErrorSize(0.);
  plain->SetOptTitle(0);

  plain->SetTextSize(0.05);
  plain->SetLabelSize(0.05,"x");
  plain->SetTitleSize(0.05,"x");
  plain->SetLabelSize(0.05,"y");
  plain->SetTitleSize(0.05,"y");
  plain->SetLabelSize(0.05,"z");
  plain->SetTitleSize(0.05,"z");

  TGaxis *ax= new TGaxis();
  ax->SetMaxDigits(4);
  ax->SetDecimals();

  //plain->SetTextFont(42);

  //const Int_t NRGBs = 5;
  const Int_t NCont = 255;
  /*
  Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
  Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
  Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
  Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
  TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
  */
  plain->SetNumberContours(NCont);

  plain->cd();
  //set_plot_style();
  //set_plot_style();
  

}

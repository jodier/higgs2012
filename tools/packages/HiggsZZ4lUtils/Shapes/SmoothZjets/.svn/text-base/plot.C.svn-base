
int plot()
{

  gROOT->Reset();
  gROOT->SetStyle("ATLAS");                                                                                                                                   gROOT->ForceStyle(); 

  //Create a Canvas
  TCanvas c1("c1","c1",600,600);

  //open the ZZ MC Files
  TFile fZxx("Zxx_nominal.root");
  TFile fZxx1("Zxx_syst.root");
  TFile fZxx2("Zxx_syst2.root");

  TTree *tree = fZxx.Get("DataTree");
  TTree *tree1 = fZxx1.Get("DataTree");
  TTree *tree2 = fZxx2.Get("DataTree");

  TH1F ZXXShape("ZXXShape","Z+XX shape",70,0,350);
  TH1F ZXXShape1("ZXXShape1","Z+XX shape",70,0,350);
  TH1F ZXXShape2("ZXXShape2","Z+XX shape",70,0,350);


  tree->Draw("M4l/1000>>ZXXShape");
  tree1->Draw("M4l/1000>>ZXXShape1");
  tree2->Draw("M4l/1000>>ZXXShape2");

  ZXXShape.SetMaximum(5e5); 
  ZXXShape.SetYTitle("Arb units/ 5.0 GeV" ); 
  ZXXShape.SetXTitle("Mass (GeV)");
  ZXXShape.SetLineColor(kBlack);
  ZXXShape.Draw("histo");

  ZXXShape1.SetLineColor(kBlue);
  ZXXShape1.Draw("histosame");

  ZXXShape2.SetLineColor(kRed);
  ZXXShape2.Draw("histosame");

  TLegend *legen = new TLegend(0.5, 0.80, 0.75,0.93, "");; 
  legen->SetFillStyle(0);
  legen->SetBorderSize(0);
  legen->AddEntry(&ZXXShape," Nominal ","l");
  legen->AddEntry(&ZXXShape1,"syst 1","l");
  legen->AddEntry(&ZXXShape2,"syst 2","l");
  legen->Draw();

  c1.Print("Zxx_shape.png");
  c1.Print("Zxx_shape.eps");

  TFile templates_irreducible("reducible.root","RECREATE");
  TH1F irredShapeNom("irredShapeNom","reducible shape",2000,0,1000);
  TH1F irredShapesyst1("irredShapesyst1","reducible shape",2000,0,1000);
  TH1F irredShapesyst2("irredShapesyst2","reducible shape",2000,0,1000);


  tree->Draw("M4l/1000>>irredShapeNom");
  tree1->Draw("M4l/1000>>irredShapesyst1");
  tree2->Draw("M4l/1000>>irredShapesyst2");
  templates_irreducible.Write();

  return 0;

}

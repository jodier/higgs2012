/*
 Christos Anastopoulos
The purpose of this Macro is to generate "smooth ZZ distributions@
It uses RooKeysPdf and writes out a new tree that can be used later
on as 
*/


#include "RooBreitWigner.h"
#include <fstream>
#include <iomanip>

using namespace RooFit ;
using namespace RooStats ;

int Create_smoothZxx()
{

  gROOT->Reset();
  gROOT->SetStyle("ATLAS");                                                                                                                                   gROOT->ForceStyle(); 

  ///////////////////////////////////////////////////////////////////////////////////////////
  //Create a Canvas
  TCanvas c1("c1","c1",600,600);
  //Max -min and binnings
  unsigned int min4l =0;
  unsigned int max4l =1000000;
  unsigned int minw =0;
  unsigned int maxw =100;

  //Define the 2 Variables to be used
  RooRealVar mass("mass","mass",min4l,max4l,"MeV");
  RooRealVar weight("weight","weight",minw,maxw,"MeV");
  RooArgSet set(mass,weight);

  //

  //********************************  ZXX MODEL  ***************************************
  //open the ZZ MC Files
  TFile fZxx("reduxbkg_tree.root");
  TTree *tree = fZxx.Get("tree");
  RooDataSet data("data","data",tree,set,0,"weight"); 
  RooKeysPdf Zxx_templ("Zxx_templ","Zxx_templ",mass,data,RooKeysPdf::NoMirror,2.5);
  ///////////////////////////////////////////////////////
  //output
  TFile output("Zxx_Nominal.root","RECREATE");
  TTree *outTree=new TTree("DataTree","DataTree");
  Float_t m_M4l;
  outTree->Branch("M4l",&m_M4l,"M4l/F");
  RooDataSet* dataM4l = Zxx_templ.generate(mass,4000000) ;      
  for (int i =0; i<dataM4l->numEntries();++i)
    {
      m_M4l =dataM4l->get(i)->getRealValue("mass");
      outTree->Fill();
    }
  ///////////////////////////////
  RooPlot* frameZxxM4l = mass.frame(200) ;
  //
  data.plotOn(frameZxxM4l) ;
  Zxx_templ.plotOn(frameZxxM4l,LineColor(kBlue));
  frameZxxM4l->Draw() ;
  c1.Print("Zxx_templ_init.png");
  //
  RooPlot* frameZxx_finalM4l = mass.frame(200) ;
  dataM4l->plotOn(frameZxx_finalM4l) ;
  Zxx_templ.plotOn(frameZxx_finalM4l,LineColor(kBlue));
  frameZxx_finalM4l->Draw() ;
  c1.Print("Zxx_final_templ_end.png");
  //
  //
  output.Write();
  output.Close();
  //
  return 0;

}
  
  

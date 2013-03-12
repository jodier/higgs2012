#include "egammaAnalysisUtils/EisoTool2012.h"

unsigned int EisoTool2012::Etcone(const double& cone,
                                  const unsigned int& Efficiency_required,
                                  const unsigned int& NPV,
                                  const double& Electron_Cluster_E,
                                  const double& Electron_Track_Eta,
                                  const double& Electron_Cluster_Eta,
                                  const double& Electron_Etas2,
                                  const double& Electron_Etap,
                                  const double& Electron_Etcone_Uncorrected,
                                  const bool& isMC)
{
  m_isMC = isMC;
  return this->Etcone(cone,Efficiency_required,NPV,Electron_Cluster_E,Electron_Track_Eta,
                      Electron_Cluster_Eta,Electron_Etas2,Electron_Etap,Electron_Etcone_Uncorrected);
}

unsigned int EisoTool2012::Etcone(const double& cone,
                            const unsigned int& Efficiency_required,
                            const unsigned int& NPV,
                            const double& Electron_Cluster_E,
                            const double& Electron_Track_Eta,
                            const double& Electron_Cluster_Eta,
                            const double& Electron_Etas2,
                            const double& Electron_Etap,
                            const double& Electron_Etcone_Uncorrected) const
{
  double Et = this->ElectronEt( Electron_Cluster_E , Electron_Track_Eta );
  double Value = this->EtconeCorrected(NPV,Electron_Cluster_E,Electron_Cluster_Eta,Electron_Etas2,Electron_Etap,Electron_Etcone_Uncorrected,cone);

  if( cone == 0.2 || cone == 20 ){
    return this->PassOrFail(Et,Electron_Cluster_Eta,Efficiency_required,Value,h_etconeCor20);
  }
  if( cone == 0.3 || cone == 30 ){
    return this->PassOrFail(Et,Electron_Cluster_Eta,Efficiency_required,Value,h_etconeCor30);
  }
  if( cone == 0.4 || cone == 40 ){
    return this->PassOrFail(Et,Electron_Cluster_Eta,Efficiency_required,Value,h_etconeCor40);
  }
  return 0; 
}

unsigned int EisoTool2012::Ptcone(const double& cone,
                    const unsigned int& Efficiency_required,
                    const double& Electron_Cluster_E,
                    const double& Electron_Track_Eta,
                    const double& Electron_Cluster_Eta,
                    const double& Electron_Ptcone) const
{
  double Et = this->ElectronEt( Electron_Cluster_E , Electron_Track_Eta );
  if( cone == 0.2 || cone == 20 ){
    return this->PassOrFail(Et,Electron_Cluster_Eta,Efficiency_required,Electron_Ptcone,h_ptcone20);
  }
  if( cone == 0.3 || cone == 30 ){
    return this->PassOrFail(Et,Electron_Cluster_Eta,Efficiency_required,Electron_Ptcone,h_ptcone30);
  }
  if( cone == 0.4 || cone == 40 ){
    return this->PassOrFail(Et,Electron_Cluster_Eta,Efficiency_required,Electron_Ptcone,h_ptcone40);
  }
  return 0;   

}

unsigned int EisoTool2012::Topocone(const double& cone,
                              const unsigned int& Efficiency_required,
                              const double& Electron_Cluster_E,
                              const double& Electron_Track_Eta,
                              const double& Electron_Cluster_Eta,
                              const double& Electron_Etas2,
                              const double& Electron_Etap,
                              const double& Electron_ED_median,
                              const double& Electron_topocone,
                              const bool& isMC)
{
  m_isMC = isMC;
  return this->Topocone(cone,Efficiency_required,Electron_Cluster_E,Electron_Track_Eta,
                        Electron_Cluster_Eta,Electron_Etas2,Electron_Etap,Electron_ED_median,Electron_topocone);
}

unsigned int EisoTool2012::Topocone(const double& cone,
                              const unsigned int& Efficiency_required,
                              const double& Electron_Cluster_E,
                              const double& Electron_Track_Eta,
                              const double& Electron_Cluster_Eta,
                              const double& Electron_Etas2,
                              const double& Electron_Etap,
                              const double& Electron_ED_median,
                              const double& Electron_topocone) const
{
  double Et = this->ElectronEt( Electron_Cluster_E , Electron_Track_Eta );
  double Value = this->TopoconeCorrected(Electron_Cluster_E,Electron_Cluster_Eta,Electron_Etas2,Electron_Etap,
                                         Electron_ED_median,Electron_topocone,cone);

  if( cone == 0.2 || cone == 20 ){
    return this->PassOrFail(Et,Electron_Cluster_Eta,Efficiency_required,Value,h_topoconeCor20);
  }
  if( cone == 0.3 || cone == 30 ){
    return this->PassOrFail(Et,Electron_Cluster_Eta,Efficiency_required,Value,h_topoconeCor30);
  }
  if( cone == 0.4 || cone == 40 ){
    return this->PassOrFail(Et,Electron_Cluster_Eta,Efficiency_required,Value,h_topoconeCor40);
  }
  return 0;
}

/////////////////////////////////////////////////////////
// Get Cut Values                                      //
/////////////////////////////////////////////////////////
double EisoTool2012::getCutValueEtcone(const double& cone,
                                       const unsigned int& Efficiency_required,
                                       const double& Electron_Cluster_E,
                                       const double& Electron_Track_Eta,
                                       const double& Electron_Cluster_Eta) const
{
  double Et = this->ElectronEt( Electron_Cluster_E , Electron_Track_Eta );
  if( cone == 0.2 || cone == 20 ){
    return this->getCutValue(Et,Electron_Cluster_Eta,Efficiency_required,h_etconeCor20);
  }
  if( cone == 0.3 || cone == 30 ){
    return this->getCutValue(Et,Electron_Cluster_Eta,Efficiency_required,h_etconeCor30);
  }
  if( cone == 0.4 || cone == 40 ){
    return this->getCutValue(Et,Electron_Cluster_Eta,Efficiency_required,h_etconeCor40);
  }
  return 0;   
}

double EisoTool2012::getCutValuePtcone(const double& cone,
                                       const unsigned int& Efficiency_required,
                                       const double& Electron_Cluster_E,
                                       const double& Electron_Track_Eta,
                                       const double& Electron_Cluster_Eta) const
{
  double Et = this->ElectronEt( Electron_Cluster_E , Electron_Track_Eta );
  if( cone == 0.2 || cone == 20 ){
    return this->getCutValue(Et,Electron_Cluster_Eta,Efficiency_required,h_ptcone20);
  }
  if( cone == 0.3 || cone == 30 ){
    return this->getCutValue(Et,Electron_Cluster_Eta,Efficiency_required,h_ptcone30);
  }
  if( cone == 0.4 || cone == 40 ){
    return this->getCutValue(Et,Electron_Cluster_Eta,Efficiency_required,h_ptcone40);
  }
  return 0;    
}

double EisoTool2012::getCutValueTopocone(const double& cone,
                                         const unsigned int& Efficiency_required,
                                         const double& Electron_Cluster_E,
                                         const double& Electron_Track_Eta,
                                         const double& Electron_Cluster_Eta) const
{
  double Et = this->ElectronEt( Electron_Cluster_E , Electron_Track_Eta );
  if( cone == 0.2 || cone == 20 ){
    return this->getCutValue(Et,Electron_Cluster_Eta,Efficiency_required,h_topoconeCor20);
  }
  if( cone == 0.3 || cone == 30 ){
    return this->getCutValue(Et,Electron_Cluster_Eta,Efficiency_required,h_topoconeCor30);
  }
  if( cone == 0.4 || cone == 40 ){
    return this->getCutValue(Et,Electron_Cluster_Eta,Efficiency_required,h_topoconeCor40);
  }
  return 0;  
}

/////////////////////////////////////////////////////////
// Correction tools                                    //
/////////////////////////////////////////////////////////
double EisoTool2012::EtconeCorrected(const unsigned int& NPV,
                                     const double& Electron_Cluster_E,
                                     const double& Electron_Cluster_Eta,
                                     const double& Electron_Etas2,
                                     const double& Electron_Etap,
                                     const double& Electron_Etcone_Uncorrected,
                                     const double& cone) const
{
  return CaloIsoCorrection::GetPtNPVCorrectedIsolation(
                            NPV,
                            Electron_Cluster_E,
                            Electron_Etas2,
                            Electron_Etap,
                            Electron_Cluster_Eta,
                            cone,
                            m_isMC,
                            Electron_Etcone_Uncorrected,
                            false,
                            CaloIsoCorrection::ELECTRON,
                            CaloIsoCorrection::REL17);
}

double EisoTool2012::TopoconeCorrected(const double& Electron_Cluster_E,
                                       const double& Electron_Cluster_Eta,
                                       const double& Electron_Etas2,
                                       const double& Electron_Etap,
                                       const double& Electron_ED_median,
                                       const double& Electron_topocone,
                                       const double& cone) const
{
  return CaloIsoCorrection::GetPtEDCorrectedTopoIsolation(
                Electron_ED_median,
                Electron_Cluster_E,
                Electron_Etas2,
                Electron_Etap,
                Electron_Cluster_Eta,
                cone,
                m_isMC,
                Electron_topocone,
                false,
                CaloIsoCorrection::ELECTRON,
                CaloIsoCorrection::REL17);

}


/////////////////////////////////////////////////////////
// Internal tools                                      //
/////////////////////////////////////////////////////////
double EisoTool2012::ElectronEt(const double& Electron_Cluster_E, const double& Electron_Track_Eta) const
{
  return Electron_Cluster_E / cosh( Electron_Track_Eta );
}

unsigned int EisoTool2012::PassOrFail(const double& Et,const double& Eta,const unsigned int& Efficiency_required, const double& value,TH3D* histo) const
{
  if( (value / m_GeV) < histo->GetBinContent(this->FindEtBin(Et),this->FindEtaBin(Eta),Efficiency_required) ){
    return 1;
  }
  return 0;
}

double EisoTool2012::getCutValue(const double& Et,const double& Eta,const unsigned int& Efficiency_required,TH3D* histo) const
{
  return histo->GetBinContent(this->FindEtBin(Et),this->FindEtaBin(Eta),Efficiency_required);
}

int EisoTool2012::FindEtBin(const double& Et) const
{
  return h_etBins->FindBin(Et / m_GeV);
}

int EisoTool2012::FindEtaBin(const double& Eta) const
{
  return h_etaBins->FindBin(fabs(Eta));
}

/////////////////////////////////////////////////////////
// Constructors, destructor and operator overloading   //
/////////////////////////////////////////////////////////


EisoTool2012::EisoTool2012() :
  m_GeV(1000.0),
  m_isMC(false),
  m_inputFileName("NULL"),
  s_etconeCor20("etconeCor20"),
  s_etconeCor30("etconeCor30"),
  s_etconeCor40("etconeCor40"),
  s_ptcone20("ptcone20"),
  s_ptcone30("ptcone30"),
  s_ptcone40("ptcone40"),
  s_topoconeCor20("topoconeCor20"),
  s_topoconeCor30("topoconeCor30"),
  s_topoconeCor40("topoconeCor40"),

  h_etconeCor20(NULL),
  h_etconeCor30(NULL),
  h_etconeCor40(NULL),
  h_ptcone20(NULL),
  h_ptcone30(NULL),
  h_ptcone40(NULL),
  h_topoconeCor20(NULL),
  h_topoconeCor30(NULL),
  h_topoconeCor40(NULL),
  h_etBins(NULL),
  h_etaBins(NULL)
{
}

EisoTool2012::EisoTool2012(const TString& inputFileName) :
  m_GeV(1000.0),
  m_isMC(false),
  m_inputFileName(inputFileName),                                  
  s_etconeCor20("etconeCor20"),
  s_etconeCor30("etconeCor30"),
  s_etconeCor40("etconeCor40"),
  s_ptcone20("ptcone20"),
  s_ptcone30("ptcone30"),
  s_ptcone40("ptcone40"),
  s_topoconeCor20("topoconeCor20"),
  s_topoconeCor30("topoconeCor30"),
  s_topoconeCor40("topoconeCor40"),

  h_etconeCor20(NULL),
  h_etconeCor30(NULL),
  h_etconeCor40(NULL),
  h_ptcone20(NULL),
  h_ptcone30(NULL),
  h_ptcone40(NULL),
  h_topoconeCor20(NULL),
  h_topoconeCor30(NULL),
  h_topoconeCor40(NULL),
  h_etBins(NULL),
  h_etaBins(NULL) 
{
  this->LoadHistograms();
}

EisoTool2012::EisoTool2012(const TString& inputFileName,const bool isMC) :
  m_GeV(1000.0),
  m_isMC(isMC),
  m_inputFileName(inputFileName),
  s_etconeCor20("etconeCor20"),
  s_etconeCor30("etconeCor30"),
  s_etconeCor40("etconeCor40"),
  s_ptcone20("ptcone20"),
  s_ptcone30("ptcone30"),
  s_ptcone40("ptcone40"),
  s_topoconeCor20("topoconeCor20"),
  s_topoconeCor30("topoconeCor30"),
  s_topoconeCor40("topoconeCor40"),  

  h_etconeCor20(NULL),
  h_etconeCor30(NULL),
  h_etconeCor40(NULL),
  h_ptcone20(NULL),
  h_ptcone30(NULL),
  h_ptcone40(NULL),
  h_topoconeCor20(NULL),
  h_topoconeCor30(NULL),
  h_topoconeCor40(NULL),
  h_etBins(NULL),
  h_etaBins(NULL) 
{
  this->LoadHistograms();
}


EisoTool2012::EisoTool2012(const EisoTool2012& rhs) :
  m_GeV(1000.0),
  m_isMC(false),
  m_inputFileName("NULL"),
  s_etconeCor20("etconeCor20"),
  s_etconeCor30("etconeCor30"),
  s_etconeCor40("etconeCor40"),
  s_ptcone20("ptcone20"),
  s_ptcone30("ptcone30"),
  s_ptcone40("ptcone40"),
  s_topoconeCor20("topoconeCor20"),
  s_topoconeCor30("topoconeCor30"),
  s_topoconeCor40("topoconeCor40"),    

  h_etconeCor20(NULL),
  h_etconeCor30(NULL),
  h_etconeCor40(NULL),
  h_ptcone20(NULL),
  h_ptcone30(NULL),
  h_ptcone40(NULL),
  h_topoconeCor20(NULL),
  h_topoconeCor30(NULL),
  h_topoconeCor40(NULL),
  h_etBins(NULL),
  h_etaBins(NULL) 
{
  m_GeV = rhs.m_GeV;
  m_isMC = rhs.m_isMC;

  m_inputFileName = rhs.m_inputFileName;

  s_etconeCor20 = rhs.s_etconeCor20;
  s_etconeCor30 = rhs.s_etconeCor30;
  s_etconeCor40 = rhs.s_etconeCor40;
  s_ptcone20 = rhs.s_ptcone20;
  s_ptcone30 = rhs.s_ptcone30;
  s_ptcone40 = rhs.s_ptcone40;
  s_topoconeCor20 = rhs.s_topoconeCor20;
  s_topoconeCor30 = rhs.s_topoconeCor30;
  s_topoconeCor40 = rhs.s_topoconeCor40;

  h_etconeCor20 = (TH3D*)rhs.h_etconeCor20->Clone();
  h_etconeCor30 = (TH3D*)rhs.h_etconeCor30->Clone();
  h_etconeCor40 = (TH3D*)rhs.h_etconeCor40->Clone();
  h_ptcone20 = (TH3D*)rhs.h_ptcone20->Clone();
  h_ptcone30 = (TH3D*)rhs.h_ptcone30->Clone();
  h_ptcone40 = (TH3D*)rhs.h_ptcone40->Clone();
  h_topoconeCor20 = (TH3D*)rhs.h_topoconeCor20->Clone();
  h_topoconeCor30 = (TH3D*)rhs.h_topoconeCor30->Clone();
  h_topoconeCor40 = (TH3D*)rhs.h_topoconeCor40->Clone();
  
  h_etBins = (TH1D*)rhs.h_etBins->Clone();
  h_etaBins = (TH1D*)rhs.h_etaBins->Clone();
}


EisoTool2012& EisoTool2012::operator=(const EisoTool2012& rhs)
{
  if( this != &rhs ){
    m_GeV = rhs.m_GeV;
    m_isMC = rhs.m_isMC;

    m_inputFileName = rhs.m_inputFileName;

    s_etconeCor20 = rhs.s_etconeCor20;
    s_etconeCor30 = rhs.s_etconeCor30;
    s_etconeCor40 = rhs.s_etconeCor40;
    s_ptcone20 = rhs.s_ptcone20;
    s_ptcone30 = rhs.s_ptcone30;
    s_ptcone40 = rhs.s_ptcone40;
    s_topoconeCor20 = rhs.s_topoconeCor20;
    s_topoconeCor30 = rhs.s_topoconeCor30;
    s_topoconeCor40 = rhs.s_topoconeCor40;

    TH3D* tmp_etconeCor20 = 0;
    TH3D* tmp_etconeCor30 = 0;
    TH3D* tmp_etconeCor40 = 0;
    TH3D* tmp_ptcone20 = 0;
    TH3D* tmp_ptcone30 = 0;
    TH3D* tmp_ptcone40 = 0;
    TH3D* tmp_topoconeCor20 = 0;
    TH3D* tmp_topoconeCor30 = 0;
    TH3D* tmp_topoconeCor40 = 0;

    TH1D* tmp_etBins = 0;
    TH1D* tmp_etaBins = 0;

    try{
      tmp_etconeCor20 = (TH3D*)rhs.h_etconeCor20->Clone();
      tmp_etconeCor30 = (TH3D*)rhs.h_etconeCor30->Clone();
      tmp_etconeCor40 = (TH3D*)rhs.h_etconeCor40->Clone();
      tmp_ptcone20 = (TH3D*)rhs.h_ptcone20->Clone();
      tmp_ptcone30 = (TH3D*)rhs.h_ptcone30->Clone();
      tmp_ptcone40 = (TH3D*)rhs.h_ptcone40->Clone();
      tmp_topoconeCor20 = (TH3D*)rhs.h_topoconeCor20->Clone();
      tmp_topoconeCor30 = (TH3D*)rhs.h_topoconeCor30->Clone();
      tmp_topoconeCor40 = (TH3D*)rhs.h_topoconeCor40->Clone();
      tmp_etBins = (TH1D*)rhs.h_etBins->Clone();
      tmp_etaBins = (TH1D*)rhs.h_etaBins->Clone();
    }
    catch(...){
      delete tmp_etconeCor20;
      delete tmp_etconeCor30;
      delete tmp_etconeCor40;
      delete tmp_ptcone20;
      delete tmp_ptcone30;
      delete tmp_ptcone40;
      delete tmp_topoconeCor20;
      delete tmp_topoconeCor30;
      delete tmp_topoconeCor40;
      delete tmp_etBins;
      delete tmp_etaBins;
    }

    delete h_etconeCor20;
    delete h_etconeCor30;
    delete h_etconeCor40;
    delete h_ptcone20;
    delete h_ptcone30;
    delete h_ptcone40;
    delete h_topoconeCor20;
    delete h_topoconeCor30;
    delete h_topoconeCor40;
    delete h_etBins;
    delete h_etaBins;

    h_etconeCor20 = tmp_etconeCor20;
    h_etconeCor30 = tmp_etconeCor30;
    h_etconeCor40 = tmp_etconeCor40;
    h_ptcone20 = tmp_ptcone20;
    h_ptcone30 = tmp_ptcone30;
    h_ptcone40 = tmp_ptcone40;
    h_topoconeCor20 = tmp_topoconeCor20;
    h_topoconeCor30 = tmp_topoconeCor30;
    h_topoconeCor40 = tmp_topoconeCor40;
    h_etBins = tmp_etBins;
    h_etaBins = tmp_etaBins;
  }
  return *this;
}

EisoTool2012::~EisoTool2012()
{
}

/////////////////////////////////////////////////////////
// Setup Names and Load histograms from file           //
/////////////////////////////////////////////////////////


void EisoTool2012::LoadHistograms()
{
  TFile* inputFile = new TFile(m_inputFileName,"READ");
  

  h_etconeCor20 = (TH3D*)inputFile->Get( s_etconeCor20 )->Clone();
  h_etconeCor30 = (TH3D*)inputFile->Get( s_etconeCor30 )->Clone();
  h_etconeCor40 = (TH3D*)inputFile->Get( s_etconeCor40 )->Clone();

  h_ptcone20 = (TH3D*)inputFile->Get( s_ptcone20 )->Clone();
  h_ptcone30 = (TH3D*)inputFile->Get( s_ptcone30 )->Clone();
  h_ptcone40 = (TH3D*)inputFile->Get( s_ptcone40 )->Clone();

  h_topoconeCor20 = (TH3D*)inputFile->Get( s_topoconeCor20 )->Clone();
  h_topoconeCor30 = (TH3D*)inputFile->Get( s_topoconeCor30 )->Clone();
  h_topoconeCor40 = (TH3D*)inputFile->Get( s_topoconeCor40 )->Clone();


  this->SetupBinningHistos();
}

void EisoTool2012::SetupBinningHistos()
{

  const double ArrayEt[13]={0.0,5.0,10.0,15.0,20.0,30.0,40.0,
                            50.0,60.0,70.0,80.0,120.0,1000000000.0};

  const double ArrayEta[10]={0.0,0.6,0.8,1.15,1.37,1.52,
                            1.81,2.01,2.37,2.47};

  h_etBins = new TH1D("etBins","etBins",12,ArrayEt);
  h_etaBins = new TH1D("etaBins","etaBins",9,ArrayEta);
}

///
/// Internal versions for testing only
///
/// - 29/01/12 : check of new central scales
/// - 03/02/12 : include forward scales, and updated constant terms
///


#include "egammaAnalysisUtils/EnergyRescalerUpgrade.h"

using namespace std;

namespace egRescaler {


  EnergyRescalerUpgrade::EnergyRescalerUpgrade() {
  
    m_debug = true;

  }
  
  
  EnergyRescalerUpgrade::EnergyRescalerUpgrade(std::string filename, std::string year, std::string esmodel) {

    //default seed
    SetRandomSeed();
  
    // initialize
    Init( filename, year, esmodel );
    
    m_debug = true;

  }
  
  
  EnergyRescalerUpgrade::~EnergyRescalerUpgrade() {
    
  }


  void EnergyRescalerUpgrade::Init(std::string filename, std::string year, std::string esmodel) {
    
    m_erFile = new TFile( filename.c_str() );

    // the Z scale values

    if( year=="2012" )
      m_zeeNom =                     (TH1D*) m_erFile->Get("Scales/2012/ZScales2012_errStat");
    else if( year=="2011" || year=="2010" )
      m_zeeNom =                     (TH1D*) m_erFile->Get("Scales/2011/ZScales2011_errStat");

    // systematic uncertainties

    if( esmodel=="es2011" ) {

      m_zeeModel =                     (TH1D*) m_erFile->Get("Scales/2011/ZScales2011_errGenerator");
      m_zeeMethod =                    (TH1D*) m_erFile->Get("Scales/2011/ZScales2011_errMethod");
      m_psNom =                        (TH1D*) m_erFile->Get("Scales/2011/alphaPSmod_b12Fit_errFit");
      m_psB12 =                        (TH1D*) m_erFile->Get("Scales/2011/alphaPSmod_b12Fit_errB12");
      m_r12Nom =                       (TH1D*) m_erFile->Get("ShowerShapes/2011/r12Hist_b12Fit_errStat");
      m_r12B12 =                       (TH1D*) m_erFile->Get("ShowerShapes/2011/r12Hist_b12Fit_errB12");

    } else if( esmodel=="es2010" ) {

      m_zeeMethod =                    (TH1D*) m_erFile->Get("Scales/2010/ZScales2010_errTot");
      m_psNom =                        (TH1D*) m_erFile->Get("Scales/2010/alphaPS_2010");
      m_r12Nom =                       (TH1D*) m_erFile->Get("ShowerShapes/2010/r12Hist_2010");

    }

    // further inputs (do not depend on year)

    m_psElectronEtaBins =           (TH1D*) m_erFile->Get("PSRecalibration/2011/ElectronEtaBins");
    m_psElectronGraphs =           (TList*) m_erFile->Get("PSRecalibration/2011/ElectronGraphs");
    m_psUnconvertedEtaBins =        (TH1D*) m_erFile->Get("PSRecalibration/2011/UnconvertedEtaBins");
    m_psUnconvertedGraphs =        (TList*) m_erFile->Get("PSRecalibration/2011/UnconvertedGraphs");
    m_psConvertedEtaBins =          (TH1D*) m_erFile->Get("PSRecalibration/2011/ConvertedEtaBins");
    m_psConvertedGraphs =          (TList*) m_erFile->Get("PSRecalibration/2011/ConvertedGraphs");
  
    m_matElectronScale =    (TGraphErrors*) m_erFile->Get("Material/2011/ZScaleDiff");
    m_matUnconvertedScale = (TGraphErrors*) m_erFile->Get("Material/2011/UncScaleDiff");
    m_matConvertedScale =   (TGraphErrors*) m_erFile->Get("Material/2011/ConvScaleDiff");
    m_matElectronEtaBins =          (TH1D*) m_erFile->Get("Material/2011/hmatEtaBins");
    m_matElectronGraphs =          (TList*) m_erFile->Get("Material/2011/LinearityGraphs");
  
    m_initialized = true;
  
  }


  // initialize random seed

  void EnergyRescalerUpgrade::SetRandomSeed( unsigned seed ) {

    m_random3.SetSeed(seed);

  }


  // apply energy rescaling (to Data)
  // note : all energies in MeV
  
  double EnergyRescalerUpgrade::applyEnergyCorrection(double cl_eta, double energy, ParticleType ptype, Variation var, double varSF) { 
    
    double alphaZee = getAlphaZee( cl_eta, var, varSF );

    double alphaLowPt =  getAlphaLowPt( energy/cosh(cl_eta), var, varSF );

    //    double meanET = getZeeMeanET( cl_eta ); // TODO
    double meanET = 40000.; // sufficient for now

    double alphaPS = getAlphaPS( cl_eta, var, varSF );
    double linPS = getPSNonLinearity( cl_eta, energy, ptype) - getPSNonLinearity( cl_eta, meanET*cosh(cl_eta), Electron );

    double r12 = getR12( cl_eta, var, varSF );
    double alphaMAT = getAlphaMaterial( cl_eta, ptype ) - getAlphaMaterial( cl_eta, Electron );
    double linMAT = getMaterialNonLinearity( cl_eta, energy, ptype);// - getMaterialNonLinearity( cl_eta, meanET*cosh(cl_eta), Electron );
                                                                    // - this subtraction is already done in the 2010 parametrization used for now

    double alphaTot = alphaZee + alphaLowPt + alphaPS*linPS + r12*(alphaMAT+linMAT);

    cout << var << " " << cl_eta << " " << energy << " / " << alphaZee << " / " << alphaPS << " " << linPS << " / " 
	 << r12 << " " << alphaMAT << " " << linMAT << " / " << alphaTot << endl;

    return energy/(1+alphaTot);

  } 


  double EnergyRescalerUpgrade::applyEnergyCorrection(double cl_eta, ParticleType ptype, Variation var, double varSF) { 
    
    return applyEnergyCorrection(cl_eta, 40000., ptype, var, varSF);

  } 


  double EnergyRescalerUpgrade::getCorrectionError(double cl_eta, double energy, ParticleType ptype, Variation var, double varSF) { 

    double nominal = applyEnergyCorrection(cl_eta, energy, ptype, Nominal);
    double variation=0.;

    if( var != AllUp && var != AllDown && var != AllUpApprox && var != AllDownApprox )

      variation = applyEnergyCorrection(cl_eta, energy, ptype, var, varSF) - nominal;

    else if( var == AllUp ) {

      variation  = pow( applyEnergyCorrection(cl_eta, energy, ptype, ZeeStatUp, varSF) - nominal, 2 );
      cout << sqrt(variation)/energy << endl;
      variation += pow( applyEnergyCorrection(cl_eta, energy, ptype, ZeeGenUp, varSF) - nominal, 2 );
      cout << sqrt(variation)/energy << endl;
      variation += pow( applyEnergyCorrection(cl_eta, energy, ptype, ZeeMethodUp, varSF) - nominal, 2 );
      cout << sqrt(variation)/energy << endl;
      variation += pow( applyEnergyCorrection(cl_eta, energy, ptype, PSStatUp, varSF) - nominal, 2 );
      cout << sqrt(variation)/energy << endl;
      variation += pow( applyEnergyCorrection(cl_eta, energy, ptype, R12StatUp, varSF) - nominal, 2 );
      cout << sqrt(variation)/energy << endl;
      variation += pow( applyEnergyCorrection(cl_eta, energy, ptype, B12Up, varSF) - nominal, 2 );
      cout << sqrt(variation)/energy << endl;

      variation = sqrt(variation);

    } else if( var == AllDown ) {

      variation  = pow( applyEnergyCorrection(cl_eta, energy, ptype, ZeeStatDown, varSF) - nominal, 2 );
      variation += pow( applyEnergyCorrection(cl_eta, energy, ptype, ZeeGenDown, varSF) - nominal, 2 );
      variation += pow( applyEnergyCorrection(cl_eta, energy, ptype, ZeeMethodDown, varSF) - nominal, 2 );
      variation += pow( applyEnergyCorrection(cl_eta, energy, ptype, PSStatDown, varSF) - nominal, 2 );
      variation += pow( applyEnergyCorrection(cl_eta, energy, ptype, R12StatDown, varSF) - nominal, 2 );
      variation += pow( applyEnergyCorrection(cl_eta, energy, ptype, B12Down, varSF) - nominal, 2 );

      variation = -sqrt(variation);

    } else if( var == AllUpApprox ) {

      variation  = pow( applyEnergyCorrection(cl_eta, energy, ptype, ZeeGenUp, varSF) - nominal, 2 );
      variation += pow( applyEnergyCorrection(cl_eta, energy, ptype, B12Up, varSF) - nominal, 2 );

      variation = sqrt(variation);

    } else if( var == AllDownApprox ) {

      variation  = pow( applyEnergyCorrection(cl_eta, energy, ptype, ZeeGenDown, varSF) - nominal, 2 );
      variation += pow( applyEnergyCorrection(cl_eta, energy, ptype, B12Down, varSF) - nominal, 2 );

      variation = -sqrt(variation);

    } 

    cout << var << " " << variation/energy << endl;

    return variation/energy;

  }



  // RESOLUTION FUNCTIONS START HERE (MB)


  // sampling term inMC, parametrization from Iro

  double EnergyRescalerUpgrade::mcSamplingTerm(double cl_eta) {

    double aeta = fabs( cl_eta );
    double sampling = 0.;

    if ( aeta<0.8 )
      sampling = 0.091;

    else if ( aeta<1.37 )
      sampling = 0.036 + 0.130 * aeta;

    else if ( aeta<1.52 )
      sampling = 0.27;

    else if ( aeta<2.0 )
      sampling = 0.85 - 0.36 * aeta;

    else if ( aeta<2.3 )
      sampling = 0.16;
  
    else if ( aeta<2.5 )
      sampling = -1.05 + 0.52 * aeta;

    return sampling;

  }


  // sampling term uncertainty

  double EnergyRescalerUpgrade::mcSamplingTermRelError( double cl_eta ) {

    cl_eta = cl_eta*1.;
    double relerr = 0.1;

    return relerr;

  }


  // noise term in MC (from Iro)

  double EnergyRescalerUpgrade::mcNoiseTerm( double cl_eta ) {

    double aeta = fabs( cl_eta );
    double noise = 0.;

    double noise37[25]={ 0.27, 0.27, 0.27, 0.27, 0.27, 
			 0.26, 0.25, 0.23, 0.21, 0.19, 
			 0.17, 0.16, 0.15, 0.14, 0.27, 
			 0.23, 0.17, 0.15, 0.13, 0.10, 
			 0.07, 0.06, 0.05, 0.04, 0.03 };  

    int ieta = (int) (aeta/0.1);

    if ( ieta<25 )
      noise =  noise37[ieta];

    return noise;

  }


  // constant term in MC (local)

  double EnergyRescalerUpgrade::mcConstantTerm( double cl_eta ) {

    double aeta = fabs( cl_eta );
    double cst = 0.;

    if ( aeta<0.6 )
      cst = 0.005;

    else if ( aeta<1.75 )
      cst = 0.003;

    else if ( aeta<2.5 )
      cst = 0.0055 * (2.69 - aeta);

    //cst = 0.005;

    return cst;

  }


  // constant term fitted in data (long range)

  double EnergyRescalerUpgrade::dataConstantTerm( double cl_eta ) {

    double cst = 0.;

    if ( cl_eta<-3.2  )
      cst = 0.0285 ;

    else if ( cl_eta<-2.8  )
      cst = 0.0363 ;

    else if ( cl_eta<-2.47  )
      cst = 0.0198 ;

    else if ( cl_eta<-1.8  )
      cst = 0.01241325;

    else if ( cl_eta<-1.52  )
      cst = 0.0211967;

    else if ( cl_eta<-1.37 )
      cst = 0.0295445;

    else if ( cl_eta<-0.8 )
      cst = 0.00609462;

    else if ( cl_eta<-0.4 )
      cst = 0.0110266;

    else if ( cl_eta<0 )
      cst = 0.009217095;

    else if ( cl_eta<0.4 )
      cst = 0.009217095;

    else if ( cl_eta<0.8 )
      cst = 0.0110266;

    else if ( cl_eta<1.37 )
      cst = 0.00609462;

    else if ( cl_eta<1.52  )
      cst = 0.0243573;

    else if ( cl_eta<1.8  )
      cst = 0.0211967;

    else if ( cl_eta<2.47 )
      cst = 0.01241325;

    else if ( cl_eta<2.8 )
      cst = 0.0258 ;

    else if ( cl_eta<3.2 )
      cst = 0.0374 ;

    else if ( cl_eta<4.9 )
      cst = 0.0289 ;

    return cst;

  }


  double EnergyRescalerUpgrade::dataConstantTermError( double cl_eta ) {

    double aeta = fabs( cl_eta );
    double err = 0.;

    if ( aeta<1.37 )
      err = 0.006;

    else if ( aeta<2.47 )
      err = 0.006;
  
    else if ( aeta<3.2 )
      err = 0.011;
  
    else if ( aeta<4.9 )
      err = 0.010;
  
    return err;
  }


  double EnergyRescalerUpgrade::dataConstantTermUpError( double cl_eta ) {

    double aeta = fabs( cl_eta );
    double err = 0.;

    if ( aeta<1.37 )
      err = 0.005;

    else if ( aeta<2.47 )
      err = 0.006;
  
    else if ( aeta<3.2 )
      err = 0.011;
  
    else if ( aeta<4.9 )
      err = 0.010;
  
    return err;
  }


  double EnergyRescalerUpgrade::dataConstantTermDownError( double cl_eta ) {

    double aeta = fabs( cl_eta );
    double err = 0.;

    if ( aeta<1.37 )
      err = -0.006;

    else if ( aeta<2.5 )
      err = -0.006;
  
    else if ( aeta<3.2 )
      err = -0.011;
  
    else if ( aeta<4.9 )
      err = -0.015;
  
    return err;
  }


  // fitted Z peak resolution, data, in GeV

  double EnergyRescalerUpgrade::dataZPeakResolution( double cl_eta ) {

    double aeta = fabs( cl_eta );
    double res = 0.;

    if ( aeta<1.37 )
      res = 1.62;

    else if ( aeta<2.5 )
      res = 1.99;

    return res;

  }


  // fitted Z peak resolution, MC, in GeV

  double EnergyRescalerUpgrade::mcZPeakResolution( double cl_eta ) {

    double aeta = fabs( cl_eta );
    double res = 0.;

    if ( aeta<1.37 )
      res = 1.45;

    else if ( aeta<2.5 )
      res = 1.63;

    return res;

  }


  // correlated part of constant term uncertainty, in data (approx.)

  double EnergyRescalerUpgrade::dataConstantTermCorError( double cl_eta ) {

    double mz = 91.2;
  
    double resData = dataZPeakResolution( cl_eta );
    double resMC   = mcZPeakResolution( cl_eta );
    double cmc     = mcConstantTerm( cl_eta );

    double smpup = 1. + mcSamplingTermRelError( cl_eta );
    double smpdo = 1. - mcSamplingTermRelError( cl_eta );

    double central = sqrt( 2*(resData*resData - resMC*resMC)/mz/mz + cmc*cmc );
    double vardown = sqrt( 2*(resData*resData - resMC*resMC*smpup*smpup)/mz/mz + cmc*cmc );
    double varup   = sqrt( 2*(resData*resData - resMC*resMC*smpdo*smpdo)/mz/mz + cmc*cmc );

    double errdown = fabs( central - vardown );
    double errup   = fabs( central - varup );

    return max( errup, errdown );

  }


  // total resolution uncertainty (fractional)

  void EnergyRescalerUpgrade::resolutionError( double energy, double cl_eta, double& errUp, double& errDown ) {

    double Cdata     = dataConstantTerm( cl_eta );
    double Cdata_cor = dataConstantTermCorError( cl_eta );
    double Cdata_err = dataConstantTermError( cl_eta );
  
    double Cdata_unc = 0.;
    if( Cdata_err > Cdata_cor )
      Cdata_unc = sqrt( Cdata_err*Cdata_err - Cdata_cor*Cdata_cor );
    if( Cdata_unc<0.001 )
      Cdata_unc = 0.001; // preserve at least the stat error

    double Smc       = mcSamplingTerm( cl_eta );
    double Smc_err   = mcSamplingTermRelError( cl_eta );

    double central = fcn_sigma( energy,  Cdata,  0.,  Smc,  0.);

    double err1 = fcn_sigma( energy, Cdata,  Cdata_unc, Smc,  0.    ) - central; 
    double err2 = fcn_sigma( energy, Cdata, -Cdata_unc, Smc,  0.    ) - central; 
    double err3 = fcn_sigma( energy, Cdata, -Cdata_cor, Smc, Smc_err) - central;
    double err4 = -err3;

    errUp = 0;
    if( err1>0 ) errUp = sqrt( errUp*errUp + err1*err1);
    if( err2>0 ) errUp = sqrt( errUp*errUp + err2*err2);
    if( err3>0 ) errUp = sqrt( errUp*errUp + err3*err3);
    if( err4>0 ) errUp = sqrt( errUp*errUp + err4*err4);

    errDown   = -errUp;
  }


  // total resolution (fractional)

  double EnergyRescalerUpgrade::resolution( double energy, double cl_eta, bool withCT ) {

    double a = mcSamplingTerm( cl_eta );
    double b = mcNoiseTerm( cl_eta );
    double c = mcConstantTerm( cl_eta );
    double d = dataConstantTerm( cl_eta );

    double sig2 = a*a/energy + b*b/energy/energy + c*c;
    if( withCT )
      sig2 += d*d;

    return sqrt(sig2);

  }


  // internal use only

  double EnergyRescalerUpgrade::fcn_sigma(double energy, double Cdata, double Cdata_er, double S, double S_er) {

    double sigma2 = std::pow((Cdata+Cdata_er)*energy,2) + std::pow(S*(1+S_er)*std::sqrt(energy),2);
  
    double sigma=0; 
    if (sigma2>0) 
      sigma=sqrt(sigma2);
  
    return sigma/energy;

  }


  // derive smearing correction

  double EnergyRescalerUpgrade::getSmearingCorrection(double eta, double energy, int value, bool mc_withCT) 
  {
    double energyGeV = energy/GeV;

    double resMC, resData, /* resVar, */ errUp, errDown;
    resMC   = resolution( energyGeV, eta, false );
    resData = resolution( energyGeV, eta, true );
    resolutionError( energyGeV, eta, errUp, errDown );

    double Cmc = 0.007;

    if( value == 1 )
      resData += errDown;
    else if( value == 2 )
      resData += errUp;
    else if( value != 0 ) {
      std::cout << "getSmearingCorrection : wrong value, return 1" << endl;
      return 1;
    }
  
    double sigma2 = std::pow( resData*energyGeV, 2 ) - std::pow( resMC*energyGeV, 2 );
    if (mc_withCT==true) 
      sigma2 = sigma2 - std::pow( Cmc*energyGeV, 2 );
  
    if (sigma2<=0) return 1;
  
    double sigma = sqrt(sigma2);
    double DeltaE0 = m_random3.Gaus(0,sigma);

    double cor0=(energyGeV+DeltaE0)/energyGeV;
  
    return cor0;
  
  }


  // AF -> G4 correction

  double EnergyRescalerUpgrade::applyAFtoG4(double eta) {

    double aeta = fabs(eta);
    if( aeta>2.47 )
      return 1.;
  
    const int nBoundaries = 27;
    double EtaBoundaries[nBoundaries] = { -2.47, -2.3, -2.1, -1.9, -1.7, -1.52, -1.37, -1.2, 
					  -1.0, -0.8, -0.6, -0.4, -0.2,  0.0,   0.2,   0.4, 
					  0.6,  0.8,  1.0,  1.2,  1.37, 1.52, 1.7, 1.9, 2.1, 2.3, 2.47 };
  
    double CalibFactors[nBoundaries-1] = { 1.01228, 1.00454, 1.00427, 1.00744, 1.00244, 1.00424, 
					   0.993664, 1.00191, 1.00366, 0.999175, 0.997696, 0.997001, 
					   0.999441, 0.999655, 0.996957, 0.997899, 0.999005, 1.00341, 
					   1.00156, 0.993236, 0.996897, 1.00218, 1.00679, 1.00396,
					   1.00353, 1.01224 };
  
    int i0 = -1;
  
    for ( int i=0; i<nBoundaries-1; i++)
      if ( eta>EtaBoundaries[i] && eta<=EtaBoundaries[i+1] )
	i0 = i;
  
    if( i0>=0 && i0<nBoundaries )
      return CalibFactors[i0];
  
    return 1.;
  
  }  












  // functions for energy scale corrections

  double EnergyRescalerUpgrade::getAlphaLowPt(double transverseEnergy, Variation var, double varSF) {

    double value = 0.;

    if( transverseEnergy>20000. )
      return value;

    double etmin = 10000.;
    double etmax = 20000.;
    double coef = 0.01;


    if( var==LowPtUp ) 
      value += coef/(etmin-etmax)*(transverseEnergy-etmax) * varSF;

    else if( var==LowPtDown ) 
      value -= coef/(etmin-etmax)*(transverseEnergy-etmax) * varSF;

    return value;
    
  }


  double EnergyRescalerUpgrade::getAlphaZee(double cl_eta, Variation var, double varSF) {

    int ieta = m_zeeNom->GetXaxis()->FindBin( cl_eta );

    double value = m_zeeNom->GetBinContent(ieta);

    if( var==ZeeStatUp ) 
      value += m_zeeNom->GetBinError(ieta) * varSF;

    else if( var==ZeeStatDown )
      value -= m_zeeNom->GetBinError(ieta) * varSF;

    else if( var==ZeeGenUp && m_zeeModel ) {
      ieta = m_zeeModel->GetXaxis()->FindBin( cl_eta );
      value += m_zeeModel->GetBinError(ieta) * varSF;
    }

    else if( var==ZeeGenDown && m_zeeModel ) {
      ieta = m_zeeModel->GetXaxis()->FindBin( cl_eta );
      value -= m_zeeModel->GetBinError(ieta) * varSF;
    }

    else if( var==ZeeMethodUp && m_zeeMethod ) {
      ieta = m_zeeMethod->GetXaxis()->FindBin( cl_eta );
      value += m_zeeMethod->GetBinError(ieta) * varSF;

      if( m_debug )
	cout << "ZeeMethodUp : " << m_zeeMethod->GetBinError(ieta) << endl;
    }

    else if( var==ZeeMethodDown && m_zeeMethod ) {
      ieta = m_zeeMethod->GetXaxis()->FindBin( cl_eta );
      value -= m_zeeMethod->GetBinError(ieta) * varSF;

      if( m_debug )
	cout << "ZeeMethodDown : " << m_zeeMethod->GetBinError(ieta) << endl;
    }

    return value;

  }


  double EnergyRescalerUpgrade::getAlphaPS(double cl_eta, Variation var, double varSF) {

    int ieta = m_psNom->GetXaxis()->FindBin( cl_eta );

    double value = m_psNom->GetBinContent(ieta);

    if( var==PSStatUp ) 
      value += m_psNom->GetBinError(ieta) * varSF;

    else if( var==PSStatDown )
      value -= m_psNom->GetBinError(ieta) * varSF;

    else if( var==B12Up && m_psB12 ) {
      ieta = m_psB12->GetXaxis()->FindBin( cl_eta );
      value += m_psB12->GetBinError(ieta) * varSF;
    }

    else if( var==B12Down && m_psB12 ) {
      ieta = m_psB12->GetXaxis()->FindBin( cl_eta );
      value -= m_psB12->GetBinError(ieta) * varSF;
    }

    return value - 1.;

  }


  double EnergyRescalerUpgrade::getPSNonLinearity(double cl_eta, double energy, ParticleType ptype) {

    double value=0;

    if( fabs(cl_eta)>=1.82 )
      return value;

    if( ptype==Electron ) {

      int ieta = m_psElectronEtaBins->GetXaxis()->FindBin( cl_eta ) - 1;
      value = ((TGraphErrors*)m_psElectronGraphs->At(ieta))->GetFunction("f2")->Eval( energy );

    } else if( ptype==Unconverted ) {

      int ieta = m_psUnconvertedEtaBins->GetXaxis()->FindBin( cl_eta ) - 1;
      value = ((TGraphErrors*)m_psUnconvertedGraphs->At(ieta))->GetFunction("f2")->Eval( energy );

    } else if( ptype==Converted ) {

      int ieta = m_psConvertedEtaBins->GetXaxis()->FindBin( cl_eta ) - 1;
      value = ((TGraphErrors*)m_psConvertedGraphs->At(ieta))->GetFunction("f2")->Eval( energy );

    }

    return value;

  }


  double EnergyRescalerUpgrade::getR12(double cl_eta, Variation var, double varSF) {

    if( fabs(cl_eta)>1.37 && fabs(cl_eta)<1.55 )
      return 0.;

    int ieta = m_r12Nom->GetXaxis()->FindBin( cl_eta );

    double value = m_r12Nom->GetBinContent(ieta);

    if( var==R12StatUp ) 
      value += m_r12Nom->GetBinError(ieta) * varSF;

    else if( var==R12StatDown )
      value -= m_r12Nom->GetBinError(ieta) * varSF;

    else if( var==B12Up && m_r12B12 ) { // WATCH SIGN : FIX THIS
      ieta = m_r12B12->GetXaxis()->FindBin( cl_eta );
      value -= m_r12B12->GetBinError(ieta) * varSF;
    }

    else if( var==B12Down && m_r12B12 ) {
      ieta = m_r12B12->GetXaxis()->FindBin( cl_eta );
      value += m_r12B12->GetBinError(ieta) * varSF;
      cout << varSF << " " << cl_eta << " " << ieta << " " <<  m_r12B12->GetBinError(ieta) << endl;
    }

    return value;

  }


  double EnergyRescalerUpgrade::getAlphaMaterial(double cl_eta, ParticleType ptype) {

    double value=0.;

    if( ptype==Electron )

      value = m_matElectronScale->Eval( cl_eta );

    else if( ptype==Unconverted )

      value = m_matUnconvertedScale->Eval( cl_eta );

    else if( ptype==Converted )

      value = m_matConvertedScale->Eval( cl_eta );

    return value;

  }


  double EnergyRescalerUpgrade::getMaterialNonLinearity(double cl_eta, double energy, ParticleType ptype) {

    double et = energy/cosh(cl_eta)/GeV;
    double value = 0.;

    // this is the 2010 parametrization

    if( ptype==Electron ) {
      if( fabs(cl_eta)<=0.6)
	value = -0.0083 * exp(-0.055*et) + 0.003;
      else if( fabs(cl_eta)<=1.0)
	value = -0.013 * exp(-0.019*et) + 0.008;
      else if( fabs(cl_eta)<=1.37)
	value = -0.025 * exp(-0.014*et) + 0.015;
      else if( fabs(cl_eta)>=1.52 && fabs(cl_eta)<=1.82)
	value = -0.023 * exp(-0.026*et) + 0.010;
      else if( fabs(cl_eta)<=2.47)
	value = -0.019 * exp(-0.019*et) + 0.01;
    }

    // this the 2011 parametrization (commented for now)

    // int ieta = m_matElectronEtaBins->GetXaxis()->FindBin( cl_eta ) - 1;
    // double value = ((TGraphErrors*)m_matElectronGraphs->At(ieta))->GetFunction("fMat")->Eval( energy/cosh(cl_eta)/GeV );

    // cout << "getMatNonLin " << ieta << " " << cl_eta << " " << ((TGraphErrors*)m_matElectronGraphs->At(ieta))->GetName() << " " 
    // 	 << energy/cosh(cl_eta)/GeV << " " << ((TGraphErrors*)m_matElectronGraphs->At(ieta))->GetFunction("fMat")->Eval( energy/cosh(cl_eta)/GeV ) << endl;

    // if( ptype==Unconverted )

    //   value *= getAlphaMaterial( cl_eta, Unconverted ) / getAlphaMaterial( cl_eta, Electron );

    // else if( ptype==Converted )

    //   value *= getAlphaMaterial( cl_eta, Converted ) / getAlphaMaterial( cl_eta, Electron );



    return value;

  }


} // egRescaler






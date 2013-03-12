//////////////////////////////////////////////////////////////
// A toy mc program to estimate the background             ///
// in the Z+ee final state                                 ///
// the Z->ee and the Z->mumu final states are              /// 
// treated  separately                                     ///
//                                                         ///
//////////////////////////////////////////////////////////////
// K. Nikolopoulos (BNL)                                   ///
// Feb 22, 2012                                            ///
//////////////////////////////////////////////////////////////
int toymc()
{
  const int Ncatexp = 3;   // number of experimental electron categories (E,C,F)
  const int Ncatmc  = 4;   // number of mc truth electron cartegories (e,c,f,b)
  const int Ncat    = 6;   // number of experimental categories for pairs
  const int Ncatm  = 10;  // number of mctruth categories for pairs
  const int nExp = 5000;   // number of pseudoexperiments
  /// observed yields at control region Z(2xloose++)+2x(reco+Rhad+Reta+Weta2+nsi>3)
  /// this should be integer (in principle), and it has no statistical uncertainty
  /// 0 --> EE
  /// 1 --> EC
  /// 2 --> EF
  /// 3 --> CC
  /// 4 --> CF
  /// 5 --> FF
  double observed[Ncat] = {0.};
  fstream filestr ("data_2mu2e.txt", fstream::in);
  for(int icount=0;icount<Ncat;icount++)
    {
      char txt1[2];
      double nevents;
      filestr >>txt1>> nevents;
      //std::cerr<<nevents<<"\n";
      observed[icount]=nevents;
    }
  filestr.close();

  /// fractions[Ncat][Ncat]
  /// purity of each experimental category from MC 
  /// two dimensional array, first dimension is experimental category for pair i, second is fraction of true events of category j in category i
  /// to correctly compute the uncertainties of these fractions, please provide the actual MC yields
  double sumfractions[Ncat][Ncatm] = { 0.};
  double fractions[Ncat][Ncatm] = { 0.};
  double efractions[Ncat][Ncatm] = { 0.};

  fstream filestr ("purityPoisson_2mu2e.txt", fstream::in);
  char txt00[200];
  filestr.getline(txt00,200);
  //std::cerr<< txt00<<"\n";
  for(int icount=0;icount<Ncat;icount++)
    {
      char txt1[2];
      double nevents;
      filestr >>txt1 >>fractions[icount][0]
	      >>fractions[icount][1]
	      >>fractions[icount][2]
	      >>fractions[icount][3]
	      >>fractions[icount][4]
	      >>fractions[icount][5]
	      >>fractions[icount][6]
	      >>fractions[icount][7]
	      >>fractions[icount][8]
	      >>fractions[icount][9];
    }
  filestr.close();
 
  /// Efficiency of trackIsolation/caloIsolation and d0significance
  /// two dimensional array, first dimension is experimental category for pair i, second is fraction of true events of category j in category i
  fstream filestr ("effi.txt", fstream::in);
  char txt01[100];
  filestr.getline(txt01,100);
  std::cout<< txt01<<"\n";
  double effi[Ncatexp][Ncatmc]  = { 0.};
  double eeffi[Ncatexp][Ncatmc] = { 0.};
  for(int icount=0;icount<Ncatexp;icount++)
    {
      char txt1[2];
      double nevents;
      filestr >>txt1>> effi[icount][0]>>eeffi[icount][0]
	      >> effi[icount][1]>>eeffi[icount][1]
	      >> effi[icount][2]>>eeffi[icount][2]
	      >> effi[icount][3]>>eeffi[icount][3];
	//std::cerr<<effi[icount][3]<<std::endl;
    }
  filestr.close();

  double effitabl[6][10]={ {effi[0][0]*effi[0][0], effi[0][0]*effi[0][3], effi[0][0]*effi[0][1], effi[0][0]*effi[0][2], effi[0][3]*effi[0][3], effi[0][3]*effi[0][1], effi[0][3]*effi[0][2], effi[0][1]*effi[0][1],effi[0][1]*effi[0][2],effi[0][2]*effi[0][2]},
			   {effi[0][0]*effi[1][0], 0.5*effi[0][0]*effi[1][3]+0.5*effi[1][0]*effi[0][3], 0.5*effi[0][0]*effi[1][1]+ 0.5*effi[1][0]*effi[0][1], 0.5*effi[0][0]*effi[1][2]+ 0.5*effi[1][0]*effi[0][2], effi[0][3]*effi[1][3],
			    0.5*effi[0][3]*effi[1][3]+0.5*effi[1][3]*effi[0][1],0.5*effi[0][3]*effi[1][2]+0.5*effi[1][3]*effi[0][2],effi[0][1]*effi[1][1],0.5*effi[0][1]*effi[1][2]+0.5*effi[1][1]*effi[0][2],effi[0][2]*effi[1][2]},
			   {effi[0][0]*effi[2][0], 0.5*effi[0][0]*effi[2][3]+0.5*effi[2][0]*effi[0][3], 0.5*effi[0][0]*effi[2][1]+ 0.5*effi[2][0]*effi[0][1], 0.5*effi[0][0]*effi[2][2]+ 0.5*effi[2][0]*effi[0][2], effi[0][3]*effi[2][3],
			    0.5*effi[0][3]*effi[2][3]+0.5*effi[2][3]*effi[0][1],0.5*effi[0][3]*effi[2][2]+0.5*effi[2][3]*effi[0][2],effi[0][1]*effi[2][1],0.5*effi[0][1]*effi[2][2]+0.5*effi[2][1]*effi[0][2],effi[0][2]*effi[2][2]},
			   {effi[1][0]*effi[1][0], effi[1][0]*effi[1][3], effi[1][0]*effi[1][1], effi[1][0]*effi[1][2], effi[1][3]*effi[1][3], effi[1][3]*effi[1][1], effi[1][3]*effi[1][2], effi[1][1]*effi[1][1],effi[1][1]*effi[1][2],effi[1][2]*effi[1][2]},
			   {effi[1][0]*effi[2][0], 0.5*effi[1][0]*effi[2][3]+0.5*effi[2][0]*effi[1][3], 0.5*effi[1][0]*effi[2][1]+ 0.5*effi[2][0]*effi[1][1], 0.5*effi[1][0]*effi[2][2]+ 0.5*effi[2][0]*effi[1][2], effi[1][3]*effi[2][3],
			    0.5*effi[1][3]*effi[2][3]+0.5*effi[2][3]*effi[1][1],0.5*effi[1][3]*effi[2][2]+0.5*effi[2][3]*effi[1][2],effi[1][1]*effi[2][1],0.5*effi[1][1]*effi[2][2]+0.5*effi[2][1]*effi[1][2],effi[1][2]*effi[2][2]},
			   {effi[2][0]*effi[2][0], effi[2][0]*effi[2][3], effi[2][0]*effi[2][1], effi[2][0]*effi[2][2], effi[2][3]*effi[2][3], effi[2][3]*effi[2][1], effi[2][3]*effi[2][2], effi[2][1]*effi[2][1],effi[2][1]*effi[2][2],effi[2][2]*effi[2][2]}};	 

  TRandom2 *rndm=new TRandom2(99);
  TH1F*h=new TH1F("h","",200,0,7);

  for(int iExp=0;iExp<nExp;iExp++)
    {
      if(iExp%250==0)
	std::cout<<iExp<<std::endl;

      /// variate fractions according to uncertainty and re-normalize fractions
      /// current approach approximate --> need the actual poisson numbers
      for(int i=0;i<Ncat;i++)
	{
	  double tmpfractions[Ncat][Ncatm] = { 0.};
	  for(int j=0;j<10;j++){
	    //tmpfractions[i][j] = rndm->Gaus(fractions[i][j],efractions[i][j]);
	    tmpfractions[i][j] = rndm->Poisson(fractions[i][j]);
      if(tmpfractions[i][j] < 0) tmpfractions[i][j] = 0;
    }
	  double sum = 0.;
	  for(int j=0;j<10;j++)
	    sum += tmpfractions[i][j];
	  for(int j=0;j<10;j++)
	    tmpfractions[i][j]/=sum;
	  sumfractions[i][0]=tmpfractions[i][0];
	  //std::cout<<sumfractions[i][0]<<"\t";
	  for(int j=1;j<10;j++)
	    {
	      sumfractions[i][j]=sumfractions[i][j-1]+tmpfractions[i][j];
	      //std::cout<<sumfractions[i][j]<<"\t";
	    }
	  //std::cout<< "\n";      
	}
      double sum = 0.;
      for(int icat=0;icat<Ncat;icat++)
	{
	  for(int idata=0;idata<(int)(observed[icat]);idata++)
	    {
	      double tmp = rndm->Uniform();
	      int icatMC = -1;
	      for(int i=0;i<10;i++)
		{
		  if(tmp<sumfractions[icat][i])
		    {
		      icatMC=i;
		      break;
		    }
		}
	      if(icatMC==0 || icatMC < 0) continue; // this is a true ee event not count it as bkg
	      sum+=effitabl[icat][icatMC];	      
      //cout<<"icatMC: "<< icatMC<<"; "<<sum<<endl;
	    }
	}
      h->Fill(sum);
    }
  gStyle->SetOptStat(1111);
  TCanvas*c=new TCanvas();
  h->SetStats(kTRUE);
  h->Draw();
  c->Print("bkg2mu2ePoisson.png");
  c->Print("bkg2mu2ePoisson.eps");
  return 0;
}

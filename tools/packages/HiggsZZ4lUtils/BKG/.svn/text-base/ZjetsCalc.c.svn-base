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
#include<iomanip>
using namespace std;
int toymc()
{
  const int Ncatexp = 3;   // number of experimental electron categories (E,C,F)
  const int Ncatmc  = 4;   // number of mc truth electron cartegories (e,c,f,b)
  const int Ncat    = 9;//6   // number of experimental categories for pairs
  const int Ncatm   = 16;//10   // number of mctruth categories for pairs
  const int nExp = 10000;  // number of pseudoexperiments
  /// observed yields at control region Z(2xloose++)+2x(reco+Rhad+Reta+Weta2+nsi>3)
  /// this should be integer (in principle), and it has no statistical uncertainty
  /// 0 --> EE
  /// 1 --> EC
  /// 2 --> EF
  /// 3 --> CC
  /// 4 --> CF
  /// 5 --> FF

  //////////////////////
  /*
  fstream filestr ("EL_data.txt", fstream::in);
  fstream filestr ("EL2_purity.txt", fstream::in);
  fstream filestr ("EL2_effi.txt", fstream::in);
  */
  ////////////////////
  /*
  fstream filestr ("MU_data.txt", fstream::in);
  fstream filestr ("MU3_purity.txt", fstream::in);
  fstream filestr ("MU3_effi.txt", fstream::in);
  */
  ////////////////////
  /*
  fstream filestr ("os_mu_data.txt", fstream::in);
  fstream filestr ("os_mu_purity.txt", fstream::in);
  fstream filestr ("os_mu_effi.txt", fstream::in);
  */
  /*
  fstream filestr ("zee_dr0.2/data.txt", fstream::in);
  fstream filestr1 ("zee_dr0.2/purity.txt", fstream::in);
  fstream filestr2 ("zee_dr0.2/effi.txt", fstream::in);
  */
  /*
  fstream filestr ("zee_nom/data.txt", fstream::in);
  fstream filestr1 ("zee_nom/purity.txt", fstream::in);
  fstream filestr2 ("zee_nom/effi.txt", fstream::in);
  */
  /*
  fstream filestr ("forxy/data.txt", fstream::in);
  fstream filestr1 ("forxy/purity.txt", fstream::in);
  fstream filestr2 ("forxy/effi.txt", fstream::in);
  */
  /// Xiangyang Looser selection
  /**
  fstream filestr ("poisson_looser/data.txt", fstream::in);
  //fstream filestr1("poisson_looser/purityPoisson.txt", fstream::in);
  fstream filestr1("poisson_looser/purityPoisson_noExchange.txt", fstream::in);
  fstream filestr2("poisson_looser/effi.txt", fstream::in);
  **/
  /**
  fstream filestr ("poisson_looser/data_2mu2e.txt", fstream::in);
  fstream filestr1("poisson_looser/purityPoisson_2mu2e.txt", fstream::in);
  //fstream filestr1("poisson_looser/purityPoisson_2mu2e_noExchange.txt", fstream::in);
  fstream filestr2("poisson_looser/effi.txt", fstream::in);
  **/
  fstream filestr ("toyExpRecommend/data_2mu2e.txt", fstream::in);
  fstream filestr1("toyExpRecommend/purityPoisson_2mu2e_noExchange.txt", fstream::in);
  fstream filestr2("toyExpRecommend/effi.txt", fstream::in);
  /*
  fstream filestr ("toyExpRecommend/data.txt", fstream::in);
  fstream filestr1("toyExpRecommend/purityPoisson_noExchange.txt", fstream::in);
  fstream filestr2("toyExpRecommend/effi.txt", fstream::in);
  */
  double observed[Ncat] = {0.};
  for(int icount=0;icount<Ncat;icount++)
    {
      char txt1[2];
      double nevents;
      filestr >>txt1>> nevents;
      std::cerr<<nevents<<"\n";
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

  char txt00[200];
  filestr1.getline(txt00,200);
  //std::cerr<< txt00<<"\n";
  for(int icount=0;icount<Ncat;icount++)
    {
      char txt1[2];
      double nevents;
      /**filestr1 >>txt1 >>fractions[icount][0]>>efractions[icount][0]
	      >>fractions[icount][1]>>efractions[icount][1]
	      >>fractions[icount][2]>>efractions[icount][2]
	      >>fractions[icount][3]>>efractions[icount][3]
	      >>fractions[icount][4]>>efractions[icount][4]
	      >>fractions[icount][5]>>efractions[icount][5]
	      >>fractions[icount][6]>>efractions[icount][6]
	      >>fractions[icount][7]>>efractions[icount][7]
	      >>fractions[icount][8]>>efractions[icount][8]
	      >>fractions[icount][9]>>efractions[icount][9];
      */
      filestr1 >>txt1 >>fractions[icount][0]
	      >>fractions[icount][1]
	      >>fractions[icount][2]
	      >>fractions[icount][3]
	      >>fractions[icount][4]
	      >>fractions[icount][5]
	      >>fractions[icount][6]
	      >>fractions[icount][7]
	      >>fractions[icount][8]
	       >>fractions[icount][9]
	      >>fractions[icount][10]
	      >>fractions[icount][11]
	      >>fractions[icount][12]
	      >>fractions[icount][13]
	      >>fractions[icount][14]
	      >>fractions[icount][15];
    }
  filestr1.close();

  /// Efficiency of trackIsolation/caloIsolation and d0significance
  /// two dimensional array, first dimension is experimental category for pair i, second is fraction of true events of category j in category i
  char txt01[100];
  filestr2.getline(txt01,100);
  std::cout<< txt01<<"\n";
  double effi[Ncatexp][Ncatmc]  = { 0.};
  double eeffi[Ncatexp][Ncatmc] = { 0.};
  for(int icount=0;icount<Ncatexp;icount++)
    {
      char txt1[2];
      double nevents;
      filestr2 >>txt1>> effi[icount][0]>>eeffi[icount][0]
	      >> effi[icount][1]>>eeffi[icount][1]
	      >> effi[icount][2]>>eeffi[icount][2]
	      >> effi[icount][3]>>eeffi[icount][3];
      std::cerr<<effi[icount][0]<<"\t"<<effi[icount][1]<<"\t"<<effi[icount][2]<<"\t"<<effi[icount][3]<<"\t"<<std::endl;
    }
  filestr2.close();

  TRandom2 *rndm=new TRandom2(0);
  TH1F*h=new TH1F("h","",400,0,10);
  TH1F*hCat[Ncat];
  for(int iCat=0;iCat<Ncat;iCat++)
    {
      TString name("hh");
      name+=iCat;
      hCat[iCat] =new TH1F(name,"",400,0,10);
    }
  TH1F*hCatMC[Ncatm];
  for(int iCat=0;iCat<Ncatm;iCat++)
    {
      TString name("hhmc");
      name+=iCat;
      hCatMC[iCat] =new TH1F(name,"",400,0,10);
    }
  for(int iExp=0;iExp<nExp;iExp++)
    {
      if(iExp%250==0)
	std::cout<<iExp<<std::endl;

      double teffi[Ncatexp][Ncatmc] = {0.};
      double TheNumber = 1.;//rndm->Uniform(0.95,1.05);
      for(int i=0;i<Ncatexp;i++)
	for(int j=0;j<4;j++)
	  teffi[i][j] = effi[i][j]*TheNumber;

      int index1[Ncat]={0,0,0,1,1,1,2,2,2};
      int index2[Ncat]={0,1,2,0,1,2,0,1,2};
      double effitabl[Ncat][Ncatm]={0.};
      for(int i=0;i<Ncat;i++)
	for(int j=0;j<Ncatmc;j++)
	  for(int k=0;k<Ncatmc;k++)
	    {
	      effitabl[i][Ncatmc*j+k] = effi[index1[i]][j]*effi[index2[i]][k];
	      //std::cout << i << "\t"<< Ncatmc*j+k << "\t"<< effitabl[i][Ncatmc*j+k]<<" "<<effi[index1[i]][j]<<"\t"<<effi[index2[i]][k]<<std::endl; 
	    }
      /*
      double effitabl[6][10]={ {effi[0][0]*effi[0][0], effi[0][0]*effi[0][3], effi[0][0]*effi[0][1], effi[0][0]*effi[0][2], effi[0][3]*effi[0][3], effi[0][3]*effi[0][1], effi[0][3]*effi[0][2], effi[0][1]*effi[0][1],effi[0][1]*effi[0][2],effi[0][2]*effi[0][2]},
			       {effi[0][0]*effi[1][0], 0.5*effi[0][0]*effi[1][3]+0.5*effi[1][0]*effi[0][3], 0.5*effi[0][0]*effi[1][1]+ 0.5*effi[1][0]*effi[0][1], 0.5*effi[0][0]*effi[1][2]+ 0.5*effi[1][0]*effi[0][2], effi[0][3]*effi[1][3],
				0.5*effi[0][3]*effi[1][3]+0.5*effi[1][3]*effi[0][1],0.5*effi[0][3]*effi[1][2]+0.5*effi[1][3]*effi[0][2],effi[0][1]*effi[1][1],0.5*effi[0][1]*effi[1][2]+0.5*effi[1][1]*effi[0][2],effi[0][2]*effi[1][2]},
			       {effi[0][0]*effi[2][0], 0.5*effi[0][0]*effi[2][3]+0.5*effi[2][0]*effi[0][3], 0.5*effi[0][0]*effi[2][1]+ 0.5*effi[2][0]*effi[0][1], 0.5*effi[0][0]*effi[2][2]+ 0.5*effi[2][0]*effi[0][2], effi[0][3]*effi[2][3],
				0.5*effi[0][3]*effi[2][3]+0.5*effi[2][3]*effi[0][1],0.5*effi[0][3]*effi[2][2]+0.5*effi[2][3]*effi[0][2],effi[0][1]*effi[2][1],0.5*effi[0][1]*effi[2][2]+0.5*effi[2][1]*effi[0][2],effi[0][2]*effi[2][2]},
			       {effi[1][0]*effi[1][0], effi[1][0]*effi[1][3], effi[1][0]*effi[1][1], effi[1][0]*effi[1][2], effi[1][3]*effi[1][3], effi[1][3]*effi[1][1], effi[1][3]*effi[1][2], effi[1][1]*effi[1][1],effi[1][1]*effi[1][2],effi[1][2]*effi[1][2]},
			       {effi[1][0]*effi[2][0], 0.5*effi[1][0]*effi[2][3]+0.5*effi[2][0]*effi[1][3], 0.5*effi[1][0]*effi[2][1]+ 0.5*effi[2][0]*effi[1][1], 0.5*effi[1][0]*effi[2][2]+ 0.5*effi[2][0]*effi[1][2], effi[1][3]*effi[2][3],
				0.5*effi[1][3]*effi[2][3]+0.5*effi[2][3]*effi[1][1],0.5*effi[1][3]*effi[2][2]+0.5*effi[2][3]*effi[1][2],effi[1][1]*effi[2][1],0.5*effi[1][1]*effi[2][2]+0.5*effi[2][1]*effi[1][2],effi[1][2]*effi[2][2]},
			       {effi[2][0]*effi[2][0], effi[2][0]*effi[2][3], effi[2][0]*effi[2][1], effi[2][0]*effi[2][2], effi[2][3]*effi[2][3], effi[2][3]*effi[2][1], effi[2][3]*effi[2][2], effi[2][1]*effi[2][1],effi[2][1]*effi[2][2],effi[2][2]*effi[2][2]}};	 
      */
      /// variate fractions according to uncertainty and re-normalize fractions
      /// current approach approximate --> need the actual poisson numbers
      for(int i=0;i<Ncat;i++)
	{
	  double tmpfractions[Ncat][Ncatm] = { 0.};
	  for(int j=0;j<Ncatm;j++)
	    {
	      //tmpfractions[i][j] = rndm->Gaus(fractions[i][j],efractions[i][j]);
	      //tmpfractions[i][j] = rndm->Poisson(fractions[i][j]);
	      tmpfractions[i][j] = fractions[i][j];
	      if(tmpfractions[i][j]<0.)
		tmpfractions[i][j]=0.;
	      //std::cout << i <<"\t"<< j<<"\t"<< tmpfractions[i][j] <<std::endl;

	    }
	  double sum = 0.;
	  for(int j=0;j<Ncatm;j++)
	    sum += tmpfractions[i][j];
	  if(sum <1.e-10)
	    {
	      sum = 0.;
	      for(int j=0;j<Ncatm;j++)
		{
		  tmpfractions[i][j] = fractions[i][j];
		  if(tmpfractions[i][j]<0.)
		    tmpfractions[i][j]=0.;

		  //std::cout <<"--> "<< i <<"\t"<< j<<"\t"<< tmpfractions[i][j] <<std::endl;
		  sum += tmpfractions[i][j];
		}
	      if(sum<1.e-10)
		{
		  std::cout << "check your purities "<<std::endl;
		  return 0;
		}
	    }
	  for(int j=0;j<Ncatm;j++)
	    tmpfractions[i][j]/=sum;
	  sumfractions[i][0]=tmpfractions[i][0];
	  //std::cout<<sumfractions[i][0]<<"\t";
	  for(int j=1;j<Ncatm;j++)
	    {
	      //std::cout << tmpfractions[i][j]<<std::endl;
	      sumfractions[i][j]=sumfractions[i][j-1]+tmpfractions[i][j];
	      //std::cout<<sumfractions[i][j]<<"\t";
	    }
	  //std::cout<< "\n";      
	  /**
	  std::cout << i<<"\t{"
		    <<sumfractions[i][0]<<"," 
		    <<sumfractions[i][1]<<"," 
		    <<sumfractions[i][2]<<"," 
		    <<sumfractions[i][3]<<"," 
		    <<sumfractions[i][4]<<"," 
		    <<sumfractions[i][5]<<"," 
		    <<sumfractions[i][6]<<"," 
		    <<sumfractions[i][7]<<"," 
		    <<sumfractions[i][8]<<"," 
		    <<sumfractions[i][9]<<"}\n"; 
	  **/
	}
      double sumCat[Ncat]={0.};
      double sumCatMC[Ncatm]={0.};
      double sum = 0.;
      for(int icat=0;icat<Ncat;icat++)
	{
	  for(int idata=0;idata<(int)(observed[icat]);idata++)
	    {
	      double tmp = rndm->Uniform();
	      int icatMC = -1;
	      for(int i=0;i<Ncatm;i++)
		{
		  if(tmp<sumfractions[icat][i])
		    {
		      icatMC=i;
		      break;
		    }
		}
	      if(icatMC==0)
		continue; // this is a true ee event not count it as bkg
	      //std::cout << "here "<<icatMC<<tmp<<std::endl;
	      sumCat[icat]+=effitabl[icat][icatMC];
	      sumCatMC[icatMC]+=effitabl[icat][icatMC];
	      sum+=effitabl[icat][icatMC];
	      //std::cout << sum << "\t"<< sumCat[icat]<<std::endl;
//std::cout << effitabl[icat][icatMC]<<"\n";
	    }
	}
      //std::cout << sum <<std::endl;
      h->Fill(sum);
      for(int iCat=0;iCat<Ncat;iCat++)
	hCat[iCat]->Fill(sumCat[iCat]);
      for(int iCat=0;iCat<Ncatm;iCat++)
	hCatMC[iCat]->Fill(sumCatMC[iCat]);
    }
  gStyle->SetOptStat(1111);
  TCanvas*c=new TCanvas();
  h->SetStats(kTRUE);
  h->Draw();
  //c->Print("bkg4e.png");
  //c->Print("bkg4e.eps");
  c->Print("bkg2mu2e.png");
  c->Print("bkg2mu2e.eps");
  std::cout << "Expected BKG in SR = "<< h->GetMean()<<"\t"<< h->GetRMS()<<std::endl;
  TCanvas*c2=new TCanvas();
  c2->Divide(2,3);
  std::cout<< " experimental categories == "<<std::endl;
  TString *catExp[Ncat];
  catExp[0]=new TString("EE");
  catExp[1]=new TString("EC");
  catExp[2]=new TString("EF");
  catExp[3]=new TString("CE");
  catExp[4]=new TString("CC");
  catExp[5]=new TString("CF");
  catExp[6]=new TString("FE");
  catExp[7]=new TString("FC");
  catExp[8]=new TString("FF");
  TString *catTrue[Ncatm];
  catTrue[0]=new TString("ee");
  catTrue[1]=new TString("eb");
  catTrue[2]=new TString("ec");
  catTrue[3]=new TString("ef");
  catTrue[4]=new TString("be");
  catTrue[5]=new TString("bb");
  catTrue[6]=new TString("bc");
  catTrue[7]=new TString("bf");
  catTrue[8]=new TString("ce");
  catTrue[9]=new TString("cb");
  catTrue[10]=new TString("cc");
  catTrue[11]=new TString("cf");
  catTrue[12]=new TString("fe");
  catTrue[13]=new TString("fb");
  catTrue[14]=new TString("fc");
  catTrue[15]=new TString("ff");

  for(int iCat=0;iCat<Ncat;iCat++)
    {
      std::cout<<setprecision(3)<< *catExp[iCat] << "\t" << hCat[iCat]->GetMean()<<"\t" <<  hCat[iCat]->GetRMS()<<std::endl;
      c2->cd(iCat+1);
      hCat[iCat]->Draw();
    }
  c2->Print("bkfdetail.eps");
  std::cout<< " true categories == "<<std::endl;
  for(int iCat=0;iCat<Ncatm;iCat++)
    {
      std::cout<<setprecision(3)<< *catTrue[iCat] << "\t" << hCatMC[iCat]->GetMean()<<"\t"<< hCatMC[iCat]->GetRMS()<<std::endl;
    }
  return 0;
}

################################
#                              #
#     F.Tarrade BNL            #
#     Jan 6, 2011              #
#     Smooth ZZ Histos         #
#                              #
################################

#!/usr/bin/env python
import sys 
import os
import commands
import string

#path='/afs/cern.ch/user/t/tarrade/scratch0/HiggsSearch/HiggsCombination/H4leptons/H4lData/Total'
path='.'

doOnlyPlots=False

#sCommand = 'cd  '+path+'; ls ahistos_*.root'
#status,output = commands.getstatusoutput(sCommand)
#print status
#print output

from ROOT import *
import ROOT
ROOT.gROOT.LoadMacro('/afs/cern.ch/user/t/tarrade/scratch0/FourLeptons/Analysis_Code/FourLeptonsD3PDAnalysis/atlasstyle/AtlasStyle.C')
ROOT.gROOT.LoadMacro('/afs/cern.ch/user/t/tarrade/scratch0/FourLeptons/Analysis_Code/FourLeptonsD3PDAnalysis/atlasstyle/AtlasUtils.C')

# Apply AtlasStyle
#ROOT.SetAtlasStyle()
c1 = TCanvas('c1','Example',200,10,700,500)

# 0) 4mu
# 1) 2mu2e
# 2) 4e
# 3) 2e2mu

channel=["4mu",
         "2mu2e",
         "4e",
         "2e2mu"]

htittle=["4\mu",
         "2\mu2e",
         "4e",
         "2e2\mu"]
print htittle

print ''
print ''
#print ' Read input histograms ...'
#histo=['histoOut.root',
#       'histoOut.root',
#       'histoOut.root',
#       'histoOut.root']
#histo=['ahistos_1100.root',
#       'ahistos_1100.root',
#       'ahistos_1100.root',
#       'ahistos_1100.root']
#print histo

print ''
print ''
print ' Read input TTree ...'
#ttree=['out0_new2011.root',
#       'out1_new2011.root',
#       'out2_new2011.root',
#       'out3_new2011.root']

#ttree=['ZZ_gg_tree_4mu.root',
#       'ZZ_gg_tree_2mu2e.root',
#       'ZZ_gg_tree_4e.root',
#       'ZZ_gg_tree_2e2mu.root']


ttree=['ZZ_qq_tree_4mu.root',
       'ZZ_qq_tree_2mu2e.root',
       'ZZ_qq_tree_4e.root',
       'ZZ_qq_tree_2e2mu.root']


print ttree

print ''
print ''
print ' Create output histograms ...'
output=['histos_ZZSmooth_2012.root',
        'histos_ZZSmooth_2012.root',
        'histos_ZZSmooth_2012.root',
        'histos_ZZSmooth_2012.root']
print output

print ''
print ''
rho1=[1.0,
      1.0,
      1.0,
      1.0]
print rho1

print ''
print ''

rho2=[0.5,
      0.5,
      0.5,
      0.5]
print rho2    
print ''
print ''

rho3=[0.25,
      0.25,
      0.25,
      0.25]
print rho3    
print ''
print ''


#    if(i==3) rho1=1.8;
#    if(i==2) rho1=1.2;
#    if(i==1) rho1=1.2;
#    if(i==0) rho1=1.8;
    
#    Double_t rho;
#    if(i==3) rho=0.6;
#    if(i==2) rho=0.4;
#    if(i==1) rho=0.6;
#    if(i==0) rho=0.6;

if not doOnlyPlots :
    for i, item in enumerate(ttree) :
        #print histo[i]
        
        # read file
        #RootFile_hZZ=TFile(path+"/"+histo[i],"read")
        #RootFile_hZZ.ls()
    
        # read histogram
        # For 'histoOut.root'
        #hZZ = RootFile_hZZ.Get('histoZZ'+str(i))
        # for 'ahistos_1100.root'
        #hZZ = RootFile_hZZ.Get('histoZZ_'+str(i))
        #hZZ.Draw()
        #c1.Update()
        # c1.SaveAs("zz.eps")
        #raw_input("Press ENTER to exit")

        print ttree[i]

        # read file
        RootFile_tZZ=TFile(path+"/"+ttree[i],"read")
        #RootFile_tZZ.ls()

        # read TTree
        tZZ=RootFile_tZZ.Get("tree")
        #tZZ.Print()
        
        hZZ=TH1D("ZZ","ZZ using TTree",2000,0,1000)
        entries = tZZ.GetEntries()
        for j in xrange(entries):
            #print tZZ.mass
            #print tZZ.weight
            tZZ.GetEntry(j)
            hZZ.Fill(tZZ.mass,tZZ.weight)

        hZZ.Draw()
        c1.Update()
        # c1.SaveAs("zz.eps")
        raw_input("Press ENTER to exit")

        print ''
        print ''
        MassMax=hZZ.GetXaxis().GetXmax()
        MassMin=hZZ.GetXaxis().GetXmin()
        print " hZZ max = ",MassMax
        print " hZZ min = ",MassMin
        
        print ''
        print ''
        NBin= hZZ.GetNbinsX()
        print " N Bins for hZZ = ",NBin
        
        print ''
        print ''
        weight =ROOT.RooRealVar("weight","weight",0,100000)
        mass   =ROOT.RooRealVar("mass","mass",MassMin,MassMax)
        var    =ROOT.RooArgSet(mass,weight);
        mass.setBins(NBin)
        mass.Print()
        
        hZZtree=TH1D("ZZtree","ZZ using TTree",NBin,MassMin,MassMax)
        entries = tZZ.GetEntries()
        for j in xrange(entries):
            #print tZZ.mass
            #print tZZ.weight
            tZZ.GetEntry(j)
            hZZtree.Fill(tZZ.mass,tZZ.weight)
        hZZtree.SetTitle("ZZ using TTree");
        hZZtree.SetMarkerStyle(34)
        hZZtree.SetLineColor(kViolet)
        hZZtree.SetMarkerColor(kViolet)
        hZZtree.GetXaxis().SetTitle("m_{"+str(htittle[i])+"} [GeV]")
        print 'ZZ = ',hZZ.Integral()
        print 'ZZ TTree = ',hZZtree.Integral()
        scale = (hZZ.Integral()/hZZtree.Integral())
        hZZtree.Scale(scale)
        hZZtree.Draw("P")
        hZZtree.Draw("SAME")
        hZZ.Draw("SAME")
        c1.Update()
        # c1.SaveAs("zz.eps")
        raw_input("Press ENTER to exit")
        
        print ''
        print ''
        d = ROOT.RooDataSet("d"," zz mass spectrum ",var,ROOT.RooFit.Import(tZZ),ROOT.RooFit.WeightVar("weight"))
        print " Weight for the RooDataset = ",d.weight()
        d.Print("v")
        print " isWeighted for the RooDataset = ",d.isWeighted()
        
        print ''
        print ''
        print ' RooDataSetplot '
        frame = mass.frame()
        # d.SetMarkerStyle(20)
        # d.SetMarkerSize(1.2)
        d.plotOn(frame,ROOT.RooFit.MarkerColor(ROOT.RooFit.kBlack),ROOT.RooFit.MarkerSize(0.2),ROOT.RooFit.MarkerStyle(20))
        # RooAbsData.plotOn( d, frame )
        
        frame.Draw()
        c1.Update()
        # c1.SaveAs("zz.eps")
        raw_input("Press ENTER to exit")
        
        keys_nomirror  =ROOT.RooKeysPdf("%s_keys_mirror"  % hZZ.GetName(),"",mass,d,ROOT.RooKeysPdf.NoMirror,rho1[i])
        keys_nomirror2 =ROOT.RooKeysPdf("%s_keys_mirror2" % hZZ.GetName(),"",mass,d,ROOT.RooKeysPdf.NoMirror,rho2[i])
        keys_nomirror3 =ROOT.RooKeysPdf("%s_keys_mirror3" % hZZ.GetName(),"",mass,d,ROOT.RooKeysPdf.NoMirror,rho3[i])
        
        
        
        keys_nomirror.plotOn(frame,ROOT.RooFit.LineColor(ROOT.RooFit.kBlue))
        keys_nomirror2.plotOn(frame,ROOT.RooFit.LineColor(ROOT.RooFit.kRed))
        keys_nomirror3.plotOn(frame,ROOT.RooFit.LineColor(ROOT.RooFit.kMagenta))
        frame.SetTitle("ZZ background")
        frame.SetXTitle("m_{"+str(htittle[i])+"} [GeV]")
        frame.Draw()
        c1.Update()
        # c1.SaveAs("zz.eps")
        raw_input("Press ENTER to exit")
        
        hZZSmooth_bigger_rho = keys_nomirror.createHistogram("hZZSmooth",mass)
        hZZSmooth_bigger_rho.SetName("histoZZSmooth"+str(i))
        hZZSmooth_bigger_rho.SetTitle("histoZZSmooth"+str(i))
        hZZSmooth_bigger_rho.SetLineColor(kBlue)
        
        bin4=0
        bin5=105*2
        bin0=105*2+1
        bin1=185*2
        bin2=185*2+1
        bin3=2000
        
        Int_bigger_h=hZZSmooth_bigger_rho.Integral(bin2,bin3)
        Int_bigger_l=hZZSmooth_bigger_rho.Integral(bin0,bin1)
        Int_bigger_ll=hZZSmooth_bigger_rho.Integral(bin4,bin5)
        
        print ''
        print ''
        print ' Integral low low mass   (bigger_rho) : ',Int_bigger_ll
        print ' Integral low mass       (bigger_rho) : ',Int_bigger_l
        print ' Integral high mass      (bigger_rho) : ',Int_bigger_h
        print ' Integral Sum            (bigger_rho) : ',Int_bigger_h+Int_bigger_l+Int_bigger_ll
        print ' Integral                (bigger_rho) : ',hZZSmooth_bigger_rho.Integral()
        print ' Integral high/low mass  (bigger_rho) : ',Int_bigger_h/Int_bigger_l
        
        hZZSmooth_smaller_rho = keys_nomirror2.createHistogram("hZZSmooth",mass)
        hZZSmooth_smaller_rho.SetName("histoZZSmooth"+str(i))
        hZZSmooth_smaller_rho.SetTitle("histoZZSmooth"+str(i))
        hZZSmooth_smaller_rho.SetLineColor(kRed)
        
        Int_smaller_h=hZZSmooth_smaller_rho.Integral(bin2,bin3)
        Int_smaller_l=hZZSmooth_smaller_rho.Integral(bin0,bin1)
        Int_smaller_ll=hZZSmooth_smaller_rho.Integral(bin4,bin5)
        
        print ''
        print ''
        print ' Integral low low mass   (smaller_rho) : ',Int_smaller_ll
        print ' Integral low mass       (smaller_rho) : ',Int_smaller_l
        print ' Integral high mass      (smaller_rho) : ',Int_smaller_h
        print ' Integral Sum            (smaller_rho) : ',Int_smaller_h+Int_smaller_l+Int_smaller_ll
        print ' Integral                (smaller_rho) : ',hZZSmooth_smaller_rho.Integral()
        print ' Integral high/low mass  (smaller_rho) : ',Int_smaller_h/Int_smaller_l

        hZZSmooth_smaller2_rho = keys_nomirror3.createHistogram("hZZSmooth",mass)
        hZZSmooth_smaller2_rho.SetName("histoZZSmooth"+str(i))
        hZZSmooth_smaller2_rho.SetTitle("histoZZSmooth"+str(i))
        hZZSmooth_smaller2_rho.SetLineColor(kRed)
        
        Int_smaller2_h=hZZSmooth_smaller2_rho.Integral(bin2,bin3)
        Int_smaller2_l=hZZSmooth_smaller2_rho.Integral(bin0,bin1)
        Int_smaller2_ll=hZZSmooth_smaller2_rho.Integral(bin4,bin5)
        
        print ''
        print ''
        print ' Integral low low mass   (smaller_rho) : ',Int_smaller2_ll
        print ' Integral low mass       (smaller_rho) : ',Int_smaller2_l
        print ' Integral high mass      (smaller_rho) : ',Int_smaller2_h
        print ' Integral Sum            (smaller_rho) : ',Int_smaller2_h+Int_smaller2_l+Int_smaller2_ll
        print ' Integral                (smaller_rho) : ',hZZSmooth_smaller2_rho.Integral()
        print ' Integral high/low mass  (smaller_rho) : ',Int_smaller2_h/Int_smaller2_l

        hZZSmooth=hZZSmooth_bigger_rho.Clone()
        hZZSmooth.SetName("histoZZSmooth"+str(i))
        hZZSmooth.SetTitle("histoZZSmooth"+str(i))
        hZZSmooth.SetLineColor(kCyan)
        
        bin_intersection_point    = -1
        value_intersection_point  = -1
        diff                      = -1
        
        for jj in range(0,NBin) :
            content_b =hZZSmooth_bigger_rho.GetBinContent(jj+1)
            bin_b     =hZZSmooth_bigger_rho.GetBinCenter(jj+1)
            
            content_s =hZZSmooth_smaller_rho.GetBinContent(jj+1)
            bin_s     =hZZSmooth_smaller_rho.GetBinCenter(jj+1)
            # print 'Bin number = ',jj,' with bin number b : ',bin_b,' and content = ',content_b
            # print 'Bin number = ',jj,' with bin number s : ',bin_s,' and content = ',content_s
            # print 'Difference = ',fabs(content_b-content_s)
            hZZSmooth.SetBinContent(jj,content_s);
        
            bin_intersection_point    = bin_b
            value_intersection_point = content_s
            diff                      = fabs(content_s-content_b)
            if bin_b>170 and bin_b<210 and fabs(content_s-content_b)<5.0*10e-6 :
                break

        print ''
        print ''
        print ' Intersection point between the two histograms : '
        print ' Bin        : ',bin_intersection_point
        print ' Content    : ',value_intersection_point
        print ' Difference : ',diff 
        
        Int_ZZsmooth_h=hZZSmooth.Integral(bin2,bin3)
        Int_ZZsmooth_l=hZZSmooth.Integral(bin0,bin1)
        
        print ''
        print ''
        print ' Integral low mass       (ZZsmooth) : ',Int_ZZsmooth_l
        print ' Integral high mass      (ZZsmooth) : ',Int_ZZsmooth_h
        print ' Integral Sum            (ZZsmooth) : ',Int_ZZsmooth_h+Int_ZZsmooth_l
        print ' Integral                (ZZsmooth) : ',hZZSmooth.Integral()
        print ' Integral high/low mass  (ZZsmooth) : ',Int_ZZsmooth_h/Int_ZZsmooth_l
        
        Int_ZZ_h=hZZ.Integral(bin2,bin3)
        Int_ZZ_l=hZZ.Integral(bin0,bin1)
        
        print ''
        print ''
        print ' Integral low mass       (ZZ) : ',Int_ZZ_l
        print ' Integral high mass      (ZZ) : ',Int_ZZ_h
        print ' Integral Sum            (ZZ) : ',Int_ZZ_h+Int_ZZ_l
        print ' Integral                (ZZ) : ',hZZ.Integral()
        print ' Integral high/low mass  (ZZ) : ',Int_ZZ_h/Int_ZZ_l
        
        print ''
        print ''
        
        scale_s = (hZZ.Integral()/hZZSmooth_smaller_rho.Integral())
        scale_b = (hZZ.Integral()/hZZSmooth_bigger_rho.Integral())
    
        hZZSmooth_bigger_rho.Scale(scale_b)
        hZZSmooth_smaller_rho.Scale(scale_s)
        
        hZZ.Draw()
        hZZSmooth_bigger_rho.Draw("SAME")
        hZZSmooth_smaller_rho.Draw("SAME")
        c1.Update()
        # c1.SaveAs("zz.eps")
        raw_input("Press ENTER to exit")
        
        scale_f = (hZZ.Integral()/hZZSmooth.Integral())
        hZZSmooth.Scale(scale_f)
        hZZ.Draw()
        hZZSmooth_bigger_rho.Draw("SAME")
        hZZSmooth_smaller_rho.Draw("SAME")
        hZZSmooth.Draw("SAME")
        c1.Update()
        # c1.SaveAs("zz.eps")
        raw_input("Press ENTER to exit")
        
        if i==0 :
            # create file
            RootFile=TFile(path+"/"+output[i],"recreate")
            RootFile.ls()
        else :
            # read file
            RootFile=TFile(path+"/"+output[i],"update")
            RootFile.ls()
        hZZ.Write("histoZZ_"+str(i))
        hZZSmooth_smaller_rho.Write("histoZZSmooth_smaller_"+str(i))
        hZZSmooth_bigger_rho.Write("histoZZSmooth_bigger_"+str(i))
        hZZSmooth.Write("histoZZSmooth_"+str(i))
        RootFile.Write()
        RootFile.Close()



# read file
RootFile_o=TFile(path+"/"+output[0],"update")
hZZ_0=0
hZZ_1=0
hZZ_2=0
hZZ_3=0

hZZ_s_0=0
hZZ_s_1=0
hZZ_s_2=0
hZZ_s_3=0

hZZ_b_0=0
hZZ_b_1=0
hZZ_b_2=0
hZZ_b_3=0

hZZ_f_0=0
hZZ_f_1=0
hZZ_f_2=0
hZZ_f_3=0

for i, item in enumerate(ttree) :

    # read histogram
    if i==0 :
        hZZ_0   = RootFile_o.Get('histoZZ_'+str(i))
        hZZ_s_0 = RootFile_o.Get('histoZZSmooth_smaller_'+str(i))
        hZZ_b_0 = RootFile_o.Get('histoZZSmooth_bigger_'+str(i))
        hZZ_f_0 = RootFile_o.Get('histoZZSmooth_'+str(i))
    if i==1 :
        hZZ_1   = RootFile_o.Get('histoZZ_'+str(i))
        hZZ_s_1 = RootFile_o.Get('histoZZSmooth_smaller_'+str(i))
        hZZ_b_1 = RootFile_o.Get('histoZZSmooth_bigger_'+str(i))
        hZZ_f_1 = RootFile_o.Get('histoZZSmooth_'+str(i))
    if i==2 :
        hZZ_2   = RootFile_o.Get('histoZZ_'+str(i))
        hZZ_s_2 = RootFile_o.Get('histoZZSmooth_smaller_'+str(i))
        hZZ_b_2 = RootFile_o.Get('histoZZSmooth_bigger_'+str(i))
        hZZ_f_2 = RootFile_o.Get('histoZZSmooth_'+str(i))
    if i==3 :
        hZZ_3   = RootFile_o.Get('histoZZ_'+str(i))
        hZZ_s_3 = RootFile_o.Get('histoZZSmooth_smaller_'+str(i))
        hZZ_b_3 = RootFile_o.Get('histoZZSmooth_bigger_'+str(i))
        hZZ_f_3 = RootFile_o.Get('histoZZSmooth_'+str(i))
        
hZZ_0.Draw()
hZZ_0.SetLineColor(kViolet)
hZZ_1.Draw("SAME")
hZZ_1.SetLineColor(kBlue)
hZZ_2.Draw("SAME")
hZZ_2.SetLineColor(kRed)
hZZ_3.Draw("SAME")
hZZ_3.SetLineColor(kGreen)

legend=TLegend(0.58,(0.78-4*0.03),0.83,0.82)
legend.SetFillColor(0)
legend.SetBorderSize(0)
legend.AddEntry(hZZ_0, "channel : "+str(htittle[0]), "l")
legend.AddEntry(hZZ_1, "channel : "+str(htittle[1]), "l")
legend.AddEntry(hZZ_2, "channel : "+str(htittle[2]), "l")
legend.AddEntry(hZZ_3, "channel : "+str(htittle[3]), "l")
legend.Draw()

c1.Update()
#c1.SaveAs("zz.eps")
raw_input("Press ENTER to exit")

hZZ_s_0.Draw()
hZZ_s_0.SetLineColor(kViolet)
hZZ_s_1.Draw("SAME")
hZZ_s_1.SetLineColor(kBlue)
hZZ_s_2.Draw("SAME")
hZZ_s_2.SetLineColor(kRed)
hZZ_s_3.Draw("SAME")
hZZ_s_3.SetLineColor(kGreen)

legend=TLegend(0.58,(0.78-4*0.03),0.83,0.82)
legend.SetFillColor(0)
legend.SetBorderSize(0)
legend.AddEntry(hZZ_0, "channel : "+str(htittle[0]), "l")
legend.AddEntry(hZZ_1, "channel : "+str(htittle[1]), "l")
legend.AddEntry(hZZ_2, "channel : "+str(htittle[2]), "l")
legend.AddEntry(hZZ_3, "channel : "+str(htittle[3]), "l")
legend.Draw()

c1.Update()
#c1.SaveAs("zz.eps")
raw_input("Press ENTER to exit")

hZZ_b_0.Draw()
hZZ_b_0.SetLineColor(kViolet)
hZZ_b_1.Draw("SAME")
hZZ_b_1.SetLineColor(kBlue)
hZZ_b_2.Draw("SAME")
hZZ_b_2.SetLineColor(kRed)
hZZ_b_3.Draw("SAME")
hZZ_b_3.SetLineColor(kGreen)

legend=TLegend(0.58,(0.78-4*0.03),0.83,0.82)
legend.SetFillColor(0)
legend.SetBorderSize(0)
legend.AddEntry(hZZ_0, "channel : "+str(htittle[0]), "l")
legend.AddEntry(hZZ_1, "channel : "+str(htittle[1]), "l")
legend.AddEntry(hZZ_2, "channel : "+str(htittle[2]), "l")
legend.AddEntry(hZZ_3, "channel : "+str(htittle[3]), "l")
legend.Draw()

c1.Update()
#c1.SaveAs("zz.eps")
raw_input("Press ENTER to exit")

hZZ_f_0.Draw()
hZZ_f_0.SetLineColor(kViolet)
hZZ_f_1.Draw("SAME")
hZZ_f_1.SetLineColor(kBlue)
hZZ_f_2.Draw("SAME")
hZZ_f_2.SetLineColor(kRed)
hZZ_f_3.Draw("SAME")
hZZ_f_3.SetLineColor(kGreen)

legend=TLegend(0.58,(0.78-4*0.03),0.83,0.82)
legend.SetFillColor(0)
legend.SetBorderSize(0)
legend.AddEntry(hZZ_0, "channel : "+str(htittle[0]), "l")
legend.AddEntry(hZZ_1, "channel : "+str(htittle[1]), "l")
legend.AddEntry(hZZ_2, "channel : "+str(htittle[2]), "l")
legend.AddEntry(hZZ_3, "channel : "+str(htittle[3]), "l")
legend.Draw()

c1.Update()
#c1.SaveAs("zz.eps")
raw_input("Press ENTER to exit")

###############C.A##############################################
#extra shape PDF +as

hZZ_f_shape_as_p_0 = TH1D("hZZ_f_shape_as_p_0","ZZ using TTree",2000,0,1000)
hZZ_f_shape_as_p_1 = TH1D("hZZ_f_shape_as_p_1","ZZ using TTree",2000,0,1000)
hZZ_f_shape_as_p_2 = TH1D("hZZ_f_shape_as_p_2","ZZ using TTree",2000,0,1000)
hZZ_f_shape_as_p_3 = TH1D("hZZ_f_shape_as_p_3","ZZ using TTree",2000,0,1000)

hZZ_f_shape_as_m_0 = TH1D("hZZ_f_shape_as_m_0","ZZ using TTree",2000,0,1000)
hZZ_f_shape_as_m_1 = TH1D("hZZ_f_shape_as_m_1","ZZ using TTree",2000,0,1000)
hZZ_f_shape_as_m_2 = TH1D("hZZ_f_shape_as_m_2","ZZ using TTree",2000,0,1000)
hZZ_f_shape_as_m_3 = TH1D("hZZ_f_shape_as_m_3","ZZ using TTree",2000,0,1000)

if ttree[0].find("gg",0 ,len(ttree[0])) != -1 :
    for bin in xrange(1,2001):
        if hZZ_f_0.GetBinCenter(bin)> 10:
            hZZ_f_shape_as_p_0.SetBinContent(bin,(1+0.0066*sqrt(hZZ_f_0.GetBinCenter(bin)-10))*hZZ_f_0.GetBinContent(bin))
            hZZ_f_shape_as_p_1.SetBinContent(bin,(1+0.0066*sqrt(hZZ_f_1.GetBinCenter(bin)-10))*hZZ_f_1.GetBinContent(bin))
            hZZ_f_shape_as_p_2.SetBinContent(bin,(1+0.0066*sqrt(hZZ_f_2.GetBinCenter(bin)-10))*hZZ_f_2.GetBinContent(bin))
            hZZ_f_shape_as_p_3.SetBinContent(bin,(1+0.0066*sqrt(hZZ_f_3.GetBinCenter(bin)-10))*hZZ_f_3.GetBinContent(bin))
            hZZ_f_shape_as_m_0.SetBinContent(bin,(1-0.0066*sqrt(hZZ_f_0.GetBinCenter(bin)-10))*hZZ_f_0.GetBinContent(bin))
            hZZ_f_shape_as_m_1.SetBinContent(bin,(1-0.0066*sqrt(hZZ_f_1.GetBinCenter(bin)-10))*hZZ_f_1.GetBinContent(bin))
            hZZ_f_shape_as_m_2.SetBinContent(bin,(1-0.0066*sqrt(hZZ_f_2.GetBinCenter(bin)-10))*hZZ_f_2.GetBinContent(bin))
            hZZ_f_shape_as_m_3.SetBinContent(bin,(1-0.0066*sqrt(hZZ_f_3.GetBinCenter(bin)-10))*hZZ_f_3.GetBinContent(bin))
        else :
            hZZ_f_shape_as_p_0.SetBinContent(bin,hZZ_f_0.GetBinContent(bin))
            hZZ_f_shape_as_p_1.SetBinContent(bin,hZZ_f_1.GetBinContent(bin))
            hZZ_f_shape_as_p_2.SetBinContent(bin,hZZ_f_2.GetBinContent(bin))
            hZZ_f_shape_as_p_3.SetBinContent(bin,hZZ_f_3.GetBinContent(bin))
            hZZ_f_shape_as_m_0.SetBinContent(bin,hZZ_f_0.GetBinContent(bin))
            hZZ_f_shape_as_m_1.SetBinContent(bin,hZZ_f_1.GetBinContent(bin))
            hZZ_f_shape_as_m_2.SetBinContent(bin,hZZ_f_2.GetBinContent(bin))
            hZZ_f_shape_as_m_3.SetBinContent(bin,hZZ_f_3.GetBinContent(bin))
    #        
    integral=hZZ_f_shape_as_p_0.Integral()
    print "ZZ shape_as_0 up integral ",integral," vs ", hZZ_f_0.Integral(), " ratio " , hZZ_f_shape_as_p_0.Integral()/hZZ_f_0.Integral()
    hZZ_f_shape_as_p_0.Scale(hZZ_f_0.Integral()/integral)
    print "scale integral", hZZ_f_shape_as_p_0.Integral()
    #
    integral=hZZ_f_shape_as_p_1.Integral()
    print "ZZ shape_as_1 up integral ",integral," vs ", hZZ_f_1.Integral(), " ratio " , hZZ_f_shape_as_p_1.Integral()/hZZ_f_1.Integral()
    hZZ_f_shape_as_p_1.Scale(hZZ_f_1.Integral()/integral)
    print "scale integral", hZZ_f_shape_as_p_1.Integral()
    #
    integral=hZZ_f_shape_as_p_2.Integral()
    print "ZZ shape_as_2 up integral ",integral," vs ", hZZ_f_2.Integral(), " ratio " , hZZ_f_shape_as_p_2.Integral()/hZZ_f_2.Integral()
    hZZ_f_shape_as_p_2.Scale(hZZ_f_2.Integral()/integral)
    print "scale integral", hZZ_f_shape_as_p_2.Integral()
    #
    integral=hZZ_f_shape_as_p_3.Integral()
    print "ZZ shape_as_3 up integral ",integral," vs ", hZZ_f_3.Integral(), " ratio " , hZZ_f_shape_as_p_3.Integral()/hZZ_f_3.Integral()
    hZZ_f_shape_as_p_3.Scale(hZZ_f_3.Integral()/integral)
    print "scale integral", hZZ_f_shape_as_p_3.Integral()
    ##################minus###############################
    integral=hZZ_f_shape_as_m_0.Integral()
    print "ZZ shape_as_0 minus integral ",integral," vs ", hZZ_f_0.Integral(), " ratio " , hZZ_f_shape_as_m_0.Integral()/hZZ_f_0.Integral()
    hZZ_f_shape_as_m_0.Scale(hZZ_f_0.Integral()/integral)
    print "scale integral", hZZ_f_shape_as_m_0.Integral()
    #
    integral=hZZ_f_shape_as_m_1.Integral()
    print "ZZ shape_as_1 minus integral ",integral," vs ", hZZ_f_1.Integral(), " ratio " , hZZ_f_shape_as_m_1.Integral()/hZZ_f_1.Integral()
    hZZ_f_shape_as_m_1.Scale(hZZ_f_1.Integral()/integral)
    print "scale integral", hZZ_f_shape_as_m_1.Integral()
    #
    integral=hZZ_f_shape_as_m_2.Integral()
    print "ZZ shape_as_2 minus integral ",integral," vs ", hZZ_f_2.Integral(), " ratio " , hZZ_f_shape_as_m_2.Integral()/hZZ_f_2.Integral()
    hZZ_f_shape_as_m_2.Scale(hZZ_f_2.Integral()/integral)
    print "scale integral", hZZ_f_shape_as_m_2.Integral()
    #
    integral=hZZ_f_shape_as_m_3.Integral()
    print "ZZ shape_as_3 minus integral ",integral," vs ", hZZ_f_3.Integral(), " ratio " , hZZ_f_shape_as_m_3.Integral()/hZZ_f_3.Integral()
    hZZ_f_shape_as_m_3.Scale(hZZ_f_3.Integral()/integral)
    print "scale integral", hZZ_f_shape_as_m_3.Integral()

else :
    for bin in xrange(1,2001):
        if hZZ_f_0.GetBinCenter(bin)> 30:
            hZZ_f_shape_as_p_0.SetBinContent(bin,(1+0.0035*sqrt(hZZ_f_0.GetBinCenter(bin)-30))*hZZ_f_0.GetBinContent(bin))
            hZZ_f_shape_as_p_1.SetBinContent(bin,(1+0.0035*sqrt(hZZ_f_1.GetBinCenter(bin)-30))*hZZ_f_1.GetBinContent(bin))
            hZZ_f_shape_as_p_2.SetBinContent(bin,(1+0.0035*sqrt(hZZ_f_2.GetBinCenter(bin)-30))*hZZ_f_2.GetBinContent(bin))
            hZZ_f_shape_as_p_3.SetBinContent(bin,(1+0.0035*sqrt(hZZ_f_3.GetBinCenter(bin)-30))*hZZ_f_3.GetBinContent(bin))
            hZZ_f_shape_as_m_0.SetBinContent(bin,(1-0.0035*sqrt(hZZ_f_0.GetBinCenter(bin)-30))*hZZ_f_0.GetBinContent(bin))
            hZZ_f_shape_as_m_1.SetBinContent(bin,(1-0.0035*sqrt(hZZ_f_1.GetBinCenter(bin)-30))*hZZ_f_1.GetBinContent(bin))
            hZZ_f_shape_as_m_2.SetBinContent(bin,(1-0.0035*sqrt(hZZ_f_2.GetBinCenter(bin)-30))*hZZ_f_2.GetBinContent(bin))
            hZZ_f_shape_as_m_3.SetBinContent(bin,(1-0.0035*sqrt(hZZ_f_3.GetBinCenter(bin)-30))*hZZ_f_3.GetBinContent(bin))
        else:
            hZZ_f_shape_as_p_0.SetBinContent(bin,hZZ_f_0.GetBinContent(bin))
            hZZ_f_shape_as_p_1.SetBinContent(bin,hZZ_f_1.GetBinContent(bin))
            hZZ_f_shape_as_p_2.SetBinContent(bin,hZZ_f_2.GetBinContent(bin))
            hZZ_f_shape_as_p_3.SetBinContent(bin,hZZ_f_3.GetBinContent(bin))
            hZZ_f_shape_as_m_0.SetBinContent(bin,hZZ_f_0.GetBinContent(bin))
            hZZ_f_shape_as_m_1.SetBinContent(bin,hZZ_f_1.GetBinContent(bin))
            hZZ_f_shape_as_m_2.SetBinContent(bin,hZZ_f_2.GetBinContent(bin))
            hZZ_f_shape_as_m_3.SetBinContent(bin,hZZ_f_3.GetBinContent(bin))

    #
    integral=hZZ_f_shape_as_p_0.Integral()
    print "ZZ shape_as_0 up integral ",integral," vs ", hZZ_f_0.Integral(), " ratio " , hZZ_f_shape_as_p_0.Integral()/hZZ_f_0.Integral()
    hZZ_f_shape_as_p_0.Scale(hZZ_f_0.Integral()/integral)
    print "scale integral", hZZ_f_shape_as_p_0.Integral()
    #
    integral=hZZ_f_shape_as_p_1.Integral()
    print "ZZ shape_as_1 up integral ",integral," vs ", hZZ_f_1.Integral(), " ratio " , hZZ_f_shape_as_p_1.Integral()/hZZ_f_1.Integral()
    hZZ_f_shape_as_p_1.Scale(hZZ_f_1.Integral()/integral)
    print "scale integral", hZZ_f_shape_as_p_1.Integral()
    #
    integral=hZZ_f_shape_as_p_2.Integral()
    print "ZZ shape_as_2 up integral ",integral," vs ", hZZ_f_2.Integral(), " ratio " , hZZ_f_shape_as_p_2.Integral()/hZZ_f_2.Integral()
    hZZ_f_shape_as_p_2.Scale(hZZ_f_2.Integral()/integral)
    print "scale integral", hZZ_f_shape_as_p_2.Integral()
    #
    integral=hZZ_f_shape_as_p_3.Integral()
    print "ZZ shape_as_3 up integral ",integral," vs ", hZZ_f_3.Integral(), " ratio " , hZZ_f_shape_as_p_3.Integral()/hZZ_f_3.Integral()
    hZZ_f_shape_as_p_3.Scale(hZZ_f_3.Integral()/integral)
    print "scale integral", hZZ_f_shape_as_p_3.Integral()
    ################minus################
    integral=hZZ_f_shape_as_m_0.Integral()
    print "ZZ shape_as_0 minus integral ",integral," vs ", hZZ_f_0.Integral(), " ratio " , hZZ_f_shape_as_m_0.Integral()/hZZ_f_0.Integral()
    hZZ_f_shape_as_m_0.Scale(hZZ_f_0.Integral()/integral)
    print "scale integral", hZZ_f_shape_as_m_0.Integral()
    #
    integral=hZZ_f_shape_as_m_1.Integral()
    print "ZZ shape_as_1 minus integral ",integral," vs ", hZZ_f_1.Integral(), " ratio " , hZZ_f_shape_as_m_1.Integral()/hZZ_f_1.Integral()
    hZZ_f_shape_as_m_1.Scale(hZZ_f_1.Integral()/integral)
    print "scale integral", hZZ_f_shape_as_m_1.Integral()
    #
    integral=hZZ_f_shape_as_m_2.Integral()
    print "ZZ shape_as_2 minus integral ",integral," vs ", hZZ_f_2.Integral(), " ratio " , hZZ_f_shape_as_m_2.Integral()/hZZ_f_2.Integral()
    hZZ_f_shape_as_m_2.Scale(hZZ_f_2.Integral()/integral)
    print "scale integral", hZZ_f_shape_as_m_2.Integral()    
    #
    integral=hZZ_f_shape_as_m_3.Integral()
    print "ZZ shape_as_3 minus integral ",integral," vs ", hZZ_f_3.Integral(), " ratio " , hZZ_f_shape_as_m_3.Integral()/hZZ_f_3.Integral()
    hZZ_f_shape_as_m_3.Scale(hZZ_f_3.Integral()/integral)
    print "scale integral", hZZ_f_shape_as_m_3.Integral()

hZZ_f_shape_as_p_0.Write()
hZZ_f_shape_as_p_1.Write()
hZZ_f_shape_as_p_2.Write()
hZZ_f_shape_as_p_3.Write()
hZZ_f_shape_as_m_0.Write()
hZZ_f_shape_as_m_1.Write()
hZZ_f_shape_as_m_2.Write()
hZZ_f_shape_as_m_3.Write()

#############################################################################
#extra qcd
hZZ_f_shape_qcd_p_0 = TH1D("hZZ_f_shape_qcd_p_0","ZZ using TTree",2000,0,1000)
hZZ_f_shape_qcd_p_1 = TH1D("hZZ_f_shape_qcd_p_1","ZZ using TTree",2000,0,1000)
hZZ_f_shape_qcd_p_2 = TH1D("hZZ_f_shape_qcd_p_2","ZZ using TTree",2000,0,1000)
hZZ_f_shape_qcd_p_3 = TH1D("hZZ_f_shape_qcd_p_3","ZZ using TTree",2000,0,1000)

hZZ_f_shape_qcd_m_0 = TH1D("hZZ_f_shape_qcd_m_0","ZZ using TTree",2000,0,1000)
hZZ_f_shape_qcd_m_1 = TH1D("hZZ_f_shape_qcd_m_1","ZZ using TTree",2000,0,1000)
hZZ_f_shape_qcd_m_2 = TH1D("hZZ_f_shape_qcd_m_2","ZZ using TTree",2000,0,1000)
hZZ_f_shape_qcd_m_3 = TH1D("hZZ_f_shape_qcd_m_3","ZZ using TTree",2000,0,1000)

if ttree[0].find("gg",0 ,len(ttree[0])) != -1 :
    for bin in xrange(1,2001):
            hZZ_f_shape_qcd_p_0.SetBinContent(bin,(1.04+0.1*sqrt((hZZ_f_0.GetBinCenter(bin)+40)/40))*hZZ_f_0.GetBinContent(bin))
            hZZ_f_shape_qcd_p_1.SetBinContent(bin,(1.04+0.1*sqrt((hZZ_f_1.GetBinCenter(bin)+40)/40))*hZZ_f_1.GetBinContent(bin))
            hZZ_f_shape_qcd_p_2.SetBinContent(bin,(1.04+0.1*sqrt((hZZ_f_2.GetBinCenter(bin)+40)/40))*hZZ_f_2.GetBinContent(bin))
            hZZ_f_shape_qcd_p_3.SetBinContent(bin,(1.04+0.1*sqrt((hZZ_f_3.GetBinCenter(bin)+40)/40))*hZZ_f_3.GetBinContent(bin))
            hZZ_f_shape_qcd_m_0.SetBinContent(bin,(1.04-0.1*sqrt((hZZ_f_0.GetBinCenter(bin)+40)/40))*hZZ_f_0.GetBinContent(bin))
            hZZ_f_shape_qcd_m_1.SetBinContent(bin,(1.04-0.1*sqrt((hZZ_f_1.GetBinCenter(bin)+40)/40))*hZZ_f_1.GetBinContent(bin))
            hZZ_f_shape_qcd_m_2.SetBinContent(bin,(1.04-0.1*sqrt((hZZ_f_2.GetBinCenter(bin)+40)/40))*hZZ_f_2.GetBinContent(bin))
            hZZ_f_shape_qcd_m_3.SetBinContent(bin,(1.04-0.1*sqrt((hZZ_f_3.GetBinCenter(bin)+40)/40))*hZZ_f_3.GetBinContent(bin))
    #        
    integral=hZZ_f_shape_qcd_p_0.Integral()
    print "ZZ shape_qcd_0 up integral ",integral," vs ", hZZ_f_0.Integral(), " ratio " , hZZ_f_shape_qcd_p_0.Integral()/hZZ_f_0.Integral()
    hZZ_f_shape_qcd_p_0.Scale(hZZ_f_0.Integral()/integral)
    print "scale integral", hZZ_f_shape_qcd_p_0.Integral()
    #
    integral=hZZ_f_shape_qcd_p_1.Integral()
    print "ZZ shape_qcd_1 up integral ",integral," vs ", hZZ_f_1.Integral(), " ratio " , hZZ_f_shape_qcd_p_1.Integral()/hZZ_f_1.Integral()
    hZZ_f_shape_qcd_p_1.Scale(hZZ_f_1.Integral()/integral)
    print "scale integral", hZZ_f_shape_qcd_p_1.Integral()
    #
    integral=hZZ_f_shape_qcd_p_2.Integral()
    print "ZZ shape_qcd_2 up integral ",integral," vs ", hZZ_f_2.Integral(), " ratio " , hZZ_f_shape_qcd_p_2.Integral()/hZZ_f_2.Integral()
    hZZ_f_shape_qcd_p_2.Scale(hZZ_f_2.Integral()/integral)
    print "scale integral", hZZ_f_shape_qcd_p_2.Integral()
    #
    integral=hZZ_f_shape_qcd_p_3.Integral()
    print "ZZ shape_qcd_3 up integral ",integral," vs ", hZZ_f_3.Integral(), " ratio " , hZZ_f_shape_qcd_p_3.Integral()/hZZ_f_3.Integral()
    hZZ_f_shape_qcd_p_3.Scale(hZZ_f_3.Integral()/integral)
    print "scale integral", hZZ_f_shape_qcd_p_3.Integral()
    ##################minus###############################
    integral=hZZ_f_shape_qcd_m_0.Integral()
    print "ZZ shape_qcd_0 minus integral ",integral," vs ", hZZ_f_0.Integral(), " ratio " , hZZ_f_shape_qcd_m_0.Integral()/hZZ_f_0.Integral()
    hZZ_f_shape_qcd_m_0.Scale(hZZ_f_0.Integral()/integral)
    print "scale integral", hZZ_f_shape_qcd_m_0.Integral()
    #
    integral=hZZ_f_shape_qcd_m_1.Integral()
    print "ZZ shape_qcd_1 minus integral ",integral," vs ", hZZ_f_1.Integral(), " ratio " , hZZ_f_shape_qcd_m_1.Integral()/hZZ_f_1.Integral()
    hZZ_f_shape_qcd_m_1.Scale(hZZ_f_1.Integral()/integral)
    print "scale integral", hZZ_f_shape_qcd_m_1.Integral()
    #
    integral=hZZ_f_shape_qcd_m_2.Integral()
    print "ZZ shape_qcd_2 minus integral ",integral," vs ", hZZ_f_2.Integral(), " ratio " , hZZ_f_shape_qcd_m_2.Integral()/hZZ_f_2.Integral()
    hZZ_f_shape_qcd_m_2.Scale(hZZ_f_2.Integral()/integral)
    print "scale integral", hZZ_f_shape_qcd_m_2.Integral()
    #
    integral=hZZ_f_shape_qcd_m_3.Integral()
    print "ZZ shape_qcd_3 minus integral ",integral," vs ", hZZ_f_3.Integral(), " ratio " , hZZ_f_shape_qcd_m_3.Integral()/hZZ_f_3.Integral()
    hZZ_f_shape_qcd_m_3.Scale(hZZ_f_3.Integral()/integral)
    print "scale integral", hZZ_f_shape_qcd_m_3.Integral()

else :
    for bin in xrange(1,2001):
        if hZZ_f_0.GetBinCenter(bin)> 20:
            hZZ_f_shape_qcd_p_0.SetBinContent(bin,(1+0.01* sqrt((hZZ_f_0.GetBinCenter(bin)-20)/13))*hZZ_f_0.GetBinContent(bin))
            hZZ_f_shape_qcd_p_1.SetBinContent(bin,(1+0.01* sqrt((hZZ_f_1.GetBinCenter(bin)-20)/13))*hZZ_f_1.GetBinContent(bin))
            hZZ_f_shape_qcd_p_2.SetBinContent(bin,(1+0.01* sqrt((hZZ_f_2.GetBinCenter(bin)-20)/13))*hZZ_f_2.GetBinContent(bin))
            hZZ_f_shape_qcd_p_3.SetBinContent(bin,(1+0.01* sqrt((hZZ_f_3.GetBinCenter(bin)-20)/13))*hZZ_f_3.GetBinContent(bin))
            hZZ_f_shape_qcd_m_0.SetBinContent(bin,(1-0.01* sqrt((hZZ_f_0.GetBinCenter(bin)-20)/13))*hZZ_f_0.GetBinContent(bin))
            hZZ_f_shape_qcd_m_1.SetBinContent(bin,(1-0.01* sqrt((hZZ_f_1.GetBinCenter(bin)-20)/13))*hZZ_f_1.GetBinContent(bin))
            hZZ_f_shape_qcd_m_2.SetBinContent(bin,(1-0.01* sqrt((hZZ_f_2.GetBinCenter(bin)-20)/13))*hZZ_f_2.GetBinContent(bin))
            hZZ_f_shape_qcd_m_3.SetBinContent(bin,(1-0.01* sqrt((hZZ_f_3.GetBinCenter(bin)-20)/13))*hZZ_f_3.GetBinContent(bin))
        else:
            hZZ_f_shape_qcd_p_0.SetBinContent(bin,hZZ_f_0.GetBinContent(bin))
            hZZ_f_shape_qcd_p_1.SetBinContent(bin,hZZ_f_1.GetBinContent(bin))
            hZZ_f_shape_qcd_p_2.SetBinContent(bin,hZZ_f_2.GetBinContent(bin))
            hZZ_f_shape_qcd_p_3.SetBinContent(bin,hZZ_f_3.GetBinContent(bin))
            hZZ_f_shape_qcd_m_0.SetBinContent(bin,hZZ_f_0.GetBinContent(bin))
            hZZ_f_shape_qcd_m_1.SetBinContent(bin,hZZ_f_1.GetBinContent(bin))
            hZZ_f_shape_qcd_m_2.SetBinContent(bin,hZZ_f_2.GetBinContent(bin))
            hZZ_f_shape_qcd_m_3.SetBinContent(bin,hZZ_f_3.GetBinContent(bin))

    #
    integral=hZZ_f_shape_qcd_p_0.Integral()
    print "ZZ shape_qcd_0 up integral ",integral," vs ", hZZ_f_0.Integral(), " ratio " , hZZ_f_shape_qcd_p_0.Integral()/hZZ_f_0.Integral()
    hZZ_f_shape_qcd_p_0.Scale(hZZ_f_0.Integral()/integral)
    print "scale integral", hZZ_f_shape_qcd_p_0.Integral()
    #
    integral=hZZ_f_shape_qcd_p_1.Integral()
    print "ZZ shape_qcd_1 up integral ",integral," vs ", hZZ_f_1.Integral(), " ratio " , hZZ_f_shape_qcd_p_1.Integral()/hZZ_f_1.Integral()
    hZZ_f_shape_qcd_p_1.Scale(hZZ_f_1.Integral()/integral)
    print "scale integral", hZZ_f_shape_qcd_p_1.Integral()
    #
    integral=hZZ_f_shape_qcd_p_2.Integral()
    print "ZZ shape_qcd_2 up integral ",integral," vs ", hZZ_f_2.Integral(), " ratio " , hZZ_f_shape_qcd_p_2.Integral()/hZZ_f_2.Integral()
    hZZ_f_shape_qcd_p_2.Scale(hZZ_f_2.Integral()/integral)
    print "scale integral", hZZ_f_shape_qcd_p_2.Integral()
    #
    integral=hZZ_f_shape_qcd_p_3.Integral()
    print "ZZ shape_qcd_3 up integral ",integral," vs ", hZZ_f_3.Integral(), " ratio " , hZZ_f_shape_qcd_p_3.Integral()/hZZ_f_3.Integral()
    hZZ_f_shape_qcd_p_3.Scale(hZZ_f_3.Integral()/integral)
    print "scale integral", hZZ_f_shape_qcd_p_3.Integral()
    ################minus################
    integral=hZZ_f_shape_qcd_m_0.Integral()
    print "ZZ shape_qcd_0 minus integral ",integral," vs ", hZZ_f_0.Integral(), " ratio " , hZZ_f_shape_qcd_m_0.Integral()/hZZ_f_0.Integral()
    hZZ_f_shape_qcd_m_0.Scale(hZZ_f_0.Integral()/integral)
    print "scale integral", hZZ_f_shape_qcd_m_0.Integral()
    #
    integral=hZZ_f_shape_qcd_m_1.Integral()
    print "ZZ shape_qcd_1 minus integral ",integral," vs ", hZZ_f_1.Integral(), " ratio " , hZZ_f_shape_qcd_m_1.Integral()/hZZ_f_1.Integral()
    hZZ_f_shape_qcd_m_1.Scale(hZZ_f_1.Integral()/integral)
    print "scale integral", hZZ_f_shape_qcd_m_1.Integral()
    #
    integral=hZZ_f_shape_qcd_m_2.Integral()
    print "ZZ shape_qcd_2 minus integral ",integral," vs ", hZZ_f_2.Integral(), " ratio " , hZZ_f_shape_qcd_m_2.Integral()/hZZ_f_2.Integral()
    hZZ_f_shape_qcd_m_2.Scale(hZZ_f_2.Integral()/integral)
    print "scale integral", hZZ_f_shape_qcd_m_2.Integral()    
    #
    integral=hZZ_f_shape_qcd_m_3.Integral()
    print "ZZ shape_qcd_3 minus integral ",integral," vs ", hZZ_f_3.Integral(), " ratio " , hZZ_f_shape_qcd_m_3.Integral()/hZZ_f_3.Integral()
    hZZ_f_shape_qcd_m_3.Scale(hZZ_f_3.Integral()/integral)
    print "scale integral", hZZ_f_shape_qcd_m_3.Integral()

hZZ_f_shape_qcd_p_0.Write()
hZZ_f_shape_qcd_p_1.Write()
hZZ_f_shape_qcd_p_2.Write()
hZZ_f_shape_qcd_p_3.Write()
hZZ_f_shape_qcd_m_0.Write()
hZZ_f_shape_qcd_m_1.Write()
hZZ_f_shape_qcd_m_2.Write()
hZZ_f_shape_qcd_m_3.Write()

raw_input("Press ENTER to exit")
###############C.A##############################################

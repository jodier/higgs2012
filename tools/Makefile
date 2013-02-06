#############################################################################

DIR=$(shell pwd)

#############################################################################

CINT          = rootcint
ROOTCONFIG    = root-config

#############################################################################

ROOTLIBS      = $(shell $(ROOTCONFIG) --libs)
ROOTGLIBS     = $(shell $(ROOTCONFIG) --glibs)
ROOTCFLAGS    = $(shell $(ROOTCONFIG) --cflags)
ROOTLDFLAGS   = $(shell $(ROOTCONFIG) --ldflags)

#############################################################################

ATLASFLAGS    =\
-I PATCore-00-00-09 \
-I HiggsZZ4lUtils-00-01-33 \
-I PileupReweighting-00-02-09 \
-I TrigMuonEfficiency-00-02-32 \
-I egammaAnalysisUtils-00-04-20 \
-I MuonIsolationCorrection-00-08 \
-I MuonMomentumCorrections-00-08-05 \
-I MuonEfficiencyCorrections-02-01-12\
-I ElectronEfficiencyCorrection-00-00-09

CXX           =g++
CXXFLAGS      =-g -O3 -fPIC -ansi -Wall -DROOTCORE $(ROOTCFLAGS) $(ATLASFLAGS) -Wunused-variable

LD            =g++
LDFLAGS       =-g $(ROOTLDFLAGS) -L.

LIBS          = $(ROOTLIBS) -lTreePlayer
GLIBS         = $(ROOTGLIBS) -lTreePlayer

#############################################################################

OBJS1         =\
PATCore-00-00-09/Root/TResult.o

OBJS2         =\
HiggsZZ4lUtils-00-01-33/Root/BkgCrossSection.o \
HiggsZZ4lUtils-00-01-33/Root/ElectronMCClassification.o \
HiggsZZ4lUtils-00-01-33/Root/ElectronRecoClassification.o \
HiggsZZ4lUtils-00-01-33/Root/GetQuadVertexIndex.o \
HiggsZZ4lUtils-00-01-33/Root/HiggsCrossSection.o \
HiggsZZ4lUtils-00-01-33/Root/McOverlapRemoval.o \
HiggsZZ4lUtils-00-01-33/Root/MzzWeightFromMCFM.o \
HiggsZZ4lUtils-00-01-33/Root/ElectronLikelihoodToolHSG2Helper.o

OBJS3         =\
PileupReweighting-00-02-09/Root/TPileupReweighting.o

OBJS4         =\
TrigMuonEfficiency-00-02-32/Root/ElectronTriggerMatching.o \
TrigMuonEfficiency-00-02-32/Root/HSG3TrigLeptonSFTool.o \
TrigMuonEfficiency-00-02-32/Root/LeptonTriggerMatching.o \
TrigMuonEfficiency-00-02-32/Root/LeptonTriggerSF.o \
TrigMuonEfficiency-00-02-32/Root/ElectronHypothesis.o \
TrigMuonEfficiency-00-02-32/Root/MuonHypothesis.o \
TrigMuonEfficiency-00-02-32/Root/MuonTriggerMatching.o

OBJS5         =\
egammaAnalysisUtils-00-04-20/Root/CaloIsoCorrection.o \
egammaAnalysisUtils-00-04-20/Root/checkOQ.o \
egammaAnalysisUtils-00-04-20/Root/ConvertedPhotonScaleTool.o \
egammaAnalysisUtils-00-04-20/Root/egammaSFclass.o \
egammaAnalysisUtils-00-04-20/Root/egammaTriggerMatching.o \
egammaAnalysisUtils-00-04-20/Root/EisoTool.o \
egammaAnalysisUtils-00-04-20/Root/ElectronEfficiencySFTool.o \
egammaAnalysisUtils-00-04-20/Root/ElectronLikelihoodTool.o \
egammaAnalysisUtils-00-04-20/Root/EnergyRescaler.o \
egammaAnalysisUtils-00-04-20/Root/EnergyRescalerUpgrade.o \
egammaAnalysisUtils-00-04-20/Root/FsrPhotons.o \
egammaAnalysisUtils-00-04-20/Root/H4l2011Defs.o \
egammaAnalysisUtils-00-04-20/Root/MultiLeptonMenu.o \
egammaAnalysisUtils-00-04-20/Root/ProbeQualityCuts.o \
egammaAnalysisUtils-00-04-20/Root/VertexPositionReweightingTool.o

OBJS6         =\
MuonMomentumCorrections-00-08-05/Root/SmearingClass.o

OBJS7         =\
MuonEfficiencyCorrections-02-01-12/Root/AnalysisMuonConfigurableScaleFactors.o \
MuonEfficiencyCorrections-02-01-12/Root/AnalysisMuonEfficiencyScaleFactors.o \
MuonEfficiencyCorrections-02-01-12/Root/EtaPhiBinning.o

#############################################################################

all: $(OBJS1) $(OBJS2) $(OBJS3) $(OBJS4) $(OBJS5) $(OBJS6) $(OBJS7)

	gcc -O2 -o hash hash.c

	$(AR) -rcs libPATCore.a $(OBJS1)
	$(AR) -rcs libHiggsZZ4lUtils.a $(OBJS2)
	$(AR) -rcs libPileupReweighting.a $(OBJS3)
	$(AR) -rcs libTrigMuonEfficiency.a $(OBJS4)
	$(AR) -rcs libegammaAnalysisUtils.a $(OBJS5)
	$(AR) -rcs libMuonMomentumCorrections.a $(OBJS6)
	$(AR) -rcs libMuonEfficiencyCorrections.a $(OBJS7)

#############################################################################

clean:
	rm -fr $(OBJS1) $(OBJS2) $(OBJS3) $(OBJS4) $(OBJS5) $(OBJS6) $(OBJS7) libPATCore.a libHiggsZZ4lUtils.a libPileupReweighting.a libTrigMuonEfficiency.a libegammaAnalysisUtils.a libMuonMomentumCorrections.a libMuonEfficiencyCorrections.a hash

#############################################################################

%.o: %.C
	@printf "Building $@\n"
	@$(CXX) $(CXXFLAGS) -c -o $@ $<
	@printf "[ \033[32mOk.\033[0m ]\n"

%.o: %.cc
	@printf "Building $@\n"
	@$(CXX) $(CXXFLAGS) -c -o $@ $<
	@printf "[ \033[32mOk.\033[0m ]\n"

%.o: %.cxx
	@printf "Building $@\n"
	@$(CXX) $(CXXFLAGS) -c -o $@ $<
	@printf "[ \033[32mOk.\033[0m ]\n"

#############################################################################


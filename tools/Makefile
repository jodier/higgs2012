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
-I ggFReweighting-00-00-08 \
-I HiggsZZ4lUtils-00-01-10 \
-I PileupReweighting-00-02-05 \
-I TrigMuonEfficiency-00-02-05 \
-I egammaAnalysisUtils-00-03-27 \
-I MuonIsolationCorrection-00-08 \
-I MuonMomentumCorrections-00-06-08 \
-I MuonEfficiencyCorrections-02-01-01

CXX           =g++
CXXFLAGS      =-g -O3 -fPIC -ansi -Wall -DROOTCORE $(ROOTCFLAGS) $(ATLASFLAGS) -Wunused-variable

LD            =g++
LDFLAGS       =-g $(ROOTLDFLAGS) -L.

LIBS          = $(ROOTLIBS) -lTreePlayer
GLIBS         = $(ROOTGLIBS) -lTreePlayer

#############################################################################

OBJS1         =\
ggFReweighting-00-00-08/ggFReweighting.o

OBJS2         =\
HiggsZZ4lUtils-00-01-10/Root/BkgCrossSection.o \
HiggsZZ4lUtils-00-01-10/Root/ElectronMCClassification.o \
HiggsZZ4lUtils-00-01-10/Root/ElectronRecoClassification.o \
HiggsZZ4lUtils-00-01-10/Root/GetQuadVertexIndex.o \
HiggsZZ4lUtils-00-01-10/Root/HiggsCrossSection.o \
HiggsZZ4lUtils-00-01-10/Root/IsEMPlusPlusH4lDefs.o \
HiggsZZ4lUtils-00-01-10/Root/MzzWeightFromMCFM.o

OBJS3         =\
PileupReweighting-00-02-05/Root/TPileupReweighting.o

OBJS4         =\
TrigMuonEfficiency-00-02-05/Root/ElectronTriggerMatching.o \
TrigMuonEfficiency-00-02-05/Root/HSG3TrigLeptonSFTool.o \
TrigMuonEfficiency-00-02-05/Root/LeptonTriggerSF.o \
TrigMuonEfficiency-00-02-05/Root/MuonHypothesis.o \
TrigMuonEfficiency-00-02-05/Root/MuonTriggerMatching.o

OBJS5         =\
egammaAnalysisUtils-00-03-27/Root/CaloIsoCorrection.o \
egammaAnalysisUtils-00-03-27/Root/checkOQ.o \
egammaAnalysisUtils-00-03-27/Root/ConvertedPhotonScaleTool.o \
egammaAnalysisUtils-00-03-27/Root/egammaSFclass.o \
egammaAnalysisUtils-00-03-27/Root/egammaTriggerMatching.o \
egammaAnalysisUtils-00-03-27/Root/EisoTool.o \
egammaAnalysisUtils-00-03-27/Root/ElectronEfficiencySFTool.o \
egammaAnalysisUtils-00-03-27/Root/ElectronLikelihoodTool.o \
egammaAnalysisUtils-00-03-27/Root/EnergyRescaler.o \
egammaAnalysisUtils-00-03-27/Root/EnergyRescalerUpgrade.o \
egammaAnalysisUtils-00-03-27/Root/FsrPhotons.o \
egammaAnalysisUtils-00-03-27/Root/IsEMPlusPlusDefs.o \
egammaAnalysisUtils-00-03-27/Root/MultiLeptonDefs.o \
egammaAnalysisUtils-00-03-27/Root/ProbeQualityCuts.o \
egammaAnalysisUtils-00-03-27/Root/VertexPositionReweightingTool.o

OBJS6         =\
MuonIsolationCorrection-00-08/Root/CorrectCaloIso.o

OBJS7         =\
MuonMomentumCorrections-00-06-08/Root/SmearingClass.o

OBJS8         =\
MuonEfficiencyCorrections-02-01-01/Root/AnalysisMuonConfigurableScaleFactors.o \
MuonEfficiencyCorrections-02-01-01/Root/AnalysisMuonEfficiencyScaleFactors.o \
MuonEfficiencyCorrections-02-01-01/Root/EtaPhiBinning.o

#############################################################################

all: $(OBJS1) $(OBJS2) $(OBJS3) $(OBJS4) $(OBJS5) $(OBJS6) $(OBJS7) $(OBJS8)

	gcc -O2 -o hash hash.c

	$(AR) -rcs libggFReweighting.a $(OBJS1)
	$(AR) -rcs libHiggsZZ4lUtils.a $(OBJS2)
	$(AR) -rcs libPileupReweighting.a $(OBJS3)
	$(AR) -rcs libTrigMuonEfficiency.a $(OBJS4)
	$(AR) -rcs libegammaAnalysisUtils.a $(OBJS5)
	$(AR) -rcs libMuonIsolationCorrection.a $(OBJS6)
	$(AR) -rcs libMuonMomentumCorrections.a $(OBJS7)
	$(AR) -rcs libMuonEfficiencyCorrections.a $(OBJS8)

#############################################################################

clean:
	rm -fr $(OBJS1) $(OBJS2) $(OBJS3) $(OBJS4) $(OBJS5) $(OBJS6) $(OBJS7) $(OBJS8) libggFReweighting.a libHiggsZZ4lUtils.a libPileupReweighting.a libTrigMuonEfficiency.a libegammaAnalysisUtils.a libMuonIsolationCorrection.a libMuonMomentumCorrections.a libMuonEfficiencyCorrections.a hash

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


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

ATLASFLAGS = -DSTANDALONE \
-I tools/PATCore-00-00-09 \
-I tools/HiggsZZ4lUtils-00-01-37 \
-I tools/PileupReweighting-00-02-09 \
-I tools/TrigMuonEfficiency-00-02-32 \
-I tools/egammaAnalysisUtils-00-04-20 \
-I tools/MuonMomentumCorrections-00-08-05 \
-I tools/MuonEfficiencyCorrections-02-01-12 \
-I tools/ElectronEfficiencyCorrection-00-00-09

ATLASLIBS = -L./tools \
-lPATCore \
-lHiggsZZ4lUtils \
-lPileupReweighting \
-lTrigMuonEfficiency \
-legammaAnalysisUtils \
-lMuonMomentumCorrections \
-lMuonEfficiencyCorrections \
-lElectronEfficiencyCorrection
#############################################################################

CXX           =g++
CXXFLAGS      =-std=c++98 -g -O3 -fPIC -ansi -Wall $(ROOTCFLAGS) $(ATLASFLAGS)

LD            =g++
LDFLAGS       =-g $(ROOTLDFLAGS) -L.

LIBS          = $(ROOTLIBS) -lTreePlayer
GLIBS         = $(ROOTGLIBS) -lTreePlayer

#############################################################################

OBJS1         = core/main.o core/core.o core/config.o core/loader.o core/utils.o core/selection/isEMOk.o core/selection/etcone.o core/selection/selection.o core/selection/triggers.o

OBJS2         = analysis/l_analysis/main.o

#############################################################################

all: core $(OBJS2) $(OBJS2)
#	@cd $(DIR)/tools && make all && cd $(DIR)

	$(LD) $(LDFLAGS) -o l_analysis $(OBJS2) -lcore $(ATLASLIBS) $(LIBS)

#############################################################################

ALL: core $(OBJS2) $(OBJS2)
	@cd $(DIR)/tools && make all && cd $(DIR)

	$(LD) $(LDFLAGS) -o l_analysis $(OBJS2) -lcore $(ATLASLIBS) $(LIBS)

#############################################################################

clean:
#	@cd $(DIR)/tools && make clean && cd $(DIR)

	rm -fr $(OBJS1) $(OBJS2) libcore.a l_analysis

#############################################################################

CLEAN:
	@cd $(DIR)/tools && make clean && cd $(DIR)

	rm -fr $(OBJS1) $(OBJS2) tools/*.a l_analysis

#############################################################################

core: $(OBJS1)
	ar -rcs libcore.a $(OBJS1) && ranlib libcore.a

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


OBJ=../Root/AnalysisMuonEfficiencyScaleFactors.o ../Root/EtaPhiBinning.o ../Root/AnalysisMuonConfigurableScaleFactors.o

CXX=g++

CXXFLAGS=-g -Wall

INCLUDEFLAGS=-I../

ROOTCFLAGS = $(shell root-config --cflags)

.SUFFIXES:	.cxx .h

libMuonEfficiencyCorrections.a: $(OBJ)
	ar -rs libMuonEfficiencyCorrections.a ./*o

.cxx.o:
	$(CXX) $(CXXFLAGS) $(ROOTCFLAGS) $(INCLUDEFLAGS) -c $<

clean:
	rm ./*.o; rm *.a

# DO NOT DELETE

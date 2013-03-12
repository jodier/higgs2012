OBJ=../Root/SmearingClass.o ../Root/MuonResolutionAndMomentumScaleFactors.o

CXX=g++

CXXFLAGS=-g -Wall

INCLUDEFLAGS=-I../

ROOTCFLAGS = $(shell root-config --cflags)
	
.SUFFIXES:      .cxx .h
	
libMuonMomentumCorrections.a: $(OBJ)
	ar -rs libMuonMomentumCorrections.a ./*o

.cxx.o:
	$(CXX) $(CXXFLAGS) $(ROOTCFLAGS) $(INCLUDEFLAGS) -c $<

clean:
	rm ./*.o; rm *.a

# DO NOT DELETE
SmearingClass.o: ../MuonMomentumCorrections/SmearingClass.h
MuonResolutionAndMomentumScaleFactors.o: ../MuonMomentumCorrections/MuonResolutionAndMomentumScaleFactors.h

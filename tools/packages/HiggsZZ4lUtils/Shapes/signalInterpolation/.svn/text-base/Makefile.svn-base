ROOTCFLAGS    = $(shell root-config --cflags)
ROOTLIBS      = $(shell root-config --glibs) -lTreePlayer -lMinuit -lMathMore -lXMLParser -lXMLIO -lCintex 

INCDIR = 
CXX           = g++
CXXFLAGS      =-I$(ROOTSYS)/include -O -Wall -fPIC
LD            = g++
LDFLAGS       = -g -m64
SOFLAGS       = -shared

CXXFLAGS     += $(ROOTCFLAGS)
LIBS          = $(ROOTLIBS)

# suffix rule
.cc.o:
	$(CXX) -c $(CXXFLAGS) $(GDBFLAGS) $<

# clean
clean:
	rm -f *~ *.o *.o~ core

interpolate : interpolationRoutine2.C 
	g++ -g -o interpolate  $(CXXFLAGS) $(LIBS) $(INCDIR) interpolationRoutine2.C 

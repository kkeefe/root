### C++ compiler
CXX           = g++
CXXFLAGS      = -O2 -Wall -fPIC -Wno-deprecated -g

### Library
ROOTCFLAGS := $(shell root-config --cflags)
ROOTLIBS   := $(shell root-config --libs)

CXXFLAGS   += $(ROOTCFLAGS)
LIBS        = $(ROOTLIBS) $(SYSLIBS)

### Targets
TARGS = createTreeData NTuples-improve NTuples-improveCutted triple_fit.C

all: $(TARGS)

### Compilation
%: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(LIBS)

.PHONY: rmproper

rmproper:
	rm -vf $(TARGS)

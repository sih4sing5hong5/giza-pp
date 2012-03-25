.SUFFIXES: .out .o .c .e .r .f .y .l .s .p .cpp .alpha2o .pentiumo .sgio .alphao

INSTALLDIR ?= /usr/local/bin/

CXX ?= g++

#CFLAGS_OPT = $(CFLAGS) -O3 -DNDEBUG -DWORDINDEX_WITH_4_BYTE -ffast-math
CFLAGS_OPT = -O3 -DNDEBUG -DWORDINDEX_WITH_4_BYTE -DBINARY_SEARCH_FOR_TTABLE
CFLAGS_PRF = -O2 -pg -DNDEBUG -DWORDINDEX_WITH_4_BYTE
CFLAGS_DBG = -g -DDEBUG -DWORDINDEX_WITH_4_BYTE
CFLAGS_NRM = -DWORDINDEX_WITH_4_BYTE
CFLAGS_VDBG = -g -DDEBUG -DWORDINDEX_WITH_4_BYTE -DVDEBUG

# These are good warnings to turn on by default
AM_CXXFLAGS = \
	-Wall \
	-Wcast-align \
	-Wcast-qual \
	-Wconversion \
	-Wextra \
	-Wfloat-equal \
	-Woverloaded-virtual \
	-Wparentheses \
	-Wpointer-arith \
	-Wswitch-enum \
	-Wwrite-strings

CFLAGS += $(CFLAGS_OPT) -Wall -Wno-parentheses $(AM_CXXFLAGS) -I.

TYPE =

ifeq ($(shell uname), Darwin)
	LDFLAGS =
else
	LDFLAGS = -static
endif

OBJ_DIR_PRF = profile/
OBJ_DIR_OPT = optimized/
OBJ_DIR_DBG = debug/
OBJ_DIR_VDBG = vdebug/
OBJ_DIR_NRM = norm/
OBJ_OPT2 = ${SRC2:%.cpp=$(OBJ_DIR_OPT)%.o}
OBJ_OPT = ${SRC:%.cpp=$(OBJ_DIR_OPT)%.o}
OBJ_DBG = ${SRC:%.cpp=$(OBJ_DIR_DBG)%.o}
OBJ_VDBG = ${SRC:%.cpp=$(OBJ_DIR_VDBG)%.o}
OBJ_NRM = ${SRC:%.cpp=$(OBJ_DIR_NRM)%.o}
OBJ_PRF = ${SRC:%.cpp=$(OBJ_DIR_PRF)%.o}
OBJ_DIR =
DATE = `date +%d-%m-%Y`

LIBOBJECTS = \
  Parameter.o \
	myassert.o \
	Perplexity.o \
	model1.o \
	model2.o \
	model3.o \
	sentence_handler.o \
	TTables.o \
	atables.o \
	align_tables.o \
	giza_main.o \
	NTables.o \
	model2to3.o \
	collCounts.o \
	alignment.o \
	vocab.o \
	MoveSwapMatrix.o \
	transpair_model3.o \
	transpair_model5.o \
	transpair_model4.o \
	utility.o \
	parse.o \
	reports.o \
	model3_viterbi.o \
	model3_viterbi_with_tricks.o \
	Dictionary.o \
	model345-peg.o \
	hmm.o \
	HMMTables.o \
	ForwardBackward.o

PROGRAMS = GIZA++ snt2plain.out plain2snt.out snt2cooc.out

opt: $(PROGRAMS)

GIZA++: $(LIBOBJECTS)
	$(CXX) $(CFLAGS_OPT) $(LIBOBJECTS) $(LDFLAGS) -o $@

prf: GIZA++.prf

GIZA++.prf: $(OBJ_DIR_PRF) $(OBJ_PRF)
	$(CXX) $(CFLAGS_PRF) $(OBJ_PRF) -o GIZA++.prf $(LDFLAGS)

dbg: GIZA++.dbg

GIZA++.dbg: $(OBJ_DIR_DBG) $(OBJ_DBG)
	$(CXX) $(CFLAGS_DBG) $(OBJ_DBG) -o GIZA++.dbg $(LDFLAGS)

vdbg: GIZA++.vdbg

GIZA++.vdbg: $(OBJ_DIR_VDBG) $(OBJ_VDBG)
	$(CXX) $(CFLAGS_VDBG) $(OBJ_VDBG) -o GIZA++.vdbg $(LDFLAGS)

nrm: GIZA++.nrm

GIZA++.nrm: $(OBJ_DIR_NRM) $(OBJ_NRM)
	$(CXX) $(CFLAGS_NRM) $(OBJ_NRM) -o GIZA++.nrm $(LDFLAGS)

all: opt

$(OBJ_DIR_PRF): $(OBJ_DIR)
	-mkdir $(OBJ_DIR_PRF)

$(OBJ_DIR_OPT): $(OBJ_DIR)
	-mkdir $(OBJ_DIR_OPT)

$(OBJ_DIR_DBG): $(OBJ_DIR)
	-mkdir $(OBJ_DIR_DBG)

$(OBJ_DIR_VDBG): $(OBJ_DIR)
	-mkdir $(OBJ_DIR_VDBG)

$(OBJ_DIR_NRM): $(OBJ_DIR)
	-mkdir $(OBJ_DIR_NRM)

$(OBJ_DIR):
	-mkdir $(OBJ_DIR)

$(OBJ_DIR_DBG)%.o: %.cpp
	$(CXX)  $(CFLAGS_DBG)  -c $< -o $@

$(OBJ_DIR_VDBG)%.o: %.cpp
	$(CXX)  $(CFLAGS_VDBG)  -c $< -o $@

$(OBJ_DIR_NRM)%.o: %.cpp
	$(CXX)  $(CFLAGS_NRM)  -c $< -o $@

$(OBJ_DIR_PRF)%.o: %.cpp
	$(CXX)  $(CFLAGS_PRF) -c $< -o $@

$(OBJ_DIR_OPT)%.o: %.cpp
	$(CXX)  $(CFLAGS_OPT)  -c $< -o $@

.cpp.o:
	$(CXX) $(CFLAGS) -c $< -o $@

iinstall: opt prf dbg
	-mkdir $(INSTALLDIR)/$(ARCH)
	-cp GIZA++ $(INSTALLDIR)/GIZA++
	-cp GIZA++.prf $(INSTALLDIR)/GIZA++.prf
	-cp GIZA++.dbg $(INSTALLDIR)/GIZA++.dbg

clean:
	-rm -f $(PROGRAMS) *.o $(OBJ_DIR_NRM)/*.o $(OBJ_DIR_DBG)/*.o $(OBJ_DIR_VDBG)/*.o $(OBJ_DIR_PRF)/*.o $(OBJ_DIR_OPT)/*.o
	-rm -rf $(OBJ_DIR_NRM) $(OBJ_DIR_DBG) $(OBJ_DIR_VDBG) $(OBJ_DIR_PRF) $(OBJ_DIR_OPT)
	-rm -fr *.dSYM

backup: clean
	tar cf - . | gzip -9 > ../GIZA++src.tar.gz

snt2plain.out: snt2plain.cpp
	$(CXX) $(LDFLAGS) -O3 -W -Wall snt2plain.cpp -o snt2plain.out

plain2snt.out: plain2snt.cpp
	$(CXX) $(LDFLAGS) -O3 -W -Wall plain2snt.cpp -o plain2snt.out

snt2cooc.out: snt2cooc.cpp
	$(CXX) $(LDFLAGS) -O3 -W -Wall snt2cooc.cpp -o snt2cooc.out

TAGS:
	find . -name \*.h -print -o -name \*.cpp -print | etags -

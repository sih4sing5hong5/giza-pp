CXX ?= g++

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

CFLAGS = -Wall -W -DNDEBUG -O3 -Wno-deprecated $(AM_CXXFLAGS) -I.

LDFLAGS =

OBJS = \
	GDAOptimization.o \
	HCOptimization.o \
	Problem.o \
	IterOptimization.o \
	ProblemTest.o \
	RRTOptimization.o \
	MYOptimization.o \
	SAOptimization.o \
	TAOptimization.o \
	Optimization.o \
	KategProblemTest.o \
	KategProblemKBC.o \
	KategProblemWBC.o \
	KategProblem.o \
	StatVar.o \
	general.o \
	mkcls.o

PROGRAMS = mkcls

.cpp.o:
	$(CXX) $(CFLAGS) -c $< -o $@

mkcls: $(OBJS)
	$(CXX) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@

clean:
	-rm -f *.o $(PROGRAMS)

TAGS:
	find . -name \*.h -print -o -name \*.cpp -print | etags -

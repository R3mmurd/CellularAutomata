# Cellular automata library.
# Author: Alejandro Mujica (aledrums@gmail.com)

CXX = clang++

WARN = -Wall -Wextra -Wcast-align -Wno-sign-compare \
	-Wno-write-strings -Wno-parentheses 

FLAGS = -DDEBUG -D_GLIBCXX__PTHREADS -g -O0 -std=c++14 $(WARN)

DSG = ~/DeSiGNAR

INCLUDE = -I. -I $(DSG)/include

LIBS = 	-L $(DSG)/lib -lDesignar

all: test-slice test-neighborhood

test-slice: test-slice.C latticeslice.H
	$(CXX) $(FLAGS) $(INCLUDE) $@.C -o $@ $(LIBS)

test-neighborhood: test-neighborhood.C lattice.H boundarycondition.H neighborhood.H
	$(CXX) $(FLAGS) $(INCLUDE) $@.C -o $@ $(LIBS)

clean:
	$(RM) test-slice test-neighborhood *~ *.o

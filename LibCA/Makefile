# This file is part of LibCA.
# Copyright (C) 2015 by Alejandro J. Mujica

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

# Any user request of this software, write to 

# Alejandro Mujica

# aledrums@gmail.com

CXX = clang++

WARN = -Wall -Wextra -Wcast-align -Wno-sign-compare \
	-Wno-write-strings -Wno-parentheses 

FLAGS = -DDEBUG -D_GLIBCXX__PTHREADS -g -O0 -std=c++14 $(WARN)

DSG = ~/DeSIGNAR

INCLUDE = -I. -I $(DSG)/include

LIBS = 	-L $(DSG)/lib -lDesignar -lc -lm -lgsl -lgslcblas -lasprintf -lpthread

all: test-slice test-clock


test-clock: test-clock.C clock.H
	$(CXX) $(FLAGS) $(INCLUDE) $@.C -o $@ $(LIBS)

test-slice: test-slice.C latticeslice.H
	$(CXX) $(FLAGS) $(INCLUDE) $@.C -o $@ $(LIBS)

test-lattice: test-lattice.C lattice.H
	$(CXX) $(FLAGS) $(INCLUDE) $@.C -o $@ $(LIBS)

test-neighborhood: test-neighborhood.C lattice.H boundarycondition.H neighborhood.H
	$(CXX) $(FLAGS) $(INCLUDE) $@.C -o $@ $(LIBS)

test-automaton: test-automaton.C automaton.H lattice.H boundarycondition.H neighborhood.H
	$(CXX) $(FLAGS) $(INCLUDE) $@.C -o $@ $(LIBS)

clean:
	$(RM) test-slice test-lattice test-neighborhood test-automaton \
	test-clock *~ *.o

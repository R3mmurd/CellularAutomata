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

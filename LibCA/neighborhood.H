/*
  This file is part of LibCA.
  Copyright (C) 2015 by Alejandro J. Mujica

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

  Any user request of this software, write to 

  Alejandro Mujica

  aledrums@gmail.com
*/

# ifndef NEIGHBORHOOD_H
# define NEIGHBORHOOD_H

# include <boundarycondition.H>

template <typename CellT>
class Neighborhood
{
  virtual vector<CellT *> get_neighbors(Lattice<CellT> &,
                                        BoundaryCondition<CellT> *,
					const ArrayDim &) = 0;
};


template <typename CellT>
class OneDimNeighborhood : public Neighborhood<CellT>,
                           public Designar::Singleton<OneDimNeighborhood<CellT>>
{
  friend class Designar::Singleton<OneDimNeighborhood<CellT>>;
public:
  vector<CellT *> get_neighbors(Lattice<CellT> & lattice,
                                BoundaryCondition<CellT> * bcond,
				const ArrayDim & arr) override
  {
    vector<CellT *> ret;
    
    ret.push_back(bcond->get(lattice, arr, {-1}));
    ret.push_back(bcond->get(lattice, arr, {1}));
    
    return ret;
  }
};

template <typename CellT>
class VonNeumannNeighborhood :
        public Neighborhood<CellT>,
        public Designar::Singleton<VonNeumannNeighborhood<CellT>>
{
public:
  vector<CellT *> get_neighbors(Lattice<CellT> & lattice,
                                BoundaryCondition<CellT> * bcond,
				const ArrayDim & arr) override
  {
    vector<CellT *> ret;

    for (size_t i = 0; i < lattice.order(); ++i)
      {
        ArrayDelta delta(lattice.order());

	for (size_t i = 0; i < delta.size(); ++i)
	  delta[i] = 0;

	delta[i] = -1;
	ret.push_back(bcond->get(lattice, arr, delta));
	delta[i] = 1;
	ret.push_back(bcond->get(lattice, arr, delta));
      }

    return ret;
  }
};

template <typename CellT>
class MooreNeighborhood : public Neighborhood<CellT>,
                          public Designar::Singleton<MooreNeighborhood<CellT>>
{
public:
  vector<CellT *> get_neighbors(Lattice<CellT> & lattice,
                                BoundaryCondition<CellT> * bcond,
				const ArrayDim & arr) override
  {
    vector<CellT *> ret;

    ArrayDelta delta(lattice.order());

    for (size_t i = 0; i < delta.size(); ++i)
      delta[i] = -1;
    
    int l = 0, r = lattice.order();
    
    while (r > lattice.order() - 1)
      {
	bool zero = true;
	
	for (size_t i = 0; i < delta.size(); ++i)
	  zero = zero and delta[i] == 0;
	
	if (not zero)
	  ret.push_back(bcond->get(lattice, arr, delta));
	
	++delta[l];
	
	while (l < r and delta[l] > 1)
	  {
	    delta[l++] = -1;
	    if (l < delta.size())
	      ++delta[l];
	  }
	
	if (l == r)
	  --r;
	
	l = 0;
      }
    
    return ret;
  }
};

# endif // NEIGHBORHOOD_H

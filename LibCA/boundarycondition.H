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

# ifndef BOUNDARYCONDITION_H
# define BOUNDARYCONDITION_H

# include <lattice.H>
# include <singleton.H>

template <typename CellT>
class BoundaryCondition
{
public:
  virtual CellT * get(Lattice<CellT> &, const ArrayDim &,
		      const ArrayDelta &) = 0;
};

template <typename CellT>
class Periodic : public BoundaryCondition<CellT>,
		 public Singleton<Periodic<CellT>>
{
 public:
  CellT * get(Lattice<CellT> & lattice, const ArrayDim & pos,
	      const ArrayDelta & delta) override
  {
    if (pos.size() != lattice.order())
      throw logic_error("pos array does not match with order");
    
    ArrayDim idxs(lattice.order());

    for (size_t n = 0; n < lattice.order(); ++n)
      {
	const size_t & p = pos[n];
	const char   & d = delta[n];
	assert(-1 <= d and d <= 1);
	size_t & i = idxs[n];

	if (d < 0)
	  if (p == 0)
	    i = lattice.size(n) - 1;
	  else
	    i = p - 1;
	    
	else if (d > 0)
	  if (p == lattice.size(n) - 1)
	    i = 0;
	  else
	    i = p + 1;
	else
	  i = p;
      }

    return &lattice.get(idxs);
  }
};

template <typename CellT>
class Reflect : public BoundaryCondition<CellT>,
		public Singleton<Reflect<CellT>>
{
 public:
  CellT * get(Lattice<CellT> & lattice, const ArrayDim & pos,
	      const ArrayDelta & delta) override
  {
    if (pos.size() != lattice.order())
      throw logic_error("pos array does not match with order");
    
    ArrayDim idxs(lattice.order());

    for (size_t n = 0; n < lattice.order(); ++n)
      {
	const size_t & p = pos[n];
	const char   & d = delta[n];
	assert(-1 <= d and d <= 1);
	size_t & i = idxs[n];

	if (d < 0)
	  if (p == 0)
	    i = p + 1;
	  else
	    i = p - 1;
	    
	else if (d > 0)
	  if (p == lattice.size(n) - 1)
	    i = p - 1;
	  else
	    i = p + 1;
	else
	  i = p;
      }

    return &lattice.get(idxs);
  }
};

template <typename CellT>
class Fixed : public BoundaryCondition<CellT>
{
  CellT fixed_value;
  
public:
  Fixed(const CellT & fval = CellT())
    : fixed_value(fval)
  {
    // Empty
  }

  Fixed(const Fixed &) = delete;

  Fixed & operator = (const Fixed &) = delete;

  void set_fixed_value(const CellT & fval)
  {
    fixed_value = fval;
  }

  const CellT & get_fixed_value() const
  {
    return fixed_value;
  }
  
  CellT * get(Lattice<CellT> & lattice, const ArrayDim & pos,
	      const ArrayDelta & delta) override
  {
    if (pos.size() != lattice.order() or delta.size() != lattice.order())
      throw logic_error("pos or delta array does not match with order");
    
    ArrayDim idxs(lattice.order());

    for (size_t n = 0; n < lattice.order(); ++n)
      {
	const size_t & p = pos[n];
	const char   & d = delta[n];
	assert(-1 <= d and d <= 1);
	size_t & i = idxs[n];

	if (d < 0)
	  if (p == 0)
	    return &fixed_value;
	  else
	    i = p - 1;
	    
	else if (d > 0)
	  if (p == lattice.size(n) - 1)
	    return &fixed_value;
	  else
	    i = p + 1;
	else
	  i = p;
      }

    return &lattice.get(idxs);
  }
};

# endif // BOUNDARYCONDITION_H

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

# ifndef AUTOMATONDEFS_H
# define AUTOMATONDEFS_H

# include <neighborhood.H>

template <typename CellT>
class UpdateRule
{
public:
  virtual CellT operator () (const CellT &, const vector<CellT *> &) const = 0;
};

template <typename CellT>
class NoUpdateRule : public UpdateRule<CellT>
{
public:
  CellT operator () (const CellT &, const vector<CellT *> &) const override
  {
    // Empty
  }  
};

class TraverseAutomaton
{
public:
  template<class Automaton, class UpdateRule>
  void operator () (Automaton & automaton, const UpdateRule & rule) const
  {
    for (auto & cell : automaton)
      {
	auto subscripts = automaton.to_subscripts(cell);
	vector<typename Automaton::CellType *> neighbors =
	  automaton.get_neighbors(cell);
	automaton.set_next_value(subscripts, rule(cell, neighbors));
      }
    
    automaton.swap_lattices();
  }
};

# endif // AUTOMATONDEFS_H

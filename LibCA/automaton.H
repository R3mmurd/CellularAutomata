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

# ifndef AUTOMATON_H
# define AUTOMATON_H

# include <automatondefs.H>

template <typename CellT,
	  size_t N,
	  template <typename, size_t> class BoundaryConditionT,
	  template <typename, class, size_t> class NeighborhoodT,
	  class UpdateRuleT,
	  class UpdateBehaviorT = TraverseAutomaton>
class Automaton : public Lattice<CellT, N>
{
public:
  using CellType = CellT;
  using LatticeType = Lattice<CellType, N>;
  using BoundaryConditionType = BoundaryConditionT<CellType, N>;
  using NeighborhoodType = NeighborhoodT<CellType, BoundaryConditionType, N>;
  using UpdateRuleType = UpdateRuleT;
  using UpdateBehaviorType = UpdateBehaviorT;

  static constexpr size_t Order = LatticeType::Order;

private:
  LatticeType           next_lattice;
  BoundaryConditionType bcond;
  NeighborhoodType      neighborhood;
  UpdateRuleType        update_rule;
  UpdateBehaviorType    update_behavior;

public:

  template <typename ...Dim>
  Automaton(Dim... dim)
    : LatticeType(dim...), next_lattice(dim...), bcond(),
      neighborhood(*this), update_rule(), update_behavior()
  {
    // Empty
  }

  BoundaryConditionType & get_boundary_condition()
  {
    return bcond;
  }

  NeighborhoodType & get_neighborhood()
  {
    return neighborhood;
  }

  UpdateRuleType & get_update_rule()
  {
    return update_rule;
  }

  UpdateBehaviorType & get_update_behavior()
  {
    return update_behavior;
  }
  
  vector<CellType *> get_neighbors(const array<size_t, N> & arr)
  {
    return neighborhood(arr, bcond);
  }

  vector<CellType *> get_neighbors(CellType & cell)
  {
    return get_neighbors(LatticeType::to_subscripts(cell));
  }
 
  void swap_lattices()
  {
    swap((LatticeType &)*this, next_lattice);
  }

  void set_next_value(const array<size_t, N> & subscripts, const CellT & val)
  {
    next_lattice.get(subscripts) = val;
  }
  
  void update()
  {
    update_behavior(*this, update_rule);
  }
};

# endif // AUTOMATON_H

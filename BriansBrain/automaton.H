/*
  This file is part of Brian's Brain.
  Copyright (C) 2016 by Alejandro J. Mujica

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

# include <QPainter>

# include <neighborhood.H>

class Automaton
{
public:
  enum class Status
  {
    ON, DYING, OFF
  };

  static constexpr unsigned WIDTH = 240;
  static constexpr unsigned HEIGHT = 160;
  static constexpr unsigned SCALE = 5;

private:
  using NeighborhoodType = MooreNeighborhood<Status>;
  using BCondType = Periodic<Status>;

  Lattice<Status> lattice;
  Lattice<Status> tmp_lattice;

public:
  Automaton();

  void draw(QPainter &);

  void update();
};

# endif // AUTOMATON_H

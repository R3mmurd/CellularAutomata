/*
  This file is part of Elementary Cellular Automaton.
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
# include <QList>

# include <bitset.H>
# include <neighborhood.H>

class Automaton
{
  public:
  enum class Status
  {
    ON, OFF
  };

  static constexpr unsigned WIDTH = 260;
  static constexpr unsigned MAX_HEIGHT = 120;
  static constexpr unsigned SCALE = 5;
  static constexpr unsigned DELAY = 100;

private:
  using NeighborhoodType = OneDimNeighborhood<Status>;

  Designar::Byte rule;

  QList<Lattice<Status>> lattices;
  Fixed<Status> bcond;

public:
  Automaton();

  void reset();

  void set_rule(const Designar::Byte &);

  void update();

  void draw(QPainter &);
};

# endif // AUTOMATON_H

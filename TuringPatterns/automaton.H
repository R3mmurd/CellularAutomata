/*
  This file is part of Turing Patterns.
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

# include <tree.H>

# include <cell.H>
# include <neighborhood.H>

class QPainter;

class Automaton
{
public:
  using Channel = Cell::ChannelVel;

  using BagType = Designar::TreeSet<Channel>;

  static constexpr unsigned L = 100;
  static constexpr unsigned SCALE = 5;

private:
  mt19937 rng;

  Lattice<Cell> L_A_0;
  Lattice<Cell> L_A_1;
  Lattice<Cell> L_I_0;
  Lattice<Cell> L_I_1;

  double p_c;
  double p_d;
  unsigned m_a;
  unsigned m_i;

  BagType bag;

  void fill_bag();

  Channel take_from_bag();

  unsigned wrap_plus(unsigned, unsigned);

  unsigned wrap_subs(unsigned, unsigned);

public:
  Automaton();

  void update();

  void randomize();

  void draw(QPainter &);

  double get_p_c() const;

  void set_p_c(const double &);

  double get_p_d() const;

  void set_p_d(const double &);

  unsigned get_m_a() const;

  void set_m_a(unsigned);

  unsigned get_m_i() const;

  void set_m_i(unsigned);
};

# endif // AUTOMATON_H

/*
  This file is part of Earthquake 2D.
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

# ifndef EARTHQUAKEAUTOMATON_H
# define EARTHQUAKEAUTOMATON_H

# include <tpl_dynListStack.H>
# include <htlist.H>

# include <neighborhood.H>

# include <QPainter>

class QPainter;

class EarthquakeAutomaton
{
  static constexpr double DE = 0.0002;
  static constexpr double EC = 4.0;

public:
  static constexpr unsigned SCALE = 10;
  static constexpr unsigned WIDTH = 64;
  static constexpr unsigned HEIGHT = 64;

private:
  struct Release : public Slinknc
  {
    unsigned i;
    unsigned j;
  };

  Release release;

  DynListStack<Release *> rel_pool;

  Release * get_release();

  unsigned num_release;
  unsigned t;

  using NeighborhoodType = VonNeumannNeighborhood<double>;

  Fixed<double> bcond;

  Lattice<double> lattice;

public:
  EarthquakeAutomaton();

  ~EarthquakeAutomaton();

  void draw(QPainter &);

  void update();
};

# endif // EARTHQUAKEAUTOMATON_H

/*
  This file is part of Ising 2D.
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

# ifndef ISINGAUTOMATON2D_H
# define ISINGAUTOMATON2D_H

# include <random>
# include <sstream>

# include <neighborhood.H>

class QPainter;
  
class IsingAutomaton2D
{  
  mt19937 rng;

  static constexpr double J =  1.0;
  static constexpr double Kb = 1.0;

public:
  static constexpr unsigned WIDTH = 500;
  static constexpr unsigned HEIGHT = 500;
  static constexpr unsigned SCALE = 2;

private:
  using NeighborhoodType = VonNeumannNeighborhood<int8_t>;

  Fixed<int8_t> bcond;

  Lattice<int8_t> lattice;
  
  double compute_delta_H(const unsigned &, const unsigned &);

public:
  IsingAutomaton2D();

  void reinit();

  void step(const double &);

  int64_t get_magnetization();

  unsigned get_num_spins() const;

  void generate_gnuplot_dat(const string &);

  void generate_gnuplot_script(const string &, const string &, const string &);
  
  IsingAutomaton2D & operator = (const IsingAutomaton2D &) = delete;

  void draw(QPainter &);
};

# endif // ISINGAUTOMATON2_H

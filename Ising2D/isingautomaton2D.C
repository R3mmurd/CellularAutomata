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

# include <fstream>

# include <QPainter>

# include <isingautomaton2D.H>

double IsingAutomaton2D::compute_delta_H(const unsigned & i,
                                         const unsigned & j)
{
  const int8_t & s_k = lattice.at({i, j});

  auto neighbors = NeighborhoodType::get_instance().
      get_neighbors(lattice, &bcond, {i,j});
  
  int8_t s_i_sum = 0;
  
  for (int8_t * s_i : neighbors)
    s_i_sum += *s_i;

  return 2.0 * J * s_k * s_i_sum;
}

IsingAutomaton2D::IsingAutomaton2D()
  : rng(time(0) % mt19937::max()), lattice({HEIGHT, WIDTH})
{
  reinit();
}

void IsingAutomaton2D::reinit()
{
  for (auto & cell : lattice)
    {
      double r = generate_canonical<double, 64>(rng);

      if (r < 0.5)
        cell = 1;
      else
        cell = -1;
    }
}

void IsingAutomaton2D::step(const double & t)
{
  uniform_int_distribution<unsigned> unif_h(0, HEIGHT - 1);
  uniform_int_distribution<unsigned> unif_w(0, WIDTH - 1);

  unsigned i = unif_h(rng);
  unsigned j = unif_w(rng);

  double delta_H = compute_delta_H(i, j);

  if (delta_H < 0.0)
    {
      lattice.at({i, j}) *= -1;
      return;
    }

  double beta = 1.0 / (t * Kb);

  double r = generate_canonical<double, 64>(rng);

  if (r < exp(-1 * beta * delta_H))
    lattice.at({i, j}) *= -1;
}

int64_t IsingAutomaton2D::get_magnetization()
{
  int64_t ret_val = 0;
  
  for (auto cell : lattice)
    ret_val -= cell;

  return ret_val;
}

unsigned IsingAutomaton2D::get_num_spins() const
{
  return WIDTH * HEIGHT;
}

void IsingAutomaton2D::generate_gnuplot_dat(const string & file_name)
{
  ofstream file(file_name.c_str());

  if (not file.is_open())
    throw runtime_error("Cannot open file");
  
  for (unsigned i = 0; i < HEIGHT; ++i)
    for (unsigned j = 0; j < WIDTH; ++j)
      if (lattice.at({i, j}) > 0)
        file << i << ' ' << j << '\n';

  file.close();
}

void IsingAutomaton2D::generate_gnuplot_script(const string & file_name,
					       const string & data_file_name,
					       const string & png_file_name)
{
  ofstream file(file_name.c_str());

  if (not file.is_open())
    throw runtime_error("Cannot open file");

  file << "set term png\n"
       << "set output '" << png_file_name << "'\n"
       << "set xdata\n"
       << "set ydata\n"
       << "set xrange [ 0 : " << HEIGHT + 1 << " ]\n"
       << "set yrange [ 0 : " << WIDTH + 1 << " ]\n"
       << "plot '" << data_file_name << "'\n"
       << "quit";

  file.close();
}

void IsingAutomaton2D::draw(QPainter & painter)
{
  for (unsigned i = 0; i < HEIGHT; ++i)
    for (unsigned j = 0; j < WIDTH; ++j)
      if (lattice.at({i, j}) > 0)
        painter.fillRect(j * SCALE, i * SCALE, SCALE, SCALE, Qt::yellow);
      else
        painter.fillRect(j * SCALE, i * SCALE, SCALE, SCALE, Qt::black);
}

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

# include <stdexcept>
# include <QDebug>
# include <QPainter>
# include <QColor>
# include <automaton.H>


double Automaton::get_p_c() const
{
  return p_c;
}

void Automaton::set_p_c(const double & value)
{
  p_c = value;
}

double Automaton::get_p_d() const
{
  return p_d;
}

void Automaton::set_p_d(const double & value)
{
  p_d = value;
}

unsigned Automaton::get_m_a() const
{
  return m_a;
}

void Automaton::set_m_a(unsigned value)
{
  m_a = value;
}

unsigned Automaton::get_m_i() const
{
  return m_i;
}

void Automaton::set_m_i(unsigned value)
{
  m_i = value;
}
void Automaton::fill_bag()
{
  bag.empty();

  bag.insert(Cell::UP);
  bag.insert(Cell::DOWN);
  bag.insert(Cell::LEFT);
  bag.insert(Cell::RIGHT);
  bag.insert(Cell::REST);
}

Automaton::Channel Automaton::take_from_bag()
{
  uniform_int_distribution<size_t> unif(0, bag.size() - 1);

  unsigned r = unif(rng);

  Channel ret_val = bag.select(r);

  bag.remove(ret_val);

  return ret_val;
}

unsigned Automaton::wrap_plus(unsigned a, unsigned b)
{
  return (a + b) % L;
}

unsigned Automaton::wrap_subs(unsigned a, unsigned b){
  if (a >= b)
    return a - b;

  return L - (b - a);
}


Automaton::Automaton()
  : rng(time(0) % mt19937::max()), L_A_0({L,L}), L_A_1({L,L}),
    L_I_0({L,L}), L_I_1({L,L})
{
  fill_bag();
  randomize();
}

void Automaton::update()
{
  for (unsigned i = 0; i < L; ++i)
    for (unsigned j = 0; j < L; ++j)
      {
        unsigned num_a = L_A_0.at({i, j}).get_num_particles();
        unsigned num_i = L_I_0.at({i, j}).get_num_particles();

        unsigned new_num_a = num_a;
        unsigned new_num_i = num_i;

        if (num_a > num_i)
          {
            double p = generate_canonical<double, 64>(rng);

            if (p < p_c)
              new_num_a = Cell::NUM_CHANNELS;

            double q = generate_canonical<double, 64>(rng);

            if (q < p_c)
              new_num_i = Cell::NUM_CHANNELS;

          }
        else if (num_i > num_a)
          {
            double p = generate_canonical<double, 64>(rng);

            if (p < p_d)
              new_num_a = 0;

            double q = generate_canonical<double, 64>(rng);

            if (q < p_d)
              new_num_i = 0;
          }

        for (unsigned k = 0; k < new_num_a; ++k)
          {
            Channel c = take_from_bag();

            unsigned pos;

            switch (c)
              {
              case Cell::UP:
                pos = wrap_subs(i, m_a);
                L_A_1.at({pos, j}).set(c, 1);
                break;
              case Cell::DOWN:
                pos = wrap_plus(i, m_a);
                L_A_1.at({pos, j}).set(c, 1);
                break;
              case Cell::LEFT:
                pos = wrap_subs(j, m_a);
                L_A_1.at({i, pos}).set(c, 1);
                break;
              case Cell::RIGHT:
                pos = wrap_plus(j, m_a);
                L_A_1.at({i, pos}).set(c, 1);
                break;
              case Cell::REST:
                L_A_1.at({i, j}).set(c, 1);
                break;
              default:
                throw logic_error("Invalid channel");
              }
          }

        fill_bag();

        for (unsigned k = 0; k < new_num_i; ++k)
          {
            Channel c = take_from_bag();

            unsigned pos;

            switch (c)
              {
              case Cell::UP:
                pos = wrap_subs(i, m_i);
                L_I_1.at({pos, j}).set(c, 1);
                break;
              case Cell::DOWN:
                pos = wrap_plus(i, m_i);
                L_I_1.at({pos, j}).set(c, 1);
                break;
              case Cell::LEFT:
                pos = wrap_subs(j, m_i);
                L_I_1.at({i, pos}).set(c, 1);
                break;
              case Cell::RIGHT:
                pos = wrap_plus(j, m_i);
                L_I_1.at({i, pos}).set(c, 1);
                break;
              case Cell::REST:
                L_I_1.at({i, j}).set(c, 1);
                break;
              default:
                throw logic_error("Invalid channel");
              }
          }
        L_A_0.at({i, j}).reset();
        L_I_0.at({i, j}).reset();

        fill_bag();
      }
  swap(L_A_0, L_A_1);
  swap(L_I_0, L_I_1);
}

void Automaton::randomize()
{
  for (unsigned i = 0; i < L; ++i)
    for (unsigned j = 0; j < L; ++j)
      {
        L_A_0.at({i, j}).randomize(rng);
        L_I_0.at({i, j}).randomize(rng);
      }
}

void Automaton::draw(QPainter & painter)
{
  for (unsigned i = 0; i < L; ++i)
    for (unsigned j = 0; j < L; ++j)
      {
        double prop = 1 -
            double(L_A_0.at({i, j}).get_num_particles()) /
            double(Cell::NUM_CHANNELS);

        int rgb = 255 * prop;

        QColor color(rgb, rgb, rgb);

        painter.fillRect(j * SCALE, i * SCALE, SCALE, SCALE, color);
      }
}

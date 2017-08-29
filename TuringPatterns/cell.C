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

# include <cell.H>

Cell::Cell()
{
  reset();
}

unsigned Cell::get_num_particles() const
{
  unsigned ret = 0;

  for (unsigned i = 0; i < NUM_CHANNELS; ++i)
    ret += channels[i];

  return ret;
}

const unsigned & Cell::get(const Cell::ChannelVel & p)
{
  return channels[p];
}

void Cell::set(const Cell::ChannelVel & p, const unsigned & v)
{
  channels[p] = v;
}

void Cell::reset()
{
  for (unsigned i = 0; i < NUM_CHANNELS; ++i)
    channels[i] = 0;
}

void Cell::randomize(std::mt19937 & rng)
{
  for (unsigned i = 0; i < NUM_CHANNELS; ++i)
    channels[i] = generate_random_bit(rng);
}


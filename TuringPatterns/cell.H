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

# ifndef CELL_H
# define CELL_H

# include <random_util.H>

class Cell
{
public:
  enum ChannelVel { UP, DOWN, LEFT, RIGHT, REST, NUM_CHANNELS };

private:
  unsigned channels[NUM_CHANNELS];

public:
  Cell();

  unsigned get_num_particles() const;

  const unsigned & get(const ChannelVel &);

  void set(const ChannelVel &, const unsigned &);

  void reset();

  void randomize(std::mt19937 &);
};

#endif // CELL_H

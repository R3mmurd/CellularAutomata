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

# define CLOCK_H

template <typename T>
class Clock
{
  /*  static_assert(is_numeric<T>::value,
		"template argument is not a numeric type");
  */
  T current_time;
  T total_time;

public:
  Clock(const T & t)
    : current_time(0), total_time(t)
  {
    // Empty
  }

  bool step(const T & t)
  {
    current_time += t;

    if (current_time >= total_time)
      {
	current_time = T(0);
	return true;
      }

    return false;
  }
};

class IntClock : public Clock<unsigned long>
{
  using Clock::Clock;
};

class RealClock : public Clock<float>
{
  using Clock::Clock;
};

# endif // CLOCK_H

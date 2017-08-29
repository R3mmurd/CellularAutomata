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

# include <cassert>
# include <cmath>

# include <iostream>

# include <clock.H>

using namespace std;

int main()
{
  IntClock ic1(1), ic2(2), ic3(3);
  unsigned long ic1_counter = 0, ic2_counter = 0, ic3_counter = 0;

  for (int i = 0; i < 100; ++i)
    {
      if (ic1.step(1))
	++ic1_counter;

      if (ic2.step(1))
	++ic2_counter;

      if (ic3.step(1))
	++ic3_counter;
    }

  assert(ic1_counter == 100);
  assert(ic2_counter == 50);
  assert(ic3_counter == 33);

  RealClock rc1(1.5), rc2(3.0), rc3(8.2);
  unsigned long rc1_counter = 0, rc2_counter = 0, rc3_counter = 0;
  
  for (float i = 0.0; i < 30.0; i += 0.1)
    {
      if (rc1.step(0.1))
	++rc1_counter;
      
      if (rc2.step(0.1))
	++rc2_counter;
      
      if (rc3.step(0.1))
	++rc3_counter;
    }

  assert(rc1_counter == 20);
  assert(rc2_counter == 9);
  assert(rc3_counter == 3);
  
  cout << "everything ok!\n";

  return 0;
}

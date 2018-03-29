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

# include <iostream>
# include <sstream>
# include <string>

# include <gsl/gsl_rng.h>

# include <lattice.H>

template<typename T>
string mat_to_str(size_t *& arr, T sz)
{
  stringstream sstr;

  sstr << "{ ";
  
  for (auto i = 0; i < sz; ++i)
    sstr << *arr++ << ' ';
  
  sstr << "}";
  
  return sstr.str();
}

template <typename T, typename... Tail>
string mat_to_str(size_t *& arr, T sz, Tail... tail)
{
  stringstream sstr;

  sstr << "{ ";

  size_t *& ptr = arr;

  for (auto i = 0; i < sz; ++i)
    sstr << mat_to_str(ptr, tail...) << ' ';

  sstr << "}";
  
  return sstr.str();
}

int main()
{
  gsl_rng * rng = gsl_rng_alloc(gsl_rng_mt19937);
  gsl_rng_set(rng, time(nullptr) % gsl_rng_max(rng));
  
  constexpr size_t D1 = 2;
  constexpr size_t D2 = 3;
  constexpr size_t D3 = 4;
  constexpr size_t D4 = 5;

  constexpr size_t Sample = 5;
  
  cout << "Testing 1-dimension LatticeSlice with length = " << D4 << endl;
  
  LatticeSlice ls1({D4});
  
  size_t arr1[ls1.size()];

  for (auto i = 0; i < ls1.size(); ++i)
    arr1[i] = i + 1;

  size_t * ptr = arr1;
  
  
  cout << "Array = ";

  cout << mat_to_str(ptr, D4) << endl << endl;

  cout << Sample << " random samples" << endl;

  for (auto s = 0; s < Sample; ++s)
    {
      size_t i = gsl_rng_uniform_int(rng, D4);
      size_t idx = ls1.to_linear_index({i});
      ArrayDim arr_pos = ls1.to_subscripts(idx);
      cout << "arr1[" << i << "] = " << arr1[idx] << " --- array pos = { "
	   << arr_pos[0] << " }" << endl;
    }

  cout << endl;
  
  cout << "Testing 2-dimensional LatticeSlice with size = "
       << D3 << " x " << D4 << endl;
  
  LatticeSlice ls2({D3, D4});

  size_t arr2[ls2.size()];

  for (auto i = 0; i < ls2.size(); ++i)
    arr2[i] = i + 1;


  ptr = arr2;
  
  cout << "Array =\n";

  cout << mat_to_str(ptr, D3, D4) << endl << endl;

  cout << Sample << " random samples" << endl;

  for (auto s = 0; s < Sample; ++s)
    {
      size_t i = gsl_rng_uniform_int(rng, D3);
      size_t j = gsl_rng_uniform_int(rng, D4);
      size_t idx = ls2.to_linear_index({i, j});
      ArrayDim arr_pos = ls2.to_subscripts(idx);
      cout << "arr2[" << i << "][" << j << "] = " << arr2[idx]
	   << " --- array pos = { " << arr_pos[0]
	   << ", " << arr_pos[1] << " }"<< endl;
    }

  cout << endl;

  cout << "Testing 3-dimensional LatticeSlice with size = "
       << D2 << " x " << D3 << " x "  << D4 << endl;
  
  LatticeSlice ls3({D2, D3, D4});

  size_t arr3[ls3.size()];

  for (auto i = 0; i < ls3.size(); ++i)
    arr3[i] = i + 1;

  ptr = arr3;

  cout << "Array =\n";

  cout << mat_to_str(ptr, D2, D3, D4) << endl << endl;

  cout << Sample << " random samples" << endl;

  for (auto s = 0; s < Sample; ++s)
    {
      size_t i = gsl_rng_uniform_int(rng, D2);
      size_t j = gsl_rng_uniform_int(rng, D3);
      size_t k = gsl_rng_uniform_int(rng, D4);
      size_t idx = ls3.to_linear_index({i, j, k});
      ArrayDim arr_pos = ls3.to_subscripts(idx);
      cout << "arr3[" << i << "][" << j << "][" << k << "] = "
	   << arr3[idx] << " --- array pos = { " << arr_pos[0]
	   << ", " << arr_pos[1] << ", " << arr_pos[2] << " }" << endl;
    }

  cout << endl;

  cout << "Testing 4-dimensional LatticeSlice with size = "
       << D1 << " x " << D2 << " x " << D3 << " x "  << D4 << endl;
  
 LatticeSlice ls4({D1, D2, D3, D4});

  size_t arr4[ls4.size()];

  for (auto i = 0; i < ls4.size(); ++i)
    arr4[i] = i + 1;

  ptr = arr4;

  cout << "Array =\n";

  cout << mat_to_str(ptr, D1, D2, D3, D4) << endl << endl;

  cout << Sample << " random samples" << endl;

  for (auto s = 0; s < Sample; ++s)
    {
      size_t i = gsl_rng_uniform_int(rng, D1);
      size_t j = gsl_rng_uniform_int(rng, D2);
      size_t k = gsl_rng_uniform_int(rng, D3);
      size_t l = gsl_rng_uniform_int(rng, D4);
      size_t idx = ls4.to_linear_index({i, j, k, l});
      ArrayDim arr_pos = ls4.to_subscripts(idx);
      cout << "arr4[" << i << "][" << j << "][" << k << "][" << l << "] = "
	   << arr4[idx] << " --- array pos = { " << arr_pos[0]
	   << ", " << arr_pos[1] << ", " << arr_pos[2] << ", " << arr_pos[3]
	   << " }" << endl;
    }

  gsl_rng_free(rng);
  
  return 0;
}
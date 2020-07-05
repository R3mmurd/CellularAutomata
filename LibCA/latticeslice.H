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

# ifndef LATTICESLICE_H
# define LATTICESLICE_H

# include <cstring>
# include <cassert>
# include <array>
# include <vector>
# include <numeric>
# include <algorithm>
# include <tuple>

using namespace std;

template <typename T>
class FixedArray
{
  size_t   sz;
  T * a;

  void copy(const FixedArray & ad)
  {
    for (size_t i = 0; i < sz; ++i)
      a[i] = ad.a[i];
  }

public:
  FixedArray()
    : sz(0), a(nullptr)
  {
    // Empty
  }
  
  FixedArray(size_t _sz)
    : sz(_sz), a(new T[sz])
  {
    reset();
  }

  FixedArray(const FixedArray & ad)
    : sz(ad.sz), a(new T[sz])
  {
    copy(ad);
  }

  FixedArray(FixedArray && ad)
    : FixedArray()
  {
    swap(ad);
  }

  FixedArray(const std::initializer_list<T> & l)
    : sz(l.size()), a(new T[sz])
  {
    size_t i = 0;
    
    for (auto item : l)
      a[i++] = item;
  }

  ~FixedArray()
  {
    delete [] a;
  }

  void swap(FixedArray & ad)
  {
    std::swap(sz, ad.sz);
    std::swap(a, ad.a);
  }

  void reset()
  {
    memset(a, T(0), sz * sizeof(T));
  }

  T & operator [] (size_t i)
  {
    if (i >= sz)
      throw std::overflow_error("index greater than array size");

    return a[i];
  }

  const T & operator [] (size_t i) const
  {
    if (i >= sz)
      throw std::overflow_error("index greater than array size");

    return a[i];
  }

  size_t size() const
  {
    return sz;
  }

  FixedArray & operator = (const FixedArray & ad)
  {
    if (&ad == this)
      return *this;
    
    delete [] a;
    sz = ad.sz;
    a = new T[sz];

    copy(ad);

    return *this;
  }

  FixedArray & operator = (FixedArray && ad)
  {
    swap(ad);
    return *this;
  }
};

class ArrayDim : public FixedArray<size_t>
{
  using Base = FixedArray<size_t>;
  using Base::Base;
};

class ArrayDelta : public FixedArray<char>
{
  using Base = FixedArray<char>;
  using Base::Base;
};

class LatticeSlice
{
  size_t   n;
  size_t   sz;   // size of linear array
  ArrayDim exts; // extents
  ArrayDim strs; // strides

  void init()
  {
    for (size_t i = 0; i < n; ++i)
      sz *= exts[i];

    strs[n - 1] = 1;

    for (auto i = n - 1; i > 0; --i)
      strs[i - 1] = strs[i] * exts[i];
  }

  void swap(LatticeSlice & another)
  {
    std::swap(n, another.n);
    std::swap(sz, another.sz);
    std::swap(exts, another.exts);
    std::swap(strs, another.strs);
  }

public:
  LatticeSlice(size_t _n)
    : n(_n), sz(1), exts(n), strs(n)
  {
    init();
  }

  LatticeSlice(const LatticeSlice & ls)
    : n(ls.n), sz(ls.sz), exts(ls.exts), strs(ls.strs)
  {
    // Empty
  }

  LatticeSlice(LatticeSlice && ls)
    : n(0), sz(1), exts(1), strs(1)
  {
    swap(ls);
  }

  LatticeSlice(const ArrayDim & arr)
    : n(arr.size()), sz(1), exts(arr), strs(arr.size())
  {
    init();
  }

  LatticeSlice(const std::initializer_list<size_t> & l)
    : n(l.size()), sz(1), exts(l), strs(l.size())
  {
    init();
  }

  const size_t & order() const
  {
    return n;
  }

  const size_t & size() const
  {
    return sz;
  }

  const ArrayDim & extents() const
  {
    return exts;
  }

  ArrayDim to_subscripts(const size_t & idx) const
  {
    ArrayDim ret(n);

    for (size_t i = n; i > 0; --i)
      ret[i - 1] = (idx / strs[i - 1]) % exts[i - 1];

    return ret;
  }

  size_t to_linear_index(const ArrayDim & arr) const
  {
    if (arr.size() != n)
      throw logic_error("Array size and slice order does not match");
    
    size_t ret = 0;

    for (size_t i = 0; i < n; ++i)
      ret += arr[i] * strs[i];

    return ret;
  }

  LatticeSlice & operator = (const LatticeSlice & ls)
  {
    if (&ls == this)
      return *this;

    n = ls.n;
    sz = ls.sz;
    exts = ls.exts;
    strs = ls.strs;
    
    return *this;
  }

  LatticeSlice & operator = (LatticeSlice && ls)
  {
    swap(ls);
    return *this;
  }
};

# endif //LATTICESLICE_H

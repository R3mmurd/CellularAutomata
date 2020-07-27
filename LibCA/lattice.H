/*
  Cellular automata library.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# ifndef LATTICE_H
# define LATTICE_H

# include <latticeslice.H>

template <typename T>
class Lattice
{
public:
  using DataType      = T;
  using KeyType       = T;
  using CellType      = T;
  using Slice         = LatticeSlice;
  using Container     = vector<T>;
  using Iterator      = typename Container::iterator;
  using ConstIterator = typename Container::const_iterator;

private:
  Slice     slice;
  Container mat;

  void swap(Lattice & another)
  {
    std::swap(slice, another.slice);
    std::swap(mat, another.mat);
  }

public:
  Lattice() = default;
  
  Lattice(const ArrayDim & dims)
    : slice(dims), mat(slice.size(), T())
  {
    // Empty
  }
  
  Lattice(const Lattice & lat)
    : slice(lat.slice), mat(lat.mat)
  {
    // Empty
  }

  Lattice(Lattice && lat)
    : slice({0,0})
  {
    swap(lat);
  }

  size_t to_index(T & cell) const
  {
    return size_t(&cell - &mat.at(0));
  }

  ArrayDim to_subscripts(T & cell) const
  {
    return slice.to_subscripts(to_index(cell));
  }

  const size_t & size(size_t i) const
  {
    return slice.extents()[i];
  }

  const ArrayDim & size() const
  {
    return slice.extents();
  }

  const size_t & order() const
  {
    return slice.order();
  }

  T & get(const ArrayDim & arr)
  {
    size_t idx = slice.to_linear_index(arr);
    return mat.at(idx);
  }

  const T & get(const ArrayDim & arr) const
  {
    size_t idx = slice.to_linear_index(arr);
    return mat.at(idx);
  }

  T & at(const ArrayDim & arr)
  {
    return get(arr);
  }

  const T & at(const ArrayDim & arr) const
  {
    return get(arr);
  }

  T & operator () (const ArrayDim & arr)
  {
    return at(arr);
  }

  const T & operator () (const ArrayDim & arr) const
  {
    return at(arr);
  }

  Lattice & operator = (const Lattice & lat)
  {
    if (&lat == this)
      return *this;

    slice = lat.slice;
    mat = lat.mat;
    
    return *this;
  }

  Lattice & operator = (Lattice && lat)
  {
    swap(lat);
    return *this;
  }

  Iterator begin()
  {
    return mat.begin();
  }

  Iterator end()
  {
    return mat.end();
  }
};

# endif // LATTICE

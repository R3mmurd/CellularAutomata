/*
  Cellular automata library.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# ifndef BOUNDARYCONDITION_H
# define BOUNDARYCONDITION_H

# include <lattice.H>
# include <singleton.H>

template <typename CellT>
class BoundaryCondition
{
public:
  virtual CellT * get(Lattice<CellT> &, const ArrayDim &,
		      const ArrayDelta &) = 0;
};

template <typename CellT>
class Periodic : public BoundaryCondition<CellT>,
                 public Designar::Singleton<Periodic<CellT>>
{
 public:
  CellT * get(Lattice<CellT> & lattice, const ArrayDim & pos,
	      const ArrayDelta & delta) override
  {
    if (pos.size() != lattice.order())
      throw logic_error("pos array does not match with order");
    
    ArrayDim idxs(lattice.order());

    for (size_t n = 0; n < lattice.order(); ++n)
      {
	const size_t & p = pos[n];
	const char   & d = delta[n];
	assert(-1 <= d and d <= 1);
	size_t & i = idxs[n];

	if (d < 0)
	  if (p == 0)
	    i = lattice.size(n) - 1;
	  else
	    i = p - 1;
	    
	else if (d > 0)
	  if (p == lattice.size(n) - 1)
	    i = 0;
	  else
	    i = p + 1;
	else
	  i = p;
      }

    return &lattice.get(idxs);
  }
};

template <typename CellT>
class Reflect : public BoundaryCondition<CellT>,
                public Designar::Singleton<Reflect<CellT>>
{
 public:
  CellT * get(Lattice<CellT> & lattice, const ArrayDim & pos,
	      const ArrayDelta & delta) override
  {
    if (pos.size() != lattice.order())
      throw logic_error("pos array does not match with order");
    
    ArrayDim idxs(lattice.order());

    for (size_t n = 0; n < lattice.order(); ++n)
      {
	const size_t & p = pos[n];
	const char   & d = delta[n];
	assert(-1 <= d and d <= 1);
	size_t & i = idxs[n];

	if (d < 0)
	  if (p == 0)
	    i = p + 1;
	  else
	    i = p - 1;
	    
	else if (d > 0)
	  if (p == lattice.size(n) - 1)
	    i = p - 1;
	  else
	    i = p + 1;
	else
	  i = p;
      }

    return &lattice.get(idxs);
  }
};

template <typename CellT>
class Fixed : public BoundaryCondition<CellT>
{
  CellT fixed_value;
  
public:
  Fixed(const CellT & fval = CellT())
    : fixed_value(fval)
  {
    // Empty
  }

  Fixed(const Fixed &) = delete;

  Fixed & operator = (const Fixed &) = delete;

  void set_fixed_value(const CellT & fval)
  {
    fixed_value = fval;
  }

  const CellT & get_fixed_value() const
  {
    return fixed_value;
  }
  
  CellT * get(Lattice<CellT> & lattice, const ArrayDim & pos,
	      const ArrayDelta & delta) override
  {
    if (pos.size() != lattice.order() or delta.size() != lattice.order())
      throw logic_error("pos or delta array does not match with order");
    
    ArrayDim idxs(lattice.order());

    for (size_t n = 0; n < lattice.order(); ++n)
      {
	const size_t & p = pos[n];
	const char   & d = delta[n];
	assert(-1 <= d and d <= 1);
	size_t & i = idxs[n];

	if (d < 0)
	  if (p == 0)
	    return &fixed_value;
	  else
	    i = p - 1;
	    
	else if (d > 0)
	  if (p == lattice.size(n) - 1)
	    return &fixed_value;
	  else
	    i = p + 1;
	else
	  i = p;
      }

    return &lattice.get(idxs);
  }
};

# endif // BOUNDARYCONDITION_H

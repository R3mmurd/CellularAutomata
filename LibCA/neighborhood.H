/*
  Cellular automata library.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# ifndef NEIGHBORHOOD_H
# define NEIGHBORHOOD_H

# include <boundarycondition.H>

template <typename CellT>
class Neighborhood
{
  virtual vector<CellT *> get_neighbors(Lattice<CellT> &,
                                        BoundaryCondition<CellT> *,
					const ArrayDim &) = 0;
};


template <typename CellT>
class OneDimNeighborhood : public Neighborhood<CellT>,
                           public Designar::Singleton<OneDimNeighborhood<CellT>>
{
  friend class Designar::Singleton<OneDimNeighborhood<CellT>>;
public:
  vector<CellT *> get_neighbors(Lattice<CellT> & lattice,
                                BoundaryCondition<CellT> * bcond,
				const ArrayDim & arr) override
  {
    vector<CellT *> ret;
    
    ret.push_back(bcond->get(lattice, arr, {-1}));
    ret.push_back(bcond->get(lattice, arr, {1}));
    
    return ret;
  }
};

template <typename CellT>
class VonNeumannNeighborhood :
        public Neighborhood<CellT>,
        public Designar::Singleton<VonNeumannNeighborhood<CellT>>
{
public:
  vector<CellT *> get_neighbors(Lattice<CellT> & lattice,
                                BoundaryCondition<CellT> * bcond,
				const ArrayDim & arr) override
  {
    vector<CellT *> ret;

    for (size_t i = 0; i < lattice.order(); ++i)
      {
        ArrayDelta delta(lattice.order());

	for (size_t i = 0; i < delta.size(); ++i)
	  delta[i] = 0;

	delta[i] = -1;
	ret.push_back(bcond->get(lattice, arr, delta));
	delta[i] = 1;
	ret.push_back(bcond->get(lattice, arr, delta));
      }

    return ret;
  }
};

template <typename CellT>
class MooreNeighborhood : public Neighborhood<CellT>,
                          public Designar::Singleton<MooreNeighborhood<CellT>>
{
public:
  vector<CellT *> get_neighbors(Lattice<CellT> & lattice,
                                BoundaryCondition<CellT> * bcond,
				const ArrayDim & arr) override
  {
    vector<CellT *> ret;

    ArrayDelta delta(lattice.order());

    for (size_t i = 0; i < delta.size(); ++i)
      delta[i] = -1;
    
    int l = 0, r = lattice.order();
    
    while (r > lattice.order() - 1)
      {
	bool zero = true;
	
	for (size_t i = 0; i < delta.size(); ++i)
	  zero = zero and delta[i] == 0;
	
	if (not zero)
	  ret.push_back(bcond->get(lattice, arr, delta));
	
	++delta[l];
	
	while (l < r and delta[l] > 1)
	  {
	    delta[l++] = -1;
	    if (l < delta.size())
	      ++delta[l];
	  }
	
	if (l == r)
	  --r;
	
	l = 0;
      }
    
    return ret;
  }
};

# endif // NEIGHBORHOOD_H

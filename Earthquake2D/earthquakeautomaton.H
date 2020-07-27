/*
  Cellular automaton: Earthquake 2D.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# ifndef EARTHQUAKEAUTOMATON_H
# define EARTHQUAKEAUTOMATON_H

# include <stack.H>
# include <list.H>

# include <neighborhood.H>

# include <QPainter>

class QPainter;

class EarthquakeAutomaton
{
  static constexpr double DE = 0.0002;
  static constexpr double EC = 4.0;

public:
  static constexpr unsigned SCALE = 10;
  static constexpr unsigned WIDTH = 64;
  static constexpr unsigned HEIGHT = 64;

private:
  struct ReleaseData
  {
    unsigned i;
    unsigned j;
  };

  using Release = Designar::SLNode<ReleaseData>;

  Release release;

  Designar::ListStack<Release *> rel_pool;

  Release * get_release();

  unsigned num_release;
  unsigned t;

  using NeighborhoodType = VonNeumannNeighborhood<double>;

  Fixed<double> bcond;

  Lattice<double> lattice;

public:
  EarthquakeAutomaton();

  ~EarthquakeAutomaton();

  void draw(QPainter &);

  void update();
};

# endif // EARTHQUAKEAUTOMATON_H

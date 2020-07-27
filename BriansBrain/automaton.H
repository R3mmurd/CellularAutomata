/*
  Cellular automaton: Brian's Brain.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# ifndef AUTOMATON_H
# define AUTOMATON_H

# include <QPainter>

# include <neighborhood.H>

class Automaton
{
public:
  enum class Status
  {
    ON, DYING, OFF
  };

  static constexpr unsigned WIDTH = 240;
  static constexpr unsigned HEIGHT = 160;
  static constexpr unsigned SCALE = 5;

private:
  using NeighborhoodType = MooreNeighborhood<Status>;
  using BCondType = Periodic<Status>;

  Lattice<Status> lattice;
  Lattice<Status> tmp_lattice;

public:
  Automaton();

  void draw(QPainter &);

  void update();
};

# endif // AUTOMATON_H

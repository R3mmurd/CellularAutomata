/*
  Conway's Game of Life.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# ifndef AUTOMATON_H
# define AUTOMATON_H

# include <neighborhood.H>

# include <QPainter>

class Automaton
{
public:
  static constexpr unsigned WIDTH = 250;
  static constexpr unsigned HEIGHT = 100;
  static constexpr unsigned SCALE = 4;

  using CellType = uint8_t;
  using NeighborhoodType = MooreNeighborhood<CellType>;
  using BCondType = Periodic<CellType>;

private:
  Lattice<CellType> lattice;
  Lattice<CellType> tmp_lattice;

public:
  Automaton();

  void update();

  void draw(QPainter &);
};

# endif // AUTOMATON_H

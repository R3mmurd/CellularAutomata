/*
  Elementary cellular automaton.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# ifndef AUTOMATON_H
# define AUTOMATON_H

# include <QPainter>
# include <QList>

# include <bitset.H>
# include <neighborhood.H>

class Automaton
{
  public:
  enum class Status
  {
    ON, OFF
  };

  static constexpr unsigned WIDTH = 260;
  static constexpr unsigned MAX_HEIGHT = 120;
  static constexpr unsigned SCALE = 5;
  static constexpr unsigned DELAY = 100;

private:
  using NeighborhoodType = OneDimNeighborhood<Status>;

  Designar::Byte rule;

  QList<Lattice<Status>> lattices;
  Fixed<Status> bcond;

public:
  Automaton();

  void reset();

  void set_rule(const Designar::Byte &);

  void update();

  void draw(QPainter &);
};

# endif // AUTOMATON_H

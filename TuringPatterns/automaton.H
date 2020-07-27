/*
  Turing patterns.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# ifndef AUTOMATON_H
# define AUTOMATON_H

# include <set.H>

# include <cell.H>
# include <neighborhood.H>

class QPainter;

class Automaton
{
public:
  using Channel = Cell::ChannelVel;

  using BagType = Designar::TreeSet<Channel>;

  static constexpr unsigned L = 100;
  static constexpr unsigned SCALE = 5;

private:
  mt19937 rng;

  Lattice<Cell> L_A_0;
  Lattice<Cell> L_A_1;
  Lattice<Cell> L_I_0;
  Lattice<Cell> L_I_1;

  double p_c;
  double p_d;
  unsigned m_a;
  unsigned m_i;

  BagType bag;

  void fill_bag();

  Channel take_from_bag();

  unsigned wrap_plus(unsigned, unsigned);

  unsigned wrap_subs(unsigned, unsigned);

public:
  Automaton();

  void update();

  void randomize();

  void draw(QPainter &);

  double get_p_c() const;

  void set_p_c(const double &);

  double get_p_d() const;

  void set_p_d(const double &);

  unsigned get_m_a() const;

  void set_m_a(unsigned);

  unsigned get_m_i() const;

  void set_m_i(unsigned);
};

# endif // AUTOMATON_H

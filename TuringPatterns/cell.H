/*
  Turing patterns.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# ifndef CELL_H
# define CELL_H

# include <random_util.H>

class Cell
{
public:
  enum ChannelVel { UP, DOWN, LEFT, RIGHT, REST, NUM_CHANNELS };

private:
  unsigned channels[NUM_CHANNELS];

public:
  Cell();

  unsigned get_num_particles() const;

  const unsigned & get(const ChannelVel &);

  void set(const ChannelVel &, const unsigned &);

  void reset();

  void randomize(std::mt19937 &);
};

#endif // CELL_H

/*
  Turing patterns.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# include <cell.H>

Cell::Cell()
{
  reset();
}

unsigned Cell::get_num_particles() const
{
  unsigned ret = 0;

  for (unsigned i = 0; i < NUM_CHANNELS; ++i)
    ret += channels[i];

  return ret;
}

const unsigned & Cell::get(const Cell::ChannelVel & p)
{
  return channels[p];
}

void Cell::set(const Cell::ChannelVel & p, const unsigned & v)
{
  channels[p] = v;
}

void Cell::reset()
{
  for (unsigned i = 0; i < NUM_CHANNELS; ++i)
    channels[i] = 0;
}

void Cell::randomize(std::mt19937 & rng)
{
  for (unsigned i = 0; i < NUM_CHANNELS; ++i)
    channels[i] = generate_random_bit(rng);
}


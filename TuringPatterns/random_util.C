/*
  Turing patterns.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# include <cmath>
# include <random_util.H>

unsigned generate_random_bit(mt19937 & rng)
{
  return round(generate_canonical<double, 64>(rng));
}

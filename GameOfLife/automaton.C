/*
  Conway's Game of Life.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# include <random>

# include <automaton.H>

Automaton::Automaton()
  : lattice({HEIGHT,WIDTH}), tmp_lattice({HEIGHT,WIDTH})
{
  for (auto & cell : lattice)
    cell = 0;

  auto seed = time(0) % mt19937::max();

  mt19937 rng(seed);

  auto sz = lattice.size();

  uniform_int_distribution<uint64_t> h_unif_dist(0, sz[1] - 1);
  uniform_int_distribution<uint64_t> v_unif_dist(0, sz[0] - 1);

  size_t num_living_cells = sz[0] * sz[1] * 0.7;

  for (size_t k = 0; k < num_living_cells; ++k)
    {
      auto i = v_unif_dist(rng);
      auto j = h_unif_dist(rng);

      lattice({i, j}) = 1;
    }
}

void Automaton::update()
{
  for (auto & cell : lattice)
    {
      auto pos = lattice.to_subscripts(cell);
      auto neighbors = NeighborhoodType::get_instance().
          get_neighbors(lattice, BCondType::get_ptr_instance(), pos);

      unsigned num = 0;

      for (auto n : neighbors)
        if (*n == 1)
          ++num;

      if (cell == 1)
        {
          if (num < 2 or num > 3)
            tmp_lattice.at(pos) = 0;
          else
            tmp_lattice.at(pos) = 1;
        }
      else
        {
          if (num == 3)
            tmp_lattice.at(pos) = 1;
          else
            tmp_lattice.at(pos) = 0;
        }
    }

  std::swap(lattice, tmp_lattice);
}

void Automaton::draw(QPainter & painter)
{
  for(unsigned i = 0; i < HEIGHT; ++i)
    for (unsigned j = 0; j < WIDTH; ++j)
      {
        auto cell = lattice.at({i, j});

        QColor color = cell == 0 ? Qt::white : Qt::black;

        painter.fillRect(j * SCALE, i * SCALE, SCALE, SCALE, color);
      }
}

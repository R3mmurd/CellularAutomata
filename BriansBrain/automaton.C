/*
  Cellular automaton: Brian's Brain.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# include <automaton.H>
# include <random>

Automaton::Automaton()
  : lattice({HEIGHT, WIDTH}), tmp_lattice(lattice.size())
{
  for (auto & cell : lattice)
    cell = Status::OFF;

  std::mt19937_64 rng(time(nullptr) % std::mt19937_64::max());
  std::uniform_int_distribution<int> dist(0, 2);

  size_t mw = WIDTH/2;
  size_t mh = HEIGHT/2;

  for (size_t i = mh - HEIGHT/6; i <= mh + HEIGHT/6; ++i)
    for (size_t j = mw - WIDTH/6; j <= mw + WIDTH/6; ++j)
      {
        int v = dist(rng);
        lattice.at({i, j}) = Status(v);
      }
}

void Automaton::draw(QPainter & painter)
{
  for (size_t i = 0; i < HEIGHT; ++i)
    for (size_t j = 0; j < WIDTH; ++j)
      {
        switch(lattice({i, j}))
          {
          case Status::ON:
            painter.setBrush(Qt::white);
            break;
          case Status::DYING:
            painter.setBrush(Qt::blue);
            break;
          default:
            painter.setBrush(Qt::black);
          }
        painter.drawRect(j * SCALE, i * SCALE, SCALE, SCALE);
      }
}

void Automaton::update()
{
  for (auto & cell : lattice)
    {
      auto pos = lattice.to_subscripts(cell);
      auto neighbors = NeighborhoodType::get_instance().
          get_neighbors(lattice, BCondType::get_ptr_instance(), pos);

      if (cell == Status::DYING)
        {
          tmp_lattice.at(pos) = Status::OFF;
          continue;
        }

      if (cell == Status::ON)
        {
          tmp_lattice.at(pos) = Status::DYING;
          continue;
        }

      size_t num = 0;

      for (auto p : neighbors)
        if (*p == Status::ON)
          ++num;

      tmp_lattice.at(pos) = (num == 2 ? Status::ON : Status::OFF);
    }

  std::swap(lattice, tmp_lattice);
}

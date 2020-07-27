/*
  Elementary cellular automaton.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# include <automaton.H>

unsigned to_num(Automaton::Status a, Automaton::Status b, Automaton::Status c)
{
  if (a == Automaton::Status::ON and b == Automaton::Status::ON and
      c == Automaton::Status::ON)
    return 7;
  if (a == Automaton::Status::ON and b == Automaton::Status::ON and
      c == Automaton::Status::OFF)
    return 6;
  if (a == Automaton::Status::ON and b == Automaton::Status::OFF and
      c == Automaton::Status::ON)
    return 5;
  if (a == Automaton::Status::ON and b == Automaton::Status::OFF and
      c == Automaton::Status::OFF)
    return 4;
  if (a == Automaton::Status::OFF and b == Automaton::Status::ON and
      c == Automaton::Status::ON)
    return 3;
  if (a == Automaton::Status::OFF and b == Automaton::Status::ON and
      c == Automaton::Status::OFF)
    return 2;
  if (a == Automaton::Status::OFF and b == Automaton::Status::OFF and
      c == Automaton::Status::ON)
    return 1;
  return 0;
}

Automaton::Automaton()
  : rule(0), bcond(Status::OFF)
{
  reset();
}

void Automaton::reset()
{
  lattices.clear();
  lattices.append(Lattice<Status>(ArrayDim({WIDTH})));
  Lattice<Status> & lattice = lattices.back();

  for (auto & cell : lattice)
    cell = Status::OFF;

  lattice.at({lattice.size(0) / 2 + 1}) = Status::ON;
}

void Automaton::set_rule(const Designar::Byte & value)
{
  rule = value;
}

void Automaton::update()
{
  if (lattices.size() >= MAX_HEIGHT)
    return;

  Lattice<Status> & lattice = lattices.back();
  lattices.append(Lattice<Status>(lattice.size()));
  Lattice<Status> & new_lattice = lattices.back();

  for (auto & cell : lattice)
    {
      auto pos = lattice.to_subscripts(cell);
      auto neighbors = NeighborhoodType::get_instance().
          get_neighbors(lattice, &bcond, pos);

      auto num = to_num(*neighbors[0], cell, *neighbors[1]);
      new_lattice.at(pos) = rule.get_bit(num) == 1 ? Status::ON : Status::OFF;
    }
}

void Automaton::draw(QPainter & painter)
{
  unsigned i = 0;

  for (auto & lattice : lattices)
    {
      for (unsigned j = 0; j < lattice.size(0); ++j)
        {
          if (lattice.at({j}) == Status::ON)
            painter.fillRect(j * SCALE, i * SCALE, SCALE, SCALE, Qt::black);
        }
      ++i;
    }
}

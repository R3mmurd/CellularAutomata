/*
  Cellular automaton: Earthquake 2D.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# include <random>
# include <fstream>

# include <earthquakeautomaton.H>

EarthquakeAutomaton::Release * EarthquakeAutomaton::get_release()
{
  Release * ret = nullptr;

  if (rel_pool.is_empty())
    ret = new Release;
  else
    ret = rel_pool.pop();

  return ret;
}

EarthquakeAutomaton::EarthquakeAutomaton()
  : num_release(0), t(0), lattice({WIDTH, HEIGHT})
{
  mt19937 rng(time(0) % mt19937::max());

 for (auto & cell : lattice)
   cell = 3.96 + 0.005 * generate_canonical<double, 64>(rng);
}

EarthquakeAutomaton::~EarthquakeAutomaton()
{
  while (not rel_pool.is_empty())
    delete rel_pool.pop();

  while (release.get_next() != nullptr)
    delete release.remove_next();
}

void EarthquakeAutomaton::draw(QPainter & painter)
{
  for (unsigned i = 0; i < lattice.size(0); ++i)
    for (unsigned j = 0; j < lattice.size(1); ++j)
      if (lattice.at({i, j}) < 1.0)
        painter.fillRect(j * SCALE, i * SCALE, SCALE, SCALE, Qt::black);
      else if (lattice.at({i, j}) < 2.0)
        painter.fillRect(j * SCALE, i * SCALE, SCALE, SCALE,
                         Qt::darkGray);
      else if (lattice.at({i, j}) < 3.0)
        painter.fillRect(j * SCALE, i * SCALE, SCALE, SCALE, Qt::gray);
      else if (lattice.at({i, j}) < 4.0)
        painter.fillRect(j * SCALE, i * SCALE, SCALE, SCALE,
                         Qt::lightGray);
      else
        painter.fillRect(j * SCALE, i * SCALE, SCALE, SCALE,
                         Qt::white);
}

void EarthquakeAutomaton::update()
{
  if (release.get_next() != nullptr)
    {
      std::ofstream file("output.dat", std::ios::app);

      file << t++ << '\t' << num_release << '\n';

      file.close();

      while (release.get_next() != nullptr)
        {
          rel_pool.push(static_cast<Release *>(release.remove_next()));

          unsigned i = rel_pool.top()->get_item().i;
          unsigned j = rel_pool.top()->get_item().j;

          double p = EC / 4.0;

          lattice.at({i, j}) -= EC;

          auto neighbors = NeighborhoodType::get_instance().
              get_neighbors(lattice, &bcond, {i,j});

          for (auto n : neighbors)
            *n += p;
        }

      num_release = 0;

      for (unsigned i(0); i < lattice.size(0); ++i)
        for (unsigned j(0); j < lattice.size(1); ++j)
          {
            if (lattice.at({i, j}) > EC)
              {
                Release * r = get_release();
                r->get_item().i = i;
                r->get_item().j = j;
                release.insert_next(r);
                ++num_release;
              }
          }

      return;
    }

  for (unsigned i(0); i < lattice.size(0); ++i)
    for (unsigned j(0); j < lattice.size(0); ++j)
      {
        lattice.at({i, j}) += DE;

        if (lattice.at({i, j}) > EC)
          {
            Release * r = get_release();
            r->get_item().i = i;
            r->get_item().j = j;
            release.insert_next(r);
            ++num_release;
          }
      }
}

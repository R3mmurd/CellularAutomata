/*
  This file is part of Ising 2D.
  Copyright (C) 2016 by Alejandro J. Mujica

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

  Any user request of this software, write to

  Alejandro Mujica

  aledrums@gmail.com
*/

# include <automatonpanel.H>

void AutomatonPanel::keyPressEvent(QKeyEvent * evt)
{
  if (evt->key() != Qt::Key_S)
    return;

  if (running)
    {
      timer.stop();
      running = false;
      automaton.generate_gnuplot_dat("data.dat");
      automaton.generate_gnuplot_script("plot.gp", "data.dat", "plot.png");
    }
  else
    {
      timer.start();
      running = true;
    }
}

void AutomatonPanel::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.fillRect(0, 0, width(), height(), Qt::white);
  automaton.draw(painter);
}

AutomatonPanel::AutomatonPanel(QWidget * parent)
  : QWidget(parent), running(false)
{
  setFixedSize(IsingAutomaton2D::WIDTH * IsingAutomaton2D::SCALE,
               IsingAutomaton2D::HEIGHT * IsingAutomaton2D::SCALE);
  timer.setInterval(10);
  connect(&timer, SIGNAL(timeout()), this, SLOT(step()));
}

void AutomatonPanel::step()
{
  automaton.step(1.5);
  repaint();
}


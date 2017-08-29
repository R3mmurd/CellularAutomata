/*
  This file is part of Earthquake 2D.
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

# include <QDebug>

void AutomatonPanel::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.fillRect(0, 0, width(), height(), Qt::white);
  automaton.draw(painter);
}

void AutomatonPanel::keyPressEvent(QKeyEvent * evt)
{
  if (evt->key() != Qt::Key_S)
    return;

  if (running)
    {
      running = false;
      timer.stop();
    }
  else
    {
      running = true;
      timer.start();
    }
}

AutomatonPanel::AutomatonPanel(QWidget * parent)
  : QWidget(parent), running(false)
{
  setFixedSize(EarthquakeAutomaton::WIDTH * EarthquakeAutomaton::SCALE,
               EarthquakeAutomaton::HEIGHT * EarthquakeAutomaton::SCALE);
  timer.setInterval(100);
  connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
}

void AutomatonPanel::update()
{
  automaton.update();
  repaint();
}


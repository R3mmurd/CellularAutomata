/*
  This file is part of Elementary Cellular Automaton.
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

AutomatonPanel::AutomatonPanel(QWidget * parent)
  : QWidget(parent)
{
  setFixedSize(Automaton::WIDTH * Automaton::SCALE,
               Automaton::MAX_HEIGHT * Automaton::SCALE);
  connect(&timer, SIGNAL(timeout()), this, SLOT(update()));

  timer.setInterval(500);
}

void AutomatonPanel::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.fillRect(0, 0, width(), height(), Qt::white);
  automaton.draw(painter);
}

void AutomatonPanel::run(Byte rule)
{
  automaton.set_rule(rule);
  timer.start();
}

void AutomatonPanel::stop()
{
  timer.stop();
}

void AutomatonPanel::clear()
{
  automaton.reset();
  repaint();
}

void AutomatonPanel::update()
{
  automaton.update();
  repaint();
}

/*
  Turing patterns.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# include <QPainter>
# include <automatonpanel.H>

void AutomatonPanel::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.fillRect(0, 0, width(), height(), Qt::white);
  automaton.draw(painter);
}

AutomatonPanel::AutomatonPanel(Automaton & _automaton, QWidget * parent)
  : QWidget(parent), automaton(_automaton)
{
  setFixedSize(Automaton::L * Automaton::SCALE,
               Automaton::L * Automaton::SCALE);
}

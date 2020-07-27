/*
  Elementary cellular automaton.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# include <automatonpanel.H>

AutomatonPanel::AutomatonPanel(QWidget * parent)
  : QWidget(parent)
{
  setFixedSize(Automaton::WIDTH * Automaton::SCALE,
               Automaton::MAX_HEIGHT * Automaton::SCALE);
  connect(&timer, SIGNAL(timeout()), this, SLOT(update()));

  timer.setInterval(Automaton::DELAY);
}

void AutomatonPanel::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.fillRect(0, 0, width(), height(), Qt::white);
  automaton.draw(painter);
}

void AutomatonPanel::run(Designar::Byte rule)
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

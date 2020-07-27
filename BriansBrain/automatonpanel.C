/*
  Cellular automaton: Brian's Brain.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# include <automatonpanel.H>

# include <QDebug>

AutomatonPanel::AutomatonPanel(QWidget * parent)
  : QWidget(parent), running(false)
{

  setFixedSize(Automaton::WIDTH * Automaton::SCALE,
               Automaton::HEIGHT * Automaton::SCALE);
  connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
  timer.setInterval(33);
}

void AutomatonPanel::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.setPen(Qt::black);
  automaton.draw(painter);
}

void AutomatonPanel::keyPressEvent(QKeyEvent *)
{
  if (running)
    {
      timer.stop();
      running = false;
    }
  else
    {
      timer.start();
      running = true;
    }
}

void AutomatonPanel::update()
{
  automaton.update();
  repaint();
}

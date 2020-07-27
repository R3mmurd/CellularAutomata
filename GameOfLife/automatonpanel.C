/*
  Conway's Game of Life.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# include <automatonpanel.H>

AutomatonPanel::AutomatonPanel(QWidget * parent)
  : QWidget(parent), running(false)
{
  setFixedSize(Automaton::WIDTH * Automaton::SCALE,
               Automaton::HEIGHT * Automaton::SCALE);
  setWindowTitle("Conway's Game of Life");

  timer.setInterval(100);

  connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
}

void AutomatonPanel::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.fillRect(0, 0, width(), height(), Qt::white);
  automaton.draw(painter);
}

void AutomatonPanel::keyPressEvent(QKeyEvent *)
{
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

void AutomatonPanel::update()
{
  automaton.update();
  repaint();
}

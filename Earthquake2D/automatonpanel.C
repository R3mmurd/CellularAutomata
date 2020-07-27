/*
  Cellular automaton: Earthquake 2D.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
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


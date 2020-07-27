/*
  Cellular automaton: Earthquake 2D.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# ifndef AUTOMATONPANEL_H
# define AUTOMATONPANEL_H

# include <QWidget>
# include <QTimer>
# include <QKeyEvent>
# include <QPainter>

# include <earthquakeautomaton.H>

class AutomatonPanel : public QWidget
{
  Q_OBJECT

  EarthquakeAutomaton automaton;

  bool running;

  QTimer timer;

protected:
  void paintEvent(QPaintEvent *);

  void keyPressEvent(QKeyEvent *);

public:
  AutomatonPanel(QWidget * parent = nullptr);

public slots:
  void update();
};

#endif // AUTOMATONPANEL_H

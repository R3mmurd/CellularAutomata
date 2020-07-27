/*
  Cellular automaton: Brian's Brain.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# ifndef AUTOMATONPANEL_H
# define AUTOMATONPANEL_H

# include <QWidget>
# include <QTimer>

# include <automaton.H>

class AutomatonPanel : public QWidget
{
  Q_OBJECT

  QTimer timer;

  Automaton automaton;

  bool running;

public:
  AutomatonPanel(QWidget * parent = 0);

  void paintEvent(QPaintEvent *);

  void keyPressEvent(QKeyEvent *);

signals:

public slots:
  void update();
};

# endif // AUTOMATONPANEL_H


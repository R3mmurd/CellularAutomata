/*
  Conway's Game of Life.
  
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

  Automaton automaton;

  QTimer timer;

  bool running;

  void init();
public:
  AutomatonPanel(QWidget * parent = nullptr);

protected:
  void paintEvent(QPaintEvent *);

  void keyPressEvent(QKeyEvent *);

public slots:
  void update();
};

# endif // AUTOMATONPANEL_H

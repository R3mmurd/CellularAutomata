/*
  Elementary cellular automaton.
  
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

public:
  AutomatonPanel(QWidget * parent = nullptr);

  void paintEvent(QPaintEvent *);

  void run(Designar::Byte);

  void stop();

  void clear();

signals:
  
public slots:
  void update();
};

# endif // AUTOMATONPANEL_H

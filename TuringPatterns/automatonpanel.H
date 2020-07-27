/*
  Turing patterns.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# ifndef AUTOMATONPANEL_H
# define AUTOMATONPANEL_H

# include <QWidget>
# include <automaton.H>

class AutomatonPanel : public QWidget
{
  Q_OBJECT

  Automaton & automaton;

protected:
  void paintEvent(QPaintEvent *);

public:
  AutomatonPanel(Automaton &, QWidget * parent = nullptr);
};

# endif // AUTOMATONPANEL_H

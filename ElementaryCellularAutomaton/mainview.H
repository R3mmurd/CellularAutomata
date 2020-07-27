/*
  Elementary cellular automaton.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# ifndef MAINVIEW_H
# define MAINVIEW_H

# include <QPushButton>
# include <QLabel>
# include <QLineEdit>
# include <QVBoxLayout>
# include <QHBoxLayout>
# include <automatonpanel.H>

class MainView : public QWidget
{
  Q_OBJECT

  QLabel      * lbl_rule;
  QLineEdit   * edt_rule;
  QPushButton * btn_run;
  QPushButton * btn_clear;

  AutomatonPanel * automaton_panel;

  bool running;

public:
  MainView(QWidget * parent = nullptr);

  void init_gui();

public slots:
  void slot_run();

  void slot_clear();
};

#endif // MAINVIEW_H

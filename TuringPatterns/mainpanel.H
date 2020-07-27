/*
  Turing patterns.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# ifndef MAINPANEL_H
# define MAINPANEL_H

# include <QWidget>
# include <QLabel>
# include <QLineEdit>
# include <QPushButton>
# include <QVBoxLayout>
# include <QHBoxLayout>
# include <QTimer>
# include <automatonpanel.H>

class MainPanel : public QWidget
{
  Q_OBJECT

  QVBoxLayout * main_layout;
  QHBoxLayout * input_layout;

  QLabel * lbl_p_c;
  QLabel * lbl_p_d;
  QLabel * lbl_m_a;
  QLabel * lbl_m_i;

  QLineEdit * edt_p_c;
  QLineEdit * edt_p_d;
  QLineEdit * edt_m_a;
  QLineEdit * edt_m_i;

  QPushButton * btn_action;

  Automaton automaton;

  AutomatonPanel * panel;

  QTimer timer;

  bool running;

  void init_gui();

  bool validate();

  void update_inputs();

public:
  MainPanel(QWidget * parent = 0);

signals:

public slots:
  void slot_btn_action_clicked();

  void update_automaton();
};

# endif // MAINPANEL_H

/*
  This file is part of Turing Patterns.
  Copyright (C) 2016 by Alejandro J. Mujica

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

  Any user request of this software, write to

  Alejandro Mujica

  aledrums@gmail.com
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

/*
  This file is part of Elementary Cellular Automaton.
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

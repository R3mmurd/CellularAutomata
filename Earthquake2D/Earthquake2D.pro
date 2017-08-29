#  This file is part of Earthquake 2D.
#  Copyright (C) 2016 by Alejandro J. Mujica

#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.

#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.

#  You should have received a copy of the GNU General Public License
#  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#  Any user request of this software, write to

#  Alejandro Mujica

#  aledrums@gmail.com

QMAKE_CXX = clang++

CONFIG += c++14

QT += widgets core

BASEDIR = /home/alex/Dropbox/Work/Programs/CC++

INCLUDEPATH += $${BASEDIR}/Aleph-w \
               $${BASEDIR}/Common \
               $${BASEDIR}/CellularAutomaton/LibCA

LIBS += -L /home/alex/Aleph-w \
        -lAleph

HEADERS += \
    earthquakeautomaton.H \
    automatonpanel.H

SOURCES += \
    main.C \
    earthquakeautomaton.C \
    automatonpanel.C

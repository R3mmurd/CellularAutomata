QT += core widgets

QMAKE_CXX = clang++

CONFIG += c++14

BASEDIR = ../..

INCLUDEPATH += $${BASEDIR}/DeSiGNAR/include \
               $${BASEDIR}/CellularAutomata/LibCA

LIBS += -lc -lstdc++

SOURCES += \
    main.C \
    automatonpanel.C \
    automaton.C

HEADERS += \
    automatonpanel.H \
    automaton.H

QMAKE_CXX = clang++
QT += core widgets
CONFIG += c++14

BASEDIR = ../../

INCLUDEPATH += $${BASEDIR}/DeSiGNAR/include \
               $${BASEDIR}/CellularAutomata/LibCA

HEADERS += \
    automaton.H \
    automatonpanel.H

SOURCES += \
    main.C \
    automaton.C \
    automatonpanel.C

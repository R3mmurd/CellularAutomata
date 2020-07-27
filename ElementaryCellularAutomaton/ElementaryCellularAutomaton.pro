QT += core widgets
QMAKE_CXX = clang++
CONFIG += c++14

BASE_DIR = ../..

INCLUDEPATH += $${BASE_DIR}/DeSiGNAR/include \
               $${BASE_DIR}/CellularAutomaton/LibCA

LIBS += -L ~/DeSiGNAR/lib -lDesignar

HEADERS += \
    automaton.H \
    mainview.H \
    automatonpanel.H

SOURCES += \
    main.C \
    automaton.C \
    mainview.C \
    automatonpanel.C

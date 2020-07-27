QMAKE_CXX = clang++

QT += core widgets

CONFIG += c++14

BASEDIR = ../..

INCLUDEPATH += $${BASEDIR}/DeSiGNAR/include \
               $${BASEDIR}/CellularAutomaton/LibCA

LIBS +=

HEADERS = \
    automaton.H \
    cell.H \
    random_util.H \
    mainpanel.H \
    automatonpanel.H

SOURCES = \
    automaton.C \
    cell.C \
    main.C \
    random_util.C \
    mainpanel.C \
    automatonpanel.C

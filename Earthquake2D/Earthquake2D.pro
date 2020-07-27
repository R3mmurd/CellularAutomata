QMAKE_CXX = clang++

CONFIG += c++14

QT += widgets core

BASEDIR = ../..

INCLUDEPATH += $${BASEDIR}/DeSiGNAR/include \
               $${BASEDIR}/CellularAutomaton/LibCA

LIBS += -L ~/DeSiGNAR/lib -lDesignar

HEADERS += \
    earthquakeautomaton.H \
    automatonpanel.H

SOURCES += \
    main.C \
    earthquakeautomaton.C \
    automatonpanel.C

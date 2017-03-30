QT += core
QT -= gui

CONFIG += c++11

TARGET = Dna_Topo
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    file.cpp \
    test.cpp \
    test1.cpp \
    test3.cpp \
    test4.cpp \
    test5.cpp

HEADERS += \
    fileread.h

DISTFILES += \
    a1.py

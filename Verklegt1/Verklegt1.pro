QT += core
QT += sql
QT -= gui

TARGET = Verklegt1
CONFIG += console
CONFIG -= app_bundle
CONFIG += c++11

TEMPLATE = app

SOURCES += main.cpp \
    person.cpp \
    data.cpp \
    domain.cpp \
    presentation.cpp

HEADERS += \
    person.h \
    data.h \
    presentation.h \
    domain.h


#-------------------------------------------------
#
# Project created by QtCreator 2015-12-09T14:28:16
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Verklegt_Namskeid-Skil3
TEMPLATE = app
CONFIG += c++11


SOURCES += main.cpp\
        mainwindow.cpp \
    person.cpp \
    machine.cpp \
    personmachine.cpp \
    data.cpp

HEADERS  += mainwindow.h \
    person.h \
    machine.h \
    personmachine.h \
    utilities.h \
    data.h \
    constants.h

FORMS    += mainwindow.ui

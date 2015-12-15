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
    data.cpp \
    services.cpp \
    utilities.cpp \
    editpersondialog.cpp \
    addpersondialog.cpp \
    uiperson.cpp \
    uimachines.cpp \
    uiconnections.cpp \
    addmachinedialog.cpp \
    typesystem.cpp \
    editmachinedialog.cpp
    connecttomachine.cpp \
    connecttoperson.cpp

HEADERS  += mainwindow.h \
    person.h \
    machine.h \
    personmachine.h \
    utilities.h \
    data.h \
    constants.h \
    services.h \
    editpersondialog.h \
    addpersondialog.h \
    addmachinedialog.h \
    typesystem.h \
    editmachinedialog.h
    connecttomachine.h \
    connecttoperson.h

FORMS    += mainwindow.ui \
    editpersondialog.ui \
    addpersondialog.ui \
    addmachinedialog.ui \
    editmachinedialog.ui
    connecttomachine.ui \
    connecttoperson.ui

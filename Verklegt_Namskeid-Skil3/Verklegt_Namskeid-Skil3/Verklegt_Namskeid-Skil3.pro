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
    models/person.cpp \
    models/machine.cpp \
    models/personmachine.cpp \
    data/data.cpp \
    domain/services.cpp \
    utilities/utilities.cpp \
    ui/editpersondialog.cpp \
    ui/addpersondialog.cpp \
    ui/addmachinedialog.cpp \
    models/typesystem.cpp \
    ui/editmachinedialog.cpp \
    ui/connecttomachine.cpp \
    ui/connecttoperson.cpp \
    mainconnections.cpp \
    mainmachines.cpp \
    mainperson.cpp \
    ui/addconnectiondialog.cpp \
    data/dataperson.cpp \
    data/datamachine.cpp \
    data/dataconnection.cpp \
    data/datatypesystem.cpp \
    maintype.cpp \
    ui/addtypesystemdialog.cpp \
    ui/edittypesystemdialog.cpp \
    mainsystem.cpp \
    domain/servicesperson.cpp \
    domain/servicesmachine.cpp \
    domain/servicesconnection.cpp \
    domain/servicestypesystem.cpp

HEADERS  += mainwindow.h \
    models/person.h \
    models/machine.h \
    models/personmachine.h \
    utilities/utilities.h \
    data/data.h \
    utilities/constants.h \
    domain/services.h \
    ui/editpersondialog.h \
    ui/addpersondialog.h \
    ui/addmachinedialog.h \
    models/typesystem.h \
    ui/editmachinedialog.h \
    ui/connecttomachine.h \
    ui/connecttoperson.h \
    ui/addconnectiondialog.h \
    ui/addtypesystemdialog.h \
    ui/edittypesystemdialog.h

FORMS    += mainwindow.ui \
    ui/editpersondialog.ui \
    ui/addpersondialog.ui \
    ui/addmachinedialog.ui \
    ui/editmachinedialog.ui \
    ui/connecttomachine.ui \
    ui/connecttoperson.ui \
    ui/addconnectiondialog.ui \
    ui/addtypesystemdialog.ui \
    ui/edittypesystemdialog.ui

RESOURCES += \
    resources.qrc

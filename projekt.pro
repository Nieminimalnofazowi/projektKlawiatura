#-------------------------------------------------
#
# Project created by QtCreator 2015-03-24T10:58:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = projekt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    user.cpp

HEADERS  += mainwindow.h \
    user.h

FORMS    += mainwindow.ui

RESOURCES += resources.qrc

QMAKE_LFLAGS += -static-libgcc

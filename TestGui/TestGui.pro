#-------------------------------------------------
#
# Project created by QtCreator 2016-11-12T15:41:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestGui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    plot.cpp

HEADERS  += mainwindow.h \
    plot.h \
    defines.h

FORMS    += mainwindow.ui

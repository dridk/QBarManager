#-------------------------------------------------
#
# Project created by QtCreator 2013-01-08T21:16:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qbar
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    blackberrymanager.cpp \
    barpackagemodel.cpp

HEADERS  += mainwindow.h \
    blackberrymanager.h \
    barpackagemodel.h

FORMS    += mainwindow.ui

RESOURCES += \
    gfx/gfx.qrc

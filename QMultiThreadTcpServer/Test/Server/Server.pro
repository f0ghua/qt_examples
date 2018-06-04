#-------------------------------------------------
#
# Project created by QtCreator 2016-09-09T14:18:16
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Server
TEMPLATE = app

CONFIG(debug, debug|release) {
    LIBS += -L../../lib/ -lStaServerd
} else {
    LIBS += -L../../lib/ -lStaServer
}

INCLUDEPATH += -I ../../include/

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

#-------------------------------------------------
#
# Project created by QtCreator 2012-06-23T12:30:29
#
#-------------------------------------------------

QT       += core gui widgets

unix:QMAKE_CXXFLAGS += -std=c++0x

TARGET = IHex
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    chexwidget.cpp \
    chexfile.cpp \
    ihexline.cpp \
    ihexfile.cpp

HEADERS  += mainwindow.h \
    chexwidget.h \
    chexfile.h \
    ihexline.h \
    ihexfile.h

FORMS    += mainwindow.ui

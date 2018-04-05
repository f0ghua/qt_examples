#-------------------------------------------------
#
# Project created by QtCreator 2018-03-22T19:47:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtWStudy
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h

FORMS += \
        mainwindow.ui

include(..\QtXSLed\xsled.pri)

#QtXSLed_PKG = .\QtXSLed
#INCLUDEPATH += $$QtXSLed_PKG
#HEADERS += $$QtXSLed_PKG/xsled.h
#SOURCES += $$QtXSLed_PKG/xsled.cpp

#top_srcdir = $$PWD
#LIBS += -L$$top_srcdir\QtXSLed -lxsledplugin

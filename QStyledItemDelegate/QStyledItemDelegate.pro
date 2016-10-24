#-------------------------------------------------
#
# Project created by QtCreator 2016-10-24T20:17:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QStyledItemDelegate
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    XHierarchicalHeaderView.cpp \
    XIGBConfigModel.cpp \
    XIGBMsgDelegate.cpp \
    XIGBSignalDelegate.cpp

HEADERS  += mainwindow.h \
    XHierarchicalHeaderView.h \
    XIGBConfigModel.h \
    XIGBMsgDelegate.h \
    XIGBSignalDelegate.h

FORMS    += mainwindow.ui

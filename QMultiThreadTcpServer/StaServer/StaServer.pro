#-------------------------------------------------
#
# Project created by QtCreator 2016-09-06T09:07:31
#
#-------------------------------------------------

QT       += network sql
QT       -= gui

CONFIG(debug, debug|release) {
    TARGET = StaServerd
} else {
    TARGET = StaServer
}

TEMPLATE = lib

INCLUDEPATH += -I private

DEFINES += STASERVER_LIBRARY

SOURCES += StaServer.cpp \
    private/StaServerPrivate_p.cpp \
    private/ThreadPoolEngine.cpp \
    private/TaskManager.cpp \
    private/TaskManagerPrivate_p.cpp \
    private/ThreadPoolEnginePrivate_p.cpp \
    private/StaClient.cpp \
    private/StaClientPrivate_p.cpp

HEADERS += StaServer.h\
        staserver_global.h \
    private/StaServerPrivate_p.h \
    private/ThreadPoolEngine.h \
    private/TaskManager.h \
    private/TaskManagerPrivate_p.h \
    private/ThreadPoolEnginePrivate_p.h \
    private/StaClient.h \
    private/StaClientPrivate_p.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DESTDIR = bin
UI_DIR = build/.ui
MOC_DIR = build/.moc
RCC_DIR = build/.qrc
OBJECTS_DIR = build/.obj

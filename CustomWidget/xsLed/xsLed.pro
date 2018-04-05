CONFIG      += plugin debug_and_release
TARGET      = $$qtLibraryTarget(xsledplugin)
TEMPLATE    = lib

HEADERS     = xsledplugin.h

SOURCES     = xsledplugin.cpp

RESOURCES   = icons.qrc
LIBS        += -L. #-lxsled

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += designer
} else {
    CONFIG += designer
}

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

include(..\QtXSLed\xsled.pri)

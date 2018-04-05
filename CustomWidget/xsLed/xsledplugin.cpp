#include "xsled.h"
#include "xsledplugin.h"

#include <QtPlugin>

XSLedPlugin::XSLedPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void XSLedPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool XSLedPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *XSLedPlugin::createWidget(QWidget *parent)
{
    return new XSLed(parent);
}

QString XSLedPlugin::name() const
{
    return QLatin1String("XSLed");
}

QString XSLedPlugin::group() const
{
    return QLatin1String("Led Widgets");
}

QIcon XSLedPlugin::icon() const
{
    return QIcon();
}

QString XSLedPlugin::toolTip() const
{
    return QLatin1String("Led Custom widget Plugin for Qt Designer");
}

QString XSLedPlugin::whatsThis() const
{
    return QLatin1String("Led Custom widget Plugin for Qt Designer");
}

bool XSLedPlugin::isContainer() const
{
    return false;
}

QString XSLedPlugin::domXml() const
{
    return QLatin1String("<widget class=\"XSLed\" name=\"xSLed\">\n</widget>\n");
}

QString XSLedPlugin::includeFile() const
{
    return QLatin1String("xsled.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(xsledplugin, XSLedPlugin)
#endif // QT_VERSION < 0x050000

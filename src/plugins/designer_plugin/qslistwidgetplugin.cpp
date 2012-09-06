#include "qslistwidget.h"
#include "qslistwidgetplugin.h"

#include <QtPlugin>

QSListWidgetPlugin::QSListWidgetPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void QSListWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;
    
    // Add extension registrations, etc. here
    
    m_initialized = true;
}

bool QSListWidgetPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *QSListWidgetPlugin::createWidget(QWidget *parent)
{
    return new QSListWidget(parent);
}

QString QSListWidgetPlugin::name() const
{
    return QLatin1String("QSListWidget");
}

QString QSListWidgetPlugin::group() const
{
    return QLatin1String("SWidgets");
}

QIcon QSListWidgetPlugin::icon() const
{
    return QIcon();
}

QString QSListWidgetPlugin::toolTip() const
{
    return QLatin1String("");
}

QString QSListWidgetPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool QSListWidgetPlugin::isContainer() const
{
    return false;
}

QString QSListWidgetPlugin::domXml() const
{
    return QLatin1String("<widget class=\"QSListWidget\" name=\"qSListWidget\">\n</widget>\n");
}

QString QSListWidgetPlugin::includeFile() const
{
    return QLatin1String("qslistwidget.h");
}


#include "qsellineedit.h"
#include "qsellineeditplugin.h"

#include <QtPlugin>

QSelLineEditPlugin::QSelLineEditPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void QSelLineEditPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;
    
    // Add extension registrations, etc. here
    
    m_initialized = true;
}

bool QSelLineEditPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *QSelLineEditPlugin::createWidget(QWidget *parent)
{
    return new QSelLineEdit(parent);
}

QString QSelLineEditPlugin::name() const
{
    return QLatin1String("QSelLineEdit");
}

QString QSelLineEditPlugin::group() const
{
    return QLatin1String("");
}

QIcon QSelLineEditPlugin::icon() const
{
    return QIcon();
}

QString QSelLineEditPlugin::toolTip() const
{
    return QLatin1String("");
}

QString QSelLineEditPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool QSelLineEditPlugin::isContainer() const
{
    return false;
}

QString QSelLineEditPlugin::domXml() const
{
    return QLatin1String("<widget class=\"QSelLineEdit\" name=\"qSelLineEdit\">\n</widget>\n");
}

QString QSelLineEditPlugin::includeFile() const
{
    return QLatin1String("qsellineedit.h");
}


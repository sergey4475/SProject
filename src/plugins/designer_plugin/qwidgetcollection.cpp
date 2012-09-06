#include "qsellineeditplugin.h"
#include "qslistwidgetplugin.h"
#include "qwidgetcollection.h"

qWidgetCollection::qWidgetCollection(QObject *parent)
    : QObject(parent)
{
    m_widgets.append(new QSelLineEditPlugin(this));
    m_widgets.append(new QSListWidgetPlugin(this));
}

QList<QDesignerCustomWidgetInterface*> qWidgetCollection::customWidgets() const
{
    return m_widgets;
}

Q_EXPORT_PLUGIN2(qwidgetcollectionplugin, qWidgetCollection)

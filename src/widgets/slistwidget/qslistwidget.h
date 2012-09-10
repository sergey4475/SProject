#ifndef QSLISTWIDGET_H
#define QSLISTWIDGET_H

#include <QListWidget>
#include <s_global.h>

#include <xml>

class Q_S_EXPORT sListWidgetItem : public QListWidgetItem
{
public:
    sListWidgetItem(const QString &text, xmlItem xItem);
    sListWidgetItem(const QIcon &icon, const QString &text,xmlItem xItem);
    xmlItem GetXmlItem();
private:
    xmlItem xmlObj;
};

class Q_S_EXPORT QSListWidget : public QListWidget
{
    Q_OBJECT
    Q_ENUMS(type_element)
public:
    enum type_element{
        Fields,
        Table
    };

    QSListWidget(QWidget *parent = 0);
    sListWidgetItem* CurrentItem();
    sListWidgetItem *itemFromIndex_(const QModelIndex &index) const;
    void LoadObject(xmlItem obj,type_element type = Fields);

private:
    XMLProc *p_xml;
    QListWidget *list;
    QWidget *m_parent;
};

#endif


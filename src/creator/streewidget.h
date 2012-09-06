#ifndef STREEWIDGET_H
#define STREEWIDGET_H

#include <QTreeWidget>
#include <QMenu>
#include <xml>
#include "general.h"

class sTreeWidgetItem : public QTreeWidgetItem
{
public:
    sTreeWidgetItem(QString strings, xmlItem xItem);
    sTreeWidgetItem(QString strings);
    xmlItem GetXmlItem();
private:
    xmlItem xmlObj;
    enum t_menu{mSpravochniki, mSpravochnik, mForm, mField, mTField, mDocs, mDoc};
};

class sTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    void Init(QWidget *frame = 0){
        m_frame= frame;
}
//    void loadSpravichniki(xmlItem xItem,sTreeWidgetItem *parent);
//    void loadDocuments(xmlItem xItem,sTreeWidgetItem *parent);

    sTreeWidget(QWidget *parent = 0);
    void loadTree(XMLProc *xml, int mdc);
    sTreeWidgetItem* CurrentItem();
    sTreeWidgetItem *itemFromIndex_(const QModelIndex &index) const;
    QMenu* GetMenu();
private:
    QWidget *m_parent;
    QWidget *m_frame;
    //XMLProc *p_xml;
    QMenu *context_menu;
    QMenu* newMenu(xmlItem obj);
    bool KeyField(xmlItem xItem,QString attr);

//    void loadFields(xmlItem xItem, sTreeWidgetItem *parent);
//    void loadForms(xmlItem xItem, sTreeWidgetItem *parent);
//    void loadTables(xmlItem xItem, sTreeWidgetItem *parent);
    void removeItem(sTreeWidgetItem *item);

    void NewSpravochnik(xmlItem xItem,QString name);
    //sTreeWidgetItem *p_item;
//    xmlItem md, iface, p_xItem, p_xSubItem, p_Fields, p_Forms;

public slots:
    void ContextMenu(const QPoint & point);
    void ClickItem(QModelIndex index);
    void DoubleClickItem(QModelIndex index);
    void NewObjMd();
    void NewElement();
    void NewForm();

    void EditElement();
    void EditDocument();

    void DelElement();
};

#endif // STREEWIDGET_H

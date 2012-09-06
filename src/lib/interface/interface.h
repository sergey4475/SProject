#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>
#include <QTabWidget>
#include <QStackedWidget>
#include "lib_global.h"
#include <xml>
#include <QVBoxLayout>
#include <QtUiTools/QUiLoader>

class sEngine;

class LIBSHARED_EXPORT Contaner : QObject{
public:
    xmlItem p_Item;
    QString p_form;
    Contaner(xmlItem id);
};

class LIBSHARED_EXPORT interface : public QWidget
{
    Q_OBJECT
public:
    explicit interface(xmlItem xml_item, sEngine *enging, QWidget *parent = 0);
    ~interface();
signals:
    
public slots:

private:
    void CreateWidgets();
    xmlItem xml_root;
    int currentTab;
    XMLProc xml;
    sEngine *eng;
    QUiLoader UIload;
    QTabWidget *root;
    QMultiMap<int,QStackedWidget*> listWindow;
    QMultiMap<QObject*,int>list;

private slots:
    void on_clicked_item();
    void on_clicked_tab(int index);

};

#endif // INTERFACE_H

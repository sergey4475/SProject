#ifndef FRMDOCUMENT_H
#define FRMDOCUMENT_H

#include <QWidget>
#include "streewidget.h"
#include "general.h"
#include "ui_frmdocument.h"

class frmDocument : public QWidget
{
    Q_OBJECT
    
public:
    explicit frmDocument(XMLProc *xml,QWidget *parent = 0);
    ~frmDocument();
    void getData(xmlItem item);
    
private:
    Ui::frmDocument *ui;
//    void init();
//    XMLProc *p_xml;
//    xmlItem md;
//    xmlItem xmlCurrentItem;
    xmlItem general, element, field;
    xmlItem data;
    void EditElement();

public slots:
    void DoubleClickItem(QModelIndex index);

};

#endif // FRMDOCUMENT_H

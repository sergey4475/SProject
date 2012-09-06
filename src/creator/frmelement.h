#ifndef FRMELEMENT_H
#define FRMELEMENT_H

#include <QWidget>
#include <xml>
#include <QDebug>

namespace Ui {
class frmElement;
}

class frmElement : public QWidget
{
    Q_OBJECT
    
public:
    explicit frmElement(XMLProc *xml,QWidget *parent = 0);
    ~frmElement();
    void getData(xmlItem item);
    
private slots:


    void on_saveButton_clicked();

private:
    Ui::frmElement *ui;
    void init();
    XMLProc *p_xml;
    xmlItem md;
    xmlItem xmlCurrentItem;
};

#endif // FRMELEMENT_H

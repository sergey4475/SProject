#include "frmdocument.h"
#include <widgets>
#include "ui_frmdocument.h"
#include "frmelement.h"

frmDocument::frmDocument(XMLProc *xml,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmDocument)
{
    ui->setupUi(this);
    p_xml = xml;
    connect(ui->lstFields,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(DoubleClickItem(QModelIndex)));
    connect(ui->lstTblFields,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(DoubleClickItem(QModelIndex)));

}

frmDocument::~frmDocument()
{

}

void frmDocument::getData(QDomElement item){
    ui->name_->setText(p_xml->attr(item,mda_name));
    ui->lstFields->LoadObject(item,ui->lstFields->Fields);
    ui->lstTblFields->LoadObject(item,ui->lstTblFields->Table);
}

void frmDocument::DoubleClickItem(QModelIndex index){
    xmlItem item = ((QSListWidget*)sender())->itemFromIndex_(index)->GetXmlItem();
    qDebug() << item.nodeName();
    if (item.nodeName() == md_field){
        EditElement();
    }
}

// Редактирование элемента
void frmDocument::EditElement(){
    xmlItem item = ((QSListWidget*)sender())->CurrentItem()->GetXmlItem();

    frmElement *frmEl = new frmElement(p_xml);
    frmEl->getData(item);
    frmEl->show();
}


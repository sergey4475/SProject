#include "frmdocument.h"
#include <widgets>
#include "ui_frmdocument.h"

frmDocument::frmDocument(XMLProc *xml,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmDocument)
{
    ui->setupUi(this);
    p_xml = xml;
}

frmDocument::~frmDocument()
{

}

void frmDocument::getData(QDomElement item){
    ui->name_->setText(p_xml->attr(item,mda_name));
    ui->listWidget->LoadObject(item,ui->listWidget->Fields);
    ui->qSListWidget->LoadObject(item,ui->listWidget->Table);
}

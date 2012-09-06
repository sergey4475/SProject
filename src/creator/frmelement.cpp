#include "frmelement.h"
#include "ui_frmelement.h"

frmElement::frmElement(XMLProc *xml, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmElement)
{
    ui->setupUi(this);
    p_xml = xml;
    init();
}

frmElement::~frmElement()
{
    delete ui;
}

void frmElement::init(){
    ui->typeElement->clear();
    ui->typeElement->addItem("Строка","S 150 0");
    ui->typeElement->addItem("Число","N 10 0");
    ui->typeElement->addItem("Дата","D ");
    ui->typeElement->addItem("Булево","B ");
    md = p_xml->find(mdc_metadata);
    xmlItem context = p_xml->find(md,md_spravochniki,0);
    xmlItem obj;
    int i, n;
    long oid;
    QString tobject;

    if ( context.isNull() ) return;
    tobject = md_spravochnik;
    n = p_xml->count( context, tobject );
    for (i=0; i<n; i++) {
        obj = p_xml->find(context, md_spravochnik, i);
        if ( !obj.isNull() ) {
            oid = p_xml->id( obj );
            if ( oid ) {
                ui->typeElement->addItem(tobject+QString(".")+p_xml->attr( obj, mda_name ),QString("L ")+QString::number(oid));
            }
        }
    }
}

void frmElement::getData(xmlItem item){
    xmlCurrentItem = item;
    QString ts;
    char t =' ';
    int oid=0, w=0, d=0;
    ts = p_xml->attr(item, mda_type);
    ui->NameElement->setText(p_xml->attr(item, mda_name));

    if ( !ts.isEmpty() )
    {
        sscanf(ts.toAscii(), "%c %d %d", &t, &w, &d );
    }
    else
    {
        t = 'S';
        w = 150;
    }

    if ( t=='L' ) {
        for(int i = 0 ; i < ui->typeElement->count(); i++ ) {
            if( ui->typeElement->itemData(i).toString()[0] == 'L' ) {
                sscanf(ui->typeElement->itemData(i).toString().toAscii(), "L %d", &oid );
                if ( oid == w ) {
                     ui->typeElement->setCurrentIndex(i);
                     break;
                }
            }
        }
    } else {
         if ( t == ' ' ) ui->typeElement->setCurrentIndex(-1);
         if ( t == 'S' )
         {

             ui->width->setMaximum(254);
             ui->decimal->setMaximum(99);
             ui->decimal->setEnabled(false);
             ui->typeElement->setCurrentIndex(0);
         }

         if ( t == 'N' )
         {
            ui->width->setMaximum(20);
            ui->decimal->setMaximum(99);
            ui->decimal->setEnabled(true);
            ui->typeElement->setCurrentIndex(1);
         }
         if ( t == 'D' ) ui->typeElement->setCurrentIndex(2);
         if ( t == 'B' ) ui->typeElement->setCurrentIndex(3);
         ui->width->setValue( w );
         ui->decimal->setValue( d );
    }

}

void frmElement::on_saveButton_clicked()
{

    QString ts;
    char t =' ';
    int w=ui->width->value();
    int oid = 0;
    int d=ui->decimal->value();

    ts = ui->typeElement->itemData(ui->typeElement->currentIndex()).toString();
    sscanf(ts.toAscii(), "%c %d", &t, &oid);

    if (t=='L')
        ts = QString("%1 %2").arg(t).arg(oid);
    else
        ts = QString("%1 %2 %3").arg(t).arg(w).arg(d);

    p_xml->setAttr(xmlCurrentItem,mda_name,ui->NameElement->text());
    p_xml->setAttr(xmlCurrentItem,mda_type,ts);
    close();
}

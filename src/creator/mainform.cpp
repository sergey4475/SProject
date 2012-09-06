#include "mainform.h"
#include <QMessageBox>
#include <QDebug>

mainForm::mainForm(QWidget *parent) :
    QMainWindow(parent)
{
    ui.setupUi(this);

    xml = new XMLProc();
    xml->ReadXML(QApplication::applicationDirPath()+"/ifase_.xml");
    ui.treeWidget->loadTree(xml,mdc_metadata);
    ui.treeWidget->Init(ui.frame);
    ui.interface_tree->loadTree(xml,mdc_interface);

}

mainForm::~mainForm()
{
    if (xml->GetModify()){
        if (QMessageBox::question(0,"Внимание!!!","Конфигурация была изменена. Сохранить изменения?",QMessageBox::Yes,QMessageBox::No)== QMessageBox::Yes){
            on_saveConf_triggered();
        }
    }
}

void mainForm::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui.retranslateUi(this);
        break;
    default:
        break;
    }
}

void mainForm::on_saveConf_triggered()
{
    xml->write(QApplication::applicationDirPath()+"/ifase_.xml");
}

void mainForm::on_mainForm_destroyed()
{
}

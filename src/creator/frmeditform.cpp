#include "frmeditform.h"
#include "ui_frmeditform.h"

frmEditForm::frmEditForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmEditForm)
{
    ui->setupUi(this);
}

frmEditForm::~frmEditForm()
{
    delete ui;
}

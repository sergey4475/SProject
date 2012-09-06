#ifndef FRMEDITFORM_H
#define FRMEDITFORM_H

#include <QWidget>

namespace Ui {
class frmEditForm;
}

class frmEditForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit frmEditForm(QWidget *parent = 0);
    ~frmEditForm();
    
private:
    Ui::frmEditForm *ui;
};

#endif // FRMEDITFORM_H

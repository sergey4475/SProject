#ifndef MAINFORM_H
#define MAINFORM_H

#include "ui_mainform.h"
#include "streewidget.h"

class mainForm : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit mainForm(QWidget *parent = 0);
    ~mainForm();
    XMLProc *xml;
protected:
    void changeEvent(QEvent *e);

private slots:
    void on_saveConf_triggered();

    void on_mainForm_destroyed();

private:
    Ui::mainForm ui;
};

#endif // MAINFORM_H

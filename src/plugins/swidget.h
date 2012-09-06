#ifndef SWIDGET_H
#define SWIDGET_H

#include <QWidget>

class sWidget : public QWidget
{
    Q_OBJECT
public:
    explicit sWidget(QWidget *parent = 0);
    
signals:
    
public slots:
    void	show(); //depricated
    void	close(); //depricated

    
};

#endif // SWIDGET_H

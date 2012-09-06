#ifndef FILTEREDIT_H
#define FILTEREDIT_H

#include <QVBoxLayout>
#include <QDate>
#include <QWidget>
#include <QKeyEvent>
#include "s_global.h"
#include <QToolButton>
#include <QLineEdit>

class Q_S_EXPORT QSelLineEdit : public QWidget
{
Q_OBJECT
    Q_PROPERTY(bool buttonVisible READ buttonIsVisible WRITE setButtonVisible)
    Q_PROPERTY(Type_Select type_select READ t_select WRITE set_t_select)
    // Параметры вводимого числа
    Q_PROPERTY(int length READ Length WRITE SetLength)
    Q_PROPERTY(int digit READ Digit WRITE SetDigit)

    Q_ENUMS(Type_Select)

public:
    enum Type_Select{
        Values,
        Calendare,
        Nothing
    };

    explicit QSelLineEdit(QWidget *parent = 0);
    bool buttonIsVisible();

    // Установка параметров
    void SetLength(int length) {m_length = length; updateControl();}
    void SetDigit(int digit) {m_digit = digit; updateControl();}

    void set_t_select(Type_Select type_select);

    const QDate date() {return QDate::fromString(qleEdit->text(),"dd.MM.yyyy");}
    void setDateCalendar(QDate date);

    // Функция возвращает число
    double Value(){ return qleEdit->text().toDouble();}

private:
    QLineEdit *qleEdit;
    QToolButton *button;
    bool visible;
    Type_Select m_select;
    int m_length;
    int m_digit;
    bool f_dec;

    void createControls();
    void setConnects();
    void slotCalendar();
    void updateControl();
    // Получение параметров вводимого числа (длина, точность)
    int Digit(){return m_digit;}
    int Length(){return m_length;}

    Type_Select t_select() const { return m_select; }

    virtual bool eventFilter(QObject *obj, QEvent *event);

public slots:
    void setButtonVisible(bool);
    void buttonClick();

private slots:
    void slotTextChanged(const QString& text);
    void setDate(const QDate date);
    void slotCheckValidate();

signals:
    void dateChanged(QDate &Date);
    void editingFinished();
    void buttonClicked();

protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif // FILTEREDIT_H


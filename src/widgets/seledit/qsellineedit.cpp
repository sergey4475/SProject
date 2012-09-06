#include "qsellineedit.h"
#include <QCalendarWidget>
#include <QRegExpValidator>
#include <QMessageBox>

QSelLineEdit::QSelLineEdit(QWidget *parent) :
    QWidget(parent)
{
    m_digit = 2;
    m_length= 10;
    f_dec = false;

    qleEdit= new QLineEdit(this);

    button=new QToolButton(this);
    button->setCursor(Qt::ArrowCursor);
    button->setGeometry(0,0,15,15);

    QHBoxLayout* qhblLayout=new QHBoxLayout(this);

    qhblLayout->addWidget(qleEdit);

    qhblLayout->addWidget(button);
    qhblLayout->setContentsMargins(0,0,0,0);
    qhblLayout->setSpacing(0);

    this->setLayout(qhblLayout);

    setConnects();
    updateControl();
}

void QSelLineEdit::set_t_select(Type_Select type_select){
    m_select = type_select;
    updateControl();
}

void QSelLineEdit::updateControl(){
    setButtonVisible(false);
    qleEdit->setAlignment(Qt::AlignLeft);
    if (m_select == Calendare){
        // Если параметр ввода даты
        qleEdit->removeEventFilter(this);
        button->setIcon(QIcon(":calendar.png"));
        qleEdit->setInputMask("00.00.0000");
        setButtonVisible(true);
    }else if (m_select == Nothing){

        qleEdit->setInputMask("");
        qleEdit->removeEventFilter(this);
        button->setText("...");
        button->setIcon(QIcon::fromTheme("edit-clear"));
        setButtonVisible(true);
    }else{
        // Если параметр ввода числа
        qleEdit->setAlignment(Qt::AlignRight);
        qleEdit->setInputMask("");
        qleEdit->installEventFilter(this);
        qleEdit->setValidator(new QDoubleValidator(0,0,m_digit,this));
        button->setIcon(QIcon::fromTheme("edit-clear"));
    }
    button->setStyleSheet("border: solid 1px black;");
}

void QSelLineEdit::setConnects(){
    connect(qleEdit,SIGNAL(editingFinished()),this,SLOT(slotCheckValidate()));
    connect(qleEdit,SIGNAL(textChanged(const QString&)),this,SLOT(slotTextChanged(const QString&)));
    connect(button,SIGNAL(clicked()),this,SLOT(buttonClick()));
}

void QSelLineEdit::slotTextChanged(const QString& text)
{
    if (m_select == Calendare){
        QStringList qslTmp=text.split(".");
        if (qslTmp.at(0).toInt()>31 || qslTmp.at(0).toInt()>QDate(qslTmp.at(2).toInt(),qslTmp.at(1).toInt(),01) .daysInMonth())
        {
                qleEdit->setCursorPosition(0);
                qleEdit->setSelection(0,2);
        }
        if (qslTmp.at(1).toInt()>12)
        {
                qleEdit->setCursorPosition(3);
                qleEdit->setSelection(3,2);
        }
        QDate date=QDate::fromString(qleEdit->text(),"dd.MM.yyyy");
        if (date.isValid())
                emit dateChanged(date);
    }
}

void QSelLineEdit::slotCalendar(){
    QCalendarWidget* qcwCalendar=new QCalendarWidget(this);
    qcwCalendar->setWindowFlags(Qt::Popup);
    qcwCalendar->setAttribute(Qt::WA_DeleteOnClose);
    QObject::connect(qcwCalendar, SIGNAL(clicked(QDate)), this, SLOT(setDate(QDate)));
    QObject::connect(qcwCalendar, SIGNAL(clicked(QDate)), qcwCalendar, SLOT(close()));

    QPoint pos = (this->layoutDirection() == Qt::RightToLeft) ? this->rect().bottomRight() : this->rect().bottomLeft();
    pos = this->mapToGlobal(pos);
    qcwCalendar->move(pos);
    qcwCalendar->setSelectedDate(QDate().fromString(qleEdit->text(),"dd.MM.yyyy"));
    qcwCalendar->show();
}

void QSelLineEdit::buttonClick()
{
    if (m_select == Calendare){
        slotCalendar();
    }else
        emit buttonClicked();

}

void QSelLineEdit::setDate(QDate date)
{
        if (date.isValid())
                qleEdit->setText(date.toString("dd.MM.yyyy"));
}

void QSelLineEdit::setDateCalendar(QDate date){
    if (date.isValid())
            qleEdit->setText(date.toString("dd.MM.yyyy"));
}

void QSelLineEdit::slotCheckValidate()
{
        QDate date=QDate::fromString(qleEdit->text(),"dd.MM.yyyy");
        if (!date.isValid())
        {
                if (qleEdit->text()!="..")
                {
                        qleEdit->setFocus();
                        qleEdit->setCursorPosition(0);
                }
                else
                {
                        emit editingFinished();
                }
        }
        else
                emit editingFinished();
}

void QSelLineEdit::keyPressEvent(QKeyEvent *event){
    QWidget::keyPressEvent(event);
}

// Отбираем события по нажатию клавиш.
// Фильтруем только числовые и "."
// Если длина строки привысила допустимой то печатем дробную часть
bool QSelLineEdit::eventFilter(QObject *obj, QEvent *event){
    if(event->type() == QEvent::KeyPress){
        QKeyEvent *pKeyEvent = static_cast<QKeyEvent *>(event);
        if ((pKeyEvent->key() >= Qt::Key_0 && pKeyEvent->key() <= Qt::Key_9)||(pKeyEvent->text()==".")){
            if ((qleEdit->text().indexOf(".",0,Qt::CaseInsensitive) == -1)&&(qleEdit->text().length() >= m_length)) {
                qleEdit->setText(qleEdit->text()+".");
            }
        }
    }
    return QWidget::eventFilter(obj, event);
}

void QSelLineEdit::setButtonVisible(bool v){
    visible = v;
    button->setVisible(v);
}

bool QSelLineEdit::buttonIsVisible(){
    return visible;
}

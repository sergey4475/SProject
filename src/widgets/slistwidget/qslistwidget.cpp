#include "qslistwidget.h"
#include <QVBoxLayout>

sListWidgetItem::sListWidgetItem(const QString &text,xmlItem xItem){
    setText(text);
    xmlObj = xItem;
}

sListWidgetItem::sListWidgetItem(const QIcon &icon, const QString &text, xmlItem xItem){
    setIcon(icon);
    setText(text);
    xmlObj = xItem;
}

xmlItem sListWidgetItem::GetXmlItem(){
    return xmlObj;
}


QSListWidget::QSListWidget(QWidget *parent): QListWidget(parent)
{
    m_parent = parent;
}

sListWidgetItem* QSListWidget::CurrentItem(){
    return (sListWidgetItem *) this->currentItem();
}

void QSListWidget::LoadObject(xmlItem obj, type_element type){
    QString nField, nVisible;
    xmlItem element;

    if (type == Fields)
        element = p_xml->findChild(obj,md_element);
    else if (type == Table){
        element = p_xml->findChild(obj,md_tables);
        element = p_xml->findChild(element,md_table);
    }
    // ОБходим элементы объекта
    while(!element.isNull()){
        xmlItem field = p_xml->findChild(element,md_field);
        // Обходи реквизиты объекта
        while(!field.isNull()){
            nField  = p_xml->attr(field,mda_name);
            nVisible= p_xml->attr(field,mda_visible);
            if (nVisible != "0"){
                addItem(new sListWidgetItem(nField,field));
            }
            field = p_xml->nextSibling(field);
        }
        element = p_xml->nextSibling(element);
    }
}

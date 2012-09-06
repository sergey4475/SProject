#include "general.h"

void loadDocuments(xmlItem xItem,sTreeWidgetItem *parent,bool find){
    if (find)
        p_xSubItem = p_xml->find(xItem,md_document);
    else
        p_xSubItem = xItem;

    while(!p_xSubItem.isNull()){
        QString name =  p_xml->attr(p_xSubItem,mda_name);
        sTreeWidgetItem *el = new sTreeWidgetItem(name,p_xSubItem);
        parent->addChild(el);

        loadFields(p_xSubItem, el);
        loadTables(p_xSubItem, el);
        loadForms(p_xSubItem, el);

        p_xSubItem = p_xml->nextSibling(p_xSubItem);
    }
}

// Загрузка справочников
void loadSpravichniki(xmlItem xItem,sTreeWidgetItem *parent){
    p_xSubItem = p_xml->find(xItem,md_spravochnik);
    while(!p_xSubItem.isNull()){
        QString name =  p_xml->attr(p_xSubItem,mda_name);
        sTreeWidgetItem *el = new sTreeWidgetItem(name,p_xSubItem);
        parent->addChild(el);

        loadFields(p_xSubItem, el);
        loadForms(p_xSubItem, el);

        p_xSubItem = p_xml->nextSibling(p_xSubItem);
    }
}


void loadFields(xmlItem xItem, sTreeWidgetItem *parent){
    xmlItem Xel = p_xml->findChild(xItem,md_element);

    sTreeWidgetItem *el = new sTreeWidgetItem(QObject::tr("Реквизиты"),Xel);
    parent->addChild(el);

    p_Fields = p_xml->findChild(p_xml->findChild(xItem,md_element),md_field);
    while(!p_Fields.isNull()){
        if (p_xml->attr(p_Fields,mda_visible)!="0"){
            QString name =  p_xml->attr(p_Fields,mda_name);
            el->addChild(new sTreeWidgetItem(name,p_Fields));
            parent->addChild(el);
        }
        p_Fields = p_xml->nextSibling(p_Fields);
    }
}

void loadForms(xmlItem xItem, sTreeWidgetItem *parent){
    xmlItem Xel = p_xml->findChild(xItem,md_forms);
    sTreeWidgetItem *el = new sTreeWidgetItem(QObject::tr("Формы"),Xel);
    parent->addChild(el);

    p_Forms = p_xml->find(p_xml->findChild(xItem,md_forms),md_form);

    while(!p_Forms.isNull()){
        QString name =  p_xml->attr(p_Forms,mda_name);
        el->addChild(new sTreeWidgetItem(name,p_Forms));
        parent->addChild(el);
        p_Forms = p_xml->nextSibling(p_Forms);
    }
}

void loadTables(xmlItem xItem, sTreeWidgetItem *parent){
    xmlItem Xel = p_xml->findChild(xItem,md_tables);
    sTreeWidgetItem *el = new sTreeWidgetItem(QObject::tr("Табличные части"),Xel);
    parent->addChild(el);

    p_Fields = p_xml->findChild(p_xml->findChild(xItem,md_tables),md_table);

    while(!p_Fields.isNull()){
        QString name =  p_xml->attr(p_Fields,mda_name);
        el->addChild(new sTreeWidgetItem(name,p_Fields));
        parent->addChild(el);
        p_Fields = p_xml->nextSibling(p_Fields);
    }
}

#include "streewidget.h"
#include <QDebug>
#include <QModelIndex>
#include <QMouseEvent>
#include <QMenu>
#include "frmelement.h"
#include "frmdocument.h"

sTreeWidget::sTreeWidget(QWidget *parent)
{
    m_parent = parent;
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this,SIGNAL(customContextMenuRequested(const QPoint & )),this,SLOT(ContextMenu(const QPoint & )));
    connect(this,SIGNAL(clicked(QModelIndex)),this,SLOT(ClickItem(QModelIndex)));
    connect(this,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(DoubleClickItem(QModelIndex)));

}

bool sTreeWidget::KeyField(QDomElement xItem, QString attr){
    if (p_xml->attr(xItem,mda_key) == "1" || p_xml->attr(xItem,mda_key)== "2")
        return true;
    return false;
}

void sTreeWidget::loadTree(XMLProc *xml,int mdc){
    p_xml = xml;
    if (mdc == mdc_metadata){
    // Загрузка метаданных
    md = p_xml->find(mdc_metadata);
    if (!md.isNull()){

        // Справочники
        p_xItem = p_xml->find(md,md_spravochniki,0);

        if(p_xItem.isNull()){
            p_xml->insert(md,md_spravochniki,QString::null,-1);
        }
        sTreeWidgetItem *el = new sTreeWidgetItem(QObject::tr("Справочники"),p_xItem);
        addTopLevelItem(el);
        loadSpravichniki(p_xItem,el);

        // Документы
        p_xItem = p_xml->find(md,md_documents,0);

        if(p_xItem.isNull()){
            p_xml->insert(md,md_documents,QString::null,-1);
            p_xItem = p_xml->find(md,md_documents,0);
        }
        sTreeWidgetItem *docs = new sTreeWidgetItem(QObject::tr("Документы"),p_xItem);
        addTopLevelItem(docs);
        loadDocuments(p_xItem,docs);

        //Регистры
        p_xItem = p_xml->find(md,md_registers,0);
        if(p_xItem.isNull()){
            p_xml->insert(md,md_registers,QString::null,-1);
            p_xItem = p_xml->find(md,md_registers,0);
        }
        addTopLevelItem(new sTreeWidgetItem(QObject::tr("Регистры"),p_xItem));
    }
    }

    if (mdc == mdc_interface){
    // Загрузка дерева интерфейса
    iface = p_xml->find(mdc_interface);
    if (!iface.isNull()){
        QString name, type, title, image;
        xmlItem ifTabs  = p_xml->findChild(iface,md_tabs);
        xmlItem tabItem;
        // обходим разделы tabs
        while (!ifTabs.isNull()){
            sTreeWidgetItem *grIface = new sTreeWidgetItem(QObject::tr("Разделы меню"),ifTabs);
            addTopLevelItem(grIface);
            tabItem = p_xml->find(ifTabs,md_tab);
            // обходим все вкладки (tab)
            while(!tabItem.isNull()){
                name = p_xml->attr(tabItem,mda_name);
                type = p_xml->attr(tabItem,mda_type);
                title = p_xml->attr(tabItem,mda_title);
                image = p_xml->attr(tabItem,mda_image);
                sTreeWidgetItem *tab = new sTreeWidgetItem(title,ifTabs);
                grIface->addChild(tab);
                // Группы меню
                xmlItem lMenu = p_xml->findChild(tabItem,md_left_menu);
                xmlItem grMenu= p_xml->findChild(lMenu,md_group);
                while (!grMenu.isNull()){
                    title = p_xml->attr(grMenu,mda_title);
                    sTreeWidgetItem *grM = new sTreeWidgetItem(title,grMenu);
                    tab->addChild(grM);
                    grMenu = p_xml->nextSibling(grMenu);
                }
                tabItem = p_xml->nextSibling(tabItem);
            }
            ifTabs = p_xml->nextSibling(ifTabs);
        }
    }
    }
}

//**************************************Slots
// Контекстное меню
void sTreeWidget::ContextMenu(const QPoint &point){
    QMenu* menu;
    sTreeWidgetItem *it = (sTreeWidgetItem*) this->itemAt(point);
    xmlItem xm = it->GetXmlItem();
    menu = newMenu(xm);

    menu->exec(QCursor::pos());
}

// Одиночное нажатие на элемент дерева
void sTreeWidget::ClickItem(QModelIndex index){
    this->itemFromIndex(index)->text(0);
}

// Двойное нажатие на элемент дерева
void sTreeWidget::DoubleClickItem(QModelIndex index){
    xmlItem item = this->itemFromIndex_(index)->GetXmlItem();
    if (item.nodeName() == md_document){
        EditDocument();
    }

    if (item.nodeName() == md_field){
        EditElement();
    }
    if (item.nodeName() == md_form){
        EditElement();
    }
}

// Создание нового объекта
void sTreeWidget::NewSpravochnik(QDomElement xItem, QString name){

}

// mda_key; key=1 Поле ключевое
void sTreeWidget::NewObjMd(){
    sTreeWidgetItem *it;
    xmlItem r;
    if (CurrentItem()->GetXmlItem().nodeName() == md_spravochniki){
        xmlItem spr = p_xml->findChild(md,md_spravochniki);

        // Справочник
        spr = p_xml->insert(spr,md_spravochnik,"Новый справочник",0);
        it = new sTreeWidgetItem("Новый справочник",spr);

        // Реквизиты
        xmlItem el = p_xml->insert(spr,md_element,QString::null,-1);
        it->addChild(new sTreeWidgetItem("Реквизиты",el));

        // Формы
        xmlItem frm = p_xml->insert(spr,md_forms,QString::null,-1);
        it->addChild(new sTreeWidgetItem("Формы",frm));

        // Ключевые поля
        if (el.nodeName() == md_element){
            r = p_xml->insert(el,md_field,"Код",0);
            p_xml->setAttr(r,mda_type,"S 10 0");
            p_xml->setAttr(r,mda_width,"10");
            p_xml->setAttr(r,mda_key,"2");
            p_xml->setAttr(r,mda_visible,"0");

            r = p_xml->insert(el,md_field,"Наименование",0);
            p_xml->setAttr(r,mda_type,"S 50 0");
            p_xml->setAttr(r,mda_width,"50");
            p_xml->setAttr(r,mda_key,"1");
            p_xml->setAttr(r,mda_visible,"0");
        }

    }
    if (CurrentItem()->GetXmlItem().nodeName() == md_documents){
        xmlItem doc = p_xml->findChild(md,md_documents);
        // Документ
        doc = p_xml->insert(doc,md_document,"Новый документ",0);
        it = new sTreeWidgetItem("Новый документ",doc);

        // Реквизиты
        xmlItem el = p_xml->insert(doc,md_element,QString::null,-1);
        it->addChild(new sTreeWidgetItem("Шапка",el));

        // Табличные части
        xmlItem tbel = p_xml->insert(doc,md_tables,QString::null,-1);
        it->addChild(new sTreeWidgetItem("Таблицы",tbel));

        // Формы
        xmlItem frm = p_xml->insert(doc,md_forms,QString::null,-1);
        it->addChild(new sTreeWidgetItem("Формы",frm));

        // Ключевые поля
        if (el.nodeName() == md_element){
            r = p_xml->insert(el,md_field,"Номер",0);
            p_xml->setAttr(r,mda_type,"S 10 0");
            p_xml->setAttr(r,mda_width,"10");
            p_xml->setAttr(r,mda_key,"2");
            p_xml->setAttr(r,mda_visible,"0");

            r = p_xml->insert(el,md_field,"Дата",0);
            p_xml->setAttr(r,mda_type,"D");
            p_xml->setAttr(r,mda_width,"10");
            p_xml->setAttr(r,mda_key,"1");
            p_xml->setAttr(r,mda_visible,"0");
        }

    }
    CurrentItem()->addChild(it);
}

// Создание нового элемента
void sTreeWidget::NewElement(){
    sTreeWidgetItem *it;
    xmlItem item = CurrentItem()->GetXmlItem();
    xmlItem r;
    if (item.nodeName() == md_element){
        r = p_xml->insert(item,md_field,"Реквизит",0);
        p_xml->setAttr(r,mda_type,"S 10 2");
        p_xml->setAttr(r,mda_width,"10");
        it = new sTreeWidgetItem("Реквизит",r);
        it->setExpanded(true);
    }
    CurrentItem()->addChild(it);
    frmElement *frmEl = new frmElement(p_xml);
    frmEl->getData(r);
    frmEl->show();
}

// Создание новой формы
// types: 1-Форма списка, 2-Форма объекта, 3-Форма выбора
void sTreeWidget::NewForm(){
    sTreeWidgetItem *it;
    xmlItem item = CurrentItem()->GetXmlItem();
    xmlItem frm, temp;
    if (item.nodeName() == md_forms){
        qDebug() << item.nodeName();
        frm = p_xml->insert(item,md_form,"Новая Форма",0);
        p_xml->setAttr(frm,mda_type,"2");
        p_xml->setAttr(frm,mda_readonly,false);

        temp = p_xml->insert(frm,md_description,QString::null,0);
        temp = p_xml->insert(frm,md_sourcecode,QString::null,0);
        temp = p_xml->insert(frm,md_defaultmod,QString::null,0);
        temp = p_xml->insert(frm,md_formdesign,QString::null,0);

        it = new sTreeWidgetItem("Новая Форма",frm);
        it->setExpanded(true);
    }
//    CurrentItem()->addChild(it);
//    frmElement *frmEl = new frmElement(p_xml);
//    frmEl->getData(r);
//    frmEl->show();
}


// Редактирование элемента
void sTreeWidget::EditElement(){
    xmlItem item = CurrentItem()->GetXmlItem();
    frmElement *frmEl = new frmElement(p_xml);
    frmEl->getData(item);
    frmEl->show();
}

// Редактирование документа
void sTreeWidget::EditDocument(){
    xmlItem item = CurrentItem()->GetXmlItem();
    frmDocument *frmDoc = new frmDocument(p_xml,m_frame);
    frmDoc->show();
    frmDoc->getData(item);
}


//Удаление
void sTreeWidget::DelElement(){
    xmlItem item = CurrentItem()->GetXmlItem();
    p_xml->remove(item);
    removeItem(CurrentItem());
}

//***********************************************************************//


//****
//// Загрузка справочников
//void sTreeWidget::loadSpravichniki(xmlItem xItem,sTreeWidgetItem *parent){
//    p_xSubItem = p_xml->find(xItem,md_spravochnik);
//    while(!p_xSubItem.isNull()){
//        QString name =  p_xml->attr(p_xSubItem,mda_name);
//        sTreeWidgetItem *el = new sTreeWidgetItem(name,p_xSubItem);
//        parent->addChild(el);

//        loadFields(p_xSubItem, el);
//        loadForms(p_xSubItem, el);

//        p_xSubItem = p_xml->nextSibling(p_xSubItem);
//    }
//}

//// Загрузка документов
//void sTreeWidget::loadDocuments(xmlItem xItem,sTreeWidgetItem *parent){
//    p_xSubItem = p_xml->find(xItem,md_document);
//    while(!p_xSubItem.isNull()){
//        QString name =  p_xml->attr(p_xSubItem,mda_name);
//        sTreeWidgetItem *el = new sTreeWidgetItem(name,p_xSubItem);
//        parent->addChild(el);

//        loadFields(p_xSubItem, el);
//        loadTables(p_xSubItem, el);
//        loadForms(p_xSubItem, el);

//        p_xSubItem = p_xml->nextSibling(p_xSubItem);
//    }
//}

void sTreeWidget::removeItem(sTreeWidgetItem *item){
    CurrentItem()->parent()->removeChild(item);
}

//void sTreeWidget::loadFields(xmlItem xItem, sTreeWidgetItem *parent){
//    xmlItem Xel = p_xml->findChild(xItem,md_element);

//    sTreeWidgetItem *el = new sTreeWidgetItem(QObject::tr("Реквизиты"),Xel);
//    parent->addChild(el);

//    p_Fields = p_xml->findChild(p_xml->findChild(xItem,md_element),md_field);
//    while(!p_Fields.isNull()){
//        if (p_xml->attr(p_Fields,mda_visible)!="0"){
//            QString name =  p_xml->attr(p_Fields,mda_name);
//            el->addChild(new sTreeWidgetItem(name,p_Fields));
//            parent->addChild(el);
//        }
//        p_Fields = p_xml->nextSibling(p_Fields);
//    }
//}

//void sTreeWidget::loadForms(xmlItem xItem, sTreeWidgetItem *parent){
//    xmlItem Xel = p_xml->findChild(xItem,md_forms);
//    sTreeWidgetItem *el = new sTreeWidgetItem(QObject::tr("Формы"),Xel);
//    parent->addChild(el);

//    p_Forms = p_xml->find(p_xml->findChild(xItem,md_forms),md_form);

//    while(!p_Forms.isNull()){
//        QString name =  p_xml->attr(p_Forms,mda_name);
//        el->addChild(new sTreeWidgetItem(name,p_Forms));
//        parent->addChild(el);
//        p_Forms = p_xml->nextSibling(p_Forms);
//    }
//}

//void sTreeWidget::loadTables(xmlItem xItem, sTreeWidgetItem *parent){
//    xmlItem Xel = p_xml->findChild(xItem,md_tables);
//    sTreeWidgetItem *el = new sTreeWidgetItem(QObject::tr("Табличные части"),Xel);
//    parent->addChild(el);

//    p_Fields = p_xml->findChild(p_xml->findChild(xItem,md_tables),md_table);

//    while(!p_Fields.isNull()){
//        QString name =  p_xml->attr(p_Fields,mda_name);
//        el->addChild(new sTreeWidgetItem(name,p_Fields));
//        parent->addChild(el);
//        p_Fields = p_xml->nextSibling(p_Fields);
//    }
//}


sTreeWidgetItem* sTreeWidget::CurrentItem(){
    return (sTreeWidgetItem *) this->currentItem();
}

sTreeWidgetItem* sTreeWidget::itemFromIndex_(const QModelIndex &index) const{
    return (sTreeWidgetItem *) this->itemFromIndex(index);
}

xmlItem sTreeWidgetItem::GetXmlItem(){
    return xmlObj;
}

QMenu * sTreeWidget::GetMenu(){
    return context_menu;
}


sTreeWidgetItem::sTreeWidgetItem(QString strings,xmlItem xItem){
    setText(0,strings);
    xmlObj = xItem;
}

sTreeWidgetItem::sTreeWidgetItem(QString strings){
    setText(0,strings);
}

QMenu* sTreeWidget::newMenu(xmlItem obj){
    QMenu* menu = new QMenu;
    qDebug() << obj.nodeName();
    if(obj.nodeName() == md_spravochniki){
        QAction *act = new QAction("Новый справочник..",this);
        connect(act,SIGNAL(triggered()),this,SLOT(NewObjMd()));
        menu->addAction(act);
    }

    if(obj.nodeName() == md_documents){
        QAction *act = new QAction("Новый документ..",this);
        connect(act,SIGNAL(triggered()),this,SLOT(NewObjMd()));
        menu->addAction(act);
    }

    if(obj.nodeName() == md_element){
        QAction *act = new QAction("Добавить",this);
        connect(act,SIGNAL(triggered()),this,SLOT(NewElement()));
        menu->addAction(act);
    }

    if(obj.nodeName() == md_forms){
        QAction *act = new QAction("Добавить",this);
        connect(act,SIGNAL(triggered()),this,SLOT(NewForm()));
        menu->addAction(act);
    }


    if(obj.nodeName() == md_field){
        QAction *edit = new QAction("Редактировать",this);
        connect(edit,SIGNAL(triggered()),this,SLOT(EditElement()));
        menu->addAction(edit);

        QAction *del = new QAction("Удалить",this);
        connect(del,SIGNAL(triggered()),this,SLOT(DelElement()));
        menu->addAction(del);
    }

    return menu;
}


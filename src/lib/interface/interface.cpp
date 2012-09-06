#include "interface.h"
#include "scripts.h"
#include <iisTaskPanel>
#include <QDebug>
#include <QGroupBox>

Contaner::Contaner(xmlItem id){
    p_Item  = id;
    //p_form  = form;
}

interface::interface(QDomElement xml_item, sEngine *enging, QWidget *parent) :
    QWidget(parent)
{
    setParent(parent);
    eng = enging;
    xml_root = xml_item;
    CreateWidgets();
}

interface::~interface(){
     UIload.~QUiLoader();
}

void interface::CreateWidgets(){
    QString name, type, title, wight, image, id, act;

    xmlItem childItem;
    xmlItem md          = xml.find(xml_root,md_metadata);
    xmlItem ifTabs      = xml.find(xml_root,md_tabs);
    xmlItem itActions   = xml.find(xml_root,md_actions);

    currentTab = 0;
    int idTab = 0;
    int idVal = 0;
    while (!ifTabs.isNull()){
        name = xml.attr(ifTabs,mda_name);
        type = xml.attr(ifTabs,mda_type);
        title = xml.attr(ifTabs,mda_title);

        QGridLayout *l = new QGridLayout(this);
        QTabWidget *root = new QTabWidget;

        l->addWidget(root);
        connect(root,SIGNAL(currentChanged(int)),this,SLOT(on_clicked_tab(int)));
        //Создаем вкладки разделов
        childItem = xml.find(ifTabs,md_tab);

        while (!childItem.isNull()){
            name = xml.attr(childItem,mda_name);
            type = xml.attr(childItem,mda_type);
            title = xml.attr(childItem,mda_title);
            image = xml.attr(childItem,mda_image);
            QWidget *Tab = UIload.createWidget(type,root,name);
            Tab->setObjectName(name);
            QIcon ic(":/"+image);
            root->setIconSize(QSize(50,50));
            root->addTab(Tab,ic,title);

            QHBoxLayout *vb = new QHBoxLayout(Tab);

            QStackedWidget *stWidget = new QStackedWidget();
            listWindow.insert(idTab,stWidget);
            idTab++;
            //idVal = 0;

            // Создаем левое меню
            xmlItem childrenItem = xml.find(childItem,md_left_menu,0);
            while (!childrenItem.isNull() && childrenItem.nodeName() == md_left_menu){
                name = xml.attr(childrenItem,mda_name);
                type = xml.attr(childrenItem,mda_type);
                title = xml.attr(childrenItem,mda_title);
                wight = xml.attr(childrenItem,mda_width);

                iisTaskPanel *tskPanel = new iisTaskPanel(Tab);
                if (!wight.isEmpty())
                    tskPanel->setMinimumWidth(wight.toInt());

                vb->addWidget(tskPanel,0);
                vb->setAlignment(tskPanel,Qt::AlignLeft);
                // Группы меню
                tskPanel->layout()->setAlignment(Qt::AlignTop);
                xmlItem xmlGr = xml.find(childrenItem,md_group);
                while (!xmlGr.isNull()){
                    name = xml.attr(xmlGr,mda_name);
                    type = xml.attr(xmlGr,mda_type);
                    title = xml.attr(xmlGr,mda_title);


                    //QGroupBox *Gr = new QGroupBox(name,prev);
                    iisTaskBox *Gr = new iisTaskBox(title);
                    tskPanel->addWidget(Gr);
                    Gr->setObjectName(name);

                    //Элементы меню
                    xmlItem xmlValue = xml.find(xmlGr,md_value);
                    while (!xmlValue.isNull()){
                        name    = xml.attr(xmlValue,mda_name);
                        id      = xml.attr(xmlValue,mda_id);
                        title   = xml.attr(xmlValue,mda_title);
                        act     = xml.sText(xmlValue,md_comaction);

                        iisIconLabel *val = new iisIconLabel(title);
                        val->setObjectName(name);
                        connect(val,SIGNAL(clicked()),this,SLOT(on_clicked_item()));
                        Gr->addIconLabel(val);
                        list.insert(val,idVal);

                        xmlItem iact = xml.findId(itActions,"",act);
                        xmlItem iObj, iFrm;
                        if (!iact.isNull()){
                            QString idObj = xml.sText(iact,md_objectid);
                            xmlItem tmp =  xml.firstChild(md);
                            while (!tmp.isNull()){
                                iObj = xml.findId(tmp,"",idObj);
                                tmp = xml.nextSibling(tmp);
                                if (!iObj.isNull()) break;
                            }
                        }
                        if (!iObj.isNull()){
                            QString idFrm = xml.sText(iact,md_formid);
                            iObj = xml.find(iObj,md_forms);
                            iFrm = xml.findId(iObj,"",idFrm);
                            // Создаем форму
                            QWidget *form =eng->OpenForm(iFrm);
                            if (form){
                                stWidget->insertWidget(idVal,form);
                                idVal++;
                            }
                        }

                        xmlValue = xml.nextSibling(xmlValue);
                    }

                    xmlGr = xml.nextSibling(xmlGr);
                }
                childrenItem = xml.nextSibling(childrenItem);
            }


            // Правая панель
            childrenItem = xml.find(childItem,md_panel);
            while (!childrenItem.isNull()){
                name = xml.attr(childrenItem,mda_name);
                type = xml.attr(childrenItem,mda_type);
                title = xml.attr(childrenItem,mda_title);
                wight = xml.attr(childrenItem,mda_width);
                if (!wight.isEmpty())
                    stWidget->setMinimumWidth(wight.toInt());
                stWidget->setObjectName(name);
                stWidget->setFrameStyle(1);
                stWidget->setFrameShadow(QFrame::Raised);
                vb->addWidget(stWidget,2);

                childrenItem = xml.nextSibling(childrenItem);
            }
            childItem = xml.nextSibling(childItem);
        }
        ifTabs = xml.nextSibling(ifTabs);
    }

}

void interface::on_clicked_item(){
    iisIconLabel * btn = dynamic_cast<iisIconLabel*>(sender());
    int id = list.find(btn).value();
    QStackedWidget *st = listWindow.find(currentTab).value();
    st->setCurrentIndex(id);
}

void interface::on_clicked_tab(int index){
    currentTab = index;
}

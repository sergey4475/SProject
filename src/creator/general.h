#ifndef GENERAL_H
#define GENERAL_H

#include <streewidget.h>
#include <xml>

class sTreeWidgetItem;
class XMLProc;

static XMLProc *p_xml;

static xmlItem md, iface, p_xItem, p_xSubItem, p_Fields, p_Forms;

 void loadSpravichniki(xmlItem xItem,sTreeWidgetItem *parent);
 void loadDocuments(xmlItem xItem,sTreeWidgetItem *parent,bool find = true);

 void loadFields(xmlItem xItem, sTreeWidgetItem *parent);
 void loadForms(xmlItem xItem, sTreeWidgetItem *parent);
 void loadTables(xmlItem xItem, sTreeWidgetItem *parent);


#endif // GENERAL_H

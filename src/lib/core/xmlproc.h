#ifndef XMLPROC_H
#define XMLPROC_H

#include <QObject>
#include <QtXml/qdom.h>
#include <QMap>
#include <QFile>
#include "lib_global.h"

#define RC_OK		0	//Рузультат ошибок нет
#define RC_ERROR	1	//Результат ошибка


#define mdc_unknown		0	/**< Unknown context */
#define mdc_root		1	/**< Root context */
#define mdc_info		2	/**< Info context */
#define mdc_interface	3	/**< Interface context */
#define mdc_metadata	4	/**< Metadata context */
#define mdc_globals		5	/**< Metadata context */
#define mdc_actions		6	/**< Actions context */


// Теги метаданных
#define md_root             "configuration"
#define md_interface		"interface"
#define md_tabs             "tabs"
#define md_tab              "tab"
#define md_info             "info"
#define md_info_name 		"name"
#define md_info_author 		"author"
#define md_info_date 		"date"
#define md_info_mdate 		"mdate"
#define md_info_remark 		"remark"
#define md_info_lastid 		"lastid"
#define md_metadata 		"metadata"
#define md_group            "group"
#define md_globals          "globals"
#define md_sourcecode       "sourcecode"
#define md_languages		"languages"
#define md_language         "language"
#define md_aliases          "aliases"
#define md_alias            "alias"
#define md_roles            "roles"
#define md_role             "role"
#define md_panel            "panel"
#define md_left_menu        "left_menu"
#define md_value            "value"


#define md_documents	"documents"
#define md_document		"document"

#define md_spravochniki	"spravochniki"
#define md_spravochnik	"spravochnik"
#define md_element		"element"
#define md_group		"group"

#define md_string_view	"string_view"
#define md_svfunction	"svfunction"

#define md_registers	"registers"
#define md_iregisters	"iregisters"
#define md_iregister	"iregister"
#define md_aregisters	"aregisters"
#define md_aregister	"aregister"

#define md_reports		"reports"
#define md_report		"report"

#define md_journals		"journals"
#define md_journal		"journal"
#define md_columns		"columns"
#define md_column		"column"
#define md_used_doc		"used_doc"
#define md_fieldid		"fieldid"

#define md_field		"field"
#define md_forms		"forms"
#define md_form			"form"
#define md_defaultmod	"defaultmod"
#define md_webforms		"webforms"
#define md_webform		"webform"
#define md_formdesign	"dialogform"
#define md_description  "description"

#define md_tables		"tables"
#define md_table		"table"
#define md_header		"header"

#define md_resources	"resources"
#define md_dimensions	"dimensions"
#define md_information	"information"

#define md_comaction	"comaction"

/*!
Action metadata object items.
*/
#define md_actions		"actions"
#define md_actiongroup	"actiongroup"
#define md_action		"action"
#define md_objectid		"objectid"
#define md_formid		"formid"
#define md_actiontype		"actiontype"
#define md_active_picture	"active_picture"
#define md_passive_picture	"passive_picture"


// Атрибуты
#define mda_key 		"key"
#define mda_name		"name"
#define mda_object		"object"
#define mda_class		"class"
#define mda_id		    "id"
#define mda_type		"type"
#define mda_readonly	"readonly"
#define mda_lang		"lang"
#define mda_nz		    "nz"
#define mda_sort		"sort"
#define mda_no_unconduct "no_unconduct"
#define mda_plus		"plus"
#define mda_sum			"sum"
#define mda_title	    "title"
#define mda_tag			"tag"
#define mda_image		"image"
#define mda_visible		"visible"
#define mda_trfile		"trfile"
#define mda_length		"length"
#define mda_format		"format"
#define mda_stdf		"stdf"
#define mda_rights		"rights"
#define mda_width       "width"

#define xmlItem 		QDomElement

#define context_startid	100

class LIBSHARED_EXPORT ItemContaner: public QObject
{
public:
    long id;
    xmlItem item;
    ItemContaner(long newid, xmlItem newitem);
};

class LIBSHARED_EXPORT XMLProc : public QObject
{
    Q_OBJECT

public:
    XMLProc(QObject *parent = 0);
    ~XMLProc();
    int ReadXML(const QString &fname);
    int write(QDomDocument doc, const QString &fname);
    int write(const QString &fname);
    QString objClass( long id );
    QString objClass( xmlItem context );
    QMap<int,ItemContaner*> idcache;
    QString attr(xmlItem context, const QString &name);
    QString text(xmlItem context);
    QString info(const QString &name);
    void setInfo(const QString &name, const QString &value);
    void setText(xmlItem context, const QString &value);
    int count(xmlItem context, const QString &classname);
    long id(xmlItem context);
    QStringList addType();

    QByteArray toHex(xmlItem context);
    QByteArray fromHex(xmlItem context);
    QByteArray toHex(QString context);
    QByteArray fromHex(QString context);

    QString sText(xmlItem context, const QString & subname );
    xmlItem findChild(QDomElement context, const QString &classname, int n = 0 );
    xmlItem find(xmlItem context, const QString &name, int n = 0 );
    xmlItem find(int id);
    xmlItem find(const QString &name);
    xmlItem findName(xmlItem context, const QString &classname, const QString &name );
    xmlItem findId(xmlItem context, const QString &classname, const QString &id );
    xmlItem firstChild(xmlItem context );
    xmlItem nextSibling(xmlItem context);
    int countChild(xmlItem context);

    long nextID();
    void createNew();
    xmlItem insert(xmlItem context, const QString &otype, const QString &name, long id);
    void remove(xmlItem context);
    void setAttr(xmlItem context, const QString &name, const QString &value);
    void setAttr(xmlItem context, const QString &name, int value);

    bool GetModify();
    void SetModify(bool mode);
private:

    QDomElement rootnode, cfginfo, md, iface, actions;
    QDomDocument xml;

    void init();
    bool modify;
signals:

public slots:

};
#endif // XMLPROC_H

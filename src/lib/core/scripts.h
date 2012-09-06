#ifndef SCRIPTS_H
#define SCRIPTS_H

#include <QObject>
#include <QtScript>
#include <QUiLoader>
#include <QtSql/qsql.h>
#include "xmlproc.h"
#include "lib_global.h"

#define sDataBase QSqlDatabase

class XMLProc;

class LIBSHARED_EXPORT sEngine : public QObject
{
    Q_OBJECT
public:
    int 		next_obj_id;

    sEngine(XMLProc *xml);
    virtual	~sEngine();
    void on_systemstart();
//    void on_systemstop();

private:
    QString pr_timer;
    QString mGlobal;
    QList <QVariant> values;
    QScriptEngine *code;
    XMLProc     *md;
    QUiLoader UI;

public slots:
    QString Time();
    QString Date();
    void ExitApp();
    QWidget* OpenForm(xmlItem item);
    void Message(int n, const QString &msg);
//	void StatusMessage( const QString &msg );
//	void settimer(int sec, QString proc);
//	aForm * OpenForm(QString fname, int mode=0, aObject * selecter=0);//Q_ULLONG ido=0);
//	QVariant value( const QString &name );
//	void setValue( const QString &name, QVariant value = QVariant::Invalid );


};

#endif // SCRIPTS_H

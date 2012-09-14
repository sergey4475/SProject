#include "db_lib_global.h"


QChar toLower(QChar c)
{
    return c.toLower();
}

QString
toLower(const QString &s)
{
    return s.toLower();
}

char toAscii(QChar c)
{
    return c.toAscii();
}

int indexOf( const QString &str, const QString &find_str )
{
    return str.indexOf( find_str );
}

const char * toLocal8Bit(const QString &s)
{
    return s.toLocal8Bit().data();
}

QStringList split(const QString &div, const QString &str )
{
    return str.split( div );
}

QString trimm(const QString &str ) {
    return str.trimmed();
}


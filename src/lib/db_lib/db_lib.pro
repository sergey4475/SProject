#-------------------------------------------------
#
# Project created by QtCreator 2012-09-14T12:58:39
#
#-------------------------------------------------

QT       += sql xml

QT       -= gui

CONFIG += dll
VERSION=1.1.0
TARGET = $$qtLibraryTarget(db_lib)

TARGET = db_lib
TEMPLATE = lib

DEFINES += DB_LIB_LIBRARY

DESTDIR = ../../../build/bin/lib

SOURCES += db_lib.cpp \
    db_drivers.cpp \
    db_lib_global.cpp \
    db_driver_mysql.cpp

HEADERS += db_lib.h\
        db_lib_global.h \
    db_drivers.h \
    db_driver_mysql.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE5F3B232
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = db_lib.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

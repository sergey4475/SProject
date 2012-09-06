QT += xml gui
TEMPLATE = lib

VERSION = 1.0.10

DEFINES += LIB_LIBRARY
TARGET = $$qtLibraryTarget(widgets)

CONFIG(debug, debug|release){
    LIBS += -L../../build/bin/lib -lcored1
}
else{
    LIBS += -L../../build/bin/lib -lcore1
}

INCLUDEPATH += ./
INCLUDEPATH += ../include

DESTDIR = ../../build/bin/lib

include(seledit/seledit.pri)
include(slistwidget/slistwidget.pri)

HEADERS += \
    s_global.h

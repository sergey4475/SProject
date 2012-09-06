QT       += gui xml script scripttools

include(../config.pri)

CONFIG   += uitools shared

TEMPLATE = lib

TARGET = $$qtLibraryTarget(iface)

CONFIG(debug, debug|release){
    LIBS += -L../../../build/bin/lib -lcored1
}
else{
    LIBS += -L../../../build/bin/lib -lcore1
}

INCLUDEPATH += ../../include \
               ../../lib \
               ../core

DESTDIR = ../../../build/bin/lib

SOURCES += interface.cpp

HEADERS += interface.h

RESOURCES += \
    res.qrc


include(iispanel/iispanel.pri)

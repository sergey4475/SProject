QT  += xml script scripttools
QT  -= gui qt

include(../config.pri)

CONFIG   += uitools shared

INCLUDEPATH += ../../include \
               ../../lib
TEMPLATE = lib

TARGET = $$qtLibraryTarget(core)

DESTDIR = ../../../build/bin/lib
SOURCES += xmlproc.cpp \
    scripts.cpp

HEADERS += xmlproc.h\
           scripts.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE3CF487C
    TARGET.CAPABILITY =
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = lib.dll
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

#include(interface/interface.pri)
include(metadata/metadata.pri)

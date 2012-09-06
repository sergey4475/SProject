#-------------------------------------------------
#
# Project created by QtCreator 2012-06-17T23:57:57
#
#-------------------------------------------------

QT       += core gui xml script scripttools

CONFIG += sWidgets

INCLUDEPATH += ../lib
INCLUDEPATH += ../include
INCLUDEPATH += ../widgets

CONFIG(debug, debug|release){
    LIBS += -L../../build/bin/lib -lcored1
    LIBS += -L../../build/bin/lib -lwidgetsd1
}
else{
    LIBS += -L../../build/bin/lib -lcore1
    LIBS += -L../../build/bin/lib -lwidgets1
}

TARGET = creator
TEMPLATE = app

DESTDIR = ../../build/bin

SOURCES += main.cpp\
        mainform.cpp \
    streewidget.cpp \
    frmelement.cpp \
    frmeditform.cpp \
    frmdocument.cpp \
    general.cpp

HEADERS  += mainform.h \
    streewidget.h \
    frmelement.h \
    frmeditform.h \
    frmdocument.h \
    general.h

FORMS    += mainform.ui \
    frmelement.ui \
    frmeditform.ui \
    frmdocument.ui

RESOURCES += \
    creator_res.qrc

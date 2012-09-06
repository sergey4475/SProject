QT       += core xml gui script

INCLUDEPATH +=  ../lib/core \
                ../lib/interface \
                ../include

CONFIG   += uitools

CONFIG(debug, debug|release){
    LIBS += -L../../build/bin/lib -lcored1 \
            -L../../build/bin/lib -lifaced1
}
else{
    LIBS += -L../../build/bin/lib -lcore1 \
            -L../../build/bin/lib -liface1
}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = XMLForms
TEMPLATE = app

DESTDIR = ../../build/bin

SOURCES += main.cpp\

FORMS    +=

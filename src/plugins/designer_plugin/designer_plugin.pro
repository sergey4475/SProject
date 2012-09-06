CONFIG      += designer plugin debug_and_release
TARGET      = $$qtLibraryTarget(qwidgetcollectionplugin)
TEMPLATE    = lib

INCLUDEPATH += ../../widgets \
               ../../widgets/seledit \
               ../../widgets/slistwidget \
               ../../include

HEADERS     = qsellineeditplugin.h qwidgetcollection.h qslistwidgetplugin.h
SOURCES     = qsellineeditplugin.cpp qwidgetcollection.cpp qslistwidgetplugin.cpp
RESOURCES   = icons.qrc
LIBS        += -L../../../build/bin/lib -lwidgets1

DESTDIR = $$[QT_INSTALL_PLUGINS]/designer

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target



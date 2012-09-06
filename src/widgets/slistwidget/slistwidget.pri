#TEMPLATE = lib

contains(TARGET, plugin){
    HEADERS += ../plugins/designer_plugin/qslistwidgetplugin.h
    SOURCES += ../plugins/designer_plugin/qslistwidgetplugin.cpp
}else{
    HEADERS += slistwidget/qslistwidget.h
    SOURCES += slistwidget/qslistwidget.cpp
}

#TARGET = widget

INCLUDEPATH += ../../include


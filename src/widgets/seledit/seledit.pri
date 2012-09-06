#TEMPLATE = lib
contains(TARGET, plugin){
    HEADERS += ../plugins/designer_plugin/qsellineeditplugin.h
    SOURCES += ../plugins/designer_plugin/qsellineeditplugin.cpp
}else{
    HEADERS += seledit/qsellineedit.h
    SOURCES += seledit/qsellineedit.cpp
}



#TARGET = widget

INCLUDEPATH += ../../include

RESOURCES += \
    seledit/res.qrc

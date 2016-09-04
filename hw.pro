#-------------------------------------------------
#
# Project created by QtCreator 2015-12-11T16:38:57
#
#-------------------------------------------------

QT       += core gui webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = hw
TEMPLATE = app


SOURCES += main.cpp\
    lib/utilsstd.cpp \
    lib/utils.cpp \
    lib/inifile.cpp \
    ui/cwebview.cpp \
    ui/cwindow.cpp \
    slots/cphpinterface.cpp \
    logic/cmetadata.cpp \
    lib/xml/cxml.cpp \
    logic/process/cprocess.cpp \
    ui/caction.cpp \
    lib/xml/cxmlattribbutes.cpp \
    slots/oslinux.cpp \
    slots/os.cpp \
    slots/oswindows.cpp

HEADERS  += \
    lib/utilsstd.h \
    lib/utils.h \
    lib/inifile.h \
    ui/cwebview.h \
    ui/cwindow.h \
    slots/cphpinterface.h \
    logic/cmetadata.h \
    lib/xml/cxml.h \
    logic/process/cprocess.h \
    ui/caction.h \
    lib/xml/cxmlattribbutes.h \
    slots/oslinux.h \
    slots/os.h \
    slots/oswindows.h

FORMS    +=

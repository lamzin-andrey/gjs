# -------------------------------------------------
# Project created by QtCreator 2015-12-11T16:38:57
# -------------------------------------------------
QT += webkit \
    sql \
    network
OBJECTS_DIR = build
MOC_DIR = build
SOURCES += main.cpp \
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
    ui/cwebpage.cpp \
    lib/binfile.cpp \
    logic/dssparser/php.cpp \
    logic/dssparser/DssParser.cpp \
    logic/dssparser/DssLine.cpp \
    lib/json/cjson.cpp
HEADERS += lib/utilsstd.h \
    lib/utils.h \
    lib/inifile.h \
    ui/cwebview.h \
    ui/cwindow.h \
    slots/cphpinterface.h \
    lib/xml/cxml.h \
    logic/process/cprocess.h \
    ui/caction.h \
    lib/xml/cxmlattribbutes.h \
    slots/oslinux.h \
    slots/os.h \
    ui/cwebpage.h \
    logic/cmetadata.h \
    lib/binfile.h \
    logic/dssparser/DssParser.h \
    logic/dssparser/DssLine.h \
    logic/dssparser/php.h \
    lib/json/cjson.h
RC_FILE = my.rc

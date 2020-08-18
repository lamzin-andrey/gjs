QT       += network webkit

SOURCES += main.cpp \
    lib/utilsstd.cpp \
    lib/utils.cpp \
    lib/inifile.cpp \
    lib/binfile.cpp \
    lib/json/cjson.cpp \
    lib/xml/cxmlattribbutes.cpp \
    lib/xml/cxml.cpp \
    logic/cmetadata.cpp \
    logic/process/cprocess.cpp \
    slots/oslinux.cpp \
    slots/os.cpp \
    slots/cphpinterface.cpp \
    ui/cwindow.cpp \
    ui/cwebview.cpp \
    ui/caction.cpp
HEADERS += lib/utilsstd.h \
    lib/utils.h \
    lib/inifile.h \
    lib/binfile.h \
    lib/json/cjson.h \
    lib/xml/cxmlattribbutes.h \
    lib/xml/cxml.h \
    logic/cmetadata.h \
    logic/process/cprocess.h \
    slots/oslinux.h \
    slots/os.h \
    slots/cphpinterface.h \
    ui/cwindow.h \
    ui/cwebview.h \
    ui/caction.h

OBJECT_DIR =  build

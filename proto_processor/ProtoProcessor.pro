QT -= gui
QT += core network serialport

INCLUDEPATH += usr/inc/
LIBS += usr/lib/ -ldata_comm

SOURCES += \
        DatagramComposerGLinkMap.cpp \
        IDatagramComposer.cpp \
        ProtoDataListener.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    DatagramComposerGLinkMap.h \
    IDatagramComposer.h \
    ProtoDataListener.h \
    VendorProtoTypes.h

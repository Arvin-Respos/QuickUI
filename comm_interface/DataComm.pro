QT -= gui
QT += network core serialport

TEMPLATE = lib
TARGET = data_comm

SOURCES += \
        CANSocketComm.cpp \
        CCommInterface.cpp \
        ConfigParse.cpp \
        IDataComm.cpp \
        SerialPortComm.cpp \
        UDPSocketComm.cpp

HEADERS += \
    CANSocketComm.h \
    CCommInterface.h \
    ConfigParse.h \
    DataCommProtoType.h \
    IDataComm.h \
    SerialPortComm.h \
    UDPSocketComm.h \
    include.h

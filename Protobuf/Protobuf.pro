QT += core
QT -= gui

TARGET = Protobuf
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    ../addressbook.pb.cc \
    Server.cpp \
    client.cpp

HEADERS += \
    ../addressbook.pb.h

DISTFILES += \
    ../addressbook.proto


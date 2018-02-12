QT += core
QT -= gui

TARGET = Protobuf
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    ../addressbook.pb.cc

HEADERS += \
    ../addressbook.pb.h

DISTFILES += \
    ../addressbook.proto


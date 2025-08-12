QT += core network sql
QT -= gui

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle


SOURCES += \
        src/Server.cpp \
        src/main.cpp \
        utils/Settings.cpp

HEADERS += \
    src/Server.h \
    utils/Settings.h

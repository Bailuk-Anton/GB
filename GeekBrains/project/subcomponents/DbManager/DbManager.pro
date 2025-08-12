QT -= gui
QT += sql network

TEMPLATE = lib
DEFINES += LIBDB_LIBRARY

CONFIG += c++11
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    src/dbManager.cpp

HEADERS += \
    src/dbManager.h \
    src/dbmanager_global.h

QT += core network sql
QT -= gui

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle

LIBS += -L/$$PWD/../../../debug/lib \
        -lDbManager

INCLUDEPATH += $$PWD/../../../debug/include \

SOURCES += \
        src/DbWatcher.cpp \
        src/TcpServer.cpp \
        src/main.cpp \
        utils/Settings.cpp

HEADERS += \
    src/DbWatcher.h \
    src/TcpServer.h \
    utils/Settings.h

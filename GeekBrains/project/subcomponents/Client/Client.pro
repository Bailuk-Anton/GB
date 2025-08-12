QT       += core network sql gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS


message("Libs: $$PWD/../../../debug/lib")
LIBS += -L/$$PWD/../../../debug/lib \
        -lDbManager

message("Include: $$PWD/../../../debug/lib")
INCLUDEPATH += $$PWD/../../../debug/include

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/widgets/BookingDialogs.cpp \
    src/widgets/EditDialog.cpp \
    src/widgets/PersonEditWidget.cpp \
    utils/Settings.cpp

HEADERS += \
    src/mainwindow.h \
    src/widgets/BookingDialogs.h \
    src/widgets/EditDialog.h \
    src/widgets/PersonEditWidget.h \
    utils/Settings.h \


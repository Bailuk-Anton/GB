QT       += core network sql gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS


SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/widgets/BookingDialogs.cpp \
    src/widgets/EditDialog.cpp \
    utils/Settings.cpp

HEADERS += \
    src/mainwindow.h \
    src/widgets/BookingDialogs.h \
    src/widgets/EditDialog.h \
    utils/Settings.h \

#FORMS += \
#    src/mainwindow.ui

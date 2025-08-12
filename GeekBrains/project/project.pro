TEMPLATE = subdirs

CONFIG  += ordered \
    qt

SUBDIRS += \
    # Installer \
    DbManager \
    Client \
    Server \

DbManager.subdir = subcomponents/DbManager
Client.subdir = subcomponents/Client
Server.subdir = subcomponents/Server

QT += widgets

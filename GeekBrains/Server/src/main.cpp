#include "utils/Settings.h"
#include <QCoreApplication>
#include <QDebug>
#include <iostream>

int main()
{
    qDebug() << "\n=========Server start\n==========\n";
    QCoreApplication a;
    a.setApplicationName( "Server" );
    a.setOrganizationName( "bylook" );
    return 0;
}

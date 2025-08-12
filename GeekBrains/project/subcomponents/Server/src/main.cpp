#include "src/TcpServer.h"
#include "utils/Settings.h"
#include <QCoreApplication>
#include <QDebug>
#include <iostream>

int main( int argc, char * argv[] )
{
    QCoreApplication a( argc, argv );
    a.setApplicationName( "Server" );
    a.setOrganizationName( "bylook" );
    TcpServer s( 1122 );
    return a.exec();
}

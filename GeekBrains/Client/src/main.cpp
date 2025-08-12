#include "mainwindow.h"
#include "utils/Settings.h"
#include <QApplication>
#include <QDebug>

int main( int argc, char * argv[] )
{
    qDebug() << "\n=========Client start==========\n";
    QApplication a( argc, argv );
    a.setApplicationName( "Server" );
    a.setOrganizationName( "bylook" );

    MainWindow w;
    w.show();
    return a.exec();
}

#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class Server
{
    void sendToDb();
    void sendToClient();

  public:
    Server();

  private slots:
    void receivedData();
};

#endif // SERVER_H

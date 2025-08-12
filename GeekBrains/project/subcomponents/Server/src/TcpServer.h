#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "DbWatcher.h"
#include <QDateTime>
#include <QJsonDocument>
#include <QList>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QTcpServer>
#include <QTcpSocket>
#include <QThread>
#include <QTimer>

struct ClientInfo
{
    QTcpSocket * socket;
    QString ip;
    quint16 port;
    int missedPings;        // количество пропущенных ping
    QDateTime lastActivity; // время последней активности
};

class TcpServer : public QObject
{
    Q_OBJECT

    void removeClient( QTcpSocket * socket );

  public:
    explicit TcpServer( quint16 port, QObject * parent = nullptr );
    ~TcpServer();

    bool startServer();

  signals:
    void sendToAll( const QString & message ); // для рассылки клиентам

  private slots:
    void onNewConnection();
    void onClientDisconnected();
    void onClientReadyRead();
    void onPingTimer();

  private:
    QTcpServer * m_server;
    QList<ClientInfo> m_clients;
    QSqlDatabase m_db;
    quint16 m_port;
    QTimer * m_pingTimer; // таймер для ping
    QThread * m_dbWatcherThread;
    DbWatcher * m_dbWatcher;
};

#endif // TCPSERVER_H

#include "TcpServer.h"
#include <QDebug>
#include <QHostAddress>
#include <QSqlQuery>

TcpServer::TcpServer( quint16 port, QObject * parent )
  : QObject( parent )
  , m_server( new QTcpServer( this ) )
  , m_port( port )
  , m_pingTimer( new QTimer() )
{
    qDebug() << "===Server start===";
    startServer();

    // Настройка таймера ping
    m_pingTimer->setInterval( 30000 ); // 30 секунд
    connect( m_pingTimer, &QTimer::timeout, this, &TcpServer::onPingTimer );
    m_pingTimer->start();

    qDebug() << "Ping-таймер запущен (каждые 30 сек)";

    // Запуск DbWatcher в отдельном потоке
    m_dbWatcherThread = new QThread( this );
    m_dbWatcher = new DbWatcher( "db_watcher_connection" );

    m_dbWatcher->moveToThread( m_dbWatcherThread );

    connect( m_dbWatcherThread, &QThread::started, m_dbWatcher, &DbWatcher::startMonitoring );
    connect( m_dbWatcherThread, &QThread::finished, m_dbWatcher, &QObject::deleteLater );

    // Перенаправляем сигналы
    connect( m_dbWatcher, &DbWatcher::dataChanged, this, [this]( const QVariantMap & change ) {
        if ( m_clients.size() == 0 ) return;
        QJsonDocument doc = QJsonDocument::fromVariant( change );
        QString json = QString::fromUtf8( doc.toJson( QJsonDocument::Compact ) ) + "\n";

        // Рассылаем всем клиентам
        for ( auto & client : m_clients ) {
            if ( client.socket->state() == QAbstractSocket::ConnectedState ) {
                client.socket->write( json.toUtf8() );
                client.socket->flush();
            }
        }

        qDebug() << "Рассылка клиентам:" << json.trimmed();
    } );

    m_dbWatcherThread->start();
}

TcpServer::~TcpServer()
{
    for ( auto & client : m_clients ) {
        client.socket->deleteLater();
    }
    m_server->close();
    if ( m_db.isOpen() ) {
        m_db.close();
        QSqlDatabase::removeDatabase( m_db.connectionName() );
    }
    qDebug() << "===Server end===";
}

bool TcpServer::startServer()
{
    if ( !m_server->listen( QHostAddress::Any, m_port ) ) {
        qCritical() << "Не удалось запустить сервер:" << m_server->errorString();
        return false;
    }

    qDebug() << "TCP-сервер запущен на порту" << m_server->serverPort();
    connect( m_server, &QTcpServer::newConnection, this, &TcpServer::onNewConnection );
    return true;
}

void TcpServer::onNewConnection()
{
    while ( m_server->hasPendingConnections() ) {
        QTcpSocket * socket = m_server->nextPendingConnection();

        QString ip = socket->peerAddress().toString();
        quint16 port = socket->peerPort();

        qDebug() << "Новое подключение:" << ip << ":" << port;

        // Сохраняем клиента
        ClientInfo info;
        info.socket = socket;
        info.ip = ip;
        info.port = port;
        m_clients.append( info );

        // Подключаем сигналы
        connect( socket, &QTcpSocket::disconnected, this, &TcpServer::onClientDisconnected );
        connect( socket, &QTcpSocket::readyRead, this, &TcpServer::onClientReadyRead );
    }
}

void TcpServer::onClientDisconnected()
{
    QTcpSocket * socket = qobject_cast<QTcpSocket *>( sender() );
    if ( !socket ) return;

    auto it = std::find_if(
      m_clients.begin(), m_clients.end(), [socket]( const ClientInfo & info ) { return info.socket == socket; } );

    if ( it != m_clients.end() ) {
        qDebug() << "Клиент отключился:" << it->ip << ":" << it->port;
        m_clients.erase( it );
    }

    socket->deleteLater();
}

void TcpServer::onClientReadyRead()
{
    //    QTcpSocket * socket = qobject_cast<QTcpSocket *>( sender() );
    //    if ( !socket ) return;

    //    QByteArray data = socket->readAll();
    //    QString message = QString::fromUtf8( data ).trimmed();

    //    qDebug() << "Получено от клиента:" << message;

    // Можно парсить JSON и реагировать
    // Например: {"command":"sync"} → отправить обновления

    QTcpSocket * socket = qobject_cast<QTcpSocket *>( sender() );
    if ( !socket ) return;

    QByteArray data = socket->readAll();
    QString message = QString::fromUtf8( data ).trimmed();

    // Найдём клиента
    auto it = std::find_if(
      m_clients.begin(), m_clients.end(), [socket]( const ClientInfo & info ) { return info.socket == socket; } );

    if ( it != m_clients.end() ) {
        // Обновляем активность
        it->lastActivity = QDateTime::currentDateTime();
        it->missedPings = 0; // сбрасываем счётчик
    }

    // Логируем
    qDebug() << "Получено от клиента:" << message;

    // Если это ответ на ping
    if ( message == "PONG" ) {
        qDebug() << "Клиент подтвердил активность:" << socket->peerAddress().toString();
        return;
    }

    // Можно обрабатывать другие команды
    // Например: {"command":"sync"}
}

void TcpServer::removeClient( QTcpSocket * socket )
{
    auto it = std::find_if(
      m_clients.begin(), m_clients.end(), [socket]( const ClientInfo & info ) { return info.socket == socket; } );
    if ( it != m_clients.end() ) {
        m_clients.erase( it );
    }
    socket->deleteLater();
}

void TcpServer::onPingTimer()
{
    qDebug() << "Проверка активности клиентов...";

    for ( auto it = m_clients.begin(); it != m_clients.end(); ) {
        QTcpSocket * socket = it->socket;

        // Проверяем, валиден ли сокет
        if ( !socket || socket->state() != QAbstractSocket::ConnectedState ) {
            qDebug() << "Сокет недоступен, удаляем:" << it->ip << ":" << it->port;
            it = m_clients.erase( it );
            continue;
        }

        // Увеличиваем счётчик пропущенных пингов
        it->missedPings++;

        // Отправляем ping
        socket->write( "PING\n" );
        socket->flush();

        qDebug() << "Отправлен PING клиенту:" << it->ip << ":" << it->port << "(пропущено пингов:" << it->missedPings
                 << ")";

        // Если клиент не ответил 2 раза подряд — отключаем
        if ( it->missedPings >= 2 ) {
            qDebug() << "Клиент не отвечает, отключаем:" << it->ip << ":" << it->port;
            socket->disconnectFromHost(); // начнётся отключение
            if ( m_clients.size() > 0 ) it = m_clients.erase( it );
        } else {
            ++it;
        }
    }
}

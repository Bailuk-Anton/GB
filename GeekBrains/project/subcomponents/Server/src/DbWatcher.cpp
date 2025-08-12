#include "DbWatcher.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

DbWatcher::DbWatcher( const QString & dbConnectionName, QObject * parent )
  : QObject( parent )
  , m_timer( new QTimer( this ) )
{
    // Копируем подключение к БД в этот поток
    m_db = QSqlDatabase::cloneDatabase( QSqlDatabase::database( "server_db" ), dbConnectionName );
    //  m_db = QSqlDatabase::addDatabase("QMYSQL");
}

DbWatcher::~DbWatcher()
{
    //  if (m_db.isOpen()) {
    //    m_db.close();
    //    QSqlDatabase::removeDatabase(m_db.connectionName());
    //  }
}

bool DbWatcher::openDatabase()
{
    m_db = QSqlDatabase::addDatabase( "QMYSQL" );
    m_db.setHostName( "127.0.0.1" );
    m_db.setDatabaseName( "bylook" );
    m_db.setUserName( "bylook" );
    m_db.setPassword( "4690163" );

    while ( !m_db.isOpen() ) {
        if ( !m_db.open() ) {
            qCritical() << "DbWatcher: Не удалось подключиться к БД:" << m_db.lastError().text();
        }
        sleep( 5 * 1000 );
    }
    return true;
}

void DbWatcher::startMonitoring()
{
    if ( !openDatabase() ) {
        return;
    }

    // Загружаем последний ID
    QSqlQuery query( "SELECT * FROM Watcher", m_db );
    if ( query.next() ) {
        m_lastProcessedId = query.value( 0 ).toInt();
    }

    // Запускаем таймер
    m_timer->setInterval( 3000 ); // каждые 3 секунды
    connect( m_timer, &QTimer::timeout, this, &DbWatcher::onTimer );
    m_timer->start();

    qDebug() << "DbWatcher запущен. Следим за Watcher начиная с ID =" << m_lastProcessedId;
}

void DbWatcher::onTimer()
{
    QList<QVariantMap> changes = getNewChanges();
    for ( const auto & change : changes ) {
        emit dataChanged( change ); // отправляем сигнал
    }
}

QList<QVariantMap> DbWatcher::getNewChanges()
{
    QList<QVariantMap> result;
    QSqlQuery query;

    query.prepare( "SELECT * FROM Watcher" );

    if ( !query.exec() ) {
        qCritical() << "Ошибка запроса в DbWatcher:" << query.lastError().text();
        return result;
    }

    while ( query.next() ) {
        QVariantMap change;
        int id = query.value( "Id" ).toInt();
        change["id"] = id;
        change["action"] = query.value( "Action" ).toString();
        change["table"] = query.value( "TableName" ).toString();
        change["item_id"] = query.value( "Item_Id" ).toInt();

        result.append( change );
        m_lastProcessedId = std::max( m_lastProcessedId, id );
    }

    if ( query.size() != 0 ) {
        query.prepare( "DELETE FROM Watcher WHERE 1=1" );

        if ( !query.exec() ) {
            qCritical() << "Ошибка запроса в DbWatcher:" << query.lastError().text();
            return result;
        }
    }

    return result;
}

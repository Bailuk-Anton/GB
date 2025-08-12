#include "dbManager.h"

#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>

// Теперь можем включить QSql здесь
#include <QSqlDatabase>

class DbManagerPrivate
{
  public:
    QSqlDatabase db;
};

DbManager::DbManager( QObject * parent )
  : QObject( parent )
{
    // Инициализируем базу данных
    auto db = QSqlDatabase::addDatabase( "QMYSQL" );
    db.setDatabaseName( "bylook" );
    m_db = QSqlDatabase( db );
    m_db.setHostName( "127.0.0.1" );
    m_db.setDatabaseName( "bylook" );
    m_db.setUserName( "bylook" );
    m_db.setPassword( "4690163" );

    initialize();
}

DbManager::~DbManager()
{
    if ( m_db.isOpen() ) {
        m_db.close();
    }
    //  QSqlDatabase::removeDatabase(connectionName());
}

bool DbManager::initialize()
{
    if ( !m_db.open() ) {
        qCritical() << "Не удалось открыть базу данных:" << m_db.lastError().text();
        return false;
    }

    return true;
}

QSqlQuery DbManager::selectFromTable( const QString table, const QMap<QString, QString> & fields )
{
    QSqlQuery query( m_db );
    QString select = "SELECT * FROM " + table;
    if ( fields.size() > 0 ) select += " WHERE " + getWhereOrSet( fields );

    query.prepare( select );

    if ( !query.exec() ) {
        qCritical() << "Ошибка запроса:" << query.lastError().text();
    }
    return query;
}

bool DbManager::deleteFromTable( const QString table, const int & id, const QMap<QString, QString> & whereFields )
{
    QSqlQuery query( m_db );
    if ( whereFields.size() == 0 )
        query.prepare( "DELETE FROM " + table + " WHERE " + table + "Id = " + QString::number( id ) );
    else
        query.prepare( "DELETE FROM " + table + " WHERE " + getWhereOrSet( whereFields ) );

    if ( !query.exec() ) {
        qCritical() << "Ошибка запроса:" << query.lastError().text();
        return false;
    }
    return true;
}

bool DbManager::deleteFromTable( const QString table,
                                 const QList<int> & id,
                                 const QMap<QString, QString> & whereFields )
{
    for ( const int item_id : id ) {
        deleteFromTable( table, item_id, whereFields );
    }
    return true;
}

bool DbManager::updateFromTable( const QString table,
                                 const int & id,
                                 const QMap<QString, QString> & setFields,
                                 const QMap<QString, QString> & whereFields )
{
    Q_UNUSED( whereFields );
    QSqlQuery query( m_db );

    QString select = "UPDATE " + table + " SET " + getWhereOrSet( setFields ) + " WHERE "
                     + /*getWhereOrSet( whereFields )*/ table + "Id = " + QString::number( id );

    qDebug() << select;

    query.prepare( select );

    if ( !query.exec() ) {
        qCritical() << "Ошибка запроса:" << query.lastError().text();
        return false;
    }
    return true;
}

bool DbManager::updateFromTable( const QString table,
                                 const QList<int> & id,
                                 const QMap<QString, QString> & setFields,
                                 const QMap<QString, QString> & updateFields )
{
    for ( const int item_id : id ) {
        updateFromTable( table, item_id, setFields, updateFields );
    }
    return true;
}

bool DbManager::insertFromTable( const QString table, const QMap<QString, QString> & fields )
{
    QSqlQuery query( m_db );
    QString select = "INSERT INTO " + table + getInsert( fields );

    qDebug() << select;
    query.prepare( select );

    if ( !query.exec() ) {
        qCritical() << "Ошибка запроса:" << query.lastError().text();
        return false;
    }
    return true;
}

QString DbManager::getWhereOrSet( const QMap<QString, QString> & fields )
{
    QString where;

    for ( auto it = fields.begin(); it != fields.end(); it++ ) {
        where += it.key() + "=" + it.value();
        if ( ( it + 1 ) != fields.end() ) where += ", ";
    }

    return where;
}

QString DbManager::getInsert( const QMap<QString, QString> & fieldsList )
{
    QString fields = " ( ", values = " ( ";

    for ( auto it = fieldsList.begin(); it != fieldsList.end(); it++ ) {
        fields += it.key();
        values += it.value();
        if ( ( it + 1 ) != fieldsList.end() ) {
            fields += ", ";
            values += ", ";
        }
    }
    fields += ") VALUES ";
    values += ")";
    return fields + values;
}

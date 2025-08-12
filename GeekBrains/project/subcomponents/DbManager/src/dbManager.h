#ifndef DBMANAGER_H
#define DBMANAGER_H

//#include "dbmanager_global.h"
#include <QDate>
#include <QObject>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <QTime>
#include <QVariantMap>

// Forward declaration
class DbManager : public QObject
{
    Q_OBJECT

  public:
    explicit DbManager( QObject * parent = nullptr );

    ~DbManager();

    bool initialize();

    //    QSqlQuery selectFromTable( const QString table );
    QSqlQuery selectFromTable( const QString table, const QMap<QString, QString> & fields = {} );

    bool deleteFromTable( const QString table, const int & id, const QMap<QString, QString> & whereFields = {} );
    bool deleteFromTable( const QString table, const QList<int> & id, const QMap<QString, QString> & whereFields = {} );

    bool updateFromTable( const QString table,
                          const int & id,
                          const QMap<QString, QString> & setFields = {},
                          const QMap<QString, QString> & updateFields = {} );
    bool updateFromTable( const QString table,
                          const QList<int> & id,
                          const QMap<QString, QString> & setFields = {},
                          const QMap<QString, QString> & updateFields = {} );

    bool insertFromTable( const QString table, const QMap<QString, QString> & fields = {} );

    QString getWhereOrSet( const QMap<QString, QString> & fields = {} );
    QString getInsert( const QMap<QString, QString> & fieldsList = {} );

  private:
    QSqlDatabase m_db;
};
#endif // DBMANAGER_H

#include "dbmanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

// Приватный конструктор
DbManager::DbManager()
    : QObject(nullptr)
    , m_db(QSqlDatabase::addDatabase("QMYSQL", connectionName()))
{
    m_db.setHostName("127.0.0.1");
    m_db.setDatabaseName("bylook");
    m_db.setUserName("bylook");
    m_db.setPassword("4690163");
}

// Статический метод — точка доступа
DbManager& DbManager::instance()
{
    static DbManager instance; // Создаётся при первом вызове
    return instance;
}

DbManager::~DbManager()
{
    if (m_db.isOpen()) {
        m_db.close();
    }
    QSqlDatabase::removeDatabase(connectionName());
}

QString DbManager::connectionName() const
{
    return "dbmanager_connection";
}

bool DbManager::initialize()
{
    if (!m_db.open()) {
        qCritical() << "Не удалось открыть базу данных:" << m_db.lastError().text();
        return false;
    }
    return true;
}

QSqlQuery DbManager::selectFromTable(const QString& table, const QMap<QString, QString>& fields)
{
    QSqlQuery query(m_db);
    QString sql = "SELECT * FROM `" + table + "`";
    
    if (!fields.isEmpty()) {
        sql += " WHERE " + getWhereOrSet(fields);
    }

    if (!query.exec(sql)) {
        qCritical() << "Ошибка SELECT:" << query.lastError().text() << "SQL:" << sql;
    }
    return query;
}

bool DbManager::deleteFromTable(const QString& table, const int& id, const QMap<QString, QString>& whereFields)
{
    QSqlQuery query(m_db);
    QString sql;
    
    if (whereFields.isEmpty()) {
        sql = "DELETE FROM `" + table + "` WHERE `Id` = " + QString::number(id);
    } else {
        sql = "DELETE FROM `" + table + "` WHERE " + getWhereOrSet(whereFields);
    }

    query.prepare(sql);
    if (!query.exec()) {
        qCritical() << "Ошибка DELETE:" << query.lastError().text();
        return false;
    }
    return true;
}

bool DbManager::deleteFromTable(const QString& table, const QList<int>& ids, const QMap<QString, QString>& whereFields)
{
    for (int id : ids) {
        if (!deleteFromTable(table, id, whereFields)) {
            return false;
        }
    }
    return true;
}

bool DbManager::updateFromTable(const QString& table,
                                const int& id,
                                const QMap<QString, QString>& setFields,
                                const QMap<QString, QString>& whereFields)
{
    QSqlQuery query(m_db);
    QString sql = "UPDATE `" + table + "` SET " + getWhereOrSet(setFields);
    
    if (whereFields.isEmpty()) {
        sql += " WHERE `Id` = " + QString::number(id);
    } else {
        sql += " WHERE " + getWhereOrSet(whereFields);
    }

    query.prepare(sql);
    if (!query.exec()) {
        qCritical() << "Ошибка UPDATE:" << query.lastError().text();
        return false;
    }
    return true;
}

bool DbManager::updateFromTable(const QString& table,
                                const QList<int>& ids,
                                const QMap<QString, QString>& setFields,
                                const QMap<QString, QString>& whereFields)
{
    for (int id : ids) {
        if (!updateFromTable(table, id, setFields, whereFields)) {
            return false;
        }
    }
    return true;
}

bool DbManager::insertFromTable(const QString& table, const QMap<QString, QString>& fields)
{
    QSqlQuery query(m_db);
    QString sql = "INSERT INTO `" + table + "` " + getInsert(fields);

    query.prepare(sql);
    if (!query.exec()) {
        qCritical() << "Ошибка INSERT:" << query.lastError().text() << "SQL:" << sql;
        return false;
    }
    return true;
}

QString DbManager::getWhereOrSet(const QMap<QString, QString>& fields)
{
    QStringList parts;
    for (auto it = fields.begin(); it != fields.end(); ++it) {
        parts << "`" + it.key() + "` = '" + it.value() + "'";
    }
    return parts.join(" AND ");
}

QString DbManager::getInsert(const QMap<QString, QString>& fields)
{
    if (fields.isEmpty()) return "() VALUES ()";

    QStringList columns, values;
    for (auto it = fields.begin(); it != fields.end(); ++it) {
        columns << "`" + it.key() + "`";
        values << "'" + it.value() + "'";
    }

    return "(" + columns.join(", ") + ") VALUES (" + values.join(", ") + ")";
}

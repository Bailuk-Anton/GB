#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QMap>
#include <QSqlDatabase>

class DbManager : public QObject
{
    Q_OBJECT

public:
    // Единственный способ получить экземпляр
    static DbManager& instance();

    // Удаляем копирование и перемещение
    DbManager(const DbManager&) = delete;
    DbManager& operator=(const DbManager&) = delete;

    ~DbManager();

    bool initialize();
    QSqlQuery selectFromTable(const QString& table, const QMap<QString, QString>& fields = {});
    bool deleteFromTable(const QString& table, const int& id, const QMap<QString, QString>& whereFields = {});
    bool deleteFromTable(const QString& table, const QList<int>& ids, const QMap<QString, QString>& whereFields = {});
    bool updateFromTable(const QString& table,
                         const int& id,
                         const QMap<QString, QString>& setFields,
                         const QMap<QString, QString>& whereFields = {});
    bool updateFromTable(const QString& table,
                         const QList<int>& ids,
                         const QMap<QString, QString>& setFields,
                         const QMap<QString, QString>& whereFields = {});
    bool insertFromTable(const QString& table, const QMap<QString, QString>& fields);

private:
    explicit DbManager(); // Приватный конструктор

    QSqlDatabase m_db;
    QString connectionName() const;

    QString getWhereOrSet(const QMap<QString, QString>& fields);
    QString getInsert(const QMap<QString, QString>& fields);
};

#endif // DBMANAGER_H

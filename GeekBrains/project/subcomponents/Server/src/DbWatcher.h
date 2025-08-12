#ifndef DBWATCHER_H
#define DBWATCHER_H

#include <QMutex>
#include <QObject>
#include <QSqlDatabase>
#include <QTimer>
#include <QVariantMap>

class DbWatcher : public QObject
{
    Q_OBJECT

    void sleep( int ms ) const
    {
        static QMutex mutex;
        static QMutexLocker locker( &mutex );
        mutex.tryLock( ms );
    }

  public:
    explicit DbWatcher( const QString & dbConnectionName, QObject * parent = nullptr );
    ~DbWatcher();

  signals:
    // Сигнал, который будет отправлен серверу при обнаружении изменений
    void dataChanged( const QVariantMap & change );

  public slots:
    void startMonitoring();

  private slots:
    void onTimer();

  private:
    QSqlDatabase m_db;
    QTimer * m_timer;
    int m_lastProcessedId = 0;

    bool openDatabase();
    QList<QVariantMap> getNewChanges();
};

#endif // DBWATCHER_H

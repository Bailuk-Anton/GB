#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>

namespace Client {
class Settings
{
    Settings();
    enum Keys
    {
        Driver,
        Hostname,
        Port,
        DbName,
        Username,
        Password,
        ConnectOptions,
        Admin,
        LocalInfoAddress
    };

    struct KeyStorage
    {
        QString DbDriver /*{ "Database/Driver" }*/;
        QString DbHost /*{ "Database/Host" }*/;
        QString DbPort /*{ "Database/Port" }*/;
        QString DbName /*{ "Database/Name" }*/;
        QString DbUsername /*{ "Database/Username" }*/;
        QString DbPassword /*{ "Database/Password" }*/;
        QString DbConnectOptions /*{ "Database/ConnectOptions" }*/;
        QString admin;
        QString localInfoAddress;
    };

    void CheckConfig();
    void setValue( Keys key, QString value );
    QVariant ReadConfValue( const QString & key ) const;

    QSettings * m_settings;
    KeyStorage m_keyStorage;

  public:
    Settings( const Settings & ) = delete;
    Settings & operator=( const Settings & ) = delete;

    Settings & instance();
    void reset( QSettings * settings = nullptr );
    void initialize( const QString appName, const QString orgName );

    ~Settings();
};
}
#endif // SETTINGS_H

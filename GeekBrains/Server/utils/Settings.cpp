#include "Settings.h"

Server::Settings::Settings()
{}

QVariant Server::Settings::ReadConfValue( const QString & key ) const
{
    return m_settings->value( key );
}

Server::Settings & Server::Settings::instance()
{
    static Settings instance;
    return instance;
}

void Server::Settings::initialize( const QString appName, const QString orgName )
{
    m_settings = new QSettings( appName, orgName );
    m_settings->sync();

    CheckConfig();
}

Server::Settings::~Settings()
{
    delete m_settings;
}

void Server::Settings::CheckConfig()
{
    setValue( Driver, "QMYSQL" );
    setValue( Hostname, "127.0.0.1" );
    setValue( Port, "3306" );
    setValue( DbName, "ATM" );
    setValue( Username, "admin" );
    setValue( Password, "admin" );
    setValue( ConnectOptions, "MYSQL_OPT_RECONNECT=1" );
}

void Server::Settings::setValue( Keys key, QString value )
{
    switch ( key ) {
        case Driver:
            if ( !m_settings->contains( "Driver" ) ) m_settings->setValue( "Driver", value );
            m_keyStorage.DbDriver = m_settings->value( "Driver" ).toString();
            break;
        case Hostname:
            if ( !m_settings->contains( "Hostname" ) ) m_settings->setValue( "Hostname", value );
            m_keyStorage.DbHost = m_settings->value( "Hostname" ).toString();
            break;
        case Port:
            if ( !m_settings->contains( "Port" ) ) m_settings->setValue( "Port", value );
            m_keyStorage.DbPort = m_settings->value( "Port" ).toString();
            break;
        case DbName:
            if ( !m_settings->contains( "DbName" ) ) m_settings->setValue( "DbName", value );
            m_keyStorage.DbName = m_settings->value( "DbName" ).toString();
            break;
        case Username:
            if ( !m_settings->contains( "Username" ) ) m_settings->setValue( "Username", value );
            m_keyStorage.DbUsername = m_settings->value( "Username" ).toString();
            break;
        case Password:
            if ( !m_settings->contains( "Password" ) ) m_settings->setValue( "Password", value );
            m_keyStorage.DbPassword = m_settings->value( "Password" ).toString();
            break;
        case ConnectOptions:
            if ( !m_settings->contains( "ConnectOptions" ) ) m_settings->setValue( "ConnectOptions", value );
            m_keyStorage.DbConnectOptions = m_settings->value( "ConnectOptions" ).toString();
            break;
        default:
            break;
    }
}

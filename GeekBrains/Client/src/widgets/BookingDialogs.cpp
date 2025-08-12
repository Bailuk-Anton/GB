#include "BookingDialogs.h".h "
#include <QDateEdit>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTimeEdit>
#include <QVBoxLayout>

BookingDialog::BookingDialog( const QString & service, QWidget * parent )
  : QDialog( parent )
  , m_service( service )
{
    setWindowTitle( "Запись на услугу" );
    setModal( true );
    resize( 300, 150 );

    // Основной layout
    QVBoxLayout * mainLayout = new QVBoxLayout( this );

    // Форма: Услуга, Дата, Время
    QFormLayout * formLayout = new QFormLayout();

    // Услуга (только для чтения)
    serviceLabel = new QLabel( m_service );
    formLayout->addRow( "Услуга:", serviceLabel );

    // Дата
    dateEdit = new QDateEdit();
    dateEdit->setDate( QDate::currentDate() );
    dateEdit->setCalendarPopup( true );
    formLayout->addRow( "Дата:", dateEdit );

    // Время
    timeEdit = new QTimeEdit();
    timeEdit->setTime( QTime( 9, 0 ) ); // начальное время
    timeEdit->setDisplayFormat( "HH:mm" );
    formLayout->addRow( "Время:", timeEdit );

    // Кнопки ОК / Отмена
    QDialogButtonBox * buttonBox = new QDialogButtonBox( QDialogButtonBox::Ok | QDialogButtonBox::Cancel );
    connect( buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept );
    connect( buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject );

    // Добавляем в основной layout
    mainLayout->addLayout( formLayout );
    mainLayout->addWidget( buttonBox );
}

BookingDialog::~BookingDialog()
{
    // Деструктор пуст — всё удалится через иерархию родителей
}

QString BookingDialog::getDate() const
{
    return dateEdit->date().toString( "dd.MM.yyyy" );
}

QString BookingDialog::getTime() const
{
    return timeEdit->time().toString( "HH:mm" );
}

QString BookingDialog::getService() const
{
    return m_service;
}

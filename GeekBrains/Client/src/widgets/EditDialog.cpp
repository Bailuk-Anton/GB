#include "EditDialog.h"
#include <QComboBox>
#include <QDateEdit>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QLabel>
#include <QTimeEdit>
#include <QVBoxLayout>

EditDialog::EditDialog( const QString & currentService,
                        const QStringList & availableServices,
                        const QString & currentDate,
                        const QString & currentTime,
                        QWidget * parent )
  : QDialog( parent )
  , action( Cancel )
{
    setWindowTitle( "Редактирование записи" );
    setModal( true );
    resize( 300, 200 );

    QVBoxLayout * mainLayout = new QVBoxLayout( this );
    QFormLayout * formLayout = new QFormLayout();

    // Дата
    dateEdit = new QDateEdit();
    dateEdit->setCalendarPopup( true );
    dateEdit->setDisplayFormat( "dd.MM.yyyy" );
    dateEdit->setDate( currentDate.isEmpty() ? QDate::currentDate() : QDate::fromString( currentDate, "dd.MM.yyyy" ) );
    formLayout->addRow( "Дата:", dateEdit );

    // Время
    timeEdit = new QTimeEdit();
    timeEdit->setDisplayFormat( "HH:mm" );
    timeEdit->setTime( currentTime.isEmpty() ? QTime( 9, 0 ) : QTime::fromString( currentTime, "HH:mm" ) );
    formLayout->addRow( "Время:", timeEdit );

    // Услуга (выпадающий список)
    serviceCombo = new QComboBox();
    serviceCombo->addItems( availableServices );
    serviceCombo->setCurrentText( currentService );
    formLayout->addRow( "Услуга:", serviceCombo );

    // Кнопки
    QDialogButtonBox * buttonBox = new QDialogButtonBox();
    QPushButton * saveButton = buttonBox->addButton( "Сохранить", QDialogButtonBox::AcceptRole );
    QPushButton * deleteButton = buttonBox->addButton( "Удалить", QDialogButtonBox::DestructiveRole );
    buttonBox->addButton( "Отмена", QDialogButtonBox::RejectRole );

    connect( deleteButton, &QPushButton::clicked, [this] {
        action = Delete;
        accept(); // закрываем диалог
    } );

    connect( saveButton, &QPushButton::clicked, [this] {
        action = Save;
        accept();
    } );

    connect( buttonBox, &QDialogButtonBox::rejected, [this] {
        action = Cancel;
        reject();
    } );

    mainLayout->addLayout( formLayout );
    mainLayout->addWidget( buttonBox );
}

EditDialog::~EditDialog()
{}

QString EditDialog::getDate() const
{
    return dateEdit->date().toString( "dd.MM.yyyy" );
}

QString EditDialog::getTime() const
{
    return timeEdit->time().toString( "HH:mm" );
}

QString EditDialog::getService() const
{
    return serviceCombo->currentText();
}

EditDialog::Action EditDialog::getAction() const
{
    return action;
}

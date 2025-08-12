#include "EditDialog.h"
#include <QComboBox>
#include <QDateEdit>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QLabel>
#include <QTimeEdit>
#include <QVBoxLayout>

EditDialog::EditDialog( DbManager * manager,
                        const int & id,
                        const QString & currentService,
                        const QMap<int, QString> & availableServices,
                        const QString & currentDate,
                        const QString & currentTime,
                        const QString & currentMaster,
                        const QMap<int, QString> & availableMaster,
                        QWidget * parent )
  : QDialog( parent )
  , m_id( id )
  , m_manager( manager )
  , services( availableServices )
  , people( availableMaster )
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
    QStringList availableServicesList;
    for ( QString item : availableServices.values() )
        availableServicesList << item;
    serviceCombo->addItems( availableServicesList );
    serviceCombo->setCurrentText( currentService );
    formLayout->addRow( "Услуга:", serviceCombo );

    // Мастер (выпадающий список)
    masterCombo = new QComboBox();
    QStringList availableMasterList;
    for ( QString item : availableMaster.values() )
        availableMasterList << item;
    masterCombo->addItems( availableMasterList );
    masterCombo->setCurrentText( currentMaster );
    formLayout->addRow( "Мастер:", masterCombo );

    // Кнопки
    QDialogButtonBox * buttonBox = new QDialogButtonBox();
    QPushButton * saveButton = buttonBox->addButton( "Сохранить", QDialogButtonBox::AcceptRole );
    QPushButton * deleteButton = buttonBox->addButton( "Удалить", QDialogButtonBox::DestructiveRole );
    buttonBox->addButton( "Отмена", QDialogButtonBox::RejectRole );

    connect( deleteButton, &QPushButton::clicked, [this] {
        deleteAction();
        accept(); // закрываем диалог
    } );

    connect( saveButton, &QPushButton::clicked, [this] {
        updateAction();
        accept();
    } );

    connect( buttonBox, &QDialogButtonBox::rejected, [this] { reject(); } );

    mainLayout->addLayout( formLayout );
    mainLayout->addWidget( buttonBox );
}

EditDialog::~EditDialog()
{
    delete m_manager;
}

QDate EditDialog::getDate() const
{
    return dateEdit->date();
}

QTime EditDialog::getTime() const
{
    return timeEdit->time();
}

QString EditDialog::getService() const
{
    return serviceCombo->currentText();
}

QString EditDialog::getMaster() const
{
    return masterCombo->currentText();
}

QMap<QString, QString> EditDialog::getFields()
{
    QMap<QString, QString> allValues;
    allValues["Date"] = "\"" + QDateTime( getDate(), getTime() ).toString( "yyyy-MM-dd hh:mm:ss" ) + "\"";
    allValues["Master_id"] = QString::number( people.key( getMaster() ) );
    allValues["Service_id"] = QString::number( services.key( getService() ) );
    return allValues;
}

void EditDialog::deleteAction()
{
    m_manager->deleteFromTable( "Journal", m_id );
}

void EditDialog::updateAction()
{
    m_manager->updateFromTable( "Journal", m_id, getFields() );
}

#include "PersonEditWidget.h"
#include <QComboBox>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>

PersonDialog::PersonDialog( QWidget * parent )
  : QDialog( parent )
{
    setWindowTitle( "Добавить человека" );
    setModal( true );
    resize( 300, 150 );

    // Поля ввода
    nameEdit = new QLineEdit( this );
    roleCombo = new QComboBox( this );
    roleCombo->addItems( { "client", "master", "admin" } );
    roleCombo->setCurrentText( "client" );

    // Форма
    QFormLayout * formLayout = new QFormLayout();
    formLayout->addRow( "ФИО:", nameEdit );
    formLayout->addRow( "Роль:", roleCombo );

    // Кнопки
    okButton = new QPushButton( "Сохранить" );
    QPushButton * cancelButton = new QPushButton( "Отмена" );

    QHBoxLayout * buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget( okButton );
    buttonLayout->addWidget( cancelButton );

    // Основной layout
    QVBoxLayout * mainLayout = new QVBoxLayout( this );
    mainLayout->addLayout( formLayout );
    mainLayout->addLayout( buttonLayout );

    // Подключаем сигналы
    connect( okButton, &QPushButton::clicked, this, &PersonDialog::onAccept );
    connect( cancelButton, &QPushButton::clicked, this, &QDialog::reject );

    // Активируем okButton только при вводе текста
    connect( nameEdit, &QLineEdit::textChanged, [this]( const QString & text ) {
        okButton->setEnabled( !text.trimmed().isEmpty() );
    } );

    // По умолчанию кнопка может быть отключена
    okButton->setEnabled( false );
}

PersonDialog::PersonDialog( const QString & name, const QString & state, const QString & role, QWidget * parent )
  : QDialog( parent )
{
    setWindowTitle( "Добавить человека" );
    setModal( true );
    resize( 300, 150 );

    // Поля ввода
    nameEdit = new QLineEdit( this );
    nameEdit->setText( name );
    roleCombo = new QComboBox( this );
    roleCombo->addItems( { "client", "master", "admin" } );
    roleCombo->setCurrentText( role );

    stateCombo = new QComboBox( this );
    stateCombo->addItems( { "active", "inactive", "blocked" } );
    stateCombo->setCurrentText( state );

    // Форма
    QFormLayout * formLayout = new QFormLayout();
    formLayout->addRow( "ФИО:", nameEdit );
    formLayout->addRow( "Роль:", roleCombo );
    formLayout->addRow( "Состояние:", stateCombo );

    // Кнопки
    okButton = new QPushButton( "Сохранить" );
    QPushButton * cancelButton = new QPushButton( "Отмена" );

    QHBoxLayout * buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget( okButton );
    buttonLayout->addWidget( cancelButton );

    // Основной layout
    QVBoxLayout * mainLayout = new QVBoxLayout( this );
    mainLayout->addLayout( formLayout );
    mainLayout->addLayout( buttonLayout );

    // Подключаем сигналы
    connect( okButton, &QPushButton::clicked, this, &PersonDialog::onAccept );
    connect( cancelButton, &QPushButton::clicked, this, &QDialog::reject );

    // Активируем okButton только при вводе текста
    connect( nameEdit, &QLineEdit::textChanged, [this]( const QString & text ) {
        okButton->setEnabled( !text.trimmed().isEmpty() );
    } );

    // По умолчанию кнопка может быть отключена
    okButton->setEnabled( false );
}

PersonDialog::~PersonDialog()
{
    // Деструктор
}

QString PersonDialog::getName() const
{
    return nameEdit->text().trimmed();
}

QString PersonDialog::getRole() const
{
    return roleCombo->currentText();
}

QString PersonDialog::getState() const
{
    return stateCombo->currentText();
}

void PersonDialog::onAccept()
{
    QString name = getName();
    if ( name.isEmpty() ) {
        QMessageBox::warning( this, "Ошибка", "Поле ФИО не может быть пустым." );
        return;
    }

    accept(); // закрываем с результатом QDialog::Accepted
}

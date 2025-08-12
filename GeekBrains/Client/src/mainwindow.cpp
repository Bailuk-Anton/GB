#include "mainwindow.h"
#include <QFileDialog>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPixmap>
#include <QPushButton>
#include <QVBoxLayout>

MainWindow::MainWindow( QWidget * parent )
  : QMainWindow( parent )
{
    QWidget * centralWidget = new QWidget( this );
    tabWidget = new QTabWidget( this );
    availableServices << "Маникюр"
                      << "Педикюр"
                      << "Покраска волос"
                      << "Стрижка"
                      << "Укладка";

    setCentralWidget( centralWidget );
    QVBoxLayout * layout = new QVBoxLayout( centralWidget );
    layout->addWidget( tabWidget );

    // Добавляем все 4 вкладки
    tabWidget->addTab( createFirstTab(), "Записи" );
    tabWidget->addTab( createSecondTab(), "Услуги" );
    tabWidget->addTab( createThirdTab(), "История" );
    tabWidget->addTab( createAdminTab(), "Админка" );
    tabWidget->addTab( createFourthTab(), "Анкета" );

    setWindowTitle( "Салон красоты — Управление записями" );
    resize( 700, 400 );
}

MainWindow::~MainWindow()
{
    delete tabWidget;
}

// --- Вкладка 1: Записи (Дата, Время, Услуга) ---
QTableWidget * MainWindow::createFirstTab()
{
    QTableWidget * table = new QTableWidget( 5, 4 );

    // Отключаем редактирование
    table->setEditTriggers( QAbstractItemView::NoEditTriggers );

    table->setHorizontalHeaderLabels( QStringList() << "Дата"
                                                    << "Время"
                                                    << "Услуга"
                                                    << "" );
    table->horizontalHeader()->setStretchLastSection( true );

    QStringList dates = { "05.04.2025", "05.04.2025" };
    QStringList times = { "10:00", "11:30" };
    QStringList services = { "Маникюр", "Педикюр" };

    for ( int i = 0; i < services.size(); ++i ) {
        table->setItem( i, 0, new QTableWidgetItem( dates[i] ) );
        table->setItem( i, 1, new QTableWidgetItem( times[i] ) );
        table->setItem( i, 2, new QTableWidgetItem( services[i] ) );

        QPushButton * button = new QPushButton( "Редактировать" );
        table->setCellWidget( i, 3, button );
        connect( button, &QPushButton::clicked, this, [this, i, table]() { onEditButtonClicked( i, table ); } );
    }

    table->resizeColumnsToContents();

    return table;
}

// --- Вкладка 2: Услуги (Услуга, Цена, Записаться) ---
QTableWidget * MainWindow::createSecondTab()
{
    QTableWidget * table = new QTableWidget( 4, 3 );
    table->setHorizontalHeaderLabels( QStringList() << "Услуга"
                                                    << "Цена (руб)"
                                                    << "" );
    table->horizontalHeader()->setStretchLastSection( true );

    QStringList services = { "Маникюр", "Педикюр", "Покраска волос", "Стрижка" };
    QList<int> prices = { 1500, 2000, 3500, 1200 };

    for ( int i = 0; i < services.size(); ++i ) {
        table->setItem( i, 0, new QTableWidgetItem( services[i] ) );
        table->setItem( i, 1, new QTableWidgetItem( QString::number( prices[i] ) ) );

        QPushButton * button = new QPushButton( "Записаться" );
        table->setCellWidget( i, 2, button );

        connect( button, &QPushButton::clicked, this, [this, services, i, table]() {
            onBookButtonClicked( services[i], table );
        } );
    }

    table->resizeColumnsToContents();

    return table;
}

// --- Вкладка 3: История (Дата, Время, Услуга, Цена) ---
QTableWidget * MainWindow::createThirdTab()
{
    QTableWidget * table = new QTableWidget( 6, 4 );

    // Отключаем редактирование
    table->setEditTriggers( QAbstractItemView::NoEditTriggers );

    table->setHorizontalHeaderLabels( QStringList() << "Дата"
                                                    << "Время"
                                                    << "Услуга"
                                                    << "Цена" );
    table->horizontalHeader()->setStretchLastSection( true );

    table->setItem( 0, 0, new QTableWidgetItem( "01.04.2025" ) );
    table->setItem( 0, 1, new QTableWidgetItem( "09:00" ) );
    table->setItem( 0, 2, new QTableWidgetItem( "Маникюр" ) );
    table->setItem( 0, 3, new QTableWidgetItem( "1500" ) );

    table->setItem( 1, 0, new QTableWidgetItem( "02.04.2025" ) );
    table->setItem( 1, 1, new QTableWidgetItem( "14:00" ) );
    table->setItem( 1, 2, new QTableWidgetItem( "Покраска волос" ) );
    table->setItem( 1, 3, new QTableWidgetItem( "3500" ) );

    table->resizeColumnsToContents();

    return table;
}
// --- Вкладка Админка ---
QWidget * MainWindow::createAdminTab()
{
    QWidget * widget = new QWidget();
    QVBoxLayout * mainLayout = new QVBoxLayout( widget );

    QTableWidget * adminTable = new QTableWidget( 0, 4 ); // начнём с 0 строк
    adminTable->setHorizontalHeaderLabels( QStringList() << "ФИО"
                                                         << "Дата"
                                                         << "Время"
                                                         << "Услуга" );
    adminTable->horizontalHeader()->setSectionResizeMode( 0, QHeaderView::Stretch ); // ФИО растягивается
    adminTable->horizontalHeader()->setSectionResizeMode( 1, QHeaderView::ResizeToContents );
    adminTable->horizontalHeader()->setSectionResizeMode( 2, QHeaderView::ResizeToContents );
    adminTable->horizontalHeader()->setSectionResizeMode( 3, QHeaderView::Stretch );

    adminTable->setEditTriggers( QAbstractItemView::NoEditTriggers );

    mainLayout->addWidget( adminTable );

    return widget;
}

// --- Вкладка 4: Анкета пользователя ---
QWidget * MainWindow::createFourthTab()
{
    QWidget * widget = new QWidget();
    QVBoxLayout * mainLayout = new QVBoxLayout( widget );

    // Форма для ФИО
    QFormLayout * formLayout = new QFormLayout();

    QLineEdit * lastNameEdit = new QLineEdit();
    QLineEdit * firstNameEdit = new QLineEdit();
    QLineEdit * middleNameEdit = new QLineEdit();

    formLayout->addRow( "Фамилия:", lastNameEdit );
    formLayout->addRow( "Имя:", firstNameEdit );
    formLayout->addRow( "Отчество:", middleNameEdit );

    // Фото
    QLabel * photoLabel = new QLabel( "Фото не загружено" );
    photoLabel->setAlignment( Qt::AlignCenter );
    photoLabel->setMinimumSize( 200, 200 );
    photoLabel->setFrameShape( QFrame::Box );
    photoLabel->setStyleSheet( "QLabel { background-color : #f0f0f0; }" );

    QPushButton * loadButton = new QPushButton( "Загрузить фото" );
    connect( loadButton, &QPushButton::clicked, this, &MainWindow::loadPhoto );

    // Сохраняем указатели, чтобы использовать в слоте
    // (или можно использовать свойства, но для простоты сделаем членами класса — см. ниже)
    // Пока просто передаём через замыкание в лямбде (но лучше — члены класса)

    // Для полноценной работы нужно хранить photoLabel как поле класса.
    // Но чтобы не усложнять — используем временное решение: сохраняем в userData
    loadButton->setProperty( "photoLabel", QVariant::fromValue<QObject *>( photoLabel ) );

    // Компоновка
    mainLayout->addLayout( formLayout );
    mainLayout->addWidget( photoLabel );
    mainLayout->addWidget( loadButton );
    mainLayout->addStretch();

    return widget;
}

void MainWindow::onEditButtonClicked( int row, QTableWidget * appointmentsTable )
{
    QTableWidgetItem * dateItem = appointmentsTable->item( row, 0 );
    QTableWidgetItem * timeItem = appointmentsTable->item( row, 1 );
    QTableWidgetItem * serviceItem = appointmentsTable->item( row, 2 );

    if ( !dateItem || !timeItem || !serviceItem ) return;

    QString currentService = serviceItem->text();
    QString currentDate = dateItem->text();
    QString currentTime = timeItem->text();

    EditDialog dialog( currentService, availableServices, currentDate, currentTime, this );
    int result = dialog.exec();

    if ( result == QDialog::Accepted ) {
        EditDialog::Action action = dialog.getAction();

        if ( action == EditDialog::Delete ) {
            // Удаляем запись
            for ( int col = 0; col < appointmentsTable->columnCount(); ++col ) {
                appointmentsTable->takeItem( row, col );
            }
            QWidget * widget = appointmentsTable->cellWidget( row, 3 );
            if ( widget ) {
                appointmentsTable->removeCellWidget( row, 3 );
            }
        } else if ( action == EditDialog::Save ) {
            // Обновляем данные
            dateItem->setText( dialog.getDate() );
            timeItem->setText( dialog.getTime() );
            serviceItem->setText( dialog.getService() );
            appointmentsTable->resizeColumnsToContents();
        }
    }
}

void MainWindow::onBookButtonClicked( const QString & service, QTableWidget * appointmentsTable )
{
    BookingDialog dialog( service, this );
    if ( dialog.exec() == QDialog::Accepted ) {
        QString date = dialog.getDate();
        QString time = dialog.getTime();

        // Найти свободную строку
        int row = -1;
        for ( int i = 0; i < appointmentsTable->rowCount(); ++i ) {
            QTableWidgetItem * item = appointmentsTable->item( i, 0 );
            if ( !item || item->text().isEmpty() ) {
                row = i;
                break;
            }
        }

        if ( row == -1 ) {
            row = appointmentsTable->rowCount();
            appointmentsTable->setRowCount( row + 1 );
        }

        appointmentsTable->setItem( row, 0, new QTableWidgetItem( date ) );
        appointmentsTable->setItem( row, 1, new QTableWidgetItem( time ) );
        appointmentsTable->setItem( row, 2, new QTableWidgetItem( service ) );

        // Подогнать размеры
        appointmentsTable->resizeColumnsToContents();
    }
}

// --- Слот: загрузка фото ---
void MainWindow::loadPhoto()
{
    QPushButton * button = qobject_cast<QPushButton *>( sender() );
    if ( !button ) return;

    QLabel * photoLabel = qobject_cast<QLabel *>( button->property( "photoLabel" ).value<QObject *>() );
    if ( !photoLabel ) return;

    QString fileName =
      QFileDialog::getOpenFileName( this, "Выберите фото", "", "Изображения (*.png *.jpg *.jpeg *.bmp)" );

    if ( !fileName.isEmpty() ) {
        QPixmap pixmap( fileName );
        if ( !pixmap.isNull() ) {
            pixmap = pixmap.scaled( photoLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation );
            photoLabel->setPixmap( pixmap );
        } else {
            photoLabel->setText( "Ошибка загрузки" );
        }
    }
}

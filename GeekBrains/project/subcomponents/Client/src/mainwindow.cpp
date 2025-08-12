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
  , m_socket( new QTcpSocket() )
  , manager( new DbManager() )
{
    connectToServer();
    QWidget * centralWidget = new QWidget( this );
    tabWidget = new QTabWidget( this );

    setCentralWidget( centralWidget );
    QVBoxLayout * layout = new QVBoxLayout( centralWidget );
    layout->addWidget( tabWidget );

    init();

    firstTab = createFirstTab();
    secondTab = createSecondTab();
    thirdTab = createThirdTab();
    fourtTab = createAdminTab();

    //    refreshFirstTab();
    //    refreshSecondTab();
    //    refreshThirdTab();
    //    refreshFourthTab();

    // Добавляем все 4 вкладки
    tabWidget->addTab( firstTab, "Записи" );
    tabWidget->addTab( secondTab, "Услуги" );
    tabWidget->addTab( thirdTab, "История" );
    tabWidget->addTab( fourtTab, "Админка" );
    tabWidget->addTab( createFourthTab(), "Анкета" );

    setWindowTitle( "Салон красоты — Управление записями" );
    resize( 700, 400 );
}

MainWindow::~MainWindow()
{
    delete tabWidget;
    delete m_socket;
}

void MainWindow::init()
{
    QSqlQuery query = manager->selectFromTable( "Services" );
    while ( query.next() ) {
        services[query.value( 0 ).toInt()] = query.value( 1 ).toString();
    }
    query = manager->selectFromTable( "People" );
    while ( query.next() ) {
        people[query.value( 0 ).toInt()] = query.value( 1 ).toString();
    }
}

// --- Вкладка 1: Записи (Дата, Время, Услуга) ---
QTableWidget * MainWindow::createFirstTab()
{
    QSqlQuery query = manager->selectFromTable( "Journal" );
    QTableWidget * table = new QTableWidget( query.size(), 5 );

    // Отключаем редактирование
    table->setEditTriggers( QAbstractItemView::NoEditTriggers );

    table->setHorizontalHeaderLabels( QStringList() << "ФИО"
                                                    << "Услуга"
                                                    << "Мастер"
                                                    << "Дата"
                                                    << "" );
    table->horizontalHeader()->setStretchLastSection( true );

    int i = 0, id = query.value( 0 ).toInt();
    qDebug() << "== Journal ==";

    while ( query.next() ) {
        id = query.value( 0 ).toInt();
        table->setItem( i, 0, new QTableWidgetItem( people[query.value( 2 ).toInt()] ) );
        table->setItem( i, 1, new QTableWidgetItem( services[query.value( 1 ).toInt()] ) );
        table->setItem( i, 2, new QTableWidgetItem( people[query.value( 3 ).toInt()] ) );

        QDateTime dateTime = QDateTime::fromString( query.value( 4 ).toString(), "yyyy-MM-dd'T'hh:mm:ss.zzz" );
        QString formatted = dateTime.toString( "dd.MM.yyyy HH:mm" );
        table->setItem( i, 3, new QTableWidgetItem( formatted ) );

        QPushButton * button = new QPushButton( "Редактировать" );
        table->setCellWidget( i, 4, button );
        connect( button, &QPushButton::clicked, this, [this, id, i, table]() { onEditButtonClicked( id, i, table ); } );

        i++;
    }
    table->resizeColumnsToContents();

    return table;
}

// --- Вкладка 2: Услуги (Услуга, Цена, Записаться) ---
QTableWidget * MainWindow::createSecondTab()
{
    QSqlQuery query = manager->selectFromTable( "Services" );
    QTableWidget * table = new QTableWidget( query.size(), 3 );
    table->setHorizontalHeaderLabels( QStringList() << "Услуга"
                                                    << "Цена (руб)"
                                                    << "" );
    table->horizontalHeader()->setStretchLastSection( true );
    int i = 0;
    qDebug() << "== Services ==";
    while ( query.next() ) {
        QString service = services[query.value( 0 ).toInt()];
        table->setItem( i, 0, new QTableWidgetItem( service ) );
        table->setItem( i, 1, new QTableWidgetItem( query.value( 2 ).toString() ) );

        QPushButton * button = new QPushButton( "Записаться" );
        connect(
          button, &QPushButton::clicked, this, [this, service, table]() { onBookButtonClicked( service, people ); } );
        table->setCellWidget( i, 2, button );
        i++;
    }

    table->resizeColumnsToContents();

    return table;
}

// --- Вкладка 3: История (Дата, Время, Услуга, Цена) ---
QTableWidget * MainWindow::createThirdTab()
{
    QSqlQuery query = manager->selectFromTable( "Journal" );
    QTableWidget * table = new QTableWidget( query.size(), 4 );

    // Отключаем рquery.addBindValue(clientName);едактирование
    table->setEditTriggers( QAbstractItemView::NoEditTriggers );

    table->setHorizontalHeaderLabels( QStringList() << "Услуга"
                                                    << "ФИО клиента"
                                                    << "ФИО мастера"
                                                    << "Дата" );
    table->horizontalHeader()->setStretchLastSection( true );

    int i = 0;
    qDebug() << "== Journal ==";

    while ( query.next() ) {
        table->setItem( i, 0, new QTableWidgetItem( services[query.value( 1 ).toInt()] ) );
        table->setItem( i, 1, new QTableWidgetItem( people[query.value( 2 ).toInt()] ) );
        table->setItem( i, 2, new QTableWidgetItem( people[query.value( 3 ).toInt()] ) );
        QDateTime dateTime = QDateTime::fromString( query.value( 4 ).toString(), "yyyy-MM-dd'T'hh:mm:ss.zzz" );
        QString formatted = dateTime.toString( "dd.MM.yyyy HH:mm" );
        table->setItem( i, 3, new QTableWidgetItem( formatted ) );

        i++;
    }
    table->resizeColumnsToContents();

    return table;
}
// --- Вкладка Админка ---
QWidget * MainWindow::createAdminTab()
{
    QWidget * widget = new QWidget();
    QVBoxLayout * mainLayout = new QVBoxLayout( widget );
    QSqlQuery query = manager->selectFromTable( "People" );

    QTableWidget * table = new QTableWidget( query.size(), 4 ); // начнём с 0 строк
    table->setHorizontalHeaderLabels( QStringList() << "ФИО"
                                                    << "Состояние"
                                                    << "Роль"
                                                    << "" );
    int i = 0;
    qDebug() << "== Admin ==";

    while ( query.next() ) {
        QString name = people[query.value( 0 ).toInt()], id = query.value( 0 ).toString(),
                state = query.value( 2 ).toString(), role = query.value( 4 ).toString();

        table->setItem( i, 0, new QTableWidgetItem( name ) );
        table->setItem( i, 1, new QTableWidgetItem( state ) );
        table->setItem( i, 2, new QTableWidgetItem( role ) );

        QPushButton * button = new QPushButton( "Редактировать" );
        table->setCellWidget( i, 3, button );
        connect( button, &QPushButton::clicked, this, [this, i, name, state, role, id]() {
            PersonDialog dialog( name, state, role );
            if ( dialog.exec() == QDialog::Accepted ) {
                QMap<QString, QString> allValues;
                allValues["Name"] = "\"" + dialog.getName() + "\"";
                allValues["Role"] = "\"" + dialog.getRole() + "\"";
                allValues["State"] = "\"" + dialog.getState() + "\"";
                manager->updateFromTable( "People", people.key( name ), allValues );
            }
        } );

        i++;
    }
    QPushButton * button = new QPushButton( "Добавить" );
    connect( button, &QPushButton::clicked, [this]() {
        PersonDialog dialog( this );
        if ( dialog.exec() == QDialog::Accepted ) {
            QMap<QString, QString> allValues;
            allValues["Name"] = "\"" + dialog.getName() + "\"";
            allValues["Role"] = "\"" + dialog.getRole() + "\"";
            manager->insertFromTable( "People", allValues );
        }
    } );
    mainLayout->addWidget( table );
    mainLayout->addWidget( button );

    table->resizeColumnsToContents();

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
    QLabel * photoLabel = new QLabel();

    QPixmap pixmap( "/home/bylook/GeekBrains/debug/user/commonphoto.png" );

    photoLabel->setPixmap( pixmap );

    photoLabel->setAlignment( Qt::AlignCenter );
    photoLabel->setMinimumSize( 200, 200 );
    photoLabel->setFrameShape( QFrame::Box );
    photoLabel->setStyleSheet( "QLabel { background-color : #f0f0f0; }" );

    QPushButton * loadButton = new QPushButton( "Загрузить фото" );
    connect( loadButton, &QPushButton::clicked, this, &MainWindow::loadPhoto );

    // Сохраняем указатели, чтобы использовать в слоте
    // (или можно использовать свойства, но для простоты сделаем членами класса —
    // см. ниже) Пока просто передаём через замыкание в лямбде (но лучше — члены
    // класса)

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

void MainWindow::connectToServer()
{
    // Простой клиент
    m_socket->connectToHost( "127.0.0.1", 1122 );
    if ( m_socket->waitForConnected() ) {
        m_socket->write( "Hello, Server!\n" );
        m_socket->waitForBytesWritten();
    }

    connect( m_socket, &QTcpSocket::readyRead, [&]() {
        QByteArray data = m_socket->readAll();
        if ( data.trimmed().contains( "PING" ) ) {
            m_socket->write( "PONG\n" );
            m_socket->flush();
            qDebug() << "Ответил PONG на ping";
        } else {
            QJsonDocument doc = QJsonDocument::fromJson( data );
            QJsonObject obj = doc.object();
            qDebug() << "Table:" << obj["table"].toString();
            qDebug() << "ID:" << obj["item_id"].toInt();
            refreshFirstTab();
            refreshSecondTab();
            refreshThirdTab();
            refreshFourthTab();
        }
    } );
}

void MainWindow::refreshFirstTab()
{
    QSqlQuery query = manager->selectFromTable( "Journal" );
    firstTab->clear();

    // Отключаем редактирование
    firstTab->setEditTriggers( QAbstractItemView::NoEditTriggers );

    firstTab->setHorizontalHeaderLabels( QStringList() << "ФИО"
                                                       << "Услуга"
                                                       << "Мастер"
                                                       << "Дата"
                                                       << "" );
    firstTab->horizontalHeader()->setStretchLastSection( true );

    int i = 0, id = query.value( 0 ).toInt();
    qDebug() << "== Journal ==";

    while ( query.next() ) {
        qDebug() << query.value( 0 ) << " " << query.value( 1 ) << " " << query.value( 2 ) << " " << query.value( 3 );

        firstTab->insertRow( i );
        id = query.value( 0 ).toInt();
        firstTab->setItem( i, 0, new QTableWidgetItem( people[query.value( 2 ).toInt()] ) );
        firstTab->setItem( i, 1, new QTableWidgetItem( services[query.value( 1 ).toInt()] ) );
        firstTab->setItem( i, 2, new QTableWidgetItem( people[query.value( 3 ).toInt()] ) );

        QDateTime dateTime = QDateTime::fromString( query.value( 4 ).toString(), "yyyy-MM-dd'T'hh:mm:ss.zzz" );
        QString formatted = dateTime.toString( "dd.MM.yyyy HH:mm" );
        firstTab->setItem( i, 3, new QTableWidgetItem( formatted ) );

        QPushButton * button = new QPushButton( "Редактировать" );
        firstTab->setCellWidget( i, 4, button );
        connect(
          button, &QPushButton::clicked, this, [this, id, i]() { onEditButtonClicked( id, i, this->firstTab ); } );

        i++;
    }
    firstTab->resizeColumnsToContents();
}

void MainWindow::refreshSecondTab()
{
    QSqlQuery query = manager->selectFromTable( "Services" );
    secondTab = new QTableWidget( query.size(), 3 );
    secondTab->setHorizontalHeaderLabels( QStringList() << "Услуга"
                                                        << "Цена (руб)"
                                                        << "" );
    secondTab->horizontalHeader()->setStretchLastSection( true );
    int i = 0;
    qDebug() << "== Services ==";
    while ( query.next() ) {
        QString service = services[query.value( 0 ).toInt()];
        secondTab->setItem( i, 0, new QTableWidgetItem( service ) );
        secondTab->setItem( i, 1, new QTableWidgetItem( query.value( 2 ).toString() ) );

        QPushButton * button = new QPushButton( "Записаться" );
        connect( button, &QPushButton::clicked, this, [this, service]() { onBookButtonClicked( service, people ); } );
        secondTab->setCellWidget( i, 2, button );
        i++;
    }

    secondTab->resizeColumnsToContents();
}

void MainWindow::refreshThirdTab()
{
    QSqlQuery query = manager->selectFromTable( "Journal" );
    thirdTab = new QTableWidget( query.size(), 4 );

    // Отключаем рquery.addBindValue(clientName);едактирование
    thirdTab->setEditTriggers( QAbstractItemView::NoEditTriggers );

    thirdTab->setHorizontalHeaderLabels( QStringList() << "Услуга"
                                                       << "ФИО клиента"
                                                       << "ФИО мастера"
                                                       << "Дата" );
    thirdTab->horizontalHeader()->setStretchLastSection( true );

    int i = 0;
    qDebug() << "== Journal ==";

    while ( query.next() ) {
        thirdTab->setItem( i, 0, new QTableWidgetItem( services[query.value( 1 ).toInt()] ) );
        thirdTab->setItem( i, 1, new QTableWidgetItem( people[query.value( 2 ).toInt()] ) );
        thirdTab->setItem( i, 2, new QTableWidgetItem( people[query.value( 3 ).toInt()] ) );
        QDateTime dateTime = QDateTime::fromString( query.value( 4 ).toString(), "yyyy-MM-dd'T'hh:mm:ss.zzz" );
        QString formatted = dateTime.toString( "dd.MM.yyyy HH:mm" );
        thirdTab->setItem( i, 3, new QTableWidgetItem( formatted ) );

        i++;
    }
    thirdTab->resizeColumnsToContents();
}

void MainWindow::refreshFourthTab()
{
    fourtTab = new QWidget();
    QVBoxLayout * mainLayout = new QVBoxLayout( fourtTab );
    QSqlQuery query = manager->selectFromTable( "People" );

    QTableWidget * table = new QTableWidget( query.size(), 3 ); // начнём с 0 строк
    table->setHorizontalHeaderLabels( QStringList() << "ФИО"
                                                    << "Состояние"
                                                    << "Роль" );
    int i = 0;
    qDebug() << "== Admin ==";

    while ( query.next() ) {
        table->setItem( i, 0, new QTableWidgetItem( people[query.value( 0 ).toInt()] ) );
        table->setItem( i, 1, new QTableWidgetItem( query.value( 2 ).toString() ) );
        table->setItem( i, 2, new QTableWidgetItem( query.value( 4 ).toString() ) );

        QPushButton * button = new QPushButton( "Редактировать" );
        table->setCellWidget( i, 3, button );
        // connect( button, &QPushButton::clicked, this, [this, i, table]() { onEditButtonClicked( id, i, table ); } );

        i++;
    }
    mainLayout->addWidget( table );
}

void MainWindow::onEditButtonClicked( const int & id, int row, QTableWidget * appointmentsTable )
{
    QTableWidgetItem * dateItem = appointmentsTable->item( row, 3 );
    QTableWidgetItem * serviceItem = appointmentsTable->item( row, 1 );
    QTableWidgetItem * currentMaster = appointmentsTable->item( row, 2 );

    if ( !dateItem || !serviceItem ) return;

    QDateTime dateTime = QDateTime::fromString( serviceItem->text(), "dd.MM.yyyy HH:mm" );

    QString currentService = serviceItem->text();
    QString currentDate = dateTime.date().toString();
    QString currentTime = dateTime.time().toString();

    EditDialog dialog(
      manager, id, currentService, services, currentDate, currentTime, currentMaster->text(), people, this );
    dialog.exec();
}

void MainWindow::onBookButtonClicked( const QString & service, const QMap<int, QString> masters )
{
    BookingDialog dialog( service, masters, this );
    if ( dialog.exec() == QDialog::Accepted ) {
        QMap<QString, QString> allValues;
        allValues["Date"] =
          "\"" + QDateTime( dialog.getDate(), dialog.getTime() ).toString( "yyyy-MM-dd hh:mm:ss" ) + "\"";
        allValues["Master_id"] = QString::number( people.key( dialog.getMaster() ) );
        allValues["People_id"] = QString::number( people.key( dialog.getClient() ) );
        allValues["Service_id"] = QString::number( services.key( dialog.getService() ) );

        manager->insertFromTable( "Journal", allValues );
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

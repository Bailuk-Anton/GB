#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QHeaderView>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMainWindow>
#include <QSqlRecord>
#include <QTabWidget>
#include <QTableWidget>
#include <QTcpSocket>
#include <QVBoxLayout>
#include <QWidget>

#include "utils/Settings.h"
#include "widgets/BookingDialogs.h"
#include "widgets/EditDialog.h"
#include "widgets/PersonEditWidget.h"
#include <dbManager.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    /**
     * @brief readLocalInfo - чтение данных с устройства клиента
     */
    void readLocalInfo();

    QMap<int, QString> services;
    QMap<int, QString> people;

    QTcpSocket * m_socket;
    DbManager * manager;

    QTableWidget * firstTab;
    QTableWidget * secondTab;
    QTableWidget * thirdTab;
    QWidget * fourtTab;

  public:
    MainWindow( QWidget * parent = nullptr );
    ~MainWindow();

  private:
    QTabWidget * tabWidget;

    QStringList availableServices;

    void init();

    QTableWidget * createFirstTab();  // Дата, Время, Услуга
    QTableWidget * createSecondTab(); // Услуга, Цена, Записаться
    QTableWidget * createThirdTab();  // Дата, Время, Услуга, Цена
    QWidget * createAdminTab();       // Админка
    QWidget * createFourthTab();      // Анкета: ФИО + фото

    void connectToServer();

  private slots:
    //    void getMessage();

    void refreshFirstTab();
    void refreshSecondTab();
    void refreshThirdTab();
    void refreshFourthTab();

    void onEditButtonClicked( const int & id, int row, QTableWidget * table );
    void onBookButtonClicked( const QString & service, const QMap<int, QString> services );
    void loadPhoto(); // Слот для загрузки фото
};

#endif // MAINWINDOW_H

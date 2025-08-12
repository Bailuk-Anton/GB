#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QHeaderView>
#include <QMainWindow>
#include <QTabWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QWidget>

#include "widgets/BookingDialogs.h"
#include "widgets/EditDialog.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    /**
     * @brief readLocalInfo - чтение данных с устройства клиента
     */
    void readLocalInfo();

  public:
    MainWindow( QWidget * parent = nullptr );
    ~MainWindow();

  private:
    QTabWidget * tabWidget;
    QStringList availableServices;

    QTableWidget * createFirstTab();  // Дата, Время, Услуга
    QTableWidget * createSecondTab(); // Услуга, Цена, Записаться
    QTableWidget * createThirdTab();  // Дата, Время, Услуга, Цена
    QWidget * createAdminTab();       // Админка
    QWidget * createFourthTab();      // Анкета: ФИО + фото

  private slots:
    void onEditButtonClicked( int row, QTableWidget * table );
    void onBookButtonClicked( const QString & service, QTableWidget * appointmentsTable );
    void loadPhoto(); // Слот для загрузки фото
};

#endif // MAINWINDOW_H

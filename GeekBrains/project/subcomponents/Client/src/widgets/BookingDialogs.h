#ifndef BOOKINGDIALOGS_H
#define BOOKINGDIALOGS_H

#include <QComboBox>
#include <QDate>
#include <QDialog>
#include <QString>
#include <QTime>

class QLabel;
class QDateEdit;
class QTimeEdit;
class QDialogButtonBox;
class QVBoxLayout;
class QHBoxLayout;

class BookingDialog : public QDialog
{
    Q_OBJECT

  public:
    explicit BookingDialog( const QString & service, const QMap<int, QString> services, QWidget * parent = nullptr );
    ~BookingDialog();

    QDate getDate() const;
    QTime getTime() const;
    QString getService() const;
    QString getMaster() const;
    QString getClient() const;

  private:
    QString m_service;
    QString m_master;
    QString m_client;
    QDate m_date;
    QTime m_time;

    // Виджеты
    QLabel * serviceLabel;
    QDateEdit * dateEdit;
    QTimeEdit * timeEdit;
    QComboBox * masterCombo;
    QComboBox * clientCombo;
};

#endif // BOOKINGDIALOGS_H

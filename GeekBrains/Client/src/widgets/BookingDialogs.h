#ifndef BOOKINGDIALOGS_H
#define BOOKINGDIALOGS_H

#include <QDialog>
#include <QString>

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
    explicit BookingDialog( const QString & service, QWidget * parent = nullptr );
    ~BookingDialog();

    QString getDate() const;
    QString getTime() const;
    QString getService() const;

  private:
    QString m_service;

    // Виджеты
    QLabel * serviceLabel;
    QDateEdit * dateEdit;
    QTimeEdit * timeEdit;
};

#endif // BOOKINGDIALOGS_H

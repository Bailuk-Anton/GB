#ifndef EditDialog_H
#define EditDialog_H

#include <QDialog>
#include <QPushButton>
#include <QString>
#include <dbManager.h>

class QLabel;
class QDateEdit;
class QTimeEdit;
class QComboBox;
class QDialogButtonBox;
class QVBoxLayout;
class QFormLayout;

class EditDialog : public QDialog
{
    Q_OBJECT

  public:
    explicit EditDialog( DbManager * manager,
                         const int & id,
                         const QString & currentService,
                         const QMap<int, QString> & availableServices,
                         const QString & currentDate,
                         const QString & currentTime,
                         const QString & currentMaster,
                         const QMap<int, QString> & availableMaster,
                         QWidget * parent = nullptr );

    ~EditDialog();

    QDate getDate() const;
    QTime getTime() const;
    QString getService() const;
    QString getMaster() const;
    QMap<QString, QString> getFields();

    void deleteAction();
    void updateAction();

  private:
    int m_id;
    QDateEdit * dateEdit;
    QTimeEdit * timeEdit;
    QComboBox * serviceCombo;
    QComboBox * masterCombo;
    DbManager * m_manager;
    QMap<int, QString> services;
    QMap<int, QString> people;
};

#endif // EDITDIALOG_H

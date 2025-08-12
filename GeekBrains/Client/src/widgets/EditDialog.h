#ifndef EditDialog_H
#define EditDialog_H

#include <QDialog>
#include <QPushButton>
#include <QString>

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
    enum Action
    {
        Save,
        Delete,
        Cancel
    };

    explicit EditDialog( const QString & currentService,
                         const QStringList & availableServices,
                         const QString & currentDate = {},
                         const QString & currentTime = {},
                         QWidget * parent = nullptr );

    ~EditDialog();

    QString getDate() const;
    QString getTime() const;
    QString getService() const;
    Action getAction() const;

  private:
    QDateEdit * dateEdit;
    QTimeEdit * timeEdit;
    QComboBox * serviceCombo;
    Action action;
};

#endif // EDITDIALOG_H

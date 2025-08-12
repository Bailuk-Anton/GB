#ifndef PERSONDIALOG_H
#define PERSONDIALOG_H

#include <QDialog>
#include <QString>

class QLineEdit;
class QComboBox;
class QFormLayout;
class QVBoxLayout;
class QHBoxLayout;
class QPushButton;

class PersonDialog : public QDialog
{
    Q_OBJECT

  public:
    PersonDialog( QWidget * parent = nullptr );
    PersonDialog( const QString & name, const QString & state, const QString & role, QWidget * parent = nullptr );
    ~PersonDialog();

    // Получение введённых данных
    QString getName() const;
    QString getRole() const;
    QString getState() const;

  private slots:
    void onAccept(); // проверка перед принятием

  private:
    QLineEdit * nameEdit;
    QComboBox * roleCombo;
    QComboBox * stateCombo;

    QPushButton * okButton;
};

#endif // PERSONDIALOG_H

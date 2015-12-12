#ifndef EDITPERSONDIALOG_H
#define EDITPERSONDIALOG_H

#include <QDialog>
#include "person.h"
#include "constants.h"

namespace Ui {
class editPersonDialog;
}

class editPersonDialog : public QDialog
{
    Q_OBJECT

public:
    explicit editPersonDialog(QWidget *parent = 0);
    ~editPersonDialog();

    void setFields();
    void setPerson(const Person &p);
    Person getPerson();
    bool getSaveClick();
    bool getChangesMade();

private slots:
    void on_cancelButton_clicked();

    void on_aliveCheckBox_clicked(bool checked);

    void on_editPersonNameField_textChanged(const QString &arg1);

    void verifyInputs();

    void on_editPersonCountryField_textChanged(const QString &arg1);

    void on_editPersonGender_currentIndexChanged(const QString &arg1);

    void on_editPersonDateOfBirth_dateChanged(const QDate &date);

    void on_editPersonDateOfDeath_dateChanged(const QDate &date);

    void on_editSaveButton_clicked();

private:
    Ui::editPersonDialog *ui;
    Person editPerson;
    bool saveClick;
    bool changesMade;
};

#endif // EDITPERSONDIALOG_H

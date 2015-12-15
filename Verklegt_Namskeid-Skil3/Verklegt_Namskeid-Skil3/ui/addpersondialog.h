#ifndef AddPersonDialog_H
#define AddPersonDialog_H

#include <QDialog>
#include "models/person.h"
#include "utilities/utilities.h"
#include "utilities/constants.h"
#include <QDebug>

namespace Ui {
class AddPersonDialog;
}

class AddPersonDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddPersonDialog(QWidget *parent = 0);
    ~AddPersonDialog();

    // Get person
    Person getPerson();

    // Verify data
    void verifyInputs();

    // Get click
    bool getAddClick();

private slots:
    void on_addPersonNameField_textChanged(const QString &arg1);

    void on_addPersonCountryField_textChanged(const QString &arg1);

    void on_aliveCheckbox_clicked(bool checked);

    void on_addPersonBirthDate_dateChanged(const QDate &date);

    void on_addPersonDeathDate_dateChanged(const QDate &date);

    void on_addPersonGenderCombobox_currentIndexChanged(const QString &arg1);

    void on_addButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::AddPersonDialog *ui;
    Person newPerson;
    bool addClick;
};

#endif // AddPersonDialog_H

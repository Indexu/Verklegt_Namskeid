#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include <QPushButton>
#include "person.h"
#include "utilities.h"
#include "constants.h"

namespace Ui {
class AddDialog;
}

class AddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddDialog(QWidget *parent = 0);
    ~AddDialog();

    // Get person
    Person getPerson();

    // Verify data
    void verifyInputs();

private slots:
    void on_addPersonNameField_textChanged(const QString &arg1);

    void on_addPersonCountryField_textChanged(const QString &arg1);

    void on_aliveCheckbox_clicked(bool checked);

    void on_addPersonBirthDate_dateChanged(const QDate &date);

    void on_addPersonDeathDate_dateChanged(const QDate &date);

    void on_addPersonGenderCombobox_currentIndexChanged(const QString &arg1);

private:
    Ui::AddDialog *ui;
    Person newPerson;
};

#endif // ADDDIALOG_H

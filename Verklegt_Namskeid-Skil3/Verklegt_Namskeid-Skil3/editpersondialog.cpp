#include "editpersondialog.h"
#include "ui_editpersondialog.h"
#include <QDebug>

editPersonDialog::editPersonDialog(QWidget *parent) :
      QDialog(parent),
    ui(new Ui::editPersonDialog)
{

    ui->setupUi(this);

    // Set minimum dates
    ui->editPersonDateOfBirth->setMinimumDate(QDate(100, 1, 1));
    ui->editPersonDateOfDeath->setMinimumDate(QDate(100, 1, 1));
}

editPersonDialog::~editPersonDialog()
{
    delete ui;
}

void editPersonDialog::setFields()
{
    int gender = 0;
    ui->editPersonNameField->setText(editPerson.getName());
    ui->editPersonCountryField->setText(editPerson.getCountry());
    ui->editPersonDateOfBirth->setDate(QDate::fromString(editPerson.getDateOfBirth(), constants::DATE_FORMAT));
    ui->editPersonDateOfDeath->setDate(QDate::fromString(editPerson.getDateOfDeath(), constants::DATE_FORMAT));
    if (editPerson.getDateOfDeath() == "") {
        ui->aliveCheckBox->setChecked(true);
        ui->editPersonDateOfDeath->setEnabled(false);
    }
    if (editPerson.getGender() == "female"){
        gender = 0;
    }
    else{
        gender = 1;
    }
    ui->editPersonGender->setCurrentIndex(gender);
}

void editPersonDialog::setPerson(const Person &p)
{
    editPerson = p;
}

Person editPersonDialog::getPerson()
{
    return editPerson;
}


// Cancel button -> click
void editPersonDialog::on_pushButton_clicked()
{
    this->close();
}

void editPersonDialog::on_aliveCheckBox_clicked()
{
    bool checked = ui->aliveCheckBox->isChecked();
    if (!checked){
        ui->editPersonDateOfDeath->setEnabled(true);
    }
    else{
        ui->editPersonDateOfDeath->setEnabled(false);
    }
}

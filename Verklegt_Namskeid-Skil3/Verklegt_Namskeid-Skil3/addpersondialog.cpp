#include "AddPersonDialog.h"
#include "ui_AddPersonDialog.h"
#include <QMessageBox>
#include <QDebug>

AddPersonDialog::AddPersonDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPersonDialog)
{
    ui->setupUi(this);

    // Set click
    addClick = false;

    // Set minimum dates
    ui->addPersonBirthDate->setMinimumDate(QDate(100, 1, 1));
    ui->addPersonDeathDate->setMinimumDate(QDate(100, 1, 1));

    // Set initial gender
    newPerson.setGender(ui->addPersonGenderCombobox->currentText().toLower());

    // Set initial dates
    newPerson.setDateOfBirth(ui->addPersonBirthDate->date().toString(constants::DATE_FORMAT));
    newPerson.setDateOfDeath(ui->addPersonDeathDate->date().toString(constants::DATE_FORMAT));

    // Verify initial values (set colors)
    verifyInputs();
}

AddPersonDialog::~AddPersonDialog()
{
    delete ui;
}

Person AddPersonDialog::getPerson(){
    return newPerson;
}

// Verify Name and Country
void AddPersonDialog::verifyInputs(){
    bool nameValid = false, countryValid = false, datesValid = false;

    // Name
    if(newPerson.getName().isEmpty()){
        ui->addPersonNameField->setStyleSheet("background-color: #FFC2C2");
        nameValid = false;
    }
    else{
        ui->addPersonNameField->setStyleSheet("background-color: #FFFFFF");
        nameValid = true;
    }

    // Country
    if(newPerson.getCountry().isEmpty()){
        ui->addPersonCountryField->setStyleSheet("background-color: #FFC2C2");
        countryValid = false;
    }
    else{
        ui->addPersonCountryField->setStyleSheet("background-color: #FFFFFF");
        countryValid = true;
    }

    // If dead, compare dates
    if(!newPerson.getDateOfDeath().isEmpty()){
        QDate birthDate = ui->addPersonBirthDate->date();
        QDate deathDate = ui->addPersonDeathDate->date();

        if(birthDate < deathDate){
            ui->dateErrorLabel->setText("");
            datesValid = true;
        }
        else{
            ui->dateErrorLabel->setText("Date of death is earlier");
            ui->dateErrorLabel->setStyleSheet("color: #FF4D4D");
            datesValid = false;
        }
    }
    else{
        ui->dateErrorLabel->setText("");
        datesValid = true;
    }

    // Check valid
    if(nameValid && countryValid && datesValid){
        ui->addButton->setEnabled(true);
    }
    else{
        ui->addButton->setEnabled(false);
    }
}

// Get add click
bool AddPersonDialog::getAddClick(){
    return addClick;
}

// Name field changes
void AddPersonDialog::on_addPersonNameField_textChanged(const QString &arg1){
    newPerson.setName(arg1);
    verifyInputs();
}

// Country field changes
void AddPersonDialog::on_addPersonCountryField_textChanged(const QString &arg1){
    newPerson.setCountry(arg1);
    verifyInputs();
}

// Alive checkbox
void AddPersonDialog::on_aliveCheckbox_clicked(bool checked){
    // Checked
    if(checked){
        // Disable death picker
        ui->addPersonDeathDate->setEnabled(false);
        // Set death date to ""
        newPerson.setDateOfDeath("");
    }
    // Unchecked
    else{
        // Enable death picker
        ui->addPersonDeathDate->setEnabled(true);
        // Assign death date
        QString death = ui->addPersonBirthDate->date().toString(constants::DATE_FORMAT);
        newPerson.setDateOfDeath(death);
    }

    verifyInputs();
}

// Date of birth changes
void AddPersonDialog::on_addPersonBirthDate_dateChanged(const QDate &date){
    newPerson.setDateOfBirth(date.toString(constants::DATE_FORMAT));
    verifyInputs();
}

// Date of death changes
void AddPersonDialog::on_addPersonDeathDate_dateChanged(const QDate &date){
    newPerson.setDateOfDeath(date.toString(constants::DATE_FORMAT));
    verifyInputs();
}

// Gender changes
void AddPersonDialog::on_addPersonGenderCombobox_currentIndexChanged(const QString &arg1){
    newPerson.setGender(arg1.toLower());
}

// Add button -> click
void AddPersonDialog::on_addButton_clicked(){
    addClick = true;
    this->close();
}

// Cancel button -> click
void AddPersonDialog::on_cancelButton_clicked(){
    this->close();
}

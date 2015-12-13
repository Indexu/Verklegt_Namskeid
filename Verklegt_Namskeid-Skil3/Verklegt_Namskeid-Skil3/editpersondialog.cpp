#include "editpersondialog.h"
#include "ui_editpersondialog.h"
#include <QDebug>

editPersonDialog::editPersonDialog(QWidget *parent) :
      QDialog(parent),
    ui(new Ui::editPersonDialog)
{

    ui->setupUi(this);

    // Set save confirmation to false
    saveClick = false;
    changesMade = false;

    // Set minimum dates
    ui->editPersonDateOfBirth->setMinimumDate(QDate(100, 1, 1));
    ui->editPersonDateOfDeath->setMinimumDate(QDate(100, 1, 1));
}

editPersonDialog::~editPersonDialog()
{
    delete ui;
}

// Verify Name and Country
void editPersonDialog::verifyInputs(){
    bool nameValid = false, countryValid = false, datesValid = false;

    // Name
    if(editPerson.getName().isEmpty()){
        ui->editPersonNameField->setStyleSheet("background-color: #FFC2C2");
        nameValid = false;
    }
    else{
        ui->editPersonNameField->setStyleSheet("background-color: #FFFFFF");
        nameValid = true;
    }

    // Country
    if(editPerson.getCountry().isEmpty()){
        ui->editPersonCountryField->setStyleSheet("background-color: #FFC2C2");
        countryValid = false;
    }
    else{
        ui->editPersonCountryField->setStyleSheet("background-color: #FFFFFF");
        countryValid = true;
    }

    // If dead, compare dates
    if(!editPerson.getDateOfDeath().isEmpty()){
        QDate birthDate = ui->editPersonDateOfBirth->date();
        QDate deathDate = ui->editPersonDateOfDeath->date();

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
        ui->editSaveButton->setEnabled(true);
    }
    else{
        ui->editSaveButton->setEnabled(false);
    }
}

// Set field values in the edit dialog
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
    verifyInputs();
}

// Set editperson inital values
void editPersonDialog::setPerson(const Person &p)
{
    editPerson = p;
}

// Get edited person
Person editPersonDialog::getPerson()
{
    return editPerson;
}

// Get true if save button is clicked, otherwise false.
bool editPersonDialog::getSaveClick()
{
    return saveClick;
}

// Get if changes are made
bool editPersonDialog::getChangesMade() {
    return changesMade;
}

// Alive check box - click
void editPersonDialog::on_aliveCheckBox_clicked(bool checked)
{
    if (checked){
        ui->editPersonDateOfDeath->setEnabled(false);
        editPerson.setDateOfDeath("");
    }
    else{
        ui->editPersonDateOfDeath->setEnabled(true);
        QString death = ui->editPersonDateOfBirth->date().toString(constants::DATE_FORMAT);
        editPerson.setDateOfDeath(death);
    }
}
// Person name changes
void editPersonDialog::on_editPersonNameField_textChanged(const QString &arg1)
{
    editPerson.setName(arg1);
    verifyInputs();
}

// Person country changes
void editPersonDialog::on_editPersonCountryField_textChanged(const QString &arg1)
{
    editPerson.setCountry(arg1);
    verifyInputs();
}

// Gender changes
void editPersonDialog::on_editPersonGender_currentIndexChanged(const QString &arg1)
{
    editPerson.setGender(arg1.toLower());
    verifyInputs();
}

// Date of birth changes
void editPersonDialog::on_editPersonDateOfBirth_dateChanged(const QDate &date)
{
    editPerson.setDateOfBirth(date.toString(constants::DATE_FORMAT));
    verifyInputs();
}

// Date of death changes
void editPersonDialog::on_editPersonDateOfDeath_dateChanged(const QDate &date)
{
    editPerson.setDateOfDeath(date.toString(constants::DATE_FORMAT));
    verifyInputs();
}

// Cancel button -> click
void editPersonDialog::on_cancelButton_clicked()
{
    this->close();
}

// Save button -> click
void editPersonDialog::on_editSaveButton_clicked()
{
    // Set values to person editPerson when saved
    editPerson.setName(ui->editPersonNameField->text());
    editPerson.setGender(ui->editPersonGender->currentText().toLower());
    editPerson.setDateOfBirth(ui->editPersonDateOfBirth->date().toString(constants::DATE_FORMAT));
    // Check if alive checkbox is checked
    if (ui->aliveCheckBox->isChecked()) {
        editPerson.setDateOfDeath("");
    }
    else {
        editPerson.setDateOfDeath(ui->editPersonDateOfDeath->date().toString(constants::DATE_FORMAT));
    }
    editPerson.setCountry(ui->editPersonCountryField->text());
    saveClick = true;
    // Checks if changes were made. Have a better look at why the program crashes when creating a new private variable of type Person.
    /*if (editPerson == backUp) {
        qDebug() << "No changes were made." <<  backUp.getName();
    }
    else{
        qDebug() << "Changes were made" << backUp.getName();
    }*/

    this->close();
}

#include "editmachinedialog.h"
#include "ui_editmachinedialog.h"
#include <QDebug>

editMachineDialog::editMachineDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editMachineDialog)
{
    ui->setupUi(this);
    // Set save confirmation to false
    saveClick = false;
    // Verify inputs
    verifyInputs();
}

editMachineDialog::~editMachineDialog()
{
    delete ui;
}

// Get if edit was saved (true/false)
bool editMachineDialog::getSaveClick(){
   return saveClick;
}

// Set machine
void editMachineDialog::setMachine(const Machine &m)
{
    editMachine = m;
}

// Get machine
Machine editMachineDialog::getMachine(){
    return editMachine;
}

// Set types
void editMachineDialog::setTypes(const QVector<TypeSystem> &t){
    types = t;
}

// Set systems
void editMachineDialog::setSystems(const QVector<TypeSystem> &s){
    systems = s;
}

// Add to comboboxes
void editMachineDialog::addToComboboxes(){
    // Types
    for(int i = 0; i < types.size(); i++){
        ui->editMachineType->addItem(types[i].getName());
    }
    // Systems
    for(int i = 0; i < systems.size(); i++){
        ui->editMachineSystem->addItem(systems[i].getName());
    }
}

// Verify inputs
void editMachineDialog::verifyInputs(){
    bool nameValid = false;

    // Name
    if(editMachine.getName().isEmpty()){
        ui->editMachineNameField->setStyleSheet("background-color: #FFC2C2");
        nameValid = false;
    }
    else{
        ui->editMachineNameField->setStyleSheet("background-color: #FFFFFF");
        nameValid = true;
    }

    // Check valid
    if(nameValid){
        ui->editMachineSaveButton->setEnabled(true);
    }
    else{
        ui->editMachineSaveButton->setEnabled(false);
    }
}

// Set edit dialog field values
void editMachineDialog::setFields() {
    ui->editMachineNameField->setText(editMachine.getName());
    if (editMachine.getYear() != 0){
        ui->editMachineYear->setDate(QDate(editMachine.getYear(), 1, 1));
    }
    else{
        ui->yearUnknownCheckbox->setChecked(true);
        ui->editMachineYear->setEnabled(false);
    }

    if (editMachine.getBuilt() == true){
        ui->builtYesRadioButton->setChecked(true);
        ui->builtNoRadioButton->setChecked(false);
    }
    else{
        ui->builtYesRadioButton->setChecked(false);
        ui->builtNoRadioButton->setChecked(true);
    }
    ui->editMachineType->setCurrentText(editMachine.getType());
    ui->editMachineSystem->setCurrentText(editMachine.getSystem());
}

// Name field -> text changed
void editMachineDialog::on_editMachineNameField_textChanged(const QString &arg1)
{
    editMachine.setName(arg1);
    verifyInputs();
}
// Year field -> year changed
void editMachineDialog::on_editMachineYear_dateChanged(const QDate &date)
{
    editMachine.setYear(date.toString(constants::YEAR_BUILT).toInt());
}

// Machine type -> index changed
void editMachineDialog::on_editMachineType_currentIndexChanged(const QString &arg1)
{
    editMachine.setType(arg1);
}
// Machine system -> index changed
void editMachineDialog::on_editMachineSystem_currentIndexChanged(const QString &arg1)
{
    editMachine.setSystem(arg1);
}

// Radio buttons -> cliked
void editMachineDialog::on_builtYesRadioButton_clicked()
{
    editMachine.setBuilt(true);
}

void editMachineDialog::on_builtNoRadioButton_clicked()
{
    editMachine.setBuilt(false);
}

// Year unknown checkbox -> cliked
void editMachineDialog::on_yearUnknownCheckbox_clicked(bool checked)
{
    if(checked){
        editMachine.setYear(0);
        ui->editMachineYear->setEnabled(false);
    }
    else{
        editMachine.setYear(ui->editMachineYear->date().year());
        ui->editMachineYear->setEnabled(true);
    }
}

// Cancel button -> clicked
void editMachineDialog::on_editMachinecancelButton_clicked()
{
    this->close();
}

// Save button -> clicked
void editMachineDialog::on_editMachineSaveButton_clicked()
{
    saveClick = true;
    this->close();
}

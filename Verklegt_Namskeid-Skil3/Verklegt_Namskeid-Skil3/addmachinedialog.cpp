#include "addmachinedialog.h"
#include "ui_addmachinedialog.h"

AddMachineDialog::AddMachineDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddMachineDialog)
{
    ui->setupUi(this);

    // Initialize addClick
    addClick = false;

    // Set initial values
    newMachine.setYear(ui->yearEdit->date().year());
    newMachine.setBuilt(true);
    newMachine.setType(ui->typeCombobox->currentText());
    newMachine.setSystem(ui->systemCombobox->currentText());

    // Verify data
    verifyInputs();
}

AddMachineDialog::~AddMachineDialog()
{
    delete ui;
}

// Get machine
Machine AddMachineDialog::getMachine(){
    return newMachine;
}

// Add to comboboxes
void AddMachineDialog::addToComboboxes(){
    // Types
    for(int i = 0; i < types.size(); i++){
        ui->typeCombobox->addItem(types[i].getName());
    }
    // Systems
    for(int i = 0; i < systems.size(); i++){
        ui->systemCombobox->addItem(systems[i].getName());
    }
}

// Set types
void AddMachineDialog::setTypes(const QVector<TypeSystem> &t){
    types = t;
}

// Set systems
void AddMachineDialog::setSystems(const QVector<TypeSystem> &s){
    systems = s;
}

// Verify inputs
void AddMachineDialog::verifyInputs(){
    bool nameValid = false;

    // Name
    if(newMachine.getName().isEmpty()){
        ui->nameField->setStyleSheet("background-color: #FFC2C2");
        nameValid = false;
    }
    else{
        ui->nameField->setStyleSheet("background-color: #FFFFFF");
        nameValid = true;
    }

    // Check valid
    if(nameValid){
        ui->addButton->setEnabled(true);
    }
    else{
        ui->addButton->setEnabled(false);
    }
}

// Get add click
bool AddMachineDialog::getAddClick(){
    return addClick;
}

// Add button -> clicked
void AddMachineDialog::on_addButton_clicked(){
    addClick = true;
    this->close();
}

// Cancel button -> clicked
void AddMachineDialog::on_cancelButton_clicked(){
    this->close();
}

// Name field -> text changed
void AddMachineDialog::on_nameField_textChanged(const QString &arg1){
    newMachine.setName(arg1);

    verifyInputs();
}

// Year edit -> date changed
void AddMachineDialog::on_yearEdit_dateChanged(const QDate &date){
    newMachine.setYear(date.year());
}

// Yes radio button -> clicked
void AddMachineDialog::on_builtYesRadioButton_clicked(){
    newMachine.setBuilt(true);
}

// No radio button -> clicked
void AddMachineDialog::on_builtNoRadioButton_clicked(){
    newMachine.setBuilt(false);
}

// Type combobox -> Index changed
void AddMachineDialog::on_typeCombobox_currentIndexChanged(const QString &arg1){
    newMachine.setType(arg1);
}

// System combobox -> Index changed
void AddMachineDialog::on_systemCombobox_currentIndexChanged(const QString &arg1){
    newMachine.setSystem(arg1);
}

// Year unknown checkbox -> clicked
void AddMachineDialog::on_yearUnknownCheckbox_clicked(bool checked){
    if(checked){
        newMachine.setYear(0);
        ui->yearEdit->setEnabled(false);
    }
    else{
        newMachine.setYear(ui->yearEdit->date().year());
        ui->yearEdit->setEnabled(true);
    }
}

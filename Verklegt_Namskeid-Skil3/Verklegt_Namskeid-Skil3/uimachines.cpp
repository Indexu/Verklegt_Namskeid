#include "mainwindow.h"
#include "ui_mainwindow.h"

// Display entire machine table
void MainWindow::displayMachinesTable(){
    // Disable edit and delete buttons
    disableEditDeleteMachineButtons();

    // Get all machines
    if(!servicesLayer.getAllMachines(machineQueryModel, error)){
        checkError();
    }

    // Update results
    updateMachineResults();
}

// Update machines results label
void MainWindow::updateMachineResults(){
    QString results = QString::number(ui->machineTable->verticalHeader()->count());

    ui->machinesResultsLabel->setText("Results: " + results);
}

// Check if re-search
void MainWindow::checkMachineSearch(){
    QString searchString = ui->machinesSearchField->text();

    // If search criteria is empty, display all
    if(searchString.isEmpty()){
        // Get all machines
        displayMachinesTable();
        return;
    }

    // Disable Machine edit and delete buttons
    disableEditDeleteMachineButtons();

    // What field is selected
    int column = ui->machinesSearchComboBox->currentIndex();

    // Search
    searchMachine(searchString, column);
}

// Disable machine edit and delete buttons
void MainWindow::disableEditDeleteMachineButtons(){
    ui->machinesDeleteButton->setEnabled(false);
    ui->machinesEditButton->setEnabled(false);
}

// Search machines
void MainWindow::searchMachine(QString searchString, int column){
    // Filter
    if(ui->machinesFilterCheckBox->isChecked()){
        // Call filterPerson
        if(!servicesLayer.filterMachine(machineQueryModel, searchString, column, error)){
            checkError();
            return;
        }
    }
    //Search
    else{
        // Call searchPerson
        if(!servicesLayer.searchMachine(machineQueryModel, searchString, column, error)){
            checkError();
            return;
        }
    }

    // Update results
    updateMachineResults();
}

// Machines filter checkbox -> clicked
void MainWindow::on_machinesFilterCheckBox_clicked(){
    checkMachineSearch();
}

// Machines search combobox -> Index changed
void MainWindow::on_machinesSearchComboBox_currentIndexChanged(int index){
    QString searchString = ui->machinesSearchField->text();

    // If search criteria is empty, display all
    if(searchString.isEmpty()){
        // Get all machines
        displayMachinesTable();
        return;
    }

    // Disable Machine edit and delete buttons
    disableEditDeleteMachineButtons();

    // Search
    searchMachine(searchString, index);
}

// Machines search field -> Text changed
void MainWindow::on_machinesSearchField_textChanged(const QString &arg1){
    // If search criteria is empty, display all
    if(arg1.isEmpty()){
        // Get all machines
        displayMachinesTable();
        return;
    }

    // Disable Machine edit and delete buttons
    disableEditDeleteMachineButtons();

    // What field is selected
    int column = ui->machinesSearchComboBox->currentIndex();

    // Search
    searchMachine(arg1, column);
}

// Machine add button -> Clicked
void MainWindow::on_machinesAddButton_clicked(){
    // Display dialog
    AddMachineDialog addDialog;

    QVector<TypeSystem> types;

    // Get types
    if(!servicesLayer.getAllTypesSystems(types, 1, error)){
        checkError();
        return;
    }

    // Set types
    addDialog.setTypes(types);

    QVector<TypeSystem> systems;

    // Get systems
    if(!servicesLayer.getAllTypesSystems(systems, 0, error)){
        checkError();
        return;
    }
    // Set systems
    addDialog.setSystems(systems);

    // Add to comboboxes
    addDialog.addToComboboxes();

    // Window
    addDialog.exec();

    // Confirm add
    if(addDialog.getAddClick()){
        // Disable Person edit and delete buttons
        disableEditDeletePersonButtons();
        // The new machine
        Machine newMachine = addDialog.getMachine();

        // Get type ID
        int type_id = 0;
        for(int i = 0; i < types.size(); i++){
            if(newMachine.getType() == types[i].getName()){
                type_id = types[i].getId();
                break;
            }
        }

        // Get system ID
        int system_id = 0;
        for(int i = 0; i < systems.size(); i++){
            if(newMachine.getSystem() == systems[i].getName()){
                system_id = systems[i].getId();
                break;
            }
        }

        // Add
        if(!servicesLayer.addMachine(newMachine, type_id, system_id, error)){
            checkError();
            return;
        }
        else{
            checkMachineSearch();
        }

        // Status bar message
        ui->statusBar->showMessage(addDialog.getMachine().getName() + " added", constants::STATUSBAR_MESSAGE_TIME);
    }
}

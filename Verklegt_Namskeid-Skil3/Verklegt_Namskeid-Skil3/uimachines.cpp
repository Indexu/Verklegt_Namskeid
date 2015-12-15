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


// Enable machine edit and delete buttons
void MainWindow::enableEditDeleteMachineButtons(){
    ui->machinesDeleteButton->setEnabled(true);
    ui->machinesEditButton->setEnabled(true);
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

// Delete machine
void MainWindow::deleteMachine(){
    // Get row
    QModelIndexList selection = ui->machineTable->selectionModel()->selectedRows();

    // No rows
    if (selection.isEmpty()) {
        return;
    }

    int numRows = selection.count();
    QString deleteConfirmMessage = "";
    QString statusBarMessage = "";

    QVector<Machine> machinesToBeDeleted;

    for(int i = 0; i < numRows;i++){
        // Get first column (id)
        QModelIndex index = selection.at(i);
        // Get id column data
        int id = ui->machineTable->model()->data(index).toInt();

        // An empty person
        Machine m;
        // Set person ID to the ID of the row
        m.setId(id);

        // Get the person info by ID
        if(!servicesLayer.getMachine(m, error)){
            checkError();
            return;
        }

        // Add to vector
        machinesToBeDeleted.push_back(m);
    }

    // Single row
    if(numRows == 1){
        deleteConfirmMessage = "Are you sure you want to delete " + machinesToBeDeleted[0].getName() + "?";
        statusBarMessage = machinesToBeDeleted[0].getName() + " deleted";
    }
    // Rows less than 11
    else if(numRows > 1 && numRows < 11){

        deleteConfirmMessage = "Are you sure you want to delete:\n";

        // Loop over names
        for(int i = 0; i < numRows;i++){
            deleteConfirmMessage += machinesToBeDeleted[i].getName() + "\n";
        }

        statusBarMessage = QString::number(numRows) + " entries deleted";
    }
    // More than 10
    else{
        deleteConfirmMessage = "Are you sure you want to delete these " + QString::number(selection.count()) + " entries?";
        statusBarMessage = QString::number(numRows) + " entries deleted";
    }

    // Confirmation window
    int ans = QMessageBox::question(this, "Confirmation", deleteConfirmMessage, QMessageBox::Yes|QMessageBox::No, QMessageBox::No);
    // Check answer
    if (ans == QMessageBox::Yes) {
        // Delete
        if(!servicesLayer.deleteMachine(machinesToBeDeleted, error)){
            checkError();
            return;
        }

        // Disable Person edit and delete buttons
        disableEditDeleteMachineButtons();

        // Status bar update
        ui->statusBar->showMessage(statusBarMessage, constants::STATUSBAR_MESSAGE_TIME);

        // Re-display
        checkMachineSearch();
    }
}

void MainWindow::connectToPerson(){
    // Get row
    QModelIndexList selection = ui->machineTable->selectionModel()->selectedRows();

    // No rows
    if (selection.isEmpty()) {
        return;
    }

    // Get first column (id)
    QModelIndex index = selection.at(0);
    // Get id column data
    int m_id = ui->machineTable->model()->data(index).toInt();

    ConnectToPerson connectionDialog;

    // Setup
    connectionDialog.setModel(personProxyModel);
    connectionDialog.displayTable();

    // Connect
    if(connectionDialog.exec()){
        // Get person ID
        int p_id = connectionDialog.getId();

        // Make the connection
        if(!servicesLayer.addConnection(p_id, m_id, error)){
            checkError();
            return;
        }
        else{
            // Get the machine
            Machine m;
            m.setId(m_id);
            if(!servicesLayer.getMachine(m, error)){
                checkError();
                return;
            }

            // Get the person
            Person p;
            p.setId(p_id);
            if(!servicesLayer.getPerson(p, error)){
                checkError();
                return;
            }

            QString statusBarMessage = "Connected " + m.getName() + " and " + p.getName();

            ui->statusBar->showMessage(statusBarMessage, constants::STATUSBAR_MESSAGE_TIME);

            // Refresh connections table
            displayConnectionsTable();
        }
    }
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

// Delete machine button -> clicked
void MainWindow::on_machinesDeleteButton_clicked(){
    deleteMachine();
}

// Machine table -> clicked
void MainWindow::on_machineTable_clicked(const QModelIndex &index){
    if(index.isValid()){
        // Enable delete button
        ui->machinesDeleteButton->setEnabled(true);
        // Enable edit button
        ui->machinesEditButton->setEnabled(true);
    }
}

// Edit machine button -> click
void MainWindow::on_machinesEditButton_clicked()
{
    editMachine();
}

// Machine table -> double clicked
void MainWindow::on_machineTable_doubleClicked(const QModelIndex &index)
{
    editMachine();
}

// Edit machine function
void MainWindow::editMachine() {
    // Edit machine dialog
    editMachineDialog editDialog;

    QVector<TypeSystem> types;

    // Get types
    if(!servicesLayer.getAllTypesSystems(types, 1, error)){
        checkError();
        return;
    }

    // Set types
    editDialog.setTypes(types);

    QVector<TypeSystem> systems;

    // Get systems
    if(!servicesLayer.getAllTypesSystems(systems, 0, error)){
        checkError();
        return;
    }

    // Set systems
    editDialog.setSystems(systems);

    // Add to comboboxes
    editDialog.addToComboboxes();

    // Get row
    QModelIndexList selection = ui->machineTable->selectionModel()->selectedRows();

    // If no rows
    if (selection.isEmpty() || selection.count() > 1) {
        qDebug() << "Only one row can be edited at a time";
        return;
    }

    QModelIndex index = selection.at(0);
    // Get ID
    int id = ui->machineTable->model()->data(index).toInt();

    // Create an empty machine
    Machine m;
    // Set machine ID to the ID of the row
    m.setId(id);

    // Get the person info by ID
    if(!servicesLayer.getMachine(m, error)){
        checkError();
        return;
    }

    // Set machine's initial values
    editDialog.setMachine(m);
    // Set field values
    editDialog.setFields();
    // Exec window
    editDialog.exec();

    // Disable edit/delete buttons
    disableEditDeleteMachineButtons();

    // Check if 'save' button was clicked
    if (editDialog.getSaveClick()) {
        // Get the edited machine
        m = editDialog.getMachine();

        // Get type ID
        int type_id = 0;
        for(int i = 0; i < types.size(); i++){
            if(m.getType() == types[i].getName()){
                type_id = types[i].getId();
                break;
            }
        }

        // Get system ID
        int system_id = 0;
        for(int i = 0; i < systems.size(); i++){
            if(m.getSystem() == systems[i].getName()){
                system_id = systems[i].getId();
                break;
            }
        }
        // Edit machine in DB
        if(!servicesLayer.editMachine(m, type_id, system_id, error)){
            checkError();
            return;
        }
        else{
            checkMachineSearch();
        }
        // Status bar message
        ui->statusBar->showMessage(editDialog.getMachine().getName() + " edited", constants::STATUSBAR_MESSAGE_TIME);
    }


// Machine table -> Context menu
/*
 * QPoint &pos is not used due to when it's used
 * it returns the context menu a bit above the cursor.
 * QCursor::pos is used instead.
 */
void MainWindow::on_machineTable_customContextMenuRequested(const QPoint &pos){
    // Get row
    QModelIndexList selection = ui->machineTable->selectionModel()->selectedRows();

    // No rows
    if (selection.isEmpty()) {
        return;
    }
    // Multiple rows
    else if(selection.count() > 1){
        // Disable Connection option
        machineContextMenu.actions().at(0)->setEnabled(false);
        // Disable Edit option
        machineContextMenu.actions().at(1)->setEnabled(false);
    }
    else{
        // Enable Connection option
        machineContextMenu.actions().at(0)->setEnabled(true);
        // Enable Edit option
        machineContextMenu.actions().at(1)->setEnabled(true);
    }

    // Display menu
    machineContextMenu.exec(QCursor::pos());
}

// Machine context menu -> Delete
void MainWindow::on_actionDeleteMachine_triggered(){
    deleteMachine();
}

// Machine context menu -> Edit
void MainWindow::on_actionEditMachine_triggered(){
    editMachine();
}

// Machine context menu -> Connect
void MainWindow::on_actionConnectToPerson_triggered(){
    connectToPerson();
}

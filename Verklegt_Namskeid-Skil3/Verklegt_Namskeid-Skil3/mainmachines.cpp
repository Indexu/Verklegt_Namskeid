#include "mainwindow.h"
#include "ui_mainwindow.h"

// Display entire machine table
void MainWindow::displayMachinesTable(){
    // Disable edit and delete buttons
    disableEditDeleteMachineButtons();

    // Get all machines
    if(!servicesLayer.getAllMachines(machineQueryModel, error)){
        checkError();
        return;
    }

    // Reset search field
    ui->machinesSearchField->setText("");

    // Resize columns
    utilities::resizeTableColumns(ui->machineTable);

    // Update results
    updateMachineResults();
}

// Update machines results label
void MainWindow::updateMachineResults(){
    QString results = QString::number(ui->machineTable->verticalHeader()->count());

    ui->machinesResultsLabel->setText("Results: " + results);
}

// Disable machine edit and delete buttons
void MainWindow::disableEditDeleteMachineButtons(){
    ui->machinesDeleteButton->setEnabled(false);
    ui->machinesEditButton->setEnabled(false);
}

// === SEARCH ===
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

    // Resize columns
    utilities::resizeTableColumns(ui->machineTable);

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

// === DELETE ===
// Delete machine
void MainWindow::deleteMachine(){
    QVector<int> ids = utilities::getSelectedTableViewIds(ui->machineTable);

    // No rows
    if (ids.isEmpty()) {
        return;
    }

    int numRows = ids.size();
    QString deleteConfirmMessage = "";
    QString statusBarMessage = "";

    // Get all the machines that are about to be deleted
    QVector<Machine> machinesToBeDeleted;
    for(int i = 0; i < numRows;i++){
        // An empty machine
        Machine m;
        // Set machine ID to the ID of the row
        m.setId(ids[i]);

        // Get the machine info by ID
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
        deleteConfirmMessage = "Are you sure you want to delete these " + QString::number(numRows) + " entries?";
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
        displayConnectionsTable();
    }
}

// === CONNECT ===
// Connect to person
void MainWindow::connectToPerson(){
    QVector<int> ids = utilities::getSelectedTableViewIds(ui->machineTable);

    // No rows
    if (ids.isEmpty()) {
        return;
    }

    int m_id = ids[0];

    ConnectToPerson connectionDialog;

    // Reset Person model
    displayPersonTable();

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

// === BUTTONS ===
// Machine add button -> Clicked
void MainWindow::on_machinesAddButton_clicked(){
    // Display dialog
    AddMachineDialog addDialog;

    QVector<TypeSystem> types;

    // Get types
    if(!servicesLayer.getAllTypesSystemsVector(types, 1, error)){
        checkError();
        return;
    }

    // Set types
    addDialog.setTypes(types);

    QVector<TypeSystem> systems;

    // Get systems
    if(!servicesLayer.getAllTypesSystemsVector(systems, 0, error)){
        checkError();
        return;
    }
    // Set systems
    addDialog.setSystems(systems);

    // Add to comboboxes
    addDialog.addToComboboxes();

    // Confirm add
    if(addDialog.exec()){
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
/*
 * Used in conjunction with currentRowChanged to have
 * desired effect of enabling and disabling buttons
 */
void MainWindow::on_machineTable_clicked(const QModelIndex &index){
    if(index.isValid()){
        // Get rows
        QModelIndexList selection = ui->machineTable->selectionModel()->selectedRows();

        // If multiple rows
        if (selection.count() > 1) {
            // Disable edit button
            ui->machinesEditButton->setEnabled(false);
        }
        // Single selection
        else{
            // Enable edit button
            ui->machinesEditButton->setEnabled(true);
        }
    }
}

// Machine table -> Current row changes
/*
 * QModelIndex &current and QModelIndex &previous are not
 * sed simply because we only want the functionality of
 * the QItemSelectionModel::CurrentRowChanged() signal
 */
void MainWindow::machineTableCurrentRowChanged(const QModelIndex &current, const QModelIndex &previous){
    if(current.isValid()){
        // Enable delete button
        ui->machinesDeleteButton->setEnabled(true);

        // Get rows
        QModelIndexList selection = ui->machineTable->selectionModel()->selectedRows();

        // If multiple rows
        if (selection.count() > 1) {
            // Disable edit button
            ui->machinesEditButton->setEnabled(false);
        }
        // Single selection
        else{
            // Enable edit button
            ui->machinesEditButton->setEnabled(true);
        }
    }
}

// Edit machine button -> click
void MainWindow::on_machinesEditButton_clicked()
{
    editMachine();
}

// Machine table -> double clicked
void MainWindow::on_machineTable_doubleClicked(const QModelIndex &index){
    if(index.isValid()){
        editMachine();
    }
}

// === EDIT ===
// Edit machine function
void MainWindow::editMachine() {
    // Get IDs
    QVector<int> ids = utilities::getSelectedTableViewIds(ui->machineTable);

    // If empty or more than one
    if (ids.size() != 1) {
        return;
    }

    int id = ids[0];

    QVector<TypeSystem> types;
    // Get types
    if(!servicesLayer.getAllTypesSystemsVector(types, 1, error)){
        checkError();
        return;
    }

    QVector<TypeSystem> systems;
    // Get systems
    if(!servicesLayer.getAllTypesSystemsVector(systems, 0, error)){
        checkError();
        return;
    }

    // Edit machine dialog
    editMachineDialog editDialog;

    // Set types
    editDialog.setTypes(types);
    // Set systems
    editDialog.setSystems(systems);

    // Add to comboboxes
    editDialog.addToComboboxes();

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

    // Check if 'save' button was clicked
    if (editDialog.exec()) {
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
            displayConnectionsTable();
        }
        // Status bar message
        ui->statusBar->showMessage(editDialog.getMachine().getName() + " edited", constants::STATUSBAR_MESSAGE_TIME);

        // Disable edit/delete buttons
        disableEditDeleteMachineButtons();
    }
}

// === CONTEXT MENU ===
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


#include "mainwindow.h"
#include "ui_mainwindow.h"

// Display entire systems table
void MainWindow::displaySystemsTable(){
    // Disable delete button
    disableEditDeleteSystemButtons();

    // Get all systems
    if(!servicesLayer.getAllSystems(systemQueryModel, error)){
        checkError();
    }

    // Resize columns
    utilities::resizeTableColumns(ui->systemsTable);

    // Update results
    updateSystemResults();
}

// Update results label
void MainWindow::updateSystemResults(){
    QString results = QString::number(ui->systemsTable->verticalHeader()->count());

    ui->systemResultLabel->setText("Results: " + results);
}

// Disable edit and delete buttons
void MainWindow::disableEditDeleteSystemButtons(){
    ui->systemDeleteButton->setEnabled(false);
    ui->systemEditButton->setEnabled(false);
}

// ==== SEARCH ====
// Search system
void MainWindow::searchSystem(QString searchString, int column){
    if(ui->systemFilterCheckBox->isChecked()){
        // Call filtersystem
        if(!servicesLayer.filterSystem(systemQueryModel, searchString, column, error)){
            checkError();
            return;
        }
    }
    else{
        // Call searchSystem
        if(!servicesLayer.searchSystem(systemQueryModel, searchString, column, error)){
            checkError();
            return;
        }
    }

    // Resize columns
    utilities::resizeTableColumns(ui->systemsTable);

    // Update results
    updateSystemResults();
}

// Filter checkbox -> clicked
void MainWindow::on_systemFilterCheckBox_clicked(){
    checkSystemSearch();
}

// Check if need for re-search
void MainWindow::checkSystemSearch(){
    QString searchString = ui->systemSearchField->text();

    // If search criteria is empty, display all
    if(searchString.isEmpty()){
        // Get all systems
        displaySystemsTable();
        return;
    }

    // Disable system edit and delete buttons
    disableEditDeleteSystemButtons();

    // What field is selected
    int column = ui->systemSearchComboBox->currentIndex();

    // Search
    searchSystem(searchString, column);
}

// Search combobox -> index changed
void MainWindow::on_systemSearchComboBox_currentIndexChanged(int index){
    QString searchString = ui->systemSearchField->text();

    // If search criteria is empty, display all
    if(searchString.isEmpty()){
        // Get all systems
        displaySystemsTable();
        return;
    }

    // Disable system edit and delete buttons
    disableEditDeleteSystemButtons();

    // Search
    searchSystem(searchString, index);
}

// Search field -> text changed
void MainWindow::on_systemSearchField_textChanged(const QString &arg1){
    // If search criteria is empty, display all
    if(arg1.isEmpty()){
        // Get all systems
        displaySystemsTable();
        return;
    }

    // Disable system edit and delete buttons
    disableEditDeleteSystemButtons();

    // What field is selected
    int column = ui->systemSearchComboBox->currentIndex();

    // Search
    searchSystem(arg1, column);
}

// ==== DELETE ====
// Delete system
void MainWindow::deleteSystem(){
    QVector<int> ids = utilities::getSelectedTableViewIds(ui->systemsTable);

    // No rows
    if (ids.isEmpty()) {
        return;
    }

    int numRows = ids.size();
    QString deleteConfirmMessage = "";
    QString statusBarMessage = "";

    // Get all the machines that are about to be deleted
    QVector<TypeSystem> systemsToBeDeleted;
    for(int i = 0; i < numRows;i++){
        // An empty machine
        TypeSystem ts;
        // Set machine ID to the ID of the row
        ts.setId(ids[i]);

        // Get the machine info by ID
        if(!servicesLayer.getTypeSystem(ts, 0, error)){
            checkError();
            return;
        }

        // Add to vector
        systemsToBeDeleted.push_back(ts);
    }

    // Single row
    if(numRows == 1){
        deleteConfirmMessage = "Are you sure you want to delete " + systemsToBeDeleted[0].getName() + "?";
        statusBarMessage = systemsToBeDeleted[0].getName() + " deleted";
    }
    // Rows less than 11
    else if(numRows > 1 && numRows < 11){

        deleteConfirmMessage = "Are you sure you want to delete:\n";

        // Loop over names
        for(int i = 0; i < numRows;i++){
            deleteConfirmMessage += systemsToBeDeleted[i].getName() + "\n";
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
        if(!servicesLayer.deleteTypeSystem(systemsToBeDeleted, 0, error)){
            checkError();
            return;
        }

        // Disable Person edit and delete buttons
        disableEditDeleteSystemButtons();

        // Status bar update
        ui->statusBar->showMessage(statusBarMessage, constants::STATUSBAR_MESSAGE_TIME);

        // Re-display
        checkSystemSearch();
        displayMachinesTable();
    }
}

// === EDIT ===
// Edit system
void MainWindow::editSystem(){
    QVector<int> ids = utilities::getSelectedTableViewIds(ui->systemsTable);

    // No rows or more than 1
    if (ids.size() != 1) {
        return;
    }

    // An empty person
    TypeSystem ts;
    // Set person ID to the ID of the row
    ts.setId(ids[0]);

    // Get the person info by ID
    if(!servicesLayer.getTypeSystem(ts, 0, error)){
        checkError();
        return;
    }

    // Edit dialog
    EditTypeSystemDialog editDialog;
    // Forward person to edit dialog
    editDialog.setName(ts.getName());
    // Set the fields
    editDialog.setFields();
    // Set title
    editDialog.setTitle("Edit System");

    // If saved
    if (editDialog.exec()) {

        ts.setName(editDialog.getName());

        // If error, show error, else update table
        if (!servicesLayer.editTypeSystem(ts, 0, error)) {
            checkError();
            return;
        }
        else{
            checkSystemSearch();
            displayMachinesTable();
        }

        // Set status bar message
        ui->statusBar->showMessage(ts.getName() + " edited", constants::STATUSBAR_MESSAGE_TIME);

        // Disable Person edit and delete buttons
        disableEditDeleteSystemButtons();
    }
}

// === BUTTONS ===
// Add system
void MainWindow::on_systemAddButton_clicked(){
    // Display dialog
    AddTypeSystemDialog addDialog;

    addDialog.setTitle("Add System");

    // Confirm add
    if(addDialog.exec()){
        // Disable system edit and delete buttons
        disableEditDeleteSystemButtons();

        // Add
        if(!servicesLayer.addTypeSystem(addDialog.getName(), 0, error)){
            checkError();
            return;
        }
        else{
            checkSystemSearch();
        }

        // Status bar message
        ui->statusBar->showMessage(addDialog.getName() + " added", constants::STATUSBAR_MESSAGE_TIME);
    }
}

// Edit button -> clicked
void MainWindow::on_systemEditButton_clicked(){
    editSystem();
}

// Systems table -> double clicked
void MainWindow::on_systemsTable_doubleClicked(const QModelIndex &index){
    if(index.isValid()){
        editSystem();
    }
}

// Delete button -> clicked
void MainWindow::on_systemDeleteButton_clicked(){
    deleteSystem();
}

// systems table -> clicked
/*
 * Used in conjunction with currentRowChanged to have
 * desired effect of enabling and disabling buttons
 */
void MainWindow::on_systemsTable_clicked(const QModelIndex &index){
    if(index.isValid()){
        // Get rows
        QModelIndexList selection = ui->systemsTable->selectionModel()->selectedRows();

        // If multiple rows
        if (selection.count() > 1) {
            // Disable edit button
            ui->systemEditButton->setEnabled(false);
        }
        // Single selection
        else{
            // Enable edit button
            ui->systemEditButton->setEnabled(true);
        }
    }
}


// Person table -> Current row changes
/*
 * QModelIndex &previous is not used simply
 * because we only want the functionality of
 * the QItemSelectionModel::CurrentRowChanged()
 * signal
 */
void MainWindow::systemsTableCurrentRowChanged(const QModelIndex &current, const QModelIndex &previous){
    if(current.isValid()){
        // Enable delete button
        ui->systemDeleteButton->setEnabled(true);

        // Get rows
        QModelIndexList selection = ui->systemsTable->selectionModel()->selectedRows();

        // If multiple rows
        if (selection.count() > 1) {
            // Disable edit button
            ui->systemEditButton->setEnabled(false);
        }
        // Single selection
        else{
            // Enable edit button
            ui->systemEditButton->setEnabled(true);
        }
    }
}

// ==== CONTEXT MENU ====
// system table context menu -> Delete
void MainWindow::on_actionDeleteSystem_triggered(){
    deleteSystem();
}

// system table context menu -> Edit
void MainWindow::on_actionEditSystem_triggered(){
    editSystem();
}

// system table -> Context menu
/*
 * QPoint &pos is not used due to when it's used
 * it returns the context menu a bit above the cursor.
 * QCursor::pos is used instead.
 */
void MainWindow::on_systemsTable_customContextMenuRequested(const QPoint &pos){
    // Get row
    QModelIndexList selection = ui->systemsTable->selectionModel()->selectedRows();

    // No rows
    if (selection.isEmpty()) {
        return;
    }
    // Multiple rows
    else if(selection.count() > 1){
        // Disable Edit option
        systemContextMenu.actions().at(1)->setEnabled(false);
    }
    else{
        // Enable Edit option
        systemContextMenu.actions().at(1)->setEnabled(true);
    }

    // Display menu
    systemContextMenu.exec(QCursor::pos());
}

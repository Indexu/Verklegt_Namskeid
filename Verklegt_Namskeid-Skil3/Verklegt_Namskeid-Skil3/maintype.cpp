#include "mainwindow.h"
#include "ui_mainwindow.h"

// Display entire types table
void MainWindow::displayTypesTable(){
    // Disable delete button
    disableEditDeleteTypeButtons();

    // Get all types
    if(!servicesLayer.getAllTypesSystems(typeQueryModel, error)){
        checkError();
    }

    // Resize columns
    utilities::resizeTableColumns(ui->typesTable);

    // Update results
    updateTypeResults();
}

// Update results label
void MainWindow::updateTypeResults(){
    QString results = QString::number(ui->typesTable->verticalHeader()->count());

    ui->typesResultLabel->setText("Results: " + results);
}

// Disable edit and delete buttons
void MainWindow::disableEditDeleteTypeButtons(){
    ui->typeDeleteButton->setEnabled(false);
    ui->typeEditButton->setEnabled(false);
}

// ==== SEARCH ====
// Search type
void MainWindow::searchType(QString searchString, int column){
    if(ui->typeFilterCheckBox->isChecked()){
        // Call filterType
        if(!servicesLayer.filterType(typeQueryModel, searchString, column, error)){
            checkError();
            return;
        }
    }
    else{
        // Call searchType
        if(!servicesLayer.searchType(typeQueryModel, searchString, column, error)){
            checkError();
            return;
        }
    }

    // Resize columns
    utilities::resizeTableColumns(ui->typesTable);

    // Update results
    updateTypeResults();
}

// Filter checkbox -> clicked
void MainWindow::on_typeFilterCheckBox_clicked(){
    checkTypeSearch();
}

// Check if need for re-search
void MainWindow::checkTypeSearch(){
    QString searchString = ui->typeSearchField->text();

    // If search criteria is empty, display all
    if(searchString.isEmpty()){
        // Get all types
        displayTypesTable();
        return;
    }

    // Disable Type edit and delete buttons
    disableEditDeleteTypeButtons();

    // What field is selected
    int column = ui->typesSearchComboBox->currentIndex();

    // Search
    searchType(searchString, column);
}

// Search combobox -> index changed
void MainWindow::on_typesSearchComboBox_currentIndexChanged(int index){
    QString searchString = ui->typeSearchField->text();

    // If search criteria is empty, display all
    if(searchString.isEmpty()){
        // Get all types
        displayTypesTable();
        return;
    }

    // Disable Type edit and delete buttons
    disableEditDeleteTypeButtons();

    // Search
    searchType(searchString, index);
}

// Search field -> text changed
void MainWindow::on_typeSearchField_textChanged(const QString &arg1){
    // If search criteria is empty, display all
    if(arg1.isEmpty()){
        // Get all types
        displayTypesTable();
        return;
    }

    // Disable Type edit and delete buttons
    disableEditDeleteTypeButtons();

    // What field is selected
    int column = ui->typesSearchComboBox->currentIndex();

    // Search
    searchType(arg1, column);
}

// ==== DELETE ====
// Delete type
void MainWindow::deleteType(){
    QVector<int> ids = utilities::getSelectedTableViewIds(ui->typesTable);

    // No rows
    if (ids.isEmpty()) {
        return;
    }

    int numRows = ids.size();
    QString deleteConfirmMessage = "";
    QString statusBarMessage = "";

    // Get all the machines that are about to be deleted
    QVector<TypeSystem> typesToBeDeleted;
    for(int i = 0; i < numRows;i++){
        // An empty machine
        TypeSystem ts;
        // Set machine ID to the ID of the row
        ts.setId(ids[i]);

        // Get the machine info by ID
        if(!servicesLayer.getTypeSystem(ts, 1, error)){
            checkError();
            return;
        }

        // Add to vector
        typesToBeDeleted.push_back(ts);
    }

    // Single row
    if(numRows == 1){
        deleteConfirmMessage = "Are you sure you want to delete " + typesToBeDeleted[0].getName() + "?";
        statusBarMessage = typesToBeDeleted[0].getName() + " deleted";
    }
    // Rows less than 11
    else if(numRows > 1 && numRows < 11){

        deleteConfirmMessage = "Are you sure you want to delete:\n";

        // Loop over names
        for(int i = 0; i < numRows;i++){
            deleteConfirmMessage += typesToBeDeleted[i].getName() + "\n";
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
        if(!servicesLayer.deleteTypeSystem(typesToBeDeleted, 1, error)){
            checkError();
            return;
        }

        // Disable Person edit and delete buttons
        disableEditDeleteTypeButtons();

        // Status bar update
        ui->statusBar->showMessage(statusBarMessage, constants::STATUSBAR_MESSAGE_TIME);

        // Re-display
        checkTypeSearch();
        displayMachinesTable();
    }
}

// === EDIT ===
// Edit type
void MainWindow::editType(){
    QVector<int> ids = utilities::getSelectedTableViewIds(ui->typesTable);

    // No rows or more than 1
    if (ids.size() != 1) {
        return;
    }

    // An empty person
    TypeSystem ts;
    // Set person ID to the ID of the row
    ts.setId(ids[0]);

    // Get the person info by ID
    if(!servicesLayer.getTypeSystem(ts, 1, error)){
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
    editDialog.setTitle("Edit Type");

    // If saved
    if (editDialog.exec()) {

        ts.setName(editDialog.getName());

        // If error, show error, else update table
        if (!servicesLayer.editTypeSystem(ts, 1, error)) {
            checkError();
            return;
        }
        else{
            checkTypeSearch();
            displayMachinesTable();
        }

        // Set status bar message
        ui->statusBar->showMessage(ts.getName() + " edited", constants::STATUSBAR_MESSAGE_TIME);

        // Disable Person edit and delete buttons
        disableEditDeleteTypeButtons();
    }
}

// === BUTTONS ===
// Add type
void MainWindow::on_typeAddButton_clicked(){
    // Display dialog
    AddTypeSystemDialog addDialog;

    addDialog.setTitle("Add Type");

    // Confirm add
    if(addDialog.exec()){
        // Disable Type edit and delete buttons
        disableEditDeleteTypeButtons();

        // Add
        if(!servicesLayer.addTypeSystem(addDialog.getName(), 1, error)){
            checkError();
            return;
        }
        else{
            checkTypeSearch();
        }

        // Status bar message
        ui->statusBar->showMessage(addDialog.getName() + " added", constants::STATUSBAR_MESSAGE_TIME);
    }
}

// Edit button -> clicked
void MainWindow::on_typeEditButton_clicked(){
    editType();
}

// Types table -> double clicked
void MainWindow::on_typesTable_doubleClicked(const QModelIndex &index){
    if(index.isValid()){
        editType();
    }
}


// Delete button -> clicked
void MainWindow::on_typeDeleteButton_clicked(){
    deleteType();
}

// Types table -> clicked
/*
 * Used in conjunction with currentRowChanged to have
 * desired effect of enabling and disabling buttons
 */
void MainWindow::on_typesTable_clicked(const QModelIndex &index){
    if(index.isValid()){
        // Get rows
        QModelIndexList selection = ui->typesTable->selectionModel()->selectedRows();

        // If multiple rows
        if (selection.count() > 1) {
            // Disable edit button
            ui->typeEditButton->setEnabled(false);
        }
        // Single selection
        else{
            // Enable edit button
            ui->typeEditButton->setEnabled(true);
        }
    }
}

// Types table -> double clicked
void MainWindow::on_typesTable_doubleClicked(const QModelIndex &index){
    editType();
}

// Person table -> Current row changes
/*
 * QModelIndex &previous is not used simply
 * because we only want the functionality of
 * the QItemSelectionModel::CurrentRowChanged()
 * signal
 */
void MainWindow::typesTableCurrentRowChanged(const QModelIndex &current, const QModelIndex &previous){
    if(current.isValid()){
        // Enable delete button
        ui->typeDeleteButton->setEnabled(true);

        // Get rows
        QModelIndexList selection = ui->typesTable->selectionModel()->selectedRows();

        // If multiple rows
        if (selection.count() > 1) {
            // Disable edit button
            ui->typeEditButton->setEnabled(false);
        }
        // Single selection
        else{
            // Enable edit button
            ui->typeEditButton->setEnabled(true);
        }
    }
}

// ==== CONTEXT MENU ====
// Type table context menu -> Delete
void MainWindow::on_actionDeleteType_triggered(){
    deleteType();
}

// Type table context menu -> Edit
void MainWindow::on_actionEditType_triggered(){
    editType();
}

// Type table -> Context menu
/*
 * QPoint &pos is not used due to when it's used
 * it returns the context menu a bit above the cursor.
 * QCursor::pos is used instead.
 */
void MainWindow::on_typesTable_customContextMenuRequested(const QPoint &pos){
    // Get row
    QModelIndexList selection = ui->typesTable->selectionModel()->selectedRows();

    // No rows
    if (selection.isEmpty()) {
        return;
    }
    // Multiple rows
    else if(selection.count() > 1){
        // Disable Edit option
        typeContextMenu.actions().at(1)->setEnabled(false);
    }
    else{
        // Enable Edit option
        typeContextMenu.actions().at(1)->setEnabled(true);
    }

    // Display menu
    typeContextMenu.exec(QCursor::pos());
}

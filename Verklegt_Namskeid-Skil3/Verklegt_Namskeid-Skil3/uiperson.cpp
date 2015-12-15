#include "mainwindow.h"
#include "ui_mainwindow.h"

// Display entire person table
void MainWindow::displayPersonTable(){
    // Disable Person edit and delete buttons
    disableEditDeletePersonButtons();

    // Get all persons
    if(!servicesLayer.getAllPersons(personQueryModel, error)){
        checkError();
        return;
    }

    // Update results
    updatePersonResults();
}

// Update the persons label displaying the number of results
void MainWindow::updatePersonResults(){
    QString results = QString::number(ui->personTable->verticalHeader()->count());

    ui->personResultsLabel->setText("Results: " + results);
}

// Disable Person edit and delete buttons
void MainWindow::disableEditDeletePersonButtons(){
    // Disable delete button
    ui->personDeleteButton->setEnabled(false);
    // Disable edit button
    ui->personEditButton->setEnabled(false);
}

// === SEARCH ===
// Check search
void MainWindow::checkPersonSearch(){
    // Search string
    QString searchString = ui->personSearchField->text();

    // If search criteria is empty, display all
    if(searchString.isEmpty()){
        // Get all persons
        displayPersonTable();
        return;
    }

    // What field is selected
    int column = ui->personSearchComboBox->currentIndex();

    // Search
    searchPerson(searchString, column);
}

// Person search
void MainWindow::searchPerson(QString searchString, int column){
    // Filter
    if(ui->personFilterCheckBox->isChecked()){
        // Call filterPerson
        if(!servicesLayer.filterPerson(personQueryModel, searchString, column, error)){
            checkError();
            return;
        }
    }
    //Search
    else{
        // Call searchPerson
        if(!servicesLayer.searchPerson(personQueryModel, searchString, column, error)){
            checkError();
            return;
        }
    }

    // Update results
    updatePersonResults();
}

// Person search field -> Text changed
void MainWindow::on_personSearchField_textChanged(const QString &arg1){
    // Disable Person edit and delete buttons
    disableEditDeletePersonButtons();

    // If search criteria is empty, display all
    if(arg1.isEmpty()){
        // Get all persons
        displayPersonTable();
        return;
    }

    // What field is selected
    int column = ui->personSearchComboBox->currentIndex();

    // Search
    searchPerson(arg1, column);
}

// Person search combobox -> Index changed
void MainWindow::on_personSearchComboBox_currentIndexChanged(int index){
    // Disable Person edit and delete buttons
    disableEditDeletePersonButtons();

    // Search string
    QString searchString = ui->personSearchField->text();

    // If search criteria is empty, display all
    if(searchString.isEmpty()){
        // Get all persons
        displayPersonTable();
        return;
    }

    // Search
    searchPerson(searchString, index);
}

// Person filter checkbox -> Clicked
void MainWindow::on_personFilterCheckBox_clicked(){
    // Disable Person edit and delete buttons
    disableEditDeletePersonButtons();

    checkPersonSearch();
}

// === BUTTONS ===
// Person add button -> clicked
void MainWindow::on_personAddButton_clicked(){
    // Display dialog
    AddPersonDialog addDialog;
    addDialog.exec();

    // Confirm add
    if(addDialog.getAddClick()){
        // Disable Person edit and delete buttons
        disableEditDeletePersonButtons();

        // Add
        if(!servicesLayer.addPerson(addDialog.getPerson(), error)){
            checkError();
            return;
        }
        else{
            checkPersonSearch();
        }

        // Status bar message
        ui->statusBar->showMessage(addDialog.getPerson().getName() + " added", constants::STATUSBAR_MESSAGE_TIME);
    }
}

// Person delete button -> clicked
void MainWindow::on_personDeleteButton_clicked(){
    deletePerson();
}

// Person edit button -> clicked
void MainWindow::on_personEditButton_clicked(){
    editPerson();
}

// Double click person table row
void MainWindow::on_personTable_doubleClicked(const QModelIndex &index){
    if(index.isValid()){
        editPerson();
    }
}

// Person table -> Clicked
void MainWindow::on_personTable_clicked(const QModelIndex &index){
    if(index.isValid()){
        // Enable delete button
        ui->personDeleteButton->setEnabled(true);
        // Enable edit button
        ui->personEditButton->setEnabled(true);
    }
}

// === DELETE ===
// Delete person
void MainWindow::deletePerson(){
    // Get row
    QModelIndexList selection = ui->personTable->selectionModel()->selectedRows();

    // No rows
    if (selection.isEmpty()) {
        return;
    }

    int numRows = selection.count();
    QString deleteConfirmMessage = "";
    QString statusBarMessage = "";

    QVector<Person> personsToBeDeleted;

    for(int i = 0; i < numRows;i++){
        // Get first column (id)
        QModelIndex index = selection.at(i);
        // Get id column data
        int id = ui->personTable->model()->data(index).toInt();

        // An empty person
        Person p;
        // Set person ID to the ID of the row
        p.setId(id);

        // Get the person info by ID
        if(!servicesLayer.getPerson(p, error)){
            checkError();
            return;
        }

        // Add to vector
        personsToBeDeleted.push_back(p);
    }

    // Single row
    if(numRows == 1){
        deleteConfirmMessage = "Are you sure you want to delete " + personsToBeDeleted[0].getName() + "?";
        statusBarMessage = personsToBeDeleted[0].getName() + " deleted";
    }
    // Rows less than 11
    else if(numRows > 1 && numRows < 11){

        deleteConfirmMessage = "Are you sure you want to delete:\n";

        // Loop over names
        for(int i = 0; i < numRows;i++){
            deleteConfirmMessage += personsToBeDeleted[i].getName() + "\n";
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
        if(!servicesLayer.deletePerson(personsToBeDeleted, error)){
            checkError();
            return;
        }

        // Disable Person edit and delete buttons
        disableEditDeletePersonButtons();

        // Status bar update
        ui->statusBar->showMessage(statusBarMessage, constants::STATUSBAR_MESSAGE_TIME);

        // Re-display
        checkPersonSearch();
    }
}

// === EDIT ===
// Edit person
void MainWindow::editPerson(){
    // Get row
    QModelIndexList selection = ui->personTable->selectionModel()->selectedRows();

    // No rows
    if (selection.isEmpty()) {
        return;
    }

    QModelIndex index = selection.at(0);
    // Get ID
    int id = ui->personTable->model()->data(index).toInt();

    // An empty person
    Person p;
    // Set person ID to the ID of the row
    p.setId(id);

    // Get the person info by ID
    if(!servicesLayer.getPerson(p, error)){
        checkError();
        return;
    }

    // Edit dialog
    editPersonDialog editDialog;
    // Forward person to edit dialog
    editDialog.setPerson(p);
    // Set the fields
    editDialog.setFields();
    // Exec window
    editDialog.exec();

    // If saved
    if (editDialog.getSaveClick()) {
        // If error, show error, else update table
        if (!servicesLayer.editPerson(editDialog.getPerson(), error)) {
            checkError();
            return;
        }
        else{
            checkPersonSearch();
        }

        // Set status bar message
        ui->statusBar->showMessage("Edit complete", constants::STATUSBAR_MESSAGE_TIME);

        // Disable Person edit and delete buttons
        disableEditDeletePersonButtons();
    }
}

// === CONNECT ===
// Connect to machine
void MainWindow::connectToMachine(){
    // Get row
    QModelIndexList selection = ui->personTable->selectionModel()->selectedRows();

    // No rows
    if (selection.isEmpty()) {
        return;
    }

    // Get first column (id)
    QModelIndex index = selection.at(0);
    // Get id column data
    int p_id = ui->personTable->model()->data(index).toInt();

    ConnectToMachine connectionDialog;

    // Setup
    connectionDialog.setModel(machineProxyModel);
    connectionDialog.displayTable();

    // Connect
    if(connectionDialog.exec()){
        // Get machine ID
        int m_id = connectionDialog.getId();

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

            QString statusBarMessage = "Connected " + p.getName() + " and " + m.getName();

            ui->statusBar->showMessage(statusBarMessage, constants::STATUSBAR_MESSAGE_TIME);

            // Refresh connections table
            displayConnectionsTable();
        }
    }
}

// === CONTEXT MENU ===
// People context menu -> Delete
void MainWindow::on_actionDeletePerson_triggered(){
    deletePerson();
}

// Persons context menu -> Edit
void MainWindow::on_actionEditPerson_triggered(){
    editPerson();
}

// Persons context menu -> Connect
void MainWindow::on_actionPersonConnectToMachine_triggered(){
    connectToMachine();
}

// Person table -> Context menu
/*
 * QPoint &pos is not used due to when it's used
 * it returns the context menu a bit above the cursor.
 * QCursor::pos is used instead.
 */
void MainWindow::on_personTable_customContextMenuRequested(const QPoint &pos){
    // Get row
    QModelIndexList selection = ui->personTable->selectionModel()->selectedRows();

    // No rows
    if (selection.isEmpty()) {
        return;
    }
    // Multiple rows
    else if(selection.count() > 1){
        // Disable Connection option
        personContextMenu.actions().at(0)->setEnabled(false);
        // Disable Edit option
        personContextMenu.actions().at(1)->setEnabled(false);
    }
    else{
        // Enable Connection option
        personContextMenu.actions().at(0)->setEnabled(true);
        // Enable Edit option
        personContextMenu.actions().at(1)->setEnabled(true);
    }

    // Display menu
    personContextMenu.exec(QCursor::pos());
}

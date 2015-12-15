#include "mainwindow.h"
#include "ui_mainwindow.h"

// Display entire connections table
void MainWindow::displayConnectionsTable(){
    // Disable delete button
    ui->connectionsDeleteButton->setEnabled(false);

    // Get all machines
    if(!servicesLayer.getAllConnections(connectionsQueryModel, error)){
        checkError();
    }

    // Update results
    updateConnectionResults();
}

// Update connection results
void MainWindow::updateConnectionResults(){
    QString results = QString::number(ui->connectionsTable->verticalHeader()->count());

    ui->connectionsResultsLabel->setText("Results: " + results);
}

// === SEARCH ===
// Search connections
void MainWindow::searchConnections(QString searchString, int column){
    // Filter
    if(ui->connectionsFilterCheckBox->isChecked()){
        // Call filterConnection
        if(!servicesLayer.filterConnection(connectionsQueryModel, searchString, column, error)){
            checkError();
            return;
        }
    }
    // Search
    else{
        // Call searchConnection
        if(!servicesLayer.searchConnection(connectionsQueryModel, searchString, column, error)){
            checkError();
            return;
        }
    }

    // Update results
    updateConnectionResults();
}

// Delete connection
void MainWindow::deleteConnection(){
    QVector<int> ids = utilities::getSelectedTableViewIds(ui->connectionsTable);

    // No rows
    if (ids.isEmpty()) {
        return;
    }

    int numRows = ids.size();
    QString deleteConfirmMessage = "";
    QString statusBarMessage = "";

    // Get all the connection that are about to be deleted
    QVector<PersonMachine> connectionsToBeDeleted;
    for(int i = 0; i < numRows;i++){
        // An empty connections
        PersonMachine pm;
        // Set person ID to the ID of the row
        pm.setId(ids[i]);

        // Get the person info by ID
        if(!servicesLayer.getConnection(pm, error)){
            checkError();
            return;
        }

        // Add to vector
        connectionsToBeDeleted.push_back(pm);
    }

    // Single row
    if(numRows == 1){
        deleteConfirmMessage = "Are you sure you want to delete the connection between "
                               + connectionsToBeDeleted[0].getP_Name() + " and "
                               + connectionsToBeDeleted[0].getM_Name() + " ?";

        statusBarMessage = "Connection between " + connectionsToBeDeleted[0].getP_Name() + " and "
                                                 + connectionsToBeDeleted[0].getM_Name() + " deleted";
    }
    // Rows less than 11
    else if(numRows > 1 && numRows < 11){

        deleteConfirmMessage = "Are you sure you want to delete the connections between:\n";

        // Loop over names
        for(int i = 0; i < numRows;i++){
            deleteConfirmMessage += connectionsToBeDeleted[i].getP_Name() + " and " + connectionsToBeDeleted[i].getM_Name() + "\n";
        }

        statusBarMessage = QString::number(numRows) + " entries deleted";
    }
    // More than 10
    else{
        deleteConfirmMessage = "Are you sure you want to delete these " + QString::number(numRows) + " connections?";
        statusBarMessage = QString::number(numRows) + " entries deleted";
    }

    // Confirmation window
    int ans = QMessageBox::question(this, "Confirmation", deleteConfirmMessage, QMessageBox::Yes|QMessageBox::No, QMessageBox::No);
    // Check answer
    if (ans == QMessageBox::Yes) {
        // Delete
        if(!servicesLayer.deleteConnection(connectionsToBeDeleted, error)){
            checkError();
            return;
        }

        // Disable delete button
        ui->connectionsDeleteButton->setEnabled(false);

        // Status bar update
        ui->statusBar->showMessage(statusBarMessage, constants::STATUSBAR_MESSAGE_TIME);

        // Re-display
        checkConnectionsSearch();
    }
}

// Check connections search
void MainWindow::checkConnectionsSearch(){
    QString searchString = ui->connectionsSearchField->text();

    // If search criteria is empty, display all
    if(searchString.isEmpty()){
        // Get all machines
        displayConnectionsTable();
        return;
    }

    // What field is selected
    int column = ui->connectionsSearchComboBox->currentIndex();

    // Search
    searchConnections(searchString, column);
}

// Connections filter box -> clicked
void MainWindow::on_connectionsFilterCheckBox_clicked(){
    checkConnectionsSearch();
}

// Connections search combobox -> clicked
void MainWindow::on_connectionsSearchComboBox_currentIndexChanged(int index){
    QString searchString = ui->connectionsSearchField->text();

    // If search criteria is empty, display all
    if(searchString.isEmpty()){
        // Get all machines
        displayConnectionsTable();
        return;
    }

    // Disable delete button
    ui->connectionsDeleteButton->setEnabled(false);

    // Search
    searchConnections(searchString, index);
}

// COnnections search field -> clicked
void MainWindow::on_connectionsSearchField_textChanged(const QString &arg1){
    // If search criteria is empty, display all
    if(arg1.isEmpty()){
        // Get all machines
        displayConnectionsTable();
        return;
    }

    // Disable delete button
    ui->connectionsDeleteButton->setEnabled(false);

    // What field is selected
    int column = ui->connectionsSearchComboBox->currentIndex();

    // Search
    searchConnections(arg1, column);
}

// Connections table -> clicked
void MainWindow::on_connectionsTable_clicked(const QModelIndex &index){
    if(index.isValid()){
        // Enable delete button
        ui->connectionsDeleteButton->setEnabled(true);
    }
}

// Delete button -> clicked
void MainWindow::on_connectionsDeleteButton_clicked(){
    deleteConnection();
}

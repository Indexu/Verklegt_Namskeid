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

}

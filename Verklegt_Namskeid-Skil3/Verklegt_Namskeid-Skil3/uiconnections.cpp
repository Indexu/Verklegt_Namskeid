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

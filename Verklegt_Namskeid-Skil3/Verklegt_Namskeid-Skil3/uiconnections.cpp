#include "mainwindow.h"
#include "ui_mainwindow.h"

// Display entire connections table
void MainWindow::displayConnectionsTable(){
    // Disable edit and delete buttons
    //disableEditDeleteMachineButtons();

    // Get all machines
    if(!servicesLayer.getAllConnections(connectionsQueryModel, error)){
        checkError();
    }

    // Update results
    //updateMachineResults();
}

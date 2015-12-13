#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "utilities.h"
#include "constants.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // ===== SETUP =====
    // Initialize error
    error = "";
    // Configure tables
    configTables();

    // Add items to comboboxes
    addToComboboxes();
    // Display tables
    displayPersonTable();
    displayMachinesTable();
    displayConnectionsTable();

    // Set the context menus
    setContextMenus();

}

// Deconstructor
MainWindow::~MainWindow(){
    // Delete models
    delete personQueryModel;
    delete personProxyModel;

    delete machineQueryModel;
    delete machineProxyModel;

    delete connectionsQueryModel;
    delete connectionsProxyModel;

    delete ui;
}

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

// Display entire machine table
void MainWindow::displayMachinesTable(){
    // Get all persons
    if(!servicesLayer.getAllMachines(machineQueryModel, error)){
        checkError();
    }
}

// Display entire connections table
void MainWindow::displayConnectionsTable(){

}

// Get all models
void MainWindow::getModels(){
    personProxyModel = servicesLayer.getPersonModel(personQueryModel);
    machineProxyModel = servicesLayer.getMachineModel(machineQueryModel);
    connectionsProxyModel = servicesLayer.getConnectionModel(connectionsQueryModel);
}

// Set table models
void MainWindow::setTableModels(){
    ui->personTable->setModel(personProxyModel);
    ui->machineTable->setModel(machineProxyModel);
    ui->connectionsTable->setModel(connectionsProxyModel);

}

// Configure the tables
void MainWindow::configTables(){
    // Get all database models
    getModels();

    // Set headers
    setModelHeaders();

    // Set table models
    setTableModels();

    // Set properties
    setTableProperties(ui->personTable);
    setTableProperties(ui->machineTable);
    setTableProperties(ui->connectionsTable);
}

// Set model headers (columns)
void MainWindow::setModelHeaders(){
    // Set Person headers
    personProxyModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
    personProxyModel->setHeaderData(1, Qt::Horizontal, tr("Name"));
    personProxyModel->setHeaderData(2, Qt::Horizontal, tr("Gender"));
    personProxyModel->setHeaderData(3, Qt::Horizontal, tr("Date of birth"));
    personProxyModel->setHeaderData(4, Qt::Horizontal, tr("Date of death"));
    personProxyModel->setHeaderData(5, Qt::Horizontal, tr("Country"));

    // Set machine headers
    machineQueryModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
    machineQueryModel->setHeaderData(1, Qt::Horizontal, tr("Name"));
    machineQueryModel->setHeaderData(2, Qt::Horizontal, tr("Year"));
    machineQueryModel->setHeaderData(3, Qt::Horizontal, tr("Built"));
    machineQueryModel->setHeaderData(4, Qt::Horizontal, tr("Type"));
    machineQueryModel->setHeaderData(5, Qt::Horizontal, tr("System"));

    // Set column names
    connectionsQueryModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
    connectionsQueryModel->setHeaderData(1, Qt::Horizontal, tr("Person"));
    connectionsQueryModel->setHeaderData(2, Qt::Horizontal, tr("Machine"));
    connectionsQueryModel->setHeaderData(3, Qt::Horizontal, tr("Type"));
    connectionsQueryModel->setHeaderData(4, Qt::Horizontal, tr("System"));
    connectionsQueryModel->setHeaderData(5, Qt::Horizontal, tr("Country"));
}

// Add to search/filter comboboxes
void MainWindow::addToComboboxes(){
    // Person search
    ui->personSearchComboBox->addItem("All");
    ui->personSearchComboBox->addItem("ID");
    ui->personSearchComboBox->addItem("Name");
    ui->personSearchComboBox->addItem("Gender");
    ui->personSearchComboBox->addItem("Birth date");
    ui->personSearchComboBox->addItem("Death date");
    ui->personSearchComboBox->addItem("Country");
}

// Set table properties
void MainWindow::setTableProperties(QTableView *tab){
    tab->setSelectionBehavior(QAbstractItemView::SelectRows);
    tab->verticalHeader()->hide();
    tab->horizontalHeader()->setStretchLastSection(true);
    tab->horizontalHeader()->setSectionsClickable(true);
    tab->setAlternatingRowColors(true);
    tab->setSortingEnabled(true);
    tab->sortByColumn(0, Qt::AscendingOrder);
    tab->resizeColumnsToContents();
    tab->horizontalHeader()->setHighlightSections(false);
}

// Set context menus
void MainWindow::setContextMenus(){
    // Person context menu
    ui->personTable->setContextMenuPolicy(Qt::CustomContextMenu);
    personContextMenu.addAction(ui->actionPersonConnectToMachine);
    personContextMenu.addAction(ui->actionEditPerson);
    personContextMenu.addAction(ui->actionDeletePerson);
}

// Display error if there is an error
void MainWindow::checkError(){
    if(!error.isEmpty()){
        QMessageBox::warning(this, "Error", error);
        error = "";
    }
}

// Update the persons label displaying the number of results
void MainWindow::updatePersonResults(){
    QString results = QString::number(ui->personTable->verticalHeader()->count());

    ui->personResultsLabel->setText("Results: " + results);
}

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

// Disable Person edit and delete buttons
void MainWindow::disableEditDeletePersonButtons(){
    // Disable delete button
    ui->personDeleteButton->setEnabled(false);
    // Disable edit button
    ui->personEditButton->setEnabled(false);
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

// Person add button
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

// Person delete button
void MainWindow::on_personDeleteButton_clicked(){
    deletePerson();
}

// Person edit button
void MainWindow::on_personEditButton_clicked(){
    editPerson();
}

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
        // Loop over rows
        for(int i = 0; i < numRows; i++){
            // Get first column (id)
            QModelIndex index = selection.at(i);

            // Get id column data
            int id = ui->personTable->model()->data(index).toInt();

            // Delete
            if(!servicesLayer.deletePerson(id, error)){
                checkError();
                return;
            }
        }

        // Disable Person edit and delete buttons
        disableEditDeletePersonButtons();

        // Status bar update
        ui->statusBar->showMessage(statusBarMessage, constants::STATUSBAR_MESSAGE_TIME);

        // Re-display
        checkPersonSearch();
    }
}

// Edit person
void MainWindow::editPerson(){
    // Get row
    QModelIndexList selection = ui->personTable->selectionModel()->selectedRows();
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

// People context menu -> Delete
void MainWindow::on_actionDeletePerson_triggered(){
    deletePerson();
}

// Double click person table row
void MainWindow::on_personTable_doubleClicked(const QModelIndex &index){
    editPerson();
}

// Persons context menu -> Edit
void MainWindow::on_actionEditPerson_triggered(){
    editPerson();
}

// Person table -> Clicked
void MainWindow::on_personTable_clicked(const QModelIndex &index){
    // Enable delete button
    ui->personDeleteButton->setEnabled(true);
    // Enable edit button
    ui->personEditButton->setEnabled(true);
}

// Person table -> Context menu
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

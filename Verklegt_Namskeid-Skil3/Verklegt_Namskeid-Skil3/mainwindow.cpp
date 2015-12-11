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

    // Disable delete button
    ui->personDeleteButton->setEnabled(false);

    // Set the context menus
    setContextMenus();
}

// Person context menu
void MainWindow::personContextMenuSlot(const QPoint& pos){
    // Set
    QPoint mappedPos = ui->personTable->mapToGlobal(pos);

    personContextMenu.exec(mappedPos);
}

// Deconstructor
MainWindow::~MainWindow(){
    // Delete models
    delete personModel;
    delete machineModel;
    delete connectionsModel;

    delete ui;
}

// Display entire person table
void MainWindow::displayPersonTable(){
    // Get all persons
    if(!servicesLayer.getAllPersons(personModel, error)){
        checkError();
    }
}

// Display entire machine table
void MainWindow::displayMachinesTable(){

}

// Display entire connections table
void MainWindow::displayConnectionsTable(){

}

// Get all models
void MainWindow::getModels(){
    personModel = servicesLayer.getPersonModel();
    machineModel = servicesLayer.getMachineModel();
    connectionsModel = servicesLayer.getConnectionModel();
}

// Set table models
void MainWindow::setTableModels(){
    ui->personTable->setModel(personModel);
    ui->machineTable->setModel(machineModel);
    ui->connectionsTable->setModel(connectionsModel);

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
    personModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
    personModel->setHeaderData(1, Qt::Horizontal, tr("Name"));
    personModel->setHeaderData(2, Qt::Horizontal, tr("Gender"));
    personModel->setHeaderData(3, Qt::Horizontal, tr("Date of birth"));
    personModel->setHeaderData(4, Qt::Horizontal, tr("Date of death"));
    personModel->setHeaderData(5, Qt::Horizontal, tr("Country"));

    // Set machine headers
    machineModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
    machineModel->setHeaderData(1, Qt::Horizontal, tr("Name"));
    machineModel->setHeaderData(2, Qt::Horizontal, tr("Year"));
    machineModel->setHeaderData(3, Qt::Horizontal, tr("Built"));
    machineModel->setHeaderData(4, Qt::Horizontal, tr("Type"));
    machineModel->setHeaderData(5, Qt::Horizontal, tr("System"));

    // Set column names
    connectionsModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
    connectionsModel->setHeaderData(1, Qt::Horizontal, tr("Person"));
    connectionsModel->setHeaderData(2, Qt::Horizontal, tr("Machine"));
    connectionsModel->setHeaderData(3, Qt::Horizontal, tr("Type"));
    connectionsModel->setHeaderData(4, Qt::Horizontal, tr("System"));
    connectionsModel->setHeaderData(5, Qt::Horizontal, tr("Country"));
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
    // Person filter
    ui->personFilterComboBox->addItem("All");
    ui->personFilterComboBox->addItem("ID");
    ui->personFilterComboBox->addItem("Name");
    ui->personFilterComboBox->addItem("Gender");
    ui->personFilterComboBox->addItem("Birth date");
    ui->personFilterComboBox->addItem("Death date");
    ui->personFilterComboBox->addItem("Country");
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
}

// Set context menus
void MainWindow::setContextMenus(){
    // Person context menu
    ui->personTable->setContextMenuPolicy(Qt::CustomContextMenu);
    personContextMenu.addAction(ui->actionEditPerson);
    personContextMenu.addAction(ui->actionPersonConnectToMachine);
    personContextMenu.addAction(ui->actionDeletePerson);

    connect(ui->personTable, SIGNAL(customContextMenuRequested(const QPoint&)),
        this, SLOT(personContextMenuSlot(const QPoint&)));
}

// Display error if there is an error
void MainWindow::checkError(){
    if(!error.isEmpty()){
        QMessageBox::warning(this, "Error", error);
        error = "";
    }
}

// Person filter field -> Text changed
void MainWindow::on_personFilterField_textChanged(const QString &arg1){
    // If search criteria is empty, display all
    if(arg1.isEmpty()){
        // Get all persons
        if(!servicesLayer.getAllPersons(personModel, error)){
            checkError();
        }
        return;
    }

    // What field is selected
    int column = ui->personSearchComboBox->currentIndex();

    // Call searchPerson
    if(!servicesLayer.filterPerson(personModel, arg1, column, error)){
        checkError();
    }
}

// Person search field -> Text changed
void MainWindow::on_personSearchField_textChanged(const QString &arg1){
    // If search criteria is empty, display all
    if(arg1.isEmpty()){
        // Get all persons
        if(!servicesLayer.getAllPersons(personModel, error)){
            checkError();
        }
        return;
    }

    // What field is selected
    int column = ui->personSearchComboBox->currentIndex();

    // Call searchPerson
    if(!servicesLayer.searchPerson(personModel, arg1, column, error)){
        checkError();
    }

}

// Person search combobox -> Index changed
void MainWindow::on_personSearchComboBox_currentIndexChanged(int index){
    // Search string
    QString searchString = ui->personSearchField->text();

    // If search criteria is empty, display all
    if(searchString.isEmpty()){
        // Get all persons
        if(!servicesLayer.getAllPersons(personModel, error)){
            checkError();
        }
        return;
    }

    // Call searchPerson
    if(!servicesLayer.searchPerson(personModel, searchString, index, error)){
        checkError();
    }
}

// Person filter combobox -> Index changed
void MainWindow::on_personFilterComboBox_currentIndexChanged(int index){
    // Search string
    QString searchString = ui->personFilterField->text();

    // If search criteria is empty, display all
    if(searchString.isEmpty()){
        // Get all persons
        if(!servicesLayer.getAllPersons(personModel, error)){
            checkError();
        }
        return;
    }

    // Call searchPerson
    if(!servicesLayer.filterPerson(personModel, searchString, index, error)){
        checkError();
    }
}

// Person add button
void MainWindow::on_personAddButton_clicked(){
    // Display dialog
    AddDialog addDialog;
    addDialog.exec();

    // Confirm add
    if(addDialog.getAddClick()){
        // Add
        if(!servicesLayer.addPerson(addDialog.getPerson(), error)){
            checkError();
        }
        else{
            displayPersonTable();
        }
    }
}

// Delete person
void MainWindow::deletePerson(){
    // Get row
    QModelIndexList selection = ui->personTable->selectionModel()->selectedRows();

    // No rows
    if (selection.isEmpty()) {
        return;
    }

    QString deleteConfirmMessage = "";

    // Single row
    if(selection.count() == 1){
        deleteConfirmMessage = "Are you sure you want to delete?";
    }
    // Multiple rows
    else if(selection.count() > 1){
        deleteConfirmMessage = "Are you sure you want to delete " + QString::number(selection.count()) + " entries?";
    }

    // Confirmation window
    int ans = QMessageBox::question(this, "Confirmation", deleteConfirmMessage, QMessageBox::Yes|QMessageBox::No);
    // Check answer
    if (ans == QMessageBox::Yes) {
        // Loop over rows
        for(int i = 0; i < selection.count(); i++){
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

        // Get call persons
        if(!servicesLayer.getAllPersons(personModel, error)){
            checkError();
        }
    }
}

// Person delete button
void MainWindow::on_personDeleteButton_clicked(){
    deletePerson();
}

// Person table -> click row
void MainWindow::on_personTable_clicked(const QModelIndex &index){
    // Enable delete button
    ui->personDeleteButton->setEnabled(true);
}

// People context menu -> Delete
void MainWindow::on_actionDeletePerson_triggered(){
    deletePerson();
}

void MainWindow::on_personTable_doubleClicked(const QModelIndex &index){

    QModelIndexList selection = ui->personTable->selectionModel()->selectedRows();
    QModelIndex dex = selection.at(0);
    int id = ui->personTable->model()->data(dex).toInt();


    QString error;
    Person p;

    p.setId(id);

    if(!servicesLayer.getPerson(p, error)){
        checkError();
        return;
    }

    editPersonDialog editDialog;
    editDialog.setPerson(p);
    editDialog.setFields();

    editDialog.exec();
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "utilities.h"
#include "constants.h"
#include <QMessageBox>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ===== SETUP =====
    // Initialize error
    error = "";
    // Get all database models
    getModels();
    // Set headers
    setModelHeaders();
    // Add items to comboboxes
    addToComboboxes();
    // Display tables
    displayPersonTable();
    displayMachinesTable();
    displayConnectionsTable();

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
    //Reset filter
    personModel->setFilter("");
    // Attatch to table
    ui->personTable->setModel(personModel);
    // Set properties
    setTableProperties(ui->personTable);
}

// Display entire machine table
void MainWindow::displayMachinesTable(){
    // Attatch to table
    ui->machineTable->setModel(machineModel);
    // Set properties
    setTableProperties(ui->machineTable);
}

// Display entire connections table
void MainWindow::displayConnectionsTable(){
    // Attatch to table
    ui->connectionsTable->setModel(connectionsModel);
    // Set properties
    setTableProperties(ui->connectionsTable);
}

// Get all models
void MainWindow::getModels(){
    personModel = servicesLayer.getPersonModel(this);
    machineModel = servicesLayer.getMachineModel(this);
    connectionsModel = servicesLayer.getConnectionModel(this);
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
    tab->horizontalHeader()->setStretchLastSection(true);
    tab->horizontalHeader()->setSectionsClickable(true);
    tab->setAlternatingRowColors(true);
    tab->setSortingEnabled(true);
    tab->sortByColumn(0, Qt::AscendingOrder);
    tab->resizeColumnsToContents();
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
        displayPersonTable();
        return;
    }

    // What field is selected
    int column = ui->personSearchComboBox->currentIndex();
    // Call filterPerson
    servicesLayer.filterPerson(personModel, arg1, column, error);
    // Check error
    checkError();
}

// Person search field -> Text changed
void MainWindow::on_personSearchField_textChanged(const QString &arg1){
    // If search criteria is empty, display all
    if(arg1.isEmpty()){
        displayPersonTable();
        return;
    }

    // What field is selected
    int column = ui->personSearchComboBox->currentIndex();
    // Call searchPerson
    servicesLayer.searchPerson(personModel, arg1, column, error);
    // Check error
    checkError();
}

// Person search combobox -> Index changed
void MainWindow::on_personSearchComboBox_currentIndexChanged(int index){
    // Search string
    QString searchString = ui->personSearchField->text();

    // If search criteria is empty, display all
    if(searchString.isEmpty()){
        displayPersonTable();
        return;
    }

    // Call searchPerson
    servicesLayer.searchPerson(personModel, searchString, index, error);
    // Check error
    checkError();
}

// Person filter combobox -> Index changed
void MainWindow::on_personFilterComboBox_currentIndexChanged(int index){
    // Search string
    QString searchString = ui->personFilterField->text();

    // If search criteria is empty, display all
    if(searchString.isEmpty()){
        displayPersonTable();
        return;
    }

    // Call filterPerson
    servicesLayer.filterPerson(personModel, searchString, index, error);
    // Check error
    checkError();
}

// Person add button
void MainWindow::on_personAddButton_clicked(){
    AddDialog *addDialog = new AddDialog(this);
    addDialog->exec();
}


void MainWindow::on_personDeleteButton_clicked()
{
    QModelIndexList selection = ui->personTable->selectionModel()->selectedRows();
    QModelIndex index = selection.at(0);
    int numRows = selection.count();
    int rowIndex = index.row();

    // Warning if too many rows are selected
    if (numRows > 1) {
        QMessageBox::warning(this, "Warning!", "Too many rows selected!");
        return;
    }
    // Confirmation pop-up
    QMessageBox::StandardButton ans;
    ans = QMessageBox::question(this, "Confirmation", "Are you sure you want to delete?", QMessageBox::Yes|QMessageBox::No);
    if (ans == QMessageBox::Yes) {
        personModel->removeRows(rowIndex, numRows);
        personModel->submitAll();
        qDebug("DELETED");
    }
    else {
        qDebug("*NOT* DELETED");
        return;
    }
}

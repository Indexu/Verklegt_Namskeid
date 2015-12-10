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

    // Get all database models
    getModels();
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

// Display person table
void MainWindow::displayPersonTable(){
    // Set column names
    personModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
    personModel->setHeaderData(1, Qt::Horizontal, tr("Name"));
    personModel->setHeaderData(2, Qt::Horizontal, tr("Gender"));
    personModel->setHeaderData(3, Qt::Horizontal, tr("Date of birth"));
    personModel->setHeaderData(4, Qt::Horizontal, tr("Date of death"));
    personModel->setHeaderData(5, Qt::Horizontal, tr("Country"));

    // Attatch to table
    ui->personTable->setModel(personModel);
    // Set properties
    setTableProperties(ui->personTable);
}

// Display machine table
void MainWindow::displayMachinesTable(){
    // Set column names
    machineModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
    machineModel->setHeaderData(1, Qt::Horizontal, tr("Name"));
    machineModel->setHeaderData(2, Qt::Horizontal, tr("Year"));
    machineModel->setHeaderData(3, Qt::Horizontal, tr("Built"));
    machineModel->setHeaderData(4, Qt::Horizontal, tr("Type"));
    machineModel->setHeaderData(5, Qt::Horizontal, tr("System"));

    // Attatch to table
    ui->machineTable->setModel(machineModel);
    // Set properties
    setTableProperties(ui->machineTable);
}

// Display
void MainWindow::displayConnectionsTable(){
    // Set column names
    connectionsModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
    connectionsModel->setHeaderData(1, Qt::Horizontal, tr("Person"));
    connectionsModel->setHeaderData(2, Qt::Horizontal, tr("Machine"));
    connectionsModel->setHeaderData(3, Qt::Horizontal, tr("Type"));
    connectionsModel->setHeaderData(4, Qt::Horizontal, tr("System"));
    connectionsModel->setHeaderData(5, Qt::Horizontal, tr("Country"));

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

// Set person model filter
void MainWindow::setFilterPerson(QString filterStr, QString searchString){
    // Set filter
    personModel->setFilter(filterStr.arg(searchString));
    // Run
    personModel->select();

    // Error
    if(personModel->lastError().isValid()){
        ui->personSearchField->setText("");
        QMessageBox::warning(this, "SQl Error", personModel->lastError().text());
    }
}
// Get filter string for person search
void MainWindow::searchPerson(QString searchString){
    // What field is selected
    int column = ui->personSearchComboBox->currentIndex();

    QString filterStr = "";

    // All
    if(column == 0){
        filterStr = "id LIKE '%%1%' OR name LIKE '%%1%' OR gender LIKE '%%1%' OR date_of_birth LIKE '%%1%' OR date_of_death LIKE '%%1%' OR country LIKE '%%1%'";
    }
    // ID
    else if(column == 1){
        filterStr = "id LIKE '%%1%'";
    }
    // Name
    else if(column == 2){
        filterStr = "name LIKE '%%1%'";
    }
    // Gender
    else if(column == 3){
        filterStr = "gender LIKE '%%1%'";
    }
    // Date of birth
    else if(column == 4){
        filterStr = "date_of_birth LIKE '%%1%'";
    }
    // Date of death
    else if(column == 5){
        filterStr = "date_of_death LIKE '%%1%'";
    }
    // Country
    else if(column == 6){
        filterStr = "country LIKE '%%1%'";
    }

    // Forward string and search string
    setFilterPerson(filterStr, searchString);
}
// Get filter string for person filter
void MainWindow::filterPerson(QString searchString){
    // What field is selected
    int column = ui->personFilterComboBox->currentIndex();

    QString filterStr = "";

    // All
    if(column == 0){
        filterStr = "id NOT LIKE '%%1%' AND name NOT LIKE '%%1%' AND gender NOT LIKE '%%1%' AND date_of_birth NOT LIKE '%%1%' AND date_of_death NOT LIKE '%%1%' AND country NOT LIKE '%%1%'";
    }
    // ID
    else if(column == 1){
        filterStr = "id NOT LIKE '%%1%'";
    }
    // Name
    else if(column == 2){
        filterStr = "name NOT LIKE '%%1%'";
    }
    // Gender
    else if(column == 3){
        filterStr = "gender NOT LIKE '%%1%'";
    }
    // Date of birth
    else if(column == 4){
        filterStr = "date_of_birth NOT LIKE '%%1%'";
    }
    // Date of death
    else if(column == 5){
        filterStr = "date_of_death NOT LIKE '%%1%'";
    }
    // Country
    else if(column == 6){
        filterStr = "country NOT LIKE '%%1%'";
    }
    // No search string
    if(searchString == ""){
        searchPerson("");
        return;
    }

    // Forward string and search string
    setFilterPerson(filterStr, searchString);
}

// Person filter field -> Text changed
void MainWindow::on_personFilterField_textChanged(const QString &arg1){
    filterPerson(arg1);
}

// Person search field -> Text changed
void MainWindow::on_personSearchField_textChanged(const QString &arg1){
    searchPerson(arg1);
}

// Person search combobox -> Index changed
void MainWindow::on_personSearchComboBox_currentIndexChanged(int index){
    QString searchString = ui->personSearchField->text();
    searchPerson(searchString);
}

// Person filter combobox -> Index changed
void MainWindow::on_personFilterComboBox_currentIndexChanged(int index){
    QString searchString = ui->personFilterField->text();
    filterPerson(searchString);
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

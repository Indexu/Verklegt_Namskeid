#include "mainwindow.h"
#include "ui_mainwindow.h"

// Constructor
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

    // Machine search
    ui->machinesSearchComboBox->addItem("All");
    ui->machinesSearchComboBox->addItem("ID");
    ui->machinesSearchComboBox->addItem("Name");
    ui->machinesSearchComboBox->addItem("Year");
    ui->machinesSearchComboBox->addItem("Built");
    ui->machinesSearchComboBox->addItem("Type");
    ui->machinesSearchComboBox->addItem("System");
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

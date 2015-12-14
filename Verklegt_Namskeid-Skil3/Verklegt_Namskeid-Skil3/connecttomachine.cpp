#include "connecttomachine.h"
#include "ui_connecttomachine.h"

ConnectToMachine::ConnectToMachine(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectToMachine)
{
    ui->setupUi(this);

    // Initialize Id
    Id = 0;

    // Disable connect button
    ui->connectButton->setEnabled(false);
}

ConnectToMachine::~ConnectToMachine()
{
    delete ui;
}

// Set model
void ConnectToMachine::setModel(QSortFilterProxyModel *&m){
    machinesConnectionModel = m;
}

// Display table
void ConnectToMachine::displayTable(){
    ui->machinesTable->setModel(machinesConnectionModel);

    ui->machinesTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->machinesTable->verticalHeader()->hide();
    ui->machinesTable->horizontalHeader()->setStretchLastSection(true);
    ui->machinesTable->horizontalHeader()->setSectionsClickable(true);
    ui->machinesTable->setAlternatingRowColors(true);
    ui->machinesTable->setSortingEnabled(true);
    ui->machinesTable->sortByColumn(0, Qt::AscendingOrder);
    ui->machinesTable->resizeColumnsToContents();
    ui->machinesTable->horizontalHeader()->setHighlightSections(false);
    ui->machinesTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->machinesTable->horizontalHeader()->hideSection(3);
    ui->machinesTable->horizontalHeader()->hideSection(4);
    ui->machinesTable->horizontalHeader()->hideSection(5);
}

// Get machine ID
int ConnectToMachine::getId(){
    return Id;
}

// Cancel button -> clicked
void ConnectToMachine::on_cancelButton_clicked(){
    this->done(0);
}

// Connect button -> clicked
void ConnectToMachine::on_connectButton_clicked(){
    // Get row
    QModelIndexList selection = ui->machinesTable->selectionModel()->selectedRows();

    // No rows
    if (selection.isEmpty()) {
        return;
    }

    // Get first column (id)
    QModelIndex index = selection.at(0);
    // Get id column data
    Id = ui->machinesTable->model()->data(index).toInt();

    this->done(1);
}

// Table -> clicked
void ConnectToMachine::on_machinesTable_clicked(const QModelIndex &index){
    if(index.isValid()){
        // Enable connect button
        ui->connectButton->setEnabled(true);
    }
}

#include "connecttoperson.h"
#include "ui_connecttoperson.h"

ConnectToPerson::ConnectToPerson(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectToPerson)
{
    ui->setupUi(this);

    // Initialize Id
    Id = 0;

    // Disable connect button
    ui->connectButton->setEnabled(false);
}

ConnectToPerson::~ConnectToPerson()
{
    delete ui;
}

// Set model
void ConnectToPerson::setModel(QSortFilterProxyModel *&p){
    personsConnectionModel = p;
}

// Display the table
void ConnectToPerson::displayTable(){
    ui->personsTable->setModel(personsConnectionModel);

    ui->personsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->personsTable->verticalHeader()->hide();
    ui->personsTable->horizontalHeader()->setStretchLastSection(true);
    ui->personsTable->horizontalHeader()->setSectionsClickable(true);
    ui->personsTable->setAlternatingRowColors(true);
    ui->personsTable->setSortingEnabled(true);
    ui->personsTable->sortByColumn(0, Qt::AscendingOrder);
    ui->personsTable->resizeColumnsToContents();
    ui->personsTable->horizontalHeader()->setHighlightSections(false);
    ui->personsTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->personsTable->horizontalHeader()->hideSection(2);
    ui->personsTable->horizontalHeader()->hideSection(4);
}

// Get the person ID
int ConnectToPerson::getId(){
    return Id;
}

// Cancel button -> clicked
void ConnectToPerson::on_cancelButton_clicked(){
    this->done(0);
}

// Connect button -> clicked
void ConnectToPerson::on_connectButton_clicked(){
    // Get row
    QModelIndexList selection = ui->personsTable->selectionModel()->selectedRows();

    // No rows
    if (selection.isEmpty()) {
        return;
    }

    // Get first column (id)
    QModelIndex index = selection.at(0);
    // Get id column data
    Id = ui->personsTable->model()->data(index).toInt();

    this->done(1);
}

// Person table -> clicked
void ConnectToPerson::on_personsTable_clicked(const QModelIndex &index){
    if(index.isValid()){
        // Enable connect button
        ui->connectButton->setEnabled(true);
    }
}

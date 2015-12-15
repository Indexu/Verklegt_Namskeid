#include "addconnectiondialog.h"
#include "ui_addconnectiondialog.h"

AddConnectionDialog::AddConnectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddConnectionDialog)
{
    ui->setupUi(this);
    // Initialize Id
    P_id = 0;
    M_id = 0;
    personValid = false;
    machineValid = false;

    // Disable connect button
    ui->connectButton->setEnabled(false);
}

AddConnectionDialog::~AddConnectionDialog()
{
    delete ui;
}

// Set person model
void AddConnectionDialog::setPersonModel(QSortFilterProxyModel *p){
    personsConnectionModel = p;
}

// Set machine model
void AddConnectionDialog::setMachineModel(QSortFilterProxyModel *m){
    machinesConnectionModel = m;
}

// Display tables
void AddConnectionDialog::displayTables(){
    // Set models
    ui->machinesTable->setModel(machinesConnectionModel);
    ui->personsTable->setModel(personsConnectionModel);

    // Set properties
    setTableProperties(ui->machinesTable);
    setTableProperties(ui->personsTable);

    // Hide columns
    // Machine
    ui->machinesTable->horizontalHeader()->hideSection(3);
    ui->machinesTable->horizontalHeader()->hideSection(4);
    ui->machinesTable->horizontalHeader()->hideSection(5);
    // Person
    ui->personsTable->horizontalHeader()->hideSection(2);
    ui->personsTable->horizontalHeader()->hideSection(4);
}

void AddConnectionDialog::setTableProperties(QTableView *tab){
    tab->setSelectionBehavior(QAbstractItemView::SelectRows);
    tab->verticalHeader()->hide();
    tab->horizontalHeader()->setStretchLastSection(true);
    tab->horizontalHeader()->setSectionsClickable(true);
    tab->setAlternatingRowColors(true);
    tab->setSortingEnabled(true);
    tab->sortByColumn(0, Qt::AscendingOrder);
    tab->resizeColumnsToContents();
    tab->horizontalHeader()->setHighlightSections(false);
    tab->setSelectionMode(QAbstractItemView::SingleSelection);
}

// Verify that both IDs are set
void AddConnectionDialog::verifyIds(){
    if(personValid && machineValid){
        ui->connectButton->setEnabled(true);
    }
}

// Get person Id
int AddConnectionDialog::getPersonId(){
    return P_id;
}

// Get machine Id
int AddConnectionDialog::getMachineId(){
    return M_id;
}

// Persons table -> clicked
void AddConnectionDialog::on_personsTable_clicked(const QModelIndex &index){
    // Get name
    QString name = utilities::getColumnData(ui->personsTable, index, 1);

    // Display name
    ui->personSelectedLabel->setText("Selected: " + name);

    personValid = index.isValid();
    verifyIds();
}

// Machines table -> clicked
void AddConnectionDialog::on_machinesTable_clicked(const QModelIndex &index){
    // Get name
    QString name = utilities::getColumnData(ui->machinesTable, index, 1);

    // Display name
    ui->machineSelectedLabel->setText("Selected: " + name);

    machineValid = index.isValid();
    verifyIds();
}

// Cancel button -> clicked
void AddConnectionDialog::on_cancelButton_clicked(){
    this->done(0);
}

// Connect button -> clicked
void AddConnectionDialog::on_connectButton_clicked(){
    // Set Person ID
    QVector<int> ids = utilities::getSelectedTableViewIds(ui->personsTable);

    // Only one row may be selected
    if (ids.count() != 1) {
        return;
    }

    P_id = ids[0];

    // Set Machine ID
    ids = utilities::getSelectedTableViewIds(ui->machinesTable);

    // Only one row may be selected
    if (ids.count() != 1) {
        return;
    }

    M_id = ids[0];

    this->done(1);
}

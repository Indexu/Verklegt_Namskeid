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

    ui->personSearchComboBox->addItem("All");
    ui->personSearchComboBox->addItem("ID");
    ui->personSearchComboBox->addItem("Name");
    ui->personSearchComboBox->addItem("Gender");
    ui->personSearchComboBox->addItem("Birth date");
    ui->personSearchComboBox->addItem("Death date");
    ui->personSearchComboBox->addItem("Country");

    ui->personFilterComboBox->addItem("All");
    ui->personFilterComboBox->addItem("ID");
    ui->personFilterComboBox->addItem("Name");
    ui->personFilterComboBox->addItem("Gender");
    ui->personFilterComboBox->addItem("Birth date");
    ui->personFilterComboBox->addItem("Death date");
    ui->personFilterComboBox->addItem("Country");

    displayPersonTable();
    displayMachinesTable();
    displayPMTable();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displayPersonTable(){
    QSqlDatabase db = dataLayer.getDBCon();

    QSqlTableModel *model = new QSqlTableModel(this, db);

    model->setTable(constants::TABLE_PERSON);
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->select();
    model->setHeaderData(0, Qt::Horizontal, tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("Name"));
    model->setHeaderData(2, Qt::Horizontal, tr("Gender"));
    model->setHeaderData(3, Qt::Horizontal, tr("Date of birth"));
    model->setHeaderData(4, Qt::Horizontal, tr("Date of death"));
    model->setHeaderData(5, Qt::Horizontal, tr("Country"));

    ui->personTable->setModel(model);
    setTableProperties(ui->personTable);
    ui->personTable->show();
}

void MainWindow::displayMachinesTable(){
    QSqlDatabase db = dataLayer.getDBCon();

    QSqlTableModel *model = new QSqlTableModel(this, db);

    model->setTable(constants::TABLE_MACHINE);
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->select();
    model->setHeaderData(0, Qt::Horizontal, tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("Name"));
    model->setHeaderData(2, Qt::Horizontal, tr("Year"));
    model->setHeaderData(3, Qt::Horizontal, tr("Built"));
    model->setHeaderData(4, Qt::Horizontal, tr("Type"));
    model->setHeaderData(5, Qt::Horizontal, tr("System"));

    ui->machineTable->setModel(model);
    setTableProperties(ui->machineTable);
    ui->machineTable->show();
}

void MainWindow::displayPMTable(){
    QSqlDatabase db = dataLayer.getDBCon();

    QSqlTableModel *model = new QSqlTableModel(this, db);

    model->setTable(constants::TABLE_CONNECTIONS);
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->select();
    model->setHeaderData(0, Qt::Horizontal, tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("Person"));
    model->setHeaderData(2, Qt::Horizontal, tr("Machine"));
    model->setHeaderData(3, Qt::Horizontal, tr("Type"));
    model->setHeaderData(4, Qt::Horizontal, tr("System"));
    model->setHeaderData(5, Qt::Horizontal, tr("Country"));

    ui->PMTable->setModel(model);
    setTableProperties(ui->PMTable);
    ui->PMTable->show();
}

void MainWindow::setTableProperties(QTableView *tab)
{
    tab->horizontalHeader()->setStretchLastSection(true);
    tab->horizontalHeader()->setSectionsClickable(true);
    tab->setAlternatingRowColors(true);
    tab->setSortingEnabled(true);
    tab->sortByColumn(0, Qt::AscendingOrder);
    tab->resizeColumnsToContents();
}

void MainWindow::setFilterPerson(QString filterStr, QString searchString)
{
    QSqlDatabase db = dataLayer.getDBCon();

    QSqlTableModel *model = new QSqlTableModel(this, db);

    model->setTable(constants::TABLE_PERSON);
    model->setEditStrategy(QSqlTableModel::OnFieldChange);

    model->setFilter(filterStr.arg(searchString));

    model->select();

    if(model->lastError().isValid()){
        ui->personSearchField->setText("");
        QMessageBox::warning(this, "SQl Error", model->lastError().text());
    }

    model->setHeaderData(0, Qt::Horizontal, tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("Name"));
    model->setHeaderData(2, Qt::Horizontal, tr("Gender"));
    model->setHeaderData(3, Qt::Horizontal, tr("Date of birth"));
    model->setHeaderData(4, Qt::Horizontal, tr("Date of death"));
    model->setHeaderData(5, Qt::Horizontal, tr("Country"));

    ui->personTable->setModel(model);

    db.close();
}

void MainWindow::searchPerson(QString searchString)
{
    int column = ui->personSearchComboBox->currentIndex();

    QString filterStr = "";
    if(column == 0){
        filterStr = "id LIKE '%%1%' OR name LIKE '%%1%' OR gender LIKE '%%1%' OR date_of_birth LIKE '%%1%' OR date_of_death LIKE '%%1%' OR country LIKE '%%1%'";
    }
    else if(column == 1){
        filterStr = "id LIKE '%%1%'";
    }
    else if(column == 2){
        filterStr = "name LIKE '%%1%'";
    }
    else if(column == 3){
        filterStr = "gender LIKE '%%1%'";
    }
    else if(column == 4){
        filterStr = "date_of_birth LIKE '%%1%'";
    }
    else if(column == 5){
        filterStr = "date_of_death LIKE '%%1%'";
    }
    else if(column == 6){
        filterStr = "country LIKE '%%1%'";
    }

    setFilterPerson(filterStr, searchString);
}

void MainWindow::filterPerson(QString searchString)
{
    int column = ui->personFilterComboBox->currentIndex();

    QString filterStr = "";
    if(column == 0){
        filterStr = "id NOT LIKE '%%1%' AND name NOT LIKE '%%1%' AND gender NOT LIKE '%%1%' AND date_of_birth NOT LIKE '%%1%' AND date_of_death NOT LIKE '%%1%' AND country NOT LIKE '%%1%'";
    }
    else if(column == 1){
        filterStr = "id NOT LIKE '%%1%'";
    }
    else if(column == 2){
        filterStr = "name NOT LIKE '%%1%'";
    }
    else if(column == 3){
        filterStr = "gender NOT LIKE '%%1%'";
    }
    else if(column == 4){
        filterStr = "date_of_birth NOT LIKE '%%1%'";
    }
    else if(column == 5){
        filterStr = "date_of_death NOT LIKE '%%1%'";
    }
    else if(column == 6){
        filterStr = "country NOT LIKE '%%1%'";
    }

    if(filterStr == ""){
        return;
    }

    setFilterPerson(filterStr, searchString);
}

void MainWindow::on_personFilterField_textChanged(const QString &arg1)
{
    filterPerson(arg1);
}

void MainWindow::on_personSearchField_textChanged(const QString &arg1)
{
    searchPerson(arg1);

}

void MainWindow::on_personSearchComboBox_currentIndexChanged(int index)
{
    QString searchString = ui->personSearchField->text();
    searchPerson(searchString);
}

void MainWindow::on_personFilterComboBox_currentIndexChanged(int index)
{
    QString searchString = ui->personFilterField->text();
    filterPerson(searchString);
}

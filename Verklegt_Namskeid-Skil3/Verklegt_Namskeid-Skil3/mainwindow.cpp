#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "utilities.h"
#include "constants.h"
#include <QMessageBox>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlTableModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
    ui->personTable->horizontalHeader()->setStretchLastSection(true);
    ui->personTable->horizontalHeader()->setSectionsClickable(true);
    ui->personTable->setAlternatingRowColors(true);
    ui->personTable->setSortingEnabled(true);
    ui->personTable->sortByColumn(0, Qt::AscendingOrder);
    ui->personTable->resizeColumnsToContents();
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
    ui->machineTable->horizontalHeader()->setStretchLastSection(true);
    ui->machineTable->horizontalHeader()->setSectionsClickable(true);
    ui->machineTable->setAlternatingRowColors(true);
    ui->machineTable->setSortingEnabled(true);
    ui->machineTable->sortByColumn(0, Qt::AscendingOrder);
    ui->machineTable->resizeColumnsToContents();
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
    ui->PMTable->horizontalHeader()->setStretchLastSection(true);
    ui->PMTable->horizontalHeader()->setSectionsClickable(true);
    ui->PMTable->setAlternatingRowColors(true);
    ui->PMTable->setSortingEnabled(true);
    ui->PMTable->sortByColumn(0, Qt::AscendingOrder);
    ui->PMTable->resizeColumnsToContents();
    ui->PMTable->show();
}

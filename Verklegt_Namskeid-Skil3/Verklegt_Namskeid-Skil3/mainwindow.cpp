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

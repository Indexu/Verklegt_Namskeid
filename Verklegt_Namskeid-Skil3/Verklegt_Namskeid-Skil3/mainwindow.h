#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include <QSortFilterProxyModel>
#include <QTableView>
#include <QMessageBox>
#include <QMenu>
#include "data.h"
#include "services.h"
#include "addpersondialog.h"
#include "editpersondialog.h"
#include "addmachinedialog.h"
#include "utilities.h"
#include "constants.h"
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // Display functions
    void displayPersonTable();
    void displayMachinesTable();
    void displayConnectionsTable();

    // Configure tables
    void configTables();
    // Get models
    void getModels();
    // Set model headers
    void setModelHeaders();
    // Set table models
    void setTableModels();
    // Add items to comboboxes
    void addToComboboxes();
    // Set table properties
    void setTableProperties(QTableView *tab);
    // Set context menus
    void setContextMenus();
    // Check error
    void checkError();

    // === Person ===
    // Update person results label
    void updatePersonResults();
    // Check if re-search
    void checkPersonSearch();
    // Disable Person edit and delete buttons
    void disableEditDeletePersonButtons();
    // Search person
    void searchPerson(QString searchString,int column);
    // Delete person
    void deletePerson();
    // Edit person
    void editPerson();

    // === Machine ===
    // Update machine results label
    void updateMachineResults();
    // Check if re-search
    void checkMachineSearch();
    // Disable machine edit and delete buttons
    void disableEditDeleteMachineButtons();
    // Search machine
    void searchMachine(QString searchString,int column);
    // Delete machine
    void deleteMachine();
    // Edit machine
    void editMachine();

private slots:
    void on_personSearchField_textChanged(const QString &arg1);

    void on_personSearchComboBox_currentIndexChanged(int index);

    void on_personAddButton_clicked();

    void on_actionDeletePerson_triggered();

    void on_personTable_doubleClicked(const QModelIndex &index);

    void on_actionEditPerson_triggered();

    void on_personFilterCheckBox_clicked();

    void on_personDeleteButton_clicked();

    void on_personTable_clicked(const QModelIndex &index);

    void on_personTable_customContextMenuRequested(const QPoint &pos);

    void on_personEditButton_clicked();

    void on_machinesFilterCheckBox_clicked();

    void on_machinesSearchComboBox_currentIndexChanged(int index);

    void on_machinesSearchField_textChanged(const QString &arg1);

    void on_machinesAddButton_clicked();

private:
    Ui::MainWindow *ui;
    Data dataLayer;
    Services servicesLayer;

    QSqlQueryModel *personQueryModel;
    QSortFilterProxyModel *personProxyModel;

    QSqlQueryModel *machineQueryModel;
    QSortFilterProxyModel *machineProxyModel;

    QSqlQueryModel *connectionsQueryModel;
    QSortFilterProxyModel *connectionsProxyModel;

    QString error;
    QMenu personContextMenu;

};

#endif // MAINWINDOW_H

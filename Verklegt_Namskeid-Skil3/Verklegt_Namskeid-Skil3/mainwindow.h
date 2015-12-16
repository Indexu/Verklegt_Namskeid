#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include <QSortFilterProxyModel>
#include <QTableView>
#include <QMessageBox>
#include <QMenu>
#include "data/data.h"
#include "domain/services.h"
#include "ui/addpersondialog.h"
#include "ui/editpersondialog.h"
#include "ui/addmachinedialog.h"
#include "ui/editmachinedialog.h"
#include "ui/connecttomachine.h"
#include "ui/connecttoperson.h"
#include "ui/addconnectiondialog.h"
#include "ui/addtypesystemdialog.h"
#include "ui/edittypesystemdialog.h"
#include "utilities/utilities.h"
#include "utilities/constants.h"
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
    void displayTypesTable();
    void displaySystemsTable();

    // Configure tables
    void configTables();
    // Get models
    void getModels();
    // Connect currentRowChanged signals to slots for tables
    void connectCurrentRowChanged();
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

    // ==== Persons ====
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
    // Connect to machine
    void connectToMachine();

    // ==== Machines ====
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
    // Connect to person
    void connectToPerson();

    // ==== Connections ====
    // Update connections results label
    void updateConnectionResults();
    // Check if re-search
    void checkConnectionsSearch();
    // Search connections
    void searchConnections(QString searchString,int column);
    // Delete connection
    void deleteConnection();

    // ==== Types ====
    // Update types results label
    void updateTypeResults();
    // Check if re-search
    void checkTypeSearch();
    // Disable Type edit and delete buttons
    void disableEditDeleteTypeButtons();
    // Search type
    void searchType(QString searchString,int column);
    // Delete type
    void deleteType();
    // Edit type
    void editType();

    // ==== Systems ====
    // Update Systems results label
    void updateSystemResults();
    // Check if re-search
    void checkSystemSearch();
    // Disable System edit and delete buttons
    void disableEditDeleteSystemButtons();
    // Search System
    void searchSystem(QString searchString,int column);
    // Delete System
    void deleteSystem();
    // Edit System
    void editSystem();

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

    void on_machinesDeleteButton_clicked();

    void on_machineTable_clicked(const QModelIndex &index);

    void on_machinesEditButton_clicked();

    void on_machineTable_doubleClicked(const QModelIndex &index);

    void on_actionPersonConnectToMachine_triggered();

    void on_actionDeleteMachine_triggered();

    void on_actionEditMachine_triggered();

    void on_actionConnectToPerson_triggered();

    void on_machineTable_customContextMenuRequested(const QPoint &pos);

    void on_connectionsDeleteButton_clicked();

    void on_connectionsTable_clicked(const QModelIndex &index);

    void on_connectionsFilterCheckBox_clicked();

    void on_connectionsSearchComboBox_currentIndexChanged(int index);

    void on_connectionsSearchField_textChanged(const QString &arg1);

    void on_connectionsTable_customContextMenuRequested(const QPoint &pos);

    void on_actionDeleteConnection_triggered();

    void on_addConnectionButton_clicked();

    void personTableCurrentRowChanged(const QModelIndex &current, const QModelIndex &previous);

    void machineTableCurrentRowChanged(const QModelIndex &current, const QModelIndex &previous);

    void typesTableCurrentRowChanged(const QModelIndex &current, const QModelIndex &previous);

    void systemsTableCurrentRowChanged(const QModelIndex &current, const QModelIndex &previous);

    void on_typeAddButton_clicked();

    void on_typesTable_clicked(const QModelIndex &index);

    void on_typeDeleteButton_clicked();

    void on_typeFilterCheckBox_clicked();

    void on_typesSearchComboBox_currentIndexChanged(int index);

    void on_typeSearchField_textChanged(const QString &arg1);

    void on_typeEditButton_clicked();

    void on_actionDeleteType_triggered();

    void on_actionEditType_triggered();

    void on_typesTable_customContextMenuRequested(const QPoint &pos);

    void on_systemAddButton_clicked();

    void on_systemsTable_clicked(const QModelIndex &index);

    void on_systemDeleteButton_clicked();

    void on_systemFilterCheckBox_clicked();

    void on_systemSearchComboBox_currentIndexChanged(int index);

    void on_systemSearchField_textChanged(const QString &arg1);

    void on_systemEditButton_clicked();

    void on_actionDeleteSystem_triggered();

    void on_actionEditSystem_triggered();

    void on_systemsTable_customContextMenuRequested(const QPoint &pos);

    void on_typesTable_doubleClicked(const QModelIndex &index);

    void on_systemsTable_doubleClicked(const QModelIndex &index);

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

    QSqlQueryModel *typeQueryModel;
    QSortFilterProxyModel *typeProxyModel;

    QSqlQueryModel *systemQueryModel;
    QSortFilterProxyModel *systemProxyModel;

    QString error;

    QMenu personContextMenu;
    QMenu machineContextMenu;
    QMenu connectionContextMenu;
    QMenu typeContextMenu;
    QMenu systemContextMenu;

};

#endif // MAINWINDOW_H

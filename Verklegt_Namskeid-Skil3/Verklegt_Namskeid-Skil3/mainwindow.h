#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSortFilterProxyModel>
#include <QTableView>
#include <QMessageBox>
#include <QMenu>
#include "data.h"
#include "services.h"
#include "addpersondialog.h"
#include "editpersondialog.h"

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

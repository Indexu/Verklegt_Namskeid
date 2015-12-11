#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTableView>
#include <QMenu>
#include "data.h"
#include "services.h"
#include "adddialog.h"
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
    // Delete person
    void deletePerson();

private slots:
    void personContextMenuSlot(const QPoint& pos);

    void on_personFilterField_textChanged(const QString &arg1);

    void on_personSearchField_textChanged(const QString &arg1);

    void on_personSearchComboBox_currentIndexChanged(int index);

    void on_personFilterComboBox_currentIndexChanged(int index);

    void on_personAddButton_clicked();

    void on_personDeleteButton_clicked();

    void on_personTable_clicked(const QModelIndex &index);

    void on_actionDeletePerson_triggered();

    void on_personTable_doubleClicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    Data dataLayer;
    Services servicesLayer;
    QSqlTableModel *personModel;
    QSqlTableModel *machineModel;
    QSqlTableModel *connectionsModel;
    QString error;
    QMenu personContextMenu;
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTableView>
#include "data.h"
#include "services.h"
#include "adddialog.h"

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

    // Get models
    void getModels();
    // Set model headers
    void setModelHeaders();
    // Add items to comboboxes
    void addToComboboxes();
    // Set table properties
    void setTableProperties(QTableView *tab);
    // Check error
    void checkError();
    
   

private slots:

    void on_personFilterField_textChanged(const QString &arg1);

    void on_personSearchField_textChanged(const QString &arg1);

    void on_personSearchComboBox_currentIndexChanged(int index);

    void on_personFilterComboBox_currentIndexChanged(int index);

    void on_personAddButton_clicked();

    void on_personDeleteButton_clicked();

private:
    Ui::MainWindow *ui;
    Data dataLayer;
    Services servicesLayer;
    QSqlTableModel *personModel;
    QSqlTableModel *machineModel;
    QSqlTableModel *connectionsModel;
    QString error;
};

#endif // MAINWINDOW_H

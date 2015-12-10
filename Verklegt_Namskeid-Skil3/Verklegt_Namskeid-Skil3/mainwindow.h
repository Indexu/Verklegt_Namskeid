#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTableView>
#include "data.h"
#include "services.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void displayPersonTable();
    void displayMachinesTable();
    void displayConnectionsTable();

    void getModels();
    void addToComboboxes();
    void setTableProperties(QTableView *tab);
    void setFilterPerson(QString filterStr, QString searchString);
    void searchPerson(QString searchString);
    void filterPerson(QString searchString);

private slots:

    void on_personFilterField_textChanged(const QString &arg1);

    void on_personSearchField_textChanged(const QString &arg1);

    void on_personSearchComboBox_currentIndexChanged(int index);

    void on_personFilterComboBox_currentIndexChanged(int index);

    void on_personDeleteButton_clicked();

private:
    Ui::MainWindow *ui;
    Data dataLayer;
    Services servicesLayer;
    QSqlTableModel *personModel;
    QSqlTableModel *machineModel;
    QSqlTableModel *connectionsModel;
};

#endif // MAINWINDOW_H

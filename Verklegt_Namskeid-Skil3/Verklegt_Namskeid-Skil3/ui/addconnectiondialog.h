#ifndef ADDCONNECTIONDIALOG_H
#define ADDCONNECTIONDIALOG_H

#include <QDialog>
#include <QSortFilterProxyModel>
#include <QTableView>
#include "utilities/utilities.h"

namespace Ui {
class AddConnectionDialog;
}

class AddConnectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddConnectionDialog(QWidget *parent = 0);
    ~AddConnectionDialog();

    // Set person model
    void setPersonModel(QSortFilterProxyModel *p);
    // Set machine model
    void setMachineModel(QSortFilterProxyModel *m);

    // Display tables
    void displayTables();
    // Set table properties
    void setTableProperties(QTableView *tab);

    // Verify IDs are set
    void verifyIds();

    // Get person ID
    int getPersonId();
    // Get machine ID
    int getMachineId();

private slots:
    void on_cancelButton_clicked();

    void on_connectButton_clicked();

    void on_personsTable_clicked(const QModelIndex &index);

    void on_machinesTable_clicked(const QModelIndex &index);

private:
    Ui::AddConnectionDialog *ui;
    QSortFilterProxyModel *personsConnectionModel;
    QSortFilterProxyModel *machinesConnectionModel;
    int P_id;
    int M_id;
    bool personValid;
    bool machineValid;
};

#endif // ADDCONNECTIONDIALOG_H

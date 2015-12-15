#ifndef CONNECTTOMACHINE_H
#define CONNECTTOMACHINE_H

#include <QDialog>
#include <QSortFilterProxyModel>
#include "utilities/utilities.h"

namespace Ui {
class ConnectToMachine;
}

class ConnectToMachine : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectToMachine(QWidget *parent = 0);
    ~ConnectToMachine();

    // Set the table model
    void setModel(QSortFilterProxyModel *&m);

    // Display the table
    void displayTable();

    // Get the machine ID
    int getId();

private slots:
    void on_cancelButton_clicked();

    void on_machinesTable_clicked(const QModelIndex &index);

    void on_connectButton_clicked();

private:
    Ui::ConnectToMachine *ui;
    QSortFilterProxyModel *machinesConnectionModel;
    int Id;
};

#endif // CONNECTTOMACHINE_H

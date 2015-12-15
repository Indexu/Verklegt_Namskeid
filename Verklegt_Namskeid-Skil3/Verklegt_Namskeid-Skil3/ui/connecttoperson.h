#ifndef CONNECTTOPERSON_H
#define CONNECTTOPERSON_H

#include <QDialog>
#include <QSortFilterProxyModel>
#include "utilities/utilities.h"

namespace Ui {
class ConnectToPerson;
}

class ConnectToPerson : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectToPerson(QWidget *parent = 0);
    ~ConnectToPerson();

    // Set the table model
    void setModel(QSortFilterProxyModel *p);

    // Display the table
    void displayTable();

    // Get the person ID
    int getId();

private slots:
    void on_cancelButton_clicked();

    void on_connectButton_clicked();

    void on_personsTable_clicked(const QModelIndex &index);

private:
    Ui::ConnectToPerson *ui;
    QSortFilterProxyModel *personsConnectionModel;
    int Id;
};

#endif // CONNECTTOPERSON_H

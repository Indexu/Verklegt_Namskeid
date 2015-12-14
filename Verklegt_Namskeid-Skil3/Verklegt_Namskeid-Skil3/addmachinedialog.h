#ifndef ADDMACHINEDIALOG_H
#define ADDMACHINEDIALOG_H

#include <QDialog>
#include "machine.h"
#include "typesystem.h"
#include <QDebug>

namespace Ui {
class AddMachineDialog;
}

class AddMachineDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddMachineDialog(QWidget *parent = 0);
    ~AddMachineDialog();

    // Get machine
    Machine getMachine();

    // Add to comboboxes
    void addToComboboxes();

    // Set types
    void setTypes(const QVector<TypeSystem> &t);

    // Set systems
    void setSystems(const QVector<TypeSystem> &s);

    // Verify data
    void verifyInputs();

    // Get click
    bool getAddClick();

private slots:
    void on_addButton_clicked();

    void on_cancelButton_clicked();

    void on_nameField_textChanged(const QString &arg1);

    void on_yearEdit_dateChanged(const QDate &date);

    void on_builtYesRadioButton_clicked();

    void on_builtNoRadioButton_clicked();

    void on_systemCombobox_currentIndexChanged(const QString &arg1);

    void on_typeCombobox_currentIndexChanged(const QString &arg1);

    void on_yearUnknownCheckbox_clicked(bool checked);

private:
    Ui::AddMachineDialog *ui;
    Machine newMachine;
    QVector<TypeSystem> types;
    QVector<TypeSystem> systems;
    bool addClick;
};

#endif // ADDMACHINEDIALOG_H

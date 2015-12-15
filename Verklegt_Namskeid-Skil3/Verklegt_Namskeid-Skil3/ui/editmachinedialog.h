#ifndef EDITMACHINEDIALOG_H
#define EDITMACHINEDIALOG_H

#include <QDialog>
#include "models/machine.h"
#include "models/typesystem.h"
#include "utilities/constants.h"

namespace Ui {
class editMachineDialog;
}

class editMachineDialog : public QDialog
{
    Q_OBJECT

public:
    explicit editMachineDialog(QWidget *parent = 0);
    ~editMachineDialog();

    // Set machine
    void setMachine(const Machine &m);

    // Set fields
    void setFields();

    // Add to comboboxes
    void addToComboboxes();

    // Set types
    void setTypes(const QVector<TypeSystem> &t);
    // Set systems
    void setSystems(const QVector<TypeSystem> &s);

    // Get machine
    Machine getMachine();

    // Verify inputs
    void verifyInputs();

private slots:
    void on_editMachineNameField_textChanged(const QString &arg1);

    void on_editMachineYear_dateChanged(const QDate &date);

    void on_editMachineType_currentIndexChanged(const QString &arg1);

    void on_editMachineSystem_currentIndexChanged(const QString &arg1);

    void on_editMachinecancelButton_clicked();

    void on_builtYesRadioButton_clicked();

    void on_builtNoRadioButton_clicked();

    void on_yearUnknownCheckbox_clicked(bool checked);

    void on_editMachineSaveButton_clicked();

private:
    Ui::editMachineDialog *ui;
    QVector<TypeSystem> types;
    QVector<TypeSystem> systems;
    Machine editMachine;
};

#endif // EDITMACHINEDIALOG_H

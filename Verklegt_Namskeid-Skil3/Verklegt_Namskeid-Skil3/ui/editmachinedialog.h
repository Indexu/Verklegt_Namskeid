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
    bool getSaveClick();
    void setMachine(const Machine &m);
    void setFields();
    void addToComboboxes();
    void setTypes(const QVector<TypeSystem> &t);
    void setSystems(const QVector<TypeSystem> &s);
    Machine getMachine();
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
    QVector<TypeSystem> types;
    QVector<TypeSystem> systems;
    Machine editMachine;
    bool saveClick;
    Ui::editMachineDialog *ui;
};

#endif // EDITMACHINEDIALOG_H

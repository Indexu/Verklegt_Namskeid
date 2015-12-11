#ifndef EDITPERSONDIALOG_H
#define EDITPERSONDIALOG_H

#include <QDialog>
#include "person.h"
#include "constants.h"

namespace Ui {
class editPersonDialog;
}

class editPersonDialog : public QDialog
{
    Q_OBJECT

public:
    explicit editPersonDialog(QWidget *parent = 0);
    ~editPersonDialog();

    void setFields();
    void setPerson(const Person &p);
    Person getPerson();

private slots:
    void on_pushButton_clicked();

    void on_aliveCheckBox_clicked();

private:
    Ui::editPersonDialog *ui;
    Person editPerson;
};

#endif // EDITPERSONDIALOG_H

#ifndef EDITPERSONDIALOG_H
#define EDITPERSONDIALOG_H

#include <QDialog>
#include "person.h"

namespace Ui {
class editPersonDialog;
}

class editPersonDialog : public QDialog
{
    Q_OBJECT

public:
    explicit editPersonDialog(QWidget *parent = 0);
    ~editPersonDialog();

    void setPerson(const Person &p);

private slots:
    void on_pushButton_clicked();

private:
    Ui::editPersonDialog *ui;
    Person editPerson;
    int Id;
};

#endif // EDITPERSONDIALOG_H

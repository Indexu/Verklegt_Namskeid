#ifndef EDITPERSONDIALOG_H
#define EDITPERSONDIALOG_H

#include <QDialog>

namespace Ui {
class editPersonDialog;
}

class editPersonDialog : public QDialog
{
    Q_OBJECT

public:
    explicit editPersonDialog(QWidget *parent = 0);
    ~editPersonDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::editPersonDialog *ui;
};

#endif // EDITPERSONDIALOG_H

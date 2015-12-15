#ifndef ADDTYPESYSTEMDIALOG_H
#define ADDTYPESYSTEMDIALOG_H

#include <QDialog>

namespace Ui {
class AddTypeSystemDialog;
}

class AddTypeSystemDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddTypeSystemDialog(QWidget *parent = 0);
    ~AddTypeSystemDialog();

    // Get name
    QString getName();

    // Set the title
    void setTitle(const QString &t);

private slots:
    void on_cancelButton_clicked();

    void on_addButton_clicked();

    void on_nameField_textChanged(const QString &arg1);

private:
    Ui::AddTypeSystemDialog *ui;
    QString Name;
};

#endif // ADDTYPESYSTEMDIALOG_H

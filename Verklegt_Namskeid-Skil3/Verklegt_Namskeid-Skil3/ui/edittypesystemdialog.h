#ifndef EDITTYPESYSTEMDIALOG_H
#define EDITTYPESYSTEMDIALOG_H

#include <QDialog>

namespace Ui {
class EditTypeSystemDialog;
}

class EditTypeSystemDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditTypeSystemDialog(QWidget *parent = 0);
    ~EditTypeSystemDialog();

    // Get name
    QString getName();
    // Set name
    void setName(const QString &n);

    // Set the title
    void setTitle(const QString &t);
    // Set field values
    void setFields();

private slots:
    void on_cancelButton_clicked();

    void on_addButton_clicked();

    void on_nameField_textChanged(const QString &arg1);

private:
    Ui::EditTypeSystemDialog *ui;
    QString Name;
};

#endif // EDITTYPESYSTEMDIALOG_H

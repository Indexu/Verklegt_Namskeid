#ifndef EDITPERSONDIALOG_H
#define EDITPERSONDIALOG_H

#include <QDialog>

namespace Ui {
class editpersondialog;
}

class editpersondialog : public QDialog
{
    Q_OBJECT

public:
    explicit editpersondialog(QWidget *parent = 0);
    ~editpersondialog();

private:
    Ui::editpersondialog *ui;
};

#endif // EDITPERSONDIALOG_H

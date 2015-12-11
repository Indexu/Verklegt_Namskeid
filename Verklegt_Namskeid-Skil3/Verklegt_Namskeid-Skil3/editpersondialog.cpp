#include "editpersondialog.h"
#include "ui_editpersondialog.h"

editpersondialog::editpersondialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editpersondialog)
{
    ui->setupUi(this);
}

editpersondialog::~editpersondialog()
{
    delete ui;
}

#include "editpersondialog.h"
#include "ui_editpersondialog.h"

editPersonDialog::editPersonDialog(QWidget *parent) :
      QDialog(parent),
    ui(new Ui::editPersonDialog)
{

    ui->setupUi(this);

    ui->editPersonNameField->setText("HIIII!");
    ui->editPersonCountryField->setText("Hi");
}

editPersonDialog::~editPersonDialog()
{
    delete ui;
}

void editPersonDialog::setPerson(const Person &p)
{
    editPerson = p;
}


// Cancel button -> click
void editPersonDialog::on_pushButton_clicked()
{
    this->close();
}

#include "addtypesystemdialog.h"
#include "ui_addtypesystemdialog.h"

AddTypeSystemDialog::AddTypeSystemDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTypeSystemDialog)
{
    ui->setupUi(this);

    // Disable add button
    ui->addButton->setEnabled(false);
    ui->nameField->setStyleSheet("background-color: #FFC2C2");
}

AddTypeSystemDialog::~AddTypeSystemDialog()
{
    delete ui;
}

// Get name
QString AddTypeSystemDialog::getName(){
    return Name;
}

// Set title
void AddTypeSystemDialog::setTitle(const QString &t){
    QString header = "<html><head/><body><p>"
                     "<span style='font-size:x-large; font-weight:600;'>"
                     + t + "</span></p></body></html>";

    ui->windowHeader->setText(header);
    this->setWindowTitle(t);
}

// Cancel button -> clicked
void AddTypeSystemDialog::on_cancelButton_clicked(){
    this->done(0);
}

// Add button -> clicked
void AddTypeSystemDialog::on_addButton_clicked(){
    this->done(1);
}

// Name field -> text changed
void AddTypeSystemDialog::on_nameField_textChanged(const QString &arg1){
    Name = arg1;

    if(Name.isEmpty()){
        ui->addButton->setEnabled(false);
        ui->nameField->setStyleSheet("background-color: #FFC2C2");
    }
    else{
        ui->addButton->setEnabled(true);
        ui->nameField->setStyleSheet("background-color: #FFFFFF");
    }
}

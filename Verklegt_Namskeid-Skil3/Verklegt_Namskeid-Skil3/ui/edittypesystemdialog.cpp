#include "edittypesystemdialog.h"
#include "ui_edittypesystemdialog.h"

EditTypeSystemDialog::EditTypeSystemDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditTypeSystemDialog)
{
    ui->setupUi(this);
}

EditTypeSystemDialog::~EditTypeSystemDialog()
{
    delete ui;
}

// Get name
QString EditTypeSystemDialog::getName(){
    return Name;
}

// Set name
void EditTypeSystemDialog::setName(const QString &n){
    Name = n;
}

// Set title
void EditTypeSystemDialog::setTitle(const QString &t){
    QString header = "<html><head/><body><p>"
                     "<span style='font-size:x-large; font-weight:600;'>"
                     + t + "</span></p></body></html>";

    ui->windowHeader->setText(header);
    this->setWindowTitle(t);
}

// Set fields
void EditTypeSystemDialog::setFields(){
    ui->nameField->setText(Name);
}

// Cancel button -> clicked
void EditTypeSystemDialog::on_cancelButton_clicked(){
    this->done(0);
}

// Add button -> clicked
void EditTypeSystemDialog::on_addButton_clicked(){
    this->done(1);
}

// Name field -> text changed
void EditTypeSystemDialog::on_nameField_textChanged(const QString &arg1){
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

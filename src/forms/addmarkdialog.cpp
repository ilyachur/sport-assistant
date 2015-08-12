#include "addmarkdialog.h"
#include "ui_addmarkdialog.h"

AddMarkDialog::AddMarkDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddMarkDialog)
{
    ui->setupUi(this);
}

AddMarkDialog::~AddMarkDialog()
{
    delete ui;
}

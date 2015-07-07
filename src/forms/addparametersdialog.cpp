#include "addparametersdialog.h"
#include "ui_addparametersdialog.h"

AddParametersDialog::AddParametersDialog(int _activityID, QString dbName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddParametersDialog)
{
    ui->setupUi(this);
}

AddParametersDialog::~AddParametersDialog()
{
    delete ui;
}

#include "marktrainingdialog.h"
#include "ui_marktrainingdialog.h"

MarkTrainingDialog::MarkTrainingDialog(int _activityID, QString dbName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MarkTrainingDialog)
{
    ui->setupUi(this);
}

MarkTrainingDialog::~MarkTrainingDialog()
{
    delete ui;
}

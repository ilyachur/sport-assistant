#include "addactivity.h"
#include "ui_addactivity.h"
#include <QMessageBox>

#include "addparametersdialog.h"

AddActivity::AddActivity(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddActivity)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(":/icons/heart.ico"));

    QObject::connect(ui->btnCancel, SIGNAL(clicked(bool)), this, SLOT(close()));
    QObject::connect(ui->btnOK, SIGNAL(clicked(bool)), this, SLOT(add()));
}

AddActivity::~AddActivity()
{
    delete ui;
}

void AddActivity::add() {
    if (ui->lineEdit->text() == "") {
        QMessageBox::warning(this, "Warning!", "Scheme name is empty!");
        return;
    }
    ((AddParametersDialog *)parentWidget())->setActivityTypes(ui->lineEdit->text());
    close();
}

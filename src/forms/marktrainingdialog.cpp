#include "marktrainingdialog.h"
#include "ui_marktrainingdialog.h"

#include "../widgets/qhspinboxrangeslider.h"
#include "../widgets/qhrangeslider.h"

MarkTrainingDialog::MarkTrainingDialog(int _activityID, QString dbName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MarkTrainingDialog)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(":/icons/heart.ico"));

    this->parent = parent;

    QHSpinBoxRangeSlider * spinBoxSlider = new QHSpinBoxRangeSlider(0, 100, 1, 22, 23);

    ui->verticalLayout->addWidget(spinBoxSlider);

    //QObject::connect(ui->)
}

MarkTrainingDialog::~MarkTrainingDialog()
{
    delete ui;
}

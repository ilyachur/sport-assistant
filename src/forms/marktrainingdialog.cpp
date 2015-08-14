#include "marktrainingdialog.h"
#include "ui_marktrainingdialog.h"

#include <QDebug>

MarkTrainingDialog::MarkTrainingDialog(int _activityID, QString dbName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MarkTrainingDialog)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(":/icons/heart.ico"));

    this->parent = parent;
    activityID = _activityID;
    dataBaseName = dbName;

    addMarkSlider();

    QObject::connect(ui->btnAddMarkSlider, SIGNAL(clicked(bool)), this, SLOT(addMarkSlider()));
}

MarkTrainingDialog::~MarkTrainingDialog()
{
    delete ui;
}

void MarkTrainingDialog::addMarkSlider(bool saved) {
    QHBoxLayout *newLayout = new QHBoxLayout();
    layoutsList.append(newLayout);
    savedList.append(saved);

    FunctionWrapper * wrapper = new FunctionWrapper(functionsWrappersList.size());
    functionsWrappersList.append(wrapper);

    QHSpinBoxRangeSlider * spinBoxSlider = new QHSpinBoxRangeSlider(0, 100, 1, 22, 23);
    slidersList.append(spinBoxSlider);
    QObject::connect(spinBoxSlider, SIGNAL(rangeChanged(double,double)), wrapper, SLOT(rangeChanged(double,double)));
    QObject::connect(wrapper, SIGNAL(rangeChangedID(int)), this, SLOT(updateButtonState(int)));

    QLineEdit *activityName = new QLineEdit();
    QObject::connect(activityName, SIGNAL(textChanged(QString)), wrapper, SLOT(textChanged(QString)));
    QObject::connect(wrapper, SIGNAL(textChangedID(int)), this, SLOT(updateButtonState(int)));
    lineEditList.append(activityName);
    activityName->setMaximumWidth(100);

    QPushButton *addRemoveUpdateBtn = new QPushButton("Add");
    QObject::connect(addRemoveUpdateBtn, SIGNAL(clicked(bool)), wrapper, SLOT(clicked(bool)));
    QObject::connect(wrapper, SIGNAL(clickedID(int)), this, SLOT(addRemoveUpdateMark(int)));
    newLayout->addWidget(spinBoxSlider);
    newLayout->addWidget(activityName);
    newLayout->addWidget(addRemoveUpdateBtn);
    buttonsList.append(addRemoveUpdateBtn);
    ui->slidersLayout->addLayout(newLayout);
}

void MarkTrainingDialog::updateButtonState(int index) {
    qDebug() << index;
}

void MarkTrainingDialog::addRemoveUpdateMark(int index) {
    qDebug() << index;
}

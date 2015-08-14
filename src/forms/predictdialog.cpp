#include "predictdialog.h"
#include "ui_predictdialog.h"

PredictDialog::PredictDialog(int activityID, QString dbName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PredictDialog)
{
    ui->setupUi(this);

    this->activityID = activityID;
    dataBaseName = dbName;

    athleteDB.setNameDB(dataBaseName);

    setActivityTypes();

    if (activityTypes.size() > 0)
        currentScheme = activityTypes.at(0).at(0);


    QObject::connect(ui->comboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(changeScheme()));
    QObject::connect(ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));
    QObject::connect(ui->btnPredict, SIGNAL(clicked(bool)), this, SLOT(predictResult()));
}

PredictDialog::~PredictDialog()
{
    delete ui;
}

void PredictDialog::setActivityTypes() {
    ui->comboBox->clear();
    activityTypes = athleteDB.getActivityTypes();
    for(auto i(0); i < activityTypes.size(); i++) {
        ui->comboBox->addItem(activityTypes.at(i).at(0));
    }
}

void PredictDialog::changeScheme() {
    currentScheme = ui->comboBox->currentText();
    for(auto i(0); i < activityTypes.size(); i++) {
        //if (currentScheme == activityTypes.at(i).at(0))
            //setParams(i);
    }
}

void PredictDialog::predictResult() {

}

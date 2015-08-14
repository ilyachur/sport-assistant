#include "marktrainingdialog.h"
#include "ui_marktrainingdialog.h"

#include <QMessageBox>

MarkTrainingDialog::MarkTrainingDialog(int _activityID, QString dbName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MarkTrainingDialog)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(":/icons/heart.ico"));

    this->parent = parent;
    activityID = _activityID;
    dataBaseName = dbName;
    athleteDB.setNameDB(dataBaseName);

    addSubActivities();

    QObject::connect(ui->btnAddMarkSlider, SIGNAL(clicked(bool)), this, SLOT(addMarkSlider()));
}

MarkTrainingDialog::~MarkTrainingDialog()
{
    for(auto i(0); i < slidersList.size(); i++) {
        layoutsList.at(i)->removeWidget(slidersList.at(i));
        layoutsList.at(i)->removeWidget(lineEditList.at(i));
        layoutsList.at(i)->removeWidget(buttonsList.at(i));
        delete slidersList.at(i);
        delete lineEditList.at(i);
        delete buttonsList.at(i);
        delete functionsWrappersList.at(i);
        ui->slidersLayout->removeItem(layoutsList.at(i));
        delete layoutsList.at(i);
    }

    functionsWrappersList.clear();
    activitiesIdList.clear();
    lineEditList.clear();
    layoutsList.clear();
    slidersList.clear();
    buttonsList.clear();

    delete ui;
}

void MarkTrainingDialog::addMarkSlider(int activityId, QString activityNameStr, int from, int to) {
    if (to <= 0) {
        to = timeLineLong.size();
    }
    QHBoxLayout *newLayout = new QHBoxLayout();
    layoutsList.append(newLayout);
    activitiesIdList.append(activityId);

    FunctionWrapper * wrapper = new FunctionWrapper(functionsWrappersList.size());
    functionsWrappersList.append(wrapper);

    QHSpinBoxRangeSlider * spinBoxSlider = new QHSpinBoxRangeSlider(0, timeLineLong.size(), 1, from, to);
    slidersList.append(spinBoxSlider);
    QObject::connect(spinBoxSlider, SIGNAL(rangeChanged(double,double)), wrapper, SLOT(rangeChanged(double,double)));
    QObject::connect(wrapper, SIGNAL(rangeChangedID(int)), this, SLOT(updateButtonState(int)));

    QLineEdit *activityName = new QLineEdit();
    lineEditList.append(activityName);
    if (activityNameStr != "")
        activityName->setText(activityNameStr);
    activityName->setMaximumWidth(100);
    QObject::connect(activityName, SIGNAL(textChanged(QString)), wrapper, SLOT(textChanged(QString)));
    QObject::connect(wrapper, SIGNAL(textChangedID(int)), this, SLOT(updateButtonState(int)));


    QPushButton *addRemoveUpdateBtn = new QPushButton("Add");
    if (activityId > 0) {
        addRemoveUpdateBtn->setText("Remove");
    }
    QObject::connect(addRemoveUpdateBtn, SIGNAL(clicked(bool)), wrapper, SLOT(clicked(bool)));
    QObject::connect(wrapper, SIGNAL(clickedID(int)), this, SLOT(addRemoveUpdateMark(int)));
    newLayout->addWidget(spinBoxSlider);
    newLayout->addWidget(activityName);
    newLayout->addWidget(addRemoveUpdateBtn);
    buttonsList.append(addRemoveUpdateBtn);
    ui->slidersLayout->addLayout(newLayout);
}

void MarkTrainingDialog::addSubActivities() {
    QMap<QString, QString> findMap;
    findMap.insert("ID", QString::number(activityID));
    QVector<QStringList> activity = athleteDB.findActivity(findMap);

    if (activity.size() != 1) {
        QMessageBox::critical(this, "Error! Cannot find current activity!",
                              "Activities vector size is " + QString::number(activity.size()) +".");
        close();
        return;
    }

    trainingID = activity.at(0).at(1).toInt();
    activityName = activity.at(0).at(3);
    QString trainingDataStr = activity.at(0).at(4);
    QMap<QString, QString> tempMap = AthleteDB::dumpQString2QMap(trainingDataStr);
    trainingData.clear();
    timeLineLong.clear();

    for(QString key : tempMap.keys()) {
        trainingData.insert(key.toULongLong(), tempMap[key].toDouble());
        timeLineLong.append(key.toULongLong());
    }
    qSort(timeLineLong);

    findMap.clear();
    findMap.insert("training_id", QString::number(trainingID));
    QVector<QStringList> subActivities = athleteDB.findActivity(findMap);

    for (auto i(0); i < subActivities.size(); i++) {
        if (subActivities.at(i).at(0).toInt() == activityID)
            continue;
        int subActivityID = subActivities.at(i).at(0).toInt();
        QString subActivityName = subActivities.at(i).at(3);
        subActivityName.replace("_" + activityName, "");


        QString subTrainingDataStr = subActivities.at(i).at(4);
        QMap<QString, QString> tempSubMap = AthleteDB::dumpQString2QMap(subTrainingDataStr);
        unsigned long long min(-1), max(0);
        for(QString key : tempSubMap.keys()) {
            if (min < 0)
                min = key.toULongLong();
            if (max < 0)
                max = key.toULongLong();
            if (key.toULongLong() > max)
                max = key.toULongLong();
            if (key.toULongLong() < min)
                min = key.toULongLong();
        }

        addMarkSlider(subActivityID, subActivityName, timeLineLong.indexOf(min), timeLineLong.indexOf(max));

    }

    if (!slidersList.size()) {
        addMarkSlider();
    }
}

void MarkTrainingDialog::updateButtonState(int index) {
    if (buttonsList.at(index)->text() == "Add") return;
    buttonsList.at(index)->setText("Update");
}

void MarkTrainingDialog::addRemoveUpdateMark(int index) {
    if (buttonsList.at(index)->text() == "Remove") {
        athleteDB.removeActivity(activityID);
    } else {
        if (lineEditList.at(index)->text() == "") {
            QMessageBox::warning(this, "Warning! Activity name is empty!", "Please, input activity name.");
            return;
        }
        QString subActivityName = lineEditList.at(index)->text() + "_" + activityName;
        double min, max;
        slidersList.at(index)->getValues(&min, &max);

        unsigned long long date = timeLineLong.at((int)min);

        QMap<QString, QString> tempMap;
        for(int i = (int)min; i < (int)max; i++) {
            tempMap.insert(QString::number(timeLineLong.at(i)),
                           QString::number(trainingData[timeLineLong.at(i)]));
        }
        QString dataTraining = AthleteDB::dumpQMap2QString(tempMap);
        athleteDB.addActivity(activitiesIdList.at(index), trainingID, subActivityName, date, dataTraining);

        buttonsList.at(index)->setText("Remove");
    }
}

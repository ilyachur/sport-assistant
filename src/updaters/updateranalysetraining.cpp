#include "updateranalysetraining.h"

#include "../algorithms/analyse.h"
#include "../visualization/qcustomplot.h"

UpdaterAnalyseTraining::UpdaterAnalyseTraining(QString _athleteName, int _activityID, QString dbName,
                                               QMap<unsigned long long, double> trainingMap, QDateTime _date,
                                               QMap<QString, bool> _analyseSettings, QString activity):
    athleteName(_athleteName), activityID(_activityID), databaseName(dbName), training(trainingMap),
    date(_date), analyseSettings(_analyseSettings), activityName(activity)
{
}

void UpdaterAnalyseTraining::run() {
    if (analyseSettings.size() < 1 || training.size() < 1)
        return;

    saveImages = analyseSettings["save_images"];
    //analyseSettings->value("save_csv", false).toBool();

    //bool trainingLoaded = self.load_analysed_trainings(self.__analysed_hash)
    bool trainingLoaded = false;

    //analyseSettings->beginGroup("pre-processing");
    if (analyseSettings["pre-processing:filtered"]) {
        Analysis::Filter trainingFilter(training);
        QObject::connect(&trainingFilter, SIGNAL(notifyProgress(int)), this, SLOT(notifyProgressSlot(int)));
        QObject::connect(&trainingFilter, SIGNAL(notifyProgressRange(int, int)), this, SLOT(notifyProgressRangeSlot(int,int)));
        QObject::connect(&trainingFilter, SIGNAL(buildGrapf(QString, QMap<QString, QVector<double>>*)), this, SLOT(buildGraphSlot(QString,QMap<QString,QVector<double>>*)));
        emit notifyProgressStatus("Filtering training data...");

        training = trainingFilter.simpleFilter();
    }

    if (analyseSettings["analyse:time:timeAnalisys"]) {
        //training = Analyse::simpleFilter(training);
    }

    // TODO: Implemented it
    if (analyseSettings["analyse:spectrum:wavelet"]) {
        // add Functions
    }
    if (analyseSettings["analyse:spectrum:lomb"]) {
        // add Functions
    }
    if (analyseSettings["analyse:spectrum:FFT"]) {
        // add Functions
    }

    emit updaterFinished(activityID);
}

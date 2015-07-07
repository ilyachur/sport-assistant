#include "updateranalysetraining.h"

UpdaterAnalyseTraining::UpdaterAnalyseTraining(QString _athleteName, int _activityID, QString dbName,
                                               QMap<unsigned long long, double> trainingMap, QDateTime _date,
                                               QSettings *_analyseSettings, QString activity):
    athleteName(_athleteName), activityID(_activityID), databaseName(dbName), training(trainingMap),
    date(_date), analyseSettings(_analyseSettings), activityName(activity)
{
}

void UpdaterAnalyseTraining::run() {

}

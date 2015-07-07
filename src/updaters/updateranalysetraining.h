#ifndef UPDATERANALYSETRAINING_H
#define UPDATERANALYSETRAINING_H

#include "updater.h"

#include <QSettings>
#include <QDateTime>
#include <QString>
#include <QMap>

class UpdaterAnalyseTraining : public Updater {
    Q_OBJECT
public:
    UpdaterAnalyseTraining(QString _athleteName, int _activityID, QString dbName,
                           QMap<unsigned long long, double> trainingMap, QDateTime _date,
                           QSettings *_analyseSettings, QString activity);
private:
    void run();

    QString athleteName;
    int activityID;
    QString databaseName;
    QMap<unsigned long long, double> training;
    QSettings *analyseSettings;
    QDateTime date;
    QString activityName;

signals:
    void notifyProgress(int value);
    void notifyProgressRange(int from, int to);
};

#endif // UPDATERANALYSETRAINING_H

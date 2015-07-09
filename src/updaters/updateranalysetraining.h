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
                           QMap<QString, bool> _analyseSettings, QString activity);
private:
    void run();

    QString athleteName;
    int activityID;
    QString databaseName;
    QMap<unsigned long long, double> training;
    QMap<QString, bool> analyseSettings;
    QDateTime date;
    QString activityName;
    bool saveImages = false;
    bool showImages = false;

public slots:
    void notifyProgressSlot(int value) {
        emit notifyProgress(value);
    }

    void notifyProgressRangeSlot(int from, int to) {
        emit notifyProgressRange(from, to);
    }

    void buildGraphSlot(QString name, QMap<QString, QVector<double>> *data) {
        emit buildGraph(name, data);
    }

signals:
    void notifyProgress(int value);
    void notifyProgressRange(int from, int to);
    void notifyProgressStatus(QString status);
    void buildGraph(QString name, QMap<QString, QVector<double>> *data);
};

#endif // UPDATERANALYSETRAINING_H

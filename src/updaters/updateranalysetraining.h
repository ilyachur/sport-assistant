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

    void buildGraphSlot(QString name, QString imageName, QMap<QString, QVector<double>> *data, bool showGraph) {
        emit buildGraph(name, imageName, data, showGraph);
    }

signals:
    void notifyProgress(int value);
    void notifyProgressRange(int from, int to);
    void notifyProgressStatus(QString status);
    void buildGraph(QString name, QString imageName, QMap<QString, QVector<double>> *data, bool showGraph);
    void updaterFinished(int);
};

#endif // UPDATERANALYSETRAINING_H

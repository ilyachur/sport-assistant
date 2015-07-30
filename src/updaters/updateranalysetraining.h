#ifndef UPDATERANALYSETRAINING_H
#define UPDATERANALYSETRAINING_H

#include "updater.h"

#include <QSettings>
#include <QDateTime>
#include <QString>
#include <QMap>

/// @file updateranalysetraining.h
/// @brief Contains definition of updater for training analysis class
/// @author Ilya Churaev ilyachur@gmail.com

/**
 * @brief The UpdaterAnalyseTraining class
 */
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
    /**
     * @brief Temp slot for sent progress from analysis to dialogs
     * @param value - progress range
     */
    void notifyProgressSlot(int value) {
        emit notifyProgress(value);
    }

    /**
     * @brief Temp slot for setting progress bar range
     * @param from - start value
     * @param to - end value
     */
    void notifyProgressRangeSlot(int from, int to) {
        emit notifyProgressRange(from, to);
    }

    /**
     * @brief Temp slot for creating graph by output data
     * @param name of function
     * @param name for saving image
     * @param data map
     * @param flag for showing graph
     */
    void buildGraphSlot(QString name, QString imageName, QMap<QString, QVector<double>> *data, bool showGraph) {
        emit buildGraph(name, imageName, data, showGraph);
    }

signals:
    /**
     * @brief Signal for changing progress bar value
     * @param value - current value
     */
    void notifyProgress(int value);

    /**
     * @brief Signal for setting progress bar range
     * @param from - start value
     * @param to - end value
     */
    void notifyProgressRange(int from, int to);

    /**
     * @brief Signal for setting progress bar status
     * @param status is a string with information about analysing process
     */
    void notifyProgressStatus(QString status);

    /**
     * @brief Signal for creating graph by output data
     * @param name of function
     * @param name for saving image
     * @param data map
     * @param flag for showing graph
     */
    void buildGraph(QString name, QString imageName, QMap<QString, QVector<double>> *data, bool showGraph);

    /**
     * @brief Signal for send message that updater finished
     */
    void updaterFinished(int);
};

#endif // UPDATERANALYSETRAINING_H

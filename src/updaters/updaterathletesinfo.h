#ifndef UPDATERATHLETESINFO_H
#define UPDATERATHLETESINFO_H

#include <QDir>
#include <QDebug>
#include <QString>
#include <QStringList>
#include "updater.h"
#include "../wrappers/athletedb.h"

/// @file updaterathletesinfo.h
/// @brief Contains definition of updater for update athlete info class
/// @author Ilya Churaev ilyachur@gmail.com

/**
 * @brief The UpdaterAthletesInfo class
 */
class UpdaterAthletesInfo: public Updater {
    Q_OBJECT
public:
    UpdaterAthletesInfo(QString _dbName, QString _dDir, bool _doAnalyse=false) {
        dbName = _dbName;
        dDir = _dDir;
        doAnalyse = _doAnalyse;
    }

private:
    QString dbName;
    QString dDir;
    bool doAnalyse;

    void run() {
        if (dbName.isEmpty() || dDir.isEmpty() || !QDir(dDir).exists()) {
            emit notifyProgressRange(0, 1);
            emit notifyProgress(1);
            return;
        }
        AthleteDB athleteDB(dbName);
        QStringList files = QDir(dDir).entryList(QDir::Dirs);
        emit notifyProgressRange(0, files.length() - 2);
        if (files.length() - 2 == 0) {

            emit notifyProgressRange(0, 1);
            emit notifyProgress(1);
            return;
        }
        int count = 0;
        for (QString athleteDir: files) {
            if (killed)
                break;
            if (athleteDir == "." || athleteDir == "..")
                continue;
            count++;
            if (!QDir(dDir + "/" + athleteDir).exists()) {
                emit notifyProgress(count);
                continue;
            }
            qDebug() << "[UpdaterAthletesInfo] " << athleteDir;
            athleteDB.updateAthleteInfo(athleteDir, dDir + "/" + athleteDir);
            emit notifyProgress(count);
        }
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

#endif // UPDATERATHLETESINFO_H

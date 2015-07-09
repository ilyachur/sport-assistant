#ifndef UPDATERATHLETESINFO_H
#define UPDATERATHLETESINFO_H

#include <QDir>
#include <QDebug>
#include <QString>
#include <QStringList>
#include "updater.h"
#include "../wrappers/athletedb.h"

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
    void notifyProgress(int value);
    void notifyProgressRange(int from, int to);
    void notifyProgressStatus(QString status);
    void buildGraph(QString name, QMap<QString, QVector<double>> *data);
};

#endif // UPDATERATHLETESINFO_H

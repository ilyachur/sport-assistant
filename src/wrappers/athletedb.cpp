#include "athletedb.h"

#include <QMap>
#include <QFile>
#include <QDebug>
#include <QDateTime>
#include <QSettings>
#include <QStringList>
#include <QtSql/QSqlError>

AthleteDB::AthleteDB(QString name): databaseName(name)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
}

QVector<QStringList> AthleteDB::findAthletes() {
    QVector<QStringList> ret;
    return ret;
}

int AthleteDB::connect(QString name) {
    if (db.isOpen())
        db.close();
    if (!name.isEmpty())
        databaseName = name;
    db.setDatabaseName(databaseName);
    if (!db.open()) {
        qDebug() << "[AthleteDB] " << "Cannot open db: " << databaseName << " with error " << db.lastError().text();
        return -1;
    }
    return 0;
}

void AthleteDB::saveSettings(QSettings *athleteInfo) {
    athleteInfo->beginGroup("athleteInfo");
    athleteInfo->setValue("bornDay", athleteInfo->value("bornDay", "Unknown").toString());
    athleteInfo->setValue("weight", athleteInfo->value("weight", "Unknown").toString());
    athleteInfo->setValue("height", athleteInfo->value("height", "Unknown").toString());
    athleteInfo->setValue("id", athleteInfo->value("id", "Unknown").toString());
    athleteInfo->setValue("sex", athleteInfo->value("sex", "Unknown").toString());
    athleteInfo->setValue("lastUpdate", athleteInfo->value("lastUpdate", "-1").toInt());
    athleteInfo->endGroup();
}

int AthleteDB::updateAthleteInfo(QString athleteName, QString athleteDir) {
    if (!db.isOpen())
        return -1;
    // Default settings
    qDebug() << "[AthleteDB] " << "athleteName " << athleteName;
    QSettings athleteInfo(athleteDir + "/data.ini", QSettings::IniFormat);
    athleteInfo.beginGroup("athleteInfo");
    QDateTime athleteBornDateTime;

    if (athleteInfo.value("bornDay", "Unknown") != "Unknown") {
        QStringList date_mask = athleteInfo.value("bornDay", "Unknown").toString().split(" ");
        if (date_mask.length() <= 2 && date_mask.at(0) != "Unknown") {
            QStringList date = date_mask.at(0).split(".");
            QString maskTmp;
            if (date_mask.length() > 1)
                maskTmp = date_mask.at(1);
            else
                maskTmp = "d.m.y";

            QStringList mask = maskTmp.split(".");
            if (mask.length() != date.length()) {
                qDebug() << "[AthleteDB] " << "Unknown format date " << date_mask.at(0) << " or mask " << maskTmp;
            } else {
                QMap<QString, int> dataMap;
                for (auto i(0); i < mask.length(); i++)
                    dataMap.insert(mask.at(i), date.at(i).toInt());
                athleteBornDateTime.setDate(QDate(dataMap["y"], dataMap["m"], dataMap["d"]));
            }
        }
    }


    qDebug() << "[AthleteDB] " << athleteBornDateTime.toMSecsSinceEpoch();
    athleteInfo.endGroup();
    saveSettings(&athleteInfo);
}

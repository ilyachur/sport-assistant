#include "athletedb.h"

#include <QMap>
#include <QFile>
#include <QDebug>
#include <QDateTime>
#include <QSettings>
#include <QFileInfo>
#include <QStringList>
#include <QtSql/QSqlError>
#include <QtSql/QSqlResult>

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
    athleteInfo->setValue("weight", athleteInfo->value("weight", "-1").toInt());
    athleteInfo->setValue("height", athleteInfo->value("height", "-1").toInt());
    athleteInfo->setValue("id", athleteInfo->value("id", "-1").toInt());
    athleteInfo->setValue("sex", athleteInfo->value("sex", "Unknown").toString());
    athleteInfo->setValue("lastUpdate", athleteInfo->value("lastUpdate", "0").toULongLong());
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

    db.exec("create table if not exists athlete (ID integer PRIMARY KEY, name string, sex string, bornDay integer, weight integer, height integer)");
    db.commit();

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

    if (QFileInfo(athleteDir).lastModified().toMSecsSinceEpoch() < athleteInfo.value("lastUpdate", "-1").toULongLong() &&
             QFileInfo(athleteDir + "/data.ini").lastModified().toMSecsSinceEpoch() < athleteInfo.value("lastUpdate", "-1").toULongLong()) {
        if (db.exec("SELECT * FROM athlete WHERE ID = " + athleteInfo.value("id", "-1").toInt()).next())
            return 0;
    }
    if (!db.exec("SELECT * FROM athlete WHERE ID = " + QString::number(athleteInfo.value("id", "-1").toInt())).next()) {

        db.exec("INSERT INTO athlete (name, sex, bornDay, weight, height) VALUES (\"" + athleteName +
                "\", \"" + athleteInfo.value("sex", "Unknown").toString() + "\", \"" + QString::number(athleteBornDateTime.toMSecsSinceEpoch()) +
                "\", \"" + QString::number(athleteInfo.value("weight", "-1").toInt()) + "\", \"" +
                QString::number(athleteInfo.value("height", "-1").toInt()) + "\")");
        db.commit();
        qDebug() << db.lastError().text();
        QString command = "SELECT ID FROM athlete WHERE name = \"" + athleteName +
                    "\" and sex = \"" + athleteInfo.value("sex", "Unknown").toString() +
                    "\" and bornDay = " + QString::number(athleteBornDateTime.toMSecsSinceEpoch()) +
                    " and weight = " + QString::number(athleteInfo.value("weight", "-1").toInt()) +
                    " and height = " + QString::number(athleteInfo.value("height", "-1").toInt());
        QSqlQuery athleteInfoQuery(db);
        athleteInfoQuery.next();
        athleteInfo.setValue("id", athleteInfoQuery.value("id").toInt());
    } else {
        db.exec("UPDATE athlete SET name = \"" + athleteName + "\" WHERE ID = " + QString::number(athleteInfo.value("id", "-1").toInt()));
        db.exec("UPDATE athlete SET sex = \"" + athleteInfo.value("sex", "Unknown").toString() + "\" WHERE ID = " + QString::number(athleteInfo.value("id", "-1").toInt()));
        db.exec("UPDATE athlete SET bornDay = " + QString::number(athleteBornDateTime.toMSecsSinceEpoch()) + " WHERE ID = " + QString::number(athleteInfo.value("id", "-1").toInt()));
        db.exec("UPDATE athlete SET weight = " + QString::number(athleteInfo.value("weight", "-1").toInt()) + " WHERE ID = " + QString::number(athleteInfo.value("id", "-1").toInt()));
        db.exec("UPDATE athlete SET height = " + QString::number(athleteInfo.value("height", "-1").toInt()) + " WHERE ID = " + QString::number(athleteInfo.value("id", "-1").toInt()));

        db.commit();
    }
    athleteInfo.setValue("lastUpdate", QDateTime::currentMSecsSinceEpoch());
    athleteInfo.endGroup();
    saveSettings(&athleteInfo);
}

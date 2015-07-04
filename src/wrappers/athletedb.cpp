#include "athletedb.h"

#include <QMap>
#include <QDir>
#include <QFile>
#include <QDebug>
#include <QDateTime>
#include <QSettings>
#include <QFileInfo>
#include <QStringList>
#include <QtSql/QSqlError>
#include <QtSql/QSqlResult>

#include "../parsers/cleverparser.h"

AthleteDB::AthleteDB(QString name): databaseName(name)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
}

QVector<QStringList> AthleteDB::findAthlete(QMap<QString, QString> findMap) {
    connect();
    QVector<QStringList> ret;
    QString command = "SELECT * FROM athlete";
    if (findMap.size() > 0) {
        command += " WHERE ";
    }
    QStringList parameters;
    for (QString key : findMap.keys()) {
        parameters.append(key + " = \"" + findMap[key] + "\"");
    }
    if (parameters.size() > 0)
        command += parameters.join(" and ");
    qDebug() << command;
    QSqlQuery allReturn = db.exec(command);
    while (allReturn.next()) {
        QStringList needAdd;
        needAdd.append(QString::number(allReturn.value("id").toInt()));
        needAdd.append(allReturn.value("name").toString());
        needAdd.append(allReturn.value("sex").toString());
        needAdd.append(QString::number(allReturn.value("bornDay").toULongLong()));
        needAdd.append(QString::number(allReturn.value("weight").toInt()));
        needAdd.append(QString::number(allReturn.value("height").toInt()));
        ret.push_back(needAdd);
    }
    return ret;
}

void AthleteDB::disconnect() {
    if (db.isOpen()){
        db.commit();
        db.close();
    }
}

int AthleteDB::connect(QString name) {
    disconnect();
    if (!name.isEmpty())
        databaseName = name;
    db = QSqlDatabase::addDatabase("QSQLITE");
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
    athleteInfo->setValue("lastUpdate", QDateTime::currentMSecsSinceEpoch());
    athleteInfo->endGroup();
}


int AthleteDB::updateAthleteInfo(QString athleteName, QString athleteDir) {
    connect();
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
        athleteInfoQuery.exec(command);
        if (athleteInfoQuery.next())
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

    db.exec("create table if not exists training (ID integer PRIMARY KEY, athlete_id integer, date string, filetype string, FOREIGN KEY(athlete_id) REFERENCES athlete(ID)))");
    db.commit();

    db.exec("create table if not exists activities (ID integer PRIMARY KEY, training_id integer, activity integer, data string, FOREIGN KEY(training_id) REFERENCES training(ID)))");
    db.commit();

    QMap <long long, QString> timeLine;
    QStringList files = QDir(athleteDir).entryList(QDir::Dirs);

    for (QString activityDir: files) {
        if (activityDir == "." || activityDir == "..")
            continue;
        QString activityPath = athleteDir + "/" + activityDir;
        if (!QDir(activityPath).exists())
            continue;

        QStringList listTrainings = QDir(activityPath).entryList(QDir::Files);
        for (QString training : listTrainings) {
            CleverParser clParser(activityPath + "/" + training);
            int retRun = clParser.run();
            if (retRun != PARSER_OK) {
                qDebug() << "Parser error code: " << retRun;
            }
        }
    }

    saveSettings(&athleteInfo);
}

#include "athletedb.h"

/// @file athletedb.cpp
/// @brief Contains class realisation for work with data base
/// @author Ilya Churaev ilyachur@gmail.com

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
    /// Set db type
    db = QSqlDatabase::addDatabase("QSQLITE");
}

QVector<QStringList> AthleteDB::findAthlete(QMap<QString, QString> findMap) {
    /// Connect to db
    connect();
    QVector<QStringList> ret;
    /// Generate command
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

    /// Get athlete info
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

QVector<QStringList> AthleteDB::findTraining(QMap<QString, QString> findMap) {
    /// Connect to db
    connect();
    QVector<QStringList> ret;
    /// Generate command
    QString command = "SELECT * FROM training";
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
    qDebug() << db.lastError().text();
    while (allReturn.next()) {
        QStringList needAdd;
        needAdd.append(QString::number(allReturn.value("ID").toInt()));
        needAdd.append(QString::number(allReturn.value("athlete_id").toInt()));
        needAdd.append(QString::number(allReturn.value("date").toULongLong()));
        needAdd.append(allReturn.value("filetype").toString());
        ret.push_back(needAdd);
    }
    return ret;
}

QVector<QStringList> AthleteDB::findActivity(QMap<QString, QString> findMap) {
    /// Connect to db
    connect();
    QVector<QStringList> ret;
    /// Generate command
    QString command = "SELECT * FROM activities";
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
    qDebug() << db.lastError().text();
    while (allReturn.next()) {
        QStringList needAdd;
        needAdd.append(QString::number(allReturn.value("ID").toInt()));
        needAdd.append(QString::number(allReturn.value("training_id").toInt()));
        needAdd.append(QString::number(allReturn.value("date").toULongLong()));
        needAdd.append(allReturn.value("activity").toString());
        needAdd.append(allReturn.value("data").toString());
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

    /// Open athlete info
    qDebug() << "[AthleteDB] " << "athleteName " << athleteName;
    QSettings athleteInfo(athleteDir + "/data.ini", QSettings::IniFormat);
    athleteInfo.beginGroup("athleteInfo");
    QDateTime athleteBornDateTime;

    /// Create table with athletes
    db.exec("create table if not exists athlete (ID integer PRIMARY KEY, name string, sex string, bornDay integer, weight integer, height integer)");
    db.commit();

    /// Generate born day
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
    /// Check modification data
    if (QFileInfo(athleteDir).lastModified().toMSecsSinceEpoch() < athleteInfo.value("lastUpdate", "-1").toLongLong() &&
             QFileInfo(athleteDir + "/data.ini").lastModified().toMSecsSinceEpoch() < athleteInfo.value("lastUpdate", "-1").toLongLong()) {
        if (db.exec("SELECT * FROM athlete WHERE ID = " + athleteInfo.value("id", "-1").toInt()).next())
            return 0;
    }


    if (!db.exec("SELECT * FROM athlete WHERE ID = " + QString::number(athleteInfo.value("id", "-1").toInt())).next()) {
        /// Create new athlete
        db.exec("INSERT INTO athlete (name, sex, bornDay, weight, height) VALUES (\"" + athleteName +
                "\", \"" + athleteInfo.value("sex", "Unknown").toString() + "\", \"" + QString::number(athleteBornDateTime.toMSecsSinceEpoch()) +
                "\", \"" + QString::number(athleteInfo.value("weight", "-1").toInt()) + "\", \"" +
                QString::number(athleteInfo.value("height", "-1").toInt()) + "\")");
        db.commit();

        /// Get athlete id
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
        /// Update athlete info
        db.exec("UPDATE athlete SET name = \"" + athleteName + "\" WHERE ID = " + QString::number(athleteInfo.value("id", "-1").toInt()));
        db.exec("UPDATE athlete SET sex = \"" + athleteInfo.value("sex", "Unknown").toString() + "\" WHERE ID = " + QString::number(athleteInfo.value("id", "-1").toInt()));
        db.exec("UPDATE athlete SET bornDay = " + QString::number(athleteBornDateTime.toMSecsSinceEpoch()) + " WHERE ID = " + QString::number(athleteInfo.value("id", "-1").toInt()));
        db.exec("UPDATE athlete SET weight = " + QString::number(athleteInfo.value("weight", "-1").toInt()) + " WHERE ID = " + QString::number(athleteInfo.value("id", "-1").toInt()));
        db.exec("UPDATE athlete SET height = " + QString::number(athleteInfo.value("height", "-1").toInt()) + " WHERE ID = " + QString::number(athleteInfo.value("id", "-1").toInt()));

        db.commit();
    }

    /// Create training table
    db.exec("create table if not exists training (ID integer PRIMARY KEY, athlete_id integer, date integer, filetype string, FOREIGN KEY(athlete_id) REFERENCES athlete(ID))");
    db.commit();

    /// Create activities table
    db.exec("create table if not exists activities (ID integer PRIMARY KEY, training_id integer, date integer, activity string, data string, FOREIGN KEY(training_id) REFERENCES training(ID))");
    db.commit();

    /// Get activities list
    QStringList files = QDir(athleteDir).entryList(QDir::Dirs);
    for (QString activityDir: files) {
        if (activityDir == "." || activityDir == "..")
            continue;
        QString activityPath = athleteDir + "/" + activityDir;
        if (!QDir(activityPath).exists())
            continue;

        QStringList listTrainings = QDir(activityPath).entryList(QDir::Files);
        //TODO: Parallel for for it
        /// Get trainings
        for (QString training : listTrainings) {
            if (athleteInfo.value("lastUpdate", "-1").toLongLong() > QFileInfo(databaseName).created().toMSecsSinceEpoch() &&
                    QFileInfo(activityPath + "/" + training).lastModified().toMSecsSinceEpoch() < athleteInfo.value("lastUpdate", "-1").toLongLong())
                continue;
            CleverParser clParser(activityPath + "/" + training);
            int retRun = clParser.run();
            if (retRun != PARSER_OK) {
                qDebug() << "Parser error code: " << retRun;
            }

            QMap<QString, QMap<QString, QString>> *parserInfo = clParser.getInfo();
            if (parserInfo == nullptr || (*parserInfo)["HrvMesg"].isEmpty()) {
                qDebug() << "Error: parserInfo == null or HrvMesg.isEmpty()";
                continue;
            }
            /// Get training map and get start time
            QMap<QString, QString> trainingMap = (*parserInfo)["HrvMesg"];
            unsigned long long start_time_long = (*parserInfo)["Times"]["StartTime"].toULongLong();
            if (!db.exec("SELECT * FROM training WHERE date = " +
                        QString::number(start_time_long) + " and athlete_id = " +
                        QString::number(athleteInfo.value("id", "-1").toInt()) +
                        " and filetype = \"" + clParser.fileType() + "\"").next()) {
                /// Add training and activities
                db.exec("INSERT INTO training (athlete_id, date, filetype) VALUES(" +
                            QString::number(athleteInfo.value("id", "-1").toInt()) + ", " +
                            QString::number(start_time_long) + ", \"" + clParser.fileType() + "\")");
                db.commit();

                /// Get training id
                QString command = "SELECT ID FROM training WHERE date = " +
                        QString::number(start_time_long) + " and athlete_id = " +
                        QString::number(athleteInfo.value("id", "-1").toInt()) +
                        " and filetype = \"" + clParser.fileType() + "\"";
                QSqlQuery athleteInfoQuery(db);
                athleteInfoQuery.exec(command);
                int training_id = -1;
                if (athleteInfoQuery.next())
                    training_id = athleteInfoQuery.value("id").toInt();

                if (training_id < 1) {
                    qDebug() << "Error: training_id < 1";
                    continue;
                }

                /// Add activity
                db.exec("INSERT INTO activities (activity, training_id, data, date) VALUES(\"" +
                            activityDir + "\", " + QString::number(training_id) + ", \"" +
                        dumpQMap2QString(trainingMap) + "\", " + QString::number(start_time_long) + ")");
                db.commit();
            }
        }
    }

    athleteInfo.endGroup();
    saveSettings(&athleteInfo);
    return 0;
}

QVector<QStringList> AthleteDB::getActivityTypes() {
    QVector<QStringList> ret;

    connect();
    db.exec("create table if not exists activityTypes (id integer PRIMARY KEY, activityType string, paramsList string)");
    db.commit();

    QSqlQuery allReturn = db.exec("SELECT activityType, paramsList FROM activityTypes");
    while (allReturn.next()) {
        QStringList needAdd;
        needAdd.append(allReturn.value("activityType").toString());
        needAdd.append(allReturn.value("paramsList").toString());
        ret.push_back(needAdd);
    }

    return ret;
}

QStringList AthleteDB::getTablesList() {
    QStringList returnList;

    connect();

    QSqlQuery allReturn = db.exec("SELECT name FROM sqlite_master WHERE type='table'");
    while (allReturn.next()) {
        returnList.append(allReturn.value("name").toString());
    }
    return returnList;
}

QVector<QSqlQuery> AthleteDB::execCommands(const QStringList commands, bool needCommit, bool* commitOk) {
    connect();
    QVector<QSqlQuery> returnVector;
    for(QString command : commands)
        returnVector.append(db.exec(command));

    /*for(auto i(0); i < returnVector.size(); i++) {
        qDebug() << commands.at(i) << " : " << returnVector.at(i).lastError().text();
    }*/

    if (needCommit) {
        bool ok = db.commit();
        if (commitOk != nullptr)
            *commitOk = ok;
    }
    return returnVector;
}

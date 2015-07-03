#include "athletedb.h"
#include <QDebug>
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
        qDebug() << "Cannot open db: " << databaseName << " with error " << db.lastError().text();
        return -1;
    }
    return 0;
}

int AthleteDB::updateAthleteInfo(QString athleteName, QString athleteDir) {
    if (!db.isOpen())
        return -1;
}

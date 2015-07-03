#ifndef ATHLETEDB_H
#define ATHLETEDB_H

#include <QtSql/QSqlDatabase>
#include <QStringList>
#include <QSettings>
#include <QVector>
#include <QString>

class AthleteDB
{
public:
    AthleteDB(QString name = "");

    QVector<QStringList> findAthletes();

    int connect(QString name = "");
    inline void disconnect() {
        if (db.isOpen())
            db.close();
    }

    int updateAthleteInfo(QString athleteName, QString athleteDir);

private:
    QString databaseName;
    QSqlDatabase db;

    void saveSettings(QSettings *athleteInfo);
};

#endif // ATHLETEDB_H

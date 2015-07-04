#ifndef ATHLETEDB_H
#define ATHLETEDB_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
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

    inline QSqlQuery exec(QString command) {
        return db.exec(command);
    }

    inline bool commit() {
        return db.commit();
    }

    int updateAthleteInfo(QString athleteName, QString athleteDir);

private:
    QString databaseName;
    QSqlDatabase db;

    void saveSettings(QSettings *athleteInfo);
};

#endif // ATHLETEDB_H

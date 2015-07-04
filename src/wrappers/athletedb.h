#ifndef ATHLETEDB_H
#define ATHLETEDB_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QStringList>
#include <QSettings>
#include <QVector>
#include <QString>
#include <QMap>

class AthleteDB
{
public:
    AthleteDB(QString name = "");

    QVector<QStringList> findAthlete(QMap<QString, QString> findMap = QMap<QString, QString>());

    inline void setNameDB(const QString name) {
        databaseName = name;
    }

    inline QSqlQuery exec(const QString command) {
        connect();
        return db.exec(command);
    }

    inline bool commit() {
        connect();
        return db.commit();
    }

    int updateAthleteInfo(QString athleteName, QString athleteDir);

private:
    QString databaseName;
    QSqlDatabase db;

    void saveSettings(QSettings *athleteInfo);

    int connect(QString name = "");
    void disconnect();
};

#endif // ATHLETEDB_H

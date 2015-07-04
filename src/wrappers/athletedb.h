#ifndef ATHLETEDB_H
#define ATHLETEDB_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QStringList>
#include <QSettings>
#include <QVector>
#include <QString>
#include <QMap>

/**
 * @brief The AthleteDB class: The main class for working with DataBase
 */
class AthleteDB
{
public:
    /**
     * @brief Default constructor
     * @param name of data base (default = "")
     */
    AthleteDB(QString name = "");

    /**
     * @brief findAthlete - need for finding athletes
     * @param findMap - Map with information about athlete (default is empty)
     * @return vector with athletes information [id, name, sex, bornDay, weight, height]
     */
    QVector<QStringList> findAthlete(QMap<QString, QString> findMap = QMap<QString, QString>());

    /**
     * @brief Setter for DataBase name
     * @param The name of data base
     */
    inline void setNameDB(const QString name) {
        databaseName = name;
    }

    /**
     * @brief exec function
     * @param command for execution
     * @return QSqlQuery
     */
    inline QSqlQuery exec(const QString command) {
        connect();
        return db.exec(command);
    }

    /**
     * @brief commit function
     * @return true if all good else false
     */
    inline bool commit() {
        connect();
        return db.commit();
    }

    /**
     * @brief updateAthleteInfo - function for updating athlete information
     * @param athleteName - the name of athlete
     * @param athleteDir - path to directory with user information
     * @return 0 or error code
     */
    int updateAthleteInfo(QString athleteName, QString athleteDir);

private:
    /**
     * @brief databaseName - data base name
     */
    QString databaseName;
    /**
     * @brief db object
     */
    QSqlDatabase db;

    /**
     * @brief Save athlete information
     * @param athleteInfo - pointer on settings
     */
    void saveSettings(QSettings *athleteInfo);

    /**
     * @brief dumpQMap2QString for saving training to db
     * @param dumpedMap - training info
     * @return string with dump
     */
    QString dumpQMap2QString(const QMap<QString, QString> dumpedMap) {
        QString retString;
        QStringList keyValueList;
        for (auto &key : dumpedMap.keys()) {
            keyValueList.append(key + ":" + dumpedMap[key]);
        }
        retString = keyValueList.join(",");
        return retString;
    }

    /**
     * @brief dumpQString2QMap for restore training data from db
     * @param dumpedString - string from data base
     * @return Map with training information
     */
    QMap<QString, QString> dumpQString2QMap(const QString dumpedString) {
        QMap<QString, QString> retMap;
        QStringList keyValueList = dumpedString.split(",");
        for (auto &keyValue : keyValueList) {
            QStringList parts = keyValue.split(":");
            retMap.insert(parts.at(0), parts.at(1));
        }
        return retMap;
    }

    /**
     * @brief connect to db
     * @param db name
     * @return 0 or error code
     */
    int connect(QString name = "");
    /**
     * @brief db disconnect
     */
    void disconnect();
};

#endif // ATHLETEDB_H

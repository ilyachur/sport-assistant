#ifndef TIMEANALYSIS_H
#define TIMEANALYSIS_H

/// @file timeanalysis.h
/// @brief Contains class for time analysis
/// @author Ilya Churaev ilyachur@gmail.com

#include <QMap>
#include <QObject>
#include <QString>
#include <QDateTime>

/**
 *  @namespace Analysis
 *  @brief The Analysis namespace contains all functions for analysis
 */
namespace Analysis {

class TimeAnalysis: public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Default constructor
     */
    TimeAnalysis();

    /**
     * @brief Constructor for TimeAnalysis class
     * @param _training - source training data
     * @param _athleteName - the name of athlete
     * @param _date - training date
     * @param _activityName - the name of training activity
     * @param _showImages - show images (default true)
     * @param _saveImages - save images (default false)
     */
    TimeAnalysis(QMap<unsigned long long, double> _training, QString _athleteName = QString(),
           QDateTime _date = QDateTime(), QString _activityName = QString(),
           bool _showImages = false, bool _saveImages = false);

    /**
     * @brief setter for training data
     * @param training data
     */
    inline void setTrainingData(const QMap<unsigned long long, double> training) {
        this->training = training;
    }

    /**
     * @brief seter for athlete name
     * @param athlete name
     */
    inline void setAthleteName(const QString name) {
        athleteName = name;
    }

    /**
     * @brief Setter for training date
     * @param training date
     */
    inline void setDate(const QDateTime date) {
        this->date = date;
    }

    /**
     * @brief Setter for activity name
     * @param activity name
     */
    inline void setActivityName(const QString name) {
        activityName = name;
    }

    /**
     * @brief Flag setter for saving images
     * @param save
     */
    inline void needSaveImages(const bool save) {
        saveImages = save;
    }

    /**
     * @brief Flag setter for showing images
     * @param save
     */
    inline void needShowImages(const bool show) {
        showImages = show;
    }

    QMap<unsigned long long, double> simpleTimeAnalysis();
private:
    QMap<unsigned long long, double> training;
    QString athleteName, activityName;
    QDateTime date;
    bool showImages, saveImages;

    int getTrainingLoadValue(double middleHb);

signals:
    void notifyProgress(int value);
    void notifyProgressRange(int from, int to);
    void buildGrapf(QString, QMap<QString, QVector<double>>*);
};

}

#endif // TIMEANALYSIS_H

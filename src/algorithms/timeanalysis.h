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
    TimeAnalysis();
    TimeAnalysis(QMap<unsigned long long, double> _training, QString _athleteName = QString(),
           QDateTime _date = QDateTime(), QString _activityName = QString(),
           bool _showImages = false, bool _saveImages = false);
private:
    QMap<unsigned long long, double> training;
    QString athleteName, activityName;
    QDateTime date;
    bool showImages, saveImages;

signals:
    void notifyProgress(int value);
    void notifyProgressRange(int from, int to);
    void buildGrapf(QString, QMap<QString, QVector<double>>*);
};

}

#endif // TIMEANALYSIS_H

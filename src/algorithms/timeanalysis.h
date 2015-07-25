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
     */
    TimeAnalysis(QMap<unsigned long long, double> _training);

    /**
     * @brief setter for training data
     * @param training data
     */
    inline void setTrainingData(const QMap<unsigned long long, double> training) {
        this->training = training;
    }

    QMap<unsigned long long, double> simpleTimeAnalysis();

private:
    QMap<unsigned long long, double> training;

    int getTrainingLoadValue(double middleHb);

signals:
    void notifyProgress(int value);
    void notifyProgressRange(int from, int to);
    void buildGraph(QString name, QString imageName, QMap<QString, QVector<double>> *data, bool showGraph);
};

}

#endif // TIMEANALYSIS_H

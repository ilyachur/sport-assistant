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

    /**
     * @brief simpleTimeAnalysis - main function for time analysis
     */
    void simpleTimeAnalysis();

private:
    QMap<unsigned long long, double> training;

    int getTrainingLoadValue(double middleHb);

signals:
    /**
     * @brief Signal for changing progress bar value
     * @param value - current value
     */
    void notifyProgress(int value);

    /**
     * @brief Signal for setting progress bar range
     * @param from - start value
     * @param to - end value
     */
    void notifyProgressRange(int from, int to);

    /**
     * @brief Signal for creating graph by output data
     * @param name of function
     * @param name for saving image
     * @param data map
     * @param flag for showing graph
     */
    void buildGraph(QString name, QString imageName, QMap<QString, QVector<double>> *data, bool showGraph);
};

}

#endif // TIMEANALYSIS_H

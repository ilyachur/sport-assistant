#ifndef FILTER_H
#define FILTER_H

/// @file filter.h
/// @brief Contains class for filtering raw data
/// @author Ilya Churaev ilyachur@gmail.com

#include <QMap>
#include <QList>
#include <QVector>
#include <QObject>
#include <QString>
#include <QDateTime>

/**
 *  @namespace Analysis
 *  @brief The Analysis namespace contains all functions for analysis
 */
namespace Analysis {

/**
 * @brief The Filter class: for filtered raw data and remove noises from it
 */
class Filter: public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Default constructor
     */
    Filter();
    /**
     * @brief Constructor for Filter class
     * @param _training - source training data
     */
    Filter(QMap<unsigned long long, double> _training);

    /**
     * @brief setter for training data
     * @param training data
     */
    inline void setTrainingData(const QMap<unsigned long long, double> training) {
        this->training = training;
    }

    /**
     * @brief simpleFilter for barrieren filter
     * @return filtered data
     */
    QMap<unsigned long long, double> simpleFilter();

    /**
     * @brief medianFilter - 1D MEDIAN FILTER wrapper
     * @param signal - input signal
     * @param result - output signal
     * @param N - length of the signal
     */
    // link http://www.librow.com/articles/article-1/appendix-a-2
    template <class T> void medianFilter(T *signal, T *result, int N);

    /**
     * @brief medianFilter - 2D MEDIAN FILTER wrapper
     * @param signal - input signal
     * @param result - output signal
     * @param N - width of the image
     * @param M -- height of the image
     */
    template <class T> void medianFilter(T* image, T* result, int N, int M);

private:
    QMap<unsigned long long, double> training;

    /**
     * @brief _medianFilter - 1D MEDIAN FILTER implementation
     * @param signal - input signal
     * @param result - output signal
     * @param N - length of the signal
     */
    template <class T> void _medianFilter(const T* signal, T* result, int N);

    /**
     * @brief medianFilter - 2D MEDIAN FILTER implementation
     * @param signal - input signal
     * @param result - output signal
     * @param N - width of the image
     * @param M -- height of the image
     */
    template <class T> void _medianFilter(const T* image, T* result, int N, int M);

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

#endif // FILTER_H

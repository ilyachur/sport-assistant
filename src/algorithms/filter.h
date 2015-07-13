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

#include "../visualization/visualization.h"

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
     * @param _athleteName - the name of athlete
     * @param _date - training date
     * @param _activityName - the name of training activity
     * @param _showImages - show images (default true)
     * @param _saveImages - save images (default false)
     */
    Filter(QMap<unsigned long long, double> _training, QString _athleteName = QString(),
           QDateTime _date = QDateTime(), QString _activityName = QString(),
           bool _showImages = true, bool _saveImages = false);

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
    QString athleteName, activityName;
    QDateTime date;
    bool showImages, saveImages;

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
     * @param data map
     */
    void buildGrapf(QString, QMap<QString, QVector<double>>*);
};

}

#endif // FILTER_H

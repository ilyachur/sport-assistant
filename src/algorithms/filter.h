#ifndef FILTER_H
#define FILTER_H

#include <QMap>
#include <QList>
#include <QVector>
#include <QObject>
#include <QString>
#include <QDateTime>

#include "../visualization/visualization.h"

namespace Analyse {

class Filter: public QObject
{
    Q_OBJECT
public:
    Filter();
    Filter(QMap<unsigned long long, double> _training, QString _athleteName = QString(),
           QDateTime _date = QDateTime(), QString _activityName = QString(),
           bool _showImages = false, bool _saveImages = false);

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

    QMap<QString, void (*)(QMap<QString, QVector<double>>)> mapTest;


signals:
    void notifyProgress(int value);
    void notifyProgressRange(int from, int to);
    void buildGrapf(QString, QMap<QString, QVector<double>>*);
};

}

#endif // FILTER_H

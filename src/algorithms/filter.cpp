#include "filter.h"

#include <QList>
#include "math.h"
#include "analyse.h"

Analyse::Filter::Filter()
{

}

Analyse::Filter::Filter(QMap<unsigned long long, double> _training, QString _athleteName,
       QDateTime _date, QString _activityName,
       bool _showImages, bool _saveImages): QObject(), training(_training),
    athleteName(_athleteName), date(_date), activityName(_activityName),
    showImages(_showImages), saveImages(_saveImages)
{

}

QMap<unsigned long long, double> Analyse::Filter::simpleFilter() {
    QMap<unsigned long long, double> trainingFiltered;

    double dMax = 0.3;

    QList<unsigned long long> timeLine = training.keys();

    qSort(timeLine);

    QList<double> rrIntervals = getTrainingSignal(training, timeLine);
    QList<double> rrIntervalsTemp = rrIntervals;

    double avrRR = 0;
    for (double value : rrIntervals)
        avrRR += value;
    avrRR /= rrIntervals.length();

    emit notifyProgressRange(0, rrIntervals.length());

    int windowSize = 2;
    for(auto i(0); i < rrIntervals.length() - 1; i++) {
        if (abs(rrIntervals.at(i + 1) - rrIntervals.at(i) / avrRR) > dMax) {

        }
        emit notifyProgress(i);
        trainingFiltered.insert(timeLine.at(i), rrIntervals.at(i));
    }

    return trainingFiltered;
}

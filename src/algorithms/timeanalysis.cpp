#include "timeanalysis.h"
#include "analyse.h"

#include <QVector>
#include <QPoint>

/// @file timeanalysis.cpp
/// @brief Contains class realisation for time analysis
/// @author Ilya Churaev ilyachur@gmail.com

Analysis::TimeAnalysis::TimeAnalysis() {}

Analysis::TimeAnalysis::TimeAnalysis(QMap<unsigned long long, double> _training, QString _athleteName,
       QDateTime _date, QString _activityName,
       bool _showImages, bool _saveImages): QObject(), training(_training),
    athleteName(_athleteName), date(_date), activityName(_activityName),
    showImages(_showImages), saveImages(_saveImages) {}

QMap<unsigned long long, double> Analysis::TimeAnalysis::simpleTimeAnalysis() {
    QMap<unsigned long long, double> timeResult;

    QVector<unsigned long long> timeLineLong;
    for (auto key : training.keys()) {
        timeLineLong.append(key);
    }
    qSort(timeLineLong);

    int secChangeStep = 60;
    secChangeStep *= 1000;

    emit notifyProgressRange(0, timeLineLong.at(timeLineLong.length() - 1) + 1);

    int lastStartPoint = 0;
    int lastEndPoint = 0;

    unsigned long long startTime = timeLineLong.at(0);
    unsigned long long finishTime = timeLineLong.at(timeLineLong.length() - 1) - startTime;

    QVector<double> tirednessValue;
    QVector<double> tirednessLine;
    double previousValue = 0;

    for(auto i(0); i < timeLineLong.at(timeLineLong.length() - 1) + 1; i++) {
        int startPoint =  findStartPoint(timeLineLong, i * secChangeStep, lastStartPoint);
        lastStartPoint = startPoint;
        int endPoint = findStartPoint(timeLineLong, (i + 1) * secChangeStep, lastStartPoint);
        lastEndPoint = endPoint;
        QVector<unsigned long long> timeRange;
        for (auto j(startPoint); j < endPoint; j++)
            timeRange.append(timeLineLong.at(j));
        QVector<double> trainingHrv = getTrainingSignal(training, timeRange);
        QVector<int> trainingHb;
        double middleHb = 0;
        for(auto j : trainingHrv) {
            int hb = hrv2hb(j);
            trainingHb.append(hb);
            middleHb += hb;
        }
        if (trainingHb.length() > 0)
            middleHb /= (double)trainingHb.length();

        double value = previousValue;
        int effective = getTrainingLoadValue(middleHb);
        switch(effective) {
        case 0:
            value -= (double)((secChangeStep / 10) / (60 * 60));
            break;
        case 1:
            value += (double)((secChangeStep / 10) / (80 * 60));
            break;
        case 2:
            value += (double)((secChangeStep / 10) / (60 * 60));
            break;
        case 3:
            value += (double)((secChangeStep / 10) / (40 * 60));
            break;
        case 4:
            value += (double)((secChangeStep / 10) / (10 * 60));
            break;
        case 5:
            value += (double)((secChangeStep / 10) / (5 * 60));
            break;
        }

        if (value < 0)
            value = 0;
        previousValue = value;
        tirednessValue.append(value);
        tirednessLine.append((double)((timeLineLong.at(endPoint) - startTime) * 100 / finishTime));
        emit notifyProgress(i);
    }

    QMap<QString, QVector<double>> *data = new QMap<QString, QVector<double>>;
    QVector<double> hbValues;
    QVector<double> hbLine;
    for (auto i(0); i < timeLineLong.length(); i++) {
        hbLine.append((double)(((timeLineLong.at(i) - startTime) * 100) / finishTime));
        hbValues.append((double)hrv2hb(training[timeLineLong.at(i)]));
    }

    data->insert("hbTime", hbValues);
    data->insert("hbData", hbValues);
    data->insert("tirednessData", tirednessValue);
    data->insert("tirednessTime", tirednessLine);
    emit buildGrapf("showSimpleTimeAnalysis", data);

    return timeResult;
}

int Analysis::TimeAnalysis::getTrainingLoadValue(double middleHb) {
    return 0;
}

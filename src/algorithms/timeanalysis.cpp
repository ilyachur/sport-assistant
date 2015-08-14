#include "timeanalysis.h"
#include "analyse.h"

#include <QVector>
#include <QPoint>

/// @file timeanalysis.cpp
/// @brief Contains class realisation for time analysis
/// @author Ilya Churaev ilyachur@gmail.com

Analysis::TimeAnalysis::TimeAnalysis() {}

Analysis::TimeAnalysis::TimeAnalysis(QMap<unsigned long long, double> _training): training(_training) {}

void Analysis::TimeAnalysis::simpleTimeAnalysis() {
    QVector<unsigned long long> timeLineLong;
    for (auto key : training.keys()) {
        timeLineLong.append(key);
    }
    qSort(timeLineLong);

    unsigned long long startTime = timeLineLong.at(0);
    unsigned long long finishTime = timeLineLong.at(timeLineLong.length() - 1) - startTime;

    int secChangeStep = 60;
    secChangeStep *= 1000;

    int lastStartPoint = 0;
    int lastEndPoint = 0;

    QVector<double> tirednessValue;
    QVector<double> tirednessLine;
    double previousValue = 0;
    int lastValue = (int)((finishTime / secChangeStep) + 1);

    emit notifyProgressRange(0, lastValue);

    for(auto i(0); i < lastValue; i++) {
        int startPoint =  findStartPoint(timeLineLong, startTime + i * secChangeStep, lastStartPoint);
        lastStartPoint = startPoint;
        int endPoint = findStartPoint(timeLineLong, startTime + (i + 1) * secChangeStep, lastEndPoint);
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
            value -= (double)((secChangeStep / 10) / (double)(60 * 60));
            break;
        case 1:
            value += (double)((secChangeStep / 10) / (double)(80 * 60));
            break;
        case 2:
            value += (double)((secChangeStep / 10) / (double)(60 * 60));
            break;
        case 3:
            value += (double)((secChangeStep / 10) / (double)(40 * 60));
            break;
        case 4:
            value += (double)((secChangeStep / 10) / (double)(10 * 60));
            break;
        case 5:
            value += (double)((secChangeStep / 10) / (5 * 60));
            break;
        }

        if (value < 0)
            value = 0;
        previousValue = value;
        tirednessValue.append(value);
        if (!finishTime)
            finishTime = 1;
        tirednessLine.append((double)((timeLineLong.at(endPoint) - startTime) * 100 / finishTime));
        emit notifyProgress(i);
    }

    QMap<QString, QVector<double>> *data = new QMap<QString, QVector<double>>;
    QVector<double> hbValues;
    QVector<double> hbLine;
    for (auto i(0); i < timeLineLong.length(); i++) {
        hbLine.append((double)(((timeLineLong.at(i) - startTime) * 100) / (double)finishTime));
        hbValues.append((double)hrv2hb(training[timeLineLong.at(i)]));
    }

    data->insert("hbTime", hbLine);
    data->insert("hbData", hbValues);
    data->insert("tirednessData", tirednessValue);
    data->insert("tirednessTime", tirednessLine);
    emit buildGraph("showSimpleTimeAnalysis", "timeAnalysis.png", data, true);
}

int Analysis::TimeAnalysis::getTrainingLoadValue(double middleHb) {
    if (middleHb < 104)
        return 0;
    else if (middleHb < 114)
        return 1;
    else if (middleHb < 134)
        return 2;
    else if (middleHb < 152)
        return 3;
    else if (middleHb < 171)
        return 4;
    return 5;
}

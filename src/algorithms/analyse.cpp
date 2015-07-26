#include "analyse.h"
#include <QDebug>

/// @file analyse.cpp
/// @brief Contains realisation of common functions for analysis
/// @author Ilya Churaev ilyachur@gmail.com


QVector<double> Analysis::getTrainingSignal(QMap<unsigned long long, double> trainingMap,
                                QVector<unsigned long long> timeLine) {
    QVector<double> retList;
    for(auto& timeValue : timeLine) {
        retList.append(trainingMap[timeValue]);
    }
    return retList;
}

int Analysis::findStartPoint(QVector<unsigned long long> timeLine, unsigned long long startPoint, int findFrom) {
    int index = -1;

    if (findFrom > timeLine.length())
        return index;

    for(auto i(findFrom); i < timeLine.length(); i++) {
        if (timeLine.at(i) == startPoint) {
            index = i;
            break;
        } else if (timeLine.at(i) > startPoint) {
            index = i;
            break;
        }
    }

    if (index < 0) {
        index = timeLine.length() - 1;
    }
    return index;
}

int Analysis::hrv2hb(double hrv) {
    if (hrv == 0) {
        qDebug() << "Divide by zero!";
        return 0;
    }
    return (int)(60 / hrv);
}

double Analysis::hb2hrv(int hb) {
    if (hb == 0) {
        qDebug() << "Divide by zero!";
        return 0.0;
    }
    return (double)(60 / (double)hb);
}


QVector<double> Analysis::findTrend(QVector<double> sourceLine, int rangeNum) {
    int firstRange = rangeNum / 2;
    int secondRange = rangeNum - firstRange;
    QVector<double> trendRange;
    for(auto i(0); i < sourceLine.size(); i++) {
        int firstPart = firstRange;
        int secondPart = secondRange;
        if (i - firstPart < 0) {
            firstPart = i;
            secondPart = rangeNum - firstPart;
        }
        if (i + secondPart > sourceLine.size() - 1) {
            secondPart = sourceLine.size() - 1 - i;
            firstPart = rangeNum - secondPart;
        }
        if (i - firstPart < 0)
            firstPart = i;
        double middleRange = 0;
        for (auto j(i - firstPart); j < i + secondPart; j++) {
            middleRange += sourceLine.at(j);
        }
        middleRange /= rangeNum + 1;
        trendRange.append(middleRange);
    }
    return trendRange;
}


QVector<int> Analysis::findStressPoints(QVector<double> lf2hf, QVector<double> tp) {
    QVector<int> stressPoints;
    if (lf2hf.size() != tp.size()) {
        qDebug() << "lf2hf.size() != tp.size()";
        return stressPoints;
    }
    return stressPoints;
}

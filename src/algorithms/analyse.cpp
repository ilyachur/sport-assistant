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

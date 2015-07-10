#include "analyse.h"

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

#include "analyse.h"

QVector<double> Analyse::getTrainingSignal(QMap<unsigned long long, double> trainingMap,
                                QVector<unsigned long long> timeLine) {
    QVector<double> retList;
    for(auto& timeValue : timeLine) {
        retList.append(trainingMap[timeValue]);
    }
    return retList;
}

#include "analyse.h"

QList<double> Analyse::getTrainingSignal(QMap<unsigned long long, double> trainingMap,
                                QList<unsigned long long> timeLine) {
    QList<double> retList;
    for(auto& timeValue : timeLine) {
        retList.append(trainingMap[timeValue]);
    }
    return retList;
}

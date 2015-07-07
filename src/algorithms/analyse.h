#ifndef ANALYSE_H
#define ANALYSE_H

#include <QList>
#include "filter.h"

namespace Analyse {

QList<double> getTrainingSignal(QMap<unsigned long long, double> trainingMap,
                                QList<unsigned long long> timeLine);

}

#endif // ALGORITHMS


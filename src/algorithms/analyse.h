#ifndef ANALYSE_H
#define ANALYSE_H

#include <QVector>
#include "filter.h"

namespace Analyse {

QVector<double> getTrainingSignal(QMap<unsigned long long, double> trainingMap,
                                  QVector<unsigned long long> timeLine);

}

#endif // ALGORITHMS


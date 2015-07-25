#ifndef ANALYSE_H
#define ANALYSE_H

/// @file analyse.h
/// @brief Contains common functions for analysis
/// @author Ilya Churaev ilyachur@gmail.com

#include <QVector>
#include "filter.h"
#include "lombscargle.h"
#include "timeanalysis.h"
#include "spectrumanalysis.h"

/**
 *  @namespace Analysis
 *  @brief The Analysis namespace contains all functions for analysis
 */
namespace Analysis {

/**
 * @brief getTrainingSignal
 * @param trainingMap - source training data
 * @param timeLine - time line
 * @return vector with training data for timeLine
 */
QVector<double> getTrainingSignal(QMap<unsigned long long, double> trainingMap,
                                  QVector<unsigned long long> timeLine);

int findStartPoint(QVector<unsigned long long> timeLine, unsigned long long startPoint, int findFrom = 0);

int hrv2hb(double hrv);
double hb2hrv(int hb);
}

#endif // ALGORITHMS


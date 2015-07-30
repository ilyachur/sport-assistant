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

/**
 * @brief find start point from time line
 * @param timeLine - total time line
 * @param startPoint - start time point
 * @param findFrom - find from index
 * @return index with start time
 */
int findStartPoint(QVector<unsigned long long> timeLine, unsigned long long startPoint, int findFrom = 0);

/**
 * @brief convert rr interbals to heart beat
 * @param hrv - rr interval
 * @return heart beat
 */
int hrv2hb(double hrv);

/**
 * @brief convert heart beat to rr interbals
 * @param hb - heart beat
 * @return rr interval
 */
double hb2hrv(int hb);

/**
 * @brief find Trend from source line
 * @param sourceLine - line with source data
 * @param rangeNum - window size (default = 30)
 * @return vector with trend line
 */
QVector<double> findTrend(QVector<double> sourceLine, int rangeNum = 30);

/**
 * @brief Function for finding stress points
 * @param lf2hf - vector with lf/hf data
 * @param tp - vector with tp data
 * @return vector with stress points
 */
QVector<int> findStressPoints(QVector<double> lf2hf, QVector<double> tp);

}

#endif // ALGORITHMS


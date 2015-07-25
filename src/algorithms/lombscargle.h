#ifndef LOMBSCARGLE_H
#define LOMBSCARGLE_H

#include <QVector>

/// @file lombscargle.h
/// @brief Contains lombscargle algorithm declaration

/**
 *  @namespace Analysis
 *  @brief The Analysis namespace contains all functions for analysis
 */
namespace Analysis {

/**
 *  Purpose
 *  =======
 *
 *  Computes the Lomb-Scargle periodogram as developed by Lomb (1976)
 *  and further extended by Scargle (1982) to find, and test the
 *  significance of weak periodic signals with uneven temporal sampling.
 *
 *  This subroutine calculates the periodogram using a slightly
 *  modified algorithm due to Townsend (2010) which allows the
 *  periodogram to be calculated using only a single pass through
 *  the input samples.
 *  This requires Nw(2Nt+3) trigonometric function evaluations (where
 *  Nw is the number of frequencies and Nt the number of input samples),
 *  giving a factor of ~2 speed increase over the straightforward
 *  implementation.
 *
 *  Arguments
 *  =========
 *
 *  signal_time     double vector
 *                  Sample times
 *
 *  training_signal double vector
 *                  Measurement values
 *
 *  freq            double vector
 *                  Angular frequencies for output periodogram
 *
 *  output_len      int number
 *                  Lenght of output vector (default = len(training_signal)
 *
 *  Return
 *  ======
 *
 *  periodogram     double vector
 *                  Lomb-Scargle periodogram
 *
 **/
QVector<double> lombscargle(QVector<double> signal_time, QVector<double> training_signal,
                            QVector<double> freq, int output_len = -1);

}

#endif // LOMBSCARGLE_H

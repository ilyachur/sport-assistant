#ifndef LOMBSCARGLE_H
#define LOMBSCARGLE_H

/// @file lombscargle.h
/// @brief Contains lombscargle algorithm declaration

/**
 *  @namespace Analysis
 *  @brief The Analysis namespace contains all functions for analysis
 */
namespace Analysis {

void lombscargle(double* t, double* x, double* w, double* P, int Nt, int Nw);

}

#endif // LOMBSCARGLE_H

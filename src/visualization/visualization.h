#ifndef VISUALIZATION_H
#define VISUALIZATION_H

#include <QMap>
#include <QVector>
#include <QColor>

#include "qcustomplot.h"

/// @file visualization.h
/// @brief Contains all function which are necessary for visualization results of analysis
/// @author Ilya Churaev ilyachur@gmail.com

/**
 *  @namespace Visualization
 *  @brief The Visualization namespace contains all functions for visualization result of analysis
 */
namespace Visualization {

/**
 * @brief Function for detecting necessary function for visualization
 * @param name - pointer to the name of function, return the name of tab for graphics
 * @param data for graph
 * @return graph
 */
QCustomPlot * useShowFunctions(QString *name, QMap<QString, QVector<double>> *data);

/**
 * @brief show result from simple time analysis
 * @param data for graph
 * @return graph
 */
QCustomPlot * showSimpleTimeAnalysis(QMap<QString, QVector<double>> data);

/**
 * @brief showSpectrumAnalysis
 * @param data for graph
 * @return graph
 */
QCustomPlot * showSpectrumAnalysis(QMap<QString, QVector<double>> data);

/**
 * @brief show simple graphs
 * @param data for graph
 * @return graph
 */
QCustomPlot * showGraphs(QMap<QString, QVector<double>> data);

/**
 * @brief show Tp with Lf / Hf graph
 * @param data for graph
 * @return graph
 */
QCustomPlot * showTpLf2HfGraph(QMap<QString, QVector<double>> data);

/**
 * @brief generate random color
 * @return color
 */
QColor generateRandomColor();

}

#endif // VISUALIZATION_H

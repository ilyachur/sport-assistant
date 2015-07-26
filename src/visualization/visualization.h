#ifndef VISUALIZATION_H
#define VISUALIZATION_H

#include <QMap>
#include <QVector>
#include <QColor>

#include "qcustomplot.h"

namespace Visualization {

QCustomPlot * useShowFunctions(QString *name, QMap<QString, QVector<double>> *data);

QCustomPlot * showFilteredData(QMap<QString, QVector<double>> data);

QCustomPlot * showSimpleTimeAnalysis(QMap<QString, QVector<double>> data);

QCustomPlot * showSpectrumAnalysis(QMap<QString, QVector<double>> data);

QCustomPlot * showGraphs(QMap<QString, QVector<double>> data);
QCustomPlot * showTpLf2HfGraph(QMap<QString, QVector<double>> data);

QColor generateRundomColor();

}

#endif // VISUALIZATION_H

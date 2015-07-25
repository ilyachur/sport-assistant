#ifndef VISUALIZATION_H
#define VISUALIZATION_H

#include <QMap>
#include <QVector>

#include "qcustomplot.h"

namespace Visualization {

QCustomPlot * useShowFunctions(QString *name, QMap<QString, QVector<double>> *data);

QCustomPlot * showFilteredData(QMap<QString, QVector<double>> data);

QCustomPlot * showSimpleTimeAnalysis(QMap<QString, QVector<double>> data);

QCustomPlot * showSpectrumAnalysis(QMap<QString, QVector<double>> data);

}

#endif // VISUALIZATION_H

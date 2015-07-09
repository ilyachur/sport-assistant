#include "visualization.h"
#include "qcustomplot.h"

#include <QPen>
#include <QBrush>
#include <QColor>
#include <QApplication>

void Visualization::showFilteredData(QVector<double> timeLine, QVector<double> startData, QVector<double> filteredData) {
    if (timeLine.size() != startData.size() && startData.size() != filteredData.size())
        return;
    QCustomPlot *customPlot = new QCustomPlot();
    /*customPlot->addGraph();
    customPlot->graph(0)->setPen(QPen(Qt::blue));
    customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
    customPlot->graph(0)->setName("Raw data");
    customPlot->graph(0)->setData(timeLine, startData);
    customPlot.addGraph();

    customPlot.graph(1)->setPen(QPen(Qt::red));
    customPlot.graph(1)->setBrush(QBrush(QColor(255, 0, 0, 20)));
    customPlot.graph(1)->setName("Filtered data");
    customPlot.graph(1)->setData(timeLine, filteredData);

    customPlot.xAxis2->setVisible(true);
    customPlot.xAxis2->setTickLabels(false);
    customPlot.yAxis2->setVisible(true);
    customPlot.yAxis2->setTickLabels(false);

    // let the ranges scale themselves so graph 0 fits perfectly in the visible area:
    customPlot.graph(0)->rescaleAxes();
    // same thing for graph 1, but only enlarge ranges (in case graph 1 is smaller than graph 0):
    customPlot.graph(1)->rescaleAxes(true);

    customPlot.savePng(QApplication::applicationDirPath() + "/../../test.png");*/
}

#include "visualization.h"

#include <QPen>
#include <QBrush>
#include <QColor>
#include <QApplication>


QCustomPlot * Visualization::useShowFunctions(QString name, QMap<QString, QVector<double>> *data) {
    if (name == "showFilteredData") {
        return showFilteredData(*data);
    }
    return nullptr;
}

QCustomPlot * Visualization::showFilteredData(QMap<QString, QVector<double>> data) {
    QVector<double> timeLine = data.take("time");
    QVector<double> startData = data.take("startData");
    QVector<double> filteredData = data.take("filteredData");
    if (timeLine.size() != startData.size())
        return nullptr;
    QCustomPlot *customPlot = new QCustomPlot;
    customPlot->addGraph();
    customPlot->graph(0)->setPen(QPen(Qt::blue));
    customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
    customPlot->graph(0)->setName("Raw data");
    customPlot->graph(0)->setData(timeLine, startData);

    customPlot->graph(0)->setLineStyle((QCPGraph::LineStyle)(1));
    customPlot->graph(0)->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(1)));
    if (filteredData.size() > 0 && filteredData.size() == timeLine.size()) {
        customPlot->addGraph();

        customPlot->graph(1)->setPen(QPen(Qt::red));
        customPlot->graph(1)->setBrush(QBrush(QColor(255, 0, 0, 20)));
        customPlot->graph(1)->setName("Filtered data");
        customPlot->graph(1)->setData(timeLine, filteredData);
        // same thing for graph 1, but only enlarge ranges (in case graph 1 is smaller than graph 0):
        customPlot->graph(1)->rescaleAxes(true);
        customPlot->graph(1)->setLineStyle((QCPGraph::LineStyle)(1));
        customPlot->graph(1)->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(1)));
    }

    customPlot->xAxis2->setVisible(true);
    customPlot->xAxis2->setTickLabels(false);
    customPlot->yAxis2->setVisible(true);
    customPlot->yAxis2->setTickLabels(false);

    // let the ranges scale themselves so graph 0 fits perfectly in the visible area:
    customPlot->graph(0)->rescaleAxes();

    return customPlot;

    customPlot->savePng(QApplication::applicationDirPath() + "/../../test.png");
}

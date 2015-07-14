#include "visualization.h"

#include <QPen>
#include <QBrush>
#include <QColor>
#include <QObject>
#include <QApplication>

#include "../algorithms/timeanalysis.h"

// TODO: set graphs scale

QCustomPlot * Visualization::useShowFunctions(QString *name, QMap<QString, QVector<double>> *data) {
    if ((*name) == "showFilteredData") {
        (*name) = "Training data";
        return showFilteredData(*data);
    }
    if ((*name) == "showSimpleTimeAnalysis") {
        (*name) = "Time analysis";
        return showSimpleTimeAnalysis(*data);
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
    //customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
    customPlot->graph(0)->setName("Raw data");
    customPlot->graph(0)->setData(timeLine, startData);

    customPlot->graph(0)->setLineStyle((QCPGraph::LineStyle)(1));
    customPlot->graph(0)->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(1)));
    if (filteredData.size() > 0 && filteredData.size() == timeLine.size()) {
        customPlot->addGraph();

        customPlot->graph(1)->setPen(QPen(Qt::red));
        //customPlot->graph(1)->setBrush(QBrush(QColor(255, 0, 0, 20)));
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



    customPlot->legend->setVisible(true);

    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    // let the ranges scale themselves so graph 0 fits perfectly in the visible area:
    customPlot->graph(0)->rescaleAxes();

    return customPlot;
}


QCustomPlot * Visualization::showSimpleTimeAnalysis(QMap<QString, QVector<double>> data) {
    QVector<double> hbTimeLine = data.take("hbTime");
    QVector<double> hbData = data.take("hbData");
    QVector<double> tirednessTimeLine = data.take("tirednessTime");
    QVector<double> tirednessData = data.take("tirednessData");
    if (hbTimeLine.size() != hbData.size() || tirednessTimeLine.size() != tirednessData.size())
        return nullptr;

    QCustomPlot *customPlot = new QCustomPlot;
    customPlot->legend->setVisible(true);

    customPlot->plotLayout()->clear();

    QCPAxisRect *hbAxisRect = new QCPAxisRect(customPlot);
    hbAxisRect->setupFullAxesBox(true);
    hbAxisRect->axis(QCPAxis::atRight, 0)->setTickLabels(true);

    QCPAxisRect *tirednessAxisRect = new QCPAxisRect(customPlot);
    tirednessAxisRect->setupFullAxesBox(true);
    tirednessAxisRect->axis(QCPAxis::atRight, 0)->setTickLabels(true);

    customPlot->plotLayout()->addElement(0, 0, hbAxisRect);
    customPlot->plotLayout()->addElement(1, 0, tirednessAxisRect);

    QString colors[6] = {"#6666ff", "#bfffe9", "#9AFF9A", "#ffff7f", "#FFB732", "#ff3232"};

    QCPItemRect* section = new QCPItemRect(customPlot);
    section->topLeft->setType(QCPItemPosition::ptPlotCoords);
    section->topLeft->setAxes(hbAxisRect->axis(QCPAxis::atBottom), hbAxisRect->axis(QCPAxis::atLeft));
    section->bottomRight->setType(QCPItemPosition::ptPlotCoords);
    section->bottomRight->setAxes(hbAxisRect->axis(QCPAxis::atBottom), hbAxisRect->axis(QCPAxis::atLeft));
    section->topLeft->setCoords(0,104);
    section->bottomRight->setCoords(100,0);
    section->setBrush(QBrush(QColor(colors[0])));
    section->setPen(Qt::NoPen);

    section = new QCPItemRect(customPlot);
    section->topLeft->setType(QCPItemPosition::ptPlotCoords);
    section->topLeft->setAxes(hbAxisRect->axis(QCPAxis::atBottom), hbAxisRect->axis(QCPAxis::atLeft));
    section->bottomRight->setType(QCPItemPosition::ptPlotCoords);
    section->bottomRight->setAxes(hbAxisRect->axis(QCPAxis::atBottom), hbAxisRect->axis(QCPAxis::atLeft));
    section->topLeft->setCoords(0,114);
    section->bottomRight->setCoords(100,104);
    section->setBrush(QBrush(QColor(colors[1])));
    section->setPen(Qt::NoPen);

    section = new QCPItemRect(customPlot);
    section->topLeft->setType(QCPItemPosition::ptPlotCoords);
    section->topLeft->setAxes(hbAxisRect->axis(QCPAxis::atBottom), hbAxisRect->axis(QCPAxis::atLeft));
    section->bottomRight->setType(QCPItemPosition::ptPlotCoords);
    section->bottomRight->setAxes(hbAxisRect->axis(QCPAxis::atBottom), hbAxisRect->axis(QCPAxis::atLeft));
    section->topLeft->setCoords(0,134);
    section->bottomRight->setCoords(100,114);
    section->setBrush(QBrush(QColor(colors[2])));
    section->setPen(Qt::NoPen);

    section = new QCPItemRect(customPlot);
    section->topLeft->setType(QCPItemPosition::ptPlotCoords);
    section->topLeft->setAxes(hbAxisRect->axis(QCPAxis::atBottom), hbAxisRect->axis(QCPAxis::atLeft));
    section->bottomRight->setType(QCPItemPosition::ptPlotCoords);
    section->bottomRight->setAxes(hbAxisRect->axis(QCPAxis::atBottom), hbAxisRect->axis(QCPAxis::atLeft));
    section->topLeft->setCoords(0,152);
    section->bottomRight->setCoords(100,134);
    section->setBrush(QBrush(QColor(colors[3])));
    section->setPen(Qt::NoPen);

    section = new QCPItemRect(customPlot);
    section->topLeft->setType(QCPItemPosition::ptPlotCoords);
    section->topLeft->setAxes(hbAxisRect->axis(QCPAxis::atBottom), hbAxisRect->axis(QCPAxis::atLeft));
    section->bottomRight->setType(QCPItemPosition::ptPlotCoords);
    section->bottomRight->setAxes(hbAxisRect->axis(QCPAxis::atBottom), hbAxisRect->axis(QCPAxis::atLeft));
    section->topLeft->setCoords(0,171);
    section->bottomRight->setCoords(100,152);
    section->setBrush(QBrush(QColor(colors[4])));
    section->setPen(Qt::NoPen);

    section = new QCPItemRect(customPlot);
    section->topLeft->setType(QCPItemPosition::ptPlotCoords);
    section->topLeft->setAxes(hbAxisRect->axis(QCPAxis::atBottom), hbAxisRect->axis(QCPAxis::atLeft));
    section->bottomRight->setType(QCPItemPosition::ptPlotCoords);
    section->bottomRight->setAxes(hbAxisRect->axis(QCPAxis::atBottom), hbAxisRect->axis(QCPAxis::atLeft));
    section->topLeft->setCoords(0,230);
    section->bottomRight->setCoords(100,171);
    section->setBrush(QBrush(QColor(colors[5])));
    section->setPen(Qt::NoPen);

    QCPGraph *mainGraph1 = customPlot->addGraph(hbAxisRect->axis(QCPAxis::atBottom), hbAxisRect->axis(QCPAxis::atLeft));
    mainGraph1->setData(hbTimeLine, hbData);
    mainGraph1->setPen(QPen(QColor(0, 0, 0), 2));

    mainGraph1->rescaleAxes();

    QCPGraph *mainGraph2 = customPlot->addGraph(tirednessAxisRect->axis(QCPAxis::atBottom),
                                                tirednessAxisRect->axis(QCPAxis::atLeft));
    mainGraph2->setData(tirednessTimeLine, tirednessData);
    mainGraph2->setPen(QPen(QColor(colors[5]), 2));

    mainGraph2->rescaleAxes();

    return customPlot;
}

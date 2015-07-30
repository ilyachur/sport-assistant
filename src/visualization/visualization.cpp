#include "visualization.h"

#include <QPen>
#include <QBrush>
#include <QColor>
#include <QObject>
#include <QApplication>

#include <time.h>

#include "../algorithms/timeanalysis.h"

/// @file visualization.cpp
/// @brief Contains all function which are necessary for visualization results of analysis
/// @author Ilya Churaev ilyachur@gmail.com

QCustomPlot * Visualization::useShowFunctions(QString *name, QMap<QString, QVector<double>> *data) {
    if ((*name) == "showFilteredData") {
        (*name) = "Training data";
        return showGraphs(*data);
    }
    if ((*name) == "showSimpleTimeAnalysis") {
        (*name) = "Time analysis";
        return showSimpleTimeAnalysis(*data);
    }
    if ((*name) == "showSpectrumAnalysisLomb") {
        (*name) = "Spectrum lomb analysis";
        return showSpectrumAnalysis(*data);
    }
    if ((*name) == "showGraphs") {
        (*name) = "Spectrum lomb analysis";
        return showGraphs(*data);
    }
    if ((*name) == "showTpLf2HfGraphLomb") {
        (*name) = "Spectrum lomb analysis";
        return showTpLf2HfGraph(*data);
    }
    return nullptr;
}

QCustomPlot * Visualization::showTpLf2HfGraph(QMap<QString, QVector<double>> data) {
    QVector<double> timeLine = data.take("time");
    QVector<double> tpData = data.take("tpData");
    QVector<double> lf2hfData = data.take("lf2hfData");
    if (timeLine.size() != tpData.size())
        return nullptr;
    QCustomPlot *customPlot = new QCustomPlot;
    customPlot->addGraph();
    customPlot->graph(0)->setPen(QPen(Qt::blue));
    customPlot->graph(0)->setName("Total Power");
    customPlot->graph(0)->setData(timeLine, tpData);

    customPlot->graph(0)->setLineStyle((QCPGraph::LineStyle)(1));
    customPlot->graph(0)->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(1)));
    if (lf2hfData.size() > 0 && lf2hfData.size() == timeLine.size()) {
        customPlot->addGraph(customPlot->xAxis, customPlot->yAxis2);

        customPlot->graph(1)->setPen(QPen(Qt::red));
        customPlot->graph(1)->setName("LF / HF");
        customPlot->graph(1)->setData(timeLine, lf2hfData);
        // same thing for graph 1, but only enlarge ranges (in case graph 1 is smaller than graph 0):
        customPlot->graph(1)->rescaleAxes(true);
        customPlot->graph(1)->setLineStyle((QCPGraph::LineStyle)(1));
        customPlot->graph(1)->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(1)));
    }


    customPlot->yAxis2->setVisible(true);
    customPlot->yAxis->setLabel("Total Power");
    customPlot->yAxis2->setLabel("LF / HF");



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

QCustomPlot * Visualization::showSpectrumAnalysis(QMap<QString, QVector<double>> data) {
    QVector<double> hbTimeLine = data.take("signalTime");
    QVector<double> hbData = data.take("signalData");
    QVector<double> tirednessTimeLine = data.take("spectrumFreq");
    QVector<double> tirednessData = data.take("spectrumData");
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

    QCPGraph *mainGraph1 = customPlot->addGraph(hbAxisRect->axis(QCPAxis::atBottom), hbAxisRect->axis(QCPAxis::atLeft));
    mainGraph1->setData(hbTimeLine, hbData);
    mainGraph1->setPen(QPen(QColor(0, 0, 0), 2));

    mainGraph1->rescaleAxes();

    QCPGraph *mainGraph2 = customPlot->addGraph(tirednessAxisRect->axis(QCPAxis::atBottom),
                                                tirednessAxisRect->axis(QCPAxis::atLeft));
    mainGraph2->setData(tirednessTimeLine, tirednessData);
    mainGraph2->setPen(QPen(QColor("#6666ff"), 2));

    mainGraph2->rescaleAxes();

    return customPlot;
}

QColor Visualization::generateRandomColor() {
    static bool srandNotNeed = false;
    if (!srandNotNeed) {
        srandNotNeed = true;
        srand(time(nullptr));
    }
    QString color = "#";
    for(auto i(0); i < 3; i++) {
        QString partColor;
        partColor.sprintf("%02X", rand() % 256);
        color += partColor;
    }
    qDebug() << color;
    return QColor(color);
}

QCustomPlot * Visualization::showGraphs(QMap<QString, QVector<double>> data) {
    QVector<double> timeLine = data.take("time");

    QList<QString> graphs = data.keys();
    if (graphs.size() < 1) {
        qDebug() << "Cannot find graphs.";
        return nullptr;
    }

    QCustomPlot *customPlot = new QCustomPlot;
    QColor standartColors[5] = {QColor(Qt::red), QColor(Qt::blue), QColor(Qt::yellow), QColor(Qt::green), QColor(Qt::gray)};

    int countColor = 0;
    for (QString graphName : graphs) {
        QVector<double> graphData = data.take(graphName);
        if (timeLine.size() != graphData.size()) {
            delete customPlot;
            qDebug() << "timeLine.size() != graphData.size()";
            return nullptr;
        }

        QCPGraph *newGraph = customPlot->addGraph();
        if (countColor < 5) {
            newGraph->setPen(QPen(standartColors[countColor]));
        } else {
            newGraph->setPen(QPen(generateRandomColor()));
        }
        countColor++;
        newGraph->setName(graphName);
        newGraph->setData(timeLine, graphData);

        newGraph->setLineStyle((QCPGraph::LineStyle)(1));
        newGraph->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(1)));
    }

    customPlot->xAxis2->setVisible(true);
    customPlot->xAxis2->setTickLabels(false);
    customPlot->yAxis2->setVisible(true);
    customPlot->yAxis2->setTickLabels(false);
    customPlot->legend->setVisible(true);

    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    // let the ranges scale themselves so graph 0 fits perfectly in the visible area:
    //customPlot->graph(0)->rescaleAxes();
    customPlot->rescaleAxes();

    return customPlot;
}

#include "updateranalysetraining.h"

#include "../algorithms/analyse.h"
#include "../visualization/qcustomplot.h"

UpdaterAnalyseTraining::UpdaterAnalyseTraining(QString _athleteName, int _activityID, QString dbName,
                                               QMap<unsigned long long, double> trainingMap, QDateTime _date,
                                               QMap<QString, bool> _analyseSettings, QString activity):
    athleteName(_athleteName), activityID(_activityID), databaseName(dbName), training(trainingMap),
    date(_date), analyseSettings(_analyseSettings), activityName(activity)
{
}

void UpdaterAnalyseTraining::run() {
    if (analyseSettings.size() < 1 || training.size() < 1)
        return;

    saveImages = analyseSettings["save_images"];
    //analyseSettings->value("save_csv", false).toBool();

    //bool trainingLoaded = self.load_analysed_trainings(self.__analysed_hash)
    bool trainingLoaded = false;

    //analyseSettings->beginGroup("pre-processing");
    if (analyseSettings["pre-processing:filtered"]) {
        Analysis::Filter trainingFilter(training);
        QObject::connect(&trainingFilter, SIGNAL(notifyProgress(int)), this, SLOT(notifyProgressSlot(int)));
        QObject::connect(&trainingFilter, SIGNAL(notifyProgressRange(int, int)), this, SLOT(notifyProgressRangeSlot(int,int)));
        QObject::connect(&trainingFilter, SIGNAL(buildGraph(QString, QString, QMap<QString, QVector<double>>*, bool)), this, SLOT(buildGraphSlot(QString, QString, QMap<QString, QVector<double>>*, bool)));
        emit notifyProgressStatus("Filtering training data...");

        training = trainingFilter.simpleFilter();
        QObject::disconnect(&trainingFilter, SIGNAL(notifyProgress(int)), this, SLOT(notifyProgressSlot(int)));
        QObject::disconnect(&trainingFilter, SIGNAL(notifyProgressRange(int, int)), this, SLOT(notifyProgressRangeSlot(int,int)));
        QObject::disconnect(&trainingFilter, SIGNAL(buildGraph(QString, QString, QMap<QString, QVector<double>>*, bool)), this, SLOT(buildGraphSlot(QString, QString, QMap<QString, QVector<double>>*, bool)));
    }

    if (analyseSettings["analyse:time:timeAnalisys"]) {
        Analysis::TimeAnalysis timeAnalyser(training);
        QObject::connect(&timeAnalyser, SIGNAL(notifyProgress(int)), this, SLOT(notifyProgressSlot(int)));
        QObject::connect(&timeAnalyser, SIGNAL(notifyProgressRange(int, int)), this, SLOT(notifyProgressRangeSlot(int,int)));
        QObject::connect(&timeAnalyser, SIGNAL(buildGraph(QString, QString, QMap<QString, QVector<double>>*, bool)), this, SLOT(buildGraphSlot(QString, QString, QMap<QString, QVector<double>>*, bool)));
        emit notifyProgressStatus("Time analysis...");

        timeAnalyser.simpleTimeAnalysis();
        QObject::disconnect(&timeAnalyser, SIGNAL(notifyProgress(int)), this, SLOT(notifyProgressSlot(int)));
        QObject::disconnect(&timeAnalyser, SIGNAL(notifyProgressRange(int, int)), this, SLOT(notifyProgressRangeSlot(int,int)));
        QObject::disconnect(&timeAnalyser, SIGNAL(buildGraph(QString, QString, QMap<QString, QVector<double>>*, bool)), this, SLOT(buildGraphSlot(QString, QString, QMap<QString, QVector<double>>*, bool)));
    }


    if (analyseSettings["analyse:spectrum:lomb"]) {
        Analysis::SpectrumAnalysis spectrumAnalyser(training);
        QObject::connect(&spectrumAnalyser, SIGNAL(notifyProgress(int)), this, SLOT(notifyProgressSlot(int)));
        QObject::connect(&spectrumAnalyser, SIGNAL(notifyProgressRange(int, int)), this, SLOT(notifyProgressRangeSlot(int,int)));
        QObject::connect(&spectrumAnalyser, SIGNAL(buildGraph(QString, QString, QMap<QString, QVector<double>>*, bool)), this, SLOT(buildGraphSlot(QString, QString, QMap<QString, QVector<double>>*, bool)));
        emit notifyProgressStatus("Spectrum Lomb analysis...");

        spectrumAnalyser.searchStressPoints(Analysis::SpectrumType::LOMB);
        QObject::disconnect(&spectrumAnalyser, SIGNAL(notifyProgress(int)), this, SLOT(notifyProgressSlot(int)));
        QObject::disconnect(&spectrumAnalyser, SIGNAL(notifyProgressRange(int, int)), this, SLOT(notifyProgressRangeSlot(int,int)));
        QObject::disconnect(&spectrumAnalyser, SIGNAL(buildGraph(QString, QString, QMap<QString, QVector<double>>*, bool)), this, SLOT(buildGraphSlot(QString, QString, QMap<QString, QVector<double>>*, bool)));
    }

    // TODO: Implemented it
    if (analyseSettings["analyse:spectrum:wavelet"]) {
        Analysis::SpectrumAnalysis spectrumAnalyser(training);
        QObject::connect(&spectrumAnalyser, SIGNAL(notifyProgress(int)), this, SLOT(notifyProgressSlot(int)));
        QObject::connect(&spectrumAnalyser, SIGNAL(notifyProgressRange(int, int)), this, SLOT(notifyProgressRangeSlot(int,int)));
        QObject::connect(&spectrumAnalyser, SIGNAL(buildGraph(QString, QString, QMap<QString, QVector<double>>*, bool)), this, SLOT(buildGraphSlot(QString, QString, QMap<QString, QVector<double>>*, bool)));
        emit notifyProgressStatus("Spectrum Wavelet analysis...");

        spectrumAnalyser.searchStressPoints(Analysis::SpectrumType::WAVELET);
        QObject::disconnect(&spectrumAnalyser, SIGNAL(notifyProgress(int)), this, SLOT(notifyProgressSlot(int)));
        QObject::disconnect(&spectrumAnalyser, SIGNAL(notifyProgressRange(int, int)), this, SLOT(notifyProgressRangeSlot(int,int)));
        QObject::disconnect(&spectrumAnalyser, SIGNAL(buildGraph(QString, QString, QMap<QString, QVector<double>>*, bool)), this, SLOT(buildGraphSlot(QString, QString, QMap<QString, QVector<double>>*, bool)));
    }
    if (analyseSettings["analyse:spectrum:fft"]) {
        Analysis::SpectrumAnalysis spectrumAnalyser(training);
        QObject::connect(&spectrumAnalyser, SIGNAL(notifyProgress(int)), this, SLOT(notifyProgressSlot(int)));
        QObject::connect(&spectrumAnalyser, SIGNAL(notifyProgressRange(int, int)), this, SLOT(notifyProgressRangeSlot(int,int)));
        QObject::connect(&spectrumAnalyser, SIGNAL(buildGraph(QString, QString, QMap<QString, QVector<double>>*, bool)), this, SLOT(buildGraphSlot(QString, QString, QMap<QString, QVector<double>>*, bool)));
        emit notifyProgressStatus("Spectrum FFT analysis...");

        spectrumAnalyser.searchStressPoints(Analysis::SpectrumType::FFT);
        QObject::disconnect(&spectrumAnalyser, SIGNAL(notifyProgress(int)), this, SLOT(notifyProgressSlot(int)));
        QObject::disconnect(&spectrumAnalyser, SIGNAL(notifyProgressRange(int, int)), this, SLOT(notifyProgressRangeSlot(int,int)));
        QObject::disconnect(&spectrumAnalyser, SIGNAL(buildGraph(QString, QString, QMap<QString, QVector<double>>*, bool)), this, SLOT(buildGraphSlot(QString, QString, QMap<QString, QVector<double>>*, bool)));
    }

    emit updaterFinished(activityID);
}

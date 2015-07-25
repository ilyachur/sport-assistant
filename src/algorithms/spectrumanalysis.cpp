#include "spectrumanalysis.h"
#include "analyse.h"

#include <QDebug>

Analysis::SpectrumAnalysis::SpectrumAnalysis() {}

Analysis::SpectrumAnalysis::SpectrumAnalysis(
        QMap<unsigned long long, double> _training):
    training(_training) {}


QMap<unsigned long long, double> Analysis::SpectrumAnalysis::searchStressPoints(SpectrumType analyseType) {
    qDebug() << analyseType;

    int secChangeStep = 60;

    if (analyseType == Analysis::SpectrumType::FFT) {
    } else if (analyseType == Analysis::SpectrumType::LOMB) {
        QVector<unsigned long long> timeLineLong;
        for (auto key : training.keys()) {
            timeLineLong.append(key);
        }
        qSort(timeLineLong);

        unsigned long long startTime = timeLineLong.at(0);
        unsigned long long finishTime = timeLineLong.at(timeLineLong.length() - 1) - startTime;

        QVector<double> timeLineDouble;
        for (auto key : timeLineLong) {
            timeLineDouble.append((key - startTime) / 1000.0);
        }

        QVector<double> trainingHrv = getTrainingSignal(training, timeLineLong);
        QVector<double> freq = getFreqForHt(trainingHrv.size());
        QVector<double> periodogram = lombscargle(timeLineDouble,trainingHrv, freq);
    } else if (analyseType == Analysis::SpectrumType::WAVELET) {
    }

    return QMap<unsigned long long, double>();
}


QVector<double> Analysis::SpectrumAnalysis::getFreqForHt(int length) {
    QVector<double> returnVector;
    if (length < 1) {
        return returnVector;
    }
    double startPoint = 0.00000000000001;
    double endPoint = 0.5;

    double plusValue = (endPoint - startPoint) / length;
    for(auto i(0); i < length; i++) {
        if (!i) {
            returnVector.append(0.00000000000001);
        } else {
            returnVector.append(returnVector.at(i - 1) + plusValue);
        }
    }

    return returnVector;
}

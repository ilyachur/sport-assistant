#include "spectrumanalysis.h"
#include "analyse.h"

#include <QDebug>

Analysis::SpectrumAnalysis::SpectrumAnalysis() {}

Analysis::SpectrumAnalysis::SpectrumAnalysis(
        QMap<unsigned long long, double> _training):
    training(_training) {}


QMap<unsigned long long, double> Analysis::SpectrumAnalysis::searchStressPoints(SpectrumType analyseType) {
    emit notifyProgress(0);

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

//        QVector<double> trainingHrv = getTrainingSignal(training, timeLineLong);
//        QVector<double> freq = getFreqForHt(trainingHrv.size());
//        QVector<double> periodogram = lombscargle(timeLineDouble,trainingHrv, freq);

//        QMap<QString, QVector<double>> *data = new QMap<QString, QVector<double>>;


//        QVector<double> hbValues;
//        QVector<double> hbLine;
//        for (auto i(0); i < timeLineLong.length(); i++) {
//            hbLine.append((double)(((timeLineLong.at(i) - startTime) * 100) / (double)finishTime));
//            hbValues.append(training[timeLineLong.at(i)]);
//        }

//        data->insert("signalTime", hbLine);
//        data->insert("signalData", hbValues);
//        data->insert("spectrumData", periodogram);
//        data->insert("spectrumFreq", freq);
//        emit buildGraph("showSpectrumAnalysisLomb", "SpectrumLombAll.png", data, true);

        int lastStartPoint = 0;
        int lastEndPoint = 0;

        int lastValue = (int)(((finishTime - milisecInterval) / milisecChangeInterval) + 1);
        if (lastValue < 1)
            lastValue = 1;
        emit notifyProgressRange(0, lastValue);

        QVector<double> vlfv;
        QVector<double> lfv;
        QVector<double> hfv;
        QVector<double> vhfv;
        QVector<double> tpv;
        QVector<double> lf2hf;

        for(auto i(0); i < lastValue; i++) {
            int startPoint =  findStartPoint(timeLineLong, startTime + i * milisecChangeInterval, lastStartPoint);
            lastStartPoint = startPoint;
            int endPoint = findStartPoint(timeLineLong, startTime + i * milisecChangeInterval + milisecInterval, lastEndPoint);
            lastEndPoint = endPoint;
            QVector<unsigned long long> timeRange;
            QVector<double> timeRangeDouble;
            for (auto j(startPoint); j < endPoint; j++) {
                timeRange.append(timeLineLong.at(j));
                timeRangeDouble.append(timeLineDouble.at(j));
            }
            QVector<double> trainingHrv = getTrainingSignal(training, timeRange);

            QVector<double> freq = getFreqForHt(trainingHrv.size());
            QVector<double> periodogram = lombscargle(timeRangeDouble, trainingHrv, freq);

            double vlf, lf, hf, vhf, tp;

            getSpectrumPower(periodogram, freq, &vlf, &lf, &hf, &vhf, &tp);

            vlfv.append(vlf);
            lfv.append(lf);
            hfv.append(hf);
            vhfv.append(vhf);
            tpv.append(tp);
            if (hf == 0) {
                qDebug() << "Error: lf/hf divide by zerro!";
                lf2hf.append(0);
            } else {
                lf2hf.append(lf / hf);
            }

            /*QMap<QString, QVector<double>> *data = new QMap<QString, QVector<double>>;

            QVector<double> hbValues;
            QVector<double> hbLine;
            for (auto i(0); i < timeRange.length(); i++) {
                hbLine.append((double)(((timeRange.at(i) - startTime) * 100) / (double)finishTime));
                hbValues.append(training[timeRange.at(i)]);
            }

            data->insert("signalTime", hbLine);
            data->insert("signalData", hbValues);
            data->insert("spectrumData", periodogram);
            data->insert("spectrumFreq", freq);
            emit buildGraph("showSpectrumAnalysisLomb", "SpectrumLomb_" + QString::number(lastStartPoint) + "_" \
                            + QString::number(lastEndPoint) + ".png", data, false);*/

            emit notifyProgress(i);
        }

        QMap<QString, QVector<double>> *data = new QMap<QString, QVector<double>>;

        QVector<double> timeLine100;
        double step = 100.0 / (double)lfv.size();
        for (auto i(0); i < lfv.size(); i++) {
            if (!i) {
                timeLine100.append(0);
            } else {
                timeLine100.append(timeLine100.at(i - 1) + step);
            }
        }
        data->insert("time", timeLine100);
        data->insert("lf", lfv);
        data->insert("hf", hfv);
        data->insert("tp", tpv);
        emit buildGraph("showGraphs", "SpectrumLfHfTp.png", data, false);

        QVector<double> lf2hfTrend = findTrend(lf2hf);
        QVector<double> tpTrend = findTrend(tpv);
        QVector<int> stressPoints = findStressPoints(lf2hfTrend, tpTrend);
        qDebug() << stressPoints;
        data = new QMap<QString, QVector<double>>;

        QVector<double> hbLine;
        QVector<double> stressPointPercents;
        step = 100.0 / (double)lf2hfTrend.size();
        for (auto i(0); i < lf2hfTrend.size(); i++) {
            if (!i) {
                hbLine.append(0);
            } else {
                hbLine.append(hbLine.at(i - 1) + step);
            }
            if (stressPoints.contains(i))
                stressPointPercents.append(hbLine.at(i));
        }

        data->insert("time", hbLine);
        data->insert("tpData", tpTrend);
        data->insert("lf2hfData", lf2hfTrend);
        data->insert("StressPoints", stressPointPercents);
        emit buildGraph("showTpLf2HfGraphLomb", "SpectrumLomb_StressPoints.png", data, true);
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

void Analysis::SpectrumAnalysis::getSpectrumPower(QVector<double> signal, QVector<double> freq,
                                                  double *vlf, double *lf, double *hf, double *vhf, double *tp) {
    if (freq.size() != signal.size()) {
        qDebug() << "Error: freq.size() != signal.size()!";
        return;
    }
    if (vlf != nullptr) {
        *vlf = 0;
        for(auto i(0); i < freq.size(); i++) {
            if (freq.at(i) < 0.015)
                continue;
            if (freq.at(i) > 0.04)
                break;
            *vlf += signal.at(i);
        }
    }
    if (lf != nullptr) {
        *lf = 0;
        for(auto i(0); i < freq.size(); i++) {
            if (freq.at(i) < 0.04)
                continue;
            if (freq.at(i) > 0.15)
                break;
            *lf += signal.at(i);
        }
    }
    if (hf != nullptr) {
        *hf = 0;
        for(auto i(0); i < freq.size(); i++) {
            if (freq.at(i) < 0.15)
                continue;
            if (freq.at(i) > 0.4)
                break;
            *hf += signal.at(i);
        }
    }
    if (vhf != nullptr) {
        *vhf = 0;
        for(auto i(0); i < freq.size(); i++) {
            if (freq.at(i) < 0.4)
                continue;
            if (freq.at(i) > 0.5)
                break;
            *vhf += signal.at(i);
        }
    }
    if (tp != nullptr) {
        *tp = 0;
        for(auto i(0); i < freq.size(); i++) {
            if (freq.at(i) < 0)
                continue;
            if (freq.at(i) > 0.4)
                break;
            *tp += signal.at(i);
        }
    }
}

#ifndef SPECTRUMANALYSIS_H
#define SPECTRUMANALYSIS_H

#include <QMap>
#include <QVector>
#include <QString>
#include <QObject>
#include <QDateTime>

namespace Analysis {

enum SpectrumType {
    FFT,
    LOMB,
    WAVELET,
};

class SpectrumAnalysis: public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Default constructor
     */
    SpectrumAnalysis();

    /**
     * @brief Constructor for SpectrumAnalysis class
     * @param _training - source training data
     */
    SpectrumAnalysis(QMap<unsigned long long, double> _training);


    /**
     * @brief setter for training data
     * @param training data
     */
    inline void setTrainingData(const QMap<unsigned long long, double> training) {
        this->training = training;
    }

    QMap<unsigned long long, double> searchStressPoints(SpectrumType analyseType);

private:
    QMap<unsigned long long, double> training;

    QVector<double> getFreqForHt(int length);

signals:
    void notifyProgress(int value);
    void notifyProgressRange(int from, int to);
    void buildGraph(QString name, QString imageName, QMap<QString, QVector<double>> *data, bool showGraph);
};

}

#endif // SPECTRUMANALYSIS_H

#ifndef SPECTRUMANALYSIS_H
#define SPECTRUMANALYSIS_H

/// @file spectrumanalysis.h
/// @brief Contains classes, functions and enums for spectrum analysis
/// @author Ilya Churaev ilyachur@gmail.com

#include <QMap>
#include <QVector>
#include <QString>
#include <QObject>
#include <QDateTime>

namespace Analysis {

/**
 * @brief The SpectrumType enum
 */
enum SpectrumType {
    FFT,
    LOMB,
    WAVELET,
};

/**
 * @brief The SpectrumAnalysis class
 */
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

    /**
     * @brief searchStressPoints is a main function for spectrum analysis
     * @param analyseType - for choosing algorithm for decomposition signal in spectrum
     */
    void searchStressPoints(SpectrumType analyseType);

private:
    QMap<unsigned long long, double> training;

    /**
     * @brief getFreqForHt
     * @param length - length of signal
     * @return Frequences vector
     */
    QVector<double> getFreqForHt(int length);

    /**
     * @brief Function for getting spectrum power
     * @param signal - signal vector
     * @param freq - frequences vector
     * @param vlf - pointer to vlf power
     * @param lf - pointer to lf power
     * @param hf - pointer to hf power
     * @param vhf - pointer to vhf power
     * @param tp - pointer to tp power
     */
    void getSpectrumPower(QVector<double> signal, QVector<double> freq, double *vlf, double *lf,
                          double *hf, double *vhf, double *tp);

    const int milisecInterval = 100 * 1000;
    const int milisecChangeInterval = 1 * 1000;

signals:
    /**
     * @brief Signal for changing progress bar value
     * @param value - current value
     */
    void notifyProgress(int value);

    /**
     * @brief Signal for setting progress bar range
     * @param from - start value
     * @param to - end value
     */
    void notifyProgressRange(int from, int to);

    /**
     * @brief Signal for creating graph by output data
     * @param name of function
     * @param name for saving image
     * @param data map
     * @param flag for showing graph
     */
    void buildGraph(QString name, QString imageName, QMap<QString, QVector<double>> *data, bool showGraph);
};

}

#endif // SPECTRUMANALYSIS_H

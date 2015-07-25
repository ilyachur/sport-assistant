#include "lombscargle.h"
#include <math.h>

#include <QDebug>

/// @file lombscargle.cpp
/// @brief Contains lombscargle algorithm realisation



//QVector<double> Analysis::lombscargle(double* t,
//double* x, double* w, double* P, int Nt, int Nw)

QVector<double> Analysis::lombscargle(QVector<double> signal_time,
                                      QVector<double> training_signal,
                                      QVector<double> freq, int output_len)
{
    QVector<double> periodogram;
    if (signal_time.size() != training_signal.size() ||
            signal_time.size() != freq.size() ||
            signal_time.size() < 1) {
        qDebug() << "Please check lenght of input arrays!";
        qDebug() << "    signal_time.size() = " << QString::number(signal_time.size());
        qDebug() << "    training_signal.size() = " << QString::number(training_signal.size());
        qDebug() << "    freq.size() = " << QString::number(freq.size());
        return periodogram;
    }

    if (output_len < 1) {
        output_len = training_signal.size();
        qDebug() << output_len;
    }

    /* Local variables */
    int i, j;
    double c, s, xc, xs, cc, ss, cs;
    double tau, c_tau, s_tau, c_tau2, s_tau2, cs_tau;
    double term0, term1;

    int signal_timep = 0;
    int training_signalp = 0;
    int freqp = 0;

    /* Use x86 decrement and compare to zero instruction (farster than ++) */
    i = output_len + 1;
    while (--i) {
        xc = 0.;
        xs = 0.;
        cc = 0.;
        ss = 0.;
        cs = 0.;

        /* (Re)set pointers to start of input arrays */
        signal_timep = 0;
        training_signalp = 0;

        j = training_signal.size();
        while (--j)
        {
            c = cos(freq.at(freqp) * signal_time.at(signal_timep));
            s = sin(freq.at(freqp) * signal_time.at(signal_timep));

            xc += training_signal.at(training_signalp) * c;
            xs += training_signal.at(training_signalp) * s;
            cc += c * c;
            ss += s * s;
            cs += c * s;

            /* Next element in input arrays */
            ++signal_timep;
            ++training_signalp;
        }

        tau = atan(2 * cs / (cc - ss)) / (2 * freq.at(freqp));
        c_tau = cos(freq.at(freqp) * tau);
        s_tau = sin(freq.at(freqp) * tau);
        c_tau2 = c_tau * c_tau;
        s_tau2 = s_tau * s_tau;
        cs_tau = 2 * c_tau * s_tau;

        term0 = c_tau * xc + s_tau * xs;
        term1 = c_tau * xs - s_tau * xc;
        periodogram.append(0.5 * (((term0 * term0) / \
                                   (c_tau2 * cc + cs_tau * cs + s_tau2 * ss)) + \
                                  ((term1 * term1) / \
                                   (c_tau2 * ss - cs_tau * cs + s_tau2 * cc))));

        /* Next frequency */
        ++freqp;
    }
    return periodogram;
}

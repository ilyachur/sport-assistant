#include "filter.h"

/// @file filter.cpp
/// @brief Contains class realisation for filtering raw data
/// @author Ilya Churaev ilyachur@gmail.com

#include <QList>
#include <QVector>
#include <QDebug>
#include <math.h>

#include "analyse.h"

#include "../visualization/visualization.h"

Analysis::Filter::Filter() {}

Analysis::Filter::Filter(QMap<unsigned long long, double> _training): training(_training) {}

QMap<unsigned long long, double> Analysis::Filter::simpleFilter() {
    QMap<unsigned long long, double> trainingFiltered;

    double dMax = 0.3;
    QVector<unsigned long long> timeLineLong;
    for (auto key : training.keys()) {
        timeLineLong.append(key);
    }
    qSort(timeLineLong);

    QVector<double> rrIntervals = getTrainingSignal(training, timeLineLong);
    QVector<double> rrIntervalsTemp = rrIntervals;

    double avrRR = 0;
    for (double value : rrIntervals)
        avrRR += value;
    avrRR /= rrIntervals.length();

    emit notifyProgressRange(0, rrIntervals.length());

    int windowSize = 2;
    for(auto i(0); i < rrIntervals.length(); i++) {
        if (i == rrIntervals.length() - 1) {
            trainingFiltered.insert(timeLineLong.at(i), rrIntervals.at(i));
        } else if (abs((rrIntervals.at(i + 1) - rrIntervals.at(i)) / avrRR) > dMax) {
            rrIntervals[i] = avrRR;
            trainingFiltered.insert(timeLineLong.at(i), rrIntervals.at(i));
            if (abs((rrIntervals.at(i + 1) - rrIntervals.at(i)) / avrRR) > dMax) {
                double *tmp;
                int start_point = i - windowSize;
                int finish_point = i + windowSize;
                if (start_point < 0) {
                    finish_point -= start_point;
                    start_point = 0;
                }
                if (finish_point > rrIntervals.size()) {
                    finish_point = rrIntervals.size();
                }
                tmp = new double[finish_point - start_point];
                double *ret_arr = new double[finish_point - start_point];
                for(auto j(start_point), k(0); j < finish_point; j++, k++) {
                    tmp[k] = rrIntervals[j];
                }

                medianFilter(tmp, ret_arr, finish_point - start_point);

                for(auto j(start_point), k(0); j < finish_point; j++, k++) {
                    rrIntervals[j] = ret_arr[k];
                    trainingFiltered.insert(timeLineLong.at(j), rrIntervals.at(j));
                }
                delete [] tmp;
                delete [] ret_arr;
            }
        } else {
            trainingFiltered.insert(timeLineLong.at(i), rrIntervals.at(i));
        }
        emit notifyProgress(i);
    }

    QVector<double> timeLine;
    for (auto i(0); i < timeLineLong.length(); i++) {
        timeLine.append(double(timeLineLong.at(i) / 1000.0));
    }

    QMap<QString, QVector<double>> *data = new QMap<QString, QVector<double>>;
    data->insert("time", timeLine);
    data->insert("Raw data", rrIntervalsTemp);
    data->insert("Filtered data", rrIntervals);

    emit buildGraph("showFilteredData", "filtered_data.png", data, true);

    return trainingFiltered;
}

template <class T> void Analysis::Filter::medianFilter(T *signal, T *result, int N) {
    // Check arguments
    if (!signal || N < 1) {
        return;
    }
    if (N == 1) {
        if (result)
           result[0] = signal[0];
        return;
    }

    // Allocate memory for signal extension
    T *extension = new T[N + 4];
    if (!extension)
       return;

    // Create signal extension
    memcpy(extension + 2, signal, N * sizeof(T));
    for (int i = 0; i < 2; ++i)
    {
       extension[i] = signal[1 - i];
       extension[N + 2 + i] = signal[N - 1 - i];
    }
    // Call median filter implementation
    _medianFilter(extension, result ? result : signal, N + 4);
    // Free memory
    delete[] extension;
}

template <class T> void Analysis::Filter::_medianFilter(const T* signal, T* result, int N)
{
   //   Move window through all elements of the signal
   for (int i = 2; i < N - 2; ++i)
   {
      //   Pick up window elements
      T window[5];
      for (int j = 0; j < 5; ++j)
         window[j] = signal[i - 2 + j];
      //   Order elements (only half of them)
      for (int j = 0; j < 3; ++j)
      {
         //   Find position of minimum element
         int min = j;
         for (int k = j + 1; k < 5; ++k)
            if (window[k] < window[min])
               min = k;
         //   Put found minimum element in its place
         const T temp = window[j];
         window[j] = window[min];
         window[min] = temp;
      }
      //   Get result - the middle element
      result[i - 2] = window[2];
   }
}

template <class T> void Analysis::Filter::medianFilter(T* image, T* result, int N, int M)
{
   //   Check arguments
   if (!image || N < 1 || M < 1)
      return;
   //   Allocate memory for signal extension
   T* extension = new T[(N + 2) * (M + 2)];
   //   Check memory allocation
   if (!extension)
      return;
   //   Create image extension
   for (int i = 0; i < M; ++i)
   {
      memcpy(extension + (N + 2) * (i + 1) + 1, image + N * i, N * sizeof(T));
      extension[(N + 2) * (i + 1)] = image[N * i];
      extension[(N + 2) * (i + 2) - 1] = image[N * (i + 1) - 1];
   }
   //   Fill first line of image extension
   memcpy(extension, extension + N + 2, (N + 2) * sizeof(T));
   //   Fill last line of image extension
   memcpy(extension + (N + 2) * (M + 1), extension + (N + 2) * M, (N + 2) * sizeof(T));
   //   Call median filter implementation
   _medianFilter(extension, result ? result : image, N + 2, M + 2);
   //   Free memory
   delete[] extension;
}

template <class T> void Analysis::Filter::_medianFilter(const T* image, T* result, int N, int M)
{
   //   Move window through all elements of the image
   for (int m = 1; m < M - 1; ++m)
      for (int n = 1; n < N - 1; ++n)
      {
         //   Pick up window elements
         int k = 0;
         T window[9];
         for (int j = m - 1; j < m + 2; ++j)
            for (int i = n - 1; i < n + 2; ++i)
               window[k++] = image[j * N + i];
         //   Order elements (only half of them)
         for (int j = 0; j < 5; ++j)
         {
            //   Find position of minimum element
            int min = j;
            for (int l = j + 1; l < 9; ++l)
            if (window[l] < window[min])
               min = l;
            //   Put found minimum element in its place
            const T temp = window[j];
            window[j] = window[min];
            window[min] = temp;
         }
         //   Get result - the middle element
         result[(m - 1) * (N - 2) + n - 1] = window[4];
      }
}

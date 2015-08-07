#include "analyse.h"
#include <QDebug>

/// @file analyse.cpp
/// @brief Contains realisation of common functions for analysis
/// @author Ilya Churaev ilyachur@gmail.com


QVector<double> Analysis::getTrainingSignal(QMap<unsigned long long, double> trainingMap,
                                QVector<unsigned long long> timeLine) {
    QVector<double> retList;
    for(auto& timeValue : timeLine) {
        retList.append(trainingMap[timeValue]);
    }
    return retList;
}

int Analysis::findStartPoint(QVector<unsigned long long> timeLine, unsigned long long startPoint, int findFrom) {
    int index = -1;

    if (findFrom > timeLine.length())
        return index;

    for(auto i(findFrom); i < timeLine.length(); i++) {
        if (timeLine.at(i) == startPoint) {
            index = i;
            break;
        } else if (timeLine.at(i) > startPoint) {
            index = i;
            break;
        }
    }

    if (index < 0) {
        index = timeLine.length() - 1;
    }
    return index;
}

int Analysis::hrv2hb(double hrv) {
    if (hrv == 0) {
        qDebug() << "Divide by zero!";
        return 0;
    }
    return (int)(60 / hrv);
}

double Analysis::hb2hrv(int hb) {
    if (hb == 0) {
        qDebug() << "Divide by zero!";
        return 0.0;
    }
    return (double)(60 / (double)hb);
}


QVector<double> Analysis::findTrend(QVector<double> sourceLine, int rangeNum) {
    int firstRange = rangeNum / 2;
    int secondRange = rangeNum - firstRange;
    QVector<double> trendRange;
    for(auto i(0); i < sourceLine.size(); i++) {
        int firstPart = firstRange;
        int secondPart = secondRange;
        if (i - firstPart < 0) {
            firstPart = i;
            secondPart = rangeNum - firstPart;
        }
        if (i + secondPart > sourceLine.size() - 1) {
            secondPart = sourceLine.size() - 1 - i;
            firstPart = rangeNum - secondPart;
        }
        if (i - firstPart < 0)
            firstPart = i;
        double middleRange = 0;
        for (auto j(i - firstPart); j < i + secondPart; j++) {
            middleRange += sourceLine.at(j);
        }
        middleRange /= rangeNum + 1;
        trendRange.append(middleRange);
    }
    return trendRange;
}

enum LineTypes {
    INCREASES,
    DECREASES,
    LOCAL_MAX,
    LOCAL_MIN,
    CONST
};

LineTypes findLineBehavior(QVector<double> line, double errorLevel, int *minIndex = nullptr) {
    LineTypes returnType;
    double startPoint = line.at(0);
    double endPoint = line.at(line.size() - 1);

    std::pair<double *, double *> localMinMax = std::minmax_element(line.begin(), line.end());
    if (minIndex != nullptr) {
        *minIndex = line.indexOf(*localMinMax.first);
    }

    returnType = LineTypes::CONST;

    if (startPoint < endPoint && (*localMinMax.second == endPoint || *localMinMax.second <= endPoint + errorLevel) &&
            (*localMinMax.first == startPoint || *localMinMax.first >= startPoint - errorLevel)) {
        returnType = LineTypes::INCREASES;
    } else if (startPoint > endPoint && (*localMinMax.second == startPoint || *localMinMax.second <= startPoint + errorLevel) &&
               (*localMinMax.first == endPoint || *localMinMax.first >= endPoint - errorLevel)) {
        returnType = LineTypes::DECREASES;
    } else if (*localMinMax.second >= startPoint + errorLevel && *localMinMax.second >= endPoint + errorLevel) {
        returnType = LineTypes::LOCAL_MAX;
    } else if (*localMinMax.first <= startPoint - errorLevel && *localMinMax.first <= endPoint - errorLevel) {
        returnType = LineTypes::LOCAL_MIN;
    }

    if (returnType == LineTypes::LOCAL_MAX &&
            *localMinMax.second - std::max(startPoint, endPoint) < std::min(startPoint, endPoint) - *localMinMax.first)
        returnType = LineTypes::LOCAL_MIN;

    return returnType;
}

QVector<int> Analysis::findStressPoints(QVector<double> lf2hf, QVector<double> tp, int stepSize) {
    QVector<int> stressPoints;
    if (lf2hf.size() != tp.size()) {
        qDebug() << "lf2hf.size() != tp.size()";
        return stressPoints;
    }

    for (auto i(0); i < (int)(tp.size() / stepSize) + 1; i++) {
        if (tp.size() - i*stepSize < 1) {
            break;
        }
        LineTypes tpBehavior = findLineBehavior(tp.mid(i*stepSize, 2*stepSize), 10000);
        int minIndex;
        LineTypes lf2hfBehavior = findLineBehavior(lf2hf.mid(i*stepSize, 2*stepSize), 0.004, &minIndex);
        if (tpBehavior != lf2hfBehavior && lf2hfBehavior == LineTypes::LOCAL_MIN && tpBehavior != LineTypes::INCREASES) {
            stressPoints.append(i*stepSize + minIndex);
        }
    }
    return stressPoints;
}

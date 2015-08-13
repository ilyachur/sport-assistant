#ifndef QVSPINBOXRANGESLIDER_H
#define QVSPINBOXRANGESLIDER_H

#include "qspinboxrangeslider.h"
#include <QVBoxLayout>

class QVSpinBoxRangeSlider: public QSpinBoxRangeSlider
{
public:
    QVSpinBoxRangeSlider(QWidget *parent = 0);
    QVSpinBoxRangeSlider(double minValue, double maxValue, double stepSize, double downSliderPos = 0, double upSliderPos = 0, QWidget *parent = 0);
    ~QVSpinBoxRangeSlider() {
        if (layout != nullptr)
            delete layout;
    }

private:
    QVBoxLayout *layout = nullptr;
};

#endif // QVSPINBOXRANGESLIDER_H

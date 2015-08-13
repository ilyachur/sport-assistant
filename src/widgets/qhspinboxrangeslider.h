#ifndef QHSPINBOXRANGESLIDER_H
#define QHSPINBOXRANGESLIDER_H

#include "qspinboxrangeslider.h"
#include <QHBoxLayout>

class QHSpinBoxRangeSlider: public QSpinBoxRangeSlider
{
public:
    QHSpinBoxRangeSlider(QWidget *parent = 0);
    QHSpinBoxRangeSlider(double minValue = 0, double maxValue = 0, double stepSize = 0, double downSliderPos = 0, double upSliderPos = 0, QWidget *parent = 0);
    ~QHSpinBoxRangeSlider() {
        if (layout != nullptr)
            delete layout;
    }

private:
    QHBoxLayout *layout = nullptr;
};

#endif // QHSPINBOXRANGESLIDER_H

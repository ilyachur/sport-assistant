#ifndef QSPINBOXRANGESLIDER_H
#define QSPINBOXRANGESLIDER_H

#include <QWidget>
#include <QDoubleSpinBox>

#include "qrangeslider.h"

class QSpinBoxRangeSlider: public QWidget
{
    Q_OBJECT
public:
    explicit QSpinBoxRangeSlider(QWidget *parent = 0);

    explicit QSpinBoxRangeSlider(double minValue = 0, double maxValue = 0, double stepSize = 0,
                          double downSliderPos = 0, double upSliderPos = 0, QWidget *parent = 0);

    ~QSpinBoxRangeSlider() {
        if (rangeSlider != nullptr)
            delete rangeSlider;
        rangeSlider = nullptr;
    }

    void addRangeSlider(QRangeSlider *slider);

    void getValues(double *min, double *max);
    void setValues(double min, double max);
    void setEmitWhileMoving(bool flag);

protected:
    QRangeSlider *rangeSlider = nullptr;
    QDoubleSpinBox minSpinBox, maxSpinBox;

private:
    double maxVal, minVal;

    double adjustValue(double newValue);
    void emitRangeChange();

public slots:
    void handleMinSpinBox(double newValue);
    void handleMaxSpinBox(double newValue);
    void handleDoubleClick(bool b);
    void handleRangeChange(double min, double max);

signals:
    void doubleClick(bool);
    void rangeChanged(double, double);
};

#endif // QSPINBOXRANGESLIDER_H

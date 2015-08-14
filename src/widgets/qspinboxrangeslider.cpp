#include "qspinboxrangeslider.h"

#include <QSizePolicy>

QSpinBoxRangeSlider::QSpinBoxRangeSlider(QWidget *parent): QWidget(parent) {
    minVal = 0;
    maxVal = 0;

    // Attempt to calculate the appropriate number of decimal points.
    // dec_pnts = abs(decimal.Decimal(slider_range[2]).as_tuple().exponent)

    //minSpinBox.setDecimals();
    minSpinBox.setMinimum(0);
    minSpinBox.setMaximum(0);
    minSpinBox.setSingleStep(0);
    minSpinBox.setValue(0);
    QObject::connect(&minSpinBox, SIGNAL(valueChanged(double)), this, SLOT(handleMinSpinBox(double)));

    //minSpinBox.setDecimals();
    maxSpinBox.setMinimum(0);
    maxSpinBox.setMaximum(0);
    maxSpinBox.setSingleStep(0);
    maxSpinBox.setValue(0);
    QObject::connect(&maxSpinBox, SIGNAL(valueChanged(double)), this, SLOT(handleMaxSpinBox(double)));
}

QSpinBoxRangeSlider::QSpinBoxRangeSlider(double minValue, double maxValue, double stepSize, double downSliderPos, double upSliderPos, QWidget *parent):
QWidget(parent) {
    minVal = minValue;
    maxVal = maxValue;

    // Attempt to calculate the appropriate number of decimal points.
    // dec_pnts = abs(decimal.Decimal(slider_range[2]).as_tuple().exponent)

    //minSpinBox.setDecimals();
    minSpinBox.setMinimum(minValue);
    minSpinBox.setMaximum(maxValue);
    minSpinBox.setSingleStep(stepSize);
    minSpinBox.setValue(downSliderPos);
    QObject::connect(&minSpinBox, SIGNAL(valueChanged(double)), this, SLOT(handleMinSpinBox(double)));

    //minSpinBox.setDecimals();
    maxSpinBox.setMinimum(minValue);
    maxSpinBox.setMaximum(maxValue);
    maxSpinBox.setSingleStep(stepSize);
    maxSpinBox.setValue(upSliderPos);
    QObject::connect(&maxSpinBox, SIGNAL(valueChanged(double)), this, SLOT(handleMaxSpinBox(double)));
}

void QSpinBoxRangeSlider::addRangeSlider(QRangeSlider *slider) {
    rangeSlider = slider;

    rangeSlider->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    QObject::connect(rangeSlider, SIGNAL(doubleClick(bool)), this, SLOT(handleDoubleClick(bool)));
    QObject::connect(rangeSlider, SIGNAL(rangeChanged(double,double)), this, SLOT(handleRangeChange(double,double)));
}

void QSpinBoxRangeSlider::getValues(double *min, double *max) {
    *min = minSpinBox.value();
    *max = maxSpinBox.value();
}

void QSpinBoxRangeSlider::setValues(double min, double max) {
    minSpinBox.setValue(min);
     maxSpinBox.setValue(max);
}

void QSpinBoxRangeSlider::handleDoubleClick(bool b) {
    emit doubleClick(b);
}

double QSpinBoxRangeSlider::adjustValue(double newValue) {
    double adj = round(newValue / rangeSlider->getSingleStep());
    adj = adj * rangeSlider->getSingleStep();
    return adj;
}

void QSpinBoxRangeSlider::emitRangeChange() {
    bool shouldEmit = false;
    if (minVal != minSpinBox.value()) {
        minVal = minSpinBox.value();
        shouldEmit = true;
    }
    if (maxVal != maxSpinBox.value()) {
        maxVal = maxSpinBox.value();
        shouldEmit = true;
    }
    if (shouldEmit) {
        rangeSlider->setValues(minVal, maxVal);
        emit rangeChanged(minVal, maxVal);
    }
}

void QSpinBoxRangeSlider::handleMaxSpinBox(double newValue) {
    maxSpinBox.setValue(adjustValue(newValue));
    if (newValue < minSpinBox.value()) minSpinBox.setValue(newValue);
    emitRangeChange();
}

void QSpinBoxRangeSlider::handleMinSpinBox(double newValue) {
    minSpinBox.setValue(adjustValue(newValue));
    if (newValue > maxSpinBox.value()) maxSpinBox.setValue(newValue);
    emitRangeChange();
}

void QSpinBoxRangeSlider::handleRangeChange(double min, double max) {
    minSpinBox.setValue(min);
    maxSpinBox.setValue(max);
}

void QSpinBoxRangeSlider::setEmitWhileMoving(bool flag) {
    rangeSlider->setEmitWhileMoving(flag);
}

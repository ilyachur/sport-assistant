#include "qvspinboxrangeslider.h"
#include "qvrangeslider.h"

QVSpinBoxRangeSlider::QVSpinBoxRangeSlider(QWidget * parent) :
    QSpinBoxRangeSlider(parent) {
    addRangeSlider(new QVRangeSlider(this));
    if (!parent) {
        setGeometry(200, 200, 300, 100);
    }
    layout = new QVBoxLayout(this);
    layout->addWidget(&minSpinBox);
    layout->addWidget(rangeSlider);
    layout->addWidget(&maxSpinBox);
}

QVSpinBoxRangeSlider::QVSpinBoxRangeSlider(double minValue, double maxValue, double stepSize, double downSliderPos, double upSliderPos, QWidget *parent):
    QSpinBoxRangeSlider(minValue, maxValue, stepSize, downSliderPos, upSliderPos, parent) {
    addRangeSlider(new QVRangeSlider(minValue, maxValue, stepSize, downSliderPos, upSliderPos, this));
    if (!parent) {
        setGeometry(200, 200, 300, 100);
    }
    layout = new QVBoxLayout(this);
    layout->addWidget(&minSpinBox);
    layout->addWidget(rangeSlider);
    layout->addWidget(&maxSpinBox);
}

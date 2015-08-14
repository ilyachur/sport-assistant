#include "qhspinboxrangeslider.h"
#include "qhrangeslider.h"

QHSpinBoxRangeSlider::QHSpinBoxRangeSlider(QWidget * parent) :
    QSpinBoxRangeSlider(parent) {
    addRangeSlider(new QHRangeSlider(this));
    if (!parent) {
        setGeometry(200, 200, 300, 100);
    }
    layout = new QHBoxLayout(this);
    layout->addWidget(&minSpinBox);
    layout->addWidget(rangeSlider);
    layout->addWidget(&maxSpinBox);
}

QHSpinBoxRangeSlider::QHSpinBoxRangeSlider(double minValue, double maxValue, double stepSize, double downSliderPos, double upSliderPos, QWidget *parent):
    QSpinBoxRangeSlider(minValue, maxValue, stepSize, downSliderPos, upSliderPos, parent) {
    addRangeSlider(new QHRangeSlider(minValue, maxValue, stepSize, downSliderPos, upSliderPos, this));
    if (!parent) {
        setGeometry(200, 200, 300, 100);
    }
    layout = new QHBoxLayout(this);
    layout->addWidget(&minSpinBox);
    layout->addWidget(rangeSlider);
    layout->addWidget(&maxSpinBox);
}

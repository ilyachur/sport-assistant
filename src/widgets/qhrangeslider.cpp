#include "qhrangeslider.h"

#include <QPainter>

QHRangeSlider::QHRangeSlider(double minValue, double maxValue, double stepSize, double downSliderPos, double upSliderPos, QWidget *parent):
QRangeSlider(minValue, maxValue, stepSize, downSliderPos, upSliderPos, parent){
    if (!parent)
        setGeometry(200, 200, 200, 100);
    setValues(downSliderPos, upSliderPos);
}

QHRangeSlider::QHRangeSlider(QWidget *parent):
QRangeSlider(parent){
    if (!parent)
        setGeometry(200, 200, 200, 100);
    setValues(0, 0);
}

void QHRangeSlider::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    int w = width();
    int h = height();
    int middle = h / 2;
    h = 20;
    middle -= h / 2;

    // background
    painter.setPen(Qt::gray);
    painter.setBrush(Qt::lightGray);
    painter.drawRect(2, middle + 2, w - 4, h - 4);

    // Range bar
    painter.setPen(Qt::darkGray);
    painter.setBrush(Qt::darkGray);
    painter.drawRect(displayMin - 1, middle + 5, displayMax - displayMin + 2, h - 10);

    // min & max tabs
    painter.setPen(Qt::black);
    painter.setBrush(Qt::gray);
    painter.drawRect(displayMin - barWidth, middle + 1, barWidth, h - 2);

    painter.setPen(Qt::black);
    painter.setBrush(Qt::gray);
    painter.drawRect(displayMax, middle + 1, barWidth, h - 2);
}

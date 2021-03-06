#include "qvrangeslider.h"

#include <QPainter>

QVRangeSlider::QVRangeSlider(double minValue, double maxValue, double stepSize, double downSliderPos, double upSliderPos, QWidget *parent):
QRangeSlider(minValue, maxValue, stepSize, downSliderPos, upSliderPos, parent){
    if (!parent)
        setGeometry(200, 200, 100, 200);
    setValues(downSliderPos, upSliderPos);
}

QVRangeSlider::QVRangeSlider(QWidget *parent):
QRangeSlider(parent){
    if (!parent)
        setGeometry(200, 200, 100, 200);
    setValues(0, 0);
}

void QVRangeSlider::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    int w = width();
    int h = height();
    int middle = w / 2;
    w = 20;
    middle -= w / 2;

    // background
    painter.setPen(Qt::gray);
    painter.setBrush(Qt::lightGray);
    painter.drawRect(middle + 2, 2, w - 4, h - 4);

    // Range bar
    painter.setPen(Qt::darkGray);
    painter.setBrush(Qt::darkGray);
    painter.drawRect(middle + 5, displayMax - 1, w - 10, displayMax - displayMin + 1);

    // min & max tabs
    painter.setPen(Qt::black);
    painter.setBrush(Qt::gray);
    painter.drawRect(middle + 1, h - displayMax - barWidth - 1, w - 2, barWidth);

    painter.setPen(Qt::black);
    painter.setBrush(Qt::gray);
    painter.drawRect(middle + 1, displayMin-1, w - 2, barWidth);
}

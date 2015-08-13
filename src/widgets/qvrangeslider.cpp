#include "qvrangeslider.h"

#include <QPainter>

QVRangeSlider::QVRangeSlider(double minValue, double maxValue, double stepSize, double downSliderPos, double upSliderPos, QWidget *parent):
QRangeSlider(minValue, maxValue, stepSize, downSliderPos, upSliderPos, parent){
    if (!parent)
        setGeometry(200, 200, 100, 200);
}

QVRangeSlider::QVRangeSlider(QWidget *parent):
QRangeSlider(parent){
    if (!parent)
        setGeometry(200, 200, 100, 200);
}

void QVRangeSlider::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    int w = width();
    int h = height();

    // background
    painter.setPen(Qt::gray);
    painter.setBrush(Qt::lightGray);
    painter.drawRect(2, 2, w - 4, h - 4);

    // Range bar
    painter.setPen(Qt::darkGray);
    painter.setBrush(Qt::darkGray);
    painter.drawRect(5, displayMax - 1, w - 10, displayMax - displayMin + 1);

    // min & max tabs
    painter.setPen(Qt::black);
    painter.setBrush(Qt::gray);
    painter.drawRect(1, h - displayMax - barWidth - 1, w - 2, barWidth);

    painter.setPen(Qt::black);
    painter.setBrush(Qt::gray);
    painter.drawRect(1, displayMin-1, w - 2, barWidth);
}

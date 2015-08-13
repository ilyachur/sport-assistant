#include "qrangeslider.h"

#include <math.h>
#include <QDebug>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QResizeEvent>

QRangeSlider::QRangeSlider(QWidget *parent) : QWidget(parent)
{
    barWidth = 10;
    emitWhileMoving = false;
    moving = MovingSlider::None;
    oldScaleMax = oldScaleMin = scale = singleStep = 0.0;
    setMouseTracking(false);
    setRange(0.0, 1.0, 0.01);
    setValues(0.3, 0.6);

    setFocusPolicy(Qt::ClickFocus);
}

QRangeSlider::QRangeSlider(double minValue, double maxValue, double stepSize, double downSliderPos, double upSliderPos, QWidget *parent)
 : QWidget(parent) {
    barWidth = 10;
    emitWhileMoving = false;
    moving = MovingSlider::None;
    oldScaleMax = oldScaleMin = scale = singleStep = 0.0;
    setMouseTracking(false);
    if (minValue || maxValue || stepSize)
        setRange(minValue, maxValue, stepSize);
    else
        setRange(0.0, 1.0, 0.01);

    if (downSliderPos || upSliderPos) {
        setValues(downSliderPos, upSliderPos);
    } else {
        setValues(0.3, 0.6);
    }

    setFocusPolicy(Qt::ClickFocus);
}

void QRangeSlider::getValues(double *startSlider, double *finishSlider) {
    *startSlider = scaleMin;
    *finishSlider = scaleMax;
}

void QRangeSlider::emitRange() {
    if (oldScaleMin != scaleMin || oldScaleMax != scaleMax) {
        emit rangeChanged(scaleMin, scaleMax);
        oldScaleMax = scaleMax;
        oldScaleMin = scaleMin;
    }
}

void QRangeSlider::keyPressEvent(QKeyEvent * event) {
    int key = event->key();

    bool movingMax = false;
    if (key == Qt::Key_Up) {
        scaleMax += singleStep;
        movingMax = true;
    } else if (key == Qt::Key_Down) {
        scaleMax -= singleStep;
        movingMax = true;
    } else if (key == Qt::Key_Left) {
        scaleMin -= singleStep;
    } else if (key == Qt::Key_Right) {
        scaleMin += singleStep;
    }

    if (scaleMax < scaleMin) {
        if (movingMax) {
            scaleMin = scaleMax;
        } else {
            scaleMax = scaleMin;
        }
    }

    if (scaleMax < start)
        scaleMax = start;
    if (scaleMin < start)
        scaleMin = start;

    double sliderMax = start + scale;

    if (scaleMax > sliderMax)
        scaleMax = sliderMax;
    if (scaleMin > sliderMax)
        scaleMin = sliderMax;

    emitRange();
    updateDisplayValues();
    update();
}

void QRangeSlider::mouseDoubleClickEvent(QMouseEvent * event) {
    emit doubleClick(true);
}

int QRangeSlider::getPos(QMouseEvent *event) {
    return event->x();
}

void QRangeSlider::mousePressEvent(QMouseEvent * event) {
    int pos = getPos(event);
    if (abs(displayMin - 0.5 * barWidth - pos) < 0.5 * barWidth) {
        moving = MovingSlider::Min;
    } else if (abs(displayMin + 0.5 * barWidth - pos) < 0.5 * barWidth) {
        moving = MovingSlider::Max;
    } else if (pos > displayMin && pos < displayMax) {
        moving = MovingSlider::Bar;
    }

    startDisplayMin = displayMin;
    startDisplayMax = displayMax;
    startPos = pos;
}

void QRangeSlider::updateDisplayValues() {
    int size = rangeSliderSize() - 2 * barWidth - 1;
    displayMin = size * (scaleMin - start) / scale + barWidth;
    displayMax = size * (scaleMax - start) / scale + barWidth;
}

void QRangeSlider::updateScaleValues() {
    int size = rangeSliderSize() - 2 * barWidth - 1;
    if (moving == MovingSlider::Min || moving == MovingSlider::Bar) {
        scaleMin = start + (displayMin - barWidth) / (double)(size) * scale;
        scaleMin = round(scaleMin / singleStep) * singleStep;
    }
    if (moving == MovingSlider::Max || moving == MovingSlider::Bar) {
        scaleMax = start + (displayMax - barWidth) / (double)(size) * scale;
        scaleMax = round(scaleMax / singleStep) * singleStep;
    }
    updateDisplayValues();
    update();
}

void QRangeSlider::mouseMoveEvent(QMouseEvent * event) {
    int size = rangeSliderSize();
    int diff = startPos - getPos(event);

    if (moving == MovingSlider::Min) {
        int temp = startDisplayMin - diff;
        if (temp >= barWidth && temp < size - barWidth) {
            displayMin = temp;
            if (displayMax < displayMin) displayMax = displayMin;
            updateScaleValues();
            if (emitWhileMoving) emitRange();
        }
    } else if (moving == MovingSlider::Max) {
        int temp = startDisplayMax - diff;
        if (temp >= barWidth && temp < size - barWidth) {
            displayMax = temp;
            if (displayMax < displayMin) displayMin = displayMax;
            updateScaleValues();
            if (emitWhileMoving) emitRange();
        }
    } else if (moving == MovingSlider::Bar) {
        int temp = startDisplayMin - diff;
        if (temp >= barWidth && temp < size - barWidth - (startDisplayMax - startDisplayMin)) {
            displayMin = temp;
            displayMax = startDisplayMax - diff;
            updateScaleValues();
            if (emitWhileMoving) emitRange();
        }
    }
}

void QRangeSlider::mouseReleaseEvent(QMouseEvent * event) {
    if (moving != MovingSlider::None) emitRange();
    moving = MovingSlider::None;
}

void QRangeSlider::resizeEvent(QResizeEvent * event) {
    updateDisplayValues();
}

void QRangeSlider::setRange(double minValue, double maxValue, double stepSize) {
    start = minValue;
    scale = maxValue - minValue;
    singleStep = stepSize;

    double steps = scale / singleStep;
    if (abs(steps - round(steps)) > 0.01 * singleStep)
        qDebug() << "Slider range is not a multiple of the step size!";
}

void QRangeSlider::setValues(double startSlider, double finishSlider) {
    scaleMin = startSlider;
    scaleMax = finishSlider;

    emitRange();
    updateDisplayValues();
    update();
}

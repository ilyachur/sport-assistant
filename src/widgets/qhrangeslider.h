#ifndef QHRANGESLIDER_H
#define QHRANGESLIDER_H

#include "qrangeslider.h"

#include <QPaintEvent>
#include <QMouseEvent>

class QHRangeSlider: public QRangeSlider
{
public:
    QHRangeSlider(QWidget *parent = 0);

    QHRangeSlider(double minValue = 0, double maxValue = 0, double stepSize = 0,
                  double downSliderPos = 0, double upSliderPos = 0, QWidget *parent = 0);


    virtual int rangeSliderSize() {
        return width();
    }

protected:
    virtual int getPos(QMouseEvent *event) {
        return event->x();
    }

private:
    void paintEvent(QPaintEvent * event);
};

#endif // QHRANGESLIDER_H

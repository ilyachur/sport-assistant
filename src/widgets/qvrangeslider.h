#ifndef QVRANGESLIDER_H
#define QVRANGESLIDER_H

#include "qrangeslider.h"

class QVRangeSlider: public QRangeSlider
{
public:
    QVRangeSlider(QWidget *parent = 0);
    QVRangeSlider(double minValue = 0, double maxValue = 0, double stepSize = 0,
                  double downSliderPos = 0, double upSliderPos = 0, QWidget *parent = 0);


    inline rangeSliderSize() {
        return height();
    }

protected:
    inline int getPos(QMouseEvent *event) {
        return height() - event->y();
    }

private:
    void paintEvent(QPaintEvent * event);
};

#endif // QVRANGESLIDER_H

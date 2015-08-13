#ifndef QRANGESLIDER_H
#define QRANGESLIDER_H

#include <QWidget>
#include <QVector>
#include <QMouseEvent>

class QRangeSlider : public QWidget
{
    Q_OBJECT
public:
    explicit QRangeSlider(QWidget *parent = 0);

    explicit QRangeSlider(double minValue = 0, double maxValue = 0, double stepSize = 0,
                          double downSliderPos = 0, double upSliderPos = 0, QWidget *parent = 0);

    QVector<double> getValues();
    void setRange(double minValue, double maxValue, double stepSize);

    inline void getValues(double *startSlider, double *finishSlider);
    inline void setValues(double startSlider, double finishSlider);

    inline int rangeSliderSize() {
        return height();
    }

    inline void setEmitWhileMoving(bool flag) {
        emitWhileMoving = flag;
    }

protected:
    int barWidth;
    inline int getPos(QMouseEvent * event);

private:
    void emitRange();
    bool emitWhileMoving;
    enum MovingSlider {
        None,
        Min,
        Max,
        Bar
    } moving;
    double oldScaleMax, oldScaleMin, singleStep;
    double scaleMin, scaleMax;
    double scale;
    int displayMin, displayMax, startDisplayMin, startDisplayMax;

    double start;

    int startPos;

    void updateDisplayValues();
    void updateScaleValues();

signals:
    void doubleClick(bool);
    void rangeChanged(double, double);

public slots:
};

#endif // QRANGESLIDER_H

#ifndef QRANGESLIDER_H
#define QRANGESLIDER_H

#include <QWidget>
#include <QVector>
#include <QKeyEvent>
#include <QMouseEvent>

class QRangeSlider : public QWidget
{
    Q_OBJECT
public:
    explicit QRangeSlider(QWidget *parent = 0);

    explicit QRangeSlider(double minValue = 0, double maxValue = 0, double stepSize = 0,
                          double downSliderPos = 0, double upSliderPos = 0, QWidget *parent = 0);

    void setRange(double minValue, double maxValue, double stepSize);

    inline void getValues(double *startSlider, double *finishSlider);
    virtual void setValues(double startSlider, double finishSlider);

    virtual int rangeSliderSize() {
        return height();
    }

    inline void setEmitWhileMoving(bool flag) {
        emitWhileMoving = flag;
    }

    inline double getSingleStep() {
        return singleStep;
    }

    inline void setSingleStep(double value) {
        singleStep = value;
    }

protected:
    int barWidth, displayMin, displayMax;
    double singleStep;
    virtual int getPos(QMouseEvent * event);
    void keyPressEvent(QKeyEvent * event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent * event);

private:
    void emitRange();
    bool emitWhileMoving;
    enum MovingSlider {
        None,
        Min,
        Max,
        Bar
    } moving;
    double oldScaleMax, oldScaleMin;
    double scaleMin, scaleMax;
    double scale;
    int startDisplayMin, startDisplayMax;

    double start;

    int startPos;

    void updateDisplayValues();
    void updateScaleValues();

signals:
    void doubleClick(bool);
    void rangeChanged(double, double);
};

#endif // QRANGESLIDER_H

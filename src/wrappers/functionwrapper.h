#ifndef FUNCTIONWRAPPER_H
#define FUNCTIONWRAPPER_H

#include <QObject>
#include <QString>

class FunctionWrapper: public QObject
{
    Q_OBJECT
public:
    FunctionWrapper(int id): QObject(), index(id) {}

private:
    int index;

public slots:
    void rangeChanged(double min, double max) {
        emit rangeChangedID(index);
    }

    void textChanged(QString text) {
        emit textChangedID(index);
    }
    void clicked(bool clk) {
        emit clickedID(index);
    }

signals:
    void rangeChangedID(int);
    void textChangedID(int);
    void clickedID(int);
};

#endif // FUNCTIONWRAPPER_H

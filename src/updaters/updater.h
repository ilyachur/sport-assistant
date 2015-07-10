#ifndef UPDATER_H
#define UPDATER_H

#include <QThread>

class Updater: public QThread
{
public:
    inline void kill() {
        killed = true;
    }
protected:
    bool killed = false;

signals:
    virtual void notifyProgress(int value) = 0;
    virtual void notifyProgressRange(int from, int to) = 0;
    virtual void notifyProgressStatus(QString status) = 0;
    virtual void buildGraph(QString name, QMap<QString, QVector<double>> *data) = 0;
    virtual void updaterFinished(int) = 0;
};

#endif // UPDATER_H

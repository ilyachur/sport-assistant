#ifndef UPDATER_H
#define UPDATER_H

#include <QThread>

class Updater: public QThread
{
public:
    inline void kill() {
        killed = true;
    }
private:
    bool killed = false;

signals:
    virtual void notifyProgress(int value) = 0;
    virtual void notifyProgressRange(int from, int to) = 0;
};

#endif // UPDATER_H

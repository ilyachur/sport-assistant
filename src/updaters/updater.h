#ifndef UPDATER_H
#define UPDATER_H

#include <QThread>

/// @file updater.h
/// @brief Contains definition of abstract updater class
/// @author Ilya Churaev ilyachur@gmail.com

/**
 * @brief The Updater abstract class common for all updater threads
 */
class Updater: public QThread
{
public:
    /**
     * @brief Function which kill updater
     */
    inline void kill() {
        killed = true;
    }
protected:
    bool killed = false;

signals:
    /**
     * @brief Signal for changing progress bar value
     * @param value - current value
     */
    virtual void notifyProgress(int value) = 0;

    /**
     * @brief Signal for setting progress bar range
     * @param from - start value
     * @param to - end value
     */
    virtual void notifyProgressRange(int from, int to) = 0;

    /**
     * @brief Signal for setting progress bar status
     * @param status is a string with information about analysing process
     */
    virtual void notifyProgressStatus(QString status) = 0;

    /**
     * @brief Signal for creating graph by output data
     * @param name of function
     * @param name for saving image
     * @param data map
     * @param flag for showing graph
     */
    virtual void buildGraph(QString name, QString imageName, QMap<QString, QVector<double>> *data, bool showGraph) = 0;

    /**
     * @brief Signal for send message that updater finished
     */
    virtual void updaterFinished(int) = 0;
};

#endif // UPDATER_H

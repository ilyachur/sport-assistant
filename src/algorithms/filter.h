#ifndef FILTER_H
#define FILTER_H

#include <QMap>
#include <QObject>
#include <QString>
#include <QDateTime>

namespace Analyse {

class Filter: public QObject
{
    Q_OBJECT
public:
    Filter();
    Filter(QMap<unsigned long long, double> _training, QString _athleteName = QString(),
           QDateTime _date = QDateTime(), QString _activityName = QString(),
           bool _showImages = false, bool _saveImages = false);

    QMap<unsigned long long, double> simpleFilter();

private:
    QMap<unsigned long long, double> training;
    QString athleteName, activityName;
    QDateTime date;
    bool showImages, saveImages;

signals:
    void notifyProgress(int value);
    void notifyProgressRange(int from, int to);
};

}

#endif // FILTER_H

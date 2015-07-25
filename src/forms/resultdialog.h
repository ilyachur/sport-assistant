#ifndef RESULTDIALOG_H
#define RESULTDIALOG_H

#include <QDateTime>
#include <QDialog>
#include <QWidget>
#include <QVector>
#include <QLayout>
#include <QString>
#include <QDebug>
#include <QMap>
#include <QDir>

#include "../visualization/visualization.h"

namespace Ui {
class ResultDialog;
}

class ResultDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ResultDialog(QWidget *parent = 0);
    ~ResultDialog();

    inline void setAthleteName(QString athleteName) {
        this->athleteName = athleteName;
    }

    inline void setDataFolder(QString dataFolder) {
        this->dataFolder = dataFolder;
    }

    inline void setDate(QDateTime date) {
        this->date = date;
    }

    inline void setSettings(QMap<QString, bool> analyseSettings) {
        saveImages = analyseSettings["save_images"];
    }

    inline void setActivity(QString activity) {
        this->activity = activity;
    }

public slots:
    void showHide() {
        if (isVisible()) {
            hide();
        } else {
            show();
        }
    }

    void buildGraph(QString name, QString imageName, QMap<QString, QVector<double>> *data, bool showGraph);

private:
    Ui::ResultDialog *ui;

    QString athleteName;
    QString dataFolder;
    QString activity;
    bool saveImages;
    QDateTime date;

    QVector<QCustomPlot *> graphics;
    QVector<QWidget *> tabs;
    QVector<QLayout *> layouts;

    QDir createOutputDirectory(QString dirName);
};

#endif // RESULTDIALOG_H

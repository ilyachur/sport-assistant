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

    void buildGraph(QString name, QMap<QString, QVector<double>> *data);

private:
    Ui::ResultDialog *ui;

    QString athleteName;
    QString activity;
    QDateTime date;
    bool saveImages;

    QVector<QCustomPlot *> graphics;
    QVector<QWidget *> tabs;
    QVector<QLayout *> layouts;
};

#endif // RESULTDIALOG_H

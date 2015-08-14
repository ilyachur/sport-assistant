#ifndef MARKTRAININGDIALOG_H
#define MARKTRAININGDIALOG_H

#include <QMap>
#include <QDialog>
#include <QString>
#include <QVector>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include "../wrappers/athletedb.h"
#include "../wrappers/functionwrapper.h"
#include "../widgets/qhspinboxrangeslider.h"

namespace Ui {
class MarkTrainingDialog;
}

class MarkTrainingDialog : public QDialog
{
    Q_OBJECT

public:
    MarkTrainingDialog(int _activityID, QString dbName, QWidget *parent = 0);
    ~MarkTrainingDialog();

private:
    Ui::MarkTrainingDialog *ui;
    QWidget *parent;
    int activityID, trainingID;
    QString activityName;
    QMap<unsigned long long, double> trainingData;
    QVector<unsigned long long> timeLineLong;
    AthleteDB athleteDB;
    QString dataBaseName;
    QVector<QHSpinBoxRangeSlider *> slidersList;
    QVector<QLineEdit *> lineEditList;
    QVector<QPushButton *> buttonsList;
    QVector<QHBoxLayout *> layoutsList;
    QVector<FunctionWrapper *> functionsWrappersList;
    QVector<int> activitiesIdList;

    void addSubActivities();

public slots:
    void addMarkSlider(int activityId = -1, QString activityNameStr = "", int from = 0, int to = 0);
    void updateButtonState(int index);
    void addRemoveUpdateMark(int index);

signals:
    void updateTable();
};

#endif // MARKTRAININGDIALOG_H

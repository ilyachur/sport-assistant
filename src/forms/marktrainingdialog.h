#ifndef MARKTRAININGDIALOG_H
#define MARKTRAININGDIALOG_H

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
    int activityID;
    AthleteDB athleteDB;
    QString dataBaseName;
    QVector<QHSpinBoxRangeSlider *> slidersList;
    QVector<QLineEdit *> lineEditList;
    QVector<QPushButton *> buttonsList;
    QVector<QHBoxLayout *> layoutsList;
    QVector<FunctionWrapper *> functionsWrappersList;
    QVector<bool> savedList;

public slots:
    void addMarkSlider(bool saved = false);
    void updateButtonState(int index);
    void addRemoveUpdateMark(int index);
};

#endif // MARKTRAININGDIALOG_H

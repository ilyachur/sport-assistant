#ifndef PREDICTDIALOG_H
#define PREDICTDIALOG_H

#include <QDialog>
#include <QString>
#include "../wrappers/athletedb.h"

namespace Ui {
class PredictDialog;
}

class PredictDialog : public QDialog
{
    Q_OBJECT

public:
    PredictDialog(int activityID, QString dbName, QWidget *parent = 0);
    ~PredictDialog();

private:
    Ui::PredictDialog *ui;
    int activityID;
    QString dataBaseName;
    AthleteDB athleteDB;
    QVector<QStringList> activityTypes;
    QString currentScheme;

    void setActivityTypes();

public slots:
    void changeScheme();
    void predictResult();
};

#endif // PREDICTDIALOG_H

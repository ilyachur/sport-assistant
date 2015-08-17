#ifndef ADDPARAMETERSDIALOG_H
#define ADDPARAMETERSDIALOG_H

#include <QDialog>
#include <QString>
#include <QVector>
#include <QStringList>
#include <QTableWidgetItem>

#include "../wrappers/athletedb.h"

namespace Ui {
class AddParametersDialog;
}

class AddParametersDialog : public QDialog
{
    Q_OBJECT

public:
    AddParametersDialog(int activityID, QString dbName, QWidget *parent = 0);
    ~AddParametersDialog();

    void setActivityTypes(QString newActivity = "");

private:
    Ui::AddParametersDialog *ui;

    int activityID;
    QVector<QTableWidgetItem *> tablesItems;
    QString dataBaseName;
    AthleteDB athleteDB;
    QVector<QStringList> activityTypes;
    QString currentScheme;

    void setParams(int row);
    QStringList getParams(int col);

    void clearTable();

public slots:
    void submit();
    void createScheme();
    void addRow();
    void removeRow();
    void changeScheme();
};

#endif // ADDPARAMETERSDIALOG_H

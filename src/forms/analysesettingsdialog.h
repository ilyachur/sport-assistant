#ifndef ANALYSESETTINGSDIALOG_H
#define ANALYSESETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class AnalyseSettingsDialog;
}

class AnalyseSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    AnalyseSettingsDialog(int activityID, QString dbName, QWidget *parent = 0);
    ~AnalyseSettingsDialog();

private:
    Ui::AnalyseSettingsDialog *ui;
};

#endif // ANALYSESETTINGSDIALOG_H

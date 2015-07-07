#ifndef ANALYSESETTINGSDIALOG_H
#define ANALYSESETTINGSDIALOG_H

#include <QDialog>
#include <QString>
#include <QSettings>

namespace Ui {
class AnalyseSettingsDialog;
}

class AnalyseSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    AnalyseSettingsDialog(int _activityID, QString dbName, QWidget *parent = 0);
    ~AnalyseSettingsDialog();

    bool getSettings(QSettings * newSettings);

private:
    Ui::AnalyseSettingsDialog *ui;

    bool spectrumAnalyseChecked() const;
    bool savedSettings = false;

    QString dataBaseName;
    int activityID;
    QSettings settings;

public slots:
    void saveSettings();
    void markClicked();
    void addInfo();
    void regressionClicked();
    void checkAnalysisType();
};

#endif // ANALYSESETTINGSDIALOG_H

#ifndef ANALYSESETTINGSDIALOG_H
#define ANALYSESETTINGSDIALOG_H

#include <QMap>
#include <QDialog>
#include <QString>
#include <QSettings>

namespace Ui {
class AnalyseSettingsDialog;
}

/**
 * @brief The AnalyseSettingsDialog class
 */
class AnalyseSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for AnalyseSettingsDialog
     * @param activity ID
     * @param database name
     * @param parent widget (dafault = 0)
     */
    AnalyseSettingsDialog(int _activityID, QString dbName, QWidget *parent = 0);
    ~AnalyseSettingsDialog();

    /**
     * @brief Function for getting settings map
     * @return Map with settings
     */
    QMap<QString, bool> getSettings();

private:
    Ui::AnalyseSettingsDialog *ui;

    /**
     * @brief Function for checking that spectrum analysis check box checked
     * @return true or false
     */
    bool spectrumAnalyseChecked() const;
    bool savedSettings = false;

    QString dataBaseName;
    int activityID;
    QMap<QString, bool> settings;

public slots:
    /**
     * @brief Slot for saveing settings
     */
    void saveSettings();
    /**
     * @brief Slot for showing mark dialog
     */
    void markClicked();

    /**
     * @brief Slot for showing dialog for additing information
     */
    void addInfo();
    /**
     * @brief Slot for showing regression dialog
     */
    void regressionClicked();
    /**
     * @brief Slot for checking type of analysis and enable/disable some buttons
     */
    void checkAnalysisType();

    void updateTableSlot();

signals:
    void updateTable();
};

#endif // ANALYSESETTINGSDIALOG_H

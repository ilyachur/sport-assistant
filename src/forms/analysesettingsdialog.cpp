#include "analysesettingsdialog.h"
#include "ui_analysesettingsdialog.h"

#include <QDebug>
#include "predictdialog.h"
#include "marktrainingdialog.h"
#include "addparametersdialog.h"

AnalyseSettingsDialog::AnalyseSettingsDialog(int activityID, QString dbName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AnalyseSettingsDialog)
{
    ui->setupUi(this);

    this->activityID = activityID;
    dataBaseName = dbName;

    setWindowIcon(QIcon(":/icons/heart.ico"));

    ui->checkSpectrumAnalysis->setChecked(false);
    ui->checkWavelet->setEnabled(false);
    ui->checkLomb->setEnabled(false);
    ui->checkFFT->setEnabled(false);

    ui->radioFilterNo->setChecked(true);

    QObject::connect(ui->startAnalyse, SIGNAL(clicked(bool)), this, SLOT(saveSettings()));
    QObject::connect(ui->markTraining, SIGNAL(clicked(bool)), this, SLOT(markClicked()));
    QObject::connect(ui->addInfo, SIGNAL(clicked(bool)), this, SLOT(addInfo()));
    QObject::connect(ui->regression, SIGNAL(clicked(bool)), this, SLOT(regressionClicked()));
    QObject::connect(ui->checkTimeAnalisys, SIGNAL(clicked(bool)), this, SLOT(checkAnalysisType()));
    QObject::connect(ui->checkSpectrumAnalysis, SIGNAL(clicked(bool)), this, SLOT(checkAnalysisType()));
    QObject::connect(ui->checkWavelet, SIGNAL(clicked(bool)), this, SLOT(checkAnalysisType()));
    QObject::connect(ui->checkLomb, SIGNAL(clicked(bool)), this, SLOT(checkAnalysisType()));
    QObject::connect(ui->checkFFT, SIGNAL(clicked(bool)), this, SLOT(checkAnalysisType()));
}

AnalyseSettingsDialog::~AnalyseSettingsDialog()
{
    delete ui;
}

bool AnalyseSettingsDialog::spectrumAnalyseChecked() const {
    if (!ui->checkSpectrumAnalysis->isChecked())
        return false;
    if (!ui->checkFFT->isChecked() && !ui->checkLomb->isChecked() && !ui->checkWavelet->isChecked())
        return false;
    return true;
}

void AnalyseSettingsDialog::checkAnalysisType() {
    if (!ui->checkTimeAnalisys->isChecked() && !spectrumAnalyseChecked())
        ui->startAnalyse->setEnabled(false);
    else
        ui->startAnalyse->setEnabled(true);

    if (ui->checkSpectrumAnalysis->isChecked()) {
        ui->checkWavelet->setEnabled(true);
        ui->checkLomb->setEnabled(true);
        ui->checkFFT->setEnabled(true);
    } else {
        ui->checkWavelet->setEnabled(false);
        ui->checkLomb->setEnabled(false);
        ui->checkFFT->setEnabled(false);
    }
}

void AnalyseSettingsDialog::saveSettings() {
    if (ui->radioFilterNo->isChecked())
        settings.insert("pre-processing:filtered", false);
    else
        settings.insert("pre-processing:filtered", true);

    if (ui->checkWavelet->isChecked())
        settings.insert("analyse:spectrum:wavelet", true);
    else
        settings.insert("analyse:spectrum:wavelet", false);
    if (ui->checkLomb->isChecked())
        settings.insert("analyse:spectrum:lomb", true);
    else
        settings.insert("analyse:spectrum:lomb", false);
    if (ui->checkFFT->isChecked())
        settings.insert("analyse:spectrum:fft", true);
    else
        settings.insert("analyse:spectrum:fft", false);

    if (ui->checkTimeAnalisys->isChecked())
        settings.insert("analyse:time:timeAnalisys", true);
    else
        settings.insert("analyse:time:timeAnalisys", false);

    //settings.beginGroup("post-processing");
    //settings.endGroup();

    if (ui->checkSaveImage->isChecked())
        settings.insert("save_images", true);
    else
        settings.insert("save_images", false);

    if (ui->checkSaveCSV->isChecked())
        settings.insert("save_csv", true);
    else
        settings.insert("save_csv", false);

    savedSettings = true;
    close();
}

QMap<QString, bool> AnalyseSettingsDialog::getSettings() {
    if (!savedSettings)
        return QMap<QString, bool>();

    return settings;
}

void AnalyseSettingsDialog::markClicked() {
    MarkTrainingDialog markDialog(activityID, dataBaseName);
    markDialog.exec();
}

void AnalyseSettingsDialog::addInfo() {
    AddParametersDialog paramDialog(activityID, dataBaseName);
    paramDialog.exec();
}

void AnalyseSettingsDialog::regressionClicked() {
    PredictDialog predictDialog("RUN");
    predictDialog.exec();
}

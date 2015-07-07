#include "analysesettingsdialog.h"
#include "ui_analysesettingsdialog.h"

#include "predictdialog.h"
#include "marktrainingdialog.h"
#include "addparametersdialog.h"

AnalyseSettingsDialog::AnalyseSettingsDialog(int activityID, QString dbName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AnalyseSettingsDialog)
{
    ui->setupUi(this);

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
    settings.beginGroup("pre-processing");
    if (ui->radioFilterNo->isChecked())
        settings.setValue("filtered", false);
    else
        settings.setValue("filtered", true);
    settings.endGroup();

    settings.beginGroup("analyse");
    settings.beginGroup("spectrum");
    if (ui->checkWavelet->isChecked())
        settings.setValue("wavelet", true);
    if (ui->checkLomb->isChecked())
        settings.setValue("lomb", true);
    if (ui->checkFFT->isChecked())
        settings.setValue("fft", true);
    settings.endGroup();

    settings.beginGroup("time");
    if (ui->checkTimeAnalisys->isChecked())
        settings.setValue("timeAnalisys", true);
    settings.endGroup();

    settings.endGroup();

    settings.beginGroup("post-processing");
    settings.endGroup();

    if (ui->checkSaveImage->isChecked())
        settings.setValue("save_images", true);
    else
        settings.setValue("save_images", false);

    if (ui->checkSaveCSV->isChecked())
        settings.setValue("save_csv", true);
    else
        settings.setValue("save_csv", false);

    savedSettings = true;
    close();
}

bool AnalyseSettingsDialog::getSettings(QSettings * newSettings) {
    if (!savedSettings)
        return false;

    settings.beginGroup("pre-processing");
    newSettings->beginGroup("pre-processing");
    newSettings->setValue("filtered", settings.value("filtered", true));
    newSettings->endGroup();
    settings.endGroup();

    settings.beginGroup("analyse");
    newSettings->beginGroup("analyse");

    settings.beginGroup("spectrum");
    newSettings->beginGroup("spectrum");
    newSettings->setValue("wavelet", settings.value("wavelet", false));
    newSettings->setValue("lomb", settings.value("lomb", false));
    newSettings->setValue("fft", settings.value("fft", false));
    newSettings->endGroup();
    settings.endGroup();

    settings.beginGroup("time");
    newSettings->beginGroup("time");
    newSettings->setValue("timeAnalisys", settings.value("timeAnalisys", false));
    newSettings->endGroup();
    settings.endGroup();

    newSettings->endGroup();
    settings.endGroup();

    settings.beginGroup("post-processing");
    newSettings->beginGroup("post-processing");
    newSettings->endGroup();
    settings.endGroup();

    newSettings->setValue("save_images", settings.value("save_images", false));
    newSettings->setValue("save_csv", settings.value("save_csv", false));

    return true;
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

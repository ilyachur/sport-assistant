#include "analysesettingsdialog.h"
#include "ui_analysesettingsdialog.h"

AnalyseSettingsDialog::AnalyseSettingsDialog(int activityID, QString dbName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AnalyseSettingsDialog)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(":/icons/heart.ico"));
}

AnalyseSettingsDialog::~AnalyseSettingsDialog()
{
    delete ui;
}

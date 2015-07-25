#include "resultdialog.h"
#include "ui_resultdialog.h"

#include <QIcon>
#include <QVBoxLayout>
#include <QScrollArea>

ResultDialog::ResultDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResultDialog)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(":/icons/heart.ico"));

    setWindowFlags(Qt::Window);
}

ResultDialog::~ResultDialog()
{
    for(auto graphic : graphics) {
        delete graphic;
    }
    graphics.clear();

    for(auto layout : layouts) {
        delete layout;
    }
    layouts.clear();

    for(auto tab : tabs) {
        delete tab;
    }
    tabs.clear();
    delete ui;
}

void ResultDialog::buildGraph(QString name, QString imageName, QMap<QString, QVector<double>> *data, bool showGraph) {
    QCustomPlot * plot = Visualization::useShowFunctions(&name, data);

    delete data;
    if (plot == nullptr)
        return;

    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    if (saveImages) {
        QDir imageFolder = createOutputDirectory("images");
        plot->savePng(imageFolder.absolutePath() + "/" + imageName);
    }
    if (!showGraph) return;

    QWidget * existTab = nullptr;
    for(auto i(0); i < ui->tabWidget->count(); i++) {
        if (ui->tabWidget->tabText(i) == name) {
            existTab = ui->tabWidget->widget(i);
            break;
        }
    }
    if (existTab == nullptr) {
        existTab = new QWidget(ui->tabWidget);
        tabs.append(existTab);
        QVBoxLayout *mainLayout = new QVBoxLayout(existTab);
        mainLayout->setContentsMargins(0,0,0,0);
        layouts.append(mainLayout);
        mainLayout->addWidget(plot);
        existTab->setLayout(mainLayout);
        graphics.append(plot);

        ui->tabWidget->addTab(existTab, name);
    } else {
        existTab->layout()->addWidget(plot);
    }
}


QDir ResultDialog::createOutputDirectory(QString dirName) {
    QDir outputDir;

    if (athleteName == "") {
        athleteName = "Unknown";
    }
    if (activity == "") {
        activity = "Unknown";
    }
    if (dataFolder != "") {
        outputDir.setPath(dataFolder + "/../output/");
    } else {
        outputDir.setPath(QApplication::applicationDirPath() + "/output/");
    }

    outputDir.setPath(outputDir.absolutePath() + "/" + dirName +
                       "/" + athleteName + "/" + date.toString("dd.MM.yyyy") +
                      "/" + activity);

    if (!outputDir.exists()) {
        outputDir.makeAbsolute();
        outputDir.mkpath(outputDir.absolutePath());
    }
    return outputDir;
}

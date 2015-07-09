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

void ResultDialog::buildGraph(QString name, QMap<QString, QVector<double>> *data) {
    QCustomPlot * plot = Visualization::useShowFunctions(name, data);
    delete data;
    if (plot == nullptr)
        return;
    QWidget * newTab = new QWidget(ui->tabWidget);
    tabs.append(newTab);
    QVBoxLayout *mainLayout = new QVBoxLayout(newTab);
    mainLayout->setContentsMargins(0,0,0,0);
    layouts.append(mainLayout);
    mainLayout->addWidget(plot);
    newTab->setLayout(mainLayout);
    graphics.append(plot);

    ui->tabWidget->addTab(newTab, "Test");
}

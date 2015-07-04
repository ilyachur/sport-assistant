#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QHeaderView>
#include <QStringList>

#include "../updaters/updaterathletesinfo.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), dataFolder("..\\sport-assistant\\test_data"),
    databaseName("db.sqlite3")
{
    ui->setupUi(this);

    /// Configure status bar
    mainProdressBar = new QProgressBar(ui->statusBar);
    mainProdressBar->setValue(0);
    ui->statusBar->addWidget(mainProdressBar);

    mainProdressBarStatus = new QLabel(ui->statusBar);
    ui->statusBar->addWidget(mainProdressBarStatus);

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QObject::connect(ui->tableWidget, SIGNAL(cellClicked(int,int)), this, SLOT(clickTable(int,int)));

    // TODO: Fixed all buttons
    QObject::connect(ui->actionChoose_data_directory, SIGNAL(triggered(bool)), this, SLOT(close()));
    QObject::connect(ui->actionOpen_data_base, SIGNAL(triggered(bool)), this, SLOT(close()));
    QObject::connect(ui->actionExit, SIGNAL(triggered(bool)), this, SLOT(close()));


    QObject::connect(this, SIGNAL(updateMainProdressBarStatus(QString)), mainProdressBarStatus, SLOT(setText(QString)));

    athleteDB.setNameDB(databaseName);

    updateAthletesInfo();

    //clever_parser.open("C:\\Study\\HSE\\sport-assistant\\test_data\\Ilya\\IceSkates\\28_02_strong_activity.fit");
    //clever_parser.run();
}

MainWindow::~MainWindow()
{
    deleteUpdater();
    clearTableItems();
    if (mainProdressBar != nullptr)
        delete mainProdressBar;
    if (mainProdressBarStatus != nullptr)
        delete mainProdressBarStatus;
    if (additionalProdressBar != nullptr)
        delete additionalProdressBar;
    if (additionalProdressBarStatus != nullptr)
        delete additionalProdressBarStatus;

    delete ui;
}

void MainWindow::clearTableItems() {
    for (auto i(0); i < tableItems.size(); i++)
        delete tableItems.at(i);
    tableItems.clear();
}

int MainWindow::updateAthletesInfo() {
    emit updateMainProdressBarStatus("Updating athletes info...");

    deleteUpdater();
    updater = new UpdaterAthletesInfo(databaseName, dataFolder);
    QObject::connect(updater, SIGNAL(notifyProgressRange(int,int)), mainProdressBar, SLOT(setRange(int,int)));
    QObject::connect(updater, SIGNAL(notifyProgress(int)), this, SLOT(updateMainProdressBar(int)));
    updater->start();
    return 0;
}

void MainWindow::updateMainProdressBar(int value) {
    mainProdressBar->setValue(value);
    if (mainProdressBar->value() >= mainProdressBar->maximum()) {
        emit updateMainProdressBarStatus("Ready");
        mainProdressBar->setValue(0);
        QObject::disconnect(updater, SIGNAL(notifyProgressRange(int, int)), mainProdressBar, SLOT(setRange(int, int)));
        QObject::disconnect(updater, SIGNAL(notifyProgress(int)), this, SLOT(updateMainProdressBar(int)));
        deleteUpdater();

        QVector<QStringList> athletes = athleteDB.findAthlete();
        if (athletes.length() < 1) {
            updateMainProdressBarStatus("Athletes were not found");
            return;
        }
        tableLevel = 0;
        /*[=]()->QVector<QStringList> {
            QVector<QStringList> ret;
            for (QStringList athleteInfo : athletes) {
                QStringList athLine;
                athLine << athleteInfo.at(0) << athleteInfo.at(1);
                athLine.append(athleteInfo.at(1));
                ret.push_back(athLine);
            }
            return ret;
        }*/
        QVector<QStringList> ret;
        for (QStringList athleteInfo : athletes) {
            QStringList athLine;
            athLine << athleteInfo.at(0) << athleteInfo.at(1);
            ret.push_back(athLine);
        }
        updateTable(ret, QString("ID,Name").split(","));
        addPathButton("Athletes");
    }
}

void MainWindow::addPathButton(QString name) {
    for (auto i(0); i < pathButtons.size(); i++) {
        if (pathButtons.at(i)->text() == name)
            return;
    }
    QPushButton *trainingButton = new QPushButton(name);
    trainingButton->setEnabled(false);
    // TODO: Fix it
    for (auto i(0); i < pathButtons.size(); i++) {
        pathButtons.at(i)->setEnabled(true);
    }
    trainingButton->clicked();
    QObject::connect(trainingButton, SIGNAL(clicked(bool)), this, SLOT([=](){choosePathButton(name)}));
    ui->pathLayout->addWidget(trainingButton);
    pathButtons.push_back(trainingButton);
}

void MainWindow::updateTable(QVector<QStringList> table, QStringList colName, QStringList rowName, int sortedBy) {
    if (table.size() < 1 || table.at(0).size() < 1) {
        emit updateMainProdressBarStatus("Table is empty!");
        return;
    }

    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(table.at(0).size());
    ui->tableWidget->setRowCount(table.size());

    clearTableItems();

    if (colName.size() > 0) {
        auto len_table = colName.size();
        if (len_table > table.at(0).size())
            len_table = table.at(0).size();

        for (auto i(0); i < len_table; i++) {
            QTableWidgetItem * tbi = new QTableWidgetItem(colName.at(i));
            ui->tableWidget->setHorizontalHeaderItem(i, tbi);
            tableItems.push_back(tbi);
        }
    }

    if (rowName.size() > 0) {
        auto len_table = rowName.size();
        if (len_table > table.size())
            len_table = table.size();

        for (auto i(0); i < len_table; i++) {
            QTableWidgetItem * tbi = new QTableWidgetItem(rowName.at(i));
            ui->tableWidget->setVerticalHeaderItem(i, tbi);
            tableItems.push_back(tbi);
        }
    }

    qSort(table.begin(), table.end(),
          [=](const QStringList& a, const QStringList& b)
                {return a.at(sortedBy) < b.at(sortedBy);});

    for (auto i(0); i < table.size(); i++) {
        for (auto j(0); j < table.at(i).size(); j++) {
            QTableWidgetItem * tbi = new QTableWidgetItem(table.at(i).at(j));
            ui->tableWidget->setItem(i, j, tbi);
            tableItems.push_back(tbi);
        }
    }
}

void MainWindow::choosePathButton(QString name) {

}

void MainWindow::clickTable(int row, int col) {

}

void MainWindow::showAthleteInfo(bool show) {}

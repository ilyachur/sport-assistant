#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QHeaderView>
#include <QStringList>
#include <QFileDialog>
#include <QDateTime>
#include <QSysInfo>
#include <QPixmap>
#include <QIcon>

#include "../updaters/updaterathletesinfo.h"
#include "analysesettingsdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    databaseName("db.sqlite3")
{
    ui->setupUi(this);

    if (QSysInfo::productType() == "osx") {
        dataFolder = QApplication::applicationDirPath() + "/../../../test_data";
    } else {
        dataFolder = QApplication::applicationDirPath() + "/../../test_data";
    }

    setWindowIcon(QIcon(":/icons/heart.ico"));

    /// Configure status bar
    mainProdressBar = new QProgressBar(ui->statusBar);
    mainProdressBar->setValue(0);
    ui->statusBar->addWidget(mainProdressBar);

    mainProdressBarStatus = new QLabel(ui->statusBar);
    ui->statusBar->addWidget(mainProdressBarStatus);

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QObject::connect(ui->tableWidget, SIGNAL(cellClicked(int,int)), this, SLOT(clickTable(int,int)));

    // TODO: Fixed all buttons
    QObject::connect(ui->actionChoose_data_directory, SIGNAL(triggered(bool)), this, SLOT(chooseDataDirectory()));
    QObject::connect(ui->actionOpen_data_base, SIGNAL(triggered(bool)), this, SLOT(openDataBase()));
    QObject::connect(ui->actionExit, SIGNAL(triggered(bool)), this, SLOT(close()));


    QObject::connect(this, SIGNAL(updateMainProdressBarStatus(QString)), mainProdressBarStatus, SLOT(setText(QString)));

    athleteDB.setNameDB(databaseName);

    updateAthletesInfo();
}

void MainWindow::chooseDataDirectory() {
    QString fileName = QFileDialog::getExistingDirectory(this, "Choose data directory");
    if (fileName == "")
        return;
    dataFolder = fileName;
    updateAthletesInfo();
}

void MainWindow::openDataBase() {
    QFileDialog openDialog(this);
    openDialog.setAcceptMode(QFileDialog::AcceptSave);
    openDialog.setNameFilter("sqlite3(*.sqlite3)");
    openDialog.setDefaultSuffix("sqlite3");
    openDialog.setWindowTitle("Open or create data base");
    openDialog.setLabelText(QFileDialog::Accept, "Open");
    if (openDialog.exec()) {
        QString fileName = openDialog.selectedFiles()[0];
        databaseName = fileName;
        athleteDB.setNameDB(databaseName);
        updateAthletesInfo();
    }
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
    /*for (auto i(0); i < tableItems.size(); i++) {
        delete tableItems.at(i);
    }*/
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
    if (tableLevel == 0)
        QObject::connect(trainingButton, SIGNAL(clicked(bool)), this, SLOT(clickAthletePath()));
    else
        QObject::connect(trainingButton, SIGNAL(clicked(bool)), this, SLOT(clickLevel1Upper()));
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

void MainWindow::clickAthletePath() {
    showAthleteInfo(false);
    while (pathButtons.size() > 1) {
        QPushButton *tempButton = pathButtons.at(1);
        pathButtons.remove(1);
        tempButton->deleteLater();
        delete tempButton;
    }
    pathButtons.at(0)->setEnabled(false);
    ui->pathLayout->update();

    QVector<QStringList> athletes = athleteDB.findAthlete();
    if (athletes.length() < 1) {
        updateMainProdressBarStatus("Athletes were not found");
        return;
    }

    QVector<QStringList> ret;
    for (QStringList athleteInfo : athletes) {
        QStringList athLine;
        athLine << athleteInfo.at(0) << athleteInfo.at(1);
        ret.push_back(athLine);
    }
    tableLevel = 0;
    updateTable(ret, QString("ID,Name").split(","));
}

void MainWindow::clickLevel1Upper() {}

void MainWindow::showAthleteInfo(bool show) {
    static QVector<QWidget *> oldWidgets;
    if (!show) {
        for (auto i(0); i < ui->userInfoLayout->count(); i++) {
            ui->userInfoLayout->itemAt(i)->widget()->setParent(nullptr);
        }
        for (auto oldWidget : oldWidgets) {
            delete oldWidget;
        }
        oldWidgets.clear();
    } else {
        QLabel *profileImage = new QLabel();
        QPixmap profilePixmap(":/icons/profile.png");
        profilePixmap = profilePixmap.scaled(profilePixmap.size().width() / 2,
                                             profilePixmap.size().height() / 2);
        profileImage->setPixmap(profilePixmap);
        ui->userInfoLayout->addWidget(profileImage);
        oldWidgets.push_back(profileImage);
        QMap<QString, QString> ret;
        ret.insert("id", QString::number(athleteID));
        QVector<QStringList> athleteInfo = athleteDB.findAthlete(ret);

        QLabel *profileCommonInfo = new QLabel();
        if (athleteInfo.size() != 1) {
            showAthleteInfo(false);
            qDebug() << "Error! We have more that one athlete with ID: " << QString::number(athleteID);
            return;
        }
        QStringList profileInfoListStr;
        profileInfoListStr << "ID: " + athleteInfo.at(0).at(0);
        profileInfoListStr << "Name: " + athleteInfo.at(0).at(1);
        profileInfoListStr << "Sex: " + athleteInfo.at(0).at(2);
        if (athleteInfo.at(0).at(3).toULongLong() != 0) {
            profileInfoListStr << "Born day: " + QDateTime::fromMSecsSinceEpoch(
                                  athleteInfo.at(0).at(3).toULongLong()).toString("dd.MM.yyyy");
        } else {
            profileInfoListStr << "Born day: Unknown";
        }
        if (athleteInfo.at(0).at(4).toInt() != -1) {
            profileInfoListStr << "Weight: " + athleteInfo.at(0).at(4) + " kg";
        } else {
            profileInfoListStr << "Weight: Unknown";
        }
        if (athleteInfo.at(0).at(5).toInt() != -1) {
            profileInfoListStr << "Height: " + athleteInfo.at(0).at(5) + " cm";
        } else {
            profileInfoListStr << "Height: Unknown";
        }

        profileCommonInfo->setText(profileInfoListStr.join("\n"));
        ui->userInfoLayout->addWidget(profileCommonInfo);
        oldWidgets.push_back(profileCommonInfo);
    }
}

void MainWindow::clickTable(int row, int col) {
    if (tableLevel < 0)
        return;
    if (tableLevel == 0) {
        athleteID = ui->tableWidget->item(row, 0)->text().toInt();
        QString name = ui->tableWidget->item(row, 1)->text();
        QMap<QString, QString> findMap;
        findMap.insert("athlete_id", QString::number(athleteID));
        QVector<QStringList> trainings = athleteDB.findTraining(findMap);
        if (trainings.length() < 1) {
            updateMainProdressBarStatus("Trainings were not found");
            return;
        }

        QVector<QStringList> ret;
        for (QStringList trainingInfo : trainings) {
            QMap<QString, QString> findMapActivity;
            findMapActivity.insert("training_id", QString::number(trainingInfo.at(0).toInt()));
            QVector<QStringList> activities = athleteDB.findActivity(findMapActivity);
            if (activities.length() < 1) {
                updateMainProdressBarStatus("Activities were not found");
                return;
            }
            for (QStringList activityInfo : activities) {
                QStringList athLine;

                athLine << QDateTime::fromMSecsSinceEpoch(activityInfo.at(2).toULongLong()).toString(
                              "dd.MM.yyyy hh:mm:ss") << activityInfo.at(0) << activityInfo.at(3) << trainingInfo.at(3) << trainingInfo.at(0);
                ret.push_back(athLine);
            }
        }

        updateTable(ret, QString("Date,Activity ID,Activity name,File type,Training ID").split(","));
        addPathButton("Trainings " + name);
        showAthleteInfo(true);
        tableLevel = 1;
    } else if (tableLevel == 1 && !isProcess) {
        int activityID = ui->tableWidget->item(row, 1)->text().toInt();
        QMap<QString, QString> findMap;
        findMap.insert("id", QString::number(activityID));
        QVector<QStringList> activityList = athleteDB.findActivity(findMap);
        QString athleteName = pathButtons.at(tableLevel)->text().split(" ").at(1);
        QString date = QDateTime::fromMSecsSinceEpoch(activityList.at(0).at(2).toULongLong())
                .toString("dd.MM.yyyy hh:mm:ss");
        QString activityName = activityList.at(0).at(3);

        AnalyseSettingsDialog settingsDialog(activityID, databaseName);
        settingsDialog.exec();
    }
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDir>
#include <QLabel>
#include <QVector>
#include <QString>
#include <QStringList>
#include <QMainWindow>
#include <QPushButton>
#include <QProgressBar>
#include <QTableWidgetItem>

#include "../wrappers/athletedb.h"
#include "../updaters/updater.h"

#include "resultdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    ResultDialog *resultDialod = nullptr;
    QProgressBar *mainProdressBar = nullptr;
    QLabel *mainProdressBarStatus = nullptr;
    QProgressBar *additionalProdressBar = nullptr;
    QLabel *additionalProdressBarStatus = nullptr;

    QVector<QTableWidgetItem*> tableItems;

    AthleteDB athleteDB;

    QVector<QPushButton*> pathButtons;
    QPushButton showResultButton;
    int tableLevel = -1;
    int athleteID = -1;
    bool isProcess = false;

    QString dataFolder;
    QString databaseName;

    Updater *updater = nullptr;

    inline bool createResultDialog() {
        if (resultDialod == nullptr) {
            resultDialod = new ResultDialog();
            return true;
        }
        return false;
    }

    inline void removeResultDialog() {
        if (resultDialod != nullptr) {
            resultDialod->close();
            QObject::disconnect(&showResultButton, SIGNAL(clicked(bool)), resultDialod, SLOT(showHide()));
            delete resultDialod;
            resultDialod = nullptr;
        }
    }

    int updateAthletesInfo();

    void showAthleteInfo(bool);
    void clearTableItems();

    inline void deleteUpdater() {
        if (updater != nullptr)
            delete updater;
        updater = nullptr;
    }

    void updateTable(QVector<QStringList> table, QStringList colName, QStringList rowName = QStringList(), int sortedBy=0);
    void addPathButton(QString name);

public slots:
    void clickTable(int row, int col);
    void updateMainProdressBar(int value);
    void updateAnalyseProgress(int value);
    void clickAthletePath();
    void clickLevel1Upper();

    void openDataBase();
    void chooseDataDirectory();

    void trainingAnalyserFinished(int trID);
    void updateTableSlot();

signals:
    void updateMainProdressBarStatus(QString text);

};

#endif // MAINWINDOW_H

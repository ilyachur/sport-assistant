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

#include "../wrappers/athletedb.h"
#include "../updaters/updater.h"

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
    QProgressBar *mainProdressBar = nullptr;
    QLabel *mainProdressBarStatus = nullptr;
    QProgressBar *additionalProdressBar = nullptr;
    QLabel *additionalProdressBarStatus = nullptr;

    AthleteDB athleteDB;

    QVector<QPushButton*> pathButtons;
    int tableLevel = -1;

    QString dataFolder;
    QString databaseName;

    Updater *updater = nullptr;

    int updateAthletesInfo();

    void showAthleteInfo(bool);

    inline void deleteUpdater() {
        if (updater != nullptr)
            delete updater;
        updater = nullptr;
    }

    void updateTable(QVector<QStringList> table, QStringList colName, QStringList rawName = QStringList(), int sortedBy=0);
    void addPathButton(QString name);

public slots:
    void clickTable(int row, int col);
    void updateMainProdressBar(int value);
    void choosePathButton(QString name);

signals:
    void updateMainProdressBarStatus(QString text);

};

#endif // MAINWINDOW_H
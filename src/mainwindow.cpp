#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ft = new FitParser("C:\\Study\\HSE\\sport-assistant\\test_data\\Ilya\\IceSkates\\28_02_strong_activity.fit");
    ft->run();
}

MainWindow::~MainWindow()
{
    delete ui;
}

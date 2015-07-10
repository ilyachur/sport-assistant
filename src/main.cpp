#include "forms/mainwindow.h"
#include <QApplication>

/**
 * @mainpage Sport assistant: main page
 * Sport assistent is a second version of CardioAnalyser. This version developing with using such technologies as C++ 11 and Qt.
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

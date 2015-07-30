#include "forms/mainwindow.h"
#include <QApplication>

/// @file main.cpp
/// @brief Contains entry point to application
/// @author Ilya Churaev ilyachur@gmail.com

/**
 * @mainpage Sport assistant: main page
 * Sport assistent is a second version of CardioAnalyser. This version developing with using such technologies as C++ 11 and Qt.
 */

int main(int argc, char *argv[])
{
    // Set format qDebug output
    qSetMessagePattern("%{file}(%{line}): %{message}");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

/**
 * @file Main.cpp
 * @author Yoan Tynakovski
 * @date 23.01.2024
 * @brief The main file
 *
 * This file contains the main function, which is the entry point of the application.
 * It initializes the QApplication and the MainWindow, and starts the main event loop.
 */

#include "mainwindow.h"

#include <QApplication>

/**
 * @brief The main entry point of the application.
 * @param argc The count of command-line arguments.
 * @param argv The command-line arguments.
 * @return Integer representing the exit status.
 *
 * This function initializes the QApplication object with command-line arguments,
 * creates the main window of the application, and enters the main event loop.
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

/**
 * @file MainWindow.h
 * @author Yoan Tynakovski
 * @date 23.01.2024
 * @brief File containing the MainWindow class definition.
 *
 * This file defines the MainWindow class, which is responsible for
 * setting up and visualizing the main user interface (UI) of the application.
 * The class inherits from QMainWindow and manages the application's main window,
 * including layout, widgets, and their interactions.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

/**
 * @class MainWindow
 * @brief The MainWindow class extends QMainWindow for the application's main UI.
 *
 * This class is responsible for initializing and displaying the main window
 * of the application. It sets up the user interface designed in the Qt Designer
 * and manages interactions within the main window.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

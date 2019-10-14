/**
* Author: Paul Muehleip
* Course: CS 3505-001 Fall 2019
* Assignment: A6 - Qt Simon Game
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "simonmodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:


private slots:
    void updateScoreDisplay(int value);
    void updateHighScoreDisplay(int value);

private:
    Ui::MainWindow *ui;
    SimonModel *simonModel;

};
#endif // MAINWINDOW_H

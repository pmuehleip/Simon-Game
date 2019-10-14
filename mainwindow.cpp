/**
* Author: Paul Muehleip
* Course: CS 3505-001 Fall 2019
* Assignment: A6 - Qt Simon Game
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <iostream>
#include "simonmodel.h"

using namespace std;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    simonModel = new SimonModel(parent);

    // Signal and Slot Connections
    connect(ui->simonPushButton, &QPushButton::pressed, simonModel, &SimonModel::start);
    connect(ui->redPushButton, &QPushButton::pressed, simonModel, &SimonModel::playRed);
    connect(ui->bluePushButton, &QPushButton::pressed, simonModel, &SimonModel::playBlue);
    connect(simonModel, &SimonModel::redButtonSignal, ui->redPushButton, &QPushButton::animateClick);
    connect(simonModel, &SimonModel::blueButtonSignal, ui->bluePushButton, &QPushButton::animateClick);
    connect(simonModel, &SimonModel::disableBlueRedButtonSignal, ui->redPushButton, &QPushButton::blockSignals);
    connect(simonModel, &SimonModel::disableBlueRedButtonSignal, ui->bluePushButton, &QPushButton::blockSignals);
    connect(simonModel, &SimonModel::disableSimonButtonSignal, ui->simonPushButton, &QPushButton::blockSignals);
    connect(simonModel, &SimonModel::updateProgressBarSignal, ui->progressBar, &QProgressBar::setValue);
    connect(simonModel, &SimonModel::updateScoreLcdSignal, this, &MainWindow::updateScoreDisplay);
    connect(simonModel, &SimonModel::updateHighScoreLcdSignal, this, &MainWindow::updateHighScoreDisplay);

    // Display light dance when first open application.
    simonModel->firstTimeOpenDisplay();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete simonModel;
}

// View Helper Methods

void MainWindow::updateScoreDisplay(int value) {
    ui->scoreLcd->display(value);
}

void MainWindow::updateHighScoreDisplay(int value) {
    ui->highScoreLcdNumber->display(value);
}

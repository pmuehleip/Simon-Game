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

    // Extra ui configuration.
    ui->simonPushButton->setMask(QRegion(QRect(-1,-1,300,300),QRegion::Ellipse));
    ui->simonPushButton->resize(300,300);

    // Signal and Slot Connections
    connect(ui->simonPushButton, &QPushButton::pressed, simonModel, &SimonModel::start);
    connect(ui->redPushButton, &QPushButton::pressed, simonModel, &SimonModel::playRed);
    connect(ui->bluePushButton, &QPushButton::pressed, simonModel, &SimonModel::playBlue);
    connect(simonModel, &SimonModel::redButtonSignal, ui->redPushButton, &QPushButton::animateClick); // Could block signal here.
    connect(simonModel, &SimonModel::blueButtonSignal, ui->bluePushButton, &QPushButton::animateClick);
    //connect(simonModel, &SimonModel::redButtonSignal, this, &MainWindow::mimickAnimateRedClick);
    //connect(simonModel, &SimonModel::blueButtonSignal, this, &MainWindow::mimickAnimateBlueClick);
    connect(simonModel, &SimonModel::setDownBlueRedButtonSignal, ui->redPushButton, &QPushButton::blockSignals);
    connect(simonModel, &SimonModel::setDownBlueRedButtonSignal, ui->bluePushButton, &QPushButton::blockSignals);
    connect(simonModel, &SimonModel::updateProgressBarSignal, ui->progressBar, &QProgressBar::setValue);
    connect(simonModel, &SimonModel::updateScoreLcdSignal, this, &MainWindow::updateDisplay);
    connect(simonModel, &SimonModel::updateHighScoreLcdSignal, this, &MainWindow::updateHighScoreDisplay);
    connect(simonModel, &SimonModel::disableSimonButtonSignal, ui->simonPushButton, &QPushButton::setDisabled);

    simonModel->firstTimeOpenDisplay();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete simonModel;
}

// View Helper Methods

void MainWindow::updateDisplay(int value) {
    ui->scoreLcd->display(value);
}

void MainWindow::updateHighScoreDisplay(int value) {
    ui->highScoreLcdNumber->display(value);
}

/*
void MainWindow::mimickAnimateRedClick(int msec) {
    QString style = "background-color: qradialgradient(cx:0.8, cy:0.8, radius: 0.7, fx:0.55, fy:0.55, stop:0 rgb(252, 233, 79), stop:1 rgba(204, 0, 0, 70%)); border-top-left-radius: 290px;";
    setStyleSheetRed(style);
    style = "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1,   stop:0 red, stop:1 rgba(204, 0, 0, 50%)); border-top-left-radius: 290px;";
    QTimer::singleShot(msec, std::bind(&MainWindow::setStyleSheetRed, this, style));
}

void MainWindow::mimickAnimateBlueClick(int msec) {
    QString style = "background-color: qradialgradient(cx:0.7, cy:0.7, radius: 0.7, fx:0.55, fy:0.55, stop:0 rgb(252, 233, 79), stop:1 rgba(0, 0, 255, 70%)); border-top-right-radius: 290px;";
    setStyleSheetBlue(style);
    style = "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1,   stop:0 blue, stop:1 rgba(0, 0, 255, 50%)); border-top-right-radius: 290px;";
    QTimer::singleShot(msec, std::bind(&MainWindow::setStyleSheetBlue, this, style));
}

void MainWindow::setStyleSheetRed(QString s) {
    ui->redPushButton->setStyleSheet(s);
}

void MainWindow::setStyleSheetBlue(QString s) {
    ui->bluePushButton->setStyleSheet(s);
}
*/

//void MainWindow::alternateFlash(int numFlashes) {
//    for(int i = 0; i < numFlashes; i++){
//        emit ui->redPushButton->animateClick(100*(i*2 + 1));
//        emit ui->bluePushButton->animateClick(200*(i + 1));
//    }
//}

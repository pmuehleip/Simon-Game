/**
* Author: Paul Muehleip & Chris Bordoy
* Course: CS 3505-001 Fall 2019
* Assignment: A6 - Qt Simon Game
*/

#ifndef SIMONMODEL_H
#define SIMONMODEL_H

#include <QMainWindow>
#include <QObject>
#include <string>

class SimonModel : public QMainWindow
{
    Q_OBJECT
public:
    explicit SimonModel(QWidget *parent = nullptr);
    void firstTimeOpenDisplay();

signals:
    void redButtonSignal(int duration);
    void blueButtonSignal(int duration);
    void disableBlueRedButtonSignal(bool disabled);
    void disableSimonButtonSignal(bool disabled);
    void updateScoreLcdSignal(int value);
    void updateProgressBarSignal(int percentage);
    void updateHighScoreLcdSignal(int value);

public slots:
    void start();
    void playRed();
    void playBlue();


private:
    int score;
    int highScore;
    int speed;
    std::vector<std::string> sequence;
    std::vector<std::string> played;

    void displayButton(std::string color, double interval, double duration);
    void playAMove(std::string color);
    void addToSequence();
    void reset();
    void stop();
    void showSequence(int speed);
    void endGameDisplay();

};

#endif // SIMONMODEL_H

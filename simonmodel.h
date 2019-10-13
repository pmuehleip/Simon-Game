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

    void playAMove(std::string color);

    void addToSequence();

    void reset();

    void start();

    void stop();

    std::vector<std::string> getSequence();

    void showSequence(int speed);

    void firstTimeOpenDisplay();

    void endGameDisplay();

    void playRed();

    void playBlue();

signals:

    void redButtonSignal(int duration);

    void blueButtonSignal(int duration);

    void setDownBlueRedButtonSignal(bool isDown);

    void updateScoreLcdSignal(int value);

    void updateProgressBarSignal(int percentage);

    void updateHighScoreLcdSignal(int value);

public slots:


private:
    int score;
    int highScore;
    int speed;
    std::vector<std::string> sequence;
    std::vector<std::string> played;


    void display(std::string color, double interval, double duration);

};

#endif // SIMONMODEL_H

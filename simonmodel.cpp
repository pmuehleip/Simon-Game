#include "simonmodel.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <QTimer>
#include <functional>
#include <algorithm>

using namespace std;

SimonModel::SimonModel(QWidget *parent) : QMainWindow(parent)
{
    score = 0;
    highScore = 0;
    speed = 1;
    srand(time(NULL));
}

void SimonModel::playAMove(string color) {
    played.push_back(color);
    cout << "played a move: " << color << endl;

    // end game
    if(played[played.size()-1] != sequence[played.size()-1]) {
        stop();
        cout << "End game: " << color << endl;
        return;
    }

    updateProgressBarSignal((100.0 * played.size()) / sequence.size());
    cout << "Progress %: " << (100.0 * played.size()) / sequence.size() << endl;

    // If end of sequence
    if(played.size() == sequence.size()) {
        played.clear();
        score++;
        speed++;
        emit updateScoreLcdSignal(score);
        highScore = max(score, highScore);
        emit updateHighScoreLcdSignal(highScore);
        QTimer::singleShot(200, this, emit bind(&SimonModel::updateProgressBarSignal, this, 0));
        addToSequence();
        showSequence(speed);
    }
}

void SimonModel::playRed() {
    playAMove("red");
}

void SimonModel::playBlue() {
    playAMove("blue");
}

void SimonModel::addToSequence() {
    int randomBinary = rand() % 2;
    if(randomBinary == 0) {
       sequence.push_back("red");
    } else {
       sequence.push_back("blue");
    }
}

void SimonModel::showSequence(int speed) {
    double speedFraction = 10.0 / (speed + 9.0);
    int oneSec = 1000.0;
    double startOffSet = oneSec;
    double time = oneSec * speedFraction;

    for(unsigned int i = 0; i < sequence.size(); i++) {
        double interval = time*i + startOffSet;
        if(sequence[i] == "red") {
            display("red", interval, time/2);
        } else {
            display("blue", interval, time/2);
        }
    }
    // Unblock signals after sequence is shown.
    QTimer::singleShot(time*sequence.size()+startOffSet, this, emit bind(&SimonModel::setDownBlueRedButtonSignal, this, false));
}

void SimonModel::firstTimeOpenDisplay() {

    // Alternating flashes.
    for(int i = 800; i < 1400; i+=150) {
        display("red", i, 75);
        display("blue", i+75, 75);
    }
    // Concurrent flashes.
    for(int i = 1400; i < 2000; i+=100) {
        display("red", i, 50);
        display("blue", i, 50);
    }

    // Unblock signals after first time display is shown.
    QTimer::singleShot(2500, this, emit bind(&SimonModel::setDownBlueRedButtonSignal, this, false));
}

void SimonModel::endGameDisplay() {
    // Alternating flashes.
    for(int i = 400; i < 2000; i+=200) {
        display("red", i, 100);
        display("blue", i+100, 100);
    }

    // Unblock signals after end game display is shown.
    QTimer::singleShot(2000, this, emit bind(&SimonModel::setDownBlueRedButtonSignal, this, false));
}

void SimonModel::display(string color, double interval, double duration) {
    emit setDownBlueRedButtonSignal(true);
    if(color == "red") {
        QTimer::singleShot(interval, this, emit bind(&SimonModel::redButtonSignal, this, duration));
    } else {
        QTimer::singleShot(interval, this, emit bind(&SimonModel::blueButtonSignal, this, duration));
    }
}

void SimonModel::reset() {
    sequence.clear();
    played.clear();
    score = 0;
    speed = 1;
    emit updateScoreLcdSignal(score);
    emit updateProgressBarSignal(0);

}

void SimonModel::start() {

    // TODO: Call reset, disable Simon button here, enable other buttons.
    reset();
    emit disableSimonButtonSignal(true);

    addToSequence();
    addToSequence();
    showSequence(speed);
}

void SimonModel::stop() {
    // TODO: do endDisplay, enable Simon button, and disable other buttons.
    endGameDisplay();
    emit disableSimonButtonSignal(false);

}

std::vector<std::string> SimonModel::getSequence() {
    return sequence;
}

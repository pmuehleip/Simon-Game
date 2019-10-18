/**
* Author: Paul Muehleip & Chris Bordoy
* Course: CS 3505-001 Fall 2019
* Assignment: A6 - Qt Simon Game
*/

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

    // end game
    if(played[played.size()-1] != sequence[played.size()-1]) {
        stop();
        return;
    }

    updateProgressBarSignal((100.0 * played.size()) / sequence.size());

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

// Display visual feedback back to the user of the current sequence.
void SimonModel::showSequence(int speed) {
    double oneSec = 1000.0;
    double startOffSet = oneSec;
    double speedFraction = 10.0 / (speed + 9.0);
    double time = oneSec * speedFraction;

    for(unsigned int i = 0; i < sequence.size(); i++) {
        double interval = time*i + startOffSet;
        if(sequence[i] == "red") {
            displayButton("red", interval, time/2);
        } else {
            displayButton("blue", interval, time/2);
        }
    }
    // Unblock signals after sequence is shown.
    QTimer::singleShot(time*sequence.size()+startOffSet, this, emit bind(&SimonModel::disableBlueRedButtonSignal, this, false));
}

void SimonModel::firstTimeOpenDisplay() {

    // Make the progress bar escalate and de-escalate.
    // Escalate:
    int startTime1 = 800;
    int endTime1 = 1400;
    int duration1 = endTime1 - startTime1;
    for(int i = startTime1; i <= endTime1; i+= 10) {
        double percentage = (100*(i-startTime1))/duration1;
        QTimer::singleShot(i, this, emit bind(&SimonModel::updateProgressBarSignal, this, percentage));
    }
    // De-escalate:
    int startTime2 = endTime1;
    int endTime2 = 2000;
    int duration2 = endTime2 - startTime2;
    for(int i = startTime2; i <= endTime2; i+= 10) {
        double percentage = (100*(i-startTime1))/(duration1+duration2-10);
        QTimer::singleShot(i, this, emit bind(&SimonModel::updateProgressBarSignal, this, 100-percentage));
    }

    // Alternating flashes.
    for(int i = 800; i < 1400; i+=150) {
        displayButton("red", i, 75);
        displayButton("blue", i+75, 75);
    }
    // Concurrent flashes.
    for(int i = 1400; i < 2000; i+=100) {
        displayButton("red", i, 50);
        displayButton("blue", i, 50);
    }
}

void SimonModel::endGameDisplay() {
    // Alternating flashes.
    for(int i = 400; i < 2000; i+=200) {
        displayButton("red", i, 100);
        displayButton("blue", i+100, 100);
    }
}

// This method is used to represent a single button being shown back to the user in the
// visual feedback sequence. It will be displayed for a duration of time in ms and played some
// amount of time in the future in ms specified by the interval.
void SimonModel::displayButton(string color, double interval, double duration) {
    emit disableBlueRedButtonSignal(true);
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
    reset();
    emit disableSimonButtonSignal(true);
    addToSequence();
    addToSequence();
    showSequence(speed);
}

void SimonModel::stop() {
    endGameDisplay();
    emit disableSimonButtonSignal(false);
    emit disableBlueRedButtonSignal(true);

}

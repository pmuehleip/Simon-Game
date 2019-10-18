/**
* Author: Paul Muehleip & Chris Bordoy
* Course: CS 3505-001 Fall 2019
* Assignment: A6 - Qt Simon Game
*/

#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

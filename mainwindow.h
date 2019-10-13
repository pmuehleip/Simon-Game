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

private:
    Ui::MainWindow *ui;
    SimonModel *simonModel;

    void updateDisplay(int value);
    void updateHighScoreDisplay(int value);

};
#endif // MAINWINDOW_H

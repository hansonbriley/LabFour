#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    timer(new QTimer),
    timerNYC(new QTimer)

{
    ui->setupUi(this);
    connect(timer, SIGNAL(timeout()),
            this, SLOT(setTime()));
    setTime();
    timer->start(1000);

    connect(timerNYC, SIGNAL(timeout()),
            this, SLOT(setNYCTime()));
    setNYCTime();
    timerNYC->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setTime()
{
    QTime time = QTime::currentTime();

    QString hour = time.toString("hh");
    QString minute = time.toString("mm");
    QString second = time.toString("ss");

    ui->hoursTime->display(hour);
    ui->minutesTime->display(minute);
    ui->secondsTime->display(second);
}

void MainWindow::setNYCTime()
{
    QDateTime time = QDateTime::currentDateTime();
    QDateTime timeNYC = time.toTimeZone(QTimeZone ("America/New_York"));


    QString hour = timeNYC.toString("hh");
    QString minute = timeNYC.toString("mm");
    QString second = timeNYC.toString("ss");

    ui->hourNYC->display(hour);
    ui->minuteNYC->display(minute);
    ui->secondNYC->display(second);
}


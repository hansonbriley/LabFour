#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    timer(new QTimer),
    timerNYC(new QTimer),
    httpManager(new HTTPManager)
{
    ui->setupUi(this);


    connect(timer, SIGNAL(timeout()),
            this, SLOT(setTime()));
    SetTime();
    timer->start(1000);

    connect(timerNYC, SIGNAL(timeout()),
            this, SLOT(setNYCTime()));
    SetNYCTime();
    timerNYC->start(1000);

    connect(httpManager, SIGNAL(ImageReady(QPixmap *)),
            this, SLOT(ProcessImage(QPixmap *)));
    SetMapImage();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetTime()
{
    QTime time = QTime::currentTime();

    QString hour = time.toString("hh");
    QString minute = time.toString("mm");
    QString second = time.toString("ss");

    ui->hoursTime->display(hour);
    ui->minutesTime->display(minute);
    ui->secondsTime->display(second);
}

void MainWindow::SetMapImage()
{
    httpManager->sendImageRequest();
}

void MainWindow::SetNYCTime()
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

void MainWindow::ProcessImage(QPixmap *image)
{
    ui->mapLabel->setPixmap(*image);
}



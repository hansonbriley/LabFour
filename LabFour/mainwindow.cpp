#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    timer(new QTimer),
    timerNYC(new QTimer),
    httpManager(new HTTPManager),
    myModel(new ToDoListModel(this))

{
    ui->setupUi(this);
    myModel->openFile("C:\\Users\\Brileys\\Documents\\toDoList.csv");
    ui->toDoList->setModel(myModel);
    SetMapImage();
    SetWeatherImage();

    connect(timer, SIGNAL(timeout()),
            this, SLOT(SetTime()));
    timer->start(1000);
    SetTime();

    connect(timerNYC, SIGNAL(timeout()),
            this, SLOT(SetNYCTime()));
    timerNYC->start(1000);
    SetNYCTime();

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

    if (hour.toInt() < 12) {
        ui->welcomeMessage->setText("Good Morning!");
    } else if (hour.toInt() < 18) {
        ui->welcomeMessage->setText("Good Afternoon!");
    } else
        ui->welcomeMessage->setText("Good Evening!");
}

void MainWindow::SetMapImage()
{
    connect(httpManager, SIGNAL(ImageReady(QPixmap *)),
            this, SLOT(ProcessImage(QPixmap *)));

    QString zipCode = ui->zipCodeEdit->text();
    httpManager->sendImageRequest(zipCode);
}

void MainWindow::SetWeatherImage()
{
    connect(httpManager, SIGNAL(WeatherJsonReady(QJsonObject *)),
            this, SLOT(ProcessWeatherJson(QJsonObject *)));

    QString zipCode = ui->zipCodeEdit->text();
    httpManager->sendWeatherRequest(zipCode);
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

void MainWindow::ProcessWeatherJson(QJsonObject *image)
{
    QString weatherInfo = image->value("weather").toArray()[0].toObject()["main"].toString();
    double temp = image->value("main").toObject()["temp"].toDouble();
    QString iconName = image->value("weather").toArray()[0].toObject()["icon"].toString();
    QString iconImage = ":/icons/" + iconName + ".png";
    int humidity = image->value("main").toObject()["humidity"].toInt();
    int tempRound = (int)qRound(temp);

    ui->humidityBox->setNum(humidity);
    ui->weatherTemp->setNum(tempRound);

    weatherIconImage.load(iconImage);
    weatherIconImage = weatherIconImage.scaled(ui->weatherIcon->size(), Qt::KeepAspectRatioByExpanding);
    ui->weatherIcon->setPixmap(weatherIconImage);

    qDebug() << weatherInfo;
    qDebug() << temp;
    qDebug() << iconName;
}



void MainWindow::on_zipCodeUpdate_clicked()
{
    QString zipCode = ui->zipCodeEdit->text();
    qDebug() << zipCode;
    httpManager->sendImageRequest(zipCode);
    httpManager->sendWeatherRequest(zipCode);
}



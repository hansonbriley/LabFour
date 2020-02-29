#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <QTimeZone>
#include <QDateTime>
#include <QJsonArray>

#include "httpmanager.h"
#include "todolistmodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void SetNYCTime();
    void SetTime();
    void SetMapImage();
    void SetWeatherImage();
    void ProcessImage(QPixmap *);
    void ProcessWeatherJson(QJsonObject *image);
    void on_zipCodeUpdate_clicked();

private:
    Ui::MainWindow *ui;
    ToDoListModel *myModel;
    QTimer *timer;
    QTimer *timerNYC;
    HTTPManager *httpManager;
    QPixmap weatherIconImage;
};
#endif // MAINWINDOW_H

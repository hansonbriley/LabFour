#include "httpmanager.h"


HTTPManager::HTTPManager(QObject *parent) :
    QObject(parent),
    imageDownloadManager(new QNetworkAccessManager(this)),
    weatherManager(new QNetworkAccessManager(this))
{
    connect(imageDownloadManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(ImageDownloadedHandler(QNetworkReply*)));

    connect(weatherManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(WeatherDownloadedHandler(QNetworkReply*)));
}

HTTPManager::~HTTPManager()
{
    delete imageDownloadManager;
    delete weatherManager;
}

void HTTPManager::sendImageRequest(QString zip)
{
    QString address = "https://dev.virtualearth.net/REST/V1/Imagery/Map/AerialWithLabels/"
            + zip +
            "/7?mapSize=431,331&mapLayer=TrafficFlow&format=png&key=Ah7fx0DSH-F8DmgbppyeKKl3c-dc9IuKrM9eaStS08d3UMPMel42Y6EYXFMTtZo8";
    QUrl url(address);
    QNetworkRequest request(url);
    imageDownloadManager->get(request);
    qDebug() << "Image requst sent to " << request.url();
}

void HTTPManager::sendWeatherRequest(QString zip)
{
    QString address = "https://api.openweathermap.org/data/2.5/weather?zip=" + zip +
            ",us&units=imperial&appid=9365f659f216fcd30cea3d1f3b36fc91";
    QUrl url(address);
    QNetworkRequest request(url);
    weatherManager->get(request);
    qDebug() << "Weather request sent to " << request.url();
}

void HTTPManager::ImageDownloadedHandler(QNetworkReply *reply)
{
    qDebug() << "Image reply has arrived";

    if (reply->error()) {
        qDebug() << reply->errorString();
        return;
    }

    qDebug() << "Download successful";
    QPixmap *image = new QPixmap();
    image->loadFromData(reply->readAll());
    reply->deleteLater();
    emit ImageReady(image);
}

void HTTPManager::WeatherDownloadedHandler(QNetworkReply *reply)
{
    qDebug() << "Weather reply has arrived";

    if (reply->error()) {
        qDebug() << reply->errorString();
        return;
    }

    qDebug() << "Download succesful";
    QString answer = reply->readAll();
    reply->deleteLater();

    QJsonDocument jsonResponse = QJsonDocument::fromJson(answer.toUtf8());
    QJsonObject *jsonObject = new QJsonObject(jsonResponse.object());
    emit WeatherJsonReady(jsonObject);
}



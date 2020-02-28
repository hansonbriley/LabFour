#include "httpmanager.h"


HTTPManager::HTTPManager(QObject *parent) :
    QObject(parent),
    imageDownloadManager(new QNetworkAccessManager(this))
{
    connect(imageDownloadManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(ImageDownloadedHandler(QNetworkReply*)));
}

HTTPManager::~HTTPManager()
{
    delete imageDownloadManager;
}

void HTTPManager::sendImageRequest(QString zip)
{
    QString address = "https://dev.virtualearth.net/REST/V1/Imagery/Map/AerialWithLabels/"
            + zip +
            "/7?mapSize=261,331&mapLayer=TrafficFlow&format=png&key=Ah7fx0DSH-F8DmgbppyeKKl3c-dc9IuKrM9eaStS08d3UMPMel42Y6EYXFMTtZo8";
    QUrl url(address);
    QNetworkRequest request(url);
    imageDownloadManager->get(request);
    qDebug() << "Image requst sent to " << request.url();
}

void HTTPManager::ImageDownloadedHandler(QNetworkReply *reply)
{
    qDebug() << "Image reply has arrived";
    qDebug() << QSslSocket::supportsSsl() << QSslSocket::sslLibraryBuildVersionString() << QSslSocket::sslLibraryVersionString();
    if (reply->error()) {
        qDebug() << reply->errorString();
        return;
    }

    qDebug() << "Download successful";
    QPixmap *image = new QPixmap();
    image->loadFromData(reply->readAll());

    emit ImageReady(image);
}

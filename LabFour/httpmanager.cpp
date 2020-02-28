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

void HTTPManager::sendImageRequest()
{
    QUrl url("https://i.imgur.com/59ODBB2.jpg");
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

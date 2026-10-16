#include "stockmanager.h"

StockManager::StockManager(QObject *parent): QObject(parent)
{
    m_networkManager = new QNetworkAccessManager(this);
}

void StockManager::getPrice(const QString& stock){

    QString apiKey = qEnvironmentVariable("TWELVE_DATA_API_KEY");

    QString urlString =
        "https://api.twelvedata.com/quote?symbol="
        + stock
        + "&apikey="
        + apiKey;

    QUrl url(urlString);

    QNetworkRequest request(url);

    QNetworkReply* reply = m_networkManager->get(request);

    connect(reply,
            &QNetworkReply::errorOccurred,
            this,
            [reply](QNetworkReply::NetworkError error)
            {
                qDebug() << "Network error:" << error;
                qDebug() << reply->errorString();
            });

    connect(reply, &QNetworkReply::finished,
            this, [this, reply, stock]()
            {
                QByteArray data = reply->readAll();

                QJsonDocument document =
                    QJsonDocument::fromJson(data);

                QJsonObject object =
                    document.object();

                double price =
                    object["close"].toString().toDouble();

                QString currency =
                    object["currency"].toString();

                emit priceReceived(stock, price, currency);

                reply->deleteLater();
            });

}

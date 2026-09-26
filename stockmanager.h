#ifndef STOCKMANAGER_H
#define STOCKMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrl>


class StockManager: public QObject
{
    Q_OBJECT

public:

    explicit StockManager(QObject *parent = nullptr);
    void getPrice(const QString& stock);

signals:

    void priceReceived(const QString& stock, const double price, const QString& currency);

private:

    QNetworkAccessManager* m_networkManager;
};

#endif // STOCKMANAGER_H

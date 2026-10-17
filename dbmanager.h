#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QMainWindow>
#include <QTextCursor>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QStandardPaths>
#include <QDir>
#include <memory>
#include <vector>
#include <map>
#include "main.h"

class Account;

class DBManager
{

public:
    DBManager();

    bool initializeDatabase();
    bool seedDemoData();

    std::unique_ptr<Account> getAccount(const int id);
    std::map <QString, Holdings> getHoldings(const int id);

    int authenticateUser(const QString &username, QString &password);
    bool persistData(const int id, const QString& stock, const double shares,
                     const double price, const QString &currency, const QString& order,
                     Account *acc);

private:
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H

#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QMainWindow>
#include <QTextCursor>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <memory>
#include <vector>
#include <map>
#include "main.h"

class Account;

class DBManager
{
public:
    DBManager();
    std::unique_ptr<Account> getAccount(const int id);
    std::map <QString, Holdings> getHoldings(const int id);
    void persistData(const int id, const QString& stock, const double shares,
                     const double total, const QString &currency, const QString& order,
                     Account *acc);

private:
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H

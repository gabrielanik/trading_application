#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QMainWindow>
#include <QTextCursor>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>
#include <memory>
#include <vector>

class Account;

class DBManager
{
public:
    std::unique_ptr<Account> getAccount(const int id);
};

#endif // DBMANAGER_H

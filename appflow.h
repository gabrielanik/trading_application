#ifndef APPFLOW_H
#define APPFLOW_H

#include "dbmanager.h"
#include <QObject>

class LogInWindow;
class MainWindow;
class DBManager;
class OrderWindow;
class Account;
class StockManager;

class AppFlow: public QObject {

    Q_OBJECT

public:
    explicit AppFlow(QObject *parent = nullptr );
    void start();

private slots:
    void handleLoginSuccess(const int userId, DBManager *dbManager);
    void handleOrderRequest(const QString &order, DBManager *dbManager, Account *account, StockManager *stockManager);
    void handleOrderExecution();

private:
    LogInWindow *loginW = nullptr;
    MainWindow *mainW = nullptr;
    OrderWindow *orderW = nullptr;
    DBManager m_db;
};

#endif // APPFLOW_H

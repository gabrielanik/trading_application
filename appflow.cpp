#include "appflow.h"
#include "loginwindow.h"
#include "mainwindow.h"
#include "orderwindow.h"
#include "account.h"

AppFlow::AppFlow(QObject *parent): QObject(parent) {}

void AppFlow::start(){
    loginW = new LogInWindow(&m_db);
    connect(loginW, &LogInWindow::loginSuccess,
            this, &AppFlow::handleLoginSuccess);
    loginW->show();
}

void AppFlow::handleLoginSuccess(const int userId, DBManager *dbManager){
    mainW = new MainWindow(userId, dbManager);

    mainW->setAttribute(Qt::WA_DeleteOnClose);
    connect(
        mainW,
        &QObject::destroyed,
        this,
        [this]() {
            mainW = nullptr;
        }
        );

    connect( mainW, &MainWindow::orderRequest,
            this, &AppFlow::handleOrderRequest);

    mainW->show();

    loginW->close();
    loginW->deleteLater();
    loginW = nullptr;

}

void AppFlow::handleOrderRequest(const QString &order, DBManager *dbManager, Account *account, StockManager *stockManager){
    orderW = new OrderWindow(order, dbManager, account, stockManager);

    orderW->setAttribute(Qt::WA_DeleteOnClose);

    connect(
        orderW,
        &QObject::destroyed,
        this,
        [this]() {
            orderW = nullptr;
        }
        );

    connect( orderW, &OrderWindow::orderExecuted,
            this, &AppFlow::handleOrderExecution);

    connect( orderW, &OrderWindow::back,
            this, &AppFlow::handleOrderExecution);

    orderW->show();

}

void AppFlow::handleOrderExecution(){

    orderW->close();
    orderW->deleteLater();
    orderW = nullptr;
    mainW->show();
}
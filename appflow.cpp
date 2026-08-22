#include "appflow.h"
#include "loginwindow.h"
#include "mainwindow.h"

AppFlow::AppFlow(QObject *parent): QObject(parent) {}

void AppFlow::start(){
    loginW = new LogInWindow(&m_db);
    connect(loginW, &LogInWindow::loginSuccess,
            this, &AppFlow::handleLoginSuccess);
    loginW->show();
}

void AppFlow::handleLoginSuccess(const int userId, DBManager* dbManager){
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

    mainW->show();

    loginW->close();
    loginW->deleteLater();
    loginW = nullptr;

}

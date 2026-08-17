#include "appflow.h"
#include "loginwindow.h"
#include "mainwindow.h"

AppFlow::AppFlow(QObject *parent): QObject(parent) {}

void AppFlow::start(){
    loginW = new LogInWindow();
    connect(loginW, &LogInWindow::loginSuccess,
            this, &AppFlow::handleLoginSuccess);
    loginW->show();
}

void AppFlow::handleLoginSuccess(const int userId){
    mainW = new MainWindow(userId);
    mainW->show();

    loginW->close();
    loginW->deleteLater();
}

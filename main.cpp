#include "mainwindow.h"
#include "loginwindow.h"
#include "appflow.h"
#include "passwordutils.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("gabrielanik");
    QCoreApplication::setApplicationName("TradingApplication");

    // generatePasswordData("8854");

    AppFlow appFlow;
    appFlow.start();

    return QCoreApplication::exec();
}

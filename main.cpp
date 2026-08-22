#include "mainwindow.h"
#include "loginwindow.h"
#include "appflow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    AppFlow appFlow;
    appFlow.start();

    return QCoreApplication::exec();
}

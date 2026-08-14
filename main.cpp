#include "mainwindow.h"
#include "loginwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LogInWindow lw;
    lw.show();
    // MainWindow w;
    //w.show();
    return QCoreApplication::exec();
}

#ifndef APPFLOW_H
#define APPFLOW_H

#include <QObject>

class LogInWindow;
class MainWindow;

class AppFlow: public QObject {

    Q_OBJECT

public:
    explicit AppFlow(QObject *parent = nullptr );
    void start();

private slots:
    void handleLoginSuccess(const int userId);

private:
    LogInWindow *loginW = nullptr;
    MainWindow *mainW = nullptr;
};

#endif // APPFLOW_H

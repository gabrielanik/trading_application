#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "user.cpp"


LogInWindow::LogInWindow(QWidget *parent, Qt::WindowFlags f)
    : QDialog(parent)
    , ui(new Ui::LogInWindow)
{
    ui->setupUi(this);
}

LogInWindow::~LogInWindow()
{
    delete ui;
}

void LogInWindow::on_logInButton_clicked(){

    QString uname = ui->passTextEdit->toPlainText();
    QString pass = ui->unameTextEdit->toPlainText();


}

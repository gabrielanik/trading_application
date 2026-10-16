#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "dbmanager.h"

LogInWindow::LogInWindow(DBManager *dbManager, QWidget *parent, Qt::WindowFlags f)
    : QDialog(parent),
    ui(new Ui::LogInWindow),
    m_db(dbManager)
{
    ui->setupUi(this);
}

LogInWindow::~LogInWindow()
{
    delete ui;
}

void LogInWindow::on_logInButton_clicked(){

    ui->invMessTextEdit->clear();

    QString uname = ui->unameLineEdit->text();
    QString pass = ui->passLineEdit->text();

    int id = m_db->authenticateUser(uname, pass);

    if (id != 0) {
        emit loginSuccess(id, m_db);
    } else {
        ui->invMessTextEdit->appendPlainText("Incorrect credentials.");
    }

}

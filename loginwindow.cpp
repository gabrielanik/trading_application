#include "loginwindow.h"
#include "ui_loginwindow.h"

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

int LogInWindow::authUser(const QString &uname, QString &pass){
    int id = 0;

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/Users/gabrielanik/trading_application/trading.db");

    if(!db.open()) {
        qDebug() << "Database error:"
                 << db.lastError().text();
    }

    QSqlQuery query(db);

    query.prepare("SELECT id FROM users WHERE username = :uname AND password = :pass");
    query.bindValue(":uname", uname);
    query.bindValue(":pass", pass);

    if(!query.exec()){
        qDebug() << "Query error:"
                 << query.lastError().text();
    }

    if(query.next()){
        id = query.value("id").toInt();
    }

    return id;
}

void LogInWindow::on_logInButton_clicked(){

    QString uname = ui->unameTextEdit->toPlainText();
    QString pass = ui->passTextEdit->toPlainText();

    int id = authUser(uname, pass);

    if (id != 0) {
        emit loginSuccess(id);
    } else {
        ui->invMessTextEdit->appendPlainText("Incorrect credentials.");
    }

}

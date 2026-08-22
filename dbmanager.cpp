#include "dbmanager.h"
#include "account.h"

std::unique_ptr<Account> DBManager::getAccount(const int id) {

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "mainwindow");
    db.setDatabaseName("/Users/gabrielanik/trading_application/trading.db");

    if(!db.open()) {
        qDebug() << "Database error:"
                 << db.lastError().text();
    }

    QSqlQuery query(db);

    query.prepare("SELECT * FROM accounts WHERE user_id = :id");
    query.bindValue(":id", id);

    if(!query.exec()){
        qDebug() << "Query error:"
                 << query.lastError().text();
    }

    if(query.next()){
        double balance = query.value("balance").toDouble();
        QString curr = query.value("currency").toString();

        return std::make_unique<Account>(
            id,
            balance,
            curr
            );
    }

    return nullptr;

}

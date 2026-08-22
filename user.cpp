#include "user.h"

int User::getId() const{
    return id;
}

int readUsers(const QString& uname, const QString& pass){

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

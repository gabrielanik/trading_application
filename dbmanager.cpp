#include "dbmanager.h"
#include "account.h"

DBManager::DBManager(){

    m_db = QSqlDatabase::addDatabase("QSQLITE", "trading");
    m_db.setDatabaseName("/Users/gabrielanik/trading_application/trading.db");

    if(!m_db.open()) {
        qDebug() << "Database error:"
                 << m_db.lastError().text();
    }
}

std::unique_ptr<Account> DBManager::getAccount(const int id) {

    QSqlQuery query(m_db);

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

std::map<QString, Holdings> DBManager::getHoldings(const int id){

    std::map<QString, Holdings> portfolio;

    QSqlQuery query(m_db);

    query.prepare( "SELECT * FROM portfolios WHERE user_id = :id" );
    query.bindValue(":id", id);

    if(!query.exec()){
        qDebug() << "Query error:"
                 << query.lastError().text();
    }

    while(query.next()){
        QString stock =
            query.value("stock").toString();

        Holdings holdings;

        holdings.shares =
            query.value("shares").toDouble();

        holdings.investment =
            query.value("investment").toDouble();

        holdings.currency =
            query.value("currency").toString();

        portfolio.emplace(stock, holdings);
    }

    return portfolio;

}

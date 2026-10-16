#include "dbmanager.h"
#include "account.h"
#include "passwordutils.h"

DBManager::DBManager(){

    QString dataPath =
        QStandardPaths::writableLocation(
            QStandardPaths::AppDataLocation
            );

    QDir().mkpath(dataPath);

    QString databasePath = dataPath + "/trading.db";

    m_db = QSqlDatabase::addDatabase("QSQLITE", "trading");
    m_db.setDatabaseName(databasePath);

    if(!m_db.open()) {
        qDebug() << "Database error:"
                 << m_db.lastError().text();
    }

    if(!initializeDatabase()){
       qDebug() << "Database initialization failed.";
    }

    if (!seedDemoData()) {
        qDebug() << "Demo data initialization failed";
    }
}

bool DBManager::initializeDatabase(){

    QSqlQuery query(m_db);

    if (!query.exec(
            "CREATE TABLE IF NOT EXISTS users ("
            "id INTEGER PRIMARY KEY, "
            "username TEXT NOT NULL UNIQUE, "
            "password_hash TEXT NOT NULL, "
            "password_salt TEXT NOT NULL"
            ")"
            )) {
        qDebug() << query.lastError().text();
        return false;
    }

    if (!query.exec(
            "CREATE TABLE IF NOT EXISTS accounts ("
            "user_id INTEGER PRIMARY KEY, "
            "balance REAL DEFAULT 0.0, "
            "currency TEXT NOT NULL, "
            "FOREIGN KEY(user_id) REFERENCES users(id)"
            ")"
            )) {
        qDebug() << query.lastError().text();
        return false;
    }

    if (!query.exec(
            "CREATE TABLE IF NOT EXISTS portfolios ("
            "user_id INTEGER NOT NULL, "
            "stock TEXT NOT NULL, "
            "shares REAL DEFAULT 0.0, "
            "investment REAL DEFAULT 0.0, "
            "currency TEXT NOT NULL, "
            "PRIMARY KEY(user_id, stock), "
            "FOREIGN KEY(user_id) REFERENCES users(id)"
            ")"
            )) {
        qDebug() << query.lastError().text();
        return false;
    }

    return true;
}

bool DBManager::seedDemoData(){

    QSqlQuery query(m_db);

    if (!query.exec("SELECT COUNT(*) FROM users")) {
        qDebug() << "Could not check users table:"
                 << query.lastError().text();
        return false;
    }

    if (!query.next()) {
        return false;
    }

    // If there's data, do not insert
    if (query.value(0).toInt() > 0) {
        return true;
    }

    if (!m_db.transaction()) {
        qDebug() << "Could not start demo data transaction:"
                 << m_db.lastError().text();
        return false;
    }

    query.prepare(
        "INSERT INTO users "
        "(id, username, password_hash, password_salt) "
        "VALUES (:id, :username, :hash, :salt)"
        );

    query.bindValue(":id", 1);
    query.bindValue(":username", "alex");

    query.bindValue(
        ":hash",
        "i7IwqhiAqDON+Fdv+kh0x8FeDfbpDIIYii+fGvKPgpY="
        );

    query.bindValue(
        ":salt",
        "m/4jcxj2s+S4/y3Hktpx/w=="
        );

    if (!query.exec()) {
        qDebug() << "Could not insert demo user:"
                 << query.lastError().text();

        m_db.rollback();
        return false;
    }

    query.prepare(
        "INSERT INTO accounts "
        "(user_id, balance, currency) "
        "VALUES (:id, :balance, :currency)"
        );

    query.bindValue(":id", 1);
    query.bindValue(":balance", 1000.00);
    query.bindValue(":currency", "USD");

    if (!query.exec()) {
        qDebug() << "Could not insert demo account:"
                 << query.lastError().text();

        m_db.rollback();
        return false;
    }

    query.prepare(
        "INSERT INTO portfolios "
        "(user_id, stock, shares, investment, currency) "
        "VALUES (:id, :stock, :shares, :investment, :currency)"
        );

    query.bindValue(":id", 1);
    query.bindValue(":stock", "AAPL");
    query.bindValue(":shares", 1.0);
    query.bindValue(":investment", 200.00);
    query.bindValue(":currency", "USD");

    if (!query.exec()) {
        qDebug() << "Could not insert demo holding:"
                 << query.lastError().text();

        m_db.rollback();
        return false;
    }

    if (!m_db.commit()) {
        qDebug() << "Could not commit demo data:"
                 << m_db.lastError().text();

        m_db.rollback();
        return false;
    }

    return true;
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

int DBManager::authenticateUser(const QString &username, QString &password){

    QSqlQuery query(m_db);

    query.prepare(
        "SELECT id, password_hash, password_salt "
        "FROM users "
        "WHERE username = :username"
        );

    query.bindValue(":username", username);

    if (!query.exec()) {
        qDebug() << query.lastError().text();
        return 0;
    }

    if (!query.next()) {
        return 0;
    }

    int id = query.value("id").toInt();

    QByteArray salt =
        QByteArray::fromBase64(
            query.value("password_salt")
                .toString()
                .toLatin1()
            );

    QByteArray storedHash =
        QByteArray::fromBase64(
            query.value("password_hash")
                .toString()
                .toLatin1()
            );

    QByteArray enteredHash =
        hashPassword(password, salt);

    if (enteredHash == storedHash) {
        return id;
    }

    return 0;
}

bool DBManager::persistData(const int id, const QString &stock, const double shares,
                            const double total, const QString &currency, const QString &order,
                            Account* acc){

    QSqlQuery query(m_db);

    const auto& portfolio = acc->getPortfolio();

    // BUY

    if(order == "Buy"){

        query.prepare( "UPDATE accounts "
                         "SET balance = balance - :total "
                          "WHERE user_id = :id" );

        query.bindValue(":id", id);
        query.bindValue(":total", total);

        if(!query.exec()){
            qDebug() << "Balance update failed:"
                     << query.lastError().text();
        }

        // Check if stock is already owned

        auto it = portfolio.find(stock);

        if(it == portfolio.end()){

            query.prepare( "INSERT INTO portfolios "
                            "(user_id, stock, shares, investment, currency) "
                             "VALUES (:id, :stock, :shares, :total, :currency)");

            query.bindValue(":shares", shares);
            query.bindValue(":total", total);
            query.bindValue(":stock", stock);
            query.bindValue(":id", id);
            query.bindValue(":currency", currency);


        } else{

            query.prepare( "UPDATE portfolios "
                             "SET shares = shares + :shares, "
                               "investment = investment + :total "
                                  "WHERE stock = :stock "
                                    "AND user_id = :id" );

            query.bindValue(":shares", shares);
            query.bindValue(":total", total);
            query.bindValue(":stock", stock);
            query.bindValue(":id", id);

        }

        if (!query.exec()) {
            qDebug() << "Portfolio update failed:"
                     << query.lastError().text();

            m_db.rollback();
            return false;

    // SELL

        } else if(order == "Sell"){

            auto it = portfolio.find(stock);

            if (it == portfolio.end()) {
                qDebug() << "No shares of this stock are owned.";

                m_db.rollback();
                return false;
            }

            const double ownedShares =
                it->second.shares;

            const double investment =
                it->second.investment;

            if (shares <= 0 || shares > ownedShares) {
                qDebug() << "Invalid number of shares.";

                m_db.rollback();
                return false;
            }


            // Average price originally paid per share
            const double averageBuyPrice =
                investment / ownedShares;

            // Cost basis belonging to the shares being sold
            const double costBasisSold =
                shares * averageBuyPrice;


        query.prepare( "UPDATE accounts "
                        "SET balance = balance + :total "
                          "WHERE user_id = :id" );

        query.bindValue(":id", id);
        query.bindValue(":total", total);

        if(!query.exec()){
            qDebug() << "Balance update failed:"
                     << query.lastError().text();

            m_db.rollback();
            return false;

        }

        query.prepare( "UPDATE portfolios "
                        "SET shares = shares - :shares, "
                          "investment = investment - :costBasisSold "
                            "WHERE stock = :stock "
                              "AND user_id = :id" );

        query.bindValue(":shares", shares);
        query.bindValue(":costBasisSold", costBasisSold);
        query.bindValue(":stock", stock);
        query.bindValue(":id", id);

        if(!query.exec()){
            qDebug() << "Query error:"
                     << query.lastError().text();

            m_db.rollback();
            return false;
        }

        } else {

            qDebug() << "Unknown order type:" << order;

            m_db.rollback();
            return false;
        }

        // COMMIT

        if(!m_db.commit()){

            qDebug() << "Transaction commit failed:"
                     << m_db.lastError().text();

            m_db.rollback();
            return false;
        }
    }

    return true;

}

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <map>
#include <vector>
#include <QString>

#include "main.h"

class Account {
private:
    const int id;
    double balance;
    QString currency;
    std::map <QString, Holdings> portfolio;

public:
    Account(const int i, double b, QString c): id(i), balance(b), currency(c){};

    void buy(const int userId, std::vector<Account> accounts, const QString& stock, double amount, double price, QString& action);
    void sell(const int userId, std::vector<Account> accounts, const QString& stock, double amount, double price, QString& action);

    int getId() const;
    double getBalance() const;
    QString getCurrency() const;
    std::map <QString, Holdings> getPortfolio() const;
    void setPortfolio(std::map <QString, Holdings>);

};


#endif // ACCOUNT_H

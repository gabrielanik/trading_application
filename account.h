#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <map>
#include <vector>
#include <QString>
#include <QDebug>

#include "main.h"

class Account {
private:
    const int id;
    double balance;
    QString currency;
    std::map <QString, Holdings> portfolio;

public:
    Account(const int i, double b, QString c): id(i), balance(b), currency(c){};

    void buy(const QString& stock, const double amount, const double price);
    void sell(const QString& stock, const double amount, const double price);

    int getId() const;
    double getBalance() const;
    QString getCurrency() const;
    const std::map <QString, Holdings>& getPortfolio() const;
    void setBalance(const double b);
    void setPortfolio(const std::map <QString, Holdings> p);

};


#endif // ACCOUNT_H

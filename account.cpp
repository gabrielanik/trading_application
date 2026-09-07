#include "account.h"

#include <string>
#include <map>
#include <vector>


void Account::buy(const int userId, std::vector<Account> accounts, const QString& stock, double amount, double price, QString& action){
    double total = amount*price;
    portfolio[stock].shares += amount;
    portfolio[stock].investment += total;
   // updateAccount(userId, accounts, action, stock, amount, total);
}

void Account::sell(const int userId, std::vector<Account> accounts, const QString& stock, double amount, double price, QString& action){
    double total = amount*price;
    portfolio[stock].shares -= amount;
    portfolio[stock].investment -= total;
    // updateAccount(userId, accounts, action, stock, amount, total);
}

int Account::getId() const{
    return id;
}

double Account::getBalance() const{
    return balance;
}

QString Account::getCurrency() const{
    return currency;
}

std::map <QString, Holdings> Account::getPortfolio() const{
    return portfolio;
}

void Account::setPortfolio(std::map <QString, Holdings> p){
    portfolio = p;
}



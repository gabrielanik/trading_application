#include "account.h"

#include <string>
#include <map>
#include <vector>


void Account::buy(const int userId, const QString& stock, const double amount, const double price){
    double total = amount*price;
    portfolio[stock].shares += amount;
    portfolio[stock].investment += total;

    // case when buying a new stock
}

void Account::sell(const int userId, const QString& stock, const double amount, const double price){
    double total = amount*price;
    portfolio[stock].shares -= amount;
    portfolio[stock].investment -= total;
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

void Account::setPortfolio(const std::map <QString, Holdings> p){
    portfolio = p;
}

void Account::setBalance(const double b){
    balance = b;
}



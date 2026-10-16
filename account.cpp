#include "account.h"

#include <string>
#include <map>
#include <vector>


void Account::buy(const QString& stock, const double amount, const double price){

    Holdings holdings;
    double shares;
    double total = amount*price;

    auto it = portfolio.find(stock);

    if (it == portfolio.end()) {
        Holdings holdings;
        holdings.shares = amount;
        holdings.investment = total;

        portfolio.insert({stock, holdings});
    }
    else {
        it->second.shares += amount;
        it->second.investment += total;
    }

    balance -= total;

}

void Account::sell(const QString& stock, const double amount, const double price){

    double averageBuyPrice =
        portfolio.at(stock).investment /
        portfolio.at(stock).shares;

    double costBasisSold =
        amount * averageBuyPrice;

    double saleProceeds = amount*price;

    portfolio[stock].shares -= amount;
    portfolio[stock].investment -= costBasisSold;

    balance += saleProceeds;
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

const std::map <QString, Holdings>& Account::getPortfolio() const{
    return portfolio;
}

void Account::setPortfolio(const std::map <QString, Holdings> p){
    portfolio = p;
}

void Account::setBalance(const double b){
    balance = b;
}



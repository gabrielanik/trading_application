#include "account.h"

#include <string>
#include <map>
#include <vector>


void Account::buy(const int userId, std::vector<Account> accounts, const std::string& stock, double amount, double price, std::string& action){
    double total = amount*price;
    portfolio[stock].shares += amount;
    portfolio[stock].value += total;
   // updateAccount(userId, accounts, action, stock, amount, total);
}

void Account::sell(const int userId, std::vector<Account> accounts, const std::string& stock, double amount, double price, std::string& action){
    double total = amount*price;
    portfolio[stock].shares -= amount;
    portfolio[stock].value -= total;
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

std::map <std::string, Holdings> Account::getPortfolio() const{
    return portfolio;
}

void Account::setPortfolio(std::map <std::string, Holdings> p){
    portfolio = p;
}



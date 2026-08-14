#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <map>
#include <vector>

#include "main.h"

class Account {
private:
    const int id;
    double balance;
    std::map <std::string, Holdings> portfolio;

public:
    Account(const int i, double b): id(i), balance(b){};

    void buy(const int userId, std::vector<Account> accounts, const std::string& stock, double amount, double price, std::string& action);
    void sell(const int userId, std::vector<Account> accounts, const std::string& stock, double amount, double price, std::string& action);

    int getId() const;
    double getBalance() const;
    std::map <std::string, Holdings> getPortfolio() const;
    void setPortfolio(std::map <std::string, Holdings>);

};

std::vector<Account> readAccounts(const std::string& filename);
void updateAccounts(const int userId, std::vector<Account> accounts, const std::string& action, const std::string& st, double amount, double val);


#endif // ACCOUNT_H

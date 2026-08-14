#include "account.h"

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include "account.h"

std::vector<Account> readAccounts(const std::string& filename){
    std::vector<Account> accounts;
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        std::cerr << "Could not open file '" << filename << "'\n";
    }

    std::string line;
    for (int i = 0; std::getline(fin, line); i++) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string userId, balance;

        if (!std::getline(ss, userId, ',')) continue;
        if (!std::getline(ss, balance, ',')) continue;
        if (userId.empty() || balance.empty()) continue;

        int id = std::stoi(userId);
        double bal = std::stod(balance);
        accounts.emplace_back(id, bal);

        std::string stock, shares, investment;
        std::map<std::string, Holdings> portf;

        while(std::getline(ss, stock, ',')){
            if (!std::getline(ss, shares, ',')) continue;
            if (!std::getline(ss, investment, ',')) continue;
            if (shares.empty() || investment.empty()) continue;
            double shar = std::stod(shares);
            double inv = std::stod(investment);

            Holdings hol;
            hol.shares = shar;
            hol.value = inv;
            portf[stock] = hol;

            accounts[i].setPortfolio(portf);
        }
    }

    return accounts;
}

void updateAccounts(const int userId, std::vector<Account> accounts, const std::string& action, const std::string& st, double amount, double val){
    std::ofstream fout(accsNewFile);
    if (!fout) {
        std::cout << "File could not open\n";
    }
    for(int i = 0; i < accounts.size(); i++){
        std::vector<std::string> portfs;
        std::vector<std::string> stocks;
        std::string stock;
        double shares;
        double value;
        int id = accounts[i].getId();
        double balance = accounts[i].getBalance();
        std::string ids = std::to_string(id);
        std::string bals = std::to_string(balance);
        std::vector<std::string> accs = {ids, bals};
        std::map<std::string, Holdings> portfolio = accounts[i].getPortfolio();

        for(auto [s, h]: portfolio){
            stock = s;
            shares = h.shares;
            value = h.value;
            if(stock == st && id == userId){
                if(action == "buy"){
                    shares += amount;
                    value += val;
                } else if(action == "sell"){
                    shares -= amount;
                    value -= val;
                }
            }
            std::string sharess = std::to_string(shares);
            std::string values = std::to_string(value);
            portfs.push_back(stock);
            portfs.push_back(sharess);
            portfs.push_back(values);
            stocks.push_back(stock);
        }

        for(int i = 0; i < stocks.size(); i++){
            if(stocks[i] != st && id == userId && i == stocks.size() - 1){
                stock = st;
                std::string amounts = std::to_string(amount);
                std::string vals = std::to_string(val);
                portfs.push_back(stock);
                portfs.push_back(amounts);
                portfs.push_back(vals);
                break;
            }
        }

        accs.insert(accs.end(),portfs.begin(),portfs.end());
        int sizes = accs.size();

        for(int i = 0; i < sizes - 1; i++){
            fout << accs[i] << ",";
        }
        fout << accs[sizes - 1] << std::endl;
    }
    remove(accsFile);
    rename(accsNewFile, accsFile);
}

void Account::buy(const int userId, std::vector<Account> accounts, const std::string& stock, double amount, double price, std::string& action){
    double total = amount*price;
    portfolio[stock].shares += amount;
    portfolio[stock].value += total;
    updateAccounts(userId, accounts, action, stock, amount, total);
}

void Account::sell(const int userId, std::vector<Account> accounts, const std::string& stock, double amount, double price, std::string& action){
    double total = amount*price;
    portfolio[stock].shares -= amount;
    portfolio[stock].value -= total;
    updateAccounts(userId, accounts, action, stock, amount, total);
}

int Account::getId() const{
    return id;
}

double Account::getBalance() const{
    return balance;
}

std::map <std::string, Holdings> Account::getPortfolio() const{
    return portfolio;
}

void Account::setPortfolio(std::map <std::string, Holdings> p){
    portfolio = p;
}



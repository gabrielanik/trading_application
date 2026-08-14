#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

#include "user.h"

int user::getId() const{
    return id;
}

std::string user::getUsername() const{
    return username;
}

std::string user::getPassword() const{
    return password;
}

std::vector<user> readUsers(const std::string& filename){
    std::vector<user> users;
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        std::cerr << "Could not open file '" << filename << "'\n";
    }

    std::string line;
    while (std::getline(fin, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string userId, username, password;

        // Split by comma
        if (!std::getline(ss, userId, ',')) continue;
        if (!std::getline(ss, username, ',')) continue;
        if (!std::getline(ss, password, ',')) continue;

        if (userId.empty() || username.empty() || password.empty()) continue;

        int id = std::stoi(userId);
        users.emplace_back(id, username, password);
    }

    return users;

}

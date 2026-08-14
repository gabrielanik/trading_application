#ifndef USER_H
#define USER_H

#include <string>
#include <map>
#include <vector>

#include "main.h"

class user {
private:
    const int id;
    std::string username;
    std::string password;

public:
    user(const int i, const std::string& u, const std::string& p): id(i), username(u), password(p){};

    int getId() const;
    std::string getUsername() const;
    std::string getPassword() const;

};

std::vector<user> readUsers(const std::string& filename);

#endif // USER_H

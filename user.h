#ifndef USER_H
#define USER_H

#include "main.h"

#include <QDialog>
#include <QTextCursor>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>

class User {
private:
    const int id;

public:
    explicit User(const int i): id(i){};
    ~User();

    int getId() const;

};

int authUser(const QString& uname, QString& pass);

#endif // USER_H

#ifndef MAIN_H
#define MAIN_H

#include <string>
#include <QObject>
#include <QString>
#ifndef CONSTANTS
#define CONSTANTS

inline constexpr const char* usersFile = "users.csv";
inline constexpr const char* accsFile = "accounts.csv";
inline constexpr const char* accsNewFile = "accountsnew.csv";

#endif

struct Holdings {
    double shares;
    double investment;
    QString currency;
};

#endif // MAIN_H

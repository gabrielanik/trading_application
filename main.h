#ifndef MAIN_H
#define MAIN_H

#include <string>
#include <QObject>
#ifndef CONSTANTS
#define CONSTANTS

inline constexpr const char* usersFile = "users.csv";
inline constexpr const char* accsFile = "accounts.csv";
inline constexpr const char* accsNewFile = "accountsnew.csv";

#endif

struct Holdings {
    double shares;
    double value;
};

// prices from 14.03.2026
inline const std::map<std::string, double> prices{
                                                  {"APC", 220.70},
                                                  {"NVD", 158.60},
                                                  {"VUAA", 111.99},
                                                  };


#endif // MAIN_H

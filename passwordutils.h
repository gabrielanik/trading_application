#ifndef PASSWORDUTILS_H
#define PASSWORDUTILS_H

#include <QString>
#include <QByteArray>

void generatePasswordData(const QString &password);
QByteArray hashPassword(const QString &password, const QByteArray &salt);


#endif // PASSWORDUTILS_H

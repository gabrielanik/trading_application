#include "passwordutils.h"

#include <QCryptographicHash>
#include <QPasswordDigestor>
#include <QRandomGenerator>
#include <QDebug>

void generatePasswordData(const QString &password){

    QByteArray salt(16, 0);

    for(int i = 0; i < salt.size(); ++i){
        salt[i] = static_cast<char>(
            QRandomGenerator::global()->bounded(256)
        );
    }

    QByteArray hash = QPasswordDigestor::deriveKeyPbkdf2(
                        QCryptographicHash::Sha256,
                        password.toUtf8(),
                        salt,
                        200000,
                        32
        );

    qDebug() << "Salt: " << salt.toBase64();
    qDebug() << "Hash: " << hash.toBase64();

}

QByteArray hashPassword(const QString &password, const QByteArray &salt){
    return QPasswordDigestor::deriveKeyPbkdf2(
        QCryptographicHash::Sha256,
        password.toUtf8(),
        salt,
        200000,
        32
        );
}

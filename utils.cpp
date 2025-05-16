#include "utils.h"
#include <QCryptographicHash>

// Реализация функции хэширования пароля
QString hashPassword(const QString &password) {
    QByteArray hash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
    return hash.toHex();
}

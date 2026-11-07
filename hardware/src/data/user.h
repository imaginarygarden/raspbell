#ifndef USER_H
#define USER_H

#include <QString>
#include <QtNumeric>

struct User {
    qint64 id{};
    QString username{};
    QString password{};
};

#endif

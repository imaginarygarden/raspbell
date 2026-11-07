#ifndef LOG_H
#define LOG_H

#include <QtNumeric>
#include <QByteArray>

struct Log {
    qint64 id{};
    QByteArray imageBase64{};
    qint64 timestamp{};
};

#endif

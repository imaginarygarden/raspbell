#include "qdatabase.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QDateTime>

QDatabase::~QDatabase() {
    if (QDatabase::isConnected()) {
        m_db.close();
    }
}

QDatabase::QDatabaseConnResult QDatabase::connect(
    const QString& path) noexcept {
    if (QDatabase::isConnected()) {
        return QDatabaseConnResult::ALREADY_CONNECTED;
    }

    m_db.setDatabaseName(path);

    const bool successfulStartup{m_db.open() && createTables()};

    if (!successfulStartup) {
        return QDatabaseConnResult::FAILED;
    }

    m_status = QDatabaseStatus::CONNECTED;
    return QDatabaseConnResult::SUCCESS;
}

std::optional<User> QDatabase::getUser(const QString& username) noexcept {
    if (QDatabase::isConnected()) {
        return std::nullopt;
    }

    QString statement{
        "SELECT id, username, password FROM users "
        "WHERE username = (:username)"};

    auto query = prepare(statement);

    if (!query) {
        return std::nullopt;
    }

    int idIndex{query->record().indexOf("id")};
    int usernameIndex{query->record().indexOf("username")};
    int passwordIndex{query->record().indexOf("password")};

    query->bindValue(":username", username);

    if (!query->next()) {
        return std::nullopt;
    }

    qint64 idField{query->value(idIndex).toLongLong()};
    QString usernameField{query->value(usernameIndex).toString()};
    QString passwordField{query->value(passwordIndex).toString()};

    return User{
        .id = idField,
        .username = usernameField,
        .password = passwordField,
    };
}

bool QDatabase::addUser(const User& user) noexcept {
    if (QDatabase::isConnected()) {
        return false;
    }

    QString statement{
        "INSERT INTO users "
        "(username, password)"
        "VALUES (:username, :password)"};

    auto query = prepare(statement);

    if (!query) {
        return false;
    }

    query->bindValue(":username", user.username);
    query->bindValue(":password", user.password);

    return query->exec();
}

bool QDatabase::deleteUser(qint64 id) noexcept {
    if (QDatabase::isConnected()) {
        return false;
    }

    QString statement{
        "DELETE FROM users "
        "WHERE id = (:id)"};

    auto query = prepare(statement);

    if (!query) {
        return false;
    }

    query->bindValue(":id", id);

    return query->exec();
}

std::optional<QList<Log>> QDatabase::getLogs(quint64 limit) noexcept {
    if (QDatabase::isConnected()) {
        return std::nullopt;
    }

    QString statement{"SELECT id, imageBase64, timestamp FROM logs"};

    auto query = prepare(statement);

    if (!query) {
        return std::nullopt;
    }

    int idIndex{query->record().indexOf("id")};
    int imageBase64Index{query->record().indexOf("imageBase64")};
    int timestampIndex{query->record().indexOf("timestamp")};

    quint64 iterator{};
    QList<Log> result{};
    bool noLimit{limit == 0};

    while (query->next() && (noLimit || iterator < limit)) {
        qint64 idField{query->value(idIndex).toLongLong()};
        QByteArray imageBase64Field{
            query->value(imageBase64Index).toByteArray(),
        };
        qint64 timestampField{query->value(timestampIndex).toLongLong()};

        Log log{
            .id = idField,
            .imageBase64 = imageBase64Field,
            .timestamp = timestampField,
        };

        result.append(log);
        ++iterator;
    }

    return result;
}

bool QDatabase::addLog(const Log& log) noexcept {
    if (QDatabase::isConnected()) {
        return false;
    }

    QString statement{
        "INSERT INTO logs "
        "(imageBase64, timestamp)"
        "VALUES (:imageBase64, :timestamp)"};

    auto query = prepare(statement);

    if (!query) {
        return false;
    }

    query->bindValue(":imageBase64", log.imageBase64);
    query->bindValue(":timestamp", log.timestamp);

    return query->exec();
}

bool QDatabase::deleteLog(qint64 id) noexcept {
    if (QDatabase::isConnected()) {
        return false;
    }

    QString statement{
        "DELETE FROM logs "
        "WHERE id = (:id)"};

    auto query = prepare(statement);

    if (!query) {
        return false;
    }

    query->bindValue(":id", id);

    return query->exec();
}

std::optional<QSqlQuery> QDatabase::prepare(
    const QString& query) const noexcept {
    QSqlQuery candidate{m_db};

    if (!candidate.prepare(query)) {
        return std::nullopt;
    }

    return candidate;
}

bool QDatabase::exec(const QString& query) const noexcept {
    auto candidate = prepare(query);

    if (!candidate) {
        return false;
    }

    return candidate->exec();
}

bool QDatabase::createTables() const noexcept {
    if (QDatabase::isConnected()) {
        return false;
    }

    QString usersQuery{
        "CREATE TABLE IF NOT EXISTS users"
        "(id INTEGER NOT NULL PRIMARY KEY, "
        "username VARCHAR(256) NOT NULL UNIQUE, "
        "password VARCHAR(256) NOT NULL) ",
    };

    QString logsQuery{
        "CREATE TABLE IF NOT EXISTS logs"
        "(id INTEGER NOT NULL PRIMARY KEY, "
        "imageBase64 BLOB NOT NULL, "
        "timestamp INTEGER NOT NULL) ",
    };

    return exec(usersQuery) && exec(logsQuery);
}

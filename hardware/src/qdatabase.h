#ifndef QDATABASE_H
#define QDATABASE_H

#include <QObject>
#include <QSqlDatabase>

#include <string>

#include "data/user.h"
#include "data/log.h"

class QDatabase final : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY(QDatabase)

   public:
    enum class QDatabaseStatus : quint8 { CLOSED, CONNECTED };
    enum class QDatabaseConnResult : quint8 {
        FAILED,
        SUCCESS,
        ALREADY_CONNECTED,
    };

    explicit QDatabase(QObject* parent = nullptr) noexcept : QObject{parent} {}
    ~QDatabase() final;

    [[nodiscard]]
    QDatabaseConnResult connect(
        const QString& path = QDatabase::DEFAULT_PATH.c_str()) noexcept;

    [[nodiscard]]
    QDatabaseStatus status() const noexcept {
        return m_status;
    }

    [[nodiscard]]
    std::optional<User> getUser(const QString& username) noexcept;

    [[nodiscard]]
    bool addUser(const User& user) noexcept;

    [[nodiscard]]
    bool deleteUser(qint64 id) noexcept;

    [[nodiscard]]
    std::optional<QList<Log>> getLogs(quint64 limit = 0) noexcept;

    [[nodiscard]]
    bool addLog(const Log& log) noexcept;

    [[nodiscard]]
    bool deleteLog(qint64 id) noexcept;

   private:
    static constexpr std::string DEFAULT_PATH{"data"};

    QSqlDatabase m_db{QSqlDatabase::addDatabase("QSQLITE")};
    QDatabaseStatus m_status{QDatabaseStatus::CLOSED};

    [[nodiscard]]
    bool isConnected() const noexcept {
        return m_db.isOpen();
    }

    [[nodiscard]]
    std::optional<QSqlQuery> prepare(const QString& query) const noexcept;

    [[nodiscard]]
    bool exec(const QString& query) const noexcept;

    [[nodiscard]]
    bool createTables() const noexcept;
};

#endif

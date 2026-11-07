#ifndef QDATABASE_H
#define QDATABASE_H

#include <QObject>
#include <QSqlDatabase>

#include <string>

class QDatabase final : public QObject {
    Q_OBJECT

   public:
    enum class QDatabaseStatus : quint8 { CLOSED, CONNECTED };
    enum class QDatabaseConnResult : quint8 {
        FAILED,
        SUCCESS,
        ALREADY_CONNECTED,
    };

    explicit QDatabase(QObject* parent = nullptr) noexcept : QObject{parent} {}

    [[nodiscard]]
    QDatabaseConnResult connect(
        const QString& path = QDatabase::DEFAULT_PATH.c_str()) noexcept;

    [[nodiscard]]
    QDatabaseStatus status() const noexcept {
        return m_status;
    }

   private:
    static constexpr std::string DEFAULT_PATH{"data"};

    QSqlDatabase m_db{QSqlDatabase::addDatabase("QSQLITE")};
    QDatabaseStatus m_status{QDatabaseStatus::CLOSED};

    [[nodiscard]]
    bool isConnected() const noexcept {
        return m_status == QDatabaseStatus::CONNECTED && m_db.isOpen();
    }
};

#endif

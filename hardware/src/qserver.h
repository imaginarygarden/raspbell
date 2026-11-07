#ifndef QSERVER_H
#define QSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QHttpServer>

#include "qdatabase.h"

class QServer final : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY(QServer)

   public:
    explicit QServer(QObject* parent = nullptr) noexcept : QObject{parent} {}

    enum class QServerStatus : quint8 { UNCONFIGURED, CONFIGURED };
    enum class QServerConfResult : quint8 {
        SUCCESS,
        FAILED,
        ALREADY_CONFIGURED,
    };

    [[nodiscard]]
    QServerConfResult setup() noexcept;

    [[nodiscard]]
    std::optional<quint16> port() const noexcept {
        if (isConfigured()) {
            return m_tcp.serverPort();
        }

        return std::nullopt;
    }

    [[nodiscard]]
    QServerStatus status() const noexcept {
        return m_status;
    }

   private:
    static constexpr quint16 DEFAULT_PORT{5003};

    QTcpServer m_tcp{this};
    QHttpServer m_server{this};
    QDatabase m_db{this};

    QServerStatus m_status{QServerStatus::UNCONFIGURED};

    [[nodiscard]]
    bool setupDatabase() noexcept;

    [[nodiscard]]
    bool setupRoutes() noexcept;

    [[nodiscard]]
    bool setupServer() noexcept;

    [[nodiscard]]
    bool isConfigured() const noexcept {
        return m_status == QServerStatus::CONFIGURED && m_tcp.isListening();
    }
};

#endif

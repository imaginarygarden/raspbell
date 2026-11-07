#include "qserver.h"

#include <QApplication>

bool QServer::setupDatabase() noexcept {
    return m_db.connect() == QDatabase::QDatabaseConnResult::SUCCESS &&
           m_db.status() == QDatabase::QDatabaseStatus::CONNECTED;
}

bool QServer::setupRoutes() noexcept {
    m_server.route("/", []() { return "hello world"; });

    return true;
}

bool QServer::setupServer() noexcept {
    return m_tcp.listen(QHostAddress::LocalHost, QServer::DEFAULT_PORT) &&
           m_server.bind(&m_tcp);
}

QServer::QServerConfResult QServer::setup() noexcept {
    if (isConfigured()) {
        return QServerConfResult::ALREADY_CONFIGURED;
    }

    const bool configStatus{setupDatabase() && setupRoutes() && setupServer()};

    if (configStatus) {
        m_status = QServerStatus::CONFIGURED;

        qDebug() << QApplication::translate(
                        "QServer",
                        "Running on http://127.0.0.1:%1 (Press CTRL+C to quit)")
                        .arg(m_tcp.serverPort());

        return QServerConfResult::SUCCESS;
    }

    return QServerConfResult::FAILED;
}

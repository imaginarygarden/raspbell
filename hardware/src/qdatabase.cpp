#include "qdatabase.h"

QDatabase::QDatabaseConnResult QDatabase::connect(
    const QString& path) noexcept {
    if (QDatabase::isConnected()) {
        return QDatabaseConnResult::ALREADY_CONNECTED;
    }

    m_db.setDatabaseName(path);

    if (!m_db.open()) {
        return QDatabaseConnResult::FAILED;
    }

    return QDatabaseConnResult::SUCCESS;
}

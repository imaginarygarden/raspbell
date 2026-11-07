#ifndef QPASSWORDHASHER_H
#define QPASSWORDHASHER_H

#include <QObject>
#include <QRandomGenerator>
#include <QCryptographicHash>

class QPasswordHasher : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY(QPasswordHasher)

   public:
    explicit QPasswordHasher(QObject* parent = nullptr) : QObject{parent} {}

    [[nodiscard]]
    QString hash(const QString& password) noexcept;

    [[nodiscard]]
    bool compare(const QString& password, const QString& hash) noexcept;

   private:
    using HashParts = QPair<QString, QString>;

    static constexpr quint8 DEFAULT_SEED_LENGTH{12};

    static constexpr QCryptographicHash::Algorithm DEFAULT_ALGORITHM{
        QCryptographicHash::Sha256,
    };

    [[nodiscard]]
    static std::optional<HashParts> parseHash(const QString& hash) noexcept;

    QRandomGenerator m_random{QRandomGenerator::securelySeeded()};
    QCryptographicHash m_hasher{DEFAULT_ALGORITHM};

    [[nodiscard]]
    QString baseHash(const QString& password, const QString& seed) noexcept;

    [[nodiscard]]
    QString baseSeed(quint8 length = DEFAULT_SEED_LENGTH) noexcept;
};

#endif

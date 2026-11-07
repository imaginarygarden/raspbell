#include "qpasswordhasher.h"

QString QPasswordHasher::hash(const QString& password) noexcept {
    return baseHash(password, baseSeed());
}

bool QPasswordHasher::compare(const QString& password,
                              const QString& hash) noexcept {
    const std::optional<HashParts> parsedParts{parseHash(hash)};

    if (!parsedParts) {
        return false;
    }

    const auto& [seed, _password] = *parsedParts;

    Q_UNUSED(_password);

    const QString candidateHash{baseHash(password, seed)};

    return candidateHash == hash;
}

std::optional<QPasswordHasher::HashParts> QPasswordHasher::parseHash(
    const QString& hash) noexcept {
    const QStringList list{hash.split("$")};

    if (list.length() != 2) {
        return std::nullopt;
    }

    return HashParts{list[0], list[1]};
}

QString QPasswordHasher::baseHash(const QString& password,
                                  const QString& seed) noexcept {
    m_hasher.reset();

    const QString fullInput{
        QString{"%1$%2"}.arg(seed, password),
    };

    m_hasher.addData(fullInput.toUtf8());

    const QString hash{m_hasher.result()};

    return hash;
}

QString QPasswordHasher::baseSeed(quint8 length) noexcept {
    const QString possibleCharacters{
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"};

    QString seed{};

    for (quint8 i = 0; i < length; ++i) {
        qint64 index{m_random.bounded(possibleCharacters.length())};
        QChar nextChar{possibleCharacters.at(index)};

        seed.append(nextChar);
    }

    return seed;
}

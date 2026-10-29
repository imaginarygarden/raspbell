#ifndef LOG_H
#define LOG_H

#include <optional>
#include <string>

#include <sqlite_orm/sqlite_orm.h>

struct Log {
    int id = 0;
    std::string image;
    std::optional<std::string> timestamp;

    static auto columns() {
        static const auto columns = sqlite_orm::columns(&Log::image);

        return columns;
    }
};

#endif

#ifndef DEVICE_H
#define DEVICE_H

#include "sqlite_orm/sqlite_orm.h"
#include <string>

struct Device {
    int id = 0;
    std::string name;
    std::string password;

    static auto columns() {
        static const auto columns =
            sqlite_orm::columns(&Device::name, &Device::password);

        return columns;
    }
};

#endif

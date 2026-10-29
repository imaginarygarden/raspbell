#ifndef STORE_H
#define STORE_H

#include "data/log.h"
#include "sqlite_orm/sqlite_orm.h"
#include "data/device.h"

class Store {
   public:
    static auto instance() noexcept {
        static auto storage(sqlite_orm::make_storage(
            "db.sqlite",
            sqlite_orm::make_table(
                "devices",
                sqlite_orm::make_column(
                    "id", &Device::id,
                    sqlite_orm::primary_key().autoincrement()),
                sqlite_orm::make_column("name", &Device::name),
                sqlite_orm::make_column("password", &Device::password)),
            sqlite_orm::make_table(
                "logs",
                sqlite_orm::make_column(
                    "id", &Log::id, sqlite_orm::primary_key().autoincrement()),
                sqlite_orm::make_column("image", &Log::image),
                sqlite_orm::make_column(
                    "timestamp", &Log::timestamp,
                    sqlite_orm::default_value(
                        sqlite_orm::datetime("now", "localtime"))))));

        return storage;
    }
};

#endif

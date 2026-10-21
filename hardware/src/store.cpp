#include "store.h"
#include "data/device.h"
#include "sqlite_orm/sqlite_orm.h"

auto Store::create() {
    return sqlite_orm::make_storage(
        "app.db",
        sqlite_orm::make_table(
            "devices",
            sqlite_orm::make_column("id", &Device::id,
                                    sqlite_orm::primary_key().autoincrement()),
            sqlite_orm::make_column("name", &Device::name),
            sqlite_orm::make_column("password", &Device::password)));
}
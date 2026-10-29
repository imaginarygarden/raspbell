#include "server.h"

#include <crow/common.h>
#include <crow/http_response.h>
#include <crow/json.h>
#include <sqlite_orm/sqlite_orm.h>

#include "data/device.h"
#include "data/store.h"

#include <functional>
#include <stop_token>
#include <chrono>

void Server::setup(crow::SimpleApp& app) noexcept {
    app.port(PORT).multithreaded();
}

void Server::define_routes(crow::SimpleApp& app) noexcept {
    CROW_ROUTE(app, "/register")
        .methods(crow::HTTPMethod::POST)([](const crow::request& req) {
            auto devices = Store::instance().get_all<Device>();
            if (!devices.empty()) {
                return crow::response(crow::status::BAD_REQUEST);
            }

            auto data = crow::json::load(req.body);

            if (!data) {
                return crow::response(crow::status::BAD_REQUEST);
            }

            Device device{.name = data["name"].s(),
                          .password = data["password"].s()};
            auto insertedId = Store::instance().insert(device);

            return crow::response(crow::json::wvalue{data});
        });

    CROW_ROUTE(app, "/get_data")
        .methods(crow::HTTPMethod::GET)([](const crow::request& req) {
            auto password = req.get_header_value("x-password");
            auto devices = Store::instance().get_all<Device>(sqlite_orm::where(
                sqlite_orm::c(&Device::password) == password));

            if (devices.empty()) {
                return crow::response(crow::status::BAD_REQUEST);
            }

            auto logs = Store::instance().get_all<Log>();

            crow::json::wvalue::list list{};

            for (auto& log : logs) {
                crow::json::wvalue json{};
                json["id"] = log.id;
                json["image"] = log.image;
                json["timestamp"] = log.timestamp;
                list.push_back(json);
            }

            return crow::response(crow::json::wvalue{list});
        });
}

Server::Server() {
    setup(m_app);
    define_routes(m_app);

    Store::instance().sync_schema();

    m_thread = std::jthread([this](const std::stop_token& token) {
        std::jthread thread{std::bind_front(&crow::SimpleApp::run, &m_app)};
        const uint16_t min_timeout{500};

        while (!token.stop_requested()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(min_timeout));
        }

        m_app.stop();
        thread.join();
    });
}

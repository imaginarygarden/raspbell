#include "server.h"
#include <functional>
#include <stop_token>
#include <chrono>

void Server::define_routes(crow::SimpleApp& app) noexcept {
    CROW_ROUTE(app, "/")([]() { return "Hello world"; });

    CROW_ROUTE(app, "/json")
    ([] {
        crow::json::wvalue json({{"message", "Hello, World!"}});
        json["message2"] = "Raspi";
        return json;
    });

    CROW_ROUTE(app, "/hello/<int>")
    ([](int count) {
        const int max_bottles = 100;
        if (count > max_bottles) {
            return crow::response(crow::status::BAD_REQUEST);
        }
        std::ostringstream stream;
        stream << count << " bottles of beer!";
        return crow::response(stream.str());
    });

    CROW_ROUTE(app, "/add_json")
        .methods("POST"_method)([](const crow::request& req) {
            auto json = crow::json::load(req.body);
            if (!json) {
                return crow::response(
                    crow::status::BAD_REQUEST);  // same as crow::response(400)
            }
            std::ostringstream stream;

            if (json.has("a") && json.has("b")) {
                stream << json["a"].i() + json["b"].i();
            } else {
                stream << "Empty";
            }

            return crow::response{stream.str()};
        });
}

Server::Server() {
    define_routes(m_app);

    m_app.port(PORT).multithreaded();

    m_thread = std::jthread([this](const std::stop_token& token) {
        std::jthread thread(std::bind_front(&crow::SimpleApp::run, &m_app));
        const uint16_t min_timeout{500};

        while (!token.stop_requested()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(min_timeout));
        }

        m_app.stop();
        thread.join();
    });
}

Server::~Server() {
    m_thread.request_stop();
    m_thread.join();
}
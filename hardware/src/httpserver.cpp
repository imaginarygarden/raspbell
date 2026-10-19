#include "httpserver.h"

HttpServer::HttpServer() {
    CROW_ROUTE(m_app, "/")([]() { return "Hello world"; });

    CROW_ROUTE(m_app, "/json")
    ([] {
        crow::json::wvalue json({{"message", "Hello, World!"}});
        json["message2"] = "Hello, World.. Again!";
        return json;
    });

    CROW_ROUTE(m_app, "/hello/<int>")
    ([](int count) {
        if (count > 100) {
            return crow::response(crow::status::BAD_REQUEST);
        }
        std::ostringstream stream;
        stream << count << " bottles of beer!";
        return crow::response(stream.str());
    });

    CROW_ROUTE(m_app, "/add_json")
    .methods("POST"_method)
    ([](const crow::request& req){
        auto json = crow::json::load(req.body);
        if (!json) {
            return crow::response(crow::status::BAD_REQUEST); // same as crow::response(400)
        }
        std::ostringstream stream;

        if (json.has("a") && json.has("b")) {
            stream << json["a"].i() + json["b"].i();
        } else {
            stream << "Empty";
        }

        return crow::response{stream.str()};
    });

    m_app.port(18080).multithreaded();
    m_thread = std::jthread(std::bind_front(&crow::SimpleApp::run, &m_app));
}

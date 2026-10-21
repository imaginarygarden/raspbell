#ifndef SERVER_H
#define SERVER_H

#include <thread>

#include "crow.h"

class Server {
    constexpr static int PORT{18080};

    crow::SimpleApp m_app;
    std::jthread m_thread;

    static void define_routes(crow::SimpleApp& app) noexcept;

   public:
    explicit Server();
    ~Server();
};

#endif
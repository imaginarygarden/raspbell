#ifndef SERVER_H
#define SERVER_H

#include "crow.h"

#include <thread>

class Server {
    constexpr static int PORT{18080};

    crow::SimpleApp m_app;
    std::jthread m_thread;

    static void setup(crow::SimpleApp& app) noexcept;
    static void define_routes(crow::SimpleApp& app) noexcept;

   public:
    Server();
};

#endif

#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <thread>

#include "crow.h"

class HttpServer {
    crow::SimpleApp m_app;
    std::jthread m_thread;

   public:
    explicit HttpServer();
};

#endif
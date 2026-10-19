#include "httpserver.h"
#include <QApplication>
#include <QtHttpServer>

#include "mainwindow.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    MainWindow window;
    window.show();

    HttpServer server{};

    return QApplication::exec();
}
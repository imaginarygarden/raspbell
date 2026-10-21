#include "server.h"
#include <QApplication>
#include <QtHttpServer>

#include "mainwindow.h"
#include "store.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    auto store = Store::create();

    MainWindow window;
    Server server;

    window.show();
    return QApplication::exec();
}
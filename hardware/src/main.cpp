#include "server.h"
#include "ui/mainwindow.h"

#include <QApplication>

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    MainWindow window;
    window.show();

    Server server;

    return QApplication::exec();
}

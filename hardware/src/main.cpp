#include "ui/mainwindow.h"
#include "qserver.h"

#include <QApplication>

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    MainWindow window{};
    window.show();

    QServer server{};

    if (server.setup() != QServer::QServerConfResult::SUCCESS) {
        return -1;
    }

    return QApplication::exec();
}

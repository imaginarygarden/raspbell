#include <qhostaddress.h>

#include <QApplication>
#include <QtHttpServer>

#include "mainwindow.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    MainWindow window;
    window.show();

    QHttpServer server;

    server.route("/", []() { return "Hello World"; });

    auto tcpserver = std::make_unique<QTcpServer>();
    if (!tcpserver->listen() || !server.bind(tcpserver.get())) {
        qWarning() << QCoreApplication::translate(
            "QHttpServerExample", "Server failed to listen on a port.");
        return -1;
    }

    quint16 port = tcpserver->serverPort();
    tcpserver.release();

    qDebug() << QCoreApplication::translate(
                    "QHttpServerExample",
                    "Running on http://127.0.0.1:%1/ (Press CTRL+C to quit)")
                    .arg(port);

    return QApplication::exec();
}
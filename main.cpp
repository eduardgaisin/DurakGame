#include "mainwindow.h"

#include <QApplication>

#include "Server/server.h"

void handler(int players_number, int port) {
    Server* server = new Server(nullptr, players_number, port);
    server->run();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    QObject::connect(&w, &MainWindow::createHostSignal, handler);

    return a.exec();
}

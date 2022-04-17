#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QtCore>
#include <QTcpServer>

#include "Game/game.h"

class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr, int players_number = 2, int port = 0);
    void run();
    void disconnect();
    ~Server();

private slots:
    void newUser();
    void readSlot();

private:
    void gameStart();
    void sendData(int user_id);
    int players_number;
    int ready_counter = 0;
    int port;
    QMap<int, QTcpSocket*> sockets;
    Game* game;

};

#endif // SERVER_H

#include <QTcpSocket>

#include "server.h"

Server::Server(QObject *parent, int players_number, int port) : QTcpServer(parent)
  , players_number(players_number)
  , ready_counter(0)
  , port(port)
{
    game = new Game(players_number);
    setMaxPendingConnections(players_number);
}

void Server::run() {
    if (this->listen(QHostAddress::Any, port)) {
        qDebug() << "Succes connection";
    } else {
        qDebug() << "Error listen";
    }
    connect(this, SIGNAL(newConnection()), this, SLOT(newUser()));
}

void Server::newUser() {
    if (sockets.size() >= 4) return;
    qDebug() << "New connection";
    QTcpSocket* new_socket = this->nextPendingConnection();
    int id_user = new_socket->socketDescriptor();
    sockets[id_user] = new_socket;
    game->addPlayer(id_user);
    if (sockets.keys().size() == 1) {
        game->setFirst(id_user);
    }
    connect(sockets[id_user], SIGNAL(readyRead()), this, SLOT(readSlot()));
}

void Server::readSlot() {
    QTcpSocket* socket = static_cast<QTcpSocket*>(sender());
    int id_user = socket->socketDescriptor();
    QTextStream in(socket->readAll());
    int pos;
    in >> pos;
    if (pos == -2) {
        ready_counter++;
        if (ready_counter == players_number) {
            gameStart();
        }
        return;
    }
    game->playerMove(id_user, pos);
    for (auto id : sockets.keys()) {
        sendData(id);
    }
}

void Server::gameStart() {
    game->startGame();
    qDebug() << "Game started";
    for (auto socket : sockets.values()) {
        qDebug() << socket->socketDescriptor();
        QTextStream out(socket);
        out << 0;
        socket->flush();
    }
    for (int key : sockets.keys()) {
        sendData(key);
    }
}

/* move_id (0 - game start, 1 - update)
 * hand_size
 * cards_list
 *** card(int, int)
 * players_size
 * hands
 *** int
 * current_player
 * deck_size
 * trump (int, int)
 * table_size
 * table
 *** card(int, int)
 * is_attack_defent
 */
void Server::sendData(int user_id) {
    QTextStream out(sockets[user_id]);
    out << 1 << "\n";
    auto hands = game->getHands();
    out << hands[user_id].size() << "\n";
    for (auto card : hands[user_id]) {
        out << static_cast<int>(card.value) << "\n";
        out << static_cast<int>(card.suit) << "\n";
    }
    out << hands.size() << "\n";
    int current_player_id = game->getCurrentPlayer();
    int user_pos;
    int current_player_pos;
    for (int i = 0; i < hands.keys().size(); i++) {
        int key = hands.keys()[i];
        if (key != user_id)
            out << hands[key].size() << "\n";
        if (key == current_player_id) {
            current_player_pos = i;
        }
        if (key == user_id) {
            user_pos = i;
        }
    }
    if (current_player_pos == user_pos) {
        current_player_pos = -1;
    } else if (current_player_pos > user_pos) {
        current_player_pos--;
    }
    out << current_player_pos << "\n";
    out << game->getDeckSize() << "\n";
    Card trump = game->getTrump();
    out << static_cast<int>(trump.value) << "\n";
    out << static_cast<int>(trump.suit) << "\n";
    QList<Card> table = game->getTable();
    out << table.size() << "\n";
    for (const Card& card : table) {
        out << static_cast<int>(card.value) << "\n";
        out << static_cast<int>(card.suit) << "\n";
    }
    int attack_id = game->getAttack();
    int defend_id = game->getDefend();
    if (user_id == attack_id) {
        out << 1;
    } else if (user_id == defend_id) {
        out << 2;
    } else {
        out << 0;
    }
    sockets[user_id]->flush();
}

Server::~Server() {
    delete game;
}

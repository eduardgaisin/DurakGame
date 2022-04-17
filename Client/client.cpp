#include "client.h"

Client::Client(QObject *parent, const QString& ip, int port) : QObject(parent),
    ip(ip)
  , port(port)
{
    socket = new QTcpSocket();
    socket->connectToHost(ip, port);
    socket->waitForConnected();
    connect(socket, &QTcpSocket::readyRead, this, &Client::readData);
    sendData(-2);
}

void Client::sendData(int pos) {
    QTextStream out(socket);
    out << pos << "\n";
    socket->flush();
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
 */

void Client::readData() {
    QTcpSocket* socket = static_cast<QTcpSocket*>(sender());
    QTextStream in(socket->readAll());
    int id;
    in >> id;
    if (id == 0) {
        emit gameStartSignal();
        return;
    }
    int size;
    in >> size;
    QList<Card> cards;
    for (int i = 0; i < size; i++) {
        int value, suit;
        in >> value;
        in >> suit;
        cards.append(Card(static_cast<Value>(value), static_cast<Suit>(suit)));
    }
    int players;
    in >> players;
    QList<int> hands;
    for (int i = 0; i < players - 1; i++) {
        int hand_size;
        in >> hand_size;
        hands.append(hand_size);
    }
    int current_player;
    in >> current_player;
    int deck_size;
    in >> deck_size;
    Card trump;
    {
        int value, suit;
        in >> value >> suit;
        trump.value = static_cast<Value>(value);
        trump.suit = static_cast<Suit>(suit);
    }
    int table_size;
    in >> table_size;
    QList<Card> table;
    for (int i = 0; i < table_size; i++) {
        int value, suit;
        in >> value;
        in >> suit;
        table.append(Card(static_cast<Value>(value), static_cast<Suit>(suit)));
    }
    int user_type;
    in >> user_type;
    emit dataSignal(cards, hands, current_player, deck_size, trump, table, user_type);
}

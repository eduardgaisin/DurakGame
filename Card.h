#ifndef CARD_H
#define CARD_H

#include <QtCore>

enum Value {
    J = 11,
    Q = 12,
    K = 13,
    A = 14
};

enum Suit {
    Hearts,
    Spades,
    Diamonds,
    Clubs
};

struct Card {
    Card() : value((Value)0), suit((Suit)0) { }
    Card(Value value, Suit suit) :
        value(value)
      , suit(suit) { }
    QString getString() const {
        QString res;
        switch (value) {
        case J:
            res.append("J");
            break;
        case Q:
            res.append("Q");
            break;
        case K:
            res.append("K");
            break;
        case A:
            res.append("A");
            break;
        default:
            res.append(QString::number(static_cast<int>(value)));
            break;
        }
        switch (suit) {
        case Hearts:
            res.append(QChar(9829));
            break;
        case Spades:
            res.append(QChar(9824));
            break;
        case Diamonds:
            res.append(QChar(9830));
            break;
        case Clubs:
            res.append(QChar(9827));
            break;
        default:
            break;
        }

        return res;
    }
    Value value;
    Suit suit;
};

#endif // CARD_H

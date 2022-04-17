#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QtCore>
#include <QTcpSocket>
#include <QHostAddress>

#include "Card.h"

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr
            , const QString& ip = "192.164.0.1", int port = 0);

    const QString& getIp() {
        return ip;
    }

    // sending selected card position
    // if id == -1 'pass' selected
    void sendData(int pos = 0);

signals:
    void dataSignal(const QList<Card>& cards
                    , const QList<int>& hands, int current_player
                    , int deck_size, const Card& trump
                    , const QList<Card>& table, int user_type);
    void gameStartSignal();

private slots:
    void readData();

private:
    QTcpSocket* socket;
    QString ip;
    int port;
};

#endif // CLIENT_H

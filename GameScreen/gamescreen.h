#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <QWidget>
#include "Client/client.h"

class QLabel;

namespace Ui {
class GameScreen;
}

class GameScreen : public QWidget
{
    Q_OBJECT

public:
    explicit GameScreen(QWidget *parent = nullptr, Client* client = nullptr);
    ~GameScreen();

private slots:
    void redrawScreen(const QList<Card>& cards
                      , const QList<int>& hands, int current_player
                      , int deck_size, const Card& trump
                      , const QList<Card>& table, int user_type);
    void sendData(int id);
    void on_passButton_clicked();

private:
    void drawPlayersCards(const QList<Card>& cards);
    void drawTable(const QList<Card>& table);
    void drawHands(const QList<int>& hands, int current_player);
    Client* client;
    Ui::GameScreen *ui;
    QVector<QLabel*> op_hands;
};

#endif // GAMESCREEN_H

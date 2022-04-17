#ifndef GAME_H
#define GAME_H

#include <QtCore>

#include "Card.h"

class Game
{
public:
    Game(int players_number);
    void startGame();

    int getDeckSize() const { return cards.size() - current_card; }
    Card getTrump() const { return *trump; }
    const QMap<int, QVector<Card>>& getHands() const { return hands; }
    const QList<Card>& getTable() const { return table; }
    int getCurrentPlayer() { return attack_id; }
    int  getAttack() { return attack_id; }
    int getDefend() { return defend_id; }

    bool addPlayer(int id);
    bool setFirst(int id);

    // returns false, if wrong id or wrong card_id
    void playerMove(int id, int card_id);

    ~Game();

private:
    void emptyPlayersHands();
    void refillCards();
    void shuffleCards();
    Card getNextCard();
    void giveCards();
    void moveTableToPlayer(int id);
    void refillPlayer(int id);
    void changePlayers();
    bool tableHaveValue(const Card& card);
    QVector<Card> cards;
    QList<int> players;
    QMap<int, QVector<Card>> hands;
    Card* trump;
    QList<Card> table;
    int player_number;
    int current_card;
    int current_player_id;
    int attack_id;
    int defend_id;
};

#endif // GAME_H

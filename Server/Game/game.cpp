#include <ctime>

#include "game.h"

Game::Game(int player_number) :
    trump(nullptr)
  , player_number(player_number) {

}

void Game::playerMove(int id, int card_id) {
    qDebug() << "Current: " << current_player_id << " " << id;
    if (id != current_player_id) {
        return;
    }
    if (card_id == -1) {
        if (table.size() == 0) {
            return;
        }
        bool isDefeated = false;
        if (attack_id == id) {
            table.clear();
        } else if (defend_id == id) {
            moveTableToPlayer(id);
            table.clear();
            isDefeated = true;
        }
        refillPlayer(attack_id);
        refillPlayer(defend_id);
        if (isDefeated) {
            changePlayers();
        }
        changePlayers();
    } else {
        if (table.size() == 0) {
            table.append(hands[id][card_id]);
            hands[id].remove(card_id);
            current_player_id = defend_id;
            return;
        }
        if (attack_id == id) {
            Card card = hands[id][card_id];
            if (!tableHaveValue(card)) {
                return;
            }
            table.append(card);
            hands[id].remove(card_id);
            current_player_id = defend_id;
        } else if (defend_id == id) {
            Card card = hands[id][card_id];
            Card attacking_card = table.last();
            if (card.suit == trump->suit) {
                if (attacking_card.suit == trump->suit
                    && card.value < attacking_card.value) {
                    return;
                }
                table.append(card);
                hands[id].remove(card_id);
            } else {
                if (card.suit != attacking_card.suit) {
                    return;
                }
                if (card.value < attacking_card.value) {
                    return;
                }
                table.append(card);
                hands[id].remove(card_id);
            }
            current_player_id = attack_id;
        }
    }
}

bool Game::tableHaveValue(const Card& card) {
    for (const Card& t_card : table) {
        if (card.value == t_card.value)
            return true;
    }
    return false;
}

void Game::moveTableToPlayer(int id) {
    for (auto card : table) {
        hands[id].append(card);
    }
    std::sort(hands[id].begin(), hands[id].end(), [] (const Card& a, const Card& b) {
        return (a.suit < b.suit) || (a.suit == b.suit && a.value < b.value);
    });
}

void Game::refillPlayer(int id) {
    while (hands[id].size() < 6) {
        Card card = getNextCard();
        if (static_cast<int>(card.value) == -1) {
            break;
        }
        hands[id].append(card);
    }
    std::sort(hands[id].begin(), hands[id].end(), [] (const Card& a, const Card& b) {
        return (a.suit < b.suit) || (a.suit == b.suit && a.value < b.value);
    });
}

void Game::changePlayers() {
    // finding next player
    QList<int> mplayers = players;
    mplayers.append(players);
    qDebug() << "Players" << mplayers.size();
    int pos = mplayers.indexOf(attack_id);
    for (int i = pos + 1; i < mplayers.size(); i++) {
        if (hands[players[i % player_number]].size() != 0) {
            attack_id = players[i % player_number];
            break;
        }
    }
    pos = mplayers.indexOf(attack_id);
    for (int i = pos + 1; i < mplayers.size(); i++) {
        if (hands[players[i % player_number]].size() != 0) {
            defend_id = players[i % player_number];
            break;
        }
    }
    current_player_id = attack_id;
}


bool Game::addPlayer(int id) {
    if (players.size() >= player_number || players.contains(id)) {
        return false;
    }
    hands[id] = QVector<Card>();
    players.append(id);
    return true;
}

bool Game::setFirst(int id) {
    if (players.contains(id)) {
        current_player_id = id;
        return true;
    }
    return false;
}

void Game::startGame() {
    table.clear();
    emptyPlayersHands();
    refillCards();
    shuffleCards();
    if (trump != nullptr)
        delete trump;
    trump = new Card(cards.last());
    giveCards();
}

void Game::emptyPlayersHands() {
    for (auto id : players) {
        hands[id].clear();
    }
}

void Game::refillCards() {
    current_card = 0;
    cards.clear();
    for (int suit = 0; suit <= 3; suit++) {
        for (int value = 2; value <= 14; value++) {
            cards.append( Card(static_cast<Value>(value), static_cast<Suit>(suit)) );
        }
    }
}

void Game::shuffleCards() {
    QRandomGenerator generator(time(nullptr));
    for (int i = 0; i < cards.size(); i++) {
        qSwap(cards[i], cards[generator.generate() % cards.size()]);
    }
}

void Game::giveCards() {
    Card lowest_trump(Value::A, Suit::Hearts);
    qDebug() << players.size();
    for (int i = 0; i < 6; i++) {
        for (int key : players) {
            hands[key].push_back(getNextCard());
            if (hands[key].last().suit == trump->suit
                && hands[key].last().value < lowest_trump.value) {
                lowest_trump = hands[key].last();
                current_player_id = key;
                attack_id = key;
            }
        }
    }
    for (int id : hands.keys()) {
        std::sort(hands[id].begin(), hands[id].end(), [] (const Card& a, const Card& b) {
            return (a.suit < b.suit) || (a.suit == b.suit && a.value < b.value);
        });
    }
    QList<int> mplayers;
    mplayers.append(players);
    mplayers.append(players);
    int pos = mplayers.indexOf(attack_id);
    for (int i = pos + 1; i < mplayers.size(); i++) {
        if (hands[players[i % player_number]].size() != 0) {
            defend_id = players[i % player_number];
            break;
        }
    }
}

Card Game::getNextCard() {
    if (current_card >= cards.size()) {
        return Card(static_cast<Value>(-1), static_cast<Suit>(-1));
    }
    int return_index = current_card;
    current_card++;
    return cards[return_index];
}

Game::~Game() {
    delete trump;
}

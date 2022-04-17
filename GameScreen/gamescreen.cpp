#include "gamescreen.h"
#include "ui_gamescreen.h"

#include "CardWidget/cardwidget.h"
#include "Card.h"

void debug(const QString& str) {
    qDebug() << str;
}

GameScreen::GameScreen(QWidget *parent, Client* client) :
    QWidget(parent),
    client(client),
    ui(new Ui::GameScreen)
{
    ui->setupUi(this);
    connect(client, &Client::dataSignal, this, &GameScreen::redrawScreen);
}

void GameScreen::redrawScreen(const QList<Card>& cards
                  , const QList<int>& hands, int current_player
                  , int deck_size, const Card& trump
                  , const QList<Card>& table, int user_type) {
    drawPlayersCards(cards);
    drawTable(table);
    drawHands(hands, current_player);
    ui->deckSizeLabel->setText(QString::number(deck_size));
    ui->trumpValueLabel->setText(trump.getString());
    switch (user_type) {
        case 0:
            ui->typeLabel->setText("wait");
        break;
        case 1:
            ui->typeLabel->setText("attack");
        break;
        case 2:
            ui->typeLabel->setText("defend");
        break;
    }
}

void GameScreen::sendData(int id) {
    client->sendData(id);
}

void GameScreen::on_passButton_clicked()
{
    client->sendData(-1);
}

void GameScreen::drawPlayersCards(const QList<Card>& cards) {
    // clearing hand
    if (ui->handAreaWidget->layout() != nullptr) {
        QLayoutItem *child;
        while ((child = ui->handAreaWidget->layout()->takeAt(0)) != NULL) {
            delete child->widget();
            Q_ASSERT(!child->layout());
        }
        delete ui->handAreaWidget->layout();
        ui->handAreaWidget->updateGeometry();
    }

    // drawing hand
    QLayout *hand_layout = new QVBoxLayout();
    hand_layout->setSizeConstraint(hand_layout->SetMinimumSize);
    hand_layout->setAlignment(Qt::AlignTop);
    int id = 0;
    for (auto card : cards) {
        CardWidget* widget = new CardWidget(nullptr, id, card);
        id++;
        hand_layout->addWidget(widget);
        hand_layout->setAlignment(widget, Qt::AlignLeft);
        connect(widget, &CardWidget::clickedSignal, this, &GameScreen::sendData);
    }
    ui->handAreaWidget->setLayout(hand_layout);
}

void GameScreen::drawTable(const QList<Card>& table) {
    // clearing table
    if (ui->tableAreaWidget->layout() != nullptr) {
        QLayoutItem *child;
        while ((child = ui->tableAreaWidget->layout()->takeAt(0)) != NULL) {
            delete child->widget();
            Q_ASSERT(!child->layout());
        }
        delete ui->tableAreaWidget->layout();
        ui->tableAreaWidget->updateGeometry();
    }

    // drawing table
    QLayout *table_layout = new QVBoxLayout();
    table_layout->setSizeConstraint(table_layout->SetMinimumSize);
    table_layout->setAlignment(Qt::AlignTop);
    for (auto card : table) {
        CardWidget* widget = new CardWidget(nullptr, 0, card);
        table_layout->addWidget(widget);
        table_layout->setAlignment(widget, Qt::AlignLeft);
    }
    ui->tableAreaWidget->setLayout(table_layout);
}

void GameScreen::drawHands(const QList<int> &hands, int current_player) {
    if (op_hands.size() == 0) {
        for (int i = 0; i < hands.size(); i++) {
            QLabel* hand_size = new QLabel();
            hand_size->setAlignment(Qt::AlignCenter);
            hand_size->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
            op_hands.append(hand_size);
            ui->handsLayout->addWidget(hand_size);
        }
    }
    int index = 0;
    for (int hand : hands) {
        QLabel* hand_size = op_hands[index];
        hand_size->setText(QString::number(hand));
        hand_size->setAlignment(Qt::AlignCenter);
        if (index == current_player) {
            hand_size->setFont(QFont("Sans Serif", 11, QFont::Bold));
        } else {
            hand_size->setFont(QFont("Sans Serif", 11));
        }
        index++;
    }
}

GameScreen::~GameScreen()
{
    delete ui;
}

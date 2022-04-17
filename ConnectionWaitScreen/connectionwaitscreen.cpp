#include "connectionwaitscreen.h"
#include "ui_connectionwaitscreen.h"

#include <QHostAddress>

ConnectionWaitScreen::ConnectionWaitScreen(QWidget *parent, Client* client) :
    QWidget(parent),
    client(client),
    ui(new Ui::ConnectionWaitScreen)
{
    ui->setupUi(this);
    ui->ipLabel->setText("IP: " + client->getIp());
    connect(client, &Client::gameStartSignal, this, &ConnectionWaitScreen::gameStartedSlot);
}

ConnectionWaitScreen::~ConnectionWaitScreen()
{
    delete ui;
}

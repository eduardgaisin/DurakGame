#ifndef CONNECTIONWAITSCREEN_H
#define CONNECTIONWAITSCREEN_H

#include <QWidget>
#include "Client/client.h"

namespace Ui {
class ConnectionWaitScreen;
}

class ConnectionWaitScreen : public QWidget
{
    Q_OBJECT

public:
    explicit ConnectionWaitScreen(QWidget *parent = nullptr, Client* client = nullptr);
    ~ConnectionWaitScreen();

signals:
    void gameStarted();

private slots:
    void gameStartedSlot() {
        emit gameStarted();
    }

private:
    Client* client;
    Ui::ConnectionWaitScreen *ui;
};

#endif // CONNECTIONWAITSCREEN_H

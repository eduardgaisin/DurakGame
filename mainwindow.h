#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "MenuScreen/menuscreenwidget.h"
#include "ConnectionWaitScreen/connectionwaitscreen.h"
#include "GameScreen/gamescreen.h"
#include "Client/client.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void createHostSignal(int players_number, int port);

private slots:
    void createHost(int players_number, int port);
    void connectToHost(const QString& ip, int port);
    void gameStartedSlot();

private:
    void createClient(const QString& ip, int port);

    MenuScreenWidget* menu_widget;
    GameScreen* game_widget;
    ConnectionWaitScreen* wait_screen_widget;

    Client* client;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

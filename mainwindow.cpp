#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtCore>
#include <QHostAddress>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(400, 400);
    menu_widget = new MenuScreenWidget();
    ui->centralLayout->addWidget(menu_widget);

    connect(menu_widget, &MenuScreenWidget::createHost, this, &MainWindow::createHost);
    connect(menu_widget, &MenuScreenWidget::connectToHost, this, &MainWindow::connectToHost);
}

void MainWindow::createHost(int players_number, int port) {
    emit createHostSignal(players_number, port);
}

void MainWindow::connectToHost(const QString& ip, int port) {
    menu_widget->deleteLater();
    ui->centralLayout->removeWidget(menu_widget);

    createClient(ip, port);

    wait_screen_widget = new ConnectionWaitScreen(nullptr, client);
    ui->centralLayout->addWidget(wait_screen_widget);
    connect(wait_screen_widget, &ConnectionWaitScreen::gameStarted, this, &MainWindow::gameStartedSlot);
}

void MainWindow::gameStartedSlot() {
    wait_screen_widget->deleteLater();
    ui->centralLayout->removeWidget(wait_screen_widget);
    game_widget = new GameScreen(nullptr, client);
    ui->centralLayout->addWidget(game_widget);
}

void MainWindow::createClient(const QString& ip, int port) {
    client = new Client(nullptr, ip, port);
}

MainWindow::~MainWindow()
{
    if (menu_widget) {
        delete menu_widget;
    }
    if (wait_screen_widget) {
        delete wait_screen_widget;
    }
    if (game_widget) {
        delete game_widget;
    }
    delete client;
    delete ui;
}


#include <QtNetwork>

#include "menuscreenwidget.h"
#include "ui_menuscreenwidget.h"

MenuScreenWidget::MenuScreenWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuScreenWidget)
{
    ui->setupUi(this);
}

void MenuScreenWidget::on_hostButton_clicked()
{
    int players_number = ui->playersSpinBox->text().toInt();
    int port = ui->portLineEdit_2->text().toInt();
    emit createHost(players_number, port);

    // getting local ip of this computer
    QString local_ip;
    const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
    for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
             local_ip =  address.toString();
    }
    qDebug() << "Local ip: " << local_ip;
    emit connectToHost(local_ip, port);
}

void MenuScreenWidget::on_connectButton_clicked()
{
    QString ip = ui->ipLineEdit->text();
    int port = ui->portLineEdit->text().toInt();
    emit connectToHost(ip, port);
}

MenuScreenWidget::~MenuScreenWidget()
{
    delete ui;
}

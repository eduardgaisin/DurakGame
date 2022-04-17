#ifndef MENUSCREENWIDGET_H
#define MENUSCREENWIDGET_H

#include <QWidget>

namespace Ui {
class MenuScreenWidget;
}

class MenuScreenWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MenuScreenWidget(QWidget *parent = nullptr);
    ~MenuScreenWidget();

signals:
    // signal to create TCP server
    void createHost(int players_number, int port);
    // signal to connect to TCP server
    void connectToHost(const QString& ip, int port);

private slots:
    void on_hostButton_clicked();
    void on_connectButton_clicked();

private:
    Ui::MenuScreenWidget *ui;
};

#endif // MENUSCREENWIDGET_H

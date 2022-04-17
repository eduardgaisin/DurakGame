#ifndef CARDWIDGET_H
#define CARDWIDGET_H

#include <QWidget>

#include "Card.h"

namespace Ui {
class CardWidget;
}

class CardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CardWidget(QWidget *parent = nullptr, int id = -1, const Card& card = Card());
    ~CardWidget();

signals:
    void clickedSignal(int id);

private slots:
    void on_button_clicked();

private:
    int id;
    Ui::CardWidget *ui;
};

#endif // CARDWIDGET_H

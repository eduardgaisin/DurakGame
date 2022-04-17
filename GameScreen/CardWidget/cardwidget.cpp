#include "cardwidget.h"
#include "ui_cardwidget.h"

CardWidget::CardWidget(QWidget *parent, int id, const Card& card) :
    QWidget(parent),
    id(id),
    ui(new Ui::CardWidget)
{
    ui->setupUi(this);
    ui->button->setText(card.getString());
}

void CardWidget::on_button_clicked()
{
    emit clickedSignal(id);
}

CardWidget::~CardWidget()
{
    delete ui;
}

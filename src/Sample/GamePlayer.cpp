#include "GamePlayer.h"
#include <QPainter>
#include <QResizeEvent>
GamePlayer::GamePlayer(QWidget *parent)
    : QWidget{parent},
    message_timer(new QTimer(this))
{
    hide();
    connect(message_timer,&QTimer::timeout,[=](){
        hide();
    });
}

void GamePlayer::Play(const QString &message)
{
    qMessageBuffer=message;
    message_timer->start(5000);
    show();

}

void GamePlayer::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);
    painter.drawText(rect(), Qt::AlignHCenter, qMessageBuffer);
}

void GamePlayer::resizeEvent(QResizeEvent *event)
{
    resize(event->size());
}

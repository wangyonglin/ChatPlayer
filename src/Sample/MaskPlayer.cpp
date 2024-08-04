#include "MaskPlayer.h"

#include <QResizeEvent>
#include <QPainterPath>

MaskPlayer::MaskPlayer(QWidget *parent)
    : QWidget{parent}
{

}

void MaskPlayer::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QFont font;
    font.setBold(true);
    font.setPointSize(24);
    font.setUnderline(true);
    font.setCapitalization(QFont::SmallCaps);
    font.setLetterSpacing(QFont::AbsoluteSpacing, 10);


    QPen pen;
    pen.setWidth(2); // 设置描边的宽度
    pen.setColor(Qt::white); // 设置描边的颜色

    QPainter pricePainter(this);
    pricePainter.setFont(font);
    pricePainter.setPen(pen);
    pricePainter.drawText(QRect(0,360,width(),42),Qt::AlignRight,tr("¥:3900"));

    QPainter titlePainter(this);
    titlePainter.setFont(font);
    titlePainter.setPen(pen);
    titlePainter.drawText(QRect(0,410,width(),42), Qt::AlignHCenter, tr("单号(%1) 鞋码(%2)").arg(888).arg(42));

    // QPainter logoPainter(this);
    // QRect logoRect(0,0,160,100);
    // logoPainter.drawImage(logoRect,QImage(":/images/logo.jpeg"));
}

void MaskPlayer::resizeEvent(QResizeEvent *event)
{
    resize(event->size());
}

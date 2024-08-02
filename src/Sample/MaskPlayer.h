#ifndef MASKPLAYER_H
#define MASKPLAYER_H

#include <QWidget>
#include <QImage>
#include <QPainter>

class MaskPlayer : public QWidget
{
    Q_OBJECT
public:
    explicit MaskPlayer(QWidget *parent = nullptr);

signals:

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;
private:
    QImage logoImage;
};

#endif // MASKPLAYER_H

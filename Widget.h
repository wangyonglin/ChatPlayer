#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "QFFmpegPlayer/QFFmpegPlayer.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private:
    QFFmpegPlayer *player;
    void resizeEvent(QResizeEvent *event);
    void keyPressEvent(QKeyEvent *event);
};
#endif // WIDGET_H

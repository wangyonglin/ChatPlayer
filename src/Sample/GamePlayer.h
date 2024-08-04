#ifndef GAMEPLAYER_H
#define GAMEPLAYER_H

#include <QWidget>
#include <QTimer>
class GamePlayer : public QWidget
{
    Q_OBJECT
public:
    explicit GamePlayer(QWidget *parent = nullptr);
    void Play(const QString &message);
signals:

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;
private:
    QString qMessageBuffer;
    QTimer *message_timer;
};

#endif // GAMEPLAYER_H

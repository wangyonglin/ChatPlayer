#ifndef ASRFRAMEPLAYER_H
#define ASRFRAMEPLAYER_H

#include <QWidget>
#include <QLabel>
#include <QWidget>
#include <QPainter>
#include <QHBoxLayout>
#include <QPainterPath>
#include <QSettings>

#include "SherpaOnnxPlayer.h"
#include "SoundThreader.h"
#include "BaseSpeaker.h"
#include "SherpaNcnnPlayer.h"

class QSettings;
class QHBoxLayout;
class QLabel;
class QTimer;
class ASRFramePlayer : public QWidget
{
    Q_OBJECT
public:
    explicit ASRFramePlayer(QWidget *parent = nullptr);
    ~ASRFramePlayer();
    void setFontSize(int fontsize);
    void setFontColor(const QColor &fontcolor);
private:
    SoundThreader * mSoundThreader;
    BaseSpeaker * mBaseSpeaker;
    SherpaOnnxPlayer * mSherpaOnnxPlayer;
    SherpaNcnnPlayer * mSherpaNcnnPlayer;
private:
    int strokeWidth;
    QColor strokeColor;
    int     textSize;//显示字体大小
    QColor  textColor;//字体颜色
    QString ASRFrameTextBuffer="";
    QTimer timer;
    QString GetTextByWidth(const QFontMetrics &fm, const QString &text, int width);
    QStringList GetTextLinesByRectSize(const QFontMetrics &fm, const QString &text, const QSize &size);
    void PaintStrokeText(QPainter *painter, const QRect &rect, const QString &text, const QFont &font, int strokeWidth = 2, const QColor &strokeColor = QColor(0xffffff), const QTextOption &option = QTextOption());
protected:
    virtual void paintEvent(QPaintEvent *event) override;
private slots:
    void hideTextLabel();
    void showTextLabel();

};

#endif // ASRFRAMEPLAYER_H

#ifndef QASRPLAYER_H
#define QASRPLAYER_H

#include <QLabel>
#include <QWidget>
#include <QPainter>
#include <QHBoxLayout>
#include <QPainterPath>
#include <QSettings>
#include "ASRThreader.h"
#include "ASRSettings.h"


class QSettings;
class QHBoxLayout;
class QLabel;
class QTimer;
class QASRPlayer : public QWidget
{
    Q_OBJECT
public:
    explicit QASRPlayer(QWidget *parent = nullptr);

    ~QASRPlayer();
private:
    ASRSettings *setting;
    int strokeWidth;
    QColor strokeColor;
    int     textSize;//显示字体大小
    QColor  textColor;//字体颜色
    ASRThreader *asrThreader;
    QString str="";
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

#endif // QASRPLAYER_H

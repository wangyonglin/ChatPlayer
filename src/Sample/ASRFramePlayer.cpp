#include "ASRFramePlayer.h"

ASRFramePlayer::ASRFramePlayer(QWidget *parent)
    : QWidget{parent},
    mSoundThreader(new SoundThreader(this)),
    mBaseSpeaker(new BaseSpeaker(this)),
    mSherpaOnnxPlayer(new SherpaOnnxPlayer(this)),
    mSherpaNcnnPlayer(new SherpaNcnnPlayer(this)),
    textSize(26),
    textColor(QColor(250,250,250)),
    strokeWidth(8),
    strokeColor(QColor(000,000,000))
{
    mBaseSpeaker->InitSpeaker();
    mSoundThreader->loopStart();
    mSherpaOnnxPlayer->InitRecognizer();
    mSherpaNcnnPlayer->InitRecognizer();



    connect(mSoundThreader,&SoundThreader::UpdateMicrophone,[=](QByteArray buffer){


        if(!bNCNNState)
        {
            QString talkNameBuffer= mSherpaOnnxPlayer->buildText(buffer);
            if(!talkNameBuffer.isEmpty()){

                if(QString::localeAwareCompare(talkNameBuffer, tr("小米小米")) == 0){
                    bNCNNState=true;
                    //qDebug() << "语音指令已开启";
                    emit SendMessageBox(tr("语音指令已开启"));
                    show();

                }else{
                    qDebug()<<"字符串不同分支" << talkNameBuffer;
                    emit SendMessageBox(talkNameBuffer);
                }
            }
        }
        if(bNCNNState){
             SherpaNcnnPlayer::ResultText ResultBuffer= mSherpaNcnnPlayer->buildText(buffer);
            mFrameTextBuffer=ResultBuffer.text;
            if(ResultBuffer.finish){
                bNCNNState=false;
                hide();
                //qDebug() << "语音指令已关闭";
                emit SendMessageBox(tr( "语音指令已关闭"));
            }
        }

    });


}
void ASRFramePlayer::setFontSize(int size)
{
    textSize=size;
}
void ASRFramePlayer::setFontColor(const QColor &color)
{
    textColor=color;
}
ASRFramePlayer::~ASRFramePlayer()
{
    mSoundThreader->loopStop();
}

void ASRFramePlayer::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    if(mFrameTextBuffer.isEmpty())return;
    QPainter painter(this);
    QFont font;
    font.setPointSize(textSize);
    font.setBold(true);
    QPen fontColor(textColor); // 设置字体颜色为红色
    painter.setPen(fontColor);
    QTextOption option(Qt::AlignCenter | Qt::AlignVCenter);
    option.setWrapMode(QTextOption::WordWrap);
    return PaintStrokeText(&painter,rect(),mFrameTextBuffer,font,strokeWidth,strokeColor,option);
}

///
/// \brief GetTextByWidth 根据宽度得到文字
/// \param fm
/// \param text
/// \param width
/// \return
///
QString ASRFramePlayer::GetTextByWidth(const QFontMetrics& fm, const QString& text, int width)
{
    if(width <= 0)
        return QString();

    int offset = 0;
    QString subStr;
    do
    {
        subStr  = text.mid(0, text.length() - offset++);
    }while(!(fm.width(subStr,width) <= width));

    return subStr;
}

///
/// \brief GetTextLinesByRectSize 根据宽、高得到文字段落
/// \param fm
/// \param text
/// \param size
/// \return
///
QStringList ASRFramePlayer::GetTextLinesByRectSize(const QFontMetrics& fm, const QString& text, const QSize& size)
{
    QStringList splitLines = text.split('\n');
    QStringList result;
    if(size.width() <= 120)
    {
        int ab =0;
        ab++;
    }
    for(int i = 0; i < splitLines.count(); i++)
    {
        QString splitLine = splitLines[i];

        do
        {

            QString splitLineElidedText = GetTextByWidth(fm, splitLine, size.width());

            if(!splitLineElidedText.isEmpty())
                result.append(splitLineElidedText);



            splitLine = splitLine.mid(splitLineElidedText.length(), splitLine.length() - splitLineElidedText.length());
        }
        while(!splitLine.isEmpty());
    }

    return result;
}

///
/// \brief PaintStrokeText 画艺术字(硬发光)
/// \param painter
/// \param rect 所需要画的区域
/// \param text 文字
/// \param font 字体
/// \param strokeWidth 艺术字发光宽度
/// \param strokeColor 艺术字发光颜色
/// \param option 对齐方式
///
void ASRFramePlayer::PaintStrokeText(QPainter* painter,
                                     const QRect& rect,
                                     const QString& text,
                                     const QFont& font,
                                     int strokeWidth,
                                     const QColor& strokeColor,
                                     const QTextOption& option
                                     )
{
    painter->save();
    painter->setFont(font);

    QPen oldPen = painter->pen();
    QPen strokePen = QPen(strokeColor,strokeWidth);

    QStringList textList = GetTextLinesByRectSize(painter->fontMetrics(), text, rect.size());
    int fontHeight = painter->fontMetrics().height();
    int lineHeight = painter->fontMetrics().lineSpacing();

    for(int i = 0; i < textList.count(); i++)
    {


        QString textLine = textList[i];
        QRect textLineBoundingRect = painter->fontMetrics().boundingRect(rect,option.flags(),textLine);
        QSize textLineSize = textLineBoundingRect.size();


        int offsetX = 0;
        int offsetY = i * lineHeight;

        //offset x
        if(option.alignment().testFlag(Qt::AlignLeft))
        {
            offsetX = 0;
        }
        if(option.alignment().testFlag(Qt::AlignRight))
        {
            offsetX = rect.width() - textLineBoundingRect.width();
        }
        if(option.alignment().testFlag(Qt::AlignHCenter))
        {
            offsetX = (rect.width() - textLineBoundingRect.width())/2;
        }

        //offset y
        if(option.alignment().testFlag(Qt::AlignTop))
        {
            //offsetY = 0;
        }
        if(option.alignment().testFlag(Qt::AlignBottom))
        {

            offsetY += rect.height() - textList.count() * lineHeight;
        }
        if(option.alignment().testFlag(Qt::AlignVCenter))
        {
            offsetY += (rect.height() - textList.count() * lineHeight)/2;
        }



        textLineBoundingRect.setLeft(rect.left() + offsetX);
        textLineBoundingRect.setRight(textLineBoundingRect.left() + textLineSize.width());
        textLineBoundingRect.setTop(rect.top() + offsetY);
        textLineBoundingRect.setBottom(textLineBoundingRect.top() + textLineSize.height());

        QPainterPath strokePath;
        strokePath.addText(textLineBoundingRect.bottomLeft(), font, textLine);
        painter->strokePath(strokePath, strokePen);
        //painter->drawPath(strokePath);//debug
        painter->fillPath(strokePath, QBrush(oldPen.color()));
    }

    //for .debug
    // painter->drawText(rect, text, option);
    painter->restore();
}

void ASRFramePlayer::hideTextLabel()
{
    hide();
}
void ASRFramePlayer::showTextLabel()
{
    show();
}

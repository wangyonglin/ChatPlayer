#include "QASRPlayer.h"

QASRPlayer::QASRPlayer(QWidget *parent)
    : QWidget{parent},
    setting(new ASRSettings(parent)),
    textSize(40),
    textColor(QColor(250,000,000)),
    strokeWidth(16),
    strokeColor(QColor(000,000,000)),
    asrThreader(new ASRThreader(this))
{
    asrThreader->InitThreader(setting);
    connect(asrThreader,&ASRThreader::updateRecognizer,[=](){
        showTextLabel();
        if(!asrThreader->listText.isEmpty()){
            if(asrThreader->listText.size()>20)return;
            str.clear();
            str = QStringList(asrThreader->listText.toList()).join("");
            update();
        }
    });

    connect(asrThreader,&ASRThreader::finishRecognizer,[=](){
        QTimer::singleShot(10,this,&QASRPlayer::hideTextLabel);
        if(!str.isEmpty()){
            str.clear();
        }
        if(!asrThreader->listText.isEmpty()){
            asrThreader->listText.clear();
        }
        update();
    });

    asrThreader->loopStart();
}



QASRPlayer::~QASRPlayer()
{
    asrThreader->loopStop();
}



void QASRPlayer::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    if(str.isEmpty())return;
    QPainter painter(this);
    QFont font;
    font.setPointSize(textSize);
    font.setBold(true);
   // QFontMetrics metrics(font); // 创建 QFontMetrics 对象
   // int width = metrics.horizontalAdvance(str); // 计算文本的水平宽度
   // int height = metrics.ascent(); // 计算文本的垂直高度
   // QRect rect((this->width()-width)/2, (this->height()-height)/2, width, height); // 根据widget大小计算居中对齐位置
    QPen fontColor(textColor); // 设置字体颜色为红色
    painter.setPen(fontColor);
    return PaintStrokeText(&painter,rect(),str,font,strokeWidth,strokeColor,QTextOption(Qt::AlignCenter));
}
void QASRPlayer::hideTextLabel()
{
    hide();
}
void QASRPlayer::showTextLabel()
{
    show();
}

///
/// \brief GetTextByWidth 根据宽度得到文字
/// \param fm
/// \param text
/// \param width
/// \return
///
QString QASRPlayer::GetTextByWidth(const QFontMetrics& fm, const QString& text, int width)
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
QStringList QASRPlayer::GetTextLinesByRectSize(const QFontMetrics& fm, const QString& text, const QSize& size)
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
void QASRPlayer::PaintStrokeText(QPainter* painter,
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


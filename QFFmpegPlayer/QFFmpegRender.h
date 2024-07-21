#ifndef QFFMPEGRENDER_H
#define QFFMPEGRENDER_H


#include <QApplication>
#include <QAudioOutput>
#include <QIODevice>
#include <QDebug>
#include <QObject>
#include <QWidget>
#include <chrono>
#include <QPaintEvent>
#include <QPainter>

class QFFmpegRender: public QObject
{
    Q_OBJECT
public:
    explicit QFFmpegRender(QObject *parent = nullptr);
    ~QFFmpegRender();

    void InitFormat(int dst_nb_samples, int rate, int sample_size, int nch);
    void WriteOutput(const char* data, qint64 len);
    void FreeFormat();
    void WriteOutput(QByteArray bytes);
protected:
private:
    QIODevice* outputDevice;
    QAudioOutput* audioOutput;
    int64_t player_start_time_ms = 0;

signals:
};

#endif // QFFMPEGRENDER_H

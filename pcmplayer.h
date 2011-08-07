#ifndef WAVPLAYER_H
#define WAVPLAYER_H

#include <QAudioOutput>
#include <QIODevice>
#include <QThread>
#include <QQueue>
#include <QMutex>
#include <QWaitCondition>

class PcmPlayer : public QThread
{
    Q_OBJECT
public:
    explicit PcmPlayer(QObject *parent = 0);
    ~PcmPlayer();

    virtual void run();

    void play(QByteArray bytes);

  private:
    void sendToDevice(QByteArray byteArray);

    QQueue<QByteArray> queue;
    QMutex queueLock;
    QWaitCondition waitCondition;

    QAudioOutput *output;
    QAudioFormat format;
    QIODevice *ioDevice;
};

#endif // WAVPLAYER_H

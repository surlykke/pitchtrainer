#include <QDebug>
#include "pcmplayer.h"

PcmPlayer::PcmPlayer(QObject *parent) : QThread(parent) {
  qDebug() << "Ind i PcmPlayer" << "\n";
  //format.setCodec("audio/pcm");
  //format.setByteOrder(QAudioFormat::LittleEndian);
  /*format.setFrequency(44100);
  format.setChannels(2);
  format.setSampleSize(16);
  format.setSampleType(QAudioFormat::SignedInt);
  output = new QAudioOutput(format, this);
  ioDevice = output->start();
  start();*/
}

PcmPlayer::~PcmPlayer() {
  delete output;
}


void PcmPlayer::run() {
  while (true) {
    qDebug() << "Looper";
    queueLock.lock();
    while (queue.isEmpty()) {
      waitCondition.wait(&queueLock);
    }
    qDebug() << "Tar af";
    QByteArray bytes = queue.dequeue();
    queueLock.unlock();
    // sendToDevice(bytes);
  }
}

void PcmPlayer::sendToDevice(QByteArray bytes) {
  qDebug() << "Ind i sendToDevice";
  const char* data = bytes.constData();
  for (int index = 0; index < bytes.size(); ) {
    int written = ioDevice->write(data + index, bytes.size() - index);
    if (written == 0) {
      msleep(20);
    }
    index += written;
  }
  qDebug() << "Ud af sendToDevice";
}

void PcmPlayer::play(QByteArray bytes) {
  qDebug() << "Ind i play";
  queueLock.lock();
  qDebug() << "Putter på";
  queue.enqueue(bytes);
  queueLock.unlock();
  qDebug() << "Vækker";
  waitCondition.wakeOne();
  qDebug() << "Ud af play";
}

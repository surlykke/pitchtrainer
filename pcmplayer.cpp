/*
  Copyright 2010, 2011 Christian Surlykke

  This file is part of PitchTrainer.

  PitchTrainer is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, version 3

  PitchTrainer is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with PitchTrainer.  If not, see <http://www.gnu.org/licenses/>.
*/
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
    queueLock.lock();
    while (queue.isEmpty()) {
      waitCondition.wait(&queueLock);
    }
    QByteArray bytes = queue.dequeue();
    queueLock.unlock();
    qDebug() << "Playing..";
    // sendToDevice(bytes);
  }
}

void PcmPlayer::sendToDevice(QByteArray bytes) {
  qDebug() << "In to sendToDevice";
  const char* data = bytes.constData();
  for (int index = 0; index < bytes.size(); ) {
    int written = ioDevice->write(data + index, bytes.size() - index);
    if (written == 0) {
      msleep(20);
    }
    index += written;
  }
  qDebug() << "Leaving sendToDevice";
}

void PcmPlayer::play(QByteArray bytes) {
  qDebug() << "In to play";
  queueLock.lock();
  qDebug() << "Adding";
  queue.enqueue(bytes);
  queueLock.unlock();
  qDebug() << "Vækker";
  waitCondition.wakeOne();
  qDebug() << "Leaving play";
}

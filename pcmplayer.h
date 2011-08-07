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

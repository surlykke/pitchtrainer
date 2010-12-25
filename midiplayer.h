/*
  Copyright 2010 Christian Surlykke 
 
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
#ifndef MIDIPLAYER_H
#define MIDIPLAYER_H
#include "note.h"
#include <qprocess.h>
#include <QObject>
#include <QAudioOutput>
#include <QBuffer>
#include <QByteArray>
#include "settings.h"

class MidiPlayer: public QObject
{
    Q_OBJECT

public:
    MidiPlayer(Settings *settings);
    ~MidiPlayer();
    void playNote(Note note);
    void playInterval(Note n1, Note n2);

signals:
    void donePlaying();

public slots: 
    void pcmPlayed(QAudio::State state);

private:
    void play(unsigned char* mididata, unsigned long size);

    QByteArray midi2pcm(unsigned char *mididata, unsigned long size);

    Settings *settings;
    QAudioFormat format;
    QAudioOutput *audioOutput;
    QBuffer      pcmData;
};



#endif // MIDIPLAYER_H

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
#include <qprocess.h>
#include <QObject>
#include <QAudioOutput>
#include <QBuffer>
#include <QByteArray>
#include <QMutex>
#include "settings.h"
#include "pcmplayer.h"

class MidiPlayer: public QObject
{
    Q_OBJECT

public:
    explicit MidiPlayer(Settings *settings);
    ~MidiPlayer();

public slots:
    void playNote(int note);
    void playInterval(int note1, int note2);

private:
    void playMidi(unsigned char *mididata, unsigned long size);

    Settings *settings;

    PcmPlayer wavPlayer;
};



#endif // MIDIPLAYER_H

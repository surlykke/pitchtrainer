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
#include "midiplayer.h"
#include <stdio.h>
#include <unistd.h>
#include <QProcess>
#include <QByteArray>
#include <iostream>
#include <QDebug>
#include <QFile>
#include <QBuffer>
#include <QAudioOutput>
#include <QStringList>

extern "C" {
#include "wildmidi_lib.h"
}

MidiPlayer::MidiPlayer(Settings *settings):  QObject(), format() {
    this->settings = settings;
    WildMidi_Init("/etc/wildmidi/wildmidi.cfg", 44100, 0);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setFrequency(44100);
    format.setChannels(2);
    format.setSampleSize(16);
    format.setSampleType(QAudioFormat::SignedInt);
    audioOutput = new QAudioOutput(format, this);
}

MidiPlayer::~MidiPlayer() {
}

void MidiPlayer::playNote(int n)
{
    qDebug() << "-->playNote(" << n << ")";
    unsigned char noteMidi[] =  {
        0x4D, 0x54, 0x68, 0x64, 0x00, 0x00, 0x00, 0x06, // Midi header
        0x00, 0x00, 0x00, 0x01, 0x00, 0x90,             // 1 track, timedivision 144/second
        0x4D, 0x54, 0x72, 0x6B,                         // Track header
        0x00, 0x00, 0x00, 0x0F,                         // 15 bytes of event data
        0x00, 0xc0, settings->getInstrument(),          // Set instrument
        0x00, 0x90,    n, 0xF0,                         // note on at time 0
        0x60, 0x80,    n, 0x00,                         // note off at 96/144 beats
        0x00, 0xFF, 0x2F, 0x00                          // end of track
    };
    play(noteMidi, sizeof(noteMidi));
}

void MidiPlayer::playInterval(int n1, int n2)
{
    qDebug() << "-->playInterval(" << n1 << ", " << n2 << ")";
    unsigned char intervalMidi[] = {
        0x4D, 0x54, 0x68, 0x64, 0x00, 0x00, 0x00, 0x06, // Midi header
        0x00, 0x00, 0x00, 0x01, 0x00, 0x90,             // 1 track, timedivision 144/beat.
        0x4D, 0x54, 0x72, 0x6B,                         // Track header
        0x00, 0x00, 0x00, 0x18,                         // 18 bytes of event data
        0x00, 0xc0, settings->getInstrument(),          // Set instrument
        0x00, 0x90,   n1, 0xF0,                         // First note on at time 0
        0x60, 0x80,   n1, 0x00,                         // First note off at 96/144 beats
        0x60, 0x90,   n2, 0xF0,                         // Second note on at 96/144 beats
        0x81, 0x40, 0x80,   n2, 0x00,                   // Second note off at 192/144 beats
        0x00, 0xFF, 0x2F, 0x00                          // end of track
    };

    play(intervalMidi, sizeof(intervalMidi));
}

QByteArray MidiPlayer::midi2pcm(unsigned char *mididata, unsigned long size) {

    unsigned char* mididataCopy = (unsigned char*) malloc(size);  // WildMidi insists on freeing the memory used to hold mididata
    memcpy(mididataCopy, mididata, size);                         // on close, so we have to make a copy of mididata

    QByteArray result;
    midi* midiPtr = WildMidi_OpenBuffer(mididataCopy, size);
    char buf[1024];
    int outputsize;
    while ((outputsize = WildMidi_GetOutput(midiPtr, buf, 1024)) > 0) {
        result.append(buf, outputsize);
    }
    WildMidi_Close(midiPtr);
    qDebug() << "Ud af midi2pcm";
    return result;
}

void MidiPlayer::play(unsigned char *mididata, unsigned long size) {
    if (audioOutput->state() == QAudio::ActiveState) {
      return;
    }

    pcmData.setData(midi2pcm(mididata, size));
    pcmData.open(QIODevice::ReadOnly);
    audioOutput->start(&pcmData);
    connect(audioOutput,SIGNAL(stateChanged(QAudio::State)),SLOT(pcmPlayed(QAudio::State)));
 }

void MidiPlayer::pcmPlayed(QAudio::State state) {
      if(state == QAudio::IdleState) {
          emit donePlaying();
          pcmData.close();
     }
}
